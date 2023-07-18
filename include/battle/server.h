#ifndef __BATTLE_SERVER_H
#define __BATTLE_SERVER_H

#include "global.h"
#include "item.h"

#include "constants/moves.h"

#define PARTNER(battler)    (battler ^ 2)
#define ENEMY(battler)      (battler ^ 1)
#define ACROSS(battler)     (battler ^ 3)

struct __attribute__((packed)) BattleMove {
    u16 effect;
    u8  pss;
    u8  power;
    u8  type;
    u8  accuracy;
    u8  pp;
    u8  secondaryChance;
    u16 target;
    s8  priority;
    u8  flag;
    u8  unk[4];
};

struct DamageDealtToMon {
    int dealt[4];       // This is the amount of damage dealt to a given mon by each client
    int lastDamager;    // This is the *last* client that dealt damage to this mon
    int allDamagers;    // This is a mask of *all* clients that dealt damage to this mon
};

struct __attribute__((packed)) SingleTurnEffects {
    u32 struggling      :1,
        ppDecremented   :1,
        protected       :1,
        helpingHand     :1,
        magicCoat       :1,
        snatching       :1,
        roosting        :1,
        fleeing         :2,
        enduring        :1,
        _padding        :22;

    struct DamageDealtToMon physDamage;
    struct DamageDealtToMon specDamage;
    
    int lastDamageDealt;    // This is for all damage types
    int lastDamagingClient;
    int assuranceDamageReceived;
};

struct __attribute__((packed)) SelfSingleTurnEffects {
    u32 noPressure          :1, // this should normally be on
        lightningRodActive  :1,
        stormDrainActive    :1,
        moldBreaker         :1,
        trickRoom           :1,
        endureItem          :1,
        rolloutCount        :3,
        _padding            :23;
    
    int physicalDamage;
    int physicalTarget;
    int specialDamage;
    int specialTarget;
    int statusFlag;
    int shellBellDamage;
};

struct __attribute__((packed)) MoveFailedChecks {
    u32 fullyParalyzed      :1,
        ineffective         :1,
        imprisoned          :1,
        fullyInfatuated     :1,
        disabled            :1,
        taunted             :1,
        flinched            :1,
        confusionSelfHit    :1,
        gravityActive       :1,
        healBlockActive     :1,
        _padding            :22;
};

struct __attribute__((packed)) MoveEffects {
    u32 disabledTurns           :3,
        encoredTurns            :3,     // TODO: can reduce to 2 bits for gen 5
        chargedTurns            :2,
        tauntedTurns            :3,
        protectChainCount       :2,
        perishSongTurns         :2,
        rolloutChainCount       :3,
        furyCutterChainCount    :3,
        stockpileCount          :3,
        stockpileDefBoosts      :3,
        stockpileSpdBoosts      :3,
        truantActive            :1,
        flashFireActive         :1;
    
    u32 lockOnTarget            :2,
        mimicSlot               :4,     // Bitmask for which move slots are Mimic'd slots (why the fuck is this a mask???)
        boundTarget             :2,
        meanLookTarget          :2,     // TODO: no longer maintains trap after a Baton Pass
        lastResortMask          :3,
        magnetRiseTurns         :3,
        healBlockTurns          :3,
        embargoTurns            :3,
        unburdenActive          :1,     // TODO: make sure this interacts correctly with Neutralizing Gas
        metronome               :4,     // this is for the item, not the move; stores the number of consecutive turns the same move has been used; TODO: we can reduce the bit allocation to 3 here
        oneTimeAccuracyMax      :1,     // micle berry
        oneTimeSpeedMax         :1,     // custap berry
        quickClawActive         :1,
        meFirstActive           :1,
        _padding                :1;
    
    int rechargeTurnCount;              // stores the turn counter for recharging after Hyper Beam
    int fakeOutTurnCount;
    int slowStartInitTurn;
    int meFirstTurnCount;
    int substituteHP;
    u32 formRand;                       // used for unown, spinda

    u16 disabledMove;
    u16 bindingMove;
    u16 encoredMove;
    u16 encoredMovePos;
    u16 lastResortMoves[4];
    u16 choicedMove;
    u16 transformedGender;

    int itemHPRestore;
};

struct __attribute__((packed)) BattlePokemon {
    u16 species;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
    u16 moves[4];

    u32 hpIV        :5,
        attackIV    :5,
        defenseIV   :5,
        speedIV     :5,
        spAttackIV  :5,
        spDefenseIV :5,
        isEgg       :1,
        hasNickname :1;
    
