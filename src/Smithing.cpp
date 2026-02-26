#include "Smithing.h"

static const int typeOffsets[] = { 0, 9, 24, 39, 54, 69, 85, 99 };

struct Recipe
{
    int ore1ID;
    int ore1Amount;
    int ore2ID;
    int ore2Amount;
};

struct GearRecipe
{
    int barsRequired;
};

static const Recipe barRecipes[] =
{
    {2, 1, 3, 1}, // Bronze  (Copper + Tin)
    {4, 1, 0, 0}, // Iron
    {4, 1, 5, 2}, // Steel   (Iron + Coal)
    {6, 1, 0, 0}, // Silver
    {7, 1, 0, 0}, // Gold
    {8, 1, 5, 4}, // Mithril (Mithril + Coal)
    {9, 1, 5, 6}, // Adamantite
    {10,1, 5, 8}, // Runite
    {11,1, 5,10}  // Dragonite
};

static const int gearBarRequirements[] =
{
    0,  // 0 = Nothing (unused)
    1,  // 1 = Bronze gear requires Bronze bar (ID 1)
    2,  // 2 = Iron gear requires Iron bar (ID 2)
    3,  // 3 = Steel gear requires Steel bar (ID 3)
    6,  // 4 = Mithril gear requires Mithril bar (ID 6)
    7,  // 5 = Adamant gear requires Adamant bar (ID 7)
    8,  // 6 = Rune gear requires Rune bar (ID 8)
    9   // 7 = Dragon gear requires Dragon bar (ID 9)
};

static const GearRecipe gearRecipes[15] =
{
    {1}, // Dagger
    {1}, // Arrowtips
    {1}, // Throwing Knife
    {1}, // Sword
    {2}, // Gloves
    {2}, // Scimitar
    {2}, // Helmet
    {3}, // Battleaxe
    {2}, // Javelin Heads
    {2}, // Boots
    {3}, // Shield
    {3}, // 2H Sword
    {3}, // Crossbow Head
    {3}, // Platelegs
    {5}  // Platebody (adjust if needed)
};

Smithing::Smithing(Inventory &inv) : inventory(inv)
{
    background = smithingBG;
}

int Smithing::getNodeLevel(int index) const
{
    if(selectedIndex == 0) // bars
    {
        static int nodeLvls[MAX_BARS]{1, 10, 25, 35, 40, 55, 60, 75, 90};
        return nodeLvls[index];
    }
    else if(selectedIndex == 1) // bronze gear
    {
        static int nodeLvls[MAX_ITEMS]{1, 1, 2, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 16, 18};
        return nodeLvls[index];
    }
    else if(selectedIndex == 2) // iron gear
    {
        static int nodeLvls[MAX_ITEMS]{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 23, 24, 25, 27};
        return nodeLvls[index];
    }
    else if(selectedIndex == 3) // steel gear
    {
        static int nodeLvls[MAX_ITEMS]{25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 36, 38, 39, 40, 42};
        return nodeLvls[index];
    }
    else if(selectedIndex == 4) // mithril gear
    {
        static int nodeLvls[MAX_ITEMS]{40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 53, 54, 55, 57};
        return nodeLvls[index];
    }
    else if(selectedIndex == 5) // adamant gear
    {
        static int nodeLvls[MAX_ITEMS]{55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 68, 69, 70, 72};
        return nodeLvls[index];
    }
    else if(selectedIndex == 6) // rune gear
    {
        static int nodeLvls[MAX_ITEMS]{70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 81, 83, 84, 85, 87};
        return nodeLvls[index];
    }
    else if(selectedIndex == 7) // dragon gear
    {
        static int nodeLvls[MAX_ITEMS]{85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 96, 98, 98, 99, 99};
        return nodeLvls[index];
    }
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
    // ---------------- ICON PANEL (ALWAYS DRAW) ----------------
    Rectangle iconPreviewPanel{345, 220 + (contentY - 100), 100, 100};
    DrawRectangleRounded(iconPreviewPanel, .05f, 16, GRAY);

    // if nothing selected, stop here
    if (selectedItemIndex <= 0)
    {
        createButton(contentY);
        return;
    }

    // ---------------- TAB DATA ----------------
    struct SmithingTabData
    {
        int itemOffset;
        const int* xpArray;
        const std::string* nameArray;
    };

    SmithingTabData tabData[] =
    {
        { 0,   xpPerBar,         barNamesText },
        { 9,   xpPerBronzeGear,  bronzeGearNamesText },
        { 24,  xpPerIronGear,    ironGearNamesText },
        { 39,  xpPerSteelGear,   steelGearNamesText },
        { 54,  xpPerMithrilGear, mithrilGearNamesText },
        { 69,  xpPerAdamantGear, adamantGearNamesText },
        { 84,  xpPerRuneGear,    runeGearNamesText },
        { 99,  xpPerDragonGear,  dragonGearNamesText }
    };

    if (selectedIndex < 0 || selectedIndex >= static_cast<int>(std::size(tabData)))
    {
        createButton(contentY);
        return;
    }

    const SmithingTabData& tab = tabData[selectedIndex];

    int index = selectedItemIndex - 1;
    int itemID = selectedItemIndex + tab.itemOffset;

    Item smithingItem = itemDatabase.getItemByID("smithing", itemID);

    // ---------------- ICON ----------------
    int targetWidth  = 64;
    int targetHeight = 64;

    float iconX = iconPreviewPanel.x + (iconPreviewPanel.width  - targetWidth)  / 2.0f;
    float iconY = iconPreviewPanel.y + (iconPreviewPanel.height - targetHeight) / 2.0f;

    float scale = std::min(targetWidth  / 512.0f, targetHeight / 512.0f);

    DrawTextureEx(smithingItem.getTexture(), {iconX, iconY}, 0.0f, scale, WHITE);

    // ---------------- REQUIREMENTS + PRODUCTION ----------------
    drawSmithingPanelInfo(contentY, index);

    // ---------------- XP TEXT ----------------
    std::string xpAmount = std::to_string(tab.xpArray[index]);

    DrawText( xpAmount.c_str(), 345 + 210, 460 + (contentY - 100), 20, WHITE);

    // ---------------- NAME TEXT ----------------
    DrawText(tab.nameArray[index].c_str(), 460, 260 + (contentY - 100), 20, WHITE);

    // ---------------- CREATE BUTTON ----------------
    createButton(contentY);
}

