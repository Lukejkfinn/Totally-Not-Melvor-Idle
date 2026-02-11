#include "raylib.h"
#include "ItemDatabase.h"
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
#include <fstream>
#include <iostream>
#include <cstddef>

struct SkillEntry
{
    BaseSkill* skill;
};

class Debugger
{
    Inventory &inventory;
    Woodcutting &woodcutting;
    Fishing &fishing;
    Firemaking &firemaking;
    Cooking &cooking;
    Mining &mining;
    Smithing &smithing;
    Thieving &thieving;
    Fletching &fletching;
    Crafting &crafting;
    Runecrafting &runecrafting;
    Herblore &herblore;
    Agility &agility;
    Summoning &summoning;
    Astrology &astrology;

public:
    Debugger(Inventory &inv, Woodcutting &wc, Fishing &fish, Firemaking &fm, Cooking &cook, Mining &mine, Smithing &smith, Thieving &thieving, 
        Fletching &fletch, Crafting &craft, Runecrafting &rc, Herblore &herb, Agility &agility, Summoning &summon, Astrology &astro);
    bool btn(Rectangle bounds, const char *text);
    void drawSkillsTemplate();
    void drawObjectsTemplate();
    void tick(float deltaTime);
    bool debugging{false};

protected:

private:
    Texture2D debuggerBG{LoadTexture("assets/ui/debuggerBG.jpg")};
    const float buttonPosX{700};
    BaseSkill baseSkill;
    ItemDatabase itemDatabase;
    Rectangle woodcuttingBtn;
    Rectangle miningBtn;
    Rectangle closeBtn;
    
};