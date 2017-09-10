#ifndef BGE_CATEGORY_H
#define BGE_CATEGORY_H

#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////
/// Exposes abstraction categories via dynamic dispatching such as -
/// equatable (including hashing and potential copying)
/// castable,
/// reflectable,
/// copyable,
/// iterable,
/// functor,
/// foldable,
/// traversable,
/// and so on.
///////////////////////////////////////////////////////////////////////////////

/// The category of abstractions that can be compared for equality, potentially copied, and hashed.
struct equatable;
bool equal_to(struct equatable*, struct equatable*);
bool try_copy_to(struct equatable*, struct equatable*);
int hash(struct equatable*);
void initialize_equatable(struct equatable*);
struct equatable
{
    bool (*equal_to_c)(struct equatable*, struct equatable*);
    bool (*try_copy_to_c)(struct equatable*, struct equatable*);
    int (*hash_c)(struct equatable*);
};

/// The category of abstractions with dynamic sub-typing.
struct castable;
const char* get_type_name(struct castable*);
void* try_cast(struct castable*, const char*);
void* cast(struct castable*, const char*);
void initialize_castable(struct castable*);
struct castable
{
    struct equatable equatable;
    const char* (*get_type_name_c)(struct castable*);
    void* (*try_cast_c)(struct castable*, const char*);
};

///////////////////////////////////////////////////////////////////////////////
/// Utility functions. TODO: find a better place for this.
///////////////////////////////////////////////////////////////////////////////

/// Hashes a pointer.
int hash_ptr(void* ptr);

#endif
