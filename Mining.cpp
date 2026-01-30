#include "Mining.h"

Mining::Mining(Inventory &inv) : inventory(inv)
{
    background = mining;

    // safety check to make sure all xp bars start at 0
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            int i = row * 4 + col;
            xpBar[i].width = 0;
        }
    }
    initRockDetails();
}

void Mining::initRockDetails()
{
    const char *names[] =
        {
            "Copper",
            "Tin",
            "Iron",
            "Coal",
            "Silver",
            "Gold",
            "Mithril",
            "Adamantite",
            "Runite",
            "Chaz why"};

    const char *xpAmount[] =
        {
            "10 XP/",
            "15 XP/",
            "22 XP/",
            "30 XP/",
            "40 XP/",
            "61 XP/",
            "81 XP/",
            "100 XP/",
            "150 XP/",
            "200 XP/"};

    const int rockCount = 10;

    for (int i = 0; i < rockCount; i++)
    {
        rockNames[i] = names[i];
        xpPerRockString[i] = xpAmount[i];
        timeToMineRocks[i] = TextFormat("%.1f seconds", rockTimer[i]);
    }
}

void Mining::drawTemplate(float contentY)
{
    BaseSkill::drawTemplate(contentY);

    // Draw XP bars
    for (int i = 0; i < MAX_ROCKS; i++)
    {
        // Draw background and XP bar
        DrawRectangleRec(skillBg[i], GRAY);
        
        if (curLvl < getNodeLevel(i))
        {
            // drawing the locked text on the backgrounds
            const char *lockedText = "Locked";
            int fontSize = 30;
            int textWidth = MeasureText(lockedText, fontSize);
            float textX = skillBg[i].x + (skillBg[i].width - textWidth) / 2;
            float textY = skillBg[i].y + (skillBg[i].height - fontSize) / 2;
            DrawText(lockedText, textX, textY, fontSize, Fade(BLACK, 0.5f));
            continue;
        }
        
        // draw skill xp bars
        DrawRectangleRounded(xpBarBG[i], 1.f, 16, BLACK);
        DrawRectangleRounded(xpBar[i], 1.f, 16, GREEN);
        
        // draw rocks
        DrawTextureEx(rockTextures[i], Vector2{skillBg[i].x + 80, skillBg[i].y + 70}, 0, 0.15f, WHITE);

        // Center rock name text on the skill background
        int rockNameTextWidth = MeasureText(rockNames[i].c_str(), 20);
        int rockNameTextX = skillBg[i].x + (skillBg[i].width - rockNameTextWidth) / 2;
        int rockNameTextY = skillBg[i].y + 20;
        DrawText(rockNames[i].c_str(), rockNameTextX, rockNameTextY, 20, WHITE);

        // Concatenate XP and time into a single string
        std::string combinedText = xpPerRockString[i] + timeToMineRocks[i];

        // Center the combined text
        int combinedTextWidth = MeasureText(combinedText.c_str(), 20);
        int combinedTextX = skillBg[i].x + (skillBg[i].width - combinedTextWidth) / 2;
        int combinedTextY = skillBg[i].y + 40; // Same line under rock name

        DrawText(combinedText.c_str(), combinedTextX, combinedTextY, 20, WHITE);
    }


}

int Mining::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_ROCKS]{1, 10, 25, 35, 40, 55, 60, 75, 80, 90};
    return nodeLvls[index];
}


int Mining::mineRocks(int i)
{
    for (int x = 0; x < MAX_ROCKS; x++)
    {
        if (x == i)
            continue;

        runningTime[x] = 0.f;
        progress[x] = 0.f;
        xpBar[x].width = 0.f;
    }

    runningTime[i] += GetFrameTime();

    progress[i] = runningTime[i] / rockTimer[i];
    progress[i] = Clamp(progress[i], 0.f, 1.f);

    maxWidth[i] = xpBarBG[i].width;
    xpBar[i].width = maxWidth[i] * progress[i];

    if (runningTime[i] >= rockTimer[i])
    {
        runningTime[i] = 0.f;
        xpBar[i].width = 0.f;

        xpAccumulated = xpPerRock[i];
        BaseSkill::updateXPBar(xpAccumulated);
    }

    return xpAccumulated;
}

void Mining::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    // treeButtons(contentY);
    BaseSkill::drawXPBar();

        for (int i = 0; i < MAX_ROCKS; i++)
    {
        if (curLvl < getNodeLevel(i))
            continue;

        // Use the skillBg[i] rectangle for button placement
        Rectangle button = {
            skillBg[i].x + 2.5f,                   // 2.5f offset as the button width changed
            skillBg[i].y + skillBg[i].height - 53, // put button near bottom of card
            skillBg[i].width - 5,                  // reduced the width of the button
            50                                     // button height
        };

        // Check if button pressed
        if (BaseSkill::btn(button, "Mine Ore") && curLvl >= getNodeLevel(i))
        {
            index = (index == i) ? -1 : i;
        }
    }

    // Only chop the active tree
    if (index >= 0 && index < MAX_ROCKS)
    {
        // do stuff
        mineRocks(index);
    }
}

// void Mining::treeButtons(float contentY)
// {
//     for (int i = 0; i < MAX_ROCKS; i++)
//     {
//         // Use the skillBg[i] rectangle for button placement
//         Rectangle button = {
//             skillBg[i].x + 2.5f,                   // 2.5f offset as the button width changed
//             skillBg[i].y + skillBg[i].height - 53, // put button near bottom of card
//             skillBg[i].width - 5,                  // reduced the width of the button
//             50                                     // button height
//         };
//
//         // Check if button pressed
//         if (BaseSkill::btn(button, "Chop Tree"))
//         {
//             index = (index == i) ? -1 : i;
//         }
//     }
// }