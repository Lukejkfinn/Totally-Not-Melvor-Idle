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
    static void loadItems();                                                    // function to initialise all the predefined items
    static Item getItemByName(const std::string &name, const int &id);          // function to get an item by name (for example)
    static std::vector<Item> items;                                             // list of all items

private:
    static void addItem(const Item &item);                                      // add all item data here
    const static int logsMaxStack{999'999};
    const static int oresMaxStack{999'999};
    
};

#endif // ITEMDATABASE_H
