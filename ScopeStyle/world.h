#ifndef BGE_SIMULATION_H
#define BGE_SIMULATION_H

#include <stdbool.h>

#include "error.h"
#include "category.h"
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
    /// The 'c' suffix means the field will never be changed after initialization.
    char name_c[SIMULANT_NAME_MAX];
};

const char* get_name_simulant(struct simulant* simulant);
void initialize_simulant(struct simulant* simulant, const char* name);
inline struct castable* to_castable_from_simulant(struct simulant* simulant) { return &simulant->castable_p; }
inline struct equatable* to_equatable_from_simulant(struct simulant* simulant) { return to_equatable_from_castable(&simulant->castable_p); }

/// An entity type, such as for buttons or characters.
struct entity
{
    struct simulant simulant_p;
    int visible;
};

const char* get_name_entity(struct entity* entity);
void initialize_entity(struct entity* entity, const char* name);
inline struct simulant* to_simulant_from_entity(struct entity* entity) { return &entity->simulant_p; }
inline struct castable* to_castable_from_entity(struct entity* entity) { return to_castable_from_simulant(&entity->simulant_p); }
inline struct equatable* to_equatable_from_entity(struct entity* entity) { return to_equatable_from_simulant(&entity->simulant_p); }

/// A clickable button.
struct button
{
    struct entity entity_p;
    void (*click_opt)(struct button*, struct world*); // the 'opt' suffix means the pointer may be null.
};

void initialize_button(struct button* button, const char* name, void (*click_opt)(struct button*, struct world*));
inline struct entity* to_entity_from_button(struct button* button) { return &button->entity_p; }

/// Represents interactive screens, such as a title screen or a gameplay screen.
struct screen
{
    struct simulant simulant_p;
};

const char* get_name_screen(struct screen* screen);
void initialize_screen(struct screen* screen, const char* name);
inline struct simulant* to_simulant_from_screen(struct screen* screen) { return &screen->simulant_p; }
inline struct castable* to_castable_from_screen(struct screen* screen) { return to_castable_from_simulant(&screen->simulant_p); }
inline struct equatable* to_equatable_from_screen(struct screen* screen) { return to_equatable_from_simulant(&screen->simulant_p); }

/// The simulation's title screen.
struct title_screen
{
    struct screen screen_p;
};

void initialize_title_screen(struct title_screen* title_screen, const char* name);
inline struct screen* to_screen_from_title_screen(struct title_screen* title_screen) { return &title_screen->screen_p; }

/// The simulation's gameplay screen.
struct gameplay_screen
{
    struct screen screen_p;
};

void initialize_gameplay_screen(struct gameplay_screen* gameplay_screen, const char* name);
inline struct screen* to_screen_from_gameplay_screen(struct gameplay_screen* gameplay_screen) { return &gameplay_screen->screen_p; }

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
    struct entity player_p;
    struct screen* selected_screen_p;
};

void get_screens_world(struct world* world, struct screen screens[WORLD_SCREEN_COUNT]);
void update_world(struct world* world, struct error* err);
void initialize_world(struct world* world, struct renderer* renderer, struct physics_engine* physics_engine, struct error* err);
void finalize_world(struct world* world);

#endif
