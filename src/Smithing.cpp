#include "Smithing.h"

Smithing::Smithing(Inventory &inv) : inventory(inv)
{
    background = smithingBG;
}

int Smithing::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_BARS]{1, 10, 25, 35, 40, 55, 60, 75, 90};
    return nodeLvls[index];
}

void Smithing::drawTemplate(float contentY)
{
    // smithing panel
    Rectangle smithingPanel{325, 200 + (contentY - 100), 930, 800};
    DrawRectangleRounded(smithingPanel, .02f, 16, DARKGRAY);
    
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

    std::string barNames[MAX_ITEMS] =
    {
        "Bronze Bar",
        "Iron Bar",
        "Steel Bar",
        "Silver Bar",
        "Gold Bar",
        "Mithril Bar",
        "       Adamantite Bar",
        "Runite Bar",
        "Dragonite Bar"
    };

    std::string bronzeGearNames[MAX_ITEMS] =
    {
        "    Bronze Dagger",
        "        Bronze Arrowtips",
        "    Bronze\n    Throwing Knife",
        "    Bronze Sword",
        "    Bronze Gloves",
        "     Bronze Scimitar",
        "    Bronze Helmet",
        "        Bronze Battleaxe",
        "   Bronze\n   Javelin Heads",
        "    Bronze Boots",
        "    Bronze Shield",
        "        Bronze 2H Sword",
        "     Bronze\n     Crossbow Head",
        "        Bronze Platelegs",
        "         Bronze Platebody",
    };

    std::string ironGearNames[MAX_ITEMS] =
    {
        "Iron Dagger",
        "    Iron Arrowtips",
        "    Iron\n    Throwing Knife",
        "Iron Sword",
        " Iron Gloves",
        "  Iron Scimitar",
        " Iron Helmet",
        "     Iron Battleaxe",
        "   Iron\n   Javelin Heads",
        " Iron Boots",
        " Iron Shield",
        "     Iron 2H Sword",
        "     Iron\n     Crossbow Head",
        "     Iron Platelegs",
        "      Iron Platebody",
    };

    std::string steelGearNames[MAX_ITEMS] =
    {
        "Steel Dagger",
        "    Steel Arrowtips",
        "    Steel\n    Throwing Knife",
        "Steel Sword",
        " Steel Gloves",
        "  Steel Scimitar",
        " Steel Helmet",
        "     Steel Battleaxe",
        "   Steel\n   Javelin Heads",
        " Steel Boots",
        " Steel Shield",
        "     Steel 2H Sword",
        "     Steel\n     Crossbow Head",
        "     Steel Platelegs",
        "      Steel Platebody",
    };
    
    std::string mithrilGearNames[MAX_ITEMS] =
    {
        "  Mithril Dagger",
        "      Mithril Arrowtips",
        "    Mithril\n    Throwing Knife",
        "  Mithril Sword",
        "  Mithril Gloves",
        "   Mithril Scimitar",
        "  Mithril Helmet",
        "       Mithril Battleaxe",
        "   Mithril\n   Javelin Heads",
        "  Mithril Boots",
        "  Mithril Shield",
        "      Mithril 2H Sword",
        "     Mithril\n     Crossbow Head",
        "      Mithril Platelegs",
        "       Mithril Platebody",
    };

    std::string adamantGearNames[MAX_ITEMS] =
    {
        "     Adamant Dagger",
        "        Adamant Arrowtips",
        "    Adamant\n    Throwing Knife",
        "     Adamant Sword",
        "     Adamant Gloves",
        "       Adamant Scimitar",
        "     Adamant Helmet",
        "          Adamant Battleaxe",
        "   Adamant\n   Javelin Heads",
        "     Adamant Boots",
        "     Adamant Shield",
        "         Adamant 2H Sword",
        "     Adamant\n     Crossbow Head",
        "         Adamant Platelegs",
        "          Adamant Platebody",
    };
    
    std::string runeGearNames[MAX_ITEMS] =
    {
        "Rune Dagger",
        "    Rune Arrowtips",
        "    Rune\n    Throwing Knife",
        "Rune Sword",
        " Rune Gloves",
        "  Rune Scimitar",
        " Rune Helmet",
        "     Rune Battleaxe",
        "   Rune\n   Javelin Heads",
        " Rune Boots",
        " Rune Shield",
        "     Rune 2H Sword",
        "     Rune\n     Crossbow Head",
        "     Rune Platelegs",
        "      Rune Platebody",
    };

    std::string dragonGearNames[MAX_ITEMS] =
    {
        "    Dragon Dagger",
        "        Dragon Arrowtips",
        "    Dragon\n    Throwing Knife",
        "    Dragon Sword",
        "    Dragon Gloves",
        "     Dragon Scimitar",
        "    Dragon Helmet",
        "        Dragon Battleaxe",
        "   Dragon\n   Javelin Heads",
        "    Dragon Boots",
        "    Dragon Shield",
        "        Dragon 2H Sword",
        "     Dragon\n     Crossbow Head",
        "        Dragon Platelegs",
        "         Dragon Platebody",
    };
    
    std::string* smithingNames = nullptr;

    if (selectedIndex == 0)
        smithingNames = barNames;
    else if (selectedIndex == 1)
        smithingNames = bronzeGearNames;
    else if (selectedIndex == 2)
        smithingNames = ironGearNames;
    else if (selectedIndex == 3)
        smithingNames = steelGearNames;
    else if (selectedIndex == 4)
        smithingNames = mithrilGearNames;
    else if (selectedIndex == 5)
        smithingNames = adamantGearNames;
    else if (selectedIndex == 6)
        smithingNames = runeGearNames;
    else if (selectedIndex == 7)
        smithingNames = dragonGearNames;
        
    drawButtonGrid(contentY, selectedIndex, smithingNames);
    drawResourcePanel(contentY, selectedIndex, smithingNames);
}

