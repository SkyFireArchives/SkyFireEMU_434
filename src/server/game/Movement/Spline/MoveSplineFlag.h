/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
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

#ifndef SKYFIRESERVER_MOVESPLINEFLAG_H
#define SKYFIRESERVER_MOVESPLINEFLAG_H
#include "MovementTypedefs.h"

#include <string>

namespace Movement
{
#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

    class MoveSplineFlag
    {
    public:
        enum eFlags{
            None              = 0x00000000,
            Forward              = 0x00000001,
            Backward          = 0x00000002,
            StrafeLeft          = 0x00000004,
            Straferight          = 0x00000008,
            TurnLeft          = 0x00000010,
            TurnRight          = 0x00000020,                                // x00-xFF(first byte) used as animation Ids storage in pair with Animation flag
            Falling              = 0x00000040,           // Affects elevation computation, can't be combined with Parabolic flag
            Trajectory          = 0x00000100,
            Walkmode          = 0x00000200,
            Flying              = 0x00000400,           // Smooth movement(Catmullrom interpolation mode), flying animation
            FixedOrientation  = 0x00000800,           // Model orientation fixed
            FinalPoint          = 0x00001000,
            FinalTarget          = 0x00002000,
            FinalOrientation  = 0x00004000,
            Catmullrom          = 0x00008000,           // Used Catmullrom interpolation mode
            Cyclic              = 0x00010000,           // Movement by cycled spline
            EnterCycle          = 0x00020000,           // Everytimes appears with cyclic flag in monster move packet, erases first spline vertex after first cycle done
            AnimationTier     = 0x00040000,           // Plays animation after some time passed
            Frozen              = 0x00008000,           // Will never arrive
            Unknown5          = 0x00100000,
            Unknown6          = 0x00200000,
            Unknown7          = 0x00400000,
            Unknown8          = 0x00800000,
            Unknown9          = 0x01000000,
            Unknown10          = 0x02000000,
            MovingBackwards      = 0x04000000,
            UsePathSmoothing  = 0x08000000,
            Animation          = 0x10000000,
            UncompressedPath  = 0x20000000,
            Unknown11          = 0x40000000,
            Unknown12          = 0x80000000,
            // Masks
            Mask_Final_Facing = FinalPoint | FinalTarget | FinalOrientation,
            // animation ids stored here, see AnimType enum, used with Animation flag
            Mask_Animations = 0xFF,
            // flags that shouldn't be appended into SMSG_MONSTER_MOVE\SMSG_MONSTER_MOVE_TRANSPORT packet, should be more probably
            Mask_No_Monster_Move = Mask_Final_Facing | Mask_Animations,
            // CatmullRom interpolation mode used
            Mask_CatmullRom = Flying | Catmullrom,
            // Unused, not suported flags
            Mask_Unused = EnterCycle|Frozen|Unknown5|Unknown6|Unknown7|Unknown8|Unknown10|Unknown11|Unknown12,
        };

        inline uint32& raw() { return (uint32&)*this;}
        inline const uint32& raw() const { return (const uint32&)*this;}

        MoveSplineFlag() { raw() = 0; }
        MoveSplineFlag(uint32 f) { raw() = f; }
        MoveSplineFlag(const MoveSplineFlag& f) { raw() = f.raw(); }

        // Constant interface

        bool isSmooth() const { return raw() & Mask_CatmullRom;}
        bool isLinear() const { return !isSmooth();}
        bool isFacing() const { return raw() & Mask_Final_Facing;}

        uint8 getAnimationId() const { return animId;}
        bool hasAllFlags(uint32 f) const { return (raw() & f) == f;}
        bool hasFlag(uint32 f) const { return (raw() & f) != 0;}
        uint32 operator & (uint32 f) const { return (raw() & f);}
        uint32 operator | (uint32 f) const { return (raw() | f);}
        std::string ToString() const;

        // Not constant interface

        void operator &= (uint32 f) { raw() &= f;}
        void operator |= (uint32 f) { raw() |= f;}

        void EnableAnimation(uint8 anim) { raw() = (raw() & ~(Mask_Animations|Falling|FixedOrientation)) | Animation|anim;}
        void EnableParabolic() { raw() = (raw() & ~(Mask_Animations|Falling|Animation)) | FixedOrientation;}
        void EnableFalling() { raw() = (raw() & ~(Mask_Animations|FixedOrientation|Animation)) | Falling;}
        void EnableFlying() { raw() = (raw() & ~Catmullrom) | Flying; }
        void EnableCatmullRom() { raw() = (raw() & ~Flying) | Catmullrom; }
        void EnableFacingPoint() { raw() = (raw() & ~Mask_Final_Facing) | FinalPoint;}
        void EnableFacingAngle() { raw() = (raw() & ~Mask_Final_Facing) | FinalOrientation;}
        void EnableFacingTarget() { raw() = (raw() & ~Mask_Final_Facing) | FinalTarget;}

        uint8 animId       : 8;
        bool done          : 1;
        bool falling       : 1;
        bool no_spline     : 1;
        bool walkmode      : 1;
        bool flying        : 1;
        bool fixedorientation : 1;
        bool finalpoint   : 1;
        bool finaltarget  : 1;
        bool finalangle   : 1;
        bool catmullrom    : 1;
        bool cyclic        : 1;
        bool entercycle   : 1;
        bool animation     : 1;
        bool frozen        : 1;
        bool unknown5      : 1;
        bool unknown6      : 1;
        bool unknown7      : 1;
        bool unknown8      : 1;
        bool orientationinversed : 1;
        bool unknown10     : 1;
        bool unknown11     : 1;
        bool unknown12     : 1;
        bool unknown13     : 1;
    };
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif
}

#endif // SKYFIRESERVER_MOVESPLINEFLAG_H
