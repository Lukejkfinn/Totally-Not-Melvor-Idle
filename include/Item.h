#ifndef ITEM_H
#define ITEM_H

#include "raylib.h" 
#include <string>

class Item
{
public:
    Texture2D texture;      // texture for the item
    int amount;             // amount of this item (if stackable)
    bool stackable;         // whether this item can be stacked
    int max_stack;          // max stack size for this item
    std::string name;       // name of the item
    std::string skillType;  // name of the skill
    int id;                 // id of the item

    // WHEN ADDING TO THIS MAKE SURE TO MAKE THE RESPECTIVE GETTER / SETTER
    Item(Texture2D img, int amount, bool stackable, int max_stack, const std::string &name, const std::string &skillType, int id)
        : texture(img), amount(amount), stackable(stackable), max_stack(max_stack), name(name), skillType(skillType), id(id) {}

    // UPDATE THIS TO MATCH THE ABOVE 
    Item() : texture({0}), amount(0), stackable(true), max_stack(64), name(""), skillType(""), id(0) {}


    Texture2D getTexture() const { return texture; }                // getter for texture
    void setAmount(int newAmount) { amount = newAmount; }           // setter for amount (needed for stackable items)
    int getAmount() const { return amount; }                        // getter for amount
    bool isStackable() const { return stackable; }                  // getter for stackable status
    int getMaxStack() const { return max_stack; }                   // getter for max stack size
    void setMaxStack(int newMaxStack) { max_stack = newMaxStack; }  // setter for max stack size
    std::string getName() const { return name; }                    // getter for item name
    std::string getSkillType() const { return skillType; }          // getter for skill type
    int getId() const { return id; }                                // getter for the id
};

#endif
