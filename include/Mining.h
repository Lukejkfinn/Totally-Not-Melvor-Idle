#ifndef MINING_H
#define MINING_H

#include "raylib.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "Item.h"
#include "BaseSkill.h"
#include <string>
#include "raymath.h"


class Mining : public BaseSkill
{
    Inventory &inventory;
public:
    Mining(Inventory &inv);
    ~Mining();
    void initRockDetails();
    virtual void drawTemplate(float contentY) override;
    int getNodeLevel(int index) const override;
    void useNode(int i);
    void onNodeComplete(const int &id);
    virtual void tick(float deltaTime, float contentY) override;

    // save/load helpers
    // non-const getters for writing
    float *getProgressArray() { return progress; }
    float *getRunningTimeArray() { return runningTime; }

    // const getters for read-only access
    const float *getProgressArray() const { return progress; }
    const float *getRunningTimeArray() const { return runningTime; }

protected:

private:
    static constexpr int MAX_ROCKS{11};
    
    float runningTime[MAX_ROCKS] = {0};
    float progress[MAX_ROCKS]{0};
    float maxWidth[MAX_ROCKS]{0};
    int xpAccumulated{0};
    int index = -1;
    float rockTimer[MAX_ROCKS]{1.5f, 2.1f, 2.8f, 3.5f, 4.2f, 5.6f, 7.f, 8.4f, 10.f, 15.f, 20.f};
    int xpPerRock[MAX_ROCKS]{5, 8, 8, 16, 20, 28, 32, 74, 81, 98, 116};
    std::string xpPerRockString[MAX_ROCKS];
    std::string rockNames[MAX_ROCKS];
    std::string timeToMineRocks[MAX_ROCKS];
    Texture2D rockTextures[MAX_ROCKS];
};

#endif