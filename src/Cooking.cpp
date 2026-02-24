#include "Cooking.h"

Cooking::Cooking(Inventory &inv) : inventory(inv)
{
    background = cookingBG;

    itemDropdown.selectedIndex = Clamp(itemDropdown.selectedIndex, 0, (int)dropdownOptions.size() - 1);
    itemDropdown.bounds = { 1010, 100, 230, 36 };
}

void Cooking::drawDropdown(Dropdown& dd, const std::vector<std::string>& options)
{
    Vector2 mouse = GetMousePosition();

    // clamp selected index to highest unlocked
    int maxUnlocked = getUnlockedSkillIndex();
    dd.selectedIndex = Clamp(dd.selectedIndex, 0, maxUnlocked);

    // main box
    DrawRectangleRec(dd.bounds, LIGHTGRAY);
    DrawRectangleLinesEx(dd.bounds, 1, DARKGRAY);
    
    if(!dd.isOpen)
        DrawText(options[dd.selectedIndex].c_str(), dd.bounds.x + 8, dd.bounds.y + 8, 20, BLACK);

    // arrow
    DrawText(dd.isOpen ? "^" : "v", dd.bounds.x + dd.bounds.width - 20, dd.bounds.y + 8, 20, BLACK);

    // click main box
    if (CheckCollisionPointRec(mouse, dd.bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dd.isOpen = !dd.isOpen;
    }

    // expanded list
    if (dd.isOpen)
    {
        resetSkillProgress();
        for (size_t i = 0; i < options.size(); i++)
        {
            Rectangle itemRect = 
            {
                dd.bounds.x,
                dd.bounds.y + dd.bounds.height * (float)(i + 1),
                dd.bounds.width,
                dd.bounds.height
            };

            bool hover = CheckCollisionPointRec(mouse, itemRect);
            bool unlocked = curLvl >= getNodeLevel(i);

            Color bgColor = unlocked
                ? (hover ? GRAY : RAYWHITE)
                : DARKGRAY;

            Color textColour = unlocked ? BLACK : LIGHTGRAY;

            DrawRectangleRec(itemRect, bgColor);
            DrawRectangleLinesEx(itemRect, 1, DARKGRAY);

            DrawText(options[i].c_str(), itemRect.x + 8, itemRect.y + 8, 20, textColour);
            
            // show level of locked skills
            if (!unlocked)
            {
                std::string req = "Lvl " + std::to_string(getNodeLevel(i));
                DrawText(req.c_str(), itemRect.x + itemRect.width - 60, itemRect.y + 8, 16, LIGHTGRAY);
            }

            // if unlocked and hover over you can left click
            if (hover && unlocked && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                resetSkillProgress();
                dd.selectedIndex = static_cast<int>(i);
                dd.isOpen = false;
            }
        }
    }
}

void Cooking::drawTemplate(float contentY)
{
    // set target size for the icon
    int targetWidth{64};
    int targetHeight{64};
    
    float contentCentreX{800.f};
    float padding{5.f};
    float textSpacing{10.f};

    // background panel
    Rectangle panelBG{contentCentreX - (panelBG.width)/2, 200 + (contentY - 100), 350, 465};
    DrawRectangleRounded(panelBG, .02f, 16, DARKGRAY);
    
    // icon preview panel 345
    Rectangle iconPreviewPanel{650, 225 + (contentY - 100), 100, 100};
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);

    // temp icon
    Item foodIcon = itemDatabase.getItemByID("cooking", 1);
    float ScaleW = targetWidth / (float)foodIcon.getTexture().width;
    float ScaleH = targetHeight / (float)foodIcon.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // name panel
    Rectangle namePreviewPanel{750 + padding, 225 + (contentY - 100), 200, 100};
    DrawRectangleRounded(namePreviewPanel, .05f, 16, GRAY);

    // requirements panel
    Rectangle requirementsPreviewPanel{650, 325 + padding + (contentY - 100), 305, 100};
    DrawRectangleRounded(requirementsPreviewPanel, .05f, 16, GRAY);

    // "Requires:" text
    DrawText("Requires:", requirementsPreviewPanel.x + 30, 325 + textSpacing + (contentY - 100), 20, WHITE);

    // "You have:" text
    DrawText("You Have:", requirementsPreviewPanel.x + requirementsPreviewPanel.width - 125, 325 + textSpacing + (contentY - 100), 20, WHITE);
 
    // production panel
    Rectangle producesPreviewPanel{650, 430 + padding + (contentY - 100), 305, 100};
    DrawRectangleRounded(producesPreviewPanel, .05f, 16, GRAY);

    // "Produces:" text
    DrawText("Produces:", producesPreviewPanel.x + 30, 440 + (contentY - 100), 20, WHITE);

    // "XP:" text
    DrawText("XP:", producesPreviewPanel.x + 210, 440 + (contentY - 100), 20, WHITE);

    // xp amount value
    std::string xpAmount = std::to_string(xpPerFood[itemDropdown.selectedIndex]);
    DrawText(xpAmount.c_str(), producesPreviewPanel.x + 215, 460 + (contentY - 100), 20, WHITE);

    // creation panel
    Rectangle creationPreviewPanel{650, 535 + padding + (contentY - 100), 305, 100};
    DrawRectangleRounded(creationPreviewPanel, .05f, 16, GRAY); 

    xpBarBG = {690, 545 + padding + (contentY-100), 220 , 20};
    DrawRectangleRounded(xpBarBG, .8f, 16, BLACK);

    // xp bar
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);

    // calculate position to centre the icon inside the preview panel
    float iconX = 650 + iconTargetW / 2;
    float iconY = 225 + (contentY -100) + iconTargetH / 2;

    // preview icon
    Vector2 iconPosition = {iconX, iconY};

    int selectedIndex = itemDropdown.selectedIndex;
    int selectedFoodID = selectedIndex +1;

    // draws resources on left panel
    foodIcon = itemDatabase.getItemByID("cooking", selectedFoodID);
    
    // icon position
    DrawTextureEx(foodIcon.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);

    // draw item name string
    DrawText(dropdownOptions[selectedIndex].c_str(), namePreviewPanel.x + padding, 270 + (contentY - 100), 20, WHITE);
    drawInfoPanel(contentY, selectedFoodID, 1);
    
    createButton(contentY);
}