    s8  statBoosts[8];
    
    int weight;

    u8  type1;
    u8  type2;
    u8  formNum     :5,
        isShiny     :1,
        _padding_A  :2;
    u8  ability;

    u32 forecastDone        :1,
        intimidateDone      :1,
        traceDone           :1,
        downloadDone        :1,
        anticipationDone    :1,
        forewarnDone        :1,
        slowStartStarted    :1,
        slowStartFinished   :1,
        friskDone           :1,
        moldBreakerShown    :1,
        pressureShown       :1,
        _padding_B          :21;
    
    u8  curPP[4];
    u8  maxPP[4];

    u8  level;
    u8  friendship;
    u16 nickname[11];

    s32 curHP;
    u32 maxHP;

    u16 otName[8];

    u32 exp;
    u32 pid;
    u32 condition;
    u32 condition2;
    u32 idNumber;       // need to figure out what this does

    u16 heldItem;
    u16 dummy;

    u8  hitCount;
    u8  messageFlag;
    u8  gender          :4,
        otGender        :4;
    u8  caughtInBall;

    u32 moveEffectsMask;
    u32 moveEffectsTempMask;
    struct __attribute__((packed)) MoveEffects moveEffects;
};

struct __attribute__((packed)) FieldConditionCounts {
    u32 weatherTurns;

    u8  futureSightTurns[4];
    u8  wishTurns[4];

    u16 futureSightMoveID[4];
    int futureSightAttacker[4];
    s32 futureSightDamage[4];

    u8  wishSelectedMon[4];
};

struct __attribute__((packed)) FieldConditions {
    u32 raw;
    struct FieldConditionCounts counts;
};

struct __attribute__((packed)) SideConditionCounts {
    u32 reflectUser         :2,
        reflectTurns        :3,
        lightScreenUser     :2,
        lightScreenTurns    :3,
        mistUser            :2,
        mistTurns           :3,
        safeguardUser       :2,
        safeguardTurns      :3,
        followMeActive      :1,
        followMeUser        :2,
        knockedOffItemID    :6,
        tailwindTurns       :3;
    
    u32 spikesLayers        :2,
        toxicSpikesLayers   :2,
        _padding            :28;
};

struct __attribute__((packed)) SideConditions {
    u32 raw[2];
    struct SideConditionCounts counts[2];
};

struct __attribute__((packed)) SeqAndCheck {
    int     seqNum;
    int     temp;
};

struct __attribute__((packed)) MessageParams {
    u8  commandCode;
    u8  tag;
    u16 id;
    int params[6];
    int digits;
    int client;
};

// This struct needs to be hella-investigated still
// mostly just what the fields actually are and do,
// not its structure
struct __attribute__((packed)) AIWork {
    u8  seqNum;
    u8  movePos;
    u16 moveID;
    s8  movePP[4];

    int calcWork;
    u32 thinkingMask;

    u8  statusFlag;
    u8  thinkingSeq;
    u8  moveCheckLoopCount;
    u8  moveCheckStackPtr;
    u8  *moveCheckLoopAddr;
    u8  damageForMove[4];
    u16 defenderMoves[4][4];
    u8  abilityNums[4];
    u16 heldItems[4];
    u16 bagItems[2][4];

    u32 stack[8];
    u8  stackSize;

    u8  itemCounts[2];

    u8  attacker;
    u8  defender;
    u8  itemType[2];
    u8  itemCondition[2];

    u8  _pad_0081;  // implicit padding, one byte

    u16 itemIDs[2];

    u8  dirSelectClient[4]; // ?

    struct BattleMove moveTable[468];   // this becomes unusable with move expansion, neat

    u16 _pad_1DCA; // implicit padding, two bytes

    struct ItemData   *itemTable;

    u16 calcCount[4];
    u16 calcInProgress[4];
};

struct __attribute__((packed)) BattleServer {
    u8      comSeqNum[4];
    u8      retSeqNum[4];
    int     serverSeqNum;
    int     serverSeqNext;

    struct SeqAndCheck fieldConditionCheck;
    struct SeqAndCheck pokeConditionCheck;
    struct SeqAndCheck sideConditionCheck;
    struct SeqAndCheck beforeActions;
    struct SeqAndCheck afterMoveHitCheck;

    int     afterMoveFailMessageType;
    int     afterMoveFailMessageSeqNum;

    struct SeqAndCheck afterMoveFailEffects;

