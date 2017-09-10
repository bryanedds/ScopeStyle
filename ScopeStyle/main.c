#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "malloc_safe.h"
#include "error.h"
#include "renderer.h"
#include "physics_engine.h"
#include "world.h"

int main(int argc, char* argv)
{
    // determine assertions on error based on build type
    bool assert_on_error =
#if _DEBUG
        true;
#else
        false;
#endif

    // initialize error, components, and world
    struct error err;
    initialize_error(&err, assert_on_error);
    {
        struct renderer renderer;
        initialize_renderer(&renderer, &err);
        if (err.active_r) log_and_handle_error(&err), finalize_renderer(&renderer);
        else
        {
            struct physics_engine physics_engine;
            initialize_physics_engine(&physics_engine, &err);
            if (err.active_r) log_and_handle_error(&err), finalize_physics_engine(&physics_engine);
            else
            {
                struct world world;
                initialize_world(&world, &renderer, &physics_engine, &err);
                if (err.active_r) log_and_handle_error(&err), finalize_world(&world);
                else
                {
                    // update world a bunch of times
                    for (int i = 0; i < 100; ++i)
                    {
                        update_world(&world, &err);
                        if (err.active_r)
                        {
                            log_and_handle_error(&err);
                            break;
                        }
                    }
                }
                finalize_world(&world);
            }
            finalize_physics_engine(&physics_engine);
        }
        finalize_renderer(&renderer);
    }
    finalize_error(&err);

    // great success!
    return EXIT_SUCCESS;
}
