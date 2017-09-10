#include "world.h"

#include <string.h>

// struct simulant

const char* get_name(struct simulant* simulant)
{
    return simulant->name_p;
}

void initialize_simulant(
    struct simulant* simulant,
    const char* (*get_type_name)(struct castable*),
    void* (*try_cast)(struct castable*, const char*),
    const char* name)
{
    initialize_castable(&simulant->castable_p, get_type_name, try_cast);
    strncpy(simulant->name_p, name, SIMULANT_NAME_MAX);
}

// struct entity

void initialize_entity(
    struct entity* entity,
    const char* (*get_type_name)(struct castable*),
    void* (*try_cast)(struct castable*, const char*),
    const char* name)
{
    initialize_simulant(&entity->simulant_p, get_type_name, try_cast, name);
    entity->visible = true;
}

// struct button

static const char* get_type_name_button(struct castable* castable)
{
    return "button";
}

static void* try_cast_button(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    if (strcmp(type_name, "button") == 0) return castable;
    return NULL;
}

void initialize_button(struct button* button, const char* name, void(*click_opt)(struct button*, struct world*))
{
    initialize_entity(&button->entity_p, get_type_name_button, try_cast_button, name);
    button->click_opt = click_opt;
}

// struct player

static const char* get_type_name_player(struct castable* castable)
{
    return "player";
}

static void* try_cast_player(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    if (strcmp(type_name, "player") == 0) return castable;
    return NULL;
}

void initialize_player(struct player* player, const char* name, int health)
{
    initialize_entity(&player->entity_p, get_type_name_player, try_cast_player, name);
    player->health = health;
}

// struct screen

void initialize_screen(struct screen* screen, const char* (*get_type_name)(struct castable*), void* (*try_cast)(struct castable*, const char*), const char* name)
{
    initialize_simulant(&screen->simulant_p, get_type_name, try_cast, name);
}

// struct title_screen

static const char* get_type_name_title_screen(struct castable* castable)
{
    return "title_screen";
}

static void* try_cast_title_screen(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    if (strcmp(type_name, "title_screen") == 0) return castable;
    return NULL;
}

void initialize_title_screen(struct title_screen* title_screen, const char* name)
{
    initialize_screen(&title_screen->screen_p, get_type_name_title_screen, try_cast_title_screen, name);
}

// struct gameplay_screen

static const char* get_type_name_gameplay_screen(struct castable* castable)
{
    return "gameplay_screen";
}

static void* try_cast_gameplay_screen(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    if (strcmp(type_name, "gameplay_screen") == 0) return castable;
    return NULL;
}

void initialize_gameplay_screen(struct gameplay_screen* gameplay_screen, const char* name)
{
    initialize_screen(&gameplay_screen->screen_p, get_type_name_gameplay_screen, try_cast_gameplay_screen, name);
}

// struct world

static void title_exit_button_click(struct button* button, struct world* world)
{
    // assume implementation...
}

static void title_play_button_click(struct button* button, struct world* world)
{
    // assume implementation...
}

static void gameplay_stop_button_click(struct button* button, struct world* world)
{
    // assume implementation...
}

void get_screens_world(struct world* world, struct screen screens[WORLD_SCREEN_COUNT])
{
    screens[0] = world->title_screen_p.screen_p;
    screens[1] = world->gameplay_screen_p.screen_p;
}

void update_world(struct world* world, struct error* err)
{
    integrate_physics_engine(world->physics_engine_p);
    // ...and update simulants
    render_renderer(world->renderer_p);
}

void initialize_world(struct world* world, struct renderer* renderer, struct physics_engine* physics_engine, struct error* err)
{
    world->renderer_p = renderer;
    world->physics_engine_p = physics_engine;
    initialize_title_screen(&world->title_screen_p, "title");
    initialize_gameplay_screen(&world->gameplay_screen_p, "gameplay");
    initialize_button(&world->title_exit_button_p, "title/exit", title_exit_button_click);
    initialize_button(&world->title_play_button_p, "title/play", title_play_button_click);
    initialize_button(&world->gameplay_stop_button_p, "gamplay/stop", gameplay_stop_button_click);
    initialize_player(&world->player_p, "gameplay/player", 10);
    world->selected_screen_p = &world->title_screen_p.screen_p;
}

void finalize_world(struct world* world)
{
    // nothing to do
}
