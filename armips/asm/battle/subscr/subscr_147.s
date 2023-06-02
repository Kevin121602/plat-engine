.nds
.thumb

.include "armips/include/battle_scrcmd.s"

.include "armips/include/abilities.s"
.include "armips/include/battle_consts.s"
.include "armips/include/moves.s"

.create "build/move/battle/skill/subscr/subscr_147.s", 0

subscr_147:
    CheckAbility                        MODE_HAVE, BATTLER_ATTACKER, ABILITY_ROCK_HEAD, 34
    CheckAbility                        MODE_HAVE, BATTLER_ATTACKER, ABILITY_MAGIC_GUARD, 29
    SetVarFromVar                       OP_SET, VAR_BATTLER_WORK, VAR_ATTACKER
    SetVarFromVar                       OP_SET, VAR_HP_TEMP, VAR_HIT_DAMAGE
    If                                  EQUAL, VAR_HP_TEMP, 0, 3
    DamageDiv                           VAR_HP_TEMP, 3
    SetVar                              OP_SET_FLAG, VAR_SERVER_STATUS_FLAG, 64
    JumpToSubscript                     2
    Message                             279, TAG_NICK, BATTLER_ATTACKER
    Wait                                
    WaitFrames                          30
    End                                 
