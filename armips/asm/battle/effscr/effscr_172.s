.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/effscr/effscr_172.s", 0

effscr_172:
    FollowMe                            
    PrepareMessage                      484, TAG_NICK, BATTLER_ATTACKER
    SetVar                              OP_SET, VAR_ADD_STATUS_INDIRECT, 536871002
    End                                 