void Smithing::drawButtonGrid(float contentY, int selectedIndex, std::string smithingNames[])
{
    const float startX{660.f};
    const float startY{220.f + (contentY-100)};
    const float buttonWidth{285.f};
    const float buttonHeight{75.f};
    const float padding{10.f};

    int index = 1;
    float barScaleX = buttonWidth / 512.0f;
    float barScaleY = buttonHeight / 512.0f;
    float barScale = std::min(barScaleX, barScaleY);

    // draws the skill panels
    for(int row = 0; row < numRows; row++)
    {   
        for (int col = 0; col < numCols; col++)
        {
            int i = row * numCols + col;

            if(i == sizeOfSmithing-1) // we have 9, not 10. Skip last
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
            Item smithingItem;

            // draws textures
            if (selectedIndex == 0) // bars
                smithingItem = itemDatabase.getItemByID("smithing", index);
            else if (selectedIndex == 1) // bronze gear
                smithingItem = itemDatabase.getItemByID("smithing", index +9);
            else if (selectedIndex == 2) // iron gear
                smithingItem = itemDatabase.getItemByID("smithing", index +24);
            else if (selectedIndex == 3) // steel gear
                smithingItem = itemDatabase.getItemByID("smithing", index +39);
            else if (selectedIndex == 4) // mithril gear
                smithingItem = itemDatabase.getItemByID("smithing", index +54);
            else if (selectedIndex == 5) // adamant gear
                smithingItem = itemDatabase.getItemByID("smithing", index +69);
            else if (selectedIndex == 6) // rune gear
                smithingItem = itemDatabase.getItemByID("smithing", index +84);
            else if (selectedIndex == 7) // dragon gear
                smithingItem = itemDatabase.getItemByID("smithing", index +99);

            if (BaseSkill::sbtn(buttons[i], smithingNames[i].c_str(), 20))
            {
                if (selectedItemIndex != index)
                {
                    selectedItemIndex = index;
                    resetSkillProgress();
                }
            }             

            DrawTextureEx(smithingItem.getTexture(), Vector2{buttons[i].x + 2, buttons[i].y}, 0.0f, barScale, WHITE);
            index++;
        }
    }
}

