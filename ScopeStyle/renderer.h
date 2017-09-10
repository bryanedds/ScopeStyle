#ifndef BGE_RENDERER_H
#define BGE_RENDERER_H

#include <stdbool.h>

#include "error.h"

/// A mock renderer component.
struct renderer
{
    // assume some private implementation
    int implementation_p;
};

/// A mock render message.
struct render_message
{
    // assume some implementation
    int implementation;
};

/// Enqueue a render message.
void add_render_message_renderer(struct render_message* render_message);

/// Render.
void render_renderer(struct renderer* renderer);

/// Initialize the renderer.
void initialize_renderer(struct renderer* renderer, struct error* err);

/// Finalize the renderer.
void finalize_renderer(struct renderer* renderer);

#endif
