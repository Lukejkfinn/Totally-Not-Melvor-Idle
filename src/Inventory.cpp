
#include "Inventory.h"



void Inventory::initializeInventory() // not used since we have a debugger to spawn in items
{
    // example of populating with a few items
    // Texture2D normalLog = LoadTexture("assets/bank/woodcutting/logs_normal.png");
    // Item normalLogItem(normalLog, 1, true, 64, "Normal Log", 1); // Example item: stackable log

    // Texture2D oakLog = LoadTexture("assets/bank/woodcutting/logs_oak.png");
    // Item oakLogItem(oakLog, 1, true, 64, "Oak Log", 2); // Example item: stackable log

    // Texture2D pickaxeTexture = LoadTexture("assets/icons/pickaxe.png");
    // Item pickaxeItem(pickaxeTexture, 20, false, 1);  // Example item: non-stackable pickaxe

    // Add the items to the inventory

    //addItem(oakLogItem);
    

    // addItem(pickaxeItem);
}

// add item to inventory
void Inventory::addItem(const Item &item)
{
    if (item.isStackable()) // check if the item is stackable
    {
        for (auto &existingItem : items)
        {
            // check if the existing item is stackable and matches the item type
            if (existingItem.getTexture().id == item.getTexture().id && existingItem.isStackable())
            {
                int newAmount = existingItem.getAmount() + item.getAmount();

                // if item can be stacked, increase the amount
                if (newAmount > existingItem.getMaxStack())
                    newAmount = existingItem.getMaxStack();
                
                existingItem.setAmount(newAmount); // increase the amount (not max stack)
                return;                            // exit after adding to the existing item
                
            }
        }
    }
    // if item isn't stackable or doesn't already exist, add it as a new item
    items.push_back(item);
}

void Inventory::drawInventory(const Inventory &inventory, int startX, int startY, int cellSize)
{
    const int itemsPerRow{8}; // number of items per row in the inventory
    const int paddingX{10};   // space between items
    const int paddingY{30};
    const int textPaddingY{5};

    // get mouse position
    Vector2 mousePos = GetMousePosition();

    // iterate over all items in the inventory
    for (size_t i = 0; i < inventory.items.size(); ++i)
    {
        int row = i / itemsPerRow; // determine the row
        int col = i % itemsPerRow; // determine the column

        // calculate position to draw the item (spacing between items)
        int posX = startX + col * (cellSize + paddingX);
        int posY = startY + row * (cellSize + paddingY);

        // get the texture for the item
        Texture2D texture = inventory.items[i].getTexture();

        // centre the image within the cell
        if (texture.id != 0)
        {
            float scale = (float)cellSize / (float)texture.width; // scaling the texture
            int imgWidth = texture.width * scale;
            int imgHeight = texture.height * scale;

            // draw the texture (icon), center the image in the cell
            DrawTextureEx(texture, Vector2{(float)(posX + (cellSize - imgWidth) / 2), (float)posY}, 0.0f, scale, WHITE);

            // check if the mouse is clicking the item
            Rectangle itemRect = {(float)(posX), (float)posY, (float)imgWidth, (float)imgHeight};
            if (CheckCollisionPointRec(mousePos, itemRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // handle the action when the item is clicked (e.g., open a UI, select the item)
                // call a function to handle this item click action
                onItemClick(i); // +1 to adjust item index to be 1-based
            }
        }

        // draw a border around the cell to help visualize it
        DrawRectangleLines(posX, posY, cellSize, cellSize, BLUE); // draw cell border (blue)

        // draw the item amount
        std::string text = std::to_string(inventory.items[i].amount);
        int textWidth = MeasureText(text.c_str(), 20); // use font size 20 for text width measurement
        int textHeight = 20;                           // set height for the text (this should match your font size)

        // adjust the vertical position of the text to add enough space under the image
        int textY = posY + cellSize + textPaddingY; // move the text further down based on cell size + padding

        // centre the text under the image (and adjust if needed for large numbers)
        DrawText(text.c_str(), posX + (cellSize / 2) - (textWidth / 2), textY, textHeight, WHITE);

        // if the info panel is visible, draw it
        if (infoPanelVisible)
        {
            const float iPBGPosX{940.f};
            const float iPBGPosY{100.f};
            const float iPBGWidth{300.f};
            const float iPBGHeight{300.f};

            // draw the info panel (background rectangle)
            Rectangle infoPanelBG{iPBGPosX, iPBGPosY, iPBGWidth, iPBGHeight};
            DrawRectangleRec(infoPanelBG, GRAY);

            // draw item name
            std::string itemName = inventory.items[currentItemIndex].getName();
            DrawText(itemName.c_str(), 950, 110, 20, WHITE);
            
            // draw item skill type
            std::string itemSkillType = "Skill: " + inventory.items[currentItemIndex].getSkillType();
            DrawText(itemSkillType.c_str(), 950, 150, 20, WHITE);

            // draw item ID
            std::string itemID = "ID: " + std::to_string(inventory.items[currentItemIndex].getId());
            DrawText(itemID.c_str(), 950, 190, 20, WHITE);
        }
    }
}

// function that gets called when an item is clicked
void Inventory::onItemClick(int itemIndex)
{
    std::cout << "Item " << itemIndex << " clicked!" << std::endl;

    // if the clicked item is the same as the currently displayed one, leave the panel open.
    // if a different item is clicked, open the panel with new information.
    if (infoPanelVisible && itemIndex == currentItemIndex)
    {
        // if the same item is clicked, do nothing (keep the panel open)
        return;
    }

    // show the info panel and update the current item index
    infoPanelVisible = true;
    currentItemIndex = itemIndex; // store the clicked item's index for display
}