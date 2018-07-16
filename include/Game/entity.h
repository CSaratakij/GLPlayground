
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_ENTITY 10
typedef unsigned int Entity;

/* --- Components --- */
enum ComponentFlags
{
    COMPONENT_EMPTY = 0,
    COMPONENT_POSITION = 1,
    COMPONENT_VELOCITY = 1 << 1,
    COMPONENT_INPUT = 1 << 2,
    COMPONENT_SPRITE = 1 << 3
};

struct Position
{
    float x;
    float y;
};

struct Velocity
{
    float x;
    float y;
};

struct Input
{
    float x;
    float y;
};

struct Sprite
{
};

/* --- World --- */
struct World
{
    Entity entity[MAX_ENTITY];
    struct Position position[MAX_ENTITY];
    struct Velocity velocity[MAX_ENTITY];
    struct Input input[MAX_ENTITY];
    struct Sprite sprite[MAX_ENTITY];
};

/* --- Component Default Value --- */
const struct Position DEFAULT_POSITION = { 0.0f, 0.0f };
const struct Velocity DEFAULT_VELOCITY = { 0.0f, 0.0f };
const struct Input DEFAULT_INPUT = { 0.0f, 0.0f };
const struct Sprite DEFAULT_SPRITE = {};

void InitWorld(struct World *world)
{
    for (unsigned int i = 0; i < MAX_ENTITY; ++i) {
        world->position[i] = DEFAULT_POSITION;
        world->velocity[i] = DEFAULT_VELOCITY;
        world->input[i] = DEFAULT_INPUT;
        world->sprite[i] = DEFAULT_SPRITE;
    }
}

bool CreateEntity(struct World *world, Entity *entity)
{
    for (Entity i = 0; i < MAX_ENTITY; ++i) {
        if ((world->entity[i] | COMPONENT_EMPTY) == COMPONENT_EMPTY) {
            *entity = i;
            return true;
        }
    }

    return false;
}

bool RemoveEntity(struct World *world, Entity entity)
{
    if (entity < MAX_ENTITY) {
        world->entity[entity] = COMPONENT_EMPTY;
        return true;
    }

    return false;
}

#endif

