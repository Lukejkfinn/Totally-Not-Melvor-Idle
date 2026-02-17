#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include "Item.h"
#include <vector>

enum class SkillType
{
    Woodcutting,
    Fishing,
    Firemaking,
    Cooking,
    Mining,
    Smithing,
    Thieving,
    Fletching,
    Crafting
};

struct ItemData 
{
    std::string texturePath;
    std::string itemName;
    std::string skillType;
    int id;
    int value;
    int amount;
    int stackAmount;
    bool stackable;
};

class ItemDatabase {

public:
    static std::vector<Item> ItemSpawner(SkillType skill, int spawnAmount);
    static void loadItems();                                                    // function to initialise all the predefined items
    static void unloadItems();                                                  // function to unload
    static Item getItemByName(const std::string &name, const int &id);          // function to get an item by name (for example)
    
    static std::vector<Item> items;                                             // list of all items

private:
    static void addItem(const Item &item);                                      // add all item data here
    static Texture2D LoadItemTexture(const std::string &texturePath);     
    
    const static int logsMaxStack{999'999};
    const static int fishMaxStack{999'999};
    const static int miscMaxStack{999'999};
    const static int foodMaxStack{999'999};
    const static int oresMaxStack{999'999};
    const static int barsMaxStack{999'999};
    const static int craftingMaxStack{999'999};


};

#endif // ITEMDATABASE_H
