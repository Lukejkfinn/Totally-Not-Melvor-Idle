#include "Runecrafting.h"

Runecrafting::Runecrafting(Inventory &inv) : inventory(inv)
{
    background = runecraftingBG;
}

void Runecrafting::drawTemplate(float contentY)
{
    // set target size for the icon
    int targetWidth = 64;
    int targetHeight = 64;

    // calculate scale factor based on the desired target size
    float scaleX = targetWidth / (float)512;
    float scaleY = targetHeight / (float)512;
    float scale = std::min(scaleX, scaleY);  // Maintain aspect ratio

    // crafting panel
    Rectangle craftingPanel{325, 200 + (contentY - 100), 930, 880};
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

    //Rectangle skillXpBar{390, 545 + (contentY-100), xpBar.width , 20};
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);


    const float startX{660.f};
    const float startY{220.f + (contentY-100)};
    const float buttonWidth{285.f};
    const float buttonHeight{75.f};
    const float padding{10.f};

    const char* barNames[sizeOfRunecrafting] = 
    {
        "Air Rune",
        "Mind Rune",
        "Water Rune",
        "Earth Rune",
        "Mist Rune",
        "Fire Rune",
        "Light Rune", 
        "Body Rune",
        "Dust Rune",
        "Mud Rune",
        "Chaos Rune",
        "   Nature Rune",
        "Smoke Rune",
        "Havoc Rune",
        "Steam Rune",
        "Lava Rune",
        "Death Rune",
        "Blood Rune",
        "Spirit Rune",
        "   Ancient Rune"
    };

    const char* previewBarNames[sizeOfRunecrafting] = 
    {
        "Air Rune",
        "Mind Rune",
        "Water Rune",
        "Earth Rune",
        "Mist Rune",
        "Fire Rune",
        "Light Rune", 
        "Body Rune",
        "Dust Rune",
        "Mud Rune",
        "Chaos Rune",
        "Nature Rune",
        "Smoke Rune",
        "Havoc Rune",
        "Steam Rune",
        "Lava Rune",
        "Death Rune",
        "Blood Rune",
        "Spirit Rune",
        "Ancient Rune"
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
            Item craftingItem = itemDatabase.getItemByName("runecrafting", index+1);

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
    for (int i = 0; i < sizeOfRunecrafting; i++)
    {
        craftingItem = itemDatabase.getItemByName("runecrafting", selectedItemIndex+1);

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

void Runecrafting::setPanelInfo(float contentY, int index)
{
    drawProductionPanel(contentY, index+1, 1);

    if (selectedItemIndex+1 == mistRune)        drawRequiresPanel(contentY, runeEssence, airRune, waterRune, 2);
    else if(selectedItemIndex+1 == dustRune)    drawRequiresPanel(contentY, runeEssence, airRune, earthRune, 2);
    else if (selectedItemIndex+1 == mudRune)    drawRequiresPanel(contentY, runeEssence, waterRune, earthRune, 2);
    else if (selectedItemIndex+1 == smokeRune)  drawRequiresPanel(contentY, runeEssence, airRune, fireRune, 2);
    else if (selectedItemIndex+1 == steamRune)  drawRequiresPanel(contentY, runeEssence, waterRune, fireRune, 2);
    else if (selectedItemIndex+1 == lavaRune)   drawRequiresPanel(contentY, runeEssence, earthRune, fireRune, 2);
    else                                        drawRequiresPanel(contentY, runeEssence, 0, 0, 1);
}

void Runecrafting::drawRequiresPanel(float contentY, int itemID1, int itemID2, int itemID3, int itemAmount)
{
    int targetW = 32;
    int targetH = 32;   

    Item item1 = itemDatabase.getItemByName("mining", itemID1);
    Item item2 = itemDatabase.getItemByName("runecrafting", itemID2);
    Item item3 = itemDatabase.getItemByName("runecrafting", itemID3);   


    float scaleW = targetW / (float)item1.getTexture().width;
    float scaleH = targetH / (float)item1.getTexture().height;
    float scale = std::min(scaleW, scaleH);

    // if a combination rune, draw the 3 combination runes
    if (selectedItemIndex+1 == 5 || selectedItemIndex+1 == 9 || selectedItemIndex+1 == 10 || selectedItemIndex+1 == 13 || selectedItemIndex+1 == 15 || selectedItemIndex+1 == 16)
    {
        Vector2 itemLocationLeft1{363, 365 + (contentY-100)};
        DrawTextureEx(item1.getTexture(), itemLocationLeft1, 1, scale, WHITE);
        std::string itemAmountString1 = std::to_string(itemAmount); 
        DrawText(itemAmountString1.c_str(), 375, 400 + (contentY-100), 20, WHITE);

        Vector2 itemLocationLeft2{400, 365 + (contentY-100)};
        DrawTextureEx(item2.getTexture(), itemLocationLeft2, 1, scale, WHITE);
        std::string itemAmountString2 = std::to_string(itemAmount); 
        DrawText(itemAmountString2.c_str(), 412, 400 + (contentY-100), 20, WHITE);

        Vector2 itemLocationLeft3{437, 365 + (contentY-100)};
        DrawTextureEx(item3.getTexture(), itemLocationLeft3, 1, scale, WHITE);
        std::string itemAmountString3 = std::to_string(itemAmount); 
        DrawText(itemAmountString3.c_str(), 449, 400 + (contentY-100), 20, WHITE);
    }
    else
    {
        // otherwise, draw the singular rune
        Vector2 itemLocationLeft{400, 365 + (contentY-100)};
        DrawTextureEx(item1.getTexture(), itemLocationLeft, 1, scale, WHITE);
        std::string itemAmountString = std::to_string(itemAmount);
        DrawText(itemAmountString.c_str(), 412, 400 + (contentY-100), 20, WHITE);
    }

    // draws the right item and amount below the item
    Vector2 itemLocationRight{555, 365 + (contentY -100)};
    DrawTextureEx(item1.getTexture(), itemLocationRight, 1, scale, WHITE);

    int invItem = inventory.getItemAmount("mining", itemID1); // get item amount from inventory
    DrawText(std::to_string(invItem).c_str(), 565, 400 + (contentY-100), 20, WHITE);
}

void Runecrafting::drawProductionPanel(float contentY, int itemType, int itemAmount)
{
    Item item = itemDatabase.getItemByName("runecrafting", itemType);

    float ScaleW = targetW / (float)item.getTexture().width;
    float ScaleH = targetH / (float)item.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // draws the produced item and amount text below the item
    Vector2 itemLocationLeft{395, 465 + (contentY -100)};
    DrawTextureEx(item.getTexture(), itemLocationLeft, 1, scale, WHITE);
    std::string itemAmountString = std::to_string(itemAmount);
    DrawText(itemAmountString.c_str(), 410, 500 + (contentY -100), 20, WHITE);
}

int Runecrafting::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_RC]{1, 1, 5, 9, 10, 14, 15, 20, 20, 30, 35, 40, 40, 50, 50, 60, 65, 75, 80, 85};
    return nodeLvls[index];
}

