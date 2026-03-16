#pragma once
#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"

class Summoning : public BaseSkill
{
    Inventory &inventory;

public:
    Summoning(Inventory &inventory);
    void drawTemplate(float contentY);
    void drawButtonGrid(float contentY, int selectedIndex);
    void drawResourcePanel(float contentY, int selectedIndex);
    int getNodeLevel(int index) const;
    void createButton(float contentY);
    bool canCreateSelected() const;
    void onCompleted();
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
    static constexpr int sizeOfSummons{numCols * numRows};
    static constexpr int MAX_SUMMONS{20};

    Rectangle buttons[sizeOfSummons];
    Rectangle xpBar;
    Rectangle xpBarBG;

    int xpPerSummon[MAX_SUMMONS]{5, 5, 7, 7, 11, 11, 15, 15, 19, 19, 23, 23, 27, 27, 31, 31, 37, 37, 41, 41};
    int selectedItemIndex{-1};
    float craftTimer{4.75f};
    float maxWidth{0};
    int xpAccumulated{0};

};