.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/item_hold_effects.s"
.include "armips/include/moves.s"

.create "build/battle/scr/movscr/waza_seq_083.bin", 0

movscr_083:
    PrepareMessage                      242, TAG_NICK, BATTLER_DEFENDER, NaN, NaN, NaN, NaN, NaN
    JumpToMoveEffectScript              

.close