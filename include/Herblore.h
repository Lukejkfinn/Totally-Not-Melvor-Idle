#pragma once
#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"

class Herblore : public BaseSkill
{
    Inventory &inventory;

public:
    Herblore(Inventory &inventory);
    void drawTemplate(float contentY);
    void drawButtonGrid(float contentY, int selectedIndex);
    void drawResourcePanel(float contentY, int selectedIndex);
    void setPanelInfo(float contentY, int index);
    void drawRequiresPanel(float contentY, int itemID1, int itemID2, int itemID3, int itemAmount);
    void drawProductionPanel(float contentY, int itemType, int itemAmount);
    int getNodeLevel(int index) const;
    void createButton(float contentY);
    bool canCreateSelected() const;
    void itemCombination(int item1, int item1Amount, int item2, int item2Amount, int item3, int item3Amount, int createdItem);
    void onCompleted();
    virtual void resetSkillProgress();
    virtual int setMenuBar (float contentY, std::string buttonNames[], int sizeOfButtons, float textPosY, int fontSize) override;
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
    static constexpr int numRows{8};
    static constexpr int sizeOfHerblore{numCols * numRows};
    static constexpr int MAX_HERBS{15};

    Rectangle buttons[sizeOfHerblore];
    Rectangle xpBar;
    Rectangle xpBarBG;

    int xpPerSkillPot[MAX_HERBS]{5, 18, 28, 33, 36, 39, 41, 47, 41, 53, 50, 61, 63, 99, 112};
    int xpPerCombatPot[MAX_HERBS]{8, 10, 14, 16, 22, 31, 38, 45, 47, 51, 60, 85, 92, 160, 180};
    int selectedItemIndex{-1};
    float craftTimer{1.9f};
    float maxWidth{0};
    int xpAccumulated{0};
    int targetW{32};
    int targetH{32};
    int selectedIndex{0};
};