#include "ItemDatabase.h"
#include <iostream>

// define the static items list
std::vector<Item> ItemDatabase::items;

Item ItemDatabase::getItemByName(const std::string &skillType, const int &id)
{
    for (const auto &item : items)
    {
        if (item.getSkillType() == skillType && item.getId() == id)
        {
            return item;
        }
    }
    // return a default item if not found (or handle it differently)
    return Item();
}

std::vector<Item> ItemDatabase::ItemSpawner(SkillType skill, int spawnAmount)
{
    std::vector<Item> spawned;

    std::string skillName;

    switch (skill)
    {
    case SkillType::Woodcutting:
        skillName = "woodcutting";
        break;

    case SkillType::Mining:
        skillName = "mining";
        break;

    case SkillType::Smithing:
        skillName = "smithing";
        break;

    default:
        std::cerr << "Unknown skill in ItemSpawner!\n";
        return spawned;
    }

    for (auto item : items)
    {
        if (item.getSkillType() == skillName)
        {
            item.setAmount(spawnAmount);
            spawned.push_back(item);
        }
    }
    return spawned;
}

Texture2D ItemDatabase::LoadItemTexture(const std::string &texturePath) {
    Texture2D texture = LoadTexture(texturePath.c_str());
    if (texture.id == 0) 
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
    return texture;
}

void ItemDatabase::loadItems()
{
    const static int logAmount{1};
    const static int rockAmount{1};

    std::vector<ItemData> woodcuttingItems = 
    {
        // texture, name, skillType, ID, value, amount, maxStack, isStackable
        {"assets/bank/woodcutting/logs_normal.png", "Normal Logs", "woodcutting", 1, 1, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_oak.png", "Oak Logs", "woodcutting", 2, 5, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_willow.png", "Willow Logs", "woodcutting", 3, 10, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_teak.png", "Teak Logs", "woodcutting", 4, 20, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_maple.png", "Maple Logs", "woodcutting", 5, 35, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_mahogany.png", "Mahogany Logs", "woodcutting", 6, 50, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_yew.png", "Yew Logs", "woodcutting", 7, 75, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_magic.png", "Magic Logs", "woodcutting", 8, 400, logAmount, logsMaxStack, true},
        {"assets/bank/woodcutting/logs_redwood.png", "Redwood Logs", "woodcutting", 9, 25, logAmount, logsMaxStack, true}
    };

    // loading woodcutting items
    for (const auto& itemData : woodcuttingItems) // loop through all items
    {
        Texture2D texture = LoadTexture(itemData.texturePath.c_str());
        if (texture.id == 0) 
            std::cerr << "Failed to load texture for " << itemData.itemName << std::endl;
        else 
            items.push_back(Item(texture, itemData.amount, itemData.stackable, itemData.stackAmount, 
                            itemData.itemName, itemData.skillType, itemData.id, itemData.value));
    }

    std::vector<ItemData> miningItems = 
    {
        // texture, name, skillType, ID, value, amount, maxStack, isStackable
        {"assets/bank/mining/ore_copper.png", "Copper Ore", "mining", 1, 2, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_tin.png", "Tin Ore", "mining", 2, 2, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_iron.png", "Iron Ore", "mining", 3, 5, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_coal.png", "Coal Ore", "mining", 4, 15, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_silver.png", "Silver Ore", "mining", 5, 25, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_gold.png", "Gold Ore", "mining", 6, 30, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_mithril.png", "Mithril Ore", "mining", 7, 65, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_adamantite.png", "Adamantite Ore", "mining", 8, 88, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_runite.png", "Runite Ore", "mining", 9, 100, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_dragonite.png", "Dragonite Ore", "mining", 10, 135, rockAmount, oresMaxStack, true}
    };

    // loading mining items
    for (const auto& itemData : miningItems) // loop through all items
    {
        Texture2D texture = LoadTexture(itemData.texturePath.c_str());
        if (texture.id == 0)
            std::cerr << "Failed to load texture for " << itemData.itemName << std::endl;
        else
            items.push_back(Item(texture, itemData.amount, itemData.stackable, itemData.stackAmount, 
                                 itemData.itemName, itemData.skillType, itemData.id, itemData.value));
    }

    std::vector<ItemData> smithingItems = 
    {
        // texture, name, skillType, ID, value, amount, maxStack, isStackable
        {"assets/bank/smithing/bronze_bar.png", "Bronze Bar", "smithing", 1, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/iron_bar.png", "Iron Bar", "smithing", 2, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/steel_bar.png", "Steel Bar", "smithing", 3, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/silver_bar.png", "Silver Bar", "smithing", 4, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/gold_bar.png", "Gold Bar", "smithing", 5, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/mithril_bar.png", "Mithril Bar", "smithing", 6, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/adamantite_bar.png", "Adamantite Bar", "smithing", 7, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/runite_bar.png", "Runite Bar", "smithing", 8, 2, 1, barsMaxStack, true},
        {"assets/bank/smithing/dragonite_bar.png", "Dragonite Bar", "smithing", 9, 2, 1, barsMaxStack, true}

    };

    // loading smithing items
    for (const auto& itemData : smithingItems) // loop through all items
    {
        Texture2D texture = LoadTexture(itemData.texturePath.c_str());
        if (texture.id == 0)
            std::cerr << "Failed to load texture for " << itemData.itemName << std::endl;
        else
            items.push_back(Item(texture, itemData.amount, itemData.stackable, itemData.stackAmount, 
                                 itemData.itemName, itemData.skillType, itemData.id, itemData.value));
    }
}

void ItemDatabase::unloadItems()
{
    for (Item &item : items)
    {
        Texture2D tex = item.getTexture();
        if (tex.id != 0)
            UnloadTexture(tex);
    }

    items.clear();
}

void ItemDatabase::addItem(const Item &item)
{
    items.push_back(item);
}