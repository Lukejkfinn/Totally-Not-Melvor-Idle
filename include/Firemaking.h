#pragma once
#include "raylib.h"
#include "BaseSkill.h"
#include "Inventory.h"
#include "ItemDatabase.h"

class Firemaking : public BaseSkill
{
    Inventory &inventory;
public:
    Firemaking(Inventory &inv);
    void drawDropdown(Dropdown& dd, const std::vector<std::string>& options);
    void drawProductionPanel(float contentY, int barType, int barAmount);
    virtual void drawTemplate(float contentY) override;
    void drawInfoPanel(float contentY, int logID, int logAmount);
    bool canBurnSelected() const;
    int getNodeLevel(int index) const;
    int getUnlockedSkillIndex() const;
    void onCompleted();
    void logBurn(int logAmount, int input, int output);
    void createButton(float contentY);
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
    Dropdown itemDropdown;

    Rectangle xpBarBG;
    Rectangle xpBar;

    static constexpr int MAX_LOGS{9};
    int selectedItemIndex{0};
    float logBurnTimer[MAX_LOGS]{1.9f};
    float maxWidth{0};
    int xpAccumulated{0};
    int xpPerLog[MAX_LOGS]{27, 56, 72, 116, 144, 180, 270, 404, 504};

    std::vector<std::string> dropdownOptions = 
    {
        "Normal Logs",
        "Oak Logs",
        "Willow Logs",
        "Teak Logs",
        "Maple Logs",
        "Mahogany Logs",
        "Yew Logs",
        "Magic Logs",
        "Redwood Logs"
    };
};