void Runecrafting::createButton(float contentY)
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

bool Runecrafting::canCreateSelected() const
{

    if (selectedItemIndex+1 == 5) // mist rune ID(5)
    {
        return inventory.getItemAmount("mining", runeEssence) >= 1 &&
        inventory.getItemAmount("runecrafting", airRune) >= 2 &&
        inventory.getItemAmount("runecrafting", waterRune) >= 2;
    }
    else if(selectedItemIndex+1 == 9) // dust rune ID(9)
    {
        return inventory.getItemAmount("mining", runeEssence) >= 1 &&
        inventory.getItemAmount("runecrafting", airRune) >= 2 &&
        inventory.getItemAmount("runecrafting", earthRune) >= 2;
    }
    else if (selectedItemIndex+1 == 10) // mud rune ID(10)
    {
        return inventory.getItemAmount("mining", runeEssence) >= 1 &&
        inventory.getItemAmount("runecrafting", waterRune) >= 2 &&
        inventory.getItemAmount("runecrafting", earthRune) >= 2;
    }
    else if (selectedItemIndex+1 == 13) // smoke rune ID(13)
    {
        return inventory.getItemAmount("mining", runeEssence) >= 1 &&
        inventory.getItemAmount("runecrafting", airRune) >= 2 &&
        inventory.getItemAmount("runecrafting", fireRune) >= 2;
    }
    else if (selectedItemIndex+1 == 15) // steam rune ID(15)
    {
        return inventory.getItemAmount("mining", runeEssence) >= 1 &&
        inventory.getItemAmount("runecrafting", waterRune) >= 2 &&
        inventory.getItemAmount("runecrafting", fireRune) >= 2;
    }
    else if (selectedItemIndex+1 == 16) // lava rune ID(16)
    {       
        return inventory.getItemAmount("mining", runeEssence) >= 1 &&
        inventory.getItemAmount("runecrafting", earthRune) >= 2 &&
        inventory.getItemAmount("runecrafting", fireRune) >= 2;
    }
    else
        return inventory.getItemAmount("mining", 1) >= 1;

    std::cout << "Not enough runes:\n" 
        << "Rune Essence: " << inventory.getItemAmount("mining", runeEssence) 
        << "\nAir Runes: " << inventory.getItemAmount("runecrafting", airRune) 
        << "\nWater Runes: " << inventory.getItemAmount("runecrafting", waterRune) 
        << "\nEarth Runes: " << inventory.getItemAmount("runecrafting", earthRune) 
        << "\nFire Runes: " << inventory.getItemAmount("runecrafting", fireRune) 
        << '\n';

    return false;
}

