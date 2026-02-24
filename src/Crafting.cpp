#include "Crafting.h"

Crafting::Crafting(Inventory &inv) : inventory(inv)
{
    background = craftingBG;
}

void Crafting::drawTemplate(float contentY)
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

    //Rectangle skillXpBar{390, 545 + (contentY-100), xpBar.width , 20};
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);


    const float startX{660.f};
    const float startY{220.f + (contentY-100)};
    const float buttonWidth{285.f};
    const float buttonHeight{75.f};
    const float padding{10.f};

    const char* barNames[sizeOfCrafting] = 
    {
        "   Leather Gloves",
        "   Leather Boots",
        "   Leather Cowl",
        "       Leather Vambraces",
        "   Leather Body",
        "   Leather Chaps",
        "       Hard Leather Gloves", 
        "       Hard Leather Boots",
        "       Hard Leather Cowl",
        "           Hard Leather Vambraces",
        "       Hard Leather Body",
        "       Hard Leather Chaps"
    };

    const char* previewBarNames[sizeOfCrafting] = 
    {
        "Leather Gloves",
        "Leather Boots",
        "Leather Cowl",
        "Leather \nVambraces",
        "Leather Body",
        "Leather Chaps",
        "Hard Leather \nGloves", 
        "Hard Leather \nBoots",
        "Hard Leather \nCowl",
        "Hard Leather \nVambraces",
        "Hard Leather \nBody",
        "Hard Leather \nChaps"
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
            Item craftingItem = itemDatabase.getItemByID("crafting", index+1);

            if (BaseSkill::sbtn(buttons[i], barNames[i], 15))
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
    for (int i = 0; i < sizeOfCrafting; i++)
    {
        craftingItem = itemDatabase.getItemByID("crafting", selectedItemIndex+1);

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

void Crafting::setPanelInfo(float contentY, int index)
{
    for (int i = 0; i < sizeOfCrafting; i++)
    {
        if (index >= 6)
            drawRequiresPanel(contentY, 13, 3); // 13 is leather ID
        else
            drawRequiresPanel(contentY, 13, 1); // 13 is leather ID

        drawProductionPanel(contentY, index+1, 1);
    }
}

void Crafting::drawRequiresPanel(float contentY, int itemID, int itemAmount)
{
    int targetW = 32;
    int targetH = 32;   

    Item item = itemDatabase.getItemByID("crafting", itemID);    

    float scaleW = targetW / (float)item.getTexture().width;
    float scaleH = targetH / (float)item.getTexture().height;
    float scale = std::min(scaleW, scaleH);

    // draws the left item and amount below the item
    Vector2 itemLocationLeft{400, 365 + (contentY-100)};
    DrawTextureEx(item.getTexture(), itemLocationLeft, 1, scale, WHITE);
    std::string itemAmountString = std::to_string(itemAmount);
    DrawText(itemAmountString.c_str(), 410, 400 + (contentY-100), 20, WHITE);

    // draws the right item and amount below the item
    Vector2 itemLocationRight{555, 365 + (contentY -100)};
    DrawTextureEx(item.getTexture(), itemLocationRight, 1, scale, WHITE);

    int invItem = inventory.getItemAmount("crafting", itemID); // get item amount from inventory
    DrawText(std::to_string(invItem).c_str(), 565, 400 + (contentY-100), 20, WHITE);
}

void Crafting::drawProductionPanel(float contentY, int itemType, int itemAmount)
{
    Item item = itemDatabase.getItemByID("crafting", itemType);

    float ScaleW = targetW / (float)item.getTexture().width;
    float ScaleH = targetH / (float)item.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // draws the produced item and amount text below the item
    Vector2 itemLocationLeft{395, 465 + (contentY -100)};
    DrawTextureEx(item.getTexture(), itemLocationLeft, 1, scale, WHITE);
    std::string itemAmountString = std::to_string(itemAmount);
    DrawText(itemAmountString.c_str(), 410, 500 + (contentY -100), 20, WHITE);
}

int Crafting::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_CRAFTS]{1, 7, 9, 11, 14, 18, 24, 28, 33, 39, 44, 50};
    return nodeLvls[index];
}

void Crafting::createButton(float contentY)
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

bool Crafting::canCreateSelected() const
{
    if (selectedItemIndex < 6 && selectedItemIndex >= 0)
        return inventory.getItemAmount("crafting", 13) >= 1;
    else if (selectedItemIndex >= 6)
        return inventory.getItemAmount("crafting", 13) >= 3;
    return false;
}

void Crafting::onCompleted()
{
    bool itemRemoval;
    // attempts to remove 1 item from the inventory
    if (selectedItemIndex < 6 && selectedItemIndex >= 0)
        itemRemoval = inventory.removeItem("crafting", 13, 1);
    else if (selectedItemIndex >= 6)
        itemRemoval = inventory.removeItem("crafting", 13, 3);

    if (itemRemoval)
    {
        // add a item to inventory
        Item createItem = ItemDatabase::getItemByID("crafting", selectedItemIndex+1);
        inventory.addItem(createItem);
    }
    else
    {
        // if failed, put back any removed items
        if (itemRemoval) inventory.addItem(ItemDatabase::getItemByID("crafting", selectedItemIndex+1));
        std::cout << "Not enough leather to craft item!\n";
    }
}

void Crafting::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();

    xpBar.width = BaseSkill::singleXpBar.width;
}

void Crafting::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    BaseSkill::drawXPBar();
}