void Smithing::drawResourcePanel(float contentY, int selectedIndex, std::string barNames[])
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
    float scale = std::min(scaleX, scaleY);  // Maintain aspect ratio

    // draws resources on left panel
    for (int i = 0; i < sizeOfSmithing; i++)
    {
        Item smithingItem;

        if (selectedItemIndex == i+1 && selectedIndex == 0)
        {
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // bar names
            DrawText(barNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 1)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+9);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // bronze gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 2)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+24);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // iron gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 3)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+39);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // steel gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 4)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+54);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // mithril gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 5)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+69);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // adamant gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 6)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+84);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // rune gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
        else if (selectedItemIndex == i+1 && selectedIndex == 7)
        {  
            smithingItem = itemDatabase.getItemByID("smithing", selectedItemIndex+99);

            // icon position
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            // xp amount value
            std::string xpAmount = std::to_string(xpPerBar[selectedItemIndex-1]);
            DrawText(xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

            // dragon gear names
            DrawText(bronzeGearNamesText[i].c_str(), 460 , 260 +(contentY - 100), 20, WHITE);
        }
    }
    beginSmithing(contentY);
}

void Smithing::drawProductionPanel(float contentY, int itemType, int itemAmount)
{
    Item smithingItem;

    float ScaleW = targetW / (float)smithingItem.getTexture().width;
    float ScaleH = targetH / (float)smithingItem.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    if (selectedIndex == 0)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 1)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+9);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 2)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+24);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 3)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+39);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 4)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+54);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 5)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+69);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 6)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+85);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
    else if (selectedIndex == 7)
    {
        smithingItem = itemDatabase.getItemByID("smithing", itemType+99);

        // draws the produced bar and amount text below the bar
        Vector2 itemLocationLeft{395, 465 + (contentY -100)};
        DrawTextureEx(smithingItem.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount); 
        DrawText(itemAmountString.c_str(), 410, 496 + (contentY -100), 20, WHITE);
    }
}

void Smithing::drawSmithingPanelInfo(float contentY, int index)
{
    if (index == 0) // copper bar requirements
    {
        drawOreCombinationPanel(contentY, 2, 1, 3, 1); // IDs for copper and tin 
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 1) // iron bar requirements
    {
        drawOreCombinationPanel(contentY, 4, 1, 0, 0);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 2) // steel bar requirements
    {
        drawOreCombinationPanel(contentY, 4, 1, 5, 2);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 3) // silver bar requirements
    {
        drawOreCombinationPanel(contentY, 6, 1, 0, 0);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 4) // gold bar requirements
    {
        drawOreCombinationPanel(contentY, 7, 1, 0, 0);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 5) // mithril bar requirements
    {
        drawOreCombinationPanel(contentY, 8, 1, 5, 4);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 6) // adamantite bar requirements
    {
        drawOreCombinationPanel(contentY, 9, 1, 5, 6);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 7) // runeite bar requirements
    {
        drawOreCombinationPanel(contentY, 10, 1, 5, 8);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 8) // dragonite bare requirements
    {
        drawOreCombinationPanel(contentY, 11, 1, 5, 10);
        drawProductionPanel(contentY, index+1, 1);
    }  
}

void Smithing::drawOreCombinationPanel(float contentY, int item1, int item1Amount, int item2, int item2Amount)
{
    Item item1Name = itemDatabase.getItemByID("mining", item1);   
    Item item2Name = itemDatabase.getItemByID("mining", item2);   

    float scaleW = targetW / (float)item1Name.getTexture().width;
    float scaleH = targetH / (float)item1Name.getTexture().height;
    float scale = std::min(scaleW, scaleH);

    // draws the two left ores and the amount text below them
    Vector2 itemLocationLeft1{375, 365 + (contentY-100)};
    Vector2 itemLocationLeft2{425, 365 + (contentY-100)};
    DrawTextureEx(item1Name.getTexture(), itemLocationLeft1, 1, scale, WHITE);
    DrawTextureEx(item2Name.getTexture(), itemLocationLeft2, 1, scale, WHITE);

    std::string item1AmountString = std::to_string(item1Amount); 
    std::string item2AmountString = std::to_string(item2Amount); 
    DrawText(item1AmountString.c_str(), 385, 396 + (contentY-100), 20, WHITE);
    DrawText(item2AmountString.c_str(), 435, 396 + (contentY-100), 20, WHITE);

    // draws the two right ores and the amount text below them
    Vector2 itemLocationRight1{530, 365 + (contentY-100)};
    Vector2 itemLocationRight2{580, 365 + (contentY-100)};
    DrawTextureEx(item1Name.getTexture(), itemLocationRight1, 1, scale, WHITE);
    DrawTextureEx(item2Name.getTexture(), itemLocationRight2, 1, scale, WHITE);

    int invItem1 = inventory.getItemAmount("mining", item1); // get ore amount from inventory
    int invItem2 = inventory.getItemAmount("mining", item2); // get ore amount from inventory
    DrawText(std::to_string(invItem1).c_str(), 540, 396 + (contentY-100), 20, WHITE);
    DrawText(std::to_string(invItem2).c_str(), 590, 396 + (contentY-100), 20, WHITE);
}

