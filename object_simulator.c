/*
 * Object Simulator Assignment
 * Computer Science XII - Computer Systems
 * 
 * This program simulates object-oriented programming using structs and
 * function pointers to understand how Python's class system works at the
 * implementation level.
 * 
 * You'll build an RPG character system with inheritance and polymorphism.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================================================================
// PART 1: BASE CHARACTER STRUCT
// =============================================================================
// Define the base Character "class" that other character types will inherit from.
// This struct contains data fields and function pointers (simulating methods).

// TODO: Define the Character struct with the following members:
// - char name[50]: character's name
// - int health: current health points
// - int level: character level
// - Function pointer: void (*attack)(struct Character* self)
// - Function pointer: void (*take_damage)(struct Character* self, int damage)
//
// Hint: Function pointers are declared as: return_type (*pointer_name)(parameters)
// Use 'struct Character*' for self parameter since the struct isn't fully defined yet

typedef struct Character {

    // TODO: Add data members here
    char name[50];
    int health;
    int level;
    
    // TODO: Add function pointer members here
    void (*attack)(struct Character* self);

    void (*take_damage)(struct Character* self, int damage);
    
} Character;

// =============================================================================
// PART 2: CHARACTER METHODS
// =============================================================================
// Implement the actual functions that Character structs will point to.
// These simulate "methods" in Python classes.

// TODO: Implement character_attack function
// This function should:
// - Accept a Character* pointer (the "self" parameter)
// - Print: "[name] performs a basic attack!"
// Hint: void character_attack(Character* self) { ... }

void character_attack(Character* self) {
    printf("%s performs a basic attack!\n", self->name);
}


// TODO: Implement character_take_damage function
// This function should:
// - Accept a Character* pointer and an int damage
// - Reduce the character's health by the damage amount
// - Print: "[name] takes [damage] damage! Health: [remaining health]"

void character_take_damage(Character* self, int damage) {
    self->health = self->health - damage;
    printf("%s takes %d damage! Health: %d\n", self->name, damage, self->health);
}


// TODO: Implement character_init function (constructor)
// This function should:
// - Accept a Character* pointer, name string, health, and level
// - Copy the name into the struct using strncpy
// - Set health and level
// - Initialize attack function pointer to character_attack
// - Initialize take_damage function pointer to character_take_damage
// Hint: strncpy(dest, src, size) and remember to null-terminate

void character_init(Character* c, const char* name, int health, int level) {
    strncpy(c->name, name, 49);
    c->name[49] = '\0';
    c->health = health;
    c->level = level;
    c->attack = character_attack;
    c->take_damage = character_take_damage;
}




// =============================================================================
// PART 3: DERIVED CHARACTER TYPES
// =============================================================================
// Create specialized Warrior and Mage types that "inherit" from Character
// using composition (embedding the base struct as the first member).

// TODO: Define the Warrior struct
// This should contain:
// - Character base: the base Character struct as the FIRST member
// - int strength: warrior-specific attribute
// Hint: Having Character as the first member allows casting between types

typedef struct Warrior {
    // TODO: Add Character base as first member
    Character base;
    
    // TODO: Add Warrior-specific data
    int strength;

} Warrior;

// TODO: Define the Mage struct
// This should contain:
// - Character base: the base Character struct as the FIRST member
// - int mana: mage-specific attribute

typedef struct Mage {
    // TODO: Add Character base as first member
    Character base;
    
    // TODO: Add Mage-specific data
    int mana;

} Mage;

// =============================================================================
// PART 4: POLYMORPHIC METHODS
// =============================================================================
// Implement specialized attack methods that override the base Character attack.
// This demonstrates polymorphism - same function call, different behavior.

// TODO: Implement warrior_attack function
// This function should:
// - Accept a Character* pointer (note: NOT Warrior*, we'll cast it)
// - Cast the Character* to Warrior* to access warrior-specific data
// - Print: "[name] swings sword with [strength] strength!"
// Hint: Warrior* w = (Warrior*)self;

void warrior_attack(Character* self) {
    Warrior* w = (Warrior*)self;
    printf("%s swings sword with %d strength!\n", w->base.name, w->strength);
}



// TODO: Implement mage_attack function
// This function should:
// - Accept a Character* pointer
// - Cast to Mage* to access mage-specific data
// - Reduce mana by 10 (cost of spell)
// - Print: "[name] casts fireball using [mana] mana!"
// - If mana is below 10, print: "[name] is out of mana!"

void mage_attack(Character* self) {
    Mage* m = (Mage*)self;
    if (m->mana < 10) {
        printf("%s is out of mana!\n", m->base.name);
    }
    else {
        printf("%s casts fireball using %d mana\n", m->base.name, m->mana);
        m->mana = m->mana - 10;
    }
}



// TODO: Implement warrior_init function (constructor)
// This function should:
// - Accept a Warrior* pointer, name, health, level, and strength
// - Initialize the base Character part using character_init
// - Set the strength field
// - Override the attack function pointer to point to warrior_attack
// Hint: To initialize base: character_init(&w->base, name, health, level);
// Then override: w->base.attack = warrior_attack;

void warrior_init(Warrior* w, const char* name, int health, int level, int strength) {
    character_init(&w->base, name, health, level);
    w->strength = strength;
    w->base.attack = warrior_attack;
}


// TODO: Implement mage_init function (constructor)
// This function should:
// - Accept a Mage* pointer, name, health, level, and mana
// - Initialize the base Character part using character_init
// - Set the mana field
// - Override the attack function pointer to point to mage_attack

void mage_init(Mage* m, const char* name, int health, int level, int mana) {
    character_init(&m->base, name, health, level);
    m->mana = mana;
    m->base.attack = mage_attack;
}



// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("=============================================================\n");
    printf("         OBJECT SIMULATOR: RPG Character System\n");
    printf("=============================================================\n");
    
    // TODO: Create and test your character system here
    // 1. Create a basic Character using character_init
    // 2. Call its attack and take_damage methods
    // 3. Create a Warrior using warrior_init
    // 4. Call the Warrior's attack method (should use warrior_attack)
    // 5. Create a Mage using mage_init
    // 6. Call the Mage's attack method multiple times (to show mana usage)
    // 7. Demonstrate polymorphism by storing different character types
    //    in an array and calling attack on each
    
    Character basic;
    character_init(&basic, "Aang", 100, 10);
    basic.attack(&basic);
    basic.take_damage(&basic, 25);
    
    Warrior war;
    warrior_init(&war, "Sokka", 95, 2, 54);
    war.base.attack(&war.base);

    Mage mag;
    mage_init(&mag, "Zuko", 98, 6, 22);
    mag.base.attack(&mag.base);
    mag.base.attack(&mag.base);  
    mag.base.attack(&mag.base);   
    
    Character* all_characters[3] = {
        &basic,
        (Character*)&war,
        (Character*)&mag
    };

    for (int i = 0; i < 3; i++) {
        all_characters[i]->attack(all_characters[i]);
    }
    
    
    
    printf("\n=============================================================\n");
    printf("Object simulation complete!\n");
    printf("=============================================================\n");
    
    return 0;
}
