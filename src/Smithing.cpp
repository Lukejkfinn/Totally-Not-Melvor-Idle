#include "Smithing.h"

Smithing::Smithing(Inventory &inv) : inventory(inv)
{
    background = smithingBG;
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
        std::cout << "Successfully combined Ore + Ore into a Bar!\n";
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
        std::cout << "Successfully combined Ore + Ore into a Bar!\n";
    }
    else
    {
        // If combination failed, put back any removed items
        if (removeOre) inventory.addItem(ItemDatabase::getItemByName(oreType, ore));
        std::cout << "Not enough ores to combine!\n";
    }
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
    //DrawTextureEx(previewIcon, iconPosition, 0.0f, scale, WHITE);

    // name panel
    Rectangle namePreviewPanel{450, 220 + (contentY - 100), 200, 100};
    DrawRectangleRounded(namePreviewPanel, .05f, 16, GRAY);

    // text preview
    //DrawText("Bronze Bar", 460, 260 +(contentY - 100), 20, WHITE);

    // requirements panel
    Rectangle requirementsPreviewPanel{345, 325 + (contentY - 100), 305, 100};
    DrawRectangleRounded(requirementsPreviewPanel, .05f, 16, GRAY);

    // production panel
    Rectangle producesPreviewPanel{345, 430 + (contentY - 100), 305, 100};
    DrawRectangleRounded(producesPreviewPanel, .05f, 16, GRAY);

    // creation panel
    Rectangle creationPreviewPanel{345, 535 + (contentY - 100), 305, 100};
    DrawRectangleRounded(creationPreviewPanel, .05f, 16, GRAY);

    // button for creating the item
    Rectangle createButton{400, 565 + (contentY-100), 200 , 50};
    //DrawRectangleRounded(createButton, 1.f, 1, WHITE);

    

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
                selectedItemIndex = index;

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

    //std::cout << "Selected Item Index: " << selectedItemIndex << '\n';
    
    for (int i = 0; i < sizeOfSmithing; i++)
    {
        smithingItem = itemDatabase.getItemByName("smithing", selectedItemIndex);

        if (selectedItemIndex == i+1)
        {
            DrawTextureEx(smithingItem.getTexture(), Vector2{iconPosition.x, iconPosition.y}, 0.0f, scale, WHITE);
            if (selectedItemIndex == sizeOfSmithing-1) // needed as the const array has loads of spaces for this particular bar
            {
                DrawText("Adamantite Bar", 460 , 260 +(contentY - 100), 20, WHITE);
                continue;
            }
            DrawText(barNames[i], 460 , 260 +(contentY - 100), 20, WHITE);
        }
    }

    if (BaseSkill::rbtn(createButton, "Create"))
    {
        if(selectedItemIndex == 1)
            oreCombination(1, 1, 1, 2, 1);  // 1(ID 1) copper, 1(ID 2) tin = 1(ID 1) bronze bar 
        else if(selectedItemIndex == 2)
            oreSmelt(1, 3, 2);              // 1(ID 3) iron  = 1(ID 2) iron bar 
        else if(selectedItemIndex == 3)
            oreCombination(1, 3, 2, 4, 3);  // 1(ID 3) iron, 2(ID 4) coal = 1(ID 3) steel bar 
        else if(selectedItemIndex == 4)
            oreSmelt(1, 5, 4);              // 1(ID 5) silver = 1(ID4) silver bar
        else if(selectedItemIndex == 5)
            oreSmelt(1, 6, 5);              // 1(ID 6) gold = 1(ID5) gold bar
        else if(selectedItemIndex == 6)
            oreCombination(1, 7, 4, 4, 6);  // 1(ID7) mithril, 4(ID4) coal = 1(ID6) mithril bar
        else if(selectedItemIndex == 7)
            oreCombination(1, 8, 6, 4, 7);  // 1(ID8) adamantite, 6(ID4) coal = 1(ID7) adamantite bar
        else if(selectedItemIndex == 8)
            oreCombination(1, 9, 8, 4, 8);  // 1(ID9) runite, 8(ID4) coal = 1(ID8) runite bar
    }
}



void Smithing::tick(float deltaTime, float contentY)
{

    BaseSkill::tick(deltaTime, contentY);
    drawTemplate(contentY);
    BaseSkill::drawXPBar();
}