void Cooking::drawInfoPanel(float contentY, int foodID, int foodAmount)
{
    Item rawFoodTex = itemDatabase.getItemByID("fishing", foodID);    
    Item cookedFoodTex = itemDatabase.getItemByID("cooking", foodID);    

    float foodScaleW = iconTargetW / (float)rawFoodTex.getTexture().width;
    float foodScaleH = iconTargetH / (float)rawFoodTex.getTexture().height;
    float scale = std::min(foodScaleW, foodScaleH);

    // draws the left raw food and amount below the food
    Vector2 foodLocationLeft{700, 365 + (contentY -100)};
    DrawTextureEx(rawFoodTex.getTexture(), foodLocationLeft, 1, scale, WHITE);
    DrawText("1", 710, 400 + (contentY-100), 20, WHITE); // requires 1 raw food
    
    // draws the right raw food and amount below the food
    Vector2 foodLocationRight{860, 365 + (contentY -100)};
    DrawTextureEx(rawFoodTex.getTexture(), foodLocationRight, 1, scale, WHITE);
    int rawFood = inventory.getItemAmount("fishing", foodID); // get raw food amount from inventory
    DrawText(std::to_string(rawFood).c_str(), 870, 400 + (contentY-100), 20, WHITE);

    // draws the bottom left cooked food and ammount below the food
    Vector2 foodLocationProduced{700, 465 + (contentY -100)};
    DrawTextureEx(cookedFoodTex.getTexture(), foodLocationProduced, 1, scale, WHITE);
    DrawText("1", 710, 500 + (contentY-100), 20, WHITE); // requires 1 raw food

}

int Cooking::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_FOOD]{1, 5, 10, 15, 20, 35, 40, 50, 50, 55, 60, 65, 70, 75, 85, 95};
    return nodeLvls[index];
}

int Cooking::getUnlockedSkillIndex() const
{
    int highest = 0;
    for (size_t i = 0; i < dropdownOptions.size(); i++)
    {
        if (curLvl >= getNodeLevel(static_cast<int>(i)))
            highest = i;
    }
    return highest;
}

bool Cooking::canCookSelected(int index) const
{
    index += 1; // itemdatabase starts at 1, not 0

    if (inventory.getItemAmount("fishing", index) >= 1) // check to see if we have at least 1 fish
        return inventory.getItemAmount("fishing", index);
    else
    {
        Item rawFishingItem = ItemDatabase::getItemByID("fishing", index);
        std::cout << "You have none of this food to cook: " << rawFishingItem.name << '\n';
    }
    return false;
}

void Cooking::onCompleted()
{
    int index = itemDropdown.selectedIndex;
    index += 1; // dropdown index starts at 0, but the IDs start at 1

    // attempts to remove 1 fish from the inventory
    bool itemRemoval = inventory.removeItem("fishing", index, 1);

    if (itemRemoval)
    {
        // add a food to inventory
        Item createItem = ItemDatabase::getItemByID("cooking", index);
        inventory.addItem(createItem);
    }
    else
    {
        // if failed, put back any removed items
        if (itemRemoval) inventory.addItem(ItemDatabase::getItemByID("fishing", index));
        std::cout << "Not enough food to cook!\n";
    }
}

void Cooking::createButton(float contentY)
{
    // button for creating the item
    Rectangle createButton{700, 580 + (contentY-100), 200 , 50};
    if (BaseSkill::rbtn(createButton, "Start Cooking"))
    {
        if (!isRunning && canCookSelected(itemDropdown.selectedIndex))
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

        progress = runningTime / foodTimer[itemDropdown.selectedIndex];
        progress = Clamp(progress, 0.f, 1.f);

        maxWidth = xpBarBG.width;
        xpBar.x = 690;
        xpBar.y = 550 + (contentY-100);
        xpBar.height = 20;
        xpBar.width = maxWidth * progress;

        if (runningTime >= foodTimer[itemDropdown.selectedIndex])
        {
            runningTime = 0.f;
            xpBar.width = 0.f;

            xpAccumulated = xpPerFood[itemDropdown.selectedIndex];
            
            BaseSkill::updateXPBar(xpAccumulated);
            onCompleted();

            if (canCookSelected(itemDropdown.selectedIndex))
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

void Cooking::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();
    xpBar.width = 0.f;
}

void Cooking::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    drawDropdown(itemDropdown, dropdownOptions);
    BaseSkill::drawXPBar();
}