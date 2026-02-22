#include "Herblore.h"

Herblore::Herblore(Inventory &inv) : inventory(inv)
{

}

void Herblore::drawTemplate(float contentY)
{
    // crafting panel
    Rectangle craftingPanel{325, 200 + (contentY - 100), 930, 800};
    DrawRectangleRounded(craftingPanel, .02f, 16, DARKGRAY);
    
    // icon preview panel
    Rectangle iconPreviewPanel{345, 220 + (contentY - 100), 100, 100};
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);

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

    //Rectangle skillXpBar{390, 545 + (contentY-100), xpBar.width , 20};
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);

    drawButtonGrid(contentY, selectedIndex);
    drawResourcePanel(contentY, selectedIndex);
    createButton(contentY);
}

void Herblore::drawButtonGrid(float contentY, int selectedIndex)
{
    const float startX{660.f};
    const float startY{220.f + (contentY-100)};
    const float buttonWidth{285.f};
    const float buttonHeight{75.f};
    const float padding{10.f};

    std::string skillPotions[MAX_HERBS] = 
    {
        "Bird Nest     \nPotion",
        "    Controlled Heat \n    Potion",
        "   Generous Cook \n   Potion",
        "Seeing Gold   \nPotion",
        "      Fishermans Potion",
        "    Skilled Fletching\n    Potion",
        "   Gentle Hands    \n   Potion",
        "    Secret Stardust\n    Potion",
        "  Crafting Potion",
        "   Perfect Swing  \n   Potion",
        "       Necromancer Potion",
        "    Performance\n    Enhancing Potion",
        "   Elemental Potion",
        "   Herblore Potion",
        "      Generous Harvest\n      Potion"
    };

    std::string combatPotions[MAX_HERBS] = 
    {
        "   Melee Accuracy \n   Potion",
        " Melee Evasion \n Potion",
        "      Ranged Assistance\n      Potion",
        "Hinder Potion",
        "    Magic Assistance\n    Potion",
        "Regeneration \nPotion",
        "   Famished Potion",
        "     Ranged Strength\n     Potion",
        "Lucky Herb  \nPotion",
        "Divine Potion ",
        "  Melee Strength\n  Potion",
        "Magic Damage \nPotion",
        "Lethal Toxin \nPotion",
        "Diamond Luck \nPotion",       
        "     Damage Reduction\n     Potion"
    };

    int index = 0;
    float barScaleX = buttonWidth / 512.0f;
    float barScaleY = buttonHeight / 512.0f;
    float barScale = std::min(barScaleX, barScaleY);

    for (int row = 0; row < numRows; row++) 
    {   
        for (int col = 0; col < numCols; col++) 
        {
            int i = row * numCols + col;

            if (i == sizeOfHerblore - 1)
                continue;

            buttons[i].width = buttonWidth;
            buttons[i].height = buttonHeight;
            buttons[i].x = startX + col * (buttonWidth + padding);
            buttons[i].y = startY + row * (buttonHeight + padding);

            DrawRectangleRoundedLinesEx(buttons[i], 0.f, 0, 1, WHITE);

            bool unlocked = getLevel() >= getNodeLevel(i);

            // ---------------- LOCKED ----------------
            if (!unlocked) {
                std::string lockedText = "Locked";
                int fontSize = 30;
                int textWidth = MeasureText(lockedText.c_str(), fontSize);

                float textX = buttons[i].x + (buttons[i].width - textWidth) / 2;
                float textY = buttons[i].y + (buttons[i].height - fontSize) / 2;

                DrawText(lockedText.c_str(), textX, textY, fontSize, Fade(BLACK, 0.8f));

                std::string unlockLevel = "Lvl " + std::to_string(getNodeLevel(i));
                DrawText(unlockLevel.c_str(), textX + 20, textY + 25, 20, Fade(BLACK, 0.8f));

                index++;
                continue;
            }

            // ---------------- UNLOCKED ----------------
            Item craftingItem;
            if (selectedIndex == 0)
            {
                craftingItem = itemDatabase.getItemByName("herblore", index +16);

                if (BaseSkill::sbtn(buttons[i], combatPotions[i].c_str(), 20)) 
                {
                    if (selectedItemIndex != index) 
                    {
                        selectedItemIndex = index;
                        resetSkillProgress();
                    }
                } 
            }
            else if(selectedIndex == 1)
            {
                craftingItem = itemDatabase.getItemByName("herblore", index +1);
                
                if (BaseSkill::sbtn(buttons[i], skillPotions[i].c_str(), 20)) 
                {
                    if (selectedItemIndex != index) 
                    {
                        selectedItemIndex = index;
                        resetSkillProgress();
                    }
                } 
            }
                
            DrawTextureEx(craftingItem.getTexture(), Vector2{buttons[i].x + 2, buttons[i].y}, 0.0f, barScale, WHITE);
            index++;
        }
    }
}