void Smithing::drawProductionPanel(float contentY, int itemType, int itemAmount)
{
    if (selectedIndex < 0 || selectedIndex >= static_cast<int>(std::size(typeOffsets)))
        return;

    int finalItemType = itemType + typeOffsets[selectedIndex];
    Item smithingItem = itemDatabase.getItemByID("smithing", finalItemType);

    const Texture2D& texture = smithingItem.getTexture();

    float scaleW = targetW / static_cast<float>(texture.width);
    float scaleH = targetH / static_cast<float>(texture.height);
    float scale  = std::min(scaleW, scaleH);

    float yOffset = contentY - 100.0f;

    Vector2 itemLocation{395.0f, 465.0f + yOffset};
    DrawTextureEx(texture, itemLocation, 0.0f, scale, WHITE);
    DrawText(std::to_string(itemAmount).c_str(), 410, static_cast<int>(496.0f + yOffset), 20, WHITE);
}

void Smithing::drawSmithingPanelInfo(float contentY, int index)
{
    // ---------------- STANDARD BARS ----------------
    if (selectedIndex == 0)
    {
        if (index >= 0 && index < static_cast<int>(std::size(barRecipes)))
        {
            const Recipe& recipe = barRecipes[index];

            drawOreCombinationPanel(contentY, recipe.ore1ID, recipe.ore1Amount, recipe.ore2ID, recipe.ore2Amount);
            drawProductionPanel(contentY, index + 1, 1);
        }
        return;
    }

    // ---------------- GEAR TABS ----------------
    if (selectedIndex > 0 && selectedIndex < static_cast<int>(std::size(gearBarRequirements)))
    {
        int requiredBarID = gearBarRequirements[selectedIndex];

        // get how many bars this gear requires from the recipe table
        int barsNeeded = 1; // default fallback
        if (index >= 0 && index < static_cast<int>(std::size(gearRecipes)))
            barsNeeded = gearRecipes[index].barsRequired;

        drawOreCombinationPanel(contentY, requiredBarID, barsNeeded, 0, 0);
        drawProductionPanel(contentY, index + 1, 1);
    }
}

void Smithing::drawOreCombinationPanel(float contentY, int item1, int item1Amount, int item2, int item2Amount)
{
    // decide which item category to use
    const std::string itemType = (selectedIndex == 0) ? "mining" : "smithing";

    // load required items
    Item item1Obj = itemDatabase.getItemByID(itemType, item1);
    Item item2Obj;

    if (item2 != 0) // second item is always ore
        item2Obj = itemDatabase.getItemByID("mining", item2); 

    // safety check
    if (item1Obj.getTexture().width == 0)
        return;

    // scale once
    float scaleW = targetW / (float)item1Obj.getTexture().width;
    float scaleH = targetH / (float)item1Obj.getTexture().height;
    float scale = std::min(scaleW, scaleH);

    float baseY = 365 + (contentY - 100);

    // --- draw REQUIRED side (left) ---
    Vector2 left1{375, baseY};
    DrawTextureEx(item1Obj.getTexture(), left1, 0, scale, WHITE);
    DrawText(std::to_string(item1Amount).c_str(), 385, baseY + 31, 20, WHITE);

    if (item2 != 0)
    {
        Vector2 left2{425, baseY};
        DrawTextureEx(item2Obj.getTexture(), left2, 0, scale, WHITE);
        DrawText(std::to_string(item2Amount).c_str(), 435, baseY + 31, 20, WHITE);
    }

    // --- draw INVENTORY side (right) ---
    Vector2 right1{530, baseY};
    DrawTextureEx(item1Obj.getTexture(), right1, 0, scale, WHITE);

    int invItem1 = inventory.getItemAmount(itemType, item1);
    DrawText(std::to_string(invItem1).c_str(), 540, baseY + 31, 20, WHITE);

    if (item2 != 0) // draw item if it's needed for the combination
    {
        Vector2 right2{580, baseY};
        DrawTextureEx(item2Obj.getTexture(), right2, 0, scale, WHITE);

        int invItem2 = inventory.getItemAmount("mining", item2);
        DrawText(std::to_string(invItem2).c_str(), 590, baseY + 31, 20, WHITE);
    }
}

