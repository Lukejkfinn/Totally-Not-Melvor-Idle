#pragma once
#include "raylib.h"
#include "BaseSkill.h"
#include "Inventory.h"

class Firemaking : public BaseSkill
{
    Inventory &inventory;
public:
    Firemaking(Inventory &inv);
    virtual void drawTemplate(float contentY) override;
protected:


private:

};