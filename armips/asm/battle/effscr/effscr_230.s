.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/effscr/effscr_230.s", 0

effscr_230:
    PaybackDamageCalc                   
    CriticalCalc                        
    DamageCalc                          
    End                                 