void Smithing::createButton(float contentY)
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
    if (selectedItemIndex == -1) return false;

    // --- smelting bars (Tab 0) - requires ores from mining ---
    if (selectedIndex == 0)
    {
        int recipeIndex = selectedItemIndex - 1;
        if (recipeIndex < 0 || recipeIndex >= static_cast<int>(std::size(barRecipes))) 
            return false;

        const Recipe& recipe = barRecipes[recipeIndex];
        
        // check first ore
        bool hasOre1 = inventory.getItemAmount("mining", recipe.ore1ID) >= recipe.ore1Amount;
        
        // check second ore (if applicable)
        bool hasOre2 = true;
        if (recipe.ore2ID != 0)
        {
            hasOre2 = inventory.getItemAmount("mining", recipe.ore2ID) >= recipe.ore2Amount;
        }

        return hasOre1 && hasOre2;
    }

    // --- smithing gear (Tabs 1-7) - requires bars from smithing ---
    if (selectedIndex > 0 && selectedIndex < static_cast<int>(std::size(gearBarRequirements)))
    {
        int gearIndex = selectedItemIndex - 1;
        if (gearIndex < 0 || gearIndex >= static_cast<int>(std::size(gearRecipes)))
            return false;

        int requiredBarID = gearBarRequirements[selectedIndex];
        int barsNeeded = gearRecipes[gearIndex].barsRequired;

        return inventory.getItemAmount("smithing", requiredBarID) >= barsNeeded;
    }

    return false;
}

void Smithing::onCompleted()
{
    int index = selectedItemIndex - 1;

    if (index < 0)
        return;

    // ---------------- STANDARD BARS ----------------
    if (selectedIndex == 0)
    {
        if (index >= static_cast<int>(std::size(barRecipes)))
            return;

        const Recipe& recipe = barRecipes[index];

        // remove required ores (always mining)
        if (!inventory.removeItem("mining", recipe.ore1ID, recipe.ore1Amount))
            return;

        if (recipe.ore2ID != 0)
        {
            if (!inventory.removeItem("mining", recipe.ore2ID, recipe.ore2Amount))
                return;
        }

        // create produced bar item from database
        Item producedBar = itemDatabase.getItemByID("smithing", selectedItemIndex);
        producedBar.setAmount(1);

        inventory.addItem(producedBar);

        return;
    }

    // ---------------- GEAR ----------------
    if (selectedIndex > 0 && selectedIndex < static_cast<int>(std::size(gearBarRequirements)))
    {
        if (index < 0 || index >= static_cast<int>(std::size(gearRecipes)))
            return;

        int requiredBarID = gearBarRequirements[selectedIndex];
        int barsNeeded = gearRecipes[index].barsRequired;

        // check amount first (safe crafting)
        if (inventory.getItemAmount("smithing", requiredBarID) < barsNeeded)
            return;

        // remove required bars
        inventory.removeItem("smithing", requiredBarID, barsNeeded);

        // calculate final gear ID
        int finalItemType = selectedItemIndex + typeOffsets[selectedIndex];

        Item producedGear = itemDatabase.getItemByID("smithing", finalItemType);
        producedGear.setAmount(1);

        inventory.addItem(producedGear);
    }
}

void Smithing::oreCombination(int ore1Amount, int ore1, int ore2Amount, int ore2, int bar)
{
    // decide which item category to use
    const std::string itemType = (selectedIndex == 0) ? "mining" : "smithing";

    // attempt to remove 1 Ore from two different types of ore
    bool removeOre1 = inventory.removeItem(itemType, ore1, ore1Amount);
    bool removedOre2 = inventory.removeItem(itemType, ore2, ore2Amount);
    
    if (removeOre1 && removedOre2)
    {
        // add Bronze Bar to inventory
        Item createBar = ItemDatabase::getItemByID(itemType, bar);
        inventory.addItem(createBar);
        
        Item ore1Name = ItemDatabase::getItemByID(itemType, ore1);
        Item ore2Name = ItemDatabase::getItemByID(itemType, ore2);
        std::cout << "Successfully combined: " << ore1Name.name << " + " << ore2Name.name << " = " << createBar.getName() << '\n';
    }
    else
    {
        // if combination failed, put back any removed items
        if (removeOre1) inventory.addItem(ItemDatabase::getItemByID(itemType, ore1));
        if (removedOre2) inventory.addItem(ItemDatabase::getItemByID(itemType, ore2));

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
    if (selectedIndex == 0) // standard bars
        numRows = 5;
    else                    // gear tabs
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

        rebuildGrid();
        selectedItemIndex = -1;
        resetSkillProgress();
    }

    BaseSkill::drawXPBar();
}