#include "raylib.h"
#include "raymath.h"
#include "ItemDatabase.h"
#include "Item.h"
#include "Inventory.h"
#include "BaseSkill.h"
#include "Woodcutting.h"
#include "Fishing.h"
#include "Firemaking.h"
#include "Cooking.h"
#include "Mining.h"
#include "Smithing.h"
#include "Thieving.h"
#include "Fletching.h"
#include "Crafting.h"
#include "Runecrafting.h"
#include "Herblore.h"
#include "Agility.h"
#include "Summoning.h"
#include "Astrology.h"
#include "debugger.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

static const float contentY{};

// forward declarations
void saveGame(const Inventory &inventory, const Woodcutting &wood, const Fishing &fishing, const Firemaking &firemaking, const Cooking &cooking, const Mining &mining, const Smithing &smithing, const Crafting &crafting, const Runecrafting &runecrafting, const std::string &filename);
void loadGame(const Inventory &inventory, const Woodcutting &wood, const Fishing &fishing, const Firemaking &firemaking, const Cooking &cooking, const Mining &mining, const Smithing &smithing, const Crafting &crafting, const Runecrafting &runecrafting, const std::string &filename);

bool Button(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // button color states
    Color bgColor = hovered ? DARKBLUE : GRAY;

    // draw button
    DrawRectangleRec(bounds, bgColor);

    // center text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        WHITE);

    // return true only when clicked
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

float ScrollBar(Rectangle track, float value)
{
    const float thumbHeight = 40.0f;

    // clamp value
    value = Clamp(value, 0.0f, 1.0f);

    // calculate thumb position
    float thumbY = track.y + value * (track.height - thumbHeight);
    Rectangle thumb = {track.x, thumbY, track.width, thumbHeight};

    Vector2 mouse = GetMousePosition();

    static bool dragging = false;

    // mouse press on thumb
    if (CheckCollisionPointRec(mouse, thumb) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dragging = true;
    }

    // release drag
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        dragging = false;
    }

    // drag logic
    if (dragging)
    {
        float newY = mouse.y - thumbHeight / 2;
        newY = Clamp(newY, track.y, track.y + track.height - thumbHeight);

        value = (newY - track.y) / (track.height - thumbHeight);
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        value -= wheel * 0.05f;
    }

    // draw
    DrawRectangleRec(track, LIGHTGRAY);
    DrawRectangleRec(thumb, DARKGRAY);

    return value;
}

void menuButtons(bool &running, bool &debugging, int &indexPage, float contentY, int winWidth, Texture &background, const Inventory &inventory, 
            const Woodcutting &woodcutting, const Fishing &fishing, const Firemaking &firemaking, const Cooking &cooking, const Mining &mining, 
            const Smithing &smithing, const Thieving &thieving, const Fletching &fletching, const Crafting &crafting, const Runecrafting &runecrafting,
            const Herblore &herblore, const Agility &agility, const Summoning &summoning, const Astrology &astrology)
{
    float buttonHeight = 30.f;
    float scale = 4.f;
    //float padding = 10.f;

    const std::string skillText[] = 
    {
        "Woodcutting",
        "Fishing",
        "Firemaking",
        "Cooking",
        "Mining",
        "Smithing",
        "Thieving",
        "Fletching",
        "Crafting",
        "Runecrafting",
        "Herblore",
        "Agility",
        "Summoning",
        "Astrology"
    };

    std::vector<const BaseSkill*> skills =
    {
        &woodcutting,
        &fishing,
        &firemaking,
        &cooking,
        &mining,
        &smithing,
        &thieving,
        &fletching,
        &crafting,
        &runecrafting,
        &herblore,
        &agility,
        &summoning,
        &astrology
    };

    float startY = 15.f;
    float spacing = 35.f;
    
    for (size_t i = 0; i < skills.size(); i++)
    {
        float posY = startY + i * spacing;
        std::string skillsText = skillText[i] + " (" + std::to_string(skills[i]->getLevel()) + "/99)";
        if(Button(Rectangle{5, posY + contentY, winWidth / scale -10, buttonHeight}, skillsText.c_str()))
        {
            indexPage = i+1;
        }

    }

    // debugger button
    if (Button(Rectangle{5, 630 + (contentY-100), winWidth / scale -10, buttonHeight}, "Debugger"))
        debugging = true;

    // quit button
    if (Button(Rectangle{5, 670 + (contentY-100), winWidth / scale -10, buttonHeight}, "Quit"))
    {
        saveGame(inventory, woodcutting, fishing, firemaking, cooking, mining, smithing, crafting, runecrafting, "data/save.txt");
        running = false;
    }
}

