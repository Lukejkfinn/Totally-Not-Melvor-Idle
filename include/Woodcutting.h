#ifndef WOODCUTTING_H
#define WOODCUTTING_H

#include "raylib.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "Item.h"
#include "BaseSkill.h"
#include "raymath.h"
#include <iostream>
#include <string>


class Woodcutting : public BaseSkill
{
    Inventory &inventory;
public:
    Woodcutting(Inventory &inv);
    void initTreeDetails();
    virtual void drawTemplate(float contentY) override;
    int getNodeLevel(int index) const override;
    int useNode(int i);
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
    Item item;
    ItemDatabase itemDatabase;

    static constexpr int MAX_TREES{9};
    float runningTime[MAX_TREES] = {0};
    float progress[MAX_TREES]{0};
    float maxWidth[MAX_TREES]{0};
    int xpAccumulated{0};
    int index = -1;
    float treeTimer[MAX_TREES]{2.1f, 2.8f, 3.5f, 4.2f, 5.6f, 7.f, 8.4f, 10.f, 12.f};
    int xpPerTree[MAX_TREES]{500, 15, 22, 30, 40, 61, 81, 100, 150};
    std::string xpPerTreeString[MAX_TREES];
    std::string treeNames[MAX_TREES];
    std::string timeToCutTree[MAX_TREES];
    Texture2D treeTextures[MAX_TREES];
};

#endif