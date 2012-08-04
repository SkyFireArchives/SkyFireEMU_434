/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "MovementPacketBuilder.h"
#include "MoveSpline.h"
#include "WorldPacket.h"

namespace Movement
{
    inline void operator << (ByteBuffer& b, const Vector3& v)
    {
        b << v.x << v.y << v.z;
    }

    inline void operator >> (ByteBuffer& b, Vector3& v)
    {
        b >> v.x >> v.y >> v.z;
    }

    enum MonsterMoveType
    {
        MonsterMoveNormal       = 0,
        MonsterMoveStop         = 1,
        MonsterMoveFacingSpot   = 2,
        MonsterMoveFacingTarget = 3,
        MonsterMoveFacingAngle  = 4
    };

    void PacketBuilder::WriteCommonMonsterMovePart(const MoveSpline& move_spline, WorldPacket& data)
    {
        MoveSplineFlag splineflags = move_spline.splineflags;

        data << uint8(0);                                       // sets/unsets MOVEMENTFLAG2_UNK7 (0x40)
        data << move_spline.spline.getPoint(move_spline.spline.first());
        data << move_spline.GetId();

        switch (splineflags & MoveSplineFlag::Mask_Final_Facing)
        {
            case MoveSplineFlag::FinalTarget:
                data << uint8(MonsterMoveFacingTarget);
                data << move_spline.facing.target;
                break;
            case MoveSplineFlag::FinalOrientation:
                data << uint8(MonsterMoveFacingAngle);
                data << move_spline.facing.angle;
                break;
            case MoveSplineFlag::FinalPoint:
                data << uint8(MonsterMoveFacingSpot);
                data << move_spline.facing.f.x << move_spline.facing.f.y << move_spline.facing.f.z;
                break;
            default:
                data << uint8(MonsterMoveNormal);
                break;
        }

        // add fake Enter_Cycle flag - needed for client-side cyclic movement (client will erase first spline vertex after first cycle done)
        splineflags.entercycle = move_spline.isCyclic();
        data << uint32(splineflags & ~MoveSplineFlag::Mask_No_Monster_Move);

        if (splineflags.animation)
        {
            data << splineflags.getAnimationId();
            data << move_spline.effect_start_time;
        }

        data << move_spline.Duration();

        if (splineflags.fixedorientation)
        {
            data << move_spline.vertical_acceleration;
            data << move_spline.effect_start_time;
        }
    }

    void WriteLinearPath(const Spline<int32>& spline, ByteBuffer& data)
    {
        uint32 last_idx = spline.getPointCount() - 3;
        const Vector3 * real_path = &spline.getPoint(1);

        data << last_idx;
        data << real_path[last_idx];   // destination
        if (last_idx > 1)
        {
            Vector3 middle = (real_path[0] + real_path[last_idx]) / 2.f;
            Vector3 offset;
            // first and last points already appended
            for (uint32 i = 1; i < last_idx; ++i)
            {
                offset = middle - real_path[i];
                data.appendPackXYZ(offset.x, offset.y, offset.z);
            }
        }
    }

    void WriteCatmullRomPath(const Spline<int32>& spline, ByteBuffer& data)
    {
        uint32 count = spline.getPointCount() - 3;
        data << count;
        data.append<Vector3>(&spline.getPoint(2), count);
    }

    void WriteCatmullRomCyclicPath(const Spline<int32>& spline, ByteBuffer& data)
    {
        uint32 count = spline.getPointCount() - 3;
        data << uint32(count + 1);
        data << spline.getPoint(1); // fake point, client will erase it from the spline after first cycle done
        data.append<Vector3>(&spline.getPoint(1), count);
    }

    void PacketBuilder::WriteMonsterMove(const MoveSpline& move_spline, WorldPacket& data)
    {
        WriteCommonMonsterMovePart(move_spline, data);

        const Spline<int32>& spline = move_spline.spline;
        MoveSplineFlag splineflags = move_spline.splineflags;
        if (splineflags & MoveSplineFlag::UncompressedPath)
        {
            if (splineflags.cyclic)
                WriteCatmullRomCyclicPath(spline, data);
            else
                WriteCatmullRomPath(spline, data);
        }
        else
            WriteLinearPath(spline, data);
    }

