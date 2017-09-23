#ifndef BGE_CASTABLE_H
#define BGE_CASTABLE_H

#include <stdbool.h>

#include "error.h"

///////////////////////////////////////////////////////////////////////////////
/// The category of abstractions with sub-typing.
///
/// Additional categories include -
///
/// reflectable & propertied (see ax C++ project),
/// iterable,
/// functor,
/// applicative,
/// alternative,
/// monoid,
/// foldable,
/// traversable,
/// and so on.
///////////////////////////////////////////////////////////////////////////////
struct castable;

const char* get_type_name(struct castable*);
void* try_cast(struct castable*, const char*);
void* cast(struct castable*, const char*);
bool try_copy_to(struct castable*, struct castable*);
bool equal_to(struct castable*, struct castable*);
int hash(struct castable*);

struct castable
{
    int castable_tag_p;
    const char* (*get_type_name_p)(struct castable*);
    void* (*try_cast_p)(struct castable*, const char*);
    bool (*try_copy_to_p)(struct castable*, struct castable*);
    bool (*equal_to_p)(struct castable*, struct castable*);
    int (*hash_p)(struct castable*);
};

void initialize_castable_6(
    struct castable* castable,
    const char* (*get_type_name)(struct castable*),
    void* (*try_cast)(struct castable*, const char*),
    bool (*try_copy_to)(struct castable*, struct castable*),
    bool (*equal_to)(struct castable*, struct castable*),
    int (*hash)(struct castable*));

void initialize_castable(
    struct castable* castable,
    const char* (*get_type_name)(struct castable*),
    void* (*try_cast)(struct castable*, const char*));

#define CASTABLE_TAG 0xAB3A3854 // CRC32 hash of 'castable'

///////////////////////////////////////////////////////////////////////////////
/// Casting utility functions.
///////////////////////////////////////////////////////////////////////////////

/// A weak check for dynamically casting to castable*.
bool is_castable(void* ptr);

/// Up-cast any castable to the expected pointer type.
/// Should be statically-verifiable when using a custom static code analysis rule.
void* up_cast(void* ptr);

/// Short-hand for up_cast.
inline void* uc(void* ptr) { return up_cast(ptr); }

/// Hashes a pointer.
int hash_ptr(void* ptr);

#endif
