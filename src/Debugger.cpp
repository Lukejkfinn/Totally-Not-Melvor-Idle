#include "debugger.h"

Debugger::Debugger(Inventory &inv, Woodcutting &wc, Mining &mine, Smithing &smith) : inventory(inv), woodcutting(wc), mining(mine), smithing(smith)
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

    // fixed button columns
    int leftButtonX = 550;
    int rightButtonX = leftButtonX + buttonWidth + 15;

    const char *labels[] =
        {
            "Set Woodcutting:",
            "Set Mining:",
            "Set Smithing"
        };

    int numLabels = sizeof(labels) / sizeof(labels[0]);

    for (int i = 0; i < numLabels; i++)
    {
        int y = startY + i * spacing;

        // draw labels
        DrawText(labels[i], startX, y, fontSize, BLACK);

        // make buttons
        Rectangle leftButton =
            {
                (float)leftButtonX,
                (float)(y + buttonYAdjust),
                (float)buttonWidth,
                (float)buttonHeight};

        Rectangle rightButton =
            {
                (float)rightButtonX,
                (float)(y + buttonYAdjust),
                (float)buttonWidth,
                (float)buttonHeight};
        
        // button actions
        if (btn(leftButton, "1"))
        {
            if (i == 0)
                woodcutting.setLevel(1);
            if (i == 1)
                mining.setLevel(1);
            if (i == 2)
                smithing.setLevel(1);
        }

        if (btn(rightButton, "99"))
        {
            if (i == 0)
                woodcutting.setLevel(99);
            if (i == 1)
                mining.setLevel(99);
            if (i == 2)
                smithing.setLevel(99);
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

    const char *labels[] =
        {
            "All Woodcutting logs:",
            "All Mining ores:",
            "All Smithing bars",
            "Clear Inventory:"
        };

    int numLabels = sizeof(labels) / sizeof(labels[0]);

    for (int i = 0; i < numLabels; i++)
    {
        int y = startY + i * spacing;

        // draw labels
        DrawText(labels[i], startX, y, fontSize, BLACK);


        // make buttons
        Rectangle leftButton =
            {
                (float)leftButtonX,
                (float)(y + buttonYAdjust),
                (float)buttonWidth,
                (float)buttonHeight};

        Rectangle rightButton =
            {
                (float)rightButtonX,
                (float)(y + buttonYAdjust),
                (float)buttonWidth,
                (float)buttonHeight};

        Rectangle singleButton =
            {
                (float)leftButtonX,
                (float)(y + buttonYAdjust),
                (float)buttonWidth,
                (float)buttonHeight};

        // if it's the last item in the array (clear Inventory)
        if (i == numLabels - 1)
        {
            // draw the clear button and clear the inventory
            if (btn(singleButton, "Clear"))
            {
                inventory.clearInventory(); // clear the inventory but keep the slots
            }
        }
        else
        {
            // draw and handle both left and right buttons for the other items
            if (btn(leftButton, "1"))
            {
                if (i == 0)
                {
                    auto spawned = itemDatabase.ItemSpawner(SkillType::Woodcutting, 1);
                    for (const auto &item : spawned)
                        inventory.addItem(item);
                }
                if (i == 1)
                {
                    auto spawned = itemDatabase.ItemSpawner(SkillType::Mining, 1);
                    for (const auto &item : spawned)
                        inventory.addItem(item);
                }
                if (i == 2)
                                {
                    auto spawned = itemDatabase.ItemSpawner(SkillType::Smithing, 1);
                    for (const auto &item : spawned)
                        inventory.addItem(item);
                }
            }

            if (btn(rightButton, "64"))
            {
                if (i == 0)
                {
                    auto spawned = itemDatabase.ItemSpawner(SkillType::Woodcutting, 64);
                    for (const auto &item : spawned)
                        inventory.addItem(item);
                }
                if (i == 1)
                {
                    auto spawned = itemDatabase.ItemSpawner(SkillType::Mining, 64);
                    for (const auto &item : spawned)
                        inventory.addItem(item);
                }
                if (i == 2)
                {
                    auto spawned = itemDatabase.ItemSpawner(SkillType::Smithing, 64);
                    for (const auto &item : spawned)
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