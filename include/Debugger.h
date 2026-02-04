#include "raylib.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "BaseSkill.h"
#include "Woodcutting.h"
#include "Mining.h"
#include "Smithing.h"
#include <fstream>
#include <iostream>
#include <cstddef>

class Debugger
{
    Inventory &inventory;
    Woodcutting &woodcutting;
    Mining &mining;
    Smithing &smithing;

public:
    Debugger(Inventory &inv, Woodcutting &wc, Mining &mine, Smithing &smith);
    bool btn(Rectangle bounds, const char *text);
    void drawSkillsTemplate();
    void drawObjectsTemplate();
    void tick(float deltaTime);
    bool debugging{false};

protected:

private:
    Texture2D debuggerBG{LoadTexture("assets/debuggerBG.jpg")};
    const float buttonPosX{700};
    BaseSkill baseSkill;
    ItemDatabase itemDatabase;
    Rectangle woodcuttingBtn;
    Rectangle miningBtn;
    Rectangle closeBtn;
    
};