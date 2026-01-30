#include "raylib.h"
#include "raymath.h"
#include "ItemDatabase.h"
#include "Item.h"
#include "Inventory.h"
#include "BaseSkill.h"
#include "Woodcutting.h"
#include "Mining.h"
#include "debugger.h"
#include <iostream>
#include <fstream>
#include <iostream>

// forward declarations
void saveGame(const Woodcutting &wood, const Mining &mine, const std::string &filename);
void loadGame(Woodcutting &wood, Mining &mine, const std::string &filename);

bool Button(Rectangle bounds, const char *text)
{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);

    // Button color states
    Color bgColor = hovered ? DARKBLUE : GRAY;

    // Draw button
    DrawRectangleRec(bounds, bgColor);

    // Center text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        bounds.x + (bounds.width - textWidth) / 2,
        bounds.y + (bounds.height - fontSize) / 2,
        fontSize,
        WHITE);

    // Return true only when clicked
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

float ScrollBar(Rectangle track, float value)
{
    const float thumbHeight = 40.0f;

    // Clamp value
    value = Clamp(value, 0.0f, 1.0f);

    // Calculate thumb position
    float thumbY = track.y + value * (track.height - thumbHeight);
    Rectangle thumb = {track.x, thumbY, track.width, thumbHeight};

    Vector2 mouse = GetMousePosition();

    static bool dragging = false;

    // Mouse press on thumb
    if (CheckCollisionPointRec(mouse, thumb) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dragging = true;
    }

    // Release drag
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        dragging = false;
    }

    // Drag logic
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

    // Draw
    DrawRectangleRec(track, LIGHTGRAY);
    DrawRectangleRec(thumb, DARKGRAY);

    return value;
}

void menuButtons(bool &running, bool &debugging, int &indexPage, float contentY, int winWidth, Texture &background, const Woodcutting &woodcutting, const Mining &mining)
{
    float buttonHeight = 30.f;
    float scale = 4.f;
    float padding = 10.f;

    std::string woodText = "Woodcutting (" + std::to_string(woodcutting.getLevel()) + "/99)";
    if (Button(Rectangle{0, 25 + contentY, winWidth / scale, buttonHeight}, woodText.c_str()))
    {
        indexPage = 3;
    }

    std::string miningText = "Mining (" + std::to_string(mining.getLevel()) + "/99)";
    if (Button(Rectangle{0, 50 + padding + contentY, winWidth / scale, buttonHeight}, miningText.c_str()))
    {
        indexPage = 4;
    }

    if (Button(Rectangle{0, 630 + contentY, winWidth / scale, buttonHeight}, "Debugger"))
    {
        debugging = true;
    }

    if (Button(Rectangle{0, 670 + contentY, winWidth / scale, buttonHeight}, "Quit"))
    {
        saveGame(woodcutting, mining, "save.txt");
        running = false;
    }
}

void saveGame(const Woodcutting &wood, const Mining &mine, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open save file!\n";
        return;
    }

    // Woodcutting
    file << wood.getLevel() << ' ' << wood.getXP() << ' ';
    for (int i = 0; i < 8; i++)
        file << wood.getProgressArray()[i] << ' ';
    file << '\n';

    // Mining
    file << mine.getLevel() << ' ' << mine.getXP() << ' ';
    for (int i = 0; i < 8; i++)
        file << mine.getProgressArray()[i] << ' ';
    file << '\n';

    std::cout << "Game saved!\n";
}

void loadGame(Woodcutting &wood, Mining &mine, const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "No save file found.\n";
        return;
    }

    int lvl, xp;
    float prog;

    // Woodcutting
    file >> lvl >> xp;
    wood.setLevel(lvl);
    wood.setXP(xp);      // set BaseSkill::xp
    wood.updateXPBar(0); // refresh visual XP bar

    for (int i = 0; i < 8; i++)
    {
        file >> prog;
        wood.getProgressArray()[i] = prog;
    }

    // Mining
    file >> lvl >> xp;
    mine.setLevel(lvl);
    mine.setXP(xp);
    mine.updateXPBar(0);

    for (int i = 0; i < 8; i++)
    {
        file >> prog;
        mine.getProgressArray()[i] = prog;
    }

    std::cout << "Game loaded!\n";
}

int main()
{
    // initialis the window
    const static int winDimensions[2]{1280, 720};
    InitWindow(winDimensions[0], winDimensions[1], "Totally Not Melvor Idle...");

    Texture2D background = LoadTexture("assets/background.jpg");
    Texture2D chaz = LoadTexture("assets/icons/chaz.jpg");

    // class declarations
    Inventory inventory;
    Woodcutting woodcutting(inventory);
    Mining mining(inventory);
    woodcutting.getWindowSize(winDimensions[0], winDimensions[1]);
    mining.getWindowSize(winDimensions[0], winDimensions[1]);
    Debugger debugger(inventory, woodcutting, mining);

   // Initialize the inventory with some items
    //inventory.initializeInventory();  // Populating inventory right away

    loadGame(woodcutting, mining, "save.txt");

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
        {
            DrawTextureEx(background, Vector2{(float)winDimensions[0] / scale, 0}, 0, 1, WHITE);
            float chazScale = 1.0f + sin(GetTime()) * 0.1f; // Pulsing effect
            DrawTextureEx(chaz, Vector2{(float)winDimensions[0] / 2 - 50, (float)winDimensions[1] / 2}, 0, chazScale, WHITE);
        }
        else if (indexPage == 1)
        {
            //std::cout << "Drawing inventory..." << std::endl;
            //const float invPosX{325.f};
            const float invPosY{100.f};
            const int cellSize{64};
            inventory.drawInventory(inventory, winDimensions[0] / scale + 20, invPosY, cellSize);
        }
        else if (indexPage == 3)
        {
            woodcutting.tick(GetFrameTime(), contentY);
        }
        else if (indexPage == 4)
        {
            // mining code goes here
            mining.tick(GetFrameTime(), contentY);
        }

        if (debugger.debugging)
        {
            debugger.tick(GetFrameTime());
        }

        // Drawing side panel
        DrawRectangle(0, 0, winDimensions[0] / scale, winDimensions[1], GRAY);

        // text on left to get a vague idea of positioning TEMP
        DrawText("Scrollable content", 50, contentY + 100, 20, BLACK);
        menuButtons(running, debugger.debugging, indexPage, contentY, winDimensions[0], background, woodcutting, mining);

        // bank and shop panel/background
        DrawRectangle(0, 0, winDimensions[0] / scale, 100, GRAY);
        DrawRectangleLines(0, 0, winDimensions[0] / scale, 100, BLACK);

        // drawing bank button
        if (Button(Rectangle{0, 10, (float)winDimensions[0] / scale -1, 30.f}, "Bank")) indexPage = 1;
        // draw the scroll bar
        scrollValue = ScrollBar({static_cast<float>(winDimensions[0]) - 20, 0, 20, static_cast<float>(winDimensions[1])}, scrollValue);

        // scrollable content WIP
        contentY = 100 - scrollValue * 400;

        EndDrawing();
    }

    if (!running || WindowShouldClose())
    {
        saveGame(woodcutting, mining, "save.txt");
        std::cout << "Game saved!\n";
    }

    UnloadTexture(background);
    CloseWindow();
}
