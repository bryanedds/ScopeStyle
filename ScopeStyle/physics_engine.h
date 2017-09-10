#ifndef BGE_PHYSICS_ENGINE_H
#define BGE_PHYSICS_ENGINE_H

#include <stdbool.h>

#include "error.h"

/// A mock physics engine component.
struct physics_engine
{
    // assume some private implementation
    int implementation_p;
};

/// Integrate physics by one frame.
void integrate_physics_engine(struct physics_engine* physics_engine);

/// Initialize the physics engine.
void initialize_physics_engine(struct physics_engine* physics_engine, struct error* err);

/// Finalize the physics engine.
void finalize_physics_engine(struct physics_engine* physics_engine);

#endif