    int     beforeMoveSeq;
    int     moveFailCheckSeq;
    int     serverStatusCheckSeq;
    int     serverAbilityCheckSeq;
    int     serverPokemonFormCheckSeq;
    int     serverVanishCheckTemp;

    int     moveSeqAddress;
    int     attacker;
    int     attackerTemp;
    int     defender;
    int     defenderTemp;
    int     faintingClient;
    int     switchingClient;
    int     switchingClientTemp;
    int     abilityCheckClient;
    int     magicCoatClient;

    int     addlEffectType;
    int     addlEffectParam;
    int     addlEffectFlags;
    int     addlEffectClient;

    int     clientStorage;

    int     expGained;
    int     extraExpGained;
    u32     monsGainingExp[2];

    int     moveSeqArchive;     // which archive to load from
    int     moveSeqIndex;       // which sequence to load
    int     moveSeqNum;         // where we are in the sequence

    int     stackPtr;
    int     stackPtrMoveSeqArchive[4];
    int     stackPtrMoveSeqIndex[4];
    int     stackPtrMoveSeqNum[4];

    int     speedCount;
    int     waitCount;

    struct MessageParams messageParams;

    int     clientWork;
    int     attackerWork;
    int     defenderWork;
    int     moveWork;
    int     itemWork;
    int     abilityWork;
    int     messageWork;
    int     calcWork;
    int     tempWork;

    u32     clientStatus[4];
    u32     payDayCount;
    int     totalTurns;
    int     totalDeaths[4];
    int     totalDamage[4];
    int     meFirstTotalTurnOrder;

    void *skillSequenceWork;    // TODO: document
    void *work;

    struct FieldConditions       fieldConditions;
    struct SideConditions        sideConditions;
    struct SingleTurnEffects     stFX[4];
    struct SelfSingleTurnEffects stSelfFX[4];
    struct MoveFailedChecks      moveFailChecks[4];

    struct AIWork aiWork;
    u32           *aiSeqWork;
    u32           aiSeqAddr;

    u32     serverStatusFlag;
    u32     serverStatusFlag2;

    int     damage;
    int     trueDamage;     // this is the amount of HP actually reduced (so it accounts for fainted mons)
    int     criticalCount;
    BOOL    critical;
    int     movePower;      // stores the final power of a move (mostly important for variable power moves)
    int     powerModifier; // stores any move-specific contextual damage multipliers (e.g. Revenge)
    int     hpCalcWork;
    int     moveType;
    int     moveEffectCounter;
    int     moneyMultiplier;    // amulet coin
    u32     moveStatusFlag;
    u32     addlDirectStatus;
    u32     addlIndirectStatus;
    u32     addlAbilityStatus;
    u8      continuationCounter;
    u8      continuationCounterTemp;
    u8      multiHitLoopCounter;    // for spread moves
    u8      beatUpCount;

    u32     loopingFlag;
    u32     moveFailedCheck;
    u32     loopingHitCheck;

    u32     condition2ClearRequest[4];

    u8      selectedMonNum[4];
    u8      switchSelectedMonNum[4];
    u8      aiSwitchSelectedMonNum[4];
    u32     clientActionWork[4][4];
    u8      clientSpeedWork[4];
    u8      pokemonSpeedWork[4];
    u32     pokemonSpeedValues[4];

    u8      serverQueue[4][4][16];
    u8      serverBuffer[4][256];

    int     moveSeqWork[400];

    struct BattlePokemon    activePokemon[4];

    u32     moveIDTemp;
    u32     moveIDCurr;
    u32     moveIDLast;
    u32     moveIDMultiTurn[4];
    
    u16     moveIDProtect[4];
    u16     moveIDHit[4];
    u16     moveIDHitClient[4];
    u16     moveIDHitType[4];
    u16     moveIDOld[4];
    u16     moveIDMirrorMove[4];
    u16     moveIDMirrorMoveHit[4][4];
    u16     moveIDSketch[4];
    u16     moveIDSelected[4];
    u16     moveIDPos[4];
    u16     moveIDConversion2[4];
    u16     moveIDConversion2Client[4];
    u16     moveIDConversion2Type[4];
    u16     moveIDMetronome[4];     // for the item, not the move

    int     storedDamage[4];        // for Bide
    int     clientNumHit[4];
    int     clientNumSpeed;
    u8      clientSwitchingTo;
    u8      pokemonLevelUp;
    u16     queueCheckWait;

    u16     speedRand[4];           // for breaking speed ties

