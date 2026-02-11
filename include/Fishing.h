#pragma once
#include "BaseSkill.h"
#include "Inventory.h"
#include "ItemDatabase.h"

class Fishing : public BaseSkill
{
    Inventory &inventory;
public:
    Fishing(Inventory &inv);
    void drawDropdown(Dropdown& dd, const std::vector<std::string>& options);
    void drawProductionPanel(float contentY, int itemType, int amount);
    void drawTemplate(float contentY);
    void drawInfoPanel(float contentY, int logID, int logAmount);
    int getNodeLevel(int index) const;
    int getUnlockedSkillIndex() const;
    void onCompleted();
    void createButton(float contentY);
    void resetSkillProgress();
    void tick(float deltaTime, float contentY);

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

    static constexpr int MAX_FISHES{16};
    static constexpr int maxLvl{99};
    int xpPerFish[MAX_FISHES]{5, 10, 16, 27, 35, 43, 54, 86, 108, 129, 129, 140, 162, 324, 534, 621};
    float fishTimer[MAX_FISHES]{2.2f, 2.2f, 2.2f, 1.65f, 2.20f, 2.2f, 2.2f, 2.75f, 2.75f, 2.20f, 2.75f, 3.3f, 3.85f, 4.4f, 4.95f, 5.5f};
    float maxWidth{0};
    int xpAccumulated{0};

    std::vector<std::string> dropdownOptions = 
    {
        "Raw Shrimp",
        "Raw Sardine",
        "Raw Herring",
        "Raw Seahorse",
        "Raw Trout",
        "Raw Salmon",
        "Raw Lobster",
        "Raw Swordfish",
        "Raw Anglerfish",
        "Raw Fanfish",
        "Raw Crab",
        "Raw Carp",
        "Raw Shark",
        "Raw Cave Fish",
        "Raw Manta Ray",
        "Raw Whale"
    };
};