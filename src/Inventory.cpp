#include "Inventory.h"

Inventory::Inventory()
{
    slots.resize(SIZE); // 64 empty slots
}

void Inventory::loadTextures()
{
    // bank slots texture
    slotTexture = LoadTexture("assets/ui/bankBorder.png");
    if (slotTexture.id == 0)
        std::cerr << "Failed to load bankBorder.png\n";
}

void Inventory::unloadTextures()
{
    if (slotTexture.id != 0)
        UnloadTexture(slotTexture);
}

void Inventory::initializeInventory()
{
    // used for spawning items in at the start
    // Item item = ItemDatabase::getItemByName("woodcutting", 1);
    // addItem(item);
}

bool Inventory::button(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // button color states
    Color bgColor = hovered ? DARKBLUE : DARKGRAY;

    // draw button
    DrawRectangleRec(bounds, bgColor);

    // centre text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        WHITE);

    // return true only when clicked
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

int Inventory::getFilledSlots() const
{
    int count = 0;
    for (auto &slot : slots)
        if (slot)
            count++;
    return count;
}

bool Inventory::addItem(const Item &item)
{
    // try stacking first
    if (item.isStackable())
    {
        for (auto &slot : slots)
        {
            if (slot && slot->getSkillType() == item.getSkillType() && slot->getId() == item.getId() &&  slot->isStackable())
            {
                int newAmount = slot->getAmount() + item.getAmount();
                newAmount = std::min(newAmount, slot->getMaxStack());
                slot->setAmount(newAmount);
                return true;
            }
        }
    }

    // find first empty slot
    for (auto &slot : slots)
    {
        if (!slot)
        {
            slot = std::make_optional<Item>(item);
            return true;
        }
    }

    // inventory is full
    std::cerr << "Inventory is full! Cannot add item: " << item.getName() << "\n";
    return false;
}

void Inventory::sellItem(int slotIndex, int amountToSell, int value)
{
    if (slotIndex < 0 || slotIndex >= SIZE || !slots[slotIndex])
        return;  // nothing to remove if the slot is invalid

    Item &item = *slots[slotIndex];
    int amountInSlot = item.getAmount();  // get the current amount of the item

    if (amountInSlot <= 0 || amountToSell <= 0)
        return;  // no item to sell or invalid amount

    // ensure we are selling an amount that doesn't exceed the available items
    amountToSell = std::min(amountToSell, amountInSlot);  

    std::cout << "Selling " << amountToSell << " " << item.getName() << "(s)\n";

    item.setAmount(amountInSlot - amountToSell);  // reduce the amount in the inventory

    // if the item amount is zero, remove the item from the slot
    if (item.getAmount() == 0)
    {
        slots[slotIndex].reset();  // reset slot if no items left

        // shift all subsequent items to the left
        for (int i = slotIndex; i < SIZE - 1; ++i)
        {
            // if the next slot contains an item, move it to the current position
            if (slots[i + 1])
            {
                slots[i] = std::move(slots[i + 1]);  // move the item to the left
                slots[i + 1].reset();  // clear the original slot
            }
        }
    }
    gold += amountToSell * value;
}

void Inventory::onItemClick(int slotIndex)
{
    if (!slots[slotIndex])
        return;

    infoPanelVisible = true;
    currentSlotIndex = slotIndex;

    std::cout << "Clicked slot " << slotIndex << " containing item: " << (*slots[slotIndex]).getName() << "\n";
}

void Inventory::clearInventory()
{
    for (auto &slot : slots)
    {
        slot.reset();  // removes the item but keeps the slot
    }
}

float Inventory::ScrollBar(Rectangle track, float value)
{
    const float thumbWidth = 25.0f;  // thumb width for horizontal scrollbar
    //const float maxValue = 64.0f;    // max value of items in stack (could be adjusted based on item properties)
    
    // clamp value to between 0.0 and 1.0
    value = Clamp(value, 0.0f, 1.0f);
    
    // calculate thumb X position based on the scroll value
    float thumbX = track.x + value * (track.width - thumbWidth);
    Rectangle thumb = {thumbX, track.y, thumbWidth, track.height};  // horizontal thumb
    
    Vector2 mouse = GetMousePosition();
    static bool dragging = false;

    // if the mouse is on the thumb, allow dragging
    if (CheckCollisionPointRec(mouse, thumb) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dragging = true;
    }

    // if dragging, update the thumb position
    if (dragging)
    {
        float newX = mouse.x - thumbWidth / 2;
        newX = Clamp(newX, track.x, track.x + track.width - thumbWidth);

        value = (newX - track.x) / (track.width - thumbWidth);  // update scroll value (0.0 to 1.0)
    }

    // release dragging
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        dragging = false;
    }

    // draw the scrollbar (track and thumb)
    DrawRectangleRounded(track, 1.f, 50, LIGHTGRAY);  // draw track
    DrawRectangleRounded(thumb, 1.f, 50, DARKBLUE);   // draw thumb

    return value;  // return the updated scroll value (0.0 to 1.0)
}

