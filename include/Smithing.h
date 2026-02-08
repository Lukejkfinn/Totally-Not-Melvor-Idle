#ifndef SMITHING_H
#define SMITHING_H

#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"
#include <iostream>
#include <String>

class Smithing : public BaseSkill
{
    Inventory &inventory;
public:
    Smithing(Inventory &invetory);
    virtual void drawTemplate(float contentY) override;
    void beginSmithing(float contentY);
    bool canSmeltSelected() const;
    void onSmeltCompleted();
    void drawSmithingPanelInfo(float contentY, int index);
    void drawOreCombinationPanel(float contentY, int ore1ID, int ore1Amount, int ore2ID, int ore2Amount);
    void drawOreSingularPanel(float contentY, int oreID, int oreAmount);
    void drawProductionPanel(float contentY, int barType, int barAmount);
    void oreCombination(int ore1Amount, int ore1, int ore2Amount, int ore2, int bar);
    void oreSmelt(int oreAmount, int ore, int bar);
    virtual void resetSkillProgress();
    virtual void tick(float deltaTime, float contentY) override;
    int getNodeLevel(int index) const override;
    // non-const getters for writing
    float& getProgress() { return progress; }

    // const getters for read-only access
    const float& getProgress() const { return progress; }

protected:

private:
    ItemDatabase itemDatabase;
    Texture2D previewIcon = LoadTexture("assets/bank/smithing/bronze_bar.png");
    
    static constexpr int MAX_BARS{9};
    static constexpr int maxLvl{99};
    int selectedItemIndex{-1};
    int targetW{32};
    int targetH{32};
    //float runningTime = {0};
    float maxWidth{0};
    int xpAccumulated{0};
    float barTimer{1.9f};
    int xpPerBar[MAX_BARS]{5, 8, 12, 15, 20, 35, 42, 51, 61};
    //bool isRunning{false};
    int nodeLvl[maxLvl]{};
    Rectangle xpBar;
    Rectangle xpBarBG;
    
    static constexpr int numCols = 2;
    static constexpr int numRows = 5;
    static constexpr int sizeOfSmithing{numCols * numRows};
    Rectangle buttons[sizeOfSmithing];
    


    //float progress{0};
};


#endif