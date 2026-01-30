#include "BaseSkill.h"
#include "raymath.h"
#include <iostream>

BaseSkill::BaseSkill()
{
};

bool BaseSkill::btn(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // Button color states
    Color bgColor = hovered ? DARKBLUE : DARKGRAY;

    // Draw button
    //DrawRectangleRec(bounds, bgColor);
    DrawRectangleRounded(bounds, 1.f, 16, bgColor);

    // Center text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        WHITE);

    // Return true only when clicked
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void BaseSkill::getWindowSize(int width, int height)
{
    winWidth = width;
    winHeight = height;
    //std::cout << "DIMENSIONS " << winWidth << " " << winHeight << '\n';
}

void BaseSkill::updateXPBar(int currentXP)
{
    xp += currentXP; // accumulate XP
    //std::cout << "XP in: " << xp << '\n';

    float xpBarMaxWidth = xpBarWidth - 2; // available width for bar

    // Level up loop in case XP exceeds max
    while (xp >= maxXP)
    {
        xp -= maxXP;    // carry over excess XP
        curLvl++;        // increase level
        maxXP *= 1.1f;  // optional: increase maxXP for next level
    }
    
    // Map XP to width of bar
    float ratio = xp / maxXP;
    ratio = Clamp(ratio, 0.f, 1.f);
    xpBarFill = {325, 40, xpBarMaxWidth * ratio, 50};
}

void BaseSkill::drawXPBar()
{
    
    Rectangle xpBarBorder{324, 0, xpBarWidth, 91};
    DrawRectangleRec(xpBarBorder, BLACK);
    
    DrawText("XP Bar", 330, 10, 30, WHITE);
    
    Rectangle xpBarBG{325, 40, xpBarWidth -2.f, 50};
    DrawRectangleRec(xpBarBG, DARKGRAY);
  
    // Draw filled bar
    DrawRectangleRec(xpBarFill, BLUE);
}

void BaseSkill::drawTemplate(float contentY)
{
    const int numRows = 3;
    const int numCols = 4;
    const float rectWidth = 225.f;
    const float rectHeight = 225.f;
    const float spacingX = 10.f;
    const float spacingY = 30.f;
    const float startX = 325.f;
    float startY = contentY;
    const float xpWidth = 220.f;
    const float xpBarBGHeight = 20.f;
    const float xpWidthOffset = 2.5f;
    const float xpHeightOffset = 150.f;

    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            int i = row * numCols + col;

            skillBg[i] = {0};
            skillBg[i].width = rectWidth;
            skillBg[i].height = rectHeight;
            skillBg[i].x = startX + col * (rectWidth + spacingX);
            skillBg[i].y = startY + row * (rectHeight + spacingY);

            // current level is too low dont draw below
            if (curLvl < nodeLvl[i])
                continue;

            xpBarBG[i] = {0};
            xpBarBG[i].width = xpWidth;
            xpBarBG[i].height = xpBarBGHeight;
            xpBarBG[i].x = skillBg[i].x + xpWidthOffset;
            xpBarBG[i].y = skillBg[i].y + xpHeightOffset;

            xpBar[i].height = xpBarBGHeight;
            xpBar[i].x = skillBg[i].x + xpWidthOffset;
            xpBar[i].y = skillBg[i].y + xpHeightOffset;

            // std::cout << skillBg[i].x << '\n';
        }
    }
}

void BaseSkill::tick(float deltaTime, float contentY)
{
    DrawTextureEx(background, Vector2{bgPosX, 0}, 0, 1, WHITE);

}
