
#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "resource.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* --- Game Entity --- */
enum EntityFlags
{
    ENTITY_PLAYER = COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_INPUT | COMPONENT_SPRITE
};

bool CreatePlayer(struct World *world, Entity *entity)
{
    if (CreateEntity(world, entity)) {
        world->entity[*entity] = ENTITY_PLAYER;
        world->position[*entity].x = 0.0f;
        world->position[*entity].y = 0.0f;
        return true;
    }

    return false;
}

/* --- Game System --- */
enum SystemFlags
{
    SYSTEM_INPUT = COMPONENT_INPUT | COMPONENT_VELOCITY,
    SYSTEM_MOVEMENT = COMPONENT_POSITION | COMPONENT_VELOCITY,
    SYSTEM_RENDER = COMPONENT_POSITION | COMPONENT_SPRITE
};

void InputSystem(struct World *world, GLFWwindow *window)
{
    struct Input *input;
    struct Velocity *velocity;

    for (Entity i = 0; i < MAX_ENTITY; ++i) {
        if ((world->entity[i] & SYSTEM_INPUT) == SYSTEM_INPUT) {
            input = &(world->input[i]);
            velocity = &(world->velocity[i]);

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                input->x = -1.0f;
            }
            else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                input->x = 1.0f;
            }
            else {
                input->x = 0.0f;
            }

            velocity->x *= (input->x * 30.0f);
        }
    }
}

void MovementSystem(struct World *world, float delta)
{
    struct Position *position;
    struct Velocity *velocity;
    
    for (Entity i = 0; i < MAX_ENTITY; ++i) {
        if ((world->entity[i] & SYSTEM_MOVEMENT) == SYSTEM_MOVEMENT) {
            position = &(world->position[i]);
            velocity = &(world->velocity[i]);

            /* position->y += (9.8f * delta); */

            position->x += velocity->x;
            position->y += velocity->y;
        }
    }
}

void RenderSystem(struct World *world)
{
    struct Sprite *sprite;
    struct Position *position;

    for (Entity i = 0; i < MAX_ENTITY; ++i) {
        if ((world->entity[i] & SYSTEM_RENDER) == SYSTEM_RENDER) {
            sprite = &(world->sprite[i]);
            position = &(world->position[i]);

            //Render sprite algorithm here..
        }
    }
}

#endif

