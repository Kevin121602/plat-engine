.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/subscr/subscr_191.s", 0

subscr_191:
    Message                             832, TAG_NICK, BATTLER_ATTACKER
    Wait                                
    WaitFrames                          30
    ClearContinuation                   BATTLER_ATTACKER
    End                                 
