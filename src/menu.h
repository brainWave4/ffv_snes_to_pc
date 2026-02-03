#ifndef MENU_H
#define MENU_H

#include <stdint.h>

typedef struct {
    uint8_t strength;
    uint8_t agility;
    uint8_t stamina;
    uint8_t magic;
} Parameters;

typedef struct {
    Parameters base;
    Parameters current;
    Parameters best;
    
    uint16_t exp;
    uint16_t currentHp;
    uint16_t maxHp;
    uint16_t currentMp;
    uint16_t maxMp;
    uint16_t currentInnateAbilities;
    uint16_t abilityPoints;
    uint16_t freelancerInnateAbilities;

    // Order: rpbb giii
    //  r: is in back Row
    //  p: is in Party
    //  b: Battle order
    //  g: Gender
    //  i: character Id
    uint8_t about;
    uint8_t jobId;
    uint8_t level;
    uint8_t headEquipId;
    uint8_t bodyEquipId;
    uint8_t accEquipId;
    uint8_t shieldIdRight;
    uint8_t shieldIdLeft;
    uint8_t weaponIdRight;
    uint8_t weaponIdLeft;
    uint8_t caughtMonsterID;
    uint8_t[4] commandID;
    uint8_t[4] status;
    uint8_t actions;
    uint8_t damageModifiers;
    uint8_t equipmentElements;
    uint8_t equipmentWeight;
    uint8_t evadeChance;
    uint8_t defense;
    uint8_t MagicEvadeChance;
    uint8_t MagicDefense;
    uint8_t elementalAbsorb;
    uint8_t elementalEvasion;
    uint8_t elementalImmunity;
    uint8_t elementalResistance;
    uint8_t elementalWeakness;
    uint8_t[3] statusResistance;
    uint8_t weaponProperties;
    uint8_t equipProperties;
    uint8_t jobLevel;
    uint8_t[3] magicLevel;
    uint8_t headEquipType;
    uint8_t bodyEquipType;
    uint8_t accEquipType;
    uint8_t weaponPowerRight;
    uint8_t weaponPowerLeft;
    uint8_t prevCommand;
    uint8_t prevAttack;
    uint8_t prevItem;
    uint8_t prevElement;
} Character;

typedef struct {
    uint8_t setting;
    uint8_t height;
    uint8_t x;
    uint8_t y;
} Vehicle;

typedef struct {
    Character[4] party;

    Vehicle[6] vehicle;

    uint32_t gil;
    uint32_t playTime;

    uint16_t enemiesDefeated;
    uint16_t windowColor;

    uint16_t timesBattle;
    uint16_t timesSaved;
    uint16_t battleEvents;

    uint16_t mapId;
    uint16_t worldId;
    uint16_t teleportMapId;

    uint16_t timerEventProgress;
    uint16_t timerEventEnd;

    uint8_t[256] itemId;
    uint8_t[256] itemAmount;

    uint8_t[4][12] jobProgression;
    uint8_t[4] abilityCount;
    uint8_t[4][20] unlockedAbilities;

    uint8_t[32] unlockedMagic;

    uint8_t config;
    uint8_t config2;
    uint8_t configController;

    uint8_t buttonConfigureA;
    uint8_t buttonConfigureB;
    uint8_t buttonConfigureX;
    uint8_t buttonConfigureY;
    uint8_t buttonConfigureL;
    uint8_t buttonConfigureR;
    uint8_t buttonConfigureSelect;

    uint8_t[4] playerNumber;
    uint8_t[4] shortcutPlacement;

    char[5][6] names;

    uint8_t magicLamp;
    uint8_t timesEscaped;
    uint8_t wonderRod;
    uint8_t battleResult;

    uint8_t[32] treasuresOpened;
    uint8_t[32] eventsCleared;
    uint8_t[32] npcStatus;

    uint8_t playerX;
    uint8_t playerY;
    uint8_t FieldCharId;
    uint8_t playerDir;
    uint8_t vehicleId;

    uint8_t teleportX;
    uint8_t teleportY;

    uint8_t randSeed;
    uint8_t walkingSpeed;
    uint8_t enableTimer;
} Save;

void func_a00a(void);
void func_a00f(void);
void execMenu(void);
void updateJoypadConfig(void);

#endif
