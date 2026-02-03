#ifndef SMITHING_H
#define SMITHING_H

#include "raylib.h"
#include "Inventory.h"
#include "ItemDatabase.h"
#include "BaseSkill.h"
#include <iostream>

class Smithing : public BaseSkill
{
    Inventory &inventory;
public:
    Smithing(Inventory &invetory);
    virtual void drawTemplate(float contentY) override;
    void oreCombination(int ore1Amount, int ore1, int ore2Amount, int ore2, int bar);
    void oreSmelt(int oreAmount, int ore, int bar);
    virtual void tick(float deltaTime, float contentY) override;
protected:

private:
    ItemDatabase itemDatabase;
    Texture2D previewIcon = LoadTexture("assets/bank/smithing/bronze_bar.png");
    int selectedItemIndex = -1;
    
};


#endif