void Herblore::drawResourcePanel(float contentY, int selectedIndex)
{
    // set target size for the icon
    int targetWidth = 64;
    int targetHeight = 64;

    // icon preview panel
    Rectangle iconPreviewPanel{345, 220 + (contentY - 100), 100, 100};
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);
    
    // calculate position to center the icon inside the preview panel
    float iconX = iconPreviewPanel.x + (iconPreviewPanel.width - targetWidth) / 2;
    float iconY = iconPreviewPanel.y + (iconPreviewPanel.height - targetHeight) / 2;

    // preview icon
    Vector2 iconPosition = {iconX, iconY};

    // calculate scale factor based on the desired target size
    float scaleX = targetWidth / (float)512;
    float scaleY = targetHeight / (float)512;
    float scale = std::min(scaleX, scaleY);  // maintain aspect ratio

    std::string skillPotions[MAX_HERBS] = 
    {
        "Bird Nest \nPotion",
        "Controlled Heat \nPotion",
        "Generous Cook \nPotion",
        "Seeing Gold \nPotion",
        "Fishermans Potion",
        "Skilled Fletching \nPotion",
        "Gentle Hands \nPotion",
        "Secret Stardust \nPotion",
        "Crafting Potion",
        "Perfect Swing \nPotion",
        "Necromancer \nPotion",
        "Performance \nEnhancing Potion",
        "Elemental Potion",
        "Herblore Potion",
        "Generous Harvest \nPotion"
    };

    std::string combatPotions[MAX_HERBS] = 
    {
        "Melee Accuracy \nPotion",
        "Melee Evasion \nPotion",
        "Ranged \nAssistance Potion",
        "Hinder Potion",
        "Magic Assistance \nPotion",
        "Regeneration \nPotion",
        "Famished Potion",
        "Ranged Strength \nPotion",
        "Lucky Herb \nPotion",
        "Divine Potion",
        "Melee Strength \nPotion",
        "Magic Damage \nPotion",
        "Lethal Toxin \nPotion",
        "Diamond Luck \nPotion",       
        "Damage Reduction \nPotion"
    };

    for (int i = 0; i < sizeOfHerblore; i++) 
    {
        if (selectedItemIndex == i) 
        {
            // display potion-specific text
            if (selectedIndex == 0) 
            {
                Item craftingItem = itemDatabase.getItemByName("herblore", selectedItemIndex +16);
                
                // icon position
                DrawTextureEx(craftingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
                setPanelInfo(contentY, i);

                // xp amount value
                std::string xpAmount = std::to_string(xpPerCombatPot[selectedItemIndex]);
                DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

                DrawText(combatPotions[i].c_str(), 460, 260 + (contentY - 100), 20, WHITE);
            } 
            else if (selectedIndex == 1) 
            {
                Item craftingItem = itemDatabase.getItemByName("herblore", selectedItemIndex +1);

                // icon position
                DrawTextureEx(craftingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
                setPanelInfo(contentY, i);

                // xp amount value
                std::string xpAmount = std::to_string(xpPerSkillPot[selectedItemIndex]);
                DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

                DrawText(skillPotions[i].c_str(), 460, 260 + (contentY - 100), 20, WHITE);
            }
        }
    }
}

void Herblore::setPanelInfo(float contentY, int index)
{
    drawProductionPanel(contentY, index+1, 1);


}

void Herblore::drawRequiresPanel(float contentY, int itemID1, int itemID2, int itemID3, int itemAmount)
{

}

void Herblore::drawProductionPanel(float contentY, int itemType, int itemAmount)
{

}

int Herblore::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_HERBS]{1, 20, 32, 36, 40, 42, 45, 47, 49, 53, 55, 62, 63, 71, 74};
    return nodeLvls[index];
}

void Herblore::createButton(float contentY)
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

            xpAccumulated = xpPerSkillPot[selectedItemIndex];
            
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

bool Herblore::canCreateSelected() const
{
    return true;
}

void Herblore::itemCombination(int item1, int item1Amount, int item2, int item2Amount, int item3, int item3Amount, int createdItem)
{

}

void Herblore::onCompleted()
{

}

void Herblore::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();

    xpBar.width = BaseSkill::singleXpBar.width;
}

int Herblore::setMenuBar (float contentY, std::string buttonNames[], int sizeOfButtons, float textPosY, int fontSize)
{
    selectedIndex = BaseSkill::setMenuBar(contentY, buttonNames, sizeOfButtons, textPosY, fontSize);
    return selectedIndex;
}

void Herblore::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);

    int sizeOfButtons{2};
    std::string buttonNames[sizeOfButtons] =
    {
        "Combat \nPotions",
        "Skill \nPotions"
    };
    setMenuBar(contentY, buttonNames, sizeOfButtons, 10, 18);
    
    BaseSkill::drawXPBar();
}