void Smithing::beginSmithing(float contentY)
{
    // button for creating the item
    Rectangle createButton{400, 575 + (contentY-100), 200 , 50};
    if (BaseSkill::rbtn(createButton, "Create") && selectedItemIndex != -1)
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

        progress = runningTime / barTimer;
        progress = Clamp(progress, 0.f, 1.f);

        maxWidth = xpBarBG.width;
        xpBar.x = 390;
        xpBar.y = 545 + (contentY-100);
        xpBar.height = 20;
        xpBar.width = maxWidth * progress;

        if (runningTime >= barTimer)
        {
            runningTime = 0.f;
            xpBar.width = 0.f;

            xpAccumulated = xpPerBar[selectedItemIndex];
            
            BaseSkill::updateXPBar(xpAccumulated);

            onCompleted();

            if (canCreateSelected())
            {
                // continue smelting
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

bool Smithing::canCreateSelected() const
{
    std::cout << "SelectedItemIndex: " << selectedItemIndex << '\n';
    switch (selectedItemIndex)
    {
        case 1: // bronze
            return inventory.getItemAmount("mining", 2) >= 1 &&
                   inventory.getItemAmount("mining", 3) >= 1;

        case 2: // iron
            return inventory.getItemAmount("mining", 4) >= 1;

        case 3: // steel
            return inventory.getItemAmount("mining", 4) >= 1 &&
                   inventory.getItemAmount("mining", 5) >= 2;

        case 4: // silver
            return inventory.getItemAmount("mining", 6) >= 1;

        case 5: // gold
            return inventory.getItemAmount("mining", 7) >= 1;

        case 6: // mithril
            return inventory.getItemAmount("mining", 8) >= 1 &&
                   inventory.getItemAmount("mining", 5) >= 4;

        case 7: // adamantite
            return inventory.getItemAmount("mining", 9) >= 1 &&
                   inventory.getItemAmount("mining", 5) >= 6;

        case 8: // runite
            return inventory.getItemAmount("mining", 10) >= 1 &&
                   inventory.getItemAmount("mining", 5) >= 8;

        case 9: // dragonite
            return inventory.getItemAmount("mining", 11) >= 1 &&
                   inventory.getItemAmount("mining", 5) >= 10;
    }
    return false;
}

void Smithing::onCompleted()
{
    if(selectedItemIndex == 1)
        oreCombination(1, 2, 1, 3, 1);      // (1) copper ore (ID=2), (1) tin (ID=3) = (1) bronze bar (ID=1)
    else if(selectedItemIndex == 2)
        oreSmelt(1, 4, 2);                  // (1) iron ore (ID=4) = (1) iron bar (ID=2)  
    else if(selectedItemIndex == 3)
        oreCombination(1, 4, 2, 5, 3);      // (1) iron ore (ID=4), (2) coal (ID=5) = (1) steel bar (ID=3) 
    else if(selectedItemIndex == 4)
        oreSmelt(1, 6, 4);                  // (1) silver ore (ID=6) = (1) silver bar (ID=4) 
    else if(selectedItemIndex == 5)
        oreSmelt(1, 7, 5);                  // (1) gold ore (ID=7) = (1) gold bar (ID=5) 
    else if(selectedItemIndex == 6)
        oreCombination(1, 8, 4, 5, 6);      // (1) mithril ore (ID=8), (4) coal (ID=5) = (1) mithril bar (ID=6) 
    else if(selectedItemIndex == 7)
        oreCombination(1, 9, 6, 5, 7);      // (1) adamantite ore (ID=9), (6) coal (ID=5) = (1) adamantite bar (ID=7)
    else if(selectedItemIndex == 8)
        oreCombination(1, 10, 8, 5, 8);      // (1) runite ore (ID=10), (8) coal (ID=5) = (1) runite bar(ID=8) 
    else if(selectedItemIndex == 9)
        oreCombination(1, 11, 10, 5, 9);    // (1) dragonite ore (ID=11), (10) coal (ID=5) = (1) dragonite bar (ID=9) 
}

void Smithing::oreCombination(int ore1Amount, int ore1, int ore2Amount, int ore2, int bar)
{
    const std::string oreType = "mining";
    const std::string barType = "smithing";
    // attempt to remove 1 Ore from two different types of ore
    bool removeOre1 = inventory.removeItem(oreType, ore1, ore1Amount);
    bool removedOre2 = inventory.removeItem(oreType, ore2, ore2Amount);
    
    if (removeOre1 && removedOre2)
    {
        // add Bronze Bar to inventory
        Item createBar = ItemDatabase::getItemByID(barType, bar);
        inventory.addItem(createBar);
        
        Item ore1Name = ItemDatabase::getItemByID("mining", ore1);
        Item ore2Name = ItemDatabase::getItemByID("mining", ore2);
        std::cout << "Successfully combined: " << ore1Name.name << " + " << ore2Name.name << " = " << createBar.getName() << '\n';
    }
    else
    {
        // if combination failed, put back any removed items
        if (removeOre1) inventory.addItem(ItemDatabase::getItemByID(oreType, ore1));
        if (removedOre2) inventory.addItem(ItemDatabase::getItemByID(oreType, ore2));

        std::cout << "Not enough ores to combine!\n";
    }
}

void Smithing::oreSmelt(int oreAmount, int ore, int bar)
{
    const std::string oreType = "mining";
    const std::string barType = "smithing";

    // attempt to remove 1 Ore from two different types of ore
    bool removeOre = inventory.removeItem(oreType, ore, oreAmount);

    if (removeOre)
    {
        // add Bronze Bar to inventory
        Item createBar = ItemDatabase::getItemByID(barType, bar);
        inventory.addItem(createBar);

        Item oreName = ItemDatabase::getItemByID("mining", ore);
        std::cout << "Successfully combined: " << oreName.name << " = " << createBar.getName() << '\n';
    }
    else
    {
        // if combination failed, put back any removed items
        if (removeOre) inventory.addItem(ItemDatabase::getItemByID(oreType, ore));
        std::cout << "Not enough ores to combine!\n";
    }
}

void Smithing::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();

    xpBar.width = BaseSkill::singleXpBar.width;
}

int Smithing::setMenuBar(float contentY, std::string buttonNames[], int sizeOfButtons, float textPosY, int fontSize)
{
    selectedIndex = BaseSkill::setMenuBar(contentY, buttonNames, sizeOfButtons, textPosY, fontSize);
    return selectedIndex;
}

void Smithing::rebuildGrid()
{
    if (selectedIndex == 0)          // Standard bars
        numRows = 5;
    else                              // Gear tabs
        numRows = 8;

    sizeOfSmithing = numCols * numRows;
}

void Smithing::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);

    int sizeOfButtons{8};
    std::string buttonNames[sizeOfButtons] =
    {
        "Standard \nBars",
        "Bronze \nGear",
        "Iron \nGear",
        "Steel \nGear",
        "Mithril \nGear",
        "Adamant \nGear",
        "Rune \nGear",
        "Dragon \nGear"
    };
    int newIndex = setMenuBar(contentY, buttonNames, sizeOfButtons, 10, 18);

    // detect change
    if (newIndex != previousMenuIndex)
    {
        previousMenuIndex = newIndex;
        selectedIndex = newIndex;

        rebuildGrid();      // <-- we’ll create this
        selectedItemIndex = -1;
        resetSkillProgress();
    }

    BaseSkill::drawXPBar();
}