    int     flingWork;
    int     flingSeqNum;

    u8      safariCatchRateCounter;
    u8      safariFleeRateCounter;
    u8      fleeRateCounter;
    u8      fightOver;

    u8      magnitude;

    u8      weatherActive;
    
    s16     hpTemp;

    u16     recyclableItem[4];

    u8      partyOrder[4][6];

    BOOL    jingle;

    int     serverQueueTimeOut;

    u8      recordingFlags[4];

    int     clientWorkingCounter;

    u32     battleProgressFlag;

    // new stuff starts here
    u8      padding_3158[0x26];     // gets the move table to 317E (for convenience of 3180 in ASM)

    struct BattleMove moveTable[TOTAL_NUM_MOVES];
};

enum BattleServerParam {
    SERVER_PARAM_SIDE_CONDITIONS,
    SERVER_PARAM_MIST_TURNS,
    SERVER_PARAM_SELECTED_MON_POS,
    SERVER_PARAM_TOTAL_TURNS,
    SERVER_PARAM_LEVEL_UP_POKEMON,
    SERVER_PARAM_SAFARI_ESCAPE_COUNT,
    SERVER_PARAM_TOTAL_FAINTED,
    SERVER_PARAM_TOTAL_DAMAGE,
    SERVER_PARAM_ACTION_NUM,
    SERVER_PARAM_AI_DEFENDER,
    SERVER_PARAM_SWITCHING_CLIENT,
    SERVER_PARAM_AI_SELECTED_CLIENT,
    SERVER_PARAM_CLIENT_ACTION_WORK,
    SERVER_PARAM_SERVER_SEQ_NUM,
    SERVER_PARAM_SERVER_SEQ_NEXT
};

