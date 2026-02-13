#ifndef INVENTORY_H
#define INVENTORY_H

#include "raylib.h"
#include "raymath.h"
#include "Item.h"
#include <string>
#include <vector>
#include <optional>
#include <iostream>

class Inventory
{
public:
    Inventory();                                                        // constructor
    void initializeInventory();                                         // optional initial items
    bool addItem(const Item &item);                                     // add item
    void sellItem(int slotIndex, int amountToSell, int value);          // sell item
    bool removeItem(const std::string &skillType, int id, int amount);  // remove item, used in smithing
    int getItemAmount(const std::string& skillType, int id) const;
    void onItemClick(int slotIndex);                                    // click logic
    void clearInventory();
    float ScrollBar(Rectangle track, float value);
    void drawInvPanel();
    void drawInventory(int startX, int startY, int cellSize);

    void loadTextures(); // slot texture
    void unloadTextures();

    // getSlots, which might be empty. It's optional
    const std::vector<std::optional<Item>> &getSlots() const noexcept { return slots; }
    std::vector<std::optional<Item>> &getSlots() noexcept { return slots; }

    // return the filled slots in the bank i.e current amount in the bank being used.
    int getFilledSlots() const;

    void setGold(int newAmount) { gold = newAmount; }
    int getGold() const { return gold ;}

    static constexpr int WIDTH = 8;             // 8 slots per row
    static constexpr int HEIGHT = 8;            // 8 rows
    static constexpr int SIZE = WIDTH * HEIGHT; // total slots (64)

private:
    bool button(Rectangle bounds, const char *text);

    std::vector<std::optional<Item>> slots; // each slot may contain an item
    Texture2D slotTexture{};                // slot background
    
    bool infoPanelVisible{false};
    int currentSlotIndex{-1}; // currently selected slot
    int gold{500};
};

#endif
