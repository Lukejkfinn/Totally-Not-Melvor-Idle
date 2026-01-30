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
    int chopTrees(int i);
    int getTreeID(int i);
    void giveLog(const int &id);
    virtual void tick(float deltaTime, float contentY) override;

    // Save/load helpers
    // Non-const getters for writing
    float *getProgressArray() { return progress; }
    float *getRunningTimeArray() { return runningTime; }

    // Const getters for read-only access
    const float *getProgressArray() const { return progress; }
    const float *getRunningTimeArray() const { return runningTime; }

protected:

private:

    
    Item item;
    ItemDatabase itemDatabase;

    //float xpBarWidth[12]; // optional: track individual widths
    static constexpr int MAX_TREES{9};
    static constexpr int maxLvl{99};
    float runningTime[MAX_TREES] = {0};
    float progress[MAX_TREES]{0};
    float maxWidth[MAX_TREES]{0};
    int xpAccumulated{0};
    int index = -1;
    float treeTimer[MAX_TREES]{2.1f, 2.8f, 3.5f, 4.2f, 5.6f, 7.f, 8.4f, 10.f, 12.f};
    int xpPerTree[MAX_TREES]{500, 15, 22, 30, 40, 61, 81, 100, 150};
    //int nodeLvl[MAX_TREES]{1, 10, 25, 35, 40, 55, 60, 75, 90};
    std::string xpPerTreeString[MAX_TREES];
    std::string treeNames[MAX_TREES];
    std::string timeToCutTree[MAX_TREES];

    Texture2D treeTextures[MAX_TREES]
    {
        LoadTexture("assets/icons/woodcutting/normal_tree.png"),
        LoadTexture("assets/icons/woodcutting/oak_tree.png"),
        LoadTexture("assets/icons/woodcutting/willow_tree.png"),
        LoadTexture("assets/icons/woodcutting/teak_tree.png"),
        LoadTexture("assets/icons/woodcutting/maple_tree.png"),
        LoadTexture("assets/icons/woodcutting/mahogany_tree.png"),
        LoadTexture("assets/icons/woodcutting/yew_tree.png"),
        LoadTexture("assets/icons/woodcutting/magic_tree.png"),
        LoadTexture("assets/icons/woodcutting/redwood_tree.png")

    };
};

#endif