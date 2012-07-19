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

#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"

void WorldSession::SendAuthResponse(uint8 code, bool shortForm, uint32 queuePos)
{
    WorldPacket packet(SMSG_AUTH_RESPONSE,16);

    packet.WriteBit(false); //isQueued
    packet.WriteBit(true); //hasAccountInfo

    packet << uint32(0);                                   // BillingTimeRemaining
    packet << uint8(Expansion());                          // 0 - normal, 1 - TBC, 2 - WOTLK, 3 - CATA; must be set in database manually for each account
    packet << uint32(0);                                   // Unk 4.3.2
    packet << uint8(Expansion());                          // Unknown, these two show the same
    packet << uint32(0);                                   // BillingTimeRested
    packet << uint8(0);                                    // BillingPlanFlags

    /*

    if (!shortForm)
    {
        packet << uint32(queuePos);                             // Queue position
        packet << uint8(0);                                     // Unk 3.3.0
    }
    */
    packet << uint8(code);

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}
