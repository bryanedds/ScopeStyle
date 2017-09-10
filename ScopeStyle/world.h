#ifndef BGE_SIMULATION_H
#define BGE_SIMULATION_H

#include <stdbool.h>

#include "error.h"
#include "castable.h"
#include "renderer.h"
#include "physics_engine.h"

/// Forward declarations.
struct simulant;
struct entity;
struct button;
struct screen;
struct title_screen;
struct gameplay_screen;
struct world;

/// The maximum number of characters in a simulant's name.
#define SIMULANT_NAME_MAX 64

/// A common simulant type.
struct simulant
{
    /// Simulants are castable (in fact, they will be reflectable when that functionality is devised).
    struct castable castable_p;

    /// The name of a simulant.
    char name_r[SIMULANT_NAME_MAX];
};

void initialize_simulant(struct simulant* simulant, const char* (*get_type_name)(struct castable*), void* (*try_cast)(struct castable*, const char*), const char* name);

/// An entity type, such as for buttons or characters.
struct entity
{
    struct simulant simulant_p;
    int visible;
};

void initialize_entity(struct entity* entity, const char* (*get_type_name)(struct castable*), void* (*try_cast)(struct castable*, const char*), const char* name);

/// A clickable button.
struct button
{
    struct entity entity_p;
    void (*click_opt)(struct button*, struct world*); // the 'opt' suffix means the pointer may be null.
};

void initialize_button(struct button* button, const char* name, void (*click_opt)(struct button*, struct world*));

/// A player character.
struct player
{
    struct entity entity_p;
    int health;
};

void initialize_player(struct player* player, const char* name, int health);

/// Represents interactive screens, such as a title screen or a gameplay screen.
struct screen
{
    struct simulant simulant_p;
    // assume some screen-specific implementation...
};

void initialize_screen(struct screen* screen, const char* (*get_type_name)(struct castable*), void* (*try_cast)(struct castable*, const char*), const char* name);

/// The simulation's title screen.
struct title_screen
{
    struct screen screen_p;
    // assume some title screen-specific implementation...
};

void initialize_title_screen(struct title_screen* title_screen, const char* name);

/// The simulation's gameplay screen.
struct gameplay_screen
{
    struct screen screen_p;
    // assume some gameplay screen-specific implementation...
};

void initialize_gameplay_screen(struct gameplay_screen* gameplay_screen, const char* name);

/// The number of screens in the world.
#define WORLD_SCREEN_COUNT 2

/// The world, in a functional sense.
/// Contains the program's entire state.
struct world
{
    struct renderer* renderer_p;
    struct physics_engine* physics_engine_p;
    struct title_screen title_screen_p;
    struct gameplay_screen gameplay_screen_p;
    struct button title_exit_button_p;
    struct button title_play_button_p;
    struct button gameplay_stop_button_p;
    struct player player_p;
    struct screen* selected_screen_p;
};

void get_screens_world(struct world* world, struct screen screens[WORLD_SCREEN_COUNT]);
void update_world(struct world* world, struct error* err);
void initialize_world(struct world* world, struct renderer* renderer, struct physics_engine* physics_engine, struct error* err);
void finalize_world(struct world* world);

#endif