enum BattlePokemonParam {
    BATTLE_MON_PARAM_SPECIES,
    BATTLE_MON_PARAM_ATTACK,
    BATTLE_MON_PARAM_DEFENSE,
    BATTLE_MON_PARAM_SPEED,
    BATTLE_MON_PARAM_SPATTACK,
    BATTLE_MON_PARAM_SPDEFENSE,
    BATTLE_MON_PARAM_MOVE_1,
    BATTLE_MON_PARAM_MOVE_2,
    BATTLE_MON_PARAM_MOVE_3,
    BATTLE_MON_PARAM_MOVE_4,
    BATTLE_MON_PARAM_HP_IV,
    BATTLE_MON_PARAM_ATTACK_IV,
    BATTLE_MON_PARAM_DEFENSE_IV,
    BATTLE_MON_PARAM_SPEED_IV,
    BATTLE_MON_PARAM_SPATTACK_IV,
    BATTLE_MON_PARAM_SPDEFENSE_IV,
    BATTLE_MON_PARAM_IS_EGG,
    BATTLE_MON_PARAM_HAS_NICKNAME,
    BATTLE_MON_PARAM_HP_STAGES,
    BATTLE_MON_PARAM_ATTACK_STAGES,
    BATTLE_MON_PARAM_DEFENSE_STAGES,
    BATTLE_MON_PARAM_SPEED_STAGES,
    BATTLE_MON_PARAM_SPATTACK_STAGES,
    BATTLE_MON_PARAM_SPDEFENSE_STAGES,
    BATTLE_MON_PARAM_ACCURACY_STAGES,
    BATTLE_MON_PARAM_EVASION_STAGES,
    BATTLE_MON_PARAM_ABILITY,
    BATTLE_MON_PARAM_TYPE_1,
    BATTLE_MON_PARAM_TYPE_2,
    BATTLE_MON_PARAM_GENDER,
    BATTLE_MON_PARAM_IS_SHINY,
    BATTLE_MON_PARAM_PP_1,
    BATTLE_MON_PARAM_PP_2,
    BATTLE_MON_PARAM_PP_3,
    BATTLE_MON_PARAM_PP_4,
    BATTLE_MON_PARAM_PP_UP_COUNT_1,
    BATTLE_MON_PARAM_PP_UP_COUNT_2,
    BATTLE_MON_PARAM_PP_UP_COUNT_3,
    BATTLE_MON_PARAM_PP_UP_COUNT_4,
    BATTLE_MON_PARAM_PP_MAX_1,
    BATTLE_MON_PARAM_PP_MAX_2,
    BATTLE_MON_PARAM_PP_MAX_3,
    BATTLE_MON_PARAM_PP_MAX_4,
    BATTLE_MON_PARAM_LEVEL,
    BATTLE_MON_PARAM_FRIENDSHIP,
    BATTLE_MON_PARAM_NICKNAME,
    BATTLE_MON_PARAM_NICKNAME_CHARS,
    BATTLE_MON_PARAM_HP_CURRENT,
    BATTLE_MON_PARAM_HP_MAX,
    BATTLE_MON_PARAM_OT_NAME,
    BATTLE_MON_PARAM_EXP,
    BATTLE_MON_PARAM_PID,
    BATTLE_MON_PARAM_CONDITION,
    BATTLE_MON_PARAM_CONDITION_V,
    BATTLE_MON_PARAM_ID_NUMBER,
    BATTLE_MON_PARAM_HELD_ITEM,
    BATTLE_MON_PARAM_HIT_COUNT,
    BATTLE_MON_PARAM_MESSAGE_FLAG,
    BATTLE_MON_PARAM_OT_GENDER,
    BATTLE_MON_PARAM_MOVE_EFFECTS,
    BATTLE_MON_PARAM_MOVE_EFFECTS_TEMP,
    BATTLE_MON_PARAM_DISABLED_TURNS,
    BATTLE_MON_PARAM_ENCORED_TURNS,
    BATTLE_MON_PARAM_CHARGED_TURNS,
    BATTLE_MON_PARAM_TAUNTED_TURNS,
    BATTLE_MON_PARAM_PROTECT_CHAIN_COUNT,
    BATTLE_MON_PARAM_PERISH_SONG_TURNS,
    BATTLE_MON_PARAM_ROLLOUT_CHAIN_COUNT,
    BATTLE_MON_PARAM_FURY_CUTTER_CHAIN_COUNT,
    BATTLE_MON_PARAM_STOCKPILE_COUNT,
    BATTLE_MON_PARAM_STOCKPILE_DEF_BOOSTS,
    BATTLE_MON_PARAM_STOCKPILE_SPD_BOOSTS,
    BATTLE_MON_PARAM_TRUANT_ACTIVE,
    BATTLE_MON_PARAM_FLASH_FIRE_ACTIVE,
    BATTLE_MON_PARAM_LOCKED_ON,
    BATTLE_MON_PARAM_MIMIC_SLOT,
    BATTLE_MON_PARAM_BOUND_TARGET,
    BATTLE_MON_PARAM_MEAN_LOOK_TARGET,
    BATTLE_MON_PARAM_LAST_RESORT_MASK,
    BATTLE_MON_PARAM_MAGNET_RISE_TURNS,
    BATTLE_MON_PARAM_HEAL_BLOCK_TURNS,
    BATTLE_MON_PARAM_EMBARGO_TURNS,
    BATTLE_MON_PARAM_UNBURDEN_ACTIVE,
    BATTLE_MON_PARAM_METRONOME,
    BATTLE_MON_PARAM_ONE_TIME_ACC_MAX,
    BATTLE_MON_PARAM_ONE_TIME_SPE_MAX,
    BATTLE_MON_PARAM_QUICK_CLAW_ACTIVE,
    BATTLE_MON_PARAM_RECHARGE_TURN_COUNT,
    BATTLE_MON_PARAM_FAKE_OUT_TURN_COUNT,
    BATTLE_MON_PARAM_SLOW_START_INIT_TURN,
    BATTLE_MON_PARAM_SUBSTITUTE_HP,
    BATTLE_MON_PARAM_FORM_RAND,
    BATTLE_MON_PARAM_DISABLED_MOVE,
    BATTLE_MON_PARAM_ENCORED_MOVE,
    BATTLE_MON_PARAM_BINDING_MOVE,
    BATTLE_MON_PARAM_ITEM_HP_RESTORE,
    BATTLE_MON_PARAM_SLOW_START_FLAG,
    BATTLE_MON_PARAM_SLOW_START_END_FLAG,
    BATTLE_MON_PARAM_FORM_NUMBER
};

enum CheckAbilityMode {
    CHECK_ABILITY_EXISTS_ON_MY_SIDE,    // checks if the ability exists on the battler's side
    CHECK_ABILITY_ACTIVE_ON_MY_SIDE,    // checks if the ability is active on the battler's side (haver is alive)
    CHECK_ABILITY_EXISTS_ON_ENEMY_SIDE, // as above, but on the enemy's side
    CHECK_ABILITY_ACTIVE_ON_ENEMY_SIDE, // as above, but on the enemy's side
    CHECK_ABILITY_ACTIVE_CLIENT_ENEMY_SIDE, // return which battler on the enemy side has the ability
    CHECK_ABILITY_EXISTS,               // as above, but side-agnostic
    CHECK_ABILITY_EXISTS_NOT_MINE,      // check if the ability exists for any battler except the input
    CHECK_ABILITY_EXISTS_CLIENT_NOT_MINE,
    CHECK_ABILITY_ACTIVE,               // as above, but side-agnostic
    CHECK_ABILITY_ACTIVE_NOT_MINE,      // check if the ability is active from any battler except the input
};

