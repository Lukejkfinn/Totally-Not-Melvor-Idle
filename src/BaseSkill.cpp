#include "BaseSkill.h"

BaseSkill::BaseSkill()
{
    buildXPTable();
};

void BaseSkill::buildXPTable()
{
    xpTable.resize(100);   // 1–99
    xpTable[1] = 0; // level 1 requires 0 xp

    double total = 0.0;

    // xp requirements for levels 2-99
    for (int level = 2; level <= 99; ++level)
    {
        // floor( (level-1) + 300 * 2^((level-1)/7) )
        total += floor((level - 1) + 300.0 * pow(2.0, (level - 1) / 7.0));
        xpTable[level] = static_cast<int>(floor(total / 4.0));
    }
}

bool BaseSkill::rbtn(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // button color states
    Color bgColor = hovered ? DARKBLUE : DARKGRAY;

    // draw button
    DrawRectangleRounded(bounds, 1.f, 16, bgColor);

    // center text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        WHITE);

    // return true only when clicked
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool BaseSkill::sbtn(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // button color states
    Color bgColor = hovered ? DARKBLUE : DARKGRAY;

    // draw button
    DrawRectangleRec(bounds, bgColor);

    // center text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        WHITE);

    // return true only when clicked
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void BaseSkill::getWindowSize(int width, int height)
{
    winWidth = width;
    winHeight = height;
}

std::string BaseSkill::formatNumber(int value)
{
    std::string num = std::to_string(value);
    int insertPosition = num.length() - 3;

    // inserts commas every 3 digits from right to left
    while (insertPosition > 0)
    {
        num.insert(insertPosition, ",");
        insertPosition -= 3;
    }

    return num;
}

void BaseSkill::updateXPBar(int gainedXP)
{
    totalXP += gainedXP; // add xp to total accumulated xp

    // increase level while player has enough xp
    while (curLvl < 99 && totalXP >= xpTable[curLvl + 1])
    {
        curLvl++; // level up
    }

    float xpBarMaxWidth = xpBarWidth - 2.f;

    // if max level, fill xp bar to max
    if (curLvl == 99)
    {
        xpBarFill = {325, 40, xpBarMaxWidth, 50};
        return;
    }

    int xpCurrentLevel = xpTable[curLvl]; // xp required for current level
    int xpNextLevel = xpTable[curLvl + 1]; // xp required for next level

    float xpIntoLevel = totalXP - xpCurrentLevel; // xp gained inside this level
    float xpNeededForLevel = xpNextLevel - xpCurrentLevel; // total xp needed to complete this level

    float ratio = xpIntoLevel / xpNeededForLevel; // convert to 0-1 percentage
    ratio = Clamp(ratio, 0.f, 1.f); // clamp to prevent overflow

    xpBarFill = {325, 40, xpBarMaxWidth * ratio, 50}; // set to visual width of the xp bar
}

void BaseSkill::drawXPBar()
{
    Rectangle xpBarBorder{324, 0, xpBarWidth, 91};
    DrawRectangleRec(xpBarBorder, BLACK);

    DrawText("XP Bar", 330, 10, 30, WHITE);

    Rectangle xpBarBG{325, 40, xpBarWidth - 2.f, 50};
    DrawRectangleRec(xpBarBG, DARKGRAY);

    DrawRectangleRec(xpBarFill, BLUE);

    std::string xpText;

    if (curLvl < 99)
    {
        int xpCurrentLevel = xpTable[curLvl];
        int xpNextLevel = xpTable[curLvl + 1];

        int xpIntoLevel = totalXP - xpCurrentLevel;
        int xpNeeded = xpNextLevel - xpCurrentLevel;

        xpText = "Level " + std::to_string(curLvl) + " (" +
                 formatNumber(xpIntoLevel) + " / " +
                 formatNumber(xpNeeded) + ")";
    }
    else
    {
        xpText = "Level 99 (MAX)";
    }

    int fontSize = 20;
    int textWidth = MeasureText(xpText.c_str(), fontSize);

    DrawText(
        xpText.c_str(),
        325 + (xpBarWidth - textWidth) / 2,
        55,
        fontSize,
        WHITE);
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

            // individual skill background data
            skillBg[i] = {0};
            skillBg[i].width = rectWidth;
            skillBg[i].height = rectHeight;
            skillBg[i].x = startX + col * (rectWidth + spacingX);
            skillBg[i].y = startY + row * (rectHeight + spacingY);

            // current level is too low dont draw below
            if (curLvl < nodeLvl[i])
                continue;

            // individual skills xp bar border
            xpBarBG[i] = {0};
            xpBarBG[i].width = xpWidth;
            xpBarBG[i].height = xpBarBGHeight;
            xpBarBG[i].x = skillBg[i].x + xpWidthOffset;
            xpBarBG[i].y = skillBg[i].y + xpHeightOffset;

            // individual skills xp bars
            xpBar[i].height = xpBarBGHeight;
            xpBar[i].x = skillBg[i].x + xpWidthOffset;
            xpBar[i].y = skillBg[i].y + xpHeightOffset;
        }
    }
}

void BaseSkill::resetSkillProgress()
{
    isRunning = false;
    runningTime = 0.f;
    progress = 0.f;
    singleXpBar.width = 0.f;
}

void BaseSkill::tick(float deltaTime, float contentY)
{
    DrawTextureEx(background, Vector2{bgPosX, 0}, 0, 1, WHITE);

}
