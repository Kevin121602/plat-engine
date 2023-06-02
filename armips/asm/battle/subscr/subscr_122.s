.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/subscr/subscr_122.s", 0

subscr_122:
    If                                  EQUAL, VAR_BATTLE_TYPE, 74, 22
    TryTeleport                         20
    JumpToSubscript                     76
    Message                             469, TAG_NICK, BATTLER_ATTACKER
    Wait                                
    WaitFrames                          30
    FadeOut                             
    Wait                                
    SetVar                              OP_SET_FLAG, VAR_BATTLE_RESULT, 5
    IncGameStat                         BATTLER_ATTACKER, 1, 99
    End                                 
    SetVar                              OP_SET_FLAG, VAR_MOVE_STATUS_FLAG, 64
    End                                 
