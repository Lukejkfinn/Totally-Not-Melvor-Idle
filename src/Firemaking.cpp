#include "Firemaking.h"

Firemaking::Firemaking(Inventory &inv) : inventory(inv)
{
    
}

void Firemaking::drawDropdown(Dropdown& dd, const std::vector<std::string>& options)
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

void Firemaking::drawProductionPanel(float contentY, int itemType, int amount)
{
    Item item = itemDatabase.getItemByName("firemaking", itemType);

    float ScaleW = iconTargetW / (float)item.getTexture().width;
    float ScaleH = iconTargetH / (float)item.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // draws the produced item and amount text
    Vector2 itemLocationLeft{395, 515 + (contentY -100)};
    DrawTextureEx(item.getTexture(), itemLocationLeft, 1, scale, WHITE);
    std::string itemAmountString = std::to_string(amount); // convert the int to a char
    DrawText(itemAmountString.c_str(), 410, 546 + (contentY -100), 20, WHITE);
}

void Firemaking::drawTemplate(float contentY) 
{
    itemDropdown.selectedIndex = Clamp(itemDropdown.selectedIndex, 0, (int)dropdownOptions.size() - 1);
    itemDropdown.bounds = { 345, 220 + (contentY-100), 230, 36 };

    // set target size for the icon
    int targetWidth = 64;
    int targetHeight = 64;

    // background panel
    Rectangle panelBG{325, 200 + (contentY - 100), 930, 800};
    DrawRectangleRounded(panelBG, .02f, 16, DARKGRAY);
    
    // icon preview panel
    Rectangle iconPreviewPanel{345, 270 + (contentY - 100), 100, 100};
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);

    // temp icon
    Item logIcon = itemDatabase.getItemByName("woodcutting", 1);
    float ScaleW = targetWidth / (float)logIcon.getTexture().width;
    float ScaleH = targetHeight / (float)logIcon.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // name panel
    Rectangle namePreviewPanel{450, 270 + (contentY - 100), 200, 100};
    DrawRectangleRounded(namePreviewPanel, .05f, 16, GRAY);

    // requirements panel
    Rectangle requirementsPreviewPanel{345, 375 + (contentY - 100), 305, 100};
    DrawRectangleRounded(requirementsPreviewPanel, .05f, 16, GRAY);

    // "Requires:" text
    DrawText("Requires:", requirementsPreviewPanel.x + 30, 390 + (contentY - 100), 20, WHITE);

    // "You have:" text
    DrawText("You Have:", 345 + requirementsPreviewPanel.width - 125, 390 + (contentY - 100), 20, WHITE);
 
    // production panel
    Rectangle producesPreviewPanel{345, 480 + (contentY - 100), 305, 100};
    DrawRectangleRounded(producesPreviewPanel, .05f, 16, GRAY);

    // "Produces:" text
    DrawText("Produces:", producesPreviewPanel.x + 30, 490 + (contentY - 100), 20, WHITE);

    // "XP:" text
    DrawText("XP:", producesPreviewPanel.x + 210, 490 + (contentY - 100), 20, WHITE);

    // creation panel
    Rectangle creationPreviewPanel{345, 585 + (contentY - 100), 305, 100};
    DrawRectangleRounded(creationPreviewPanel, .05f, 16, GRAY); 

    xpBarBG = {390, 595 + (contentY-100), 220 , 20};
    DrawRectangleRounded(xpBarBG, .8f, 16, BLACK);

    //xpBar = {390, 595 + (contentY - 100), 0, 20};
    DrawRectangleRounded(xpBar, .8f, 16, GREEN);

    // calculate position to centre the icon inside the preview panel
    float iconX = 340 + (100 - iconTargetW) / 2;
    float iconY = 270 + (contentY -100) + (100 - iconTargetH) / 2;

    // preview icon
    Vector2 iconPosition = {iconX, iconY};

    int selectedIndex = itemDropdown.selectedIndex;
    int selectedLogID = selectedIndex +1;

    // draws resources on left panel
    logIcon = itemDatabase.getItemByName("woodcutting", selectedLogID);
    // icon position
    DrawTextureEx(logIcon.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);

    // xp amount value
    std::string xpAmount = std::to_string(xpPerLog[itemDropdown.selectedIndex]);
    DrawText(xpAmount.c_str(), producesPreviewPanel.x + 210, 510 + (contentY - 100), 20, WHITE);
    DrawText(dropdownOptions[selectedIndex].c_str(), 460 , 310 +(contentY - 100), 20, WHITE);
    drawProductionPanel(contentY, 1, 1);
    drawInfoPanel(contentY, selectedLogID, 1);
    
    createButton(contentY);
}

