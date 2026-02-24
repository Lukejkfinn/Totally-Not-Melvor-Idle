#include "ItemDatabase.h"
#include <iostream>

// define the static items list
std::vector<Item> ItemDatabase::items;

Item ItemDatabase::getItemByID(const std::string &skillType, const int &id)
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

    case SkillType::Fletching:
        skillName = "fletching";
        break;


    case SkillType::Crafting:
        skillName = "crafting";
        break;
    
    case SkillType::Runecrafting:
        skillName = "runecrafting";
        break;

    case SkillType::Herblore:
        skillName = "herblore";
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
    const static int fletchAmount{1};
    const static int craftAmount{1};
    const static int runecraftingAmount{1};
    const static int herbloreAmount{1};

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
        {"assets/bank/cooking/whale_burnt.png", "Burnt Whale", "cooking",           32, 0, foodAmount, foodMaxStack, true}
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
        // texture,                                 name,   skillType,                                 ID, value, amount, maxStack, isStackable
        // bars (IDs 1–9)
        {"assets/bank/smithing/bronze_bar.png", "Bronze Bar", "smithing",                               1, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/iron_bar.png", "Iron Bar", "smithing",                                   2, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/steel_bar.png", "Steel Bar", "smithing",                                 3, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/silver_bar.png", "Silver Bar", "smithing",                               4, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/gold_bar.png", "Gold Bar", "smithing",                                   5, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/mithril_bar.png", "Mithril Bar", "smithing",                             6, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/adamantite_bar.png", "Adamantite Bar", "smithing",                       7, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/runite_bar.png", "Runite Bar", "smithing",                               8, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/dragonite_bar.png", "Dragonite Bar", "smithing",                         9, 2, barAmount, barsMaxStack, true},

        // bronze items (IDs 10–24)
        {"assets/bank/smithing/weapon_dagger_bronze.png", "Bronze Dagger", "smithing",                  10, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_bronze.png", "Bronze Arrowtips", "smithing",                   11, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_bronze.png", "Bronze Throwing Knife", "smithing",   12, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_bronze.png", "Bronze Sword", "smithing",                    13, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_bronze.png", "Bronze Gloves", "smithing",                  14, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_bronze.png", "Bronze Scimitar", "smithing",              15, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_bronze.png", "Bronze Helmet", "smithing",                  16, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_bronze.png", "Bronze Battleaxe", "smithing",            17, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/bronze_javelin_heads.png", "Bronze Javelin Heads", "smithing",           18, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_bronze.png", "Bronze Boots", "smithing",                    19, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_bronze.png", "Bronze Shield", "smithing",                  20, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_bronze.png", "Bronze 2H Sword", "smithing",                    21, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_bronze.png", "Bronze Crossbow Head", "smithing",           22, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_bronze.png", "Bronze Platelegs", "smithing",            23, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_bronze.png", "Bronze Platebody", "smithing",            24, 2, barAmount, barsMaxStack, true},

        // iron items (IDs 25–39)
        {"assets/bank/smithing/weapon_dagger_iron.png", "Iron Dagger", "smithing",                      25, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_iron.png", "Iron Arrowtips", "smithing",                       26, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_iron.png", "Iron Throwing Knife", "smithing",       27, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_iron.png", "Iron Sword", "smithing",                        28, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_iron.png", "Iron Gloves", "smithing",                      29, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_iron.png", "Iron Scimitar", "smithing",                  30, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_iron.png", "Iron Helmet", "smithing",                      31, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_iron.png", "Iron Battleaxe", "smithing",                32, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/iron_javelin_heads.png", "Iron Javelin Heads", "smithing",               33, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_iron.png", "Iron Boots", "smithing",                        34, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_iron.png", "Iron Shield", "smithing",                      35, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_iron.png", "Iron 2H Sword", "smithing",                        36, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_iron.png", "Iron Crossbow Head", "smithing",               37, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_iron.png", "Iron Platelegs", "smithing",                38, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_iron.png", "Iron Platebody", "smithing",                39, 2, barAmount, barsMaxStack, true},

        // steel items (IDs 40–54)
        {"assets/bank/smithing/weapon_dagger_steel.png", "Steel Dagger", "smithing",                    40, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_steel.png", "Steel Arrowtips", "smithing",                     41, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_steel.png", "Steel Throwing Knife", "smithing",     42, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_steel.png", "Steel Sword", "smithing",                      43, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_steel.png", "Steel Gloves", "smithing",                    44, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_steel.png", "Steel Scimitar", "smithing",                45, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_steel.png", "Steel Helmet", "smithing",                    46, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_steel.png", "Steel Battleaxe", "smithing",              47, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/steel_javelin_heads.png", "Steel Javelin Heads", "smithing",             48, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_steel.png", "Steel Boots", "smithing",                      49, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_steel.png", "Steel Shield", "smithing",                    50, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_steel.png", "Steel 2H Sword", "smithing",                      51, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_steel.png", "Steel Crossbow Head", "smithing",             52, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_steel.png", "Steel Platelegs", "smithing",              53, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_steel.png", "Steel Platebody", "smithing",              54, 2, barAmount, barsMaxStack, true},

        // mithril items (IDs 55–69)
        {"assets/bank/smithing/weapon_dagger_mithril.png", "Mithril Dagger", "smithing",                55, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_mithril.png", "Mithril Arrowtips", "smithing",                 56, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_mithril.png", "Mithril Throwing Knife", "smithing", 57, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_mithril.png", "Mithril Sword", "smithing",                  58, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_mithril.png", "Mithril Gloves", "smithing",                59, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_mithril.png", "Mithril Scimitar", "smithing",            60, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_mithril.png", "Mithril Helmet", "smithing",                61, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_mithril.png", "Mithril Battleaxe", "smithing",          62, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/mithril_javelin_heads.png", "Mithril Javelin Heads", "smithing",         63, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_mithril.png", "Mithril Boots", "smithing",                  64, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_mithril.png", "Mithril Shield", "smithing",                65, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_mithril.png", "Mithril 2H Sword", "smithing",                  66, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_mithril.png", "Mithril Crossbow Head", "smithing",         67, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_mithril.png", "Mithril Platelegs", "smithing",          68, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_mithril.png", "Mithril Platebody", "smithing",          69, 2, barAmount, barsMaxStack, true},

        // adamant items (IDs 70–84)
        {"assets/bank/smithing/weapon_dagger_adamant.png", "Adamant Dagger", "smithing",                70, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_adamant.png", "Adamant Arrowtips", "smithing",                 71, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_adamant.png", "Adamant Throwing Knife", "smithing", 72, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_adamant.png", "Adamant Sword", "smithing",                  73, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_adamant.png", "Adamant Gloves", "smithing",                74, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_adamant.png", "Adamant Scimitar", "smithing",            75, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_adamant.png", "Adamant Helmet", "smithing",                76, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_adamant.png", "Adamant Battleaxe", "smithing",          77, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/adamant_javelin_heads.png", "Adamant Javelin Heads", "smithing",         78, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_adamant.png", "Adamant Boots", "smithing",                  79, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_adamant.png", "Adamant Shield", "smithing",                80, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_adamant.png", "Adamant 2H Sword", "smithing",                  81, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_adamant.png", "Adamant Crossbow Head", "smithing",         82, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_adamant.png", "Adamant Platelegs", "smithing",          83, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_adamant.png", "Adamant Platebody", "smithing",          84, 2, barAmount, barsMaxStack, true},

        // rune items (IDs 85–99)
        {"assets/bank/smithing/weapon_dagger_rune.png", "Rune Dagger", "smithing",                      85, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_rune.png", "Rune Arrowtips", "smithing",                       86, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_rune.png", "Rune Throwing Knife", "smithing",       87, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_rune.png", "Rune Sword", "smithing",                        88, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_rune.png", "Rune Gloves", "smithing",                      89, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_rune.png", "Rune Scimitar", "smithing",                  90, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_rune.png", "Rune Helmet", "smithing",                      91, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_rune.png", "Rune Battleaxe", "smithing",                92, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/rune_javelin_heads.png", "Rune Javelin Heads", "smithing",               93, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_rune.png", "Rune Boots", "smithing",                        94, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_rune.png", "Rune Shield", "smithing",                      95, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_rune.png", "Rune 2H Sword", "smithing",                        96, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_rune.png", "Rune Crossbow Head", "smithing",               97, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_rune.png", "Rune Platelegs", "smithing",                98, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_rune.png", "Rune Platebody", "smithing",                99, 2, barAmount, barsMaxStack, true},

        // dragon items (IDs 100–114)
        {"assets/bank/smithing/weapon_dagger_dragon.png", "Dragon Dagger", "smithing",                  100, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/arrowtips_dragon.png", "Dragon Arrowtips", "smithing",                   101, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_throwingknife_dragon.png", "Dragon Throwing Knife", "smithing",   102, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_sword_dragon.png", "Dragon Sword", "smithing",                    103, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_gloves_dragon.png", "Dragon Gloves", "smithing",                  104, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_scimitar_dragon.png", "Dragon Scimitar", "smithing",              105, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_helmet_dragon.png", "Dragon Helmet", "smithing",                  106, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_battleaxe_dragon.png", "Dragon Battleaxe", "smithing",            107, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/dragon_javelin_heads.png", "Dragon Javelin Heads", "smithing",           108, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_boots_dragon.png", "Dragon Boots", "smithing",                    109, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_shield_dragon.png", "Dragon Shield", "smithing",                  110, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/weapon_2h_dragon.png", "Dragon 2H Sword", "smithing",                    111, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/crossbow_head_dragon.png", "Dragon Crossbow Head", "smithing",           112, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platelegs_dragon.png", "Dragon Platelegs", "smithing",            113, 2, barAmount, barsMaxStack, true},
        {"assets/bank/smithing/armour_platebody_dragon.png", "Dragon Platebody", "smithing",            114, 2, barAmount, barsMaxStack, true}
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

    std::vector<ItemData> fletchingItems = 
    {
        // texture,                                     name,           skillType,             ID, value, amount, maxStack, isStackable
        {"assets/bank/fletching/headless_arrows.png", "Arrow Shafts", "fletching",              1, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/arrowshaft.png", "Headless Arrows", "fletching",                2, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_bronze.png", "Bronze Arrows", "fletching",           3, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_iron.png", "Iron Arrows", "fletching",               4, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_steel.png", "Steel Arrows", "fletching",             5, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_mithril.png", "Mithril Arrows", "fletching",         6, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_adamant.png", "Adamantite Arrows", "fletching",   7, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_rune.png", "Runite Arrows", "fletching",           8, 2, fletchAmount, fletchingMaxStack, true},
        {"assets/bank/fletching/ammo_arrow_dragon.png", "Dragon Arrows", "fletching",        9, 2, fletchAmount, fletchingMaxStack, true}
    };

    // loading fletching items
    for (const auto& itemData : fletchingItems) // loop through all items
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

        std::vector<ItemData> herbloreItems = 
    {
        // texture,                                 name,       skillType,                             ID, value, amount,     maxStack,        isStackable
        {"assets/bank/herblore/potion_woodcutting_i.png", "Bird Nest Potion", "herblore",               1, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_firemaking_i.png", "Controlled Heat Potion", "herblore",          2, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_cooking_i.png", "Generous Cook Potion", "herblore",               3, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_smithing_i.png", "Seeing Gold Potion", "herblore",                4, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_fishing_i.png", "Fishermans Potion", "herblore",                  5, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_fletching_i.png", "Skilled Fletching Potion", "herblore",         6, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_thieving_i.png", "Gentle Hands Potion", "herblore",               7, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_astrology_i.png", "Secret Stardust Potion", "herblore",           8, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_crafting_i.png", "Crafting Potion", "herblore",                   9, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_mining_i.png", "Perfect Swing Potion", "herblore",                10, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_summoning_i.png", "Necromancer Potion", "herblore",               11, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_agility_i.png", "Performance Enhancing Potion", "herblore",       12, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_runecrafting_i.png", "Elemental Potion", "herblore",              13, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_herblore_i.png", "Herblore Potion", "herblore",                   14, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_farming_i.png", "Generous Harvest Potion", "herblore",            15, 75, herbloreAmount, herbloreMaxStack, true},

        {"assets/bank/herblore/potion_attack_i.png", "Melee Accuracy Potion", "herblore",               16, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_defence_i.png", "Melee Evasion Potion", "herblore",               17, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_ranged_i.png", "Ranged Assistance Potion", "herblore",            18, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/hinder_potion_i.png", "Hinder Potion", "herblore",                       19, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_magic_i.png", "Magic Assistance Potion", "herblore",              20, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_hitpoints_i.png", "Regeneration Potion", "herblore",              21, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/famished_potion_i.png", "Famished Potion", "herblore",                   22, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_ranged_i.png", "Ranged Strength Potion", "herblore",              23, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_herblore_i.png", "Lucky Herb Potion", "herblore",                 24, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_prayer_i.png", "Divine Potion", "herblore",                       25, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_strength_i.png", "Melee Strength Potion", "herblore",             26, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_magic_i.png", "Magic Damage Potion", "herblore",                  27, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/lethal_toxins_potion_i.png", "Lethal Toxin Potion", "herblore",          28, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_mining_i.png", "Diamond Luck Potion", "herblore",                 29, 75, herbloreAmount, herbloreMaxStack, true},
        {"assets/bank/herblore/potion_damage_reduction_i.png", "Damage Reduction Potion", "herblore",   30, 75, herbloreAmount, herbloreMaxStack, true}
    };

    // loading herblore items
    for (const auto& itemData : herbloreItems) // loop through all items
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