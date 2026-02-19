#include "Mining.h"

Mining::Mining(Inventory &inv) : inventory(inv)
{
    background = miningBG;

    // safety check to make sure all xp bars start at 0
    for (size_t i = 0; i < MAX_ROCKS; i++)
        xpBar[i].width = 0;

    initRockDetails();
}

Mining::~Mining()
{
    for (int i = 0; i < MAX_ROCKS; ++i)
    {
        if (rockTextures[i].id != 0)
        {
            UnloadTexture(rockTextures[i]);
            rockTextures[i].id = 0;
        }
    }
}

void Mining::initRockDetails()
{
    // list of textures to load
    const char * rockTexturePaths[MAX_ROCKS] = 
    {
        "assets/icons/mining/rune_essence.png",
        "assets/icons/mining/rock_copper.png",
        "assets/icons/mining/rock_tin.png",
        "assets/icons/mining/rock_iron.png",
        "assets/icons/mining/rock_coal.png",
        "assets/icons/mining/rock_silver.png",
        "assets/icons/mining/rock_gold.png",
        "assets/icons/mining/rock_mithril.png",
        "assets/icons/mining/rock_adamantite.png",
        "assets/icons/mining/rock_runite.png",
        "assets/icons/mining/rock_dragonite.png"
    };

    // load textures for rocks
    for (int i = 0; i < MAX_ROCKS; ++i)
    {
        rockTextures[i] = LoadTexture(rockTexturePaths[i]);

        // check if the texture loaded successfully
        if (rockTextures[i].id == 0)
            std::cerr << "Failed to load texture for rock: " << rockTexturePaths[i] << std::endl; // report the failure

    }

    const char *names[] =
    {
        "Rune Essence",
        "Copper",
        "Tin",
        "Iron",
        "Coal",
        "Silver",
        "Gold",
        "Mithril",
        "Adamantite",
        "Runite",
        "Dragonite"
    };

    const char *xpAmount[] =
    {
        "5 XP/",
        "8 XP/",
        "8 XP/",
        "16 XP/",
        "20 XP/",
        "28 XP/",
        "32 XP/",
        "74 XP/",
        "81 XP/",
        "98 XP/",
        "116 XP/"
    };

    for (int i = 0; i < MAX_ROCKS; i++)
    {
        rockNames[i] = names[i];
        xpPerRockString[i] = xpAmount[i];
        timeToMineRocks[i] = TextFormat("%.1f seconds", rockTimer[i]);
    }
}

void Mining::drawTemplate(float contentY)
{
    BaseSkill::drawTemplate(contentY);

    // draw XP bars
    for (int i = 0; i < MAX_ROCKS; i++)
    {
        // draw background and XP bar
        DrawRectangleRec(skillBg[i], GRAY);
        
        if (getLevel() < getNodeLevel(i))
        {
            // drawing the locked text on the backgrounds
            std::string lockedText = "Locked";
            int fontSize = 30;
            int textWidth = MeasureText(lockedText.c_str(), fontSize);
            float textX = skillBg[i].x + (skillBg[i].width - textWidth) / 2;
            float textY = skillBg[i].y + (skillBg[i].height - fontSize) / 2;
            DrawText(lockedText.c_str(), textX, textY, fontSize, Fade(BLACK, 0.8f));

            std::string unlockLevel = "Lvl " + std::to_string(getNodeLevel(i));
            DrawText(unlockLevel.c_str(), textX+20, textY+25, 20, Fade(BLACK, 0.8f));

            continue;
        }
        
        // draw skill xp bars
        DrawRectangleRounded(xpBarBG[i], 1.f, 16, BLACK);
        DrawRectangleRounded(xpBar[i], 1.f, 16, GREEN);
        
        // draw rocks
        DrawTextureEx(rockTextures[i], Vector2{skillBg[i].x + 80, skillBg[i].y + 70}, 0, 0.15f, WHITE);

        // centre rock name text on the skill background
        int rockNameTextWidth = MeasureText(rockNames[i].c_str(), 20);
        int rockNameTextX = skillBg[i].x + (skillBg[i].width - rockNameTextWidth) / 2;
        int rockNameTextY = skillBg[i].y + 20;
        DrawText(rockNames[i].c_str(), rockNameTextX, rockNameTextY, 20, WHITE);

        // concatenate XP and time into a single string
        std::string combinedText = xpPerRockString[i] + timeToMineRocks[i];

        // centre the combined text
        int combinedTextWidth = MeasureText(combinedText.c_str(), 20);
        int combinedTextX = skillBg[i].x + (skillBg[i].width - combinedTextWidth) / 2;
        int combinedTextY = skillBg[i].y + 40; // Same line under rock name

        DrawText(combinedText.c_str(), combinedTextX, combinedTextY, 20, WHITE);
    }
}

int Mining::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_ROCKS]{1, 1, 1, 15, 30, 30, 40, 50, 70, 80, 95};
    return nodeLvls[index];
}

void Mining::useNode(int i)
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

        int rockID = i + 1;     // (i + 1) (node index 1 = Tree iD 1)
        onNodeComplete(rockID); // pass the index in
    }

    //return xpAccumulated;
}

void Mining::onNodeComplete(const int& id)
{
    Item nodeItem = ItemDatabase::getItemByName("mining", id);

    if (nodeItem.getTexture().id == 0)
    {
        std::cerr << "Failed to load ore item: " << "mining" << " from ItemDatabase!" << std::endl;
        return;
    }

    inventory.addItem(nodeItem); // add the ore item to the inventory
}

void Mining::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    // treeButtons(contentY);

    for (int i = 0; i < MAX_ROCKS; i++)
    {
        if (getLevel() < getNodeLevel(i))
            continue;

        // use the skillBg[i] rectangle for button placement
        Rectangle button = {
            skillBg[i].x + 2.5f,                   // 2.5f offset as the button width changed
            skillBg[i].y + skillBg[i].height - 53, // put button near bottom of card
            skillBg[i].width - 5,                  // reduced the width of the button
            50                                     // button height
        };

        // check if button pressed
        if (BaseSkill::rbtn(button, "Mine Ore") && getLevel() >= getNodeLevel(i))
        {
            index = (index == i) ? -1 : i;
        }
    }

    // only chop the active tree
    if (index >= 0 && index < MAX_ROCKS)
    {
        // do stuff
        useNode(index);
    }

    BaseSkill::drawXPBar();
}