.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/effscr/effscr_249.s", 0

effscr_249:
    TryToxicSpikes                      9
    PrepareMessage                      1063, TAG_NONE_DIR, BATTLER_ATTACKER_ENEMY
    SetVar                              OP_SET, VAR_ADD_STATUS_INDIRECT, 536871002
    End                                 
    SetVar                              OP_SET_FLAG, VAR_MOVE_STATUS_FLAG, 64
    End                                 
