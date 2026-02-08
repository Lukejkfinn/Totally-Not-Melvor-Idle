#include "Firemaking.h"

Firemaking::Firemaking(Inventory &inv) : inventory(inv)
{
    
}

void Firemaking::DrawDropdown(Dropdown& dd, const std::vector<std::string>& options)
{
    Vector2 mouse = GetMousePosition();

    // Main box
    DrawRectangleRec(dd.bounds, LIGHTGRAY);
    DrawRectangleLinesEx(dd.bounds, 1, DARKGRAY);
    DrawText(options[dd.selectedIndex].c_str(),
             dd.bounds.x + 8, dd.bounds.y + 8, 20, BLACK);

    // Arrow
    DrawText(dd.isOpen ? "^" : "v",
             dd.bounds.x + dd.bounds.width - 20,
             dd.bounds.y + 8, 20, BLACK);

    // Click main box
    if (CheckCollisionPointRec(mouse, dd.bounds) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dd.isOpen = !dd.isOpen;
    }

    // Expanded list
    if (dd.isOpen)
    {
        for (size_t i = 0; i < options.size(); i++)
        {
            Rectangle itemRect = {
                dd.bounds.x,
                dd.bounds.y + dd.bounds.height * (float)(i + 1),
                dd.bounds.width,
                dd.bounds.height
            };

            bool hover = CheckCollisionPointRec(mouse, itemRect);

            DrawRectangleRec(itemRect, hover ? GRAY : RAYWHITE);
            DrawRectangleLinesEx(itemRect, 1, DARKGRAY);
            DrawText(options[i].c_str(),
                    itemRect.x + 8, itemRect.y + 8, 20, BLACK);

            if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                dd.selectedIndex = static_cast<int>(i);
                dd.isOpen = false;
            }
        }
    }
}

void Firemaking::drawProductionPanel(float contentY, int itemType, int amount)
{
    Item item = itemDatabase.getItemByName("firemaking", itemType);

    float ScaleW = targetW / (float)item.getTexture().width;
    float ScaleH = targetH / (float)item.getTexture().height;
    float scale = std::min(ScaleW, ScaleH);

    // draws the produced item and amount text
    Vector2 itemLocationLeft{395, 515 + (contentY -100)};
    DrawTextureEx(item.getTexture(), itemLocationLeft, 1, scale, WHITE);
    std::string itemAmountString = std::to_string(amount); // convert the int to a char
    DrawText(itemAmountString.c_str(), 410, 546 + (contentY -100), 20, WHITE);
}

void Firemaking::drawTemplate(float contentY) 
{

    logDropdown.selectedIndex = Clamp(logDropdown.selectedIndex, 0, (int)logOptions.size() - 1);
    logDropdown.bounds = { 345, 220 + (contentY-100), 220, 36 };

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
    // DrawTextureEx(logIcon.getTexture(), iconPosition, 1, scale, WHITE);

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

    // calculate position to center the icon inside the preview panel
    float iconX = 340 + (100 - targetW) / 2;
    float iconY = 270 + (contentY -100) + (100 - targetH) / 2;

    // preview icon
    Vector2 iconPosition = {iconX, iconY};

    int selectedIndex = logDropdown.selectedIndex;
    int selectedLogID = selectedIndex +1;

    // draws resources on left panel
    logIcon = itemDatabase.getItemByName("woodcutting", selectedLogID);
    // icon position
    DrawTextureEx(logIcon.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);

    // xp amount value
    std::string xpAmount = std::to_string(xpPerLog[logDropdown.selectedIndex]);
    DrawText(xpAmount.c_str(), producesPreviewPanel.x + 210, 510 + (contentY - 100), 20, WHITE);
    DrawText(logOptions[selectedIndex].c_str(), 460 , 310 +(contentY - 100), 20, WHITE);
    drawProductionPanel(contentY, 1, 1);
    drawInfoPanel(contentY, selectedLogID, 1);
    
    createButton(contentY);
}

void Firemaking::drawInfoPanel(float contentY, int logID, int logAmount)
{
    Item log = itemDatabase.getItemByName("woodcutting", logID);    

    float logScaleW = targetW / (float)log.getTexture().width;
    float logScaleH = targetH / (float)log.getTexture().height;
    float scale = std::min(logScaleW, logScaleH);

    // draws the left log and amount below the log
    Vector2 logLocationLeft{400, 415 + (contentY-100)};
    DrawTextureEx(log.getTexture(), logLocationLeft, 1, scale, WHITE);
    std::string logAmountString = std::to_string(logAmount); // convert the int to a char
    DrawText(logAmountString.c_str(), 410, 445 + (contentY-100), 20, WHITE);

    // draws the right log and amount below the log
    Vector2 logLocationRight{555, 415 + (contentY -100)};
    DrawTextureEx(log.getTexture(), logLocationRight, 1, scale, WHITE);

    int invlog = inventory.getItemAmount("woodcutting", logID); // get log amount from inventory
    DrawText(std::to_string(invlog).c_str(), 565, 446 + (contentY-100), 20, WHITE);
}

bool Firemaking::canBurnSelected() const
{
    switch (logDropdown.selectedIndex)
    {
        case 0: // bronze
            return inventory.getItemAmount("woodcutting", 1) >= 1;

        case 1: // iron
            return inventory.getItemAmount("woodcutting", 2) >= 1;

        case 2: // steel
            return inventory.getItemAmount("woodcutting", 3) >= 1;

        case 3: // silver
            return inventory.getItemAmount("woodcutting", 4) >= 1;

        case 4: // gold
            return inventory.getItemAmount("woodcutting", 5) >= 1;

        case 5: // mithril
            return inventory.getItemAmount("woodcutting", 6) >= 1;

        case 6: // adamantite
            return inventory.getItemAmount("woodcutting", 7) >= 1;

        case 7: // runite
            return inventory.getItemAmount("woodcutting", 8) >= 1;

        case 8: // dragonite
            return inventory.getItemAmount("woodcutting", 9) >= 1;
    }
    return false;
}

void Firemaking::onLogCompleted()
{
    int index = logDropdown.selectedIndex; // index of selected log
    logBurn(1, index+1, 1);
}

void Firemaking::logBurn(int logAmount, int input, int output)
{
    const std::string logType = "woodcutting";
    const std::string itemType = "firemaking";

    // Attempt to remove 1 log from two different types of log
    bool removeLog = inventory.removeItem(logType, input, logAmount);

    if (removeLog)
    {
        // Add ashes to inventory
        Item createItem = ItemDatabase::getItemByName(itemType, output);
        inventory.addItem(createItem);

        Item logName = ItemDatabase::getItemByName("woodcutting", input);
        std::cout << "Successfully burnt: " << logName.name << " into " << createItem.getName() << '\n';
    }
    else
    {
        Item logName = ItemDatabase::getItemByName("woodcutting", input);
        // If combination failed, put back any removed items
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

        progress = runningTime / barTimer;
        progress = Clamp(progress, 0.f, 1.f);

        maxWidth = xpBarBG.width;
        xpBar.x = 390;
        xpBar.y = 595 + (contentY-100);
        xpBar.height = 20;
        xpBar.width = maxWidth * progress;

        if (runningTime >= barTimer)
        {
            runningTime = 0.f;
            xpBar.width = 0.f;

            xpAccumulated = xpPerLog[logDropdown.selectedIndex];
            
            BaseSkill::updateXPBar(xpAccumulated);

            onLogCompleted();

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
}

void Firemaking::tick(float deltaTime, float contentY)
{
    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    DrawDropdown(logDropdown, logOptions);
    BaseSkill::drawXPBar();
}