void Inventory::drawInvPanel()
{
    const float panelX{940.f};
    const float panelY{100.f};
    const float panelW{300.f};
    const float panelH{300.f};
    const float buttonW{75.f};
    const float buttonH{50.f};
    
    Item &item = *slots[currentSlotIndex];

    // scrollbar for adjusting item quantity (1 -> max stack size based on selected item)
    static float scrollValue = 0.0f;  // initialize scroll value
    const int maxItemAmount = item.getAmount();  // Get the amount of the current item in the slot
    
    // clamp the scrollbar value between 1 and maxItemAmount
    int itemAmount = static_cast<int>(scrollValue * maxItemAmount);  // scale the value to match item range
    itemAmount = std::max(1, itemAmount);  // ensure we have at least 1 item selected
    
    DrawRectangle(panelX, panelY, panelW, panelH, GRAY);                                                                // draw panel background
    DrawText(item.getName().c_str(), panelX + 10, panelY + 10, 20, WHITE);                                              // item name
    DrawText(("Skill: " + item.getSkillType()).c_str(), panelX + 10, panelY + 50, 20, WHITE);                           // item skillType
    DrawText(("ID: " + std::to_string(item.getId())).c_str(), panelX + 10, panelY + 90, 20, WHITE);                     // item ID
    DrawText(("Value: " + std::to_string(item.getValue() * itemAmount)).c_str(), panelX + 10, panelY + 130, 20, WHITE); // item value
    std::string amountText = "Sell Item: " + std::to_string(itemAmount);                                                // item sell price
    DrawText(amountText.c_str(), panelX + 10, panelY + panelH - 120, 20, WHITE);                                        // draw the sell price text
    scrollValue = ScrollBar({panelX+5, panelY + panelH - 90, panelW-10, 20}, scrollValue);                              // draw horizontal scrollbar

    // "Sell" button
    if (button(Rectangle{panelX + buttonW + 30, panelY + panelH - 50, buttonW + 10, buttonH}, "Sell"))
    {
        // pass the selected amount from the scrollbar to sellItem
        sellItem(currentSlotIndex, itemAmount, item.getValue());  // perform the selling action based on the current slot index and the selected amount
    }
}

void Inventory::drawInventory(int startX, int startY, int cellSize)
{
    Vector2 mouse = GetMousePosition();
    const int hPadding = 10;       // horizontal padding
    const int vPadding = 20;       // vertical padding (increased)
    const int textureInset = 5;    // texture inset inside slot

    for (int i = 0; i < SIZE; i++)
    {
        int row = i / WIDTH;
        int col = i % WIDTH;

        int x = startX + col * (cellSize + hPadding);
        int y = startY + row * (cellSize + vPadding);

        // draw slot background
        DrawTextureEx(slotTexture,
            Vector2{ (float)x, (float)y },
            0.0f,
            (float)cellSize / slotTexture.width,
            WHITE);

        // draw item in slot if exists
        if (slots[i])
        {
            Item &item = *slots[i];
            Texture2D tex = item.getTexture();

            // draw item slightly smaller than the slot
            float scaleX = (float)(cellSize - 2 * textureInset) / tex.width;
            float scaleY = (float)(cellSize - 2 * textureInset) / tex.height;
            DrawTextureEx(tex,
                Vector2{ (float)x + textureInset, (float)y + textureInset },
                0.0f,
                std::min(scaleX, scaleY),
                WHITE);

            // draw item amount under the cell, centered horizontally
            if (item.isStackable())
            {
                std::string amountText = std::to_string(item.getAmount());
                int textWidth = MeasureText(amountText.c_str(), 14);
                DrawText(amountText.c_str(),
                         x + (cellSize - textWidth) / 2,
                         y + cellSize + 2, // 2 pixels below the slot
                         14,
                         WHITE);
            }

            // detect click
            Rectangle slotRect{ (float)x, (float)y, (float)cellSize, (float)cellSize };
            if (CheckCollisionPointRec(mouse, slotRect) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                onItemClick(i);
            }
        }
    }

    // draw info panel if visible
    if (infoPanelVisible && currentSlotIndex >= 0 && slots[currentSlotIndex])
        drawInvPanel();
}
