#pragma once
#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"

class Crafting : public BaseSkill
{
    Inventory &inventory;
public:
    Crafting(Inventory &inventory);
    void drawTemplate(float contentY);
    void setPanelInfo(float contentY, int index);
    void drawRequiresPanel(float contentY, int itemID, int itemAmount);
    void drawProductionPanel(float contentY, int itemType, int itemAmount);
    void createButton(float contentY);
    bool canCreateSelected() const;
    void onCompleted();
    virtual void resetSkillProgress();
    virtual void tick(float deltaTime, float contentY) override;
protected:

private:
    ItemDatabase itemDatabase;    

    static constexpr int numCols{2};
    static constexpr int numRows{6};
    static constexpr int sizeOfCrafting{numCols * numRows};
    static constexpr int MAX_CRAFTS{12};

    Rectangle buttons[sizeOfCrafting];
    Rectangle xpBar;
    Rectangle xpBarBG;

    int xpPerCraft[MAX_CRAFTS]{14, 18, 20, 24, 28, 30, 29, 36, 40, 49, 56, 61};
    int selectedItemIndex{-1};
    float craftTimer{2.85f};
    float maxWidth{0};
    int xpAccumulated{0};
    int targetW{32};
    int targetH{32};

};