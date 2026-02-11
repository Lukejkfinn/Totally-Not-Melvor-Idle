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

    case SkillType::Fishing:
        skillName = "fishing";
        break;
    
    case SkillType::Firemaking:
        skillName = "firemaking";
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
    const static int fishAmount{1};
    const static int rockAmount{1};
    const static int barAmount{1};

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

    std::vector<ItemData> fishingItems = 
    {
        // texture, name, skillType, ID, value, amount, maxStack, isStackable
        {"assets/bank/fishing/shrimp.png", "Raw Shrimp", "fishing", 1, 1, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/sardine.png", "Raw Sardine", "fishing", 2, 5, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/herring.png", "Raw Herring", "fishing", 3, 10, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/seahorse.png", "Raw Seahorse", "fishing", 4, 20, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/trout.png", "Raw Trout", "fishing", 5, 35, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/salmon.png", "Raw Salmon", "fishing", 6, 50, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/lobster.png", "Raw Lobster", "fishing", 7, 75, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/swordfish.png", "Raw Swordfish", "fishing", 8, 400, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/anglerfish.png", "Raw Anglerfish", "fishing", 9, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/fanfish.png", "Raw Fanfish", "fishing", 10, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/crab.png", "Raw Crab", "fishing", 11, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/carp.png", "Raw Carp", "fishing", 12, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/shark.png", "Raw Shark", "fishing", 13, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/cavefish.png", "Raw Cave Fish", "fishing", 14, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/mantaray.png", "Raw Manta Ray", "fishing", 15, 25, fishAmount, fishMaxStack, true},
        {"assets/bank/fishing/whale.png", "Raw Whale", "fishing", 16, 25, fishAmount, fishMaxStack, true}
    };

    // loading fishing items
    for (const auto& itemData : fishingItems) // loop through all items
    {
        Texture2D texture = LoadTexture(itemData.texturePath.c_str());
        if (texture.id == 0) 
            std::cerr << "Failed to load texture for " << itemData.itemName << std::endl;
        else 
            items.push_back(Item(texture, itemData.amount, itemData.stackable, itemData.stackAmount, 
                            itemData.itemName, itemData.skillType, itemData.id, itemData.value));
    }

    std::vector<ItemData> firemakingItems =
    {
        // texture,                           name,   skillType, ID, value, amount, maxStack, isStackable
        {"assets/bank/firemaking/ashes.png", "Ashes", "firemaking", 1, 2, rockAmount, oresMaxStack, true},
    };

    // loading firemaking items
    for (const auto& itemData : firemakingItems) // loop through all items
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
        {"assets/bank/smithing/bronze_bar.png", "Bronze Bar", "smithing", 1, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/iron_bar.png", "Iron Bar", "smithing", 2, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/steel_bar.png", "Steel Bar", "smithing", 3, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/silver_bar.png", "Silver Bar", "smithing", 4, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/gold_bar.png", "Gold Bar", "smithing", 5, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/mithril_bar.png", "Mithril Bar", "smithing", 6, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/adamantite_bar.png", "Adamantite Bar", "smithing", 7, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/runite_bar.png", "Runite Bar", "smithing", 8, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/dragonite_bar.png", "Dragonite Bar", "smithing", 9, 2, barAmount, barsMaxStack, true}

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