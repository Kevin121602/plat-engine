.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/subscr/subscr_155.s", 0

subscr_155:
    IfMonData                           EQUAL, BATTLER_DEFENDER, BATTLE_MON_HP, 0, 15
    SetMonData                          OP_CLEAR_FLAG, BATTLER_DEFENDER, BATTLE_MON_CONDITION, 7
    Message                             302, TAG_NICK, BATTLER_DEFENDER
    Wait                                
    SetStatusIcon                       BATTLER_DEFENDER, STATUS_NORMAL
    WaitFrames                          30
    End                                 
