#include "Smithing.h"

Smithing::Smithing(Inventory &inv) : inventory(inv)
{
    background = smithingBG;
    
}

void Smithing::drawTemplate(float contentY)
{
    
    // ensure texture is loaded once and not every frame
    if (previewIcon.id == 0) {
        std::cerr << "Texture not loaded!" << std::endl;
        return;
    }

    // set target size for the icon
    int targetWidth = 64;
    int targetHeight = 64;

    // calculate scale factor based on the desired target size
    float scaleX = targetWidth / (float)previewIcon.width;
    float scaleY = targetHeight / (float)previewIcon.height;
    float scale = std::min(scaleX, scaleY);  // Maintain aspect ratio

    Rectangle iconPreviewPanel{345, 220 + (contentY - 100), 100, 100};

    // calculate position to center the icon inside the preview panel
    float iconX = iconPreviewPanel.x + (iconPreviewPanel.width - targetWidth) / 2;
    float iconY = iconPreviewPanel.y + (iconPreviewPanel.height - targetHeight) / 2;

    // smithing panel
    Rectangle smithingPanel{325, 200 + (contentY - 100), 930, 800};
    DrawRectangleRounded(smithingPanel, .02f, 16, DARKGRAY);

    // icon preview panel
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);

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

    // button for creating the item
    Rectangle createButton{400, 575 + (contentY-100), 200 , 50};

    Rectangle xpBarBG{390, 545 + (contentY-100), 220 , 20};
    DrawRectangleRounded(xpBarBG, .8f, 16, BLACK);

    //Rectangle skillXpBar{390, 545 + (contentY-100), xpBar.width , 20};
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);

    const int numCols = 2;
    const int numRows = 5;
    const int sizeOfSmithing{numCols * numRows};
    const float startX{660.f};
    const float startY{220.f + (contentY-100)};
    const float buttonWidth{285.f};
    const float buttonHeight{75.f};
    const float padding{10.f};

    Rectangle buttons[sizeOfSmithing]{};

    const char* barNames[sizeOfSmithing] = 
    {
        "Bronze Bar",
        "Iron Bar",
        "Steel Bar",
        "Silver Bar",
        "Gold Bar",
        "Mithril Bar",
        "       Adamantite Bar", //long ass name so needs the spaces
        "Runite Bar",
        "Dragonite Bar"
    };

    int index = 1;
    
    float barScaleX = buttonWidth / 512.0f;
    float barScaleY = buttonHeight / 512.0f;
    float barScale = std::min(barScaleX, barScaleY);
    
    Item smithingItem;
    
    for(int row = 0; row < numRows; row++)
    {   
        for (int col = 0; col < numCols; col++)
        {
            int i = row * numCols + col;

            if(i == sizeOfSmithing-1) // we have 9, not 10. Skip laste
                continue;

            buttons[i].width = buttonWidth;
            buttons[i].height = buttonHeight;
            buttons[i].x = startX + col * (buttonWidth + padding);
            buttons[i].y = startY + row * (buttonHeight + padding);

            DrawRectangleRoundedLinesEx(buttons[i], 0.f, 0, 1, WHITE);
            
            smithingItem = itemDatabase.getItemByName("smithing", index);

            if (BaseSkill::sbtn(buttons[i], barNames[i]))
            {
                if (selectedItemIndex != index)   // only reset if recipe actually changed
                {
                    selectedItemIndex = index;
                    resetCraftingProgress();
                }
            }                

            if (smithingItem.getTexture().id != 0) 
                DrawTextureEx(smithingItem.getTexture(), Vector2{buttons[i].x + 2, buttons[i].y}, 0.0f, barScale, WHITE);
            else
            {
                std::cerr << "Texture for smithing item is not loaded! " << index << std::endl;
                return;
            }
            index++;
        }
    }
    
    // draws resources on left panel
    for (int i = 0; i < sizeOfSmithing; i++)
    {
        smithingItem = itemDatabase.getItemByName("smithing", selectedItemIndex);

        if (selectedItemIndex == i+1)
        {
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            drawSmithingPanelInfo(contentY, i);

            if (selectedItemIndex == sizeOfSmithing-3) // needed as the const array has loads of spaces for this particular bar
            {
                DrawText("Adamantite Bar", 460 , 260 +(contentY - 100), 20, WHITE);
                continue;
            }

            DrawText(barNames[i], 460 , 260 +(contentY - 100), 20, WHITE);
        }
    }

    if (BaseSkill::rbtn(createButton, "Create") && selectedItemIndex != -1)
    {
        if (!isRunning && canSmeltSelected())
        {
            isRunning = true;   // start smelting
        }
        else
        {
            resetCraftingProgress(); // cancel
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

            onSmeltCompleted();

            if (canSmeltSelected())
            {
                // continue smelting
                isRunning = true;
            }
            else
            {
                // out of ores
                resetCraftingProgress();
            }
        }
    }
}