void saveGame(const Inventory &inventory, const Woodcutting &wood, const Fishing &fishing, const Firemaking &firemaking, const Cooking &cooking, const Mining &mining, const Smithing &smithing, const Crafting &crafting, const Runecrafting &runecrafting, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open save file!\n";
        return;
    }

    // currency
    file << "[Currency]\n";
    file << "gold=" << inventory.getGold();
    file << "\n\n";

    // woodcutting
    file << "[Woodcutting]\n";
    file << "level=" << wood.getLevel() << '\n';
    file << "xp=" << wood.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << wood.getProgressArray()[i] << ' ';
    file << "\n\n";

    // fishing
    file << "[Fishing]\n";
    file << "level=" << fishing.getLevel() << '\n';
    file << "xp=" << fishing.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << fishing.getProgress() << ' ';
    file << "\n\n";
    
    // firemaking
    file << "[Firemaking]\n";
    file << "level=" << firemaking.getLevel() << '\n';
    file << "xp=" << firemaking.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << firemaking.getProgress() << ' ';
    file << "\n\n";

    // cooking
    file << "[Cooking]\n";
    file << "level=" << cooking.getLevel() << '\n';
    file << "xp=" << cooking.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << cooking.getProgress() << ' ';
    file << "\n\n";

    // mining
    file << "[Mining]\n";
    file << "level=" << mining.getLevel() << '\n';
    file << "xp=" << mining.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << mining.getProgressArray()[i] << ' ';
    file << "\n\n";

    // smithing
    file << "[Smithing]\n";
    file << "level=" << smithing.getLevel() << '\n';
    file << "xp=" << smithing.getXP() << '\n';
    file << "progress=";
    file << smithing.getProgress() << ' ';
    file << "\n\n";

    // crafting
    file << "[Crafting]\n";
    file << "level=" << crafting.getLevel() << '\n';
    file << "xp=" << crafting.getXP() << '\n';
    file << "progress=";
    file << crafting.getProgress() << ' ';
    file << "\n\n";

    // runecrafting
    file << "[Runecrafting]\n";
    file << "level=" << runecrafting.getLevel() << '\n';
    file << "xp=" << runecrafting.getXP() << '\n';
    file << "progress=";
    file << runecrafting.getProgress() << ' ';
    file << "\n\n";

    // inventory
    file << "[Inventory]\n";
    for (const auto &slot : inventory.getSlots())
    {
        if (slot)
        {   
            const Item &item = *slot;
            file << item.getSkillType() << "="
                << item.getId() << ","
                << item.getAmount() << "\n";
        }
    }
    file << "\n";

    std::cout << "Game saved!\n";
}

