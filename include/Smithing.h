#ifndef SMITHING_H
#define SMITHING_H

#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"
#include <iostream>

class Smithing : public BaseSkill
{
    Inventory &inventory;
public:
    Smithing(Inventory &invetory);
    virtual void drawTemplate(float contentY) override;
    void drawButtonGrid(float contentY, int selectedIndex, std::string barNames[]);
    void drawResourcePanel(float contentY, int selectedIndex, std::string barNames[]);
    void drawProductionPanel(float contentY, int itemType, int itemAmount);
    void drawSmithingPanelInfo(float contentY, int index);
    void drawOreCombinationPanel(float contentY, int item1, int item1Amount, int item2, int item2Amount);
    void createButton(float contentY);
    bool canCreateSelected() const;
    void onCompleted();
    void oreCombination(int ore1Amount, int ore1, int ore2Amount, int ore2, int bar);
    virtual void resetSkillProgress();
    virtual int setMenuBar (float contentY, std::string buttonNames[], int sizeOfButtons, float textPosY, int fontSize);
    void rebuildGrid();
    virtual void tick(float deltaTime, float contentY) override;
    int getNodeLevel(int index) const override;

    // non-const getters for writing
    float& getProgress() { return progress; }

    // const getters for read-only access
    const float& getProgress() const { return progress; }

protected:

private:
    ItemDatabase itemDatabase;
    
    int numCols{2};
    int numRows{5};
    int sizeOfSmithing{numCols * numRows};
    static constexpr int MAX_BARS{9};
    static constexpr int MAX_ITEMS{16};

    Rectangle xpBar;
    Rectangle xpBarBG;
    Rectangle buttons[MAX_ITEMS];
    
    int selectedItemIndex{-1};
    int targetW{32};
    int targetH{32};
    float maxWidth{0};
    int xpAccumulated{0};
    float barTimer{1.9f};
    int xpPerBar[MAX_BARS]{5, 8, 12, 15, 20, 35, 42, 50, 60};
    int xpPerBronzeGear[MAX_ITEMS]{10, 10, 10, 10, 20, 20, 20, 30, 20, 20, 30, 30, 30, 30, 50, 0};
    int xpPerIronGear[MAX_ITEMS]{20, 20, 20, 20, 40, 40, 40, 60, 40, 40, 60, 60, 60, 60, 100, 0};
    int xpPerSteelGear[MAX_ITEMS]{30, 30, 30, 30, 60, 60, 60, 90, 60, 60, 90, 90, 90, 90, 150, 0};
    int xpPerMithrilGear[MAX_ITEMS]{50, 50, 50, 50, 100, 100, 100, 150, 100, 100, 150, 150, 150, 150, 250, 0};
    int xpPerAdamantGear[MAX_ITEMS]{60, 60, 60, 60, 120, 120, 120, 180, 120, 120, 180, 180, 180, 180, 300, 0};
    int xpPerRuneGear[MAX_ITEMS]{75, 75, 75, 75, 150, 150, 150, 225, 150, 150, 225, 225, 225, 225, 375, 0};
    int xpPerDragonGear[MAX_ITEMS]{100, 100, 100, 100, 200, 200, 200, 300, 200, 200, 300, 300, 300, 300, 500, 0};
    int selectedIndex{0};
    int previousMenuIndex{-1};

    std::string barNamesText[MAX_ITEMS] =
    {
        "Bronze Bar",
        "Iron Bar",
        "Steel Bar",
        "Silver Bar",
        "Gold Bar",
        "Mithril Bar",
        "Adamantite Bar",
        "Runite Bar",
        "Dragonite Bar"
    };

    std::string bronzeGearNamesText[MAX_ITEMS] =
    {
        "Bronze Dagger",
        "Bronze Arrowtips",
        "Bronze\nThrowing Knife",
        "Bronze Sword",
        "Bronze Gloves",
        "Bronze Scimitar",
        "Bronze Helmet",
        "Bronze Battleaxe",
        "Bronze\nJavelin Heads",
        "Bronze Boots",
        "Bronze Shield",
        "Bronze 2H Sword",
        "Bronze\nCrossbow Head",
        "Bronze Platelegs",
        "Bronze Platebody",
    };

    std::string ironGearNamesText[MAX_ITEMS] =
    {
        "Iron Dagger",
        "Iron Arrowtips",
        "Iron\nThrowing Knife",
        "Iron Sword",
        "Iron Gloves",
        "Iron Scimitar",
        "Iron Helmet",
        "Iron Battleaxe",
        "Iron\nJavelin Heads",
        "Iron Boots",
        "Iron Shield",
        "Iron 2H Sword",
        "Iron\nCrossbow Head",
        "Iron Platelegs",
        "Iron Platebody",
    };

    std::string steelGearNamesText[MAX_ITEMS] =
    {
        "Steel Dagger",
        "Steel Arrowtips",
        "Steel\nThrowing Knife",
        "Steel Sword",
        "Steel Gloves",
        "Steel Scimitar",
        "Steel Helmet",
        "Steel Battleaxe",
        "Steel\nJavelin Heads",
        "Steel Boots",
        "Steel Shield",
        "Steel 2H Sword",
        "Steel\nCrossbow Head",
        "Steel Platelegs",
        "Steel Platebody",
    };
    
    std::string mithrilGearNamesText[MAX_ITEMS] =
    {
        "Mithril Dagger",
        "Mithril Arrowtips",
        "Mithril\nThrowing Knife",
        "Mithril Sword",
        "Mithril Gloves",
        "Mithril Scimitar",
        "Mithril Helmet",
        "Mithril Battleaxe",
        "Mithril\nJavelin Heads",
        "Mithril Boots",
        "Mithril Shield",
        "Mithril 2H Sword",
        "Mithril\nCrossbow Head",
        "Mithril Platelegs",
        "Mithril Platebody",
    };

    std::string adamantGearNamesText[MAX_ITEMS] =
    {
        "Adamant Dagger",
        "Adamant Arrowtips",
        "Adamant\nThrowing Knife",
        "Adamant Sword",
        "Adamant Gloves",
        "Adamant Scimitar",
        "Adamant Helmet",
        "Adamant Battleaxe",
        "Adamant\nJavelin Heads",
        "Adamant Boots",
        "Adamant Shield",
        "Adamant 2H Sword",
        "Adamant\nCrossbow Head",
        "Adamant Platelegs",
        "Adamant Platebody",
    };
    
    std::string runeGearNamesText[MAX_ITEMS] =
    {
        "Rune Dagger",
        "Rune Arrowtips",
        "Rune\nThrowing Knife",
        "Rune Sword",
        "Rune Gloves",
        "Rune Scimitar",
        "Rune Helmet",
        "Rune Battleaxe",
        "Rune\nJavelin Heads",
        "Rune Boots",
        "Rune Shield",
        "Rune 2H Sword",
        "Rune\nCrossbow Head",
        "Rune Platelegs",
        "Rune Platebody",
    };

    std::string dragonGearNamesText[MAX_ITEMS] =
    {
        "Dragon Dagger",
        "Dragon Arrowtips",
        "Dragon\nThrowing Knife",
        "Dragon Sword",
        "Dragon Gloves",
        "Dragon Scimitar",
        "Dragon Helmet",
        "Dragon Battleaxe",
        "Dragon\nJavelin Heads",
        "Dragon Boots",
        "Dragon Shield",
        "Dragon 2H Sword",
        "Dragon\nCrossbow Head",
        "Dragon Platelegs",
        "Dragon Platebody",
    };
};
#endif