void Smithing::drawProductionPanel(float contentY, int barType, int barAmount)
{
    Item bar = itemDatabase.getItemByName("smithing", barType);

    float ScaleW = targetW / (float)bar.getTexture().width;
    float ScaleH = targetH / (float)bar.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // draws the produced bar and amount text below the bar
    Vector2 barLocationLeft{395, 465 + (contentY -100)};
    DrawTextureEx(bar.getTexture(), barLocationLeft, 1, scale, WHITE);
    const char* barAmountString = std::to_string(barAmount).c_str(); // convert the int to a char
    DrawText(barAmountString, 410, 496 + (contentY -100), 20, WHITE);
}

void Smithing::drawSmithingPanelInfo(float contentY, int index)
{
    if (index == 0) // copper bar requirements
    {
        drawOreCombinationPanel(contentY, 1, 1, 2, 1); // IDs for copper and tin 
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 1) // iron bar requirements
    {
        drawOreSingularPanel(contentY, 3, 1);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 2) // steel bar requirements
    {
        drawOreCombinationPanel(contentY, 3, 1, 4, 2);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 3) // silver bar requirements
    {
        drawOreSingularPanel(contentY, 5, 1);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 4) // gold bar requirements
    {
        drawOreSingularPanel(contentY, 6, 1);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 5) // mithril bar requirements
    {
        drawOreCombinationPanel(contentY, 7, 1, 4, 4);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 6) // adamantite bar requirements
    {
        drawOreCombinationPanel(contentY, 8, 1, 4, 6);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 7) // runeite bar requirements
    {
        drawOreCombinationPanel(contentY, 9, 1, 4, 8);
        drawProductionPanel(contentY, index+1, 1);
    }
    else if (index == 8) // dragonite bare requirements
    {
        drawOreCombinationPanel(contentY, 10, 1, 4, 10);
        drawProductionPanel(contentY, index+1, 1);
    }  
}

