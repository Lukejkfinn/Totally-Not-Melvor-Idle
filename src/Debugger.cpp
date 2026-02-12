#include "debugger.h"

Debugger::Debugger(Inventory &inv, Woodcutting &wc, Fishing &fish, Firemaking &fm, Cooking &cook, Mining &mine, Smithing &smith, Thieving &thieving, 
        Fletching &fletch, Crafting &craft, Runecrafting &rc, Herblore &herb, Agility &agility, Summoning &summon, Astrology &astro) : 
        inventory(inv), woodcutting(wc), fishing(fish), firemaking(fm), cooking(cook), mining(mine), smithing(smith), thieving(thieving), fletching(fletch), crafting(craft),
        runecrafting(rc), herblore(herb), agility(agility), summoning(summon), astrology(astro)
{
}

bool Debugger::btn(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // button color states
    Color bgColor = hovered ? DARKBLUE : GRAY;

    // draw button
    DrawRectangleRec(bounds, bgColor);

    // centre text
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

// function will handle all elements for drawing/manipulating skills
void Debugger::drawSkillsTemplate()
{
    int startX = 350;
    int startY = 50;
    int spacing = 40;

    int fontSize = 18;

    int buttonWidth = 60;
    int buttonHeight = 30;
    int buttonYAdjust = -5;

    int leftButtonX = 550;
    int rightButtonX = leftButtonX + buttonWidth + 15;

    const char* labels[] =
    {
        "Set Woodcutting:",
        "Set Fishing",
        "Set Firemaking",
        "Set Cooking",
        "Set Mining:",
        "Set Smithing",
        "Set Thieving",
        "Set Fletching",
        "Set Crafting",
        "Set Runecrafting",
        "Set Herblore",
        "Set Agility",
        "Set Summoning",
        "Set Astrology",
        "Set All Skills"
    };

    std::vector<BaseSkill*> skills =
    {
        &woodcutting,
        &fishing,
        &firemaking,
        &cooking,
        &mining,
        &smithing,
        &thieving,
        &fletching,
        &crafting,
        &runecrafting,
        &herblore,
        &agility,
        &summoning,
        &astrology
    };

    int numLabels = sizeof(labels) / sizeof(labels[0]);

    for (int i = 0; i < numLabels; i++)
    {
        int y = startY + i * spacing;

        // draw label
        DrawText(labels[i], startX, y, fontSize, BLACK);

        Rectangle leftButton = { (float)leftButtonX, (float)(y + buttonYAdjust), (float)buttonWidth, (float)buttonHeight };
        Rectangle rightButton = { (float)rightButtonX, (float)(y + buttonYAdjust), (float)buttonWidth, (float)buttonHeight };

        // determine which skills this row should affect
        std::vector<BaseSkill*> allSkills;

        if (i == numLabels - 1) // last row: "Set All"
        {
            allSkills = skills; // all skills
        }
        else
        {
            allSkills.push_back(skills[i]);
        }

        // handle buttons
        if (btn(leftButton, "1"))
        {
            for (auto* skill : allSkills)
            {
                skill->setLevel(1);
                skill->setXP(0);
                skill->updateXPBar(0);
            }
        }

        if (btn(rightButton, "99"))
        {
            for (auto* skill : allSkills)
                skill->setLevel(99);
        }
    }
}

// function will handle all elements for drawing/spawning items
void Debugger::drawObjectsTemplate() 
{
    int startX = 750;
    int startY = 50;
    int spacing = 40;

    int fontSize = 18;

    int buttonWidth = 60;
    int buttonHeight = 30;
    int buttonYAdjust = -5;

    // fixed button columns
    int leftButtonX = 950;
    int rightButtonX = leftButtonX + buttonWidth + 15;

    // labels for display
    const char* labels[] =
    {
        "All Woodcutting logs:",
        "All Fishing items",
        "All Firemaking items",
        "All Cooking items",
        "All Mining ores:",
        "All Smithing bars",
        "Clear Inventory:"
    };

    // map each row to a SkillType (last entry has no skill)
    SkillType skillMap[] = { SkillType::Woodcutting, SkillType::Fishing, SkillType::Firemaking, SkillType::Cooking, SkillType::Mining, SkillType::Smithing };

    int numLabels = sizeof(labels) / sizeof(labels[0]);

    for (int i = 0; i < numLabels; i++)
    {
        int y = startY + i * spacing;

        // draw label
        DrawText(labels[i], startX, y, fontSize, BLACK);

        if (i == numLabels - 1) // last row: clear inventory
        {
            Rectangle clearButton = { (float)leftButtonX, (float)(y + buttonYAdjust), (float)buttonWidth, (float)buttonHeight };
            if (btn(clearButton, "Clear"))
                inventory.clearInventory();
        }
        else // other rows: spawn items
        {
            Rectangle leftButton  = { (float)leftButtonX,  (float)(y + buttonYAdjust), (float)buttonWidth, (float)buttonHeight };
            Rectangle rightButton = { (float)rightButtonX, (float)(y + buttonYAdjust), (float)buttonWidth, (float)buttonHeight };

            int amounts[] = { 1, 64 };
            Rectangle buttons[] = { leftButton, rightButton };

            for (int j = 0; j < 2; j++) // loop over left/right buttons
            {
                if (btn(buttons[j], std::to_string(amounts[j]).c_str()))
                {
                    auto spawned = itemDatabase.ItemSpawner(skillMap[i], amounts[j]);
                    for (const auto& item : spawned)
                        inventory.addItem(item);
                }
            }
        }
    }
}

void Debugger::tick(float deltaTime)
{
    DrawTextureEx(debuggerBG, Vector2{320, 0}, 0, 1.1, WHITE);
    DrawRectangle(340, 20, 900, 650, Fade(DARKGRAY, 0.9f));
    drawSkillsTemplate();
    drawObjectsTemplate();

    closeBtn = {1125, 25, 100, 30};
    if (btn(closeBtn, "Close"))
    {
        debugging = false;
    }
}