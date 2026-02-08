#pragma once
#include "raylib.h"
#include "BaseSkill.h"
#include "Inventory.h"
#include "ItemDatabase.h"

struct Dropdown {
    Rectangle bounds;
    bool isOpen = false;
    int selectedIndex = 0;
};

class Firemaking : public BaseSkill
{
    Inventory &inventory;
public:
    Firemaking(Inventory &inv);
    void DrawDropdown(Dropdown& dd, const std::vector<std::string>& options);
    void drawProductionPanel(float contentY, int barType, int barAmount);
    virtual void drawTemplate(float contentY) override;
    void drawInfoPanel(float contentY, int logID, int logAmount);
    bool canBurnSelected() const;
    void onLogCompleted();
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
    Dropdown logDropdown;
    int selectedItemIndex{0};
    int targetW{32};
    int targetH{32};
    //static constexpr int sizeOfLogs{logoption};
    float barTimer{1.9f};
    float maxWidth{0};
    Rectangle xpBarBG;
    Rectangle xpBar;
    int xpAccumulated{0};
    int xpPerLog[9]{27, 56, 72, 116, 144, 180, 270, 404, 504};

    std::vector<std::string> logOptions = 
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