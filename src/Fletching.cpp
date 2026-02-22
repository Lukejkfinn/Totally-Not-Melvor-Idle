#include "Fletching.h"

Fletching::Fletching(Inventory &inv) : inventory(inv)
{

}

void Fletching::drawTemplate(float contentY)
{
    // set target size for the icon
    int targetWidth = 64;
    int targetHeight = 64;

    // calculate scale factor based on the desired target size
    float scaleX = targetWidth / (float)512;
    float scaleY = targetHeight / (float)512;
    float scale = std::min(scaleX, scaleY);  // Maintain aspect ratio

    // crafting panel
    Rectangle craftingPanel{325, 200 + (contentY - 100), 930, 800};
    DrawRectangleRounded(craftingPanel, .02f, 16, DARKGRAY);
    
    // icon preview panel
    Rectangle iconPreviewPanel{345, 220 + (contentY - 100), 100, 100};
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);
    
    // calculate position to center the icon inside the preview panel
    float iconX = iconPreviewPanel.x + (iconPreviewPanel.width - targetWidth) / 2;
    float iconY = iconPreviewPanel.y + (iconPreviewPanel.height - targetHeight) / 2;

    // preview icon
    Vector2 iconPosition = {iconX, iconY};

    // name panel
    Rectangle namePreviewPanel{450, 220 + (contentY - 100), 200, 100};
    DrawRectangleRounded(namePreviewPanel, .05f, 16, GRAY);

    // requirements panel
    Rectangle requirementsPreviewPanel{345, 325 + (contentY - 100), 305, 100};
    DrawRectangleRounded(requirementsPreviewPanel, .05f, 16, GRAY);

    // "Requires:" text
    DrawText("Requires:", requirementsPreviewPanel.x + 30, 340 + (contentY - 100), 20, WHITE);

    // "You have:" text
    DrawText("You Have:", 345 + requirementsPreviewPanel.width - 125, 340 + (contentY - 100), 20, WHITE);
 
    // production panel
    Rectangle producesPreviewPanel{345, 430 + (contentY - 100), 305, 100};
    DrawRectangleRounded(producesPreviewPanel, .05f, 16, GRAY);

    // "Produces:" text
    DrawText("Produces:", producesPreviewPanel.x + 30, 440 + (contentY - 100), 20, WHITE);

    // "XP:" text
    DrawText("XP:", producesPreviewPanel.x + 210, 440 + (contentY - 100), 20, WHITE);

    // creation panel
    Rectangle creationPreviewPanel{345, 535 + (contentY - 100), 305, 100};
    DrawRectangleRounded(creationPreviewPanel, .05f, 16, GRAY);

    xpBarBG = {390, 545 + (contentY-100), 220 , 20};
    DrawRectangleRounded(xpBarBG, .8f, 16, BLACK);

    // xp bar
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);

    const float startX{660.f};
    const float startY{220.f + (contentY-100)};
    const float buttonWidth{285.f};
    const float buttonHeight{75.f};
    const float padding{10.f};

    const char* barNames[MAX_FLETCH] = 
    {
        "   Arrow Shafts",
        "       Headless Arrows",
        "   Bronze Arrows",
        "   Iron Arrows",
        "   Steel Arrows",
        "   Mithril Arrows",
        "   Adamant Arrows",
        "   Rune Arrows",
        "   Dragon Arrows"
    };

    const char* previewBarNames[MAX_FLETCH] = 
    {
        "Arrow Shafts",
        "Headless Arrows",
        "Bronze Arrows",
        "Iron Arrows",
        "Steel Arrows",
        "Mithril Arrows",
        "Adamant Arrows",
        "Rune Arrows",
        "Dragon Arrows"
    };

    int index = 0;
    
    float barScaleX = buttonWidth / 512.0f;
    float barScaleY = buttonHeight / 512.0f;
    float barScale = std::min(barScaleX, barScaleY);
    
    Item craftingItem;
    
    // draws the skill panels
    for(int row = 0; row < numRows; row++)
    {   
        for (int col = 0; col < numCols; col++)
        {
            int i = row * numCols + col;

            if (i == sizeOfFletching-1)
                continue;

            buttons[i].width = buttonWidth;
            buttons[i].height = buttonHeight;
            buttons[i].x = startX + col * (buttonWidth + padding);
            buttons[i].y = startY + row * (buttonHeight + padding);

            DrawRectangleRoundedLinesEx(buttons[i], 0.f, 0, 1, WHITE);

            bool unlocked = getLevel() >= getNodeLevel(i);

            // ---------------- LOCKED ----------------
            if (!unlocked)
            {
                std::string lockedText = "Locked";
                int fontSize = 30;
                int textWidth = MeasureText(lockedText.c_str(), fontSize);

                float textX = buttons[i].x + (buttons[i].width - textWidth) / 2;
                float textY = buttons[i].y + (buttons[i].height - fontSize) / 2;

                DrawText(lockedText.c_str(), textX, textY, fontSize, Fade(BLACK, 0.8f));

                std::string unlockLevel = "Lvl " + std::to_string(getNodeLevel(i));
                DrawText(unlockLevel.c_str(), textX+20, textY+25, 20, Fade(BLACK, 0.8f));

                index++;
                continue;
            }

            // ---------------- UNLOCKED ----------------
            Item craftingItem = itemDatabase.getItemByName("fletching", index+1);

            if (BaseSkill::sbtn(buttons[i], barNames[i], 20))
            {
                if (selectedItemIndex != index)
                {
                    selectedItemIndex = index;
                    resetSkillProgress();
                }
            }             

            DrawTextureEx(craftingItem.getTexture(), Vector2{buttons[i].x + 2, buttons[i].y}, 0.0f, barScale, WHITE);
            index++;
        }
    }

        // draws resources on left panel
    for (int i = 0; i < sizeOfFletching; i++)
    {
        craftingItem = itemDatabase.getItemByName("fletching", selectedItemIndex+1);

        if (selectedItemIndex == i)
        {
            // icon position
            DrawTextureEx(craftingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            setPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerCraft[selectedItemIndex]);
            DrawText(xpAmount.c_str(), producesPreviewPanel.x + 210, 460 + (contentY - 100), 20, WHITE);
            DrawText(previewBarNames[i], 460 , 260 +(contentY - 100), 20, WHITE);
        }
    }
    createButton(contentY);
}

