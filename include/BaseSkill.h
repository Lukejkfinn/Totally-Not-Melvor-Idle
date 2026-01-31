#ifndef BASE_SKILL_H
#define BASE_SKILL_H
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>
#include <iostream>

class BaseSkill
{
public:
    BaseSkill();
    bool btn(Rectangle bounds, const char *text);
    void getWindowSize(int width, int height);
    void drawXPBar();
    void updateXPBar(int xpAmount);
    virtual void drawTemplate(float contentY);
    virtual void tick(float deltaTime, float contentY);
    virtual int getNodeLevel(int index) const { return nodeLvl[index]; }

    // save/load helpers
    int getLevel() const { return curLvl; }
    int getXP() const { return xp; }
    void setLevel(int lvl) { curLvl = lvl; }
    void setXP(int newXP) { xp = newXP; }
    
protected:
    Texture2D background{LoadTexture("assets/background.jpg")};
    Texture2D woodcutting{LoadTexture("assets/woodcuttingBG.png")};
    Texture2D mining{LoadTexture("assets/miningBG.jpg")};
    Rectangle skillBg[12]; // 3 rows * 4 cols
    Rectangle xpBar[12];   // XP bars
    Rectangle xpBarBG[12]; // XP bar backgrounds
    int curLvl{1};
    
private:
    int winWidth{0};
    int winHeight{0};
    Rectangle xpBarFill{325, 40, 0, 50};
    float xp{0.f};
    float bgPosX{320.f};
    float maxXP{1000.f};
    const int MAX_SKILLS{28};
    static constexpr int maxLvl{99};
    float xpBarWidth{924};
    int nodeLvl[maxLvl]{};
};

#endif