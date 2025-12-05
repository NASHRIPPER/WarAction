#include "Interface.hxx"
#include "Assets.hxx"

//undefined4 InterfaceGamma_10057080(undefined4 type, char* name, undefined4 palette)
//
//{
//    char cVar1;
//    int iVar2;
//    undefined4 uVar3;
//
//    LPVOID content = AllocateZero(140);
//    *(undefined4*)((int)content + 4) = type;
//    iVar2 = 8 - (int)name;
//    do {
//        cVar1 = *name;
//        name[(int)content + iVar2] = cVar1;
//        name = name + 1;
//    } while (cVar1 != '\0');
//    *(undefined4*)((int)content + 0x88) = palette;
//    *(LPVOID*)content = DAT_10295148;
//    DAT_10295148 = content;
//    if (DAT_1029514c != 0) {
//        uVar3 = FUN_100583a0(content);
//        return uVar3;
//    }
//    return 1;
//}