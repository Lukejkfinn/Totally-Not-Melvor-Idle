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

void ItemDatabase::loadItems()
{
    const static int logAmount{1};
    const static int rockAmount{1};
    
    //* WOODCUTTING *//
    //* WOODCUTTING *//
    //* WOODCUTTING *//

    // Normal log
    Texture2D normalLogTexture = LoadTexture("assets/bank/woodcutting/logs_normal.png");
    if (normalLogTexture.id == 0) std::cerr << "Failed to load normal log texture!" << std::endl;
    items.push_back(Item(normalLogTexture, logAmount, true, logsMaxStack, "Normal Logs", "woodcutting", 1));

    // Oak log
    Texture2D oakLogTexture = LoadTexture("assets/bank/woodcutting/logs_oak.png");
    if (oakLogTexture.id == 0) std::cerr << "Failed to load oak log texture!" << std::endl;
    items.push_back(Item(oakLogTexture, logAmount, true, logsMaxStack, "Oak Logs", "woodcutting", 2));

    // Willow log
    Texture2D willowLogTexture = LoadTexture("assets/bank/woodcutting/logs_willow.png");
    if (willowLogTexture.id == 0) std::cerr << "Failed to load willow log texture!" << std::endl;
    items.push_back(Item(willowLogTexture, logAmount, true, logsMaxStack, "Willow Logs", "woodcutting", 3));

    // Teak log
    Texture2D teakLogTexture = LoadTexture("assets/bank/woodcutting/logs_teak.png");
    if (teakLogTexture.id == 0) std::cerr << "Failed to load teak log texture!" << std::endl;
    items.push_back(Item(teakLogTexture, logAmount, true, logsMaxStack, "Teak Logs", "woodcutting", 4));

    // Maple log
    Texture2D mapleLogTexture = LoadTexture("assets/bank/woodcutting/logs_maple.png");
    if (mapleLogTexture.id == 0) std::cerr << "Failed to load maple log texture!" << std::endl;
    items.push_back(Item(mapleLogTexture, logAmount, true, logsMaxStack, "Maple Logs", "woodcutting", 5));

    // Mahogany log
    Texture2D mahoganyLogTexture = LoadTexture("assets/bank/woodcutting/logs_mahogany.png");
    if (mahoganyLogTexture.id == 0) std::cerr << "Failed to load mahogany log texture!" << std::endl;
    items.push_back(Item(mahoganyLogTexture, logAmount, true, logsMaxStack, "Mahogany Logs", "woodcutting", 6));

    // Yew log
    Texture2D yewLogTexture = LoadTexture("assets/bank/woodcutting/logs_yew.png");
    if (yewLogTexture.id == 0) std::cerr << "Failed to load yew log texture!" << std::endl;
    items.push_back(Item(yewLogTexture, logAmount, true, logsMaxStack, "Yew Logs", "woodcutting", 7));

    // Magic log
    Texture2D magicLogTexture = LoadTexture("assets/bank/woodcutting/logs_magic.png");
    if (magicLogTexture.id == 0) std::cerr << "Failed to load magic log texture!" << std::endl;
    items.push_back(Item(magicLogTexture, logAmount, true, logsMaxStack, "Magic Logs", "woodcutting", 8));

    // Redwood log
    Texture2D redwoodLogTexture = LoadTexture("assets/bank/woodcutting/logs_redwood.png");
    if (redwoodLogTexture.id == 0) std::cerr << "Failed to load redwood log texture!" << std::endl;
    items.push_back(Item(redwoodLogTexture, logAmount, true, logsMaxStack, "Redwood Logs", "woodcutting", 9));


    //* MINING *//
    //* MINING *//
    //* MINING *//

    // Copper ore
    Texture2D copperOreTexture = LoadTexture("assets/bank/mining/ore_copper.png");
    if (copperOreTexture.id == 0) std::cerr << "Failed to load copper ore texture!" << std::endl;
    items.push_back(Item(copperOreTexture, rockAmount, true, oresMaxStack, "Copper Ore", "mining", 1));

    // Tin ore
    Texture2D tinOreTexture = LoadTexture("assets/bank/mining/ore_tin.png");
    if (tinOreTexture.id == 0) std::cerr << "Failed to load tin ore texture!" << std::endl;
    items.push_back(Item(tinOreTexture, rockAmount, true, oresMaxStack, "Tin Ore", "mining", 2));

    // Iron ore
    Texture2D ironOreTexture = LoadTexture("assets/bank/mining/ore_iron.png");
    if (ironOreTexture.id == 0) std::cerr << "Failed to load iron ore texture!" << std::endl;
    items.push_back(Item(ironOreTexture, rockAmount, true, oresMaxStack, "Iron Ore", "mining", 3));

    // Coal ore
    Texture2D coalOreTexture = LoadTexture("assets/bank/mining/ore_coal.png");
    if (coalOreTexture.id == 0) std::cerr << "Failed to load coal ore texture!" << std::endl;
    items.push_back(Item(coalOreTexture, rockAmount, true, oresMaxStack, "Coal Ore", "mining", 4));

    // Silver ore
    Texture2D silverOreTexture = LoadTexture("assets/bank/mining/ore_silver.png");
    if (silverOreTexture.id == 0) std::cerr << "Failed to load silver ore texture!" << std::endl;
    items.push_back(Item(silverOreTexture, rockAmount, true, oresMaxStack, "Silver Ore", "mining", 5));

    // Gold ore
    Texture2D goldOreTexture = LoadTexture("assets/bank/mining/ore_gold.png");
    if (goldOreTexture.id == 0) std::cerr << "Failed to load gold ore texture!" << std::endl;
    items.push_back(Item(goldOreTexture, rockAmount, true, oresMaxStack, "Gold ore", "mining", 6));

    // Mithril ore
    Texture2D mithrilOreTexture = LoadTexture("assets/bank/mining/ore_mithril.png");
    if (mithrilOreTexture.id == 0) std::cerr << "Failed to load mithril ore texture!" << std::endl;
    items.push_back(Item(mithrilOreTexture, rockAmount, true, oresMaxStack, "Mithril Ore", "mining", 7));

    // Adamantite ore
    Texture2D adamantiteOreTexture = LoadTexture("assets/bank/mining/ore_adamantite.png");
    if (adamantiteOreTexture.id == 0) std::cerr << "Failed to load adamantite ore texture!" << std::endl;
    items.push_back(Item(adamantiteOreTexture, rockAmount, true, oresMaxStack, "Adamantite Ore", "mining", 8));

    // Runite ore
    Texture2D runiteOreTexture = LoadTexture("assets/bank/mining/ore_runite.png");
    if (runiteOreTexture.id == 0) std::cerr << "Failed to load runite ore texture!" << std::endl;
    items.push_back(Item(runiteOreTexture, rockAmount, true, oresMaxStack, "Runite Ore", "mining", 9));

    // Dragonite ore
    Texture2D dragoniteOreTexture = LoadTexture("assets/bank/mining/ore_dragonite.png");
    if (dragoniteOreTexture.id == 0) std::cerr << "Failed to load dragonite ore texture!" << std::endl;
    items.push_back(Item(dragoniteOreTexture, rockAmount, true, oresMaxStack, "Dragonite Ore", "mining", 10));
}

void ItemDatabase::addItem(const Item &item)
{
    items.push_back(item);
}