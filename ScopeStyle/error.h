#ifndef BGE_ERROR_H
#define BGE_ERROR_H

#include <stdbool.h>

/// The maximum length of an error message.
#define ERROR_MSG_MAX 1024

/// A simple error-propagation abstraction.
struct error
{
    /// The current error message.
    /// The 'r' suffix denotes that the field is read-only outside of error.h or error.c.
    char msg_r[ERROR_MSG_MAX];

    /// The current error code.
    int code_r;

    /// Is there an active error?
    bool active_r;

    /// Should an incident of an error assert as well? (useful in _DEBUG mode)
    bool assert_as_well_r;
};

/// Declare a fatal error, asserting and then exiting the program.
void fatal_error(const char* msg);

/// Declare that the current error is handled.
void handle_error(struct error* err);

/// Log the current error, then declare that it is handled.
void log_and_handle_error(struct error* err);

/// Propagate a new error in the context of an existing error.
void propagate_error(struct error* err, const char* msg, int code);

/// Declare the incident of a new error.
void raise_error(struct error* err, const char* msg, int code);

/// Initialize the error struct.
void initialize_error(struct error* err, bool assert_as_well);

/// Finalize the error struct.
void finalize_error(struct error* err);

#endif
