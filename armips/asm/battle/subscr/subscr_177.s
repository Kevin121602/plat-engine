.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/subscr/subscr_177.s", 0

subscr_177:
    Message                             1087, TAG_NICK_ABILITY, BATTLER_WORKING, BATTLER_CLIENT_WORK
    Wait                                
    WaitFrames                          30
    End                                 
