#include "Firemaking.h"

Firemaking::Firemaking(Inventory &inv) : inventory(inv)
{

}

void Firemaking::drawTemplate(float contentY) 
{
    BaseSkill::drawTemplate(contentY);
}