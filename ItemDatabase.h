#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include "Item.h"
#include <vector>

enum class SkillType
{
    Woodcutting,
    Mining
};

class ItemDatabase {

public:
    static std::vector<Item> ItemSpawner(SkillType skill, int spawnAmount);
    static void loadItems(); // Function to initialize all the predefined items
    static Item getItemByName(const std::string &name, const int &id); // Function to get an item by name (for example)
    static std::vector<Item> items; // List of all items

private:
    static void addItem(const Item &item); // Add all item data here
    const static int logsMaxStack{999'999};
    const static int oresMaxStack{999'999};
    
};

#endif // ITEMDATABASE_H
