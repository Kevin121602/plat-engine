.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/item_hold_effects.s"
.include "armips/include/moves.s"

.create "build/battle/scr/effscr/be_seq_043.bin", 0

effscr_043:
    SetVar                              OP_ADD, VAR_CRITICAL_CHANCE, 1
    CriticalCalc                        
    DamageCalc                          
    End                                 

.close