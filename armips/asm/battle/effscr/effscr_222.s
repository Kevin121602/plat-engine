.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/battle_pokemon_params.s"
.include "armips/include/battle_subscr_def.s"
.include "armips/include/item_hold_effects.s"
.include "armips/include/moves.s"
.include "armips/include/types.s"


.create "build/battle/scr/effscr/be_seq_222.bin", 0

// Natural Gift
effscr_222:
    TryNaturalGift                      effscr_222_NotHoldingBerry
    CriticalCalc                        
    DamageCalc                          
    RemoveItem                          BATTLER_ATTACKER
    End

effscr_222_NotHoldingBerry:                                 
    SetVar                              OP_SET_FLAG, VAR_MOVE_STATUS_FLAG, MOVE_STATUS_FLAG_FAILED
    End                                 

.close