#ifndef BASE_SKILL_H
#define BASE_SKILL_H
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>
#include <iostream>

struct Dropdown 
{
    Rectangle bounds;
    bool isOpen = false;
    int selectedIndex = 0;
};

class BaseSkill
{
public:
    BaseSkill();
    bool rbtn(Rectangle bounds, const char *text);
    bool sbtn(Rectangle bounds, const char *text);
    void getWindowSize(int width, int height);
    void drawXPBar();
    void updateXPBar(int xpAmount);
    virtual void drawTemplate(float contentY);
    virtual void tick(float deltaTime, float contentY);
    virtual void resetSkillProgress();
    
    // save/load helpers
    virtual int getNodeLevel(int index) const { return nodeLvl[index]; }
    int getLevel() const { return curLvl; }
    int getXP() const { return xp; }
    void setLevel(int lvl) { curLvl = lvl; }
    void setXP(int newXP) { xp = newXP; }
    Texture2D background{LoadTexture("assets/ui/background.jpg")};

protected:
    Texture2D woodcuttingBG{LoadTexture("assets/ui/woodcuttingBG.png")};
    Texture2D fishingBG{LoadTexture("assets/ui/fishingBG.jpg")};
    Texture2D miningBG{LoadTexture("assets/ui/miningBG.jpg")};
    Texture2D smithingBG{LoadTexture("assets/ui/smithingBG.jpg")};
    Rectangle skillBg[12]; // 3 rows * 4 cols
    Rectangle xpBar[12];   // XP bars
    Rectangle xpBarBG[12]; // XP bar backgrounds
    int curLvl{1};

    Rectangle singleXpBar;
    float progress{0};
    bool isRunning{false};
    float runningTime = {0};
    int iconTargetW{32};
    int iconTargetH{32};
    
private:
    int winWidth{0};
    int winHeight{0};
    Rectangle xpBarFill{325, 40, 0, 50};
    float xp{0.f};
    float bgPosX{320.f};
    float maxXP{1000.f};
    const int MAX_SKILLS{28};
    static constexpr int maxLvl{99};
    float xpBarWidth{930};
    int nodeLvl[maxLvl]{};
};

#endif