/**
 * @brief Get a piece of data from th server, considering a particular battler.
 * 
 * Original function: 0x0225B45C (ov16)
 */
int __attribute__((long_call)) Server_Get(struct Battle *battle, struct BattleServer *server, int paramID, int battler);

/**
 * @brief Gets the ability for a particular battler, considering suppression effects.
 * 
 * Original function: 0x02255A4C (ov16)
 */
u8 __attribute__((long_call)) Server_Ability(struct BattleServer *server, int battler);

/**
 * @brief Check if any active battler has a particular move effect active.
 * 
 * Original function: 0x02255F68 (ov16)
 */
BOOL __attribute__((long_call)) Server_CheckActiveMoveEffect(struct Battle *battle, struct BattleServer *server, int effect);

/**
 * @brief Check if an ability is active. Exact functionality varies with the input to checkMode.
 * 
 * Original function: 0x022555A4 (ov16)
 */
int __attribute__((long_call)) Server_CheckAbility(struct Battle *battle, struct BattleServer *server, int checkMode, int battler, int ability);

/**
 * @brief Check if the defender has a given ability, ignoring it if the attacker has Mold Breaker.
 * 
 * Original function: 0x02255AB4 (ov16)
 */
BOOL __attribute__((long_call)) Server_CheckDefenderAbility(struct BattleServer *server, int attacker, int defender, int ability);

/**
 * @brief Gets the held item effect of a given active battler.
 * 
 * Original function: 0x02258AB8 (ov16)
 */
s32 __attribute__((long_call)) Server_HeldItemEffect(struct BattleServer *server, int battler);

/**
 * @brief Gets the held item power of a given active battler.
 * 
 * Original function: 0x02258ACC (ov16)
 * 
 * Flag:
 * - 0: Gets the battler's item. Does some extra checks (?)
 * - 1: Gets the battler's item, no extra checks
 * - 2: Checks for Embargo before getting the item
 */
s32 __attribute__((long_call)) Server_HeldItemPower(struct BattleServer *server, int battler, int flag);

/**
 * @brief Checks how many hits occurred for the current move.
 * 
 * If flag is 0, then all clients will be considered.
 * If flag is 1, then only clients on the same side as the input battler
 * will be considered.
 * 
 * Original function: 0x022554E0 (ov16)
 */
u8 __attribute__((long_call)) Server_HitCount(struct Battle *battle, struct BattleServer *server, int flag, int battler);

/**
 * @brief Checks if a given move is a 2-turn move.
 * 
 * Original function: 0x0225B6C8 (ov16)
 */
BOOL __attribute__((long_call)) Server_CheckTwoTurnMove(struct BattleServer *server, int moveID);

/**
 * @brief Gets a data value for a particular active battler.
 * 
 * Original function: 0x02252060 (ov16)
 */
int __attribute__((long_call)) BattlePokemon_Get(struct BattleServer *server, int battler, int paramID, void *data);

/**
 * @brief Initializes the battle server. This function is invoked at the start
 * of battle, after the execution of each move, and at the end of the turn.
 * 
 * Hooked into: 0x022541C4 (ov16)
 */
void __attribute__((long_call)) Server_InitState(struct BattleServer *server);

/**
 * @brief Master damage calc function.
 * 
 * Hooked into: 0x02241374 (ov16)
 */
void __attribute__((long_call)) Calc_MoveDamage(struct Battle *battle, struct BattleServer *server);

/**
 * @brief Master critical determination function.
 * 
 * Hooked into: 0x0225A280 (ov16)
 * 
 * @return TRUE if a critical hit should occur, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Calc_Critical(struct Battle *battle, struct BattleServer *server);

/**
 * @brief Only here to hook into the Stealth Rock check.
 * 
 * Hooked into: 0x022558CC (ov16)
 */
int  __attribute__((long_call)) Calc_TypeEffectivenessPower(u8 moveType, u8 pokeType1, u8 pokeType2);

#endif // __BATTLE_SERVER_H