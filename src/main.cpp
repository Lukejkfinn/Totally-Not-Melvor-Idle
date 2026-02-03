#include "raylib.h"
#include "raymath.h"
#include "ItemDatabase.h"
#include "Item.h"
#include "Inventory.h"
#include "BaseSkill.h"
#include "Woodcutting.h"
#include "Mining.h"
#include "Smithing.h"
#include "debugger.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

// forward declarations
void saveGame(const Inventory &inventory, const Woodcutting &wood, const Mining &mine, const std::string &filename);
void loadGame(const Inventory &inventory, const Woodcutting &wood, const Mining &mine, const std::string &filename);

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

void menuButtons(bool &running, bool &debugging, int &indexPage, float contentY, int winWidth, Texture &background, const Inventory &inventory, const Woodcutting &woodcutting, const Mining &mining, const Smithing &smithing)
{
    float buttonHeight = 30.f;
    float scale = 4.f;
    float padding = 10.f;

    std::string woodText = "Woodcutting (" + std::to_string(woodcutting.getLevel()) + "/99)";
    if (Button(Rectangle{5, 25 + contentY, winWidth / scale -10, buttonHeight}, woodText.c_str()))
    {
        indexPage = 3;
    }

    std::string miningText = "Mining (" + std::to_string(mining.getLevel()) + "/99)";
    if (Button(Rectangle{5, 50 + padding + contentY, winWidth / scale -10, buttonHeight}, miningText.c_str()))
    {
        indexPage = 4;
    }

    std::string smithingText = "Smithing (" + std::to_string(smithing.getLevel()) + "/99)";
    if (Button(Rectangle{5, 75 + 20 + contentY, winWidth / scale -10, buttonHeight}, smithingText.c_str()))
    {
        indexPage = 5;
    }

    if (Button(Rectangle{5, 630 + contentY, winWidth / scale -10, buttonHeight}, "Debugger"))
    {
        debugging = true;
    }

    if (Button(Rectangle{5, 670 + contentY, winWidth / scale -10, buttonHeight}, "Quit"))
    {
        saveGame(inventory, woodcutting, mining, "data/save.txt");
        running = false;
    }
}

void saveGame(const Inventory &inventory, const Woodcutting &wood, const Mining &mine, const std::string &filename)
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

    // woodcutting
    file << "[Woodcutting]\n";
    file << "level=" << wood.getLevel() << '\n';
    file << "xp=" << wood.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << wood.getProgressArray()[i] << ' ';
    file << "\n\n";

    // mining
    file << "[Mining]\n";
    file << "level=" << mine.getLevel() << '\n';
    file << "xp=" << mine.getXP() << '\n';
    file << "progress=";
    for (int i = 0; i < 8; i++)
        file << mine.getProgressArray()[i] << ' ';
    file << "\n\n";

    std::cout << "Game saved!\n";
}

void loadGame(Inventory &inventory, Woodcutting &wood, Mining &mine, const std::string &filename)
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
    enum class Section { None, Currency, Inventory, Woodcutting, Mining };
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
        if (line == "[Inventory]")
        {
            currentSection = Section::Inventory;
            continue;
        }
        if (line == "[Woodcutting]")
        {
            currentSection = Section::Woodcutting;
            continue;
        }
        if (line == "[Mining]")
        {
            currentSection = Section::Mining;
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
        else if (currentSection == Section::Mining)
        {
            if (key == "level")
            {
                int lvl;
                ss >> lvl;
                mine.setLevel(lvl);
            }
            else if (key == "xp")
            {
                int xp;
                ss >> xp;
                mine.setXP(xp);
                mine.updateXPBar(0);
            }
            else if (key == "progress")
            {
                for (int i = 0; i < 8; i++)
                    ss >> mine.getProgressArray()[i];
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

    Texture2D background = LoadTexture("assets/background.jpg");

    // load meta data
    ItemDatabase::loadItems();

    // class declarations
    Inventory inventory;
    Woodcutting woodcutting(inventory);
    Mining mining(inventory);
    Smithing smithing(inventory);
    Debugger debugger(inventory, woodcutting, mining);
    //BaseSkill baseSkill;
    //baseSkill.loadBackground(); // load background image after InitWindow

    // set up window sizes after all objects exist
    woodcutting.getWindowSize(winDimensions[0], winDimensions[1]);
    mining.getWindowSize(winDimensions[0], winDimensions[1]);

    inventory.loadTextures();
    loadGame(inventory, woodcutting, mining, "data/save.txt");

    // variable declarations
    int scale{4};
    float scrollValue = 0.0f;
    int indexPage{};
    float contentY{};
    bool running{true};

    SetTargetFPS(60);
    while (running && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // draw background
        if (indexPage == 0)
            DrawTextureEx(background, Vector2{(float)winDimensions[0] / scale, 0}, 0, 1, WHITE);
        else if (indexPage == 1)
        {
            const float invPosY{100.f};
            const int cellSize{64};
            inventory.drawInventory(winDimensions[0] / scale + 20, invPosY + contentY-100, cellSize);
        }
        else if (indexPage == 3) 
            woodcutting.tick(GetFrameTime(), contentY);
        else if (indexPage == 4) 
            mining.tick(GetFrameTime(), contentY);
        else if (indexPage == 5) 
            smithing.tick(GetFrameTime(), contentY);

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
        menuButtons(running, debugger.debugging, indexPage, contentY, winDimensions[0], background, inventory, woodcutting, mining, smithing);

        // TOP LEFT PANEL
        DrawRectangle(0, 0, panelW, 100, GRAY);
        DrawRectangleLines(0, 0, panelW, 100, BLACK);

        // BANK TEXT
        std::string bankSlots = "Bank " + std::to_string(inventory.getFilledSlots()) + "/" + std::to_string(inventory.SIZE);
        if (Button(Rectangle{0, 10, (float)winDimensions[0] / scale -1, 30.f}, bankSlots.c_str())) indexPage = 1;

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
        saveGame(inventory, woodcutting, mining, "data/save.txt");
        std::cout << "Game saved!\n";
    }
    ItemDatabase::unloadItems();
    inventory.unloadTextures();
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