void Fletching::setPanelInfo(float contentY, int index)
{
    drawProductionPanel(contentY, index+1, 1);


}

void Fletching::drawRequiresPanel(float contentY, int itemID1, int itemID2, int itemID3, int itemAmount)
{

}

void Fletching::drawProductionPanel(float contentY, int itemType, int itemAmount)
{

}

int Fletching::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_FLETCH]{1, 1, 1, 15, 30, 45, 60, 75, 90};
    return nodeLvls[index];
}

void Fletching::createButton(float contentY)
{
    // button for creating the item
    Rectangle createButton{400, 575 + (contentY-100), 200 , 50};
    if (BaseSkill::rbtn(createButton, "Create"))
    {
        if (!isRunning && canCreateSelected())
        {
            isRunning = true;   // start
        }
        else
        {
            resetSkillProgress(); // cancel
        }       
    }

    if (isRunning)
    {      
        runningTime += GetFrameTime();

        progress = runningTime / craftTimer;
        progress = Clamp(progress, 0.f, 1.f);

        maxWidth = xpBarBG.width;
        xpBar.x = 390;
        xpBar.y = 545 + (contentY-100);
        xpBar.height = 20;
        xpBar.width = maxWidth * progress;

        if (runningTime >= craftTimer)
        {
            runningTime = 0.f;
            xpBar.width = 0.f;

            xpAccumulated = xpPerCraft[selectedItemIndex];
            
            BaseSkill::updateXPBar(xpAccumulated);
            onCompleted();

            if (canCreateSelected())
            {
                // continue cooking
                isRunning = true;
            }
            else
            {
                // out of resources
                resetSkillProgress();
            }
        }
    }
}

bool Fletching::canCreateSelected() const
{
    return true;
}

void Fletching::itemCombination(int item1, int item1Amount, int item2, int item2Amount, int item3, int item3Amount, int createdItem)
{

}

void Fletching::onCompleted()
{

}

void Fletching::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();

    xpBar.width = BaseSkill::singleXpBar.width;
}

void Fletching::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    BaseSkill::drawXPBar();
}