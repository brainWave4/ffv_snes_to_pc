#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <wchar.h>

typedef struct {
    Uint8 strength;
    Uint8 agility;
    Uint8 stamina;
    Uint8 magic;
} Parameters;

typedef struct {
    Parameters base;
    Parameters current;
    Parameters best;
    
    Uint16 exp;
    Uint16 currentHp;
    Uint16 maxHp;
    Uint16 currentMp;
    Uint16 maxMp;
    Uint16 currentInnateAbilities;
    Uint16 abilityPoints;
    Uint16 freelancerInnateAbilities;

    // Order: rpbb giii
    //  r: is in back Row
    //  p: is in Party
    //  b: Battle order
    //  g: Gender
    //  i: character Id
    Uint8 about;
    Uint8 jobId;
    Uint8 level;
    Uint8 headEquipId;
    Uint8 bodyEquipId;
    Uint8 accEquipId;
    Uint8 shieldIdRight;
    Uint8 shieldIdLeft;
    Uint8 weaponIdRight;
    Uint8 weaponIdLeft;
    Uint8 caughtMonsterID;
    Uint8[4] commandID;
    Uint8[4] status;
    Uint8 actions;
    Uint8 damageModifiers;
    Uint8 equipmentElements;
    Uint8 equipmentWeight;
    Uint8 evadeChance;
    Uint8 defense;
    Uint8 MagicEvadeChance;
    Uint8 MagicDefense;
    Uint8 elementalAbsorb;
    Uint8 elementalEvasion;
    Uint8 elementalImmunity;
    Uint8 elementalResistance;
    Uint8 elementalWeakness;
    Uint8[3] statusResistance;
    Uint8 weaponProperties;
    Uint8 equipProperties;
    Uint8 jobLevel;
    Uint8[3] magicLevel;
    Uint8 headEquipType;
    Uint8 bodyEquipType;
    Uint8 accEquipType;
    Uint8 weaponPowerRight;
    Uint8 weaponPowerLeft;
    Uint8 prevCommand;
    Uint8 prevAttack;
    Uint8 prevItem;
    Uint8 prevElement;
} Character;

typedef struct {
    Uint8 setting;
    Uint8 height;
    Uint8 x;
    Uint8 y;
} Vehicle;

typedef struct {
    Character[4] party;

    Vehicle[6] vehicle;

    Uint32 gil;
    Uint32 playTime;

    wchar_t[5][6] names;

    Uint16 enemiesDefeated;
    Uint16 windowColor;

    Uint16 timesBattle;
    Uint16 timesSaved;
    Uint16 battleEvents;

    Uint16 mapId;
    Uint16 worldId;
    Uint16 teleportMapId;

    Uint16 timerEventProgress;
    Uint16 timerEventEnd;

    Uint8[256] itemId;
    Uint8[256] itemAmount;

    Uint8[4][12] jobProgression;
    Uint8[4] abilityCount;
    Uint8[4][20] unlockedAbilities;

    Uint8[32] unlockedMagic;

    Uint8 config;
    Uint8 config2;
    Uint8 configController;

    Uint8 buttonConfigureA;
    Uint8 buttonConfigureB;
    Uint8 buttonConfigureX;
    Uint8 buttonConfigureY;
    Uint8 buttonConfigureL;
    Uint8 buttonConfigureR;
    Uint8 buttonConfigureSelect;

    Uint8[4] playerNumber;
    Uint8[4] shortcutPlacement;

    Uint8 magicLamp;
    Uint8 timesEscaped;
    Uint8 wonderRod;
    Uint8 battleResult;

    Uint8[32] treasuresOpened;
    Uint8[32] eventsCleared;
    Uint8[32] npcStatus;

    Uint8 playerX;
    Uint8 playerY;
    Uint8 FieldCharId;
    Uint8 playerDir;
    Uint8 vehicleId;

    Uint8 teleportX;
    Uint8 teleportY;

    Uint8 randSeed;
    Uint8 walkingSpeed;
    Uint8 enableTimer;
} Save;

void func_a00a(void); // Incomplete
void func_a00f(void); // Incomplete
void execMenu(void); // Incomplete
void updateJoypadConfig(void); // Incomplete

// Address: $7e0500 - $7e0aff
Save currentSave;

#endif
