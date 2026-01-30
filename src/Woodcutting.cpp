#include "Woodcutting.h"

Woodcutting::Woodcutting(Inventory &inv) : inventory(inv)
{
    background = woodcutting;

    // safety check to make sure all xp bars start at 0
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            int i = row * 4 + col;
            xpBar[i].width = 0;
        }
    }
    initTreeDetails();
};

void Woodcutting::initTreeDetails()
{
    const char *names[] =
        {
            "Normal Tree",
            "Oak Tree",
            "Willow Tree",
            "Teak Tree",
            "Maple Tree",
            "Mahogany Tree",
            "Yew Tree",
            "Magic Tree",
            "Redwood Tree"};

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
            "150 XP/"};

    const int treeCount = 9;

    for (int i = 0; i < treeCount; i++)
    {
        treeNames[i] = names[i];
        xpPerTreeString[i] = xpAmount[i];
        timeToCutTree[i] = TextFormat("%.1f seconds", treeTimer[i]);
    }
}

void Woodcutting::drawTemplate(float contentY)
{
    BaseSkill::drawTemplate(contentY);

    // draw XP bars
    for (int i = 0; i < MAX_TREES; i++)
    {
        // draw background and XP bar
        DrawRectangleRec(skillBg[i], GRAY); // gray padding

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

        // draw tree
        DrawTextureEx(treeTextures[i], Vector2{skillBg[i].x + 80, skillBg[i].y + 70}, 0, 0.15f, WHITE);

        // centre tree name text on the skill background
        int treeNameTextWidth = MeasureText(treeNames[i].c_str(), 20);
        int treeNameTextX = skillBg[i].x + (skillBg[i].width - treeNameTextWidth) / 2;
        int treeNameTextY = skillBg[i].y + 20;
        DrawText(treeNames[i].c_str(), treeNameTextX, treeNameTextY, 20, WHITE);

        // concatenate XP and time into a single string
        std::string combinedText = xpPerTreeString[i] + timeToCutTree[i];

        // centre the combined text
        int combinedTextWidth = MeasureText(combinedText.c_str(), 20);
        int combinedTextX = skillBg[i].x + (skillBg[i].width - combinedTextWidth) / 2;
        int combinedTextY = skillBg[i].y + 40; // Same line under tree name

        DrawText(combinedText.c_str(), combinedTextX, combinedTextY, 20, WHITE);
    }

   
}

int Woodcutting::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_TREES]{1, 10, 25, 35, 40, 55, 60, 75, 90};
    return nodeLvls[index];
}

int Woodcutting::chopTrees(int i)
{
    for (int x = 0; x < MAX_TREES; x++)
    {
        if (x == i)
            continue;

        runningTime[x] = 0.f;
        progress[x] = 0.f;
        xpBar[x].width = 0.f;
    }

    runningTime[i] += GetFrameTime();

    progress[i] = runningTime[i] / treeTimer[i];
    progress[i] = Clamp(progress[i], 0.f, 1.f);

    maxWidth[i] = xpBarBG[i].width;
    xpBar[i].width = maxWidth[i] * progress[i];

    if (runningTime[i] >= treeTimer[i])
    {
        runningTime[i] = 0.f;
        xpBar[i].width = 0.f;

        xpAccumulated = xpPerTree[i];
        BaseSkill::updateXPBar(xpAccumulated);

        // pass the correct log name based on the tree index
        int treeID = getTreeID(i); // this function returns the log id
        giveLog(treeID);
    }

    return xpAccumulated;
}

int Woodcutting::getTreeID(const int i)
{
    switch (i)
    {
    case 0:
        return  1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 8:
        return 9;
    default:
        return 0; // fallback for unknown trees, which returns nothing
    }
}

void Woodcutting::giveLog(const int& id)
{
    Item logItem = ItemDatabase::getItemByName("woodcutting", id);

    if (logItem.getTexture().id == 0)
    {
        std::cerr << "Failed to load log item: " << "woodcutting" << " from ItemDatabase!" << std::endl;
        return;
    }

    inventory.addItem(logItem); // add the log item to the inventory
}

void Woodcutting::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    BaseSkill::drawXPBar(); // draws xp bar last so everything hides underneath it as you scroll

     for (int i = 0; i < MAX_TREES; i++)
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

        // check if button pressed
        if (BaseSkill::btn(button, "Chop Tree") && curLvl >= getNodeLevel(i))
        {
            index = (index == i) ? -1 : i;
        }
    }

    // only chop the active tree
    if (index >= 0 && index < MAX_TREES)
    {
        chopTrees(index);
    }
}