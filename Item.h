#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"  // raylib texture handling
#include <string>

class Item
{
public:
    Texture2D texture;      // Texture for the item
    int amount;             // Amount of this item (if stackable)
    bool stackable;         // Whether this item can be stacked
    int max_stack;          // Max stack size for this item
    std::string name;       // Name of the item
    std::string skillType;  // Name of the skill
    int id;                 // Id of the item

    // WHEN ADDING TO THIS MAKE SURE TO MAKE THE RESPECTIVE GETTER / SETTER
    Item(Texture2D img, int amount, bool stackable, int max_stack, const std::string &name, const std::string &skillType, int id)
        : texture(img), amount(amount), stackable(stackable), max_stack(max_stack), name(name), skillType(skillType), id(id) {}

    // UPDATE THIS TO MATCH THE ABOVE 
    Item() : texture({0}), amount(0), stackable(true), max_stack(64), name(""), skillType(""), id(0) {}


    Texture2D getTexture() const { return texture; } // Getter for texture
    void setAmount(int newAmount) { amount = newAmount; } // Setter for amount (needed for stackable items)
    int getAmount() const { return amount; } // Getter for amount
    bool isStackable() const { return stackable; } // Getter for stackable status
    int getMaxStack() const { return max_stack; } // Getter for max stack size
    void setMaxStack(int newMaxStack) { max_stack = newMaxStack; } // Setter for max stack size
    std::string getName() const { return name; } // Getter for item name
    std::string getSkillType() const { return skillType; } // Getter for skill type
    int getId() const { return id; } // Getter for the id

    // Optional method to unload the texture
    // void unloadTexture()
    // {
    //     if (texture.id != 0) {
    //         UnloadTexture(texture);  // Properly unload texture to free memory
    //     }
    // }

    // Destructor: Cleanup texture when item is destroyed
    // ~Item() {
    //     unloadTexture();
    // }
};

#endif // ITEM_H
