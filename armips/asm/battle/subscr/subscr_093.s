.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/item_hold_effects.s"
.include "armips/include/moves.s"

.create "build/battle/scr/subscr/sub_seq_093.bin", 0

subscr_093:
    CheckSubstitute                     BATTLER_DEFENDER, 27
    IfMonData                           FLAG_EQ, BATTLER_DEFENDER, BATTLE_MON_CONDITION_2, 134217728, 21
    IfMonData                           FLAG_NEQ, BATTLER_DEFENDER, BATTLE_MON_CONDITION, 7, 15
    JumpToSubscript                     76
    SetMonData                          OP_SET_FLAG, BATTLER_DEFENDER, BATTLE_MON_CONDITION_2, 134217728
    Message                             411, TAG_NICK, BATTLER_DEFENDER, NaN, NaN, NaN, NaN, NaN
    Wait                                
    WaitTime                            30
    End                                 
    SetVar                              OP_SET_FLAG, VAR_MOVE_STATUS_FLAG, 64
    End                                 

.close