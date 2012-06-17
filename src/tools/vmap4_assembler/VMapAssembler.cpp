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

#include "TileAssembler.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

//=======================================================
// remove last return or LF and tailing SPACE
// remove all char after a #

void chompAndTrim(std::string& str)
{
    for (unsigned int i = 0; i < str.length(); ++i) 
    {
        char lc = str[i];
        if (lc == '#') 
        {
            str = str.substr(0, i);
            break;
        }
    }

    while (str.length() > 0) 
    {
        char lc = str[str.length()-1];
        if (lc == '\r' || lc == '\n' || lc == ' ') 
        {
            str = str.substr(0, str.length()-1);
        } 
        else 
        {
            break;
        }
    }
}

//=======================================================

/*
 * This callback method is called for each model found in the dir file.
 * return true if it should be included in the vmap
 */

bool modelNameFilter(char* pName)
{
#if 0
    bool result;
    result = !Wildcard::wildcardfit("*bush[0-9]*", pName);
    if (result) result = !Wildcard::wildcardfit("*shrub[0-9]*", pName);
    if (result) result = !Wildcard::wildcardfit("*_Bushes_*", pName);
    if (result) result = !Wildcard::wildcardfit("*_Bush_*", pName);
    if (!result) 
    {
        printf("%s", pName);
    }
#endif
    return true;
}

//=======================================================

int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 4)
    {
        printf("\nusage: %s <raw data dir> <vmap dest dir>\n", argv[0]);
        return 1;
    }

    char* src        = argv[1];
    char* dest        = argv[2];
    char* conffile = NULL;
    
    if (argc >= 4)
        conffile   = argv[3];

    VMAP::TileAssembler* ta = new VMAP::TileAssembler(std::string(src), std::string(dest));
    ta->setModelNameFilterMethod(modelNameFilter);

    if (!ta->convertWorld2())
    {
        printf("exit with errors\n");
        delete ta;
        return 1;
    }

    delete ta;
    printf("Ok, all done\n");
    return 0;
}
