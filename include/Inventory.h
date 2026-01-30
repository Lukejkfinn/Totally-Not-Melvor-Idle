#ifndef INVENTORY_H
#define INVENTORY_H

#include "raylib.h"
#include <string> 
#include <cstddef> 
#include "Item.h"
#include <vector>
#include <iostream>

class Inventory
{
public:
    void initializeInventory(); // new method to initialize inventory
    void addItem(const Item &item);
    void onItemClick(int itemIndex);
    void drawInventory(const Inventory &inventory, int startX, int startY, int cellSize);
    std::vector<Item> items; // inventory holds a list of items

private:
    void loadTextures();
    bool infoPanelVisible = false; // flag to track if the info panel is visible
    int currentItemIndex = 0;      // track the currently selected item index
};

#endif
