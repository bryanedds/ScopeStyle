#include "error.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void clear_error(struct error* err)
{
    err->msg_r[0] = '\0';
    err->code_r = 0;
    err->active_r = false;
}

static void populate_error(struct error* err, const char* msg, int code)
{
    strncpy(err->msg_r, msg, ERROR_MSG_MAX);
    err->code_r = code;
    err->active_r = true;
}

void fatal_error(const char* msg)
{
    assert(false && msg);
    exit(EXIT_FAILURE);
}

void handle_error(struct error* err)
{
    if (!err->active_r) assert(false && "No error to handle!");
    clear_error(err);
}

void log_and_handle_error(struct error* err)
{
    if (!err->active_r) assert(false && "No error to handle!");
    // TODO: log error.
    clear_error(err);
}

void propagate_error(struct error* err, const char* msg, int code)
{
    if (!err->active_r) assert(false && "No error to propagate!");
    if (err->assert_as_well_r) assert(false && msg);
    populate_error(err, msg, code);
}

void raise_error(struct error* err, const char* msg, int code)
{
    if (err->active_r) assert(false && "Error already raised!");
    if (err->assert_as_well_r) assert(false && msg);
    populate_error(err, msg, code);
}

void initialize_error(struct error* err, bool assert_as_well)
{
    clear_error(err);
    err->assert_as_well_r = assert_as_well;
}

void finalize_error(struct error* err)
{
    // nothing to do
}
