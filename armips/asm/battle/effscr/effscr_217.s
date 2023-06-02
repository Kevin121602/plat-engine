.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/effscr/effscr_217.s", 0

effscr_217:
    CheckSubstitute                     BATTLER_DEFENDER, 20
    IfMonData                           FLAG_EQ, BATTLER_DEFENDER, BATTLE_MON_CONDITION, 7, 6
    SetVar                              OP_SET, VAR_DAMAGE_MULTI, 10
    Jump                                8
    SetVar                              OP_SET, VAR_DAMAGE_MULTI, 20
    SetVar                              OP_SET, VAR_ADD_STATUS_INDIRECT, 536871029
    CriticalCalc                        
    DamageCalc                          
    End                                 
