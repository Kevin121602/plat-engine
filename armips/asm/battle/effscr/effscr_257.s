.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/effscr/effscr_257.s", 0

effscr_257:
    SetVar                              OP_SET_FLAG, VAR_SERVER_STATUS_FLAG, 16
    SetVar                              OP_SET, VAR_DAMAGE_MULTI, 10
    IfMonData                           FLAG_NEQ, BATTLER_DEFENDER, BATTLE_MON_MOVE_EFFECTS, 262144, 4
    SetVar                              OP_SET, VAR_DAMAGE_MULTI, 20
    CriticalCalc                        
    DamageCalc                          
    End                                 