void Smithing::drawOreCombinationPanel(float contentY, int ore1ID, int ore1Amount, int ore2ID, int ore2Amount)
{
    Item ore1 = itemDatabase.getItemByName("mining", ore1ID);   
    Item ore2 = itemDatabase.getItemByName("mining", ore2ID);   

    float oreScaleW = targetW / (float)ore1.getTexture().width;
    float oreScaleH = targetH / (float)ore1.getTexture().height;
    float scale = std::min(oreScaleW, oreScaleH);

    // draws the two left ores and the amount text below them
    Vector2 oreLocationLeft1{375, 365 + (contentY-100)};
    Vector2 oreLocationLeft2{425, 365 + (contentY-100)};
    DrawTextureEx(ore1.getTexture(), oreLocationLeft1, 1, scale, WHITE);
    DrawTextureEx(ore2.getTexture(), oreLocationLeft2, 1, scale, WHITE);

    const char* ore1AmountString = std::to_string(ore1Amount).c_str(); // convert the int to a char
    const char* ore2AmountString = std::to_string(ore2Amount).c_str(); // convert the int to a char
    DrawText(ore1AmountString, 385, 396 + (contentY-100), 20, WHITE);
    DrawText(ore2AmountString, 435, 396 + (contentY-100), 20, WHITE);

    // draws the two right ores and the amount text below them
    Vector2 oreLocationRight1{530, 365 + (contentY-100)};
    Vector2 oreLocationRight2{580, 365 + (contentY-100)};
    DrawTextureEx(ore1.getTexture(), oreLocationRight1, 1, scale, WHITE);
    DrawTextureEx(ore2.getTexture(), oreLocationRight2, 1, scale, WHITE);

    int invOre1 = inventory.getItemAmount("mining", ore1ID); // get ore amount from inventory
    int invOre2 = inventory.getItemAmount("mining", ore2ID); // get ore amount from inventory
    DrawText(std::to_string(invOre1).c_str(), 540, 396 + (contentY-100), 20, WHITE);
    DrawText(std::to_string(invOre2).c_str(), 590, 396 + (contentY-100), 20, WHITE);
}


bool Smithing::canSmeltSelected() const
{
    switch (selectedItemIndex)
    {
        case 1: // bronze
            return inventory.getItemAmount("mining", 1) >= 1 &&
                   inventory.getItemAmount("mining", 2) >= 1;

        case 2: // iron
            return inventory.getItemAmount("mining", 3) >= 1;

        case 3: // steel
            return inventory.getItemAmount("mining", 3) >= 1 &&
                   inventory.getItemAmount("mining", 4) >= 2;

        case 4: // silver
            return inventory.getItemAmount("mining", 5) >= 1;

        case 5: // gold
            return inventory.getItemAmount("mining", 6) >= 1;

        case 6: // mithril
            return inventory.getItemAmount("mining", 7) >= 1 &&
                   inventory.getItemAmount("mining", 4) >= 4;

        case 7: // adamantite
            return inventory.getItemAmount("mining", 8) >= 1 &&
                   inventory.getItemAmount("mining", 4) >= 6;

        case 8: // runite
            return inventory.getItemAmount("mining", 9) >= 1 &&
                   inventory.getItemAmount("mining", 4) >= 8;

        case 9: // dragonite
            return inventory.getItemAmount("mining", 10) >= 1 &&
                   inventory.getItemAmount("mining", 4) >= 10;
    }
    return false;
}

void Smithing::onSmeltCompleted()
{
    if(selectedItemIndex == 1)
        oreCombination(1, 1, 1, 2, 1);      // (1) copper ore (ID=1), (1) tin (ID=2) = (1) bronze bar (ID=1)
    else if(selectedItemIndex == 2)
        oreSmelt(1, 3, 2);                  // (1) iron ore (ID=3) = (1) iron bar (ID=2)  
    else if(selectedItemIndex == 3)
        oreCombination(1, 3, 2, 4, 3);      // (1) iron ore (ID=3), (2) coal (ID=4) = (1) steel bar (ID=3) 
    else if(selectedItemIndex == 4)
        oreSmelt(1, 5, 4);                  // (1) silver ore (ID=5) = (1) silver bar (ID=4) 
    else if(selectedItemIndex == 5)
        oreSmelt(1, 6, 5);                  // (1) gold ore (ID=6) = (1) gold bar (ID=5) 
    else if(selectedItemIndex == 6)
        oreCombination(1, 7, 4, 4, 6);      // (1) mithril ore (ID=7), (4) coal (ID=4) = (1) mithril bar (ID=6) 
    else if(selectedItemIndex == 7)
        oreCombination(1, 8, 6, 4, 7);      // (1) adamantite ore (ID=8), (6) coal (ID=4) = (1) adamantite bar (ID=7)
    else if(selectedItemIndex == 8)
        oreCombination(1, 9, 8, 4, 8);      // (1) runite ore (ID=9), (8) coal (ID=4) = (1) runite bar(ID=8) 
    else if(selectedItemIndex == 9)
        oreCombination(1, 10, 10, 4, 9);    // (1) dragonite ore (ID=10), (10) coal (ID=4) = (1) dragonite bar (ID=9) 
}



void Smithing::drawOreSingularPanel(float contentY, int oreID, int oreAmount)
{
    int targetW = 32;
    int targetH = 32;   

    Item ore = itemDatabase.getItemByName("mining", oreID);    

    float oreScaleW = targetW / (float)ore.getTexture().width;
    float oreScaleH = targetH / (float)ore.getTexture().height;
    float scale = std::min(oreScaleW, oreScaleH);

    // draws the left ore and amount below the ore
    Vector2 oreLocationLeft{400, 365 + (contentY-100)};
    DrawTextureEx(ore.getTexture(), oreLocationLeft, 1, scale, WHITE);
    const char* oreAmountString = std::to_string(oreAmount).c_str(); // convert the int to a char
    DrawText(oreAmountString, 410, 396 + (contentY-100), 20, WHITE);

    // draws the right ore and amount below the ore
    Vector2 oreLocationRight{555, 365 + (contentY -100)};
    DrawTextureEx(ore.getTexture(), oreLocationRight, 1, scale, WHITE);

    int invOre = inventory.getItemAmount("mining", oreID); // get ore amount from inventory
    DrawText(std::to_string(invOre).c_str(), 565, 396 + (contentY-100), 20, WHITE);
}

void Smithing::oreCombination(int ore1Amount, int ore1, int ore2Amount, int ore2, int bar)
{
    const std::string oreType = "mining";
    const std::string barType = "smithing";
    // Attempt to remove 1 Ore from two different types of ore
    bool removeOre1 = inventory.removeItem(oreType, ore1, ore1Amount);
    bool removedOre2 = inventory.removeItem(oreType, ore2, ore2Amount);
    
    if (removeOre1 && removedOre2)
    {
        // Add Bronze Bar to inventory
        Item createBar = ItemDatabase::getItemByName(barType, bar);
        inventory.addItem(createBar);
        
        Item ore1Name = ItemDatabase::getItemByName("mining", ore1);
        Item ore2Name = ItemDatabase::getItemByName("mining", ore2);
        std::cout << "Successfully combined: " << ore1Name.name << " + " << ore2Name.name << " = " << createBar.getName() << '\n';
    }
    else
    {
        // If combination failed, put back any removed items
        if (removeOre1) inventory.addItem(ItemDatabase::getItemByName(oreType, ore1));
        if (removedOre2) inventory.addItem(ItemDatabase::getItemByName(oreType, ore2));

        std::cout << "Not enough ores to combine!\n";
    }
}

void Smithing::oreSmelt(int oreAmount, int ore, int bar)
{
    const std::string oreType = "mining";
    const std::string barType = "smithing";

    // Attempt to remove 1 Ore from two different types of ore
    bool removeOre = inventory.removeItem(oreType, ore, oreAmount);

    if (removeOre)
    {
        // Add Bronze Bar to inventory
        Item createBar = ItemDatabase::getItemByName(barType, bar);
        inventory.addItem(createBar);

        Item oreName = ItemDatabase::getItemByName("mining", ore);
        std::cout << "Successfully combined: " << oreName.name << " = " << createBar.getName() << '\n';
    }
    else
    {
        // If combination failed, put back any removed items
        if (removeOre) inventory.addItem(ItemDatabase::getItemByName(oreType, ore));
        std::cout << "Not enough ores to combine!\n";
    }
}

void Smithing::resetCraftingProgress()
{
    isRunning = false;
    runningTime = 0.f;
    progress = 0.f;
    xpBar.width = 0.f;
}

void Smithing::tick(float deltaTime, float contentY)
{

    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    BaseSkill::drawXPBar();
}