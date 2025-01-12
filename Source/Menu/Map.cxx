/*
Copyright (c) 2024 Americus Maximus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Map.hxx"
#include "Strings.hxx"
#include "Version.hxx"

#include <stdlib.h>

// 0x10017e00
MAPPTR CLASSCALL ActivateMap(MAPPTR self)
{
    self->Unk00.Unk00 = 0; // TODO
    self->Unk00.Unk01 = 0; // TODO
    self->Unk00.Unk02 = 0; // TODO
    self->Unk00.Unk03 = 0; // TODO

    self->Unk01.Actors.Min = 0;
    self->Unk01.Actors.Max = 0;
    self->Unk01.Actors.Unk02 = 0; // TODO
    self->Unk01.Actors.Unk03 = 0; // TODO

    self->Unk01.TypeAndSize.Type = 0; // TODO
    self->Unk01.TypeAndSize.Width = 0;
    self->Unk01.TypeAndSize.Height = 0;

    self->Description = NULL;
    self->Pixels = NULL;
    self->Unk0x154 = NULL;

    return self;
}

// 0x10017e50
VOID CLASSCALL DisposeMap(MAPPTR self)
{
    if (self->Description != NULL)
    {
        free(self->Description);

        self->Description = NULL;
    }

    if (self->Unk0x154 != NULL)
    {
        free(self->Unk0x154);

        self->Unk0x154 = NULL;
    }

    if (self->Pixels != NULL)
    {
        free(self->Pixels);

        self->Pixels = NULL;
    }
}

// 0x1001aaa0
BOOL InitializeSingleMap(LPCSTR name, MAPPTR map)
{
    DisposeMap(map);

    ZIPFILE zip;
    ZeroMemory(&zip, sizeof(ZIPFILE));

    if (!OpenZipFile(&zip, name, ZIPFILE_OPEN_READ)) { return FALSE; }

    {
        U32 magic = 0;
        ReadZipFile(&zip, &magic, sizeof(U32));

        if (magic != MAP_FILE_SINGLE_MAGIC)
        {
            CloseZipFile(&zip);

            return FALSE;
        }
    }

    {
        U32 version = 0;
        ReadZipFile(&zip, &version, sizeof(U32));

        if (version != MODULE_VERSION_VALUE)
        {
            CloseZipFile(&zip);

            return FALSE;
        }
    }

    ReadZipFile(&zip, &map->Unk00, sizeof(MAPSTRUCT1));
    ReadZipFile(&zip, &map->Unk01, sizeof(MAPSTRUCT2));

    map->Unk01.Actors.Min = 1;
    map->Unk01.Actors.Max = 1;
    map->Unk01.Actors.Unk02 = 1; // TODO
    map->Unk01.Actors.Unk03 = 1; // TODO

    {
        U32 length = 0;
        ReadZipFile(&zip, &length, sizeof(U32));

        LPSTR description = (LPSTR)malloc(length + 1);
        description[length] = NULL;

        ReadZipFile(&zip, description, length);

        map->Description = AcquireCleanUnicodeString(description, TRUE);
    }

    if (map->Description[0] == '$')
    {
        U32 x = 0;
        LPSTR description = map->Description;

        while (description[x] != '\n' && description[x] != '\r') 
        { 
            x++; 
        }

        description[x] = NULL;
        do 
        { 
            do 
            { 
                x++; 
            } 
            while (description[x] == '\n'); 
        } 
        while (description[x] == '\r');

        map->Description = (LPSTR)malloc(strlen(&description[x]) + 1);

        strcpy(map->Description, &description[x]);

        map->Unk0x154 = (LPSTR)malloc(strlen(description));

        strcpy(map->Unk0x154, description);

        free(description);
    }
    else { map->Unk0x154 = NULL; }

    for (U32 x = 0; map->Description[x] != NULL; x++)
    {
        if (map->Description[x] == '#') 
        { 
            map->Description[x] = NULL; break; 
        }
    }

    {
        // Calculating the size of the minimap
        CONST U32 size = map->Unk01.TypeAndSize.Width <= MAX_MAP_SIZE && map->Unk01.TypeAndSize.Height <= MAX_MAP_SIZE
            ? map->Unk01.TypeAndSize.Height * map->Unk01.TypeAndSize.Width * sizeof(PIXEL)
            : map->Unk01.TypeAndSize.Height * map->Unk01.TypeAndSize.Width / 2;

        map->Pixels = (PIXEL*)malloc(size);
        ReadZipFile(&zip, map->Pixels, size);
    }

    CloseZipFile(&zip);

    return TRUE;
}

// 0x10018240
BOOL InitializeMultiMap(LPCSTR name, MAPPTR map)
{
    DisposeMap(map);

    ZIPFILE zip;
    ZeroMemory(&zip, sizeof(ZIPFILE));

    if (!OpenZipFile(&zip, name, ZIPFILE_OPEN_READ)) 
    { 
        return FALSE; 
    }

    {
        U32 magic = 0;
        ReadZipFile(&zip, &magic, sizeof(U32));

        if (magic != MAP_FILE_MULTI_MAGIC)
        {
            CloseZipFile(&zip);

            return FALSE;
        }
    }

    {
        U32 version = 0;
        ReadZipFile(&zip, &version, sizeof(U32));
        if (version != MODULE_MULTI_MAP_VERSION_VALUE)
        {
            CloseZipFile(&zip);

            return FALSE;
        }
    }

    ReadZipFile(&zip, &map->Unk00, sizeof(MAPSTRUCT1));
    ReadZipFile(&zip, &map->Unk01.Actors, sizeof(MAPMINMAX));

    ReadZipFile(&zip, &map->Unk02, MAX_MAP_STRUCT3_COUNT * sizeof(MAPSTRUCT3));

    for (U32 x = 0; x < MAX_MAP_STRUCT3_COUNT; x++)
    {
        if (map->Unk02[x].Unk00 < 0 || map->Unk02[x].Unk01 < 0
            || map->Unk01.TypeAndSize.Width <= map->Unk02[x].Unk00 || map->Unk01.TypeAndSize.Height <= map->Unk02[x].Unk01
            || map->Unk02[x].Unk02 < 0 || (MAX_MAP_SIZE - 1) < map->Unk02[x].Unk02)
        {
            map->Unk02[x].Unk00 = 0;
            map->Unk02[x].Unk02 = 0;
            map->Unk02[x].Unk01 = 0;
        }
    }

    ReadZipFile(&zip, &map->Unk01.TypeAndSize, sizeof(MAPTYPESIZE));

    for (U32 x = 0; x < MAX_MAP_STRUCT4_COUNT; x++)
    {
        ReadZipFile(&zip, &map->Unk03[x], sizeof(U32));
        map->Unk03[x].Unk01 = 0xffff; // TODO
    }

    {
        CHAR buffer[272]; // TODO
        ReadZipFile(&zip, buffer, 272); // TODO
    }

    FUN_10017f60(map, &zip);

    {
        U32 length = 0;
        ReadZipFile(&zip, &length, sizeof(U32));

        LPSTR description = (LPSTR)malloc(length + 1);
        description[length] = NULL;

        ReadZipFile(&zip, description, length);

        map->Description = AcquireCleanUnicodeString(description, TRUE);
    }

    if (map->Description[0] == '$')
    {
        U32 x = 0;
        LPSTR description = map->Description;

        while (description[x] != '\n' && description[x] != '\r') 
        { 
            x++; 
        }

        description[x] = NULL;

        do 
        { 
            do 
            { 
                x++; 
            } 
            while (description[x] == '\n'); 
        } 
        while (description[x] == '\r');

        map->Description = (LPSTR)malloc(strlen(&description[x]) + 1);

        strcpy(map->Description, &description[x]);

        map->Unk0x154 = (LPSTR)malloc(strlen(description));

        strcpy(map->Unk0x154, description);

        free(description);
    }
    else { map->Unk0x154 = NULL; }

    for (U32 x = 0; map->Description[x] != NULL; x++)
    {
        if (map->Description[x] == '#') { map->Description[x] = NULL; break; }
    }

    {
        // Calculating the size of the minimap
        CONST U32 size = map->Unk01.TypeAndSize.Width <= MAX_MAP_SIZE && map->Unk01.TypeAndSize.Height <= MAX_MAP_SIZE
            ? map->Unk01.TypeAndSize.Height * map->Unk01.TypeAndSize.Width * sizeof(PIXEL)
            : map->Unk01.TypeAndSize.Height * map->Unk01.TypeAndSize.Width / 2; // TODO

        map->Pixels = (PIXEL*)malloc(size);
        ReadZipFile(&zip, map->Pixels, size);
    }

    CloseZipFile(&zip);

    return TRUE;
}

// 0x10017f60 parsing scripts
BOOL FUN_10017f60(MAPPTR map, ZIPFILEPTR file) // TODO
{
    U32 count = 0;
    ReadZipFile(file, &count, sizeof(U32));

    for (U32 x = 0; x < count; x++)
    {
        U32 length = 0;
        ReadZipFile(file, &length, sizeof(U32));

        if (length != 0)
        {
            LPVOID value = malloc(length); // TODO
            ReadZipFile(file, value, length);
            FUN_10017FE0(map, value); // TODO Decoding script commands
            free(value);
        }
    }

    return TRUE;
}

//Decoding script commands
S32 FUN_10017FE0(MAPPTR map, LPVOID value)
{
    S32* result; // eax
    S32* v3; // ebp
    S32 v4; // edi
    S32* v5; // esi
    S32 v6; // eax
    S32 v7; // [esp+4h] [ebp-1004h]
    S8 v8; // [esp+8h] [ebp-1000h] BYREF

    result = (S32*)value;
    v3 = (S32*)value;
    if (*(S32*)value != 0x7FFFFFFF) // Filter conditions and parameters for these conditions
    {
        v4 = v7;
        v5 = (S32*)&v8;
        do
        {
            v6 = *v3;
            if (*v3 >= 0)
            {
                switch (v6)
                {
                    case And:
                    case Or:
                    case IfCountDown:
                    case IfTimeFromMissionStart:
                    case IfGroupBehaviour:
                    case IfGroupBehaviourZone1:
                    case IfGroupBehaviourZone2:
                    case IfGroupBehaviourGroup1:
                    case IfGroupBehaviourGroup2:
                        v4 = *(v5 - 2);
                        --v5;
                        break;
                    case IfGroupUnitCountOfType:
                    case IfPlayerUnitCountOfType:
                    case IfZoneUnitCountForGroup:
                    case IfZoneUnitCountForPlayer:
                    case IfPlanesForPlayerCount:
                    case IfPlanesForPlayerMissionsCount:
                    case IfZoneUnitCountPercentForGroup:
                    case IfZoneUnitCountPercentForPlayer:
                        v4 = *(v5 - 4);
                        v5 -= 3;
                        break;
                    case ReturnIfFalse:
                    case TimerStop:
                    case ZonePointTo:
                    case PhraseShow:
                    case CountDownStart:
                    case CampaignSetNextMission:
                    case MissionComplete:
                    case PlanesRouteAddObject:
                    case PlanesRouteAddObjectAsDrop:
                        --v5;
                        goto LABEL_22;
                    case PlanesForPlayerSendToZoneAndLand:
                    case PlanesForPlayerSendToObjectAndLand:
                    case MultiReinforcementStart:
                        v5 -= 4;
                        goto LABEL_22;
                    case TimerStart:
                    case GroupBehaviourSet:
                    case GroupBehaviourZone1Set:
                    case GroupBehaviourZone2Set:
                    case GroupBehaviourGroup1Set:
                    case GroupBehaviourGroup2Set:
                    case VariableSet:
                    case PhraseShowAndPointToMarker:
                    case GroupGiveToPlayer:
                    case GroupShotOneRocketArtilleryToZone:
                    case GroupShotOneRocketArtilleryToObject:
                        v5 -= 2;
                        goto LABEL_22;
                    case PlanesAddToPlayer:
                    case PlanesMissionsAddToPlayer:
                    case PlanesRouteSendAndLandForPlayer:
                    case VariableModify:
                        v5 -= 3;
                        goto LABEL_22;
                    case Negate:
                    case IfTimerComplete:
                    case IfObjectIsDestroyed:
                        v4 = *(v5 - 1);
                        break;
                    case IfGroupUnitCountPercentOfTypeRelativeToGroup:
                        v4 = *(v5 - 6);
                        v5 -= 5;
                        break;
                    case IfPlayerUnitCountPercentOfTypeRelativeToPlayer:
                        v4 = *(v5 - 5);
                        v5 -= 4;
                        break;
                    case GroupResurrectThroughFlagWithParams:
                        v5 -= 7;
                        goto LABEL_22;
                    case ReinforcementSend:
                        v5 -= 5;
                    LABEL_22:
                        v4 = *v5;
                        break;
                    case IfGroupWasAttackedTimeAgo:
                    case IfVariableValue:
                        v4 = *(v5 - 3);
                        v5 -= 2;
                        break;
                    case IfMissionStart:
                        *v5++ = v4;
                        break;
                    case MultiReinforcementForFlags:
                        v4 = *(v5 - 5);
                        v5 -= 5;
                        //sub_100181F0(a1, v4);
                        break;
                    case MultiPlanesForFlags:
                    case MultiPlanesMissionsForFlags:
                        v4 = *(v5 - 3);
                        v5 -= 3;
                        //sub_100181F0(a1, v4);
                        break;
                    case MultiPhraseForFlags:
                        v4 = *(v5 - 2);
                        v5 -= 2;
                        //sub_100181F0(a1, v4);
                        break;
                    default:
                        break;
                }
            }
            else
            {
                *v5++ = v6 & 0x7FFFFFFF; //remove the negative value from the parameter
            }
            result = (S32*)v3[1];
            ++v3;
        } 
        while (result != (S32*)ScriptEND);
    }
    return (S32)result;
    //return 0;
}

//_WORD* sub_100181F0(int a1, int a2)
//{
//    S32 v2; // edx
//    S16* v3; // ecx
//    S32 v4; // edi
//    S16 v5; // dx
//    S16* result; // eax
//    S32 i; // ecx
//
//    v2 = -1;
//    v3 = (__int16*)(a1 + 144);
//    v4 = 32;
//    do
//    {
//        if (*v3 > v2)
//            v2 = *v3;
//        v3 += 3;
//        --v4;
//    } while (v4);
//    v5 = v2 + 1;
//    result = (_WORD*)(a1 + 144);
//    for (i = 0; i < 32; ++i)
//    {
//        if (((1 << i) & a2) != 0)
//            *result = v5;
//        result += 3;
//    }
//    return result;
//}