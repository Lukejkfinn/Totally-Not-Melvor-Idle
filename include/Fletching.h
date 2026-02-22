#pragma once
#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"

class Fletching : public BaseSkill
{
    Inventory &inventory;

public:
    Fletching(Inventory &inventory);
    void drawTemplate(float contentY);
    void setPanelInfo(float contentY, int index);
    void drawRequiresPanel(float contentY, int itemID1, int itemID2, int itemID3, int itemAmount);
    void drawProductionPanel(float contentY, int itemType, int itemAmount);
    int getNodeLevel(int index) const;
    void createButton(float contentY);
    bool canCreateSelected() const;
    void itemCombination(int item1, int item1Amount, int item2, int item2Amount, int item3, int item3Amount, int createdItem);
    void onCompleted();
    virtual void resetSkillProgress();
    virtual void tick(float deltaTime, float contentY) override;

    // save/load helpers
    // non-const getters for writing
    float& getProgress() { return progress; }

    // const getters for read-only access
    const float& getProgress() const { return progress; }

protected:

private:
    ItemDatabase itemDatabase;    

    static constexpr int numCols{2};
    static constexpr int numRows{5};
    static constexpr int sizeOfFletching{numCols * numRows};
    static constexpr int MAX_FLETCH{9};

    Rectangle buttons[sizeOfFletching];
    Rectangle xpBar;
    Rectangle xpBarBG;

    int xpPerCraft[MAX_FLETCH]{5, 15, 18, 35, 70, 110, 140, 180, 225};
    int selectedItemIndex{-1};
    float craftTimer{1.8f};
    float maxWidth{0};
    int xpAccumulated{0};
    int targetW{32};
    int targetH{32};

};