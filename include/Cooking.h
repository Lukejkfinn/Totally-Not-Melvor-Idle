
#pragma once
#include "raylib.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "Item.h"
#include "BaseSkill.h"

class Cooking : public BaseSkill
{
    Inventory &inventory;
public:
    Cooking(Inventory &inv);
    void drawDropdown(Dropdown& dd, const std::vector<std::string>& options);
    void drawTemplate(float contentY);
    void drawInfoPanel(float contentY, int logID, int logAmount);
    int getNodeLevel(int index) const;
    int getUnlockedSkillIndex() const;
    bool canCookSelected(int index) const;
    void onCompleted();
    void createButton(float contentY);
    void resetSkillProgress();
    virtual void tick(float deltaTime, float contentY) override;

    // save/load helpers
    // non-const getters for writing
    float& getProgress() { return progress; }

    // const getters for read-only access
    const float& getProgress() const { return progress; }

protected:

private:
    ItemDatabase itemDatabase;
    Dropdown itemDropdown;

    Rectangle xpBarBG;
    Rectangle xpBar;

    static constexpr int MAX_FOOD{16};
    static constexpr int maxLvl{99};
    int xpPerFood[MAX_FOOD]{8, 16, 24, 82, 54, 66, 108, 136, 165, 198, 231, 247, 306, 306, 480, 660};
    float foodTimer[MAX_FOOD]{1.9f, 1.9f, 2.85f, 3.8f, 3.8f, 3.8f, 4.75f, 4.75f, 5.7f, 5.7f, 6.65f, 6.65f, 7.6f, 8.55f, 9.5f, 10.45f};
    float maxWidth{0};
    int xpAccumulated{0};

    std::vector<std::string> dropdownOptions = 
    {
        "Shrimp",
        "Sardine",
        "Herring",
        "Seahorse",
        "Trout",
        "Salmon",
        "Lobster",
        "Swordfish",
        "Anglerfish",
        "Fanfish",
        "Crab",
        "Carp",
        "Shark",
        "Cave Fish",
        "Manta Ray",
        "Whale"
    };

};