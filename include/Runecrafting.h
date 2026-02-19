#pragma once
#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"

class Runecrafting : public BaseSkill
{
    Inventory &inventory;

public:
    Runecrafting(Inventory &inventory);
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
    static constexpr int numRows{10};
    static constexpr int sizeOfRunecrafting{numCols * numRows};
    static constexpr int MAX_RC{20};

    Rectangle buttons[sizeOfRunecrafting];
    Rectangle xpBar;
    Rectangle xpBarBG;

    int xpPerCraft[MAX_RC]{4, 5, 8, 10, 24, 12, 12, 14, 28, 32, 16, 18, 36, 20, 40, 44, 18, 20, 24, 22};
    int selectedItemIndex{-1};
    float craftTimer{2.f};
    float maxWidth{0};
    int xpAccumulated{0};
    int targetW{32};
    int targetH{32};

    const int runeEssence{1};
    const int airRune{1};
    const int waterRune{3};
    const int earthRune{4};
    const int fireRune{6};

    const int mistRune{5};
    const int dustRune{9};
    const int mudRune{10};
    const int smokeRune{13};
    const int steamRune{15};
    const int lavaRune{16};

};