void loadGame(Inventory &inventory, Woodcutting &wood, Fishing &fishing, Firemaking &firemaking, Cooking &cooking, Mining &mining, Smithing &smithing, Crafting &crafting, Runecrafting &runecrafting, const std::string &filename)
{
    // open the file
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "No save file found.\n";
        return;
    }

    // preparation for reading the file (line by line and by sections of data)
    std::string line;
    enum class Section 
    { 
        None, Currency, Woodcutting, Fishing, Firemaking, Cooking, Mining, Smithing, Crafting, Runecrafting, Inventory 
    };
    Section currentSection = Section::None;

    // clear inventory slots
    for (auto &slot : inventory.getSlots())
    slot.reset();

    // loop over each line of data
    while (std::getline(file, line))
    {
        if (line.empty()) // if this line is empty, then skip
            continue;

        // section headers
        if (line == "[Currency]")
        {
            currentSection = Section::Currency;
            continue;
        }
        if (line == "[Woodcutting]")
        {
            currentSection = Section::Woodcutting;
            continue;
        }
        if (line == "[Fishing]")
        {
            currentSection = Section::Fishing;
            continue;
        }
        if (line == "[Firemaking]")
        {
            currentSection = Section::Firemaking;
            continue;
        }
        if (line == "[Cooking]")
        {
            currentSection = Section::Cooking;
            continue;
        }
        if (line == "[Mining]")
        {
            currentSection = Section::Mining;
            continue;
        }
        if (line == "[Smithing]")
        {
            currentSection = Section::Smithing;
            continue;
        }
        if (line == "[Crafting]")
        {
            currentSection = Section::Crafting;
            continue;
        }
        if (line == "[Runecrafting]")
        {
            currentSection = Section::Runecrafting;
            continue;
        }
        if (line == "[Inventory]")
        {
            currentSection = Section::Inventory;
            continue;
        }

        // split the data by key=value
        size_t equals = line.find('=');
        if (equals == std::string::npos) // if there is no equals then skip the line
            continue;

        std::string key = line.substr(0, equals);
        std::string value = line.substr(equals + 1);

        std::stringstream ss(value); // convert the value string into numbers

        if (currentSection == Section::Currency)
        {
            std::string rest = line.substr(equals + 1);
            size_t equals = rest.find('=');

            int curAmount = std::stoi(rest.substr(equals + 1));
            inventory.setGold(curAmount);
        }
        else if (currentSection == Section::Woodcutting)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                wood.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                wood.setXP(xp);
                wood.updateXPBar(0);
            }
            else if (key == "progress")
            {
                for (int i = 0; i < 8; i++)
                    ss >> wood.getProgressArray()[i];
            }
        }
        else if (currentSection == Section::Fishing)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                fishing.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                fishing.setXP(xp);
                fishing.updateXPBar(0);
            }
            else if (key == "progress")
            {
                for (int i = 0; i < 8; i++)
                    ss >> fishing.getProgress();
            }
        }
        else if (currentSection == Section::Firemaking)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                firemaking.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                firemaking.setXP(xp);
                firemaking.updateXPBar(0);
            }
            else if (key == "progress")
            {
                for (int i = 0; i < 8; i++)
                    ss >> firemaking.getProgress();
            }
        }
        else if (currentSection == Section::Cooking)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                cooking.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                cooking.setXP(xp);
                cooking.updateXPBar(0);
            }
            else if (key == "progress")
            {
                for (int i = 0; i < 8; i++)
                    ss >> cooking.getProgress();
            }
        }
        else if (currentSection == Section::Mining)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                mining.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                mining.setXP(xp);
                mining.updateXPBar(0);
            }
            else if (key == "progress")
            {
                for (int i = 0; i < 8; i++)
                    ss >> mining.getProgressArray()[i];
            }
        }
        else if (currentSection == Section::Smithing)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                smithing.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                smithing.setXP(xp);
                smithing.updateXPBar(0);
            }
            else if (key == "progress")
            {
                ss >> smithing.getProgress();
            }
        }
        else if (currentSection == Section::Crafting)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                crafting.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                crafting.setXP(xp);
                crafting.updateXPBar(0);
            }
            else if (key == "progress")
            {
                ss >> crafting.getProgress();
            }
        }
        else if (currentSection == Section::Runecrafting)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                runecrafting.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                runecrafting.setXP(xp);
                runecrafting.updateXPBar(0);
            }
            else if (key == "progress")
            {
                ss >> runecrafting.getProgress();
            }
        }
        else if (currentSection == Section::Inventory)
        {

            std::string skillType = line.substr(0, equals);
            std::string rest = line.substr(equals + 1);

            size_t comma = rest.find(',');
            if (comma == std::string::npos)
                continue;

            int id = std::stoi(rest.substr(0, comma));
            int amount = std::stoi(rest.substr(comma + 1));

            Item item = ItemDatabase::getItemByName(skillType, id);

            if (item.getTexture().id == 0)
                std::cerr << "Failed to load item: " << skillType << " id=" << id << '\n';
            else
            {
                item.setAmount(amount);
                inventory.addItem(item);
                std::cout << "Item loaded into bank: " << item.getName() << '\n'; 
            }
        }
    }
    std::cout << "Game loaded!\n";
}

