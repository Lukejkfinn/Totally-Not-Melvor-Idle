
#include "Inventory.h"



void Inventory::initializeInventory() // not used since we have a debugger to spawn in items
{
    // Example of populating with a few items
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

// Add item to inventory
void Inventory::addItem(const Item &item)
{
    if (item.isStackable()) // Check if the item is stackable
    {
        for (auto &existingItem : items)
        {
            // Check if the existing item is stackable and matches the item type
            if (existingItem.getTexture().id == item.getTexture().id && existingItem.isStackable())
            {
                int newAmount = existingItem.getAmount() + item.getAmount();

                // If item can be stacked, increase the amount
                if (newAmount > existingItem.getMaxStack())
                    newAmount = existingItem.getMaxStack();
                
                existingItem.setAmount(newAmount); // Increase the amount (not max stack)
                return;                                               // Exit after adding to the existing item
                
            }
        }
    }
    // If item isn't stackable or doesn't already exist, add it as a new item
    items.push_back(item);
}

void Inventory::drawInventory(const Inventory &inventory, int startX, int startY, int cellSize)
{
    const int itemsPerRow{8}; // Number of items per row in the inventory
    const int paddingX{10};   // Space between items
    const int paddingY{30};
    const int textPaddingY{5};

    // Get mouse position
    Vector2 mousePos = GetMousePosition();

    // Iterate over all items in the inventory
    for (size_t i = 0; i < inventory.items.size(); ++i)
    {
        int row = i / itemsPerRow; // Determine the row
        int col = i % itemsPerRow; // Determine the column

        // Calculate position to draw the item (spacing between items)
        int posX = startX + col * (cellSize + paddingX);
        int posY = startY + row * (cellSize + paddingY);

        // Get the texture for the item
        Texture2D texture = inventory.items[i].getTexture();

        // Center the image within the cell
        if (texture.id != 0)
        {
            float scale = (float)cellSize / (float)texture.width; // Scaling the texture
            int imgWidth = texture.width * scale;
            int imgHeight = texture.height * scale;

            // Draw the texture (icon), center the image in the cell
            DrawTextureEx(texture, Vector2{(float)(posX + (cellSize - imgWidth) / 2), (float)posY}, 0.0f, scale, WHITE);

            // Check if the mouse is clicking the item
            Rectangle itemRect = {(float)(posX), (float)posY, (float)imgWidth, (float)imgHeight};
            if (CheckCollisionPointRec(mousePos, itemRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // Handle the action when the item is clicked (e.g., open a UI, select the item)
                // Call a function to handle this item click action
                onItemClick(i); // +1 to adjust item index to be 1-based
            }
        }

        // Draw a border around the cell to help visualize it
        DrawRectangleLines(posX, posY, cellSize, cellSize, BLUE); // Draw cell border (blue)

        // Draw the item amount
        std::string text = std::to_string(inventory.items[i].amount);
        int textWidth = MeasureText(text.c_str(), 20); // Use font size 20 for text width measurement
        int textHeight = 20;                           // Set height for the text (this should match your font size)

        // Adjust the vertical position of the text to add enough space under the image
        int textY = posY + cellSize + textPaddingY; // Move the text further down based on cell size + padding

        // Center the text under the image (and adjust if needed for large numbers)
        DrawText(text.c_str(), posX + (cellSize / 2) - (textWidth / 2), textY, textHeight, WHITE);

        // If the info panel is visible, draw it
        if (infoPanelVisible)
        {
            const float iPBGPosX{940.f};
            const float iPBGPosY{100.f};
            const float iPBGWidth{300.f};
            const float iPBGHeight{300.f};

            // Draw the info panel (background rectangle)
            Rectangle infoPanelBG{iPBGPosX, iPBGPosY, iPBGWidth, iPBGHeight};
            DrawRectangleRec(infoPanelBG, GRAY);

            // Draw item name
            std::string itemName = inventory.items[currentItemIndex].getName();
            DrawText(itemName.c_str(), 950, 110, 20, WHITE);
            
            // Draw item skill type
            std::string itemSkillType = "Skill: " + inventory.items[currentItemIndex].getSkillType();
            DrawText(itemSkillType.c_str(), 950, 150, 20, WHITE);

            // Draw item ID
            std::string itemID = "ID: " + std::to_string(inventory.items[currentItemIndex].getId());
            DrawText(itemID.c_str(), 950, 190, 20, WHITE);
        }
    }
}

// Function that gets called when an item is clicked
void Inventory::onItemClick(int itemIndex)
{
    std::cout << "Item " << itemIndex << " clicked!" << std::endl;

    // If the clicked item is the same as the currently displayed one, leave the panel open.
    // If a different item is clicked, open the panel with new information.
    if (infoPanelVisible && itemIndex == currentItemIndex)
    {
        // If the same item is clicked, do nothing (keep the panel open)
        return;
    }

    // Show the info panel and update the current item index
    infoPanelVisible = true;
    currentItemIndex = itemIndex; // Store the clicked item's index for display
}




// void Inventory::drawInventory(const Inventory &inventory, int startX, int startY, int cellSize)
// {
//     int itemsPerRow = 5;  // Number of items per row in the inventory
//     int padding = 10;     // Space between items

//     // Iterate over all items in the inventory
//     for (size_t i = 0; i < inventory.items.size(); ++i)
//     {
//         int row = i / itemsPerRow;  // Determine the row
//         int col = i % itemsPerRow;  // Determine the column

//         // Calculate position to draw the item (spacing between items)
//         int posX = startX + col * (cellSize + padding);
//         int posY = startY + row * (cellSize + padding);

//         // Get the texture for the item
//         Texture2D texture = inventory.items[i].getTexture();

//         // Declare imgWidth and imgHeight before the if-block so they are accessible
//         int imgWidth = 0;
//         int imgHeight = 0;

//         // Center the image within the cell
//         if (texture.id != 0) {
//             float scale = (float)cellSize / (float)texture.width;  // Scaling the texture
//             imgWidth = texture.width * scale;
//             imgHeight = texture.height * scale;

//             // Draw the texture (icon), center the image in the cell
//             DrawTextureEx(texture, Vector2{(float)(posX + (cellSize - imgWidth) / 2), (float)posY}, 0.0f, scale, WHITE);
//         }

//         // Draw a border around the cell to help visualize it
//         DrawRectangleLines(posX, posY, cellSize, cellSize, BLUE);  // Draw cell border (blue)

//         // Draw the item amount (text below the icon)
//         std::string text = std::to_string(inventory.items[i].amount);

//         // Measure the text width based on font size
//         int textWidth = MeasureText(text.c_str(), 20);  // Measure the width of the text using font size 20
//         int textHeight = 20;  // Set height for the text (this should match your font size)

//         // Calculate position to center the text horizontally and place it below the image vertically
//         int textX = posX + (cellSize / 2) - (textWidth / 2);  // Center text horizontally
//         int textY = posY + (cellSize - imgHeight) / 2 + imgHeight + padding;  // Center text vertically under the image

//         // Draw the text at the calculated position
//         DrawText(text.c_str(), textX, textY, textHeight, WHITE);

//         // Draw a line for debugging the text positioning too (e.g., the center of the text)
//         DrawLine(textX, textY, textX + textWidth, textY, RED);  // Draw a red line across the text for visual reference
//     }
// }

// void Inventory::drawInventory(const Inventory &inventory, int startX, int startY, int cellSize)
// {
//     int itemsPerRow = 5;  // Number of items per row in the inventory
//     int padding = 10;     // Space between items

//     // Iterate over all items in the inventory
//     for (size_t i = 0; i < inventory.items.size(); ++i)
//     {
//         int row = i / itemsPerRow;  // Determine the row
//         int col = i % itemsPerRow;  // Determine the column

//         // Calculate position to draw the item (spacing between items)
//         int posX = startX + col * (cellSize + padding);
//         int posY = startY + row * (cellSize + padding);

//         // Get the texture for the item
//         Texture2D texture = inventory.items[i].getTexture();

//         // Declare imgWidth and imgHeight before the if-block so they are accessible
//         int imgWidth = 0;
//         int imgHeight = 0;

//         // Center the image within the cell
//         if (texture.id != 0) {
//             float scale = (float)cellSize / (float)texture.width;  // Scaling the texture
//             imgWidth = texture.width * scale;
//             imgHeight = texture.height * scale;

//             // Draw the texture (icon), center the image in the cell
//             DrawTextureEx(texture, Vector2{(float)(posX + (cellSize - imgWidth) / 2), (float)posY}, 0.0f, scale, WHITE);
//         }

//         // Draw the item amount (text below the icon)
//         std::string text = std::to_string(inventory.items[i].amount);

//         // Measure the text width based on font size
//         int textWidth = MeasureText(text.c_str(), 20);  // Measure the width of the text using font size 20
//         int textHeight = 20;  // Set height for the text (this should match your font size)

//         // Calculate position to center the text horizontally and place it below the image vertically
//         int textX = posX + (cellSize / 2) - (textWidth / 2);  // Center text horizontally
//         int textY = posY + (cellSize - imgHeight) / 2 + imgHeight + padding;  // Center text vertically under the image

//         // Draw the text at the calculated position
//         DrawText(text.c_str(), textX, textY, textHeight, WHITE);
//     }
// }