void Firemaking::drawInfoPanel(float contentY, int logID, int logAmount)
{
    Item log = itemDatabase.getItemByName("woodcutting", logID);    

    float logScaleW = iconTargetW / (float)log.getTexture().width;
    float logScaleH = iconTargetH / (float)log.getTexture().height;
    float scale = std::min(logScaleW, logScaleH);

    // draws the left log and amount below the log
    Vector2 logLocationLeft{400, 415 + (contentY-100)};
    DrawTextureEx(log.getTexture(), logLocationLeft, 1, scale, WHITE);
    std::string logAmountString = std::to_string(logAmount); // convert the int to a char
    DrawText(logAmountString.c_str(), 410, 450 + (contentY-100), 20, WHITE);

    // draws the right log and amount below the log
    Vector2 logLocationRight{555, 415 + (contentY -100)};
    DrawTextureEx(log.getTexture(), logLocationRight, 1, scale, WHITE);

    int invlog = inventory.getItemAmount("woodcutting", logID); // get log amount from inventory
    DrawText(std::to_string(invlog).c_str(), 565, 450 + (contentY-100), 20, WHITE);
}

bool Firemaking::canBurnSelected() const
{
    switch (itemDropdown.selectedIndex)
    {
        case 0: // normal log
            return inventory.getItemAmount("woodcutting", 1) >= 1;

        case 1: // oak log
            return inventory.getItemAmount("woodcutting", 2) >= 1;

        case 2: // willow log
            return inventory.getItemAmount("woodcutting", 3) >= 1;

        case 3: // teak log
            return inventory.getItemAmount("woodcutting", 4) >= 1;

        case 4: // maple log
            return inventory.getItemAmount("woodcutting", 5) >= 1;

        case 5: // mahogany log
            return inventory.getItemAmount("woodcutting", 6) >= 1;

        case 6: // yew log
            return inventory.getItemAmount("woodcutting", 7) >= 1;

        case 7: // magic log
            return inventory.getItemAmount("woodcutting", 8) >= 1;

        case 8: // redwood log
            return inventory.getItemAmount("woodcutting", 9) >= 1;
    }
    return false;
}

int Firemaking::getNodeLevel(int index) const
{
    static int nodeLvls[MAX_LOGS]{1, 10, 25, 35, 45, 55, 60, 75, 90};
    return nodeLvls[index];
}

int Firemaking::getUnlockedSkillIndex() const
{
    int highest = 0;
    for (size_t i = 0; i < dropdownOptions.size(); i++)
    {
        if (curLvl >= getNodeLevel(static_cast<int>(i)))
            highest = i;
    }
    return highest;
}

void Firemaking::onCompleted()
{
    int index = itemDropdown.selectedIndex; // index of selected log
    logBurn(1, index+1, 1);
}

void Firemaking::logBurn(int logAmount, int input, int output)
{
    const std::string logType = "woodcutting";
    const std::string itemType = "firemaking";

    // attempt to remove 1 log from two different types of log
    bool removeLog = inventory.removeItem(logType, input, logAmount);

    if (removeLog)
    {
        // add ashes to inventory
        Item createItem = ItemDatabase::getItemByName(itemType, output);
        inventory.addItem(createItem);

        Item logName = ItemDatabase::getItemByName("woodcutting", input);
        std::cout << "Successfully burnt: " << logName.name << " into " << createItem.getName() << '\n';
    }
    else
    {
        Item logName = ItemDatabase::getItemByName("woodcutting", input);
        
        // if combination failed, put back any removed items
        if (removeLog) inventory.addItem(ItemDatabase::getItemByName(logType, input));
        std::cout << "Not enough " << logName.name <<  " to burn!\n";
    }
}

void Firemaking::createButton(float contentY)
{
    // button for creating the item
    Rectangle createButton{400, 625 + (contentY-100), 200 , 50};
    if (BaseSkill::rbtn(createButton, "Burn"))
    {
        if (!isRunning && canBurnSelected())
        {
            isRunning = true;   // start smelting
        }
        else
        {
            resetSkillProgress(); // cancel
        }       
    }

    if (isRunning)
    {      
        runningTime += GetFrameTime();

        progress = runningTime / logBurnTimer[itemDropdown.selectedIndex];
        progress = Clamp(progress, 0.f, 1.f);

        maxWidth = xpBarBG.width;
        xpBar.x = 390;
        xpBar.y = 595 + (contentY-100);
        xpBar.height = 20;
        xpBar.width = maxWidth * progress;

        if (runningTime >= logBurnTimer[itemDropdown.selectedIndex])
        {
            runningTime = 0.f;
            xpBar.width = 0.f;

            xpAccumulated = xpPerLog[itemDropdown.selectedIndex];
            
            BaseSkill::updateXPBar(xpAccumulated);

            onCompleted();

            if (canBurnSelected())
            {
                // continue smelting
                isRunning = true;
            }
            else
            {
                // out of logs
                resetSkillProgress();
            }
        }
    }
}

void Firemaking::resetSkillProgress()
{
    BaseSkill::resetSkillProgress();
    xpBar.width = 0.f;
}

void Firemaking::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    drawDropdown(itemDropdown, dropdownOptions);
    BaseSkill::drawXPBar();
}