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

    case SkillType::Cooking:
        skillName = "cooking";
        break;

    case SkillType::Mining:
        skillName = "mining";
        break;

    case SkillType::Smithing:
        skillName = "smithing";
        break;

    case SkillType::Crafting:
        skillName = "crafting";
        break;
    
    case SkillType::Runecrafting:
        skillName = "runecrafting";
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
    const static int miscAmount{1};
    const static int foodAmount{1};
    const static int rockAmount{1};
    const static int barAmount{1};
    const static int craftAmount{1};
    const static int runecraftingAmount{1};

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
        {"assets/bank/firemaking/ashes.png", "Ashes", "firemaking", 1, 2, miscAmount, miscMaxStack, true},
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

    std::vector<ItemData> cookingItems =
    {
        // texture,                           name,   skillType,                    ID, value, amount, maxStack, isStackable
        {"assets/bank/cooking/shrimp_cooked.png", "Shrimp", "cooking",              1, 2, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/sardine_cooked.png", "Sardine", "cooking",            2, 5, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/herring_cooked.png", "Herring", "cooking",            3, 10, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/seahorse_cooked.png", "Seahorse", "cooking",          4, 65, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/trout_cooked.png", "Trout", "cooking",                5, 27, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/salmon_cooked.png", "Salmon", "cooking",              6, 58, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/lobster_cooked.png", "Lobster", "cooking",            7, 108, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/swordfish_cooked.png", "Swordfish", "cooking",        8, 134, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/anglerfish_cooked.png", "Anglerfish", "cooking",      9, 209, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/fanfish_cooked.png", "Fanfish", "cooking",            10, 250, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/crab_cooked.png", "Crab", "cooking",                  11, 280, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/carp_cooked.png", "Carp", "cooking",                  12, 395, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/shark_cooked.png", "Shark", "cooking",                13, 674, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/cavefish_cooked.png", "Cave Fish", "cooking",         14, 538, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/mantaray_cooked.png", "Manta Ray", "cooking",         15, 1624, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/whale_cooked.png", "Whale", "cooking",                16, 2048, foodAmount, foodMaxStack, true},

        {"assets/bank/cooking/shrimp_burnt.png", "Burnt Shrimp", "cooking",         17, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/sardine_burnt.png", "Burnt Sardine", "cooking",       18, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/herring_burnt.png", "Burnt Herring", "cooking",       19, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/seahorse_burnt.png", "Burnt Seahorse", "cooking",     20, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/trout_burnt.png", "Burnt Trout", "cooking",           21, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/salmon_burnt.png", "Burnt Salmon", "cooking",         22, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/lobster_burnt.png", "Burnt Lobster", "cooking",       23, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/swordfish_burnt.png", "Burnt Swordfish", "cooking",   24, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/anglerfish_burnt.png", "Burnt Anglerfish", "cooking", 25, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/fanfish_burnt.png", "Burnt Fanfish", "cooking",       26, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/crab_burnt.png", "Burnt Crab", "cooking",             27, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/carp_burnt.png", "Burnt Carp", "cooking",             28, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/shark_burnt.png", "Burnt Shark", "cooking",           29, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/cavefish_burnt.png", "Burnt Cave Fish", "cooking",    30, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/mantaray_burnt.png", "Burnt Manta Ray", "cooking",    31, 0, foodAmount, foodMaxStack, true},
        {"assets/bank/cooking/whale_burnt.png", "Burnt Whale", "cooking",           32, 0, foodAmount, foodMaxStack, true},
    };

    // loading cooking items
    for (const auto& itemData : cookingItems) // loop through all items
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
        {"assets/bank/mining/rune_essence.png", "Rune Essence", "mining", 1, 2, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_copper.png", "Copper Ore", "mining", 2, 2, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_tin.png", "Tin Ore", "mining", 3, 2, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_iron.png", "Iron Ore", "mining", 4, 5, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_coal.png", "Coal Ore", "mining", 5, 15, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_silver.png", "Silver Ore", "mining", 6, 25, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_gold.png", "Gold Ore", "mining", 7, 30, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_mithril.png", "Mithril Ore", "mining", 8, 65, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_adamantite.png", "Adamantite Ore", "mining", 9, 88, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_runite.png", "Runite Ore", "mining", 10, 100, rockAmount, oresMaxStack, true},
        {"assets/bank/mining/ore_dragonite.png", "Dragonite Ore", "mining", 11, 135, rockAmount, oresMaxStack, true}
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

    std::vector<ItemData> craftingItems = 
    {
        // texture, name, skillType, ID, value, amount, maxStack, isStackable
        {"assets/bank/crafting/armour_leather_gloves.png", "Leather Gloves", "crafting", 1, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_leather_boots.png", "Leather Boots", "crafting", 2, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_leather_cowl.png", "Leather Cowl", "crafting", 3, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_leather_vambraces.png", "Leather Vambraces", "crafting", 4, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_leather_body.png", "Leather Body", "crafting", 5, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_leather_chaps.png", "Leather Chaps", "crafting", 6, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_hard_leather_gloves.png", "Hard Leather Gloves", "crafting", 7, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_hard_leather_boots.png", "Hard Leather Boots", "crafting", 8, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_hard_leather_cowl.png", "Hard Leather Cowl", "crafting", 9, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_hard_leather_vambraces.png", "Hard Leather Vambraces", "crafting", 10, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_hard_leather_body.png", "Hard Leather Body", "crafting", 11, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/armour_hard_leather_chaps.png", "Hard Leather Chaps", "crafting", 12, 75, craftAmount, craftingMaxStack, true},
        {"assets/bank/crafting/leather.png", "Leather", "crafting", 13, 50, craftAmount, craftingMaxStack, true}
    };

    // loading crafting items
    for (const auto& itemData : craftingItems) // loop through all items
    {
        Texture2D texture = LoadTexture(itemData.texturePath.c_str());
        if (texture.id == 0)
            std::cerr << "Failed to load texture for " << itemData.itemName << std::endl;
        else
            items.push_back(Item(texture, itemData.amount, itemData.stackable, itemData.stackAmount, 
                                 itemData.itemName, itemData.skillType, itemData.id, itemData.value));
    }

    std::vector<ItemData> runecraftingItems = 
    {
        // texture,                                 name,       skillType,              ID, value, amount,      maxStack, isStackable
        {"assets/bank/runecrafting/rune_air.png", "Rune Air", "runecrafting",           1, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_mind.png", "Rune mind", "runecrafting",         2, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_water.png", "Rune Water", "runecrafting",       3, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_earth.png", "Rune Earth", "runecrafting",       4, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_mist.png", "Rune Mist", "runecrafting",         5, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_fire.png", "Rune Fire", "runecrafting",         6, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_light.png", "Rune Light", "runecrafting",       7, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_body.png", "Rune Body", "runecrafting",         8, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_dust.png", "Rune Dust", "runecrafting",         9, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_mud.png", "Rune Mud", "runecrafting",           10, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_chaos.png", "Rune Chaos", "runecrafting",       11, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_nature.png", "Rune Nature", "runecrafting",     12, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_smoke.png", "Rune Smoke", "runecrafting",       13, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_havoc.png", "Rune Havoc", "runecrafting",       14, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_steam.png", "Rune Steam", "runecrafting",       15, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_lava.png", "Rune Lava", "runecrafting",         16, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_death.png", "Rune Death", "runecrafting",       17, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_blood.png", "Rune Blood", "runecrafting",       18, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_spirit.png", "Rune Spirit", "runecrafting",     19, 75, runecraftingAmount, runecraftingMaxStack, true},
        {"assets/bank/runecrafting/rune_ancient.png", "Rune Ancient", "runecrafting",   20, 75, runecraftingAmount, runecraftingMaxStack, true}
    };

    // loading runecrafting items
    for (const auto& itemData : runecraftingItems) // loop through all items
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