void Runecrafting::itemCombination(int item1, int item1Amount, int item2, int item2Amount, int item3, int item3Amount, int createdItem)
{
    const std::string runeEssence = "mining";
    const std::string essenceType = "runecrafting";

    // attempts to remove 1 essence and two runes by an ammount
    bool removeItem1 = inventory.removeItem(runeEssence, item1, item1Amount);
    bool removeItem2 = inventory.removeItem(essenceType, item2, item2Amount);
    bool removeItem3 = inventory.removeItem(essenceType, item3, item3Amount);
    
    if (removeItem1 && removeItem2 && removeItem3)
    {
        Item item1Name = ItemDatabase::getItemByName("mining", item1);          // rune essence
        Item item2Name = ItemDatabase::getItemByName("runecrafting", item2);    // rune type
        Item item3Name = ItemDatabase::getItemByName("runecrafting", item3);    // rune type
        
        // create combined item
        Item createItem = ItemDatabase::getItemByName(essenceType, createdItem);
        inventory.addItem(createItem);
        

        std::cout << "Successfully combined: " << item1Name.name << " + " << item2Name.name << " + " << item3Name.name << " = " << createItem.getName() << '\n';
    }
    else
    {
        // if combination failed, put back any removed items
        if (removeItem1) inventory.addItem(ItemDatabase::getItemByName(runeEssence, item1));
        if (removeItem2) inventory.addItem(ItemDatabase::getItemByName(essenceType, item2));
        if (removeItem3) inventory.addItem(ItemDatabase::getItemByName(essenceType, item3));

        // 943 need to check that this adds the correct amount back 
        std::cout << "Not enough ores to combine!\n";
    }
}

void Runecrafting::onCompleted()
{
    if (selectedItemIndex+1 == mistRune) // mist rune ID(5)
    {
        itemCombination(runeEssence, 1, airRune, 2, waterRune, 2, mistRune);
    }
    else if(selectedItemIndex+1 == dustRune) // dust rune ID(9)
    {
        itemCombination(runeEssence, 1, airRune, 2, earthRune, 2, dustRune);
    }
    else if (selectedItemIndex+1 == mudRune) // mud rune ID(10)
    {
        itemCombination(runeEssence, 1, waterRune, 2, earthRune, 2, mudRune);
    }
    else if (selectedItemIndex+1 == smokeRune) // smoke rune ID(13)
    {
        itemCombination(runeEssence, 1, airRune, 2, fireRune, 2, smokeRune);
    }
    else if (selectedItemIndex+1 == steamRune) // steam rune ID(15)
    {
        itemCombination(runeEssence, 1, waterRune, 2, fireRune, 2, steamRune);
    }
    else if (selectedItemIndex+1 == lavaRune) // lava rune ID(16)
    {       
        itemCombination(runeEssence, 1, earthRune, 2, fireRune, 2, lavaRune);
    }
}

void Runecrafting::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();

    xpBar.width = BaseSkill::singleXpBar.width;
}

void Runecrafting::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    BaseSkill::drawXPBar();
}