.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/subscr/subscr_170.s", 0

subscr_170:
    JumpToSubscript                     147
    If                                  FLAG_NEQ, VAR_SERVER_STATUS_FLAG, 4194304, 2
    JumpToSubscript                     25
    End                                 
