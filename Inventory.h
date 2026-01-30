#ifndef INVENTORY_H
#define INVENTORY_H

#include "raylib.h"
#include <string>  // Include for std::string
#include <cstddef> // Include for size_t
#include "Item.h"
#include <vector>
#include <iostream>

class Inventory
{
public:
    void initializeInventory(); // New method to initialize inventory
    void addItem(const Item &item);
    void onItemClick(int itemIndex);
    void drawInventory(const Inventory &inventory, int startX, int startY, int cellSize);
    std::vector<Item> items; // Inventory holds a list of items
private:
    void loadTextures();
    bool infoPanelVisible = false; // Flag to track if the info panel is visible
    int currentItemIndex = 0;      // Track the currently selected item index
};

#endif
