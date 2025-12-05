#include "Unit.hxx"



//1000f080
//VOID RendererVehicleInfo_1000f080(UNITPTR unit, S32 param_2) //thiscall
//{
//    undefined4 uVar2;
//    UNITSCRIPTSPTR scripts;
//
//    S32 iVar1 = (*(code*)*unit->ptr000)();
//    if (iVar1 != 0) 
//    {
//        scripts = unit->scripts_ptr;
//
//        uVar2 = RendererUnitHealthLine_10009be0 (scripts, (int)unit->HP, unit->unk015, unit->unk101, unit->unk032);
//
//        RendererUnitInfoLine_10009d30
//        ((int)*(short*)(param_2 + 6), (int)*(short*)(param_2 + 8), scripts->selector,
//            unit->vehicleLineHP, unit->vehicleLineExperience, unit->vehicleLineGun1,
//            unit->vehicleLineGun2, uVar2);
//    }
//    return;
//}
//
//1000ceb0
//VOID  RendererUnitInfo_1000ceb0(UNITPTR unit, S32 param_2)
//
//{
//    int iVar1;
//    undefined4 uVar2;
//    UNITSCRIPTSPTR scripts;
//
//    iVar1 = (*(code*)*unit->ptr000)();
//
//    if (iVar1 != 0) {
//        scripts = unit->scripts_ptr;
//        uVar2 = RendererUnitHealthLine_10009be0
//        (scripts, (S32)unit->HP, unit->unk015, unit->unk101, unit->unk032);
//        RendererUnitInfoLine_10009d30
//        ((S32)*(S16*)(param_2 + 6), (S32)*(short*)(param_2 + 8), scripts->selector,
//            unit->vehicleLineHP, unit->vehicleLineExperience, unit->vehicleLineGun1,
//            unit->vehicleLineGun2, uVar2);
//    }
//    return;
//}