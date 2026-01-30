#include "raylib.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "Item.h"
#include "BaseSkill.h"
#include <string>
#include "raymath.h"

#ifndef MINING_H
#define MINING_H

class Mining : public BaseSkill
{
    Inventory &inventory;
public:
    Mining(Inventory &inv);
    void initRockDetails();
    virtual void drawTemplate(float contentY) override;
    int getNodeLevel(int index) const override;
    int mineRocks(int i);
    virtual void tick(float deltaTime, float contentY) override;

    
        // Save/load helpers
    // Non-const getters for writing
    float *getProgressArray() { return progress; }
    float *getRunningTimeArray() { return runningTime; }

    // Const getters for read-only access
    const float *getProgressArray() const { return progress; }
    const float *getRunningTimeArray() const { return runningTime; }

    
    
    // Save/load helpers
    // Non-const getters (for writing)
    // float *getProgressArray() { return progress; }
    // // Const getters (for reading)
    // const float *getProgressArray() const { return progress; }
    // // Setters
    // void setProgress(int index, float value)
    // {
    //     if (index >= 0 && index < MAX_ROCKS)
    //         progress[index] = value;
    // }

protected:

private:
    static constexpr int MAX_ROCKS{10};
    float runningTime[MAX_ROCKS] = {0};
    float progress[MAX_ROCKS]{0};
    float maxWidth[MAX_ROCKS]{0};
    int xpAccumulated{0};
    int index = -1;
    float rockTimer[MAX_ROCKS]{2.1f, 2.8f, 3.5f, 4.2f, 5.6f, 7.f, 8.4f, 10.f, 15.f, 20.f};
    int xpPerRock[MAX_ROCKS]{500, 15, 22, 30, 40, 61, 81, 100, 150, 200};
    //int nodeLvl[MAX_ROCKS]{1, 10, 25, 35, 40, 55, 60, 75, 80, 90};
    std::string xpPerRockString[MAX_ROCKS];
    std::string rockNames[MAX_ROCKS];
    std::string timeToMineRocks[MAX_ROCKS];

    Texture2D rockTextures[MAX_ROCKS]
    {
        LoadTexture("assets/icons/mining/rock_copper.png"),
        LoadTexture("assets/icons/mining/rock_tin.png"),
        LoadTexture("assets/icons/mining/rock_iron.png"),
        LoadTexture("assets/icons/mining/rock_coal.png"),
        LoadTexture("assets/icons/mining/rock_silver.png"),
        LoadTexture("assets/icons/mining/rock_gold.png"),
        LoadTexture("assets/icons/mining/rock_mithril.png"),
        LoadTexture("assets/icons/mining/rock_adamantite.png"),
        LoadTexture("assets/icons/mining/rock_runite.png"),
        LoadTexture("assets/icons/mining/rock_dragonite.png"),
    };
};

#endif