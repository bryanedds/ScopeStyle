#include "world.h"

#include <string.h>

// struct simulant

static const char* get_type_name_simulant(struct castable* castable)
{
    return "simulant";
}

static void* try_cast_simulant(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    return NULL;
}

const char* get_name_simulant(struct simulant* simulant)
{
    return simulant->name_c;
}

void initialize_simulant(struct simulant* simulant, const char* name)
{
    initialize_equatable(&simulant->castable_p.equatable_p);
    simulant->castable_p.get_type_name_c = get_type_name_simulant;
    simulant->castable_p.try_cast_c = try_cast_simulant;
    strncpy(simulant->name_c, name, SIMULANT_NAME_MAX);
}

// struct entity

static const char* get_type_name_entity(struct castable* castable)
{
    return "entity";
}

static void* try_cast_entity(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    return NULL;
}

const char* get_name_entity(struct entity* entity)
{
    return get_name_simulant(&entity->simulant_p);
}

void initialize_entity(struct entity* entity, const char* name)
{
    initialize_simulant(&entity->simulant_p, name);
    entity->simulant_p.castable_p.get_type_name_c = get_type_name_entity;
    entity->simulant_p.castable_p.try_cast_c = try_cast_entity;
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
    initialize_entity(&button->entity_p, name);
    button->entity_p.simulant_p.castable_p.get_type_name_c = get_type_name_button;
    button->entity_p.simulant_p.castable_p.try_cast_c = try_cast_button;
    button->click_opt = click_opt;
}

// struct screen

static const char* get_type_name_screen(struct castable* castable)
{
    return "screen";
}

static void* try_cast_screen(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "screen") == 0) return castable;
    return NULL;
}

const char* get_name_screen(struct screen* screen)
{
    return get_name_simulant(&screen->simulant_p);
}

void initialize_screen(struct screen* screen, const char* name)
{
    initialize_simulant(&screen->simulant_p, name);
    screen->simulant_p.castable_p.get_type_name_c = get_type_name_screen;
    screen->simulant_p.castable_p.try_cast_c = try_cast_screen;
}

// struct title_screen

static const char* get_type_name_title_screen(struct castable* castable)
{
    return "title_screen";
}

static void* try_cast_title_screen(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    if (strcmp(type_name, "title_screen") == 0) return castable;
    return NULL;
}

void initialize_title_screen(struct title_screen* title_screen, const char* name)
{
    initialize_screen(&title_screen->screen_p, name);
    title_screen->screen_p.simulant_p.castable_p.get_type_name_c = get_type_name_title_screen;
    title_screen->screen_p.simulant_p.castable_p.try_cast_c = try_cast_title_screen;
}

// struct gameplay_screen

static const char* get_type_name_gameplay_screen(struct castable* castable)
{
    return "gameplay_screen";
}

static void* try_cast_gameplay_screen(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    if (strcmp(type_name, "simulant") == 0) return castable;
    if (strcmp(type_name, "entity") == 0) return castable;
    if (strcmp(type_name, "gameplay_screen") == 0) return castable;
    return NULL;
}

void initialize_gameplay_screen(struct gameplay_screen* gameplay_screen, const char* name)
{
    initialize_screen(&gameplay_screen->screen_p, name);
    gameplay_screen->screen_p.simulant_p.castable_p.get_type_name_c = get_type_name_gameplay_screen;
    gameplay_screen->screen_p.simulant_p.castable_p.try_cast_c = try_cast_gameplay_screen;
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
    initialize_entity(&world->player_p, "player");
    world->selected_screen_p = &world->title_screen_p.screen_p;
}

void finalize_world(struct world* world)
{
    // nothing to do
}