    void PacketBuilder::WriteBytes(const MoveSpline& move_spline, ByteBuffer& data)
     {
        uint32 nodes = move_spline.getPath().size();

        //SlineType
        /*switch (hasSplineType)
                        {
                            case 0:
                                splineType = SplineType.FacingAngle;
                                break;
                            case 1:
                                splineType = SplineType.FacingSpot;
                                break;
                            case 2:
                                splineType = SplineType.FacingTarget;
                                break;
                            case 3:
                                splineType = SplineType.Normal;
                                break;
                        }
        */
        data.WriteBits(0, 2); //SPLINEMODE_LINEAR = 0
        data.WriteBit(false);
        data.WriteBits(nodes, 22);

        data.WriteBits(3, 2);

        MoveSplineFlag splineflags = move_spline.splineflags;

        if (splineflags.walkmode)
        {

            uint8 guidMask[] = {  4, 3, 7, 2, 6, 1, 0, 5 };
            data.WriteGuidMask(move_spline.facing.target, guidMask, 8);
        }
     }

    void PacketBuilder::WriteCreate(MoveSpline const& moveSpline, ByteBuffer& data)
    {
        data.WriteBits(uint8(moveSpline.spline.mode()), 2);
        data.WriteBit(moveSpline.splineflags & (MoveSplineFlag::Trajectory | MoveSplineFlag::Animation));
        data.WriteBits(moveSpline.getPath().size(), 22);
        switch (moveSpline.splineflags & MoveSplineFlag::Mask_Final_Facing)
        {
            case MoveSplineFlag::FinalTarget:
            {
                ObjectGuid targetGuid = moveSpline.facing.target;
                data.WriteBits(2, 2);
                data.WriteBit(targetGuid[4]);
                data.WriteBit(targetGuid[3]);
                data.WriteBit(targetGuid[7]);
                data.WriteBit(targetGuid[2]);
                data.WriteBit(targetGuid[6]);
                data.WriteBit(targetGuid[1]);
                data.WriteBit(targetGuid[0]);
                data.WriteBit(targetGuid[5]);
                break;
            }
            case MoveSplineFlag::FinalOrientation:
                data.WriteBits(0, 2);
                break;
            case MoveSplineFlag::FinalPoint:
                data.WriteBits(1, 2);
                break;
            default:
                data.WriteBits(3, 2);
                break;
        }

        data.WriteBit((moveSpline.splineflags & MoveSplineFlag::Trajectory) && moveSpline.effect_start_time < moveSpline.Duration());
        data.WriteBits(moveSpline.splineflags.raw(), 25);
    }

    void PacketBuilder::WriteData(MoveSpline const& moveSpline, ByteBuffer& data)
    {
        MoveSplineFlag splineFlags = moveSpline.splineflags;

        if ((splineFlags & MoveSplineFlag::Trajectory) && moveSpline.effect_start_time < moveSpline.Duration())
            data << moveSpline.vertical_acceleration;   // added in 3.1

        data << moveSpline.timePassed();

        switch (moveSpline.splineflags & MoveSplineFlag::Mask_Final_Facing)
        {
            case MoveSplineFlag::FinalOrientation:
                data << moveSpline.facing.angle;
                break;
            case MoveSplineFlag::FinalTarget:
            {
                ObjectGuid facingGuid = moveSpline.facing.target;
                data.WriteByteSeq(facingGuid[5]);
                data.WriteByteSeq(facingGuid[3]);
                data.WriteByteSeq(facingGuid[7]);
                data.WriteByteSeq(facingGuid[1]);
                data.WriteByteSeq(facingGuid[6]);
                data.WriteByteSeq(facingGuid[4]);
                data.WriteByteSeq(facingGuid[2]);
                data.WriteByteSeq(facingGuid[0]);
                break;
            }
        }


        uint32 nodes = moveSpline.getPath().size();
        for (uint32 i = 0; i < nodes; ++i)
        {
            data << float(moveSpline.getPath()[i].z);
            data << float(moveSpline.getPath()[i].x);
            data << float(moveSpline.getPath()[i].y);
        }

        if (splineFlags.finalpoint)
            data << moveSpline.facing.f.x << moveSpline.facing.f.z << moveSpline.facing.f.y;

        data << float(1.f);                             // splineInfo.duration_mod_next; added in 3.1
        data << moveSpline.Duration();
        if (splineFlags & (MoveSplineFlag::Trajectory | MoveSplineFlag::Animation))
            data << moveSpline.effect_start_time;       // added in 3.1

        data << float(1.f);                             // splineInfo.duration_mod; added in 3.1

        if (!moveSpline.isCyclic())
        {
            Vector3 dest = moveSpline.FinalDestination();
            data << float(dest.z);
            data << float(dest.x);
            data << float(dest.y);
        }
        else
            data << Vector3::zero();

        data << moveSpline.GetId();
    }
}