int main()
{
    // initialise the window
    const static int winDimensions[2]{1280, 720};
    InitWindow(winDimensions[0], winDimensions[1], "Totally Not Melvor Idle");

    // load icon
    Image icon = LoadImage("assets/logo.png"); 
    SetWindowIcon(icon);
    UnloadImage(icon);

    // ensure the data folder exists
    std::filesystem::create_directory("data");

    Texture2D background = LoadTexture("assets/ui/background.jpg");

    // load meta data
    ItemDatabase::loadItems();

    // class declarations
    Inventory inventory;
    Woodcutting woodcutting(inventory);
    Fishing fishing(inventory);
    Firemaking firemaking(inventory);
    Cooking cooking(inventory);
    Mining mining(inventory);
    Smithing smithing(inventory);
    Thieving thieving;
    Fletching fletching;
    Crafting crafting(inventory);
    Runecrafting runecrafting(inventory);
    Herblore herblore;
    Agility agility;
    Summoning summoning;
    Astrology astrology;
    Debugger debugger(inventory, woodcutting, fishing, firemaking, cooking, mining, smithing, thieving, fletching, crafting, runecrafting, herblore, agility, summoning, astrology);
    //BaseSkill baseSkill;
    //baseSkill.loadBackground(); // load background image after InitWindow

    // set up window sizes after all objects exist
    woodcutting.getWindowSize(winDimensions[0], winDimensions[1]);
    mining.getWindowSize(winDimensions[0], winDimensions[1]);

    inventory.loadTextures();
    loadGame(inventory, woodcutting, fishing, firemaking, cooking, mining, smithing, crafting, runecrafting, "data/save.txt");

    // variable declarations
    int scale{4};
    float scrollValue = 0.0f;
    int indexPage{-2};
    float contentY{};
    bool running{true};

    SetTargetFPS(60);
    while (running && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // draw background
        DrawTextureEx(background, Vector2{(float)winDimensions[0] / scale, 0}, 0, 1, WHITE);

        if (indexPage == 0) // inventory
        {
            const float invPosY{100.f};
            const int cellSize{64};
            inventory.drawInventory(winDimensions[0] / scale + 20, invPosY + contentY-100, cellSize);
        }
        else if (indexPage == 1) 
            woodcutting.tick(GetFrameTime(), contentY); 
        else if (indexPage == 2)
            fishing.tick(GetFrameTime(), contentY);
        else if (indexPage == 3) 
            firemaking.tick(GetFrameTime(), contentY);
        else if (indexPage == 4) 
            cooking.tick(GetFrameTime(), contentY);
        else if (indexPage == 5) 
            mining.tick(GetFrameTime(), contentY);
        else if (indexPage == 6) 
            smithing.tick(GetFrameTime(), contentY);
        else if (indexPage == 9)
            crafting.tick(GetFrameTime(), contentY);
        else if (indexPage == 10)
            runecrafting.tick(GetFrameTime(), contentY);

        if (debugger.debugging)
        {
            debugger.tick(GetFrameTime());
        }
        
        const float panelW{320.f};
        const int fontSize = 20;
        
        // LEFT SIDE PANEL
        DrawRectangle(0, 0, panelW, winDimensions[1], GRAY);
        DrawRectangleLines(0, 0, panelW, winDimensions[1], BLACK);

        // SIDE PANEL TEXT
        DrawText("Scrollable content", 50, contentY + 200, 20, BLACK);
        menuButtons(running, debugger.debugging, indexPage, contentY, winDimensions[0], background, inventory, woodcutting, fishing, firemaking, cooking, 
                mining, smithing, thieving, fletching, crafting, runecrafting, herblore, agility, summoning, astrology);

        // TOP LEFT PANEL
        DrawRectangle(0, 0, panelW, 100, GRAY);
        DrawRectangleLines(0, 0, panelW, 100, BLACK);

        // BANK TEXT
        std::string bankSlots = "Bank " + std::to_string(inventory.getFilledSlots()) + "/" + std::to_string(inventory.SIZE);
        if (Button(Rectangle{0, 10, (float)winDimensions[0] / scale -1, 30.f}, bankSlots.c_str())) 
        {
            indexPage = 0;
        }

        // CURRENCY TEXT     
        std::string currencyText = "Gold: " + std::to_string(inventory.getGold());
        int currencyTextWidth = MeasureText(currencyText.c_str(), fontSize); // centre text
        DrawText(currencyText.c_str(), (panelW - currencyTextWidth)/2, 50, fontSize, GOLD);

        // SCROLL BAR
        scrollValue = ScrollBar({static_cast<float>(winDimensions[0]) - 20, 0, 20, static_cast<float>(winDimensions[1])}, scrollValue);

        // scrollable content WIP
        contentY = 100 - scrollValue * 400;
        
        EndDrawing();
    }

    if (!running || WindowShouldClose())
    {
        saveGame(inventory, woodcutting, fishing, firemaking, cooking, mining, smithing, crafting, runecrafting, "data/save.txt");
        std::cout << "Game saved!\n";
    }
    ItemDatabase::unloadItems();
    inventory.unloadTextures();
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
