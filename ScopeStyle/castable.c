#include "castable.h"

#include <string.h>

#include "error.h"

///////////////////////////////////////////////////////////////////////////////
/// The category of abstractions with sub-typing.
///////////////////////////////////////////////////////////////////////////////

static const char* get_type_name_castable(struct castable* castable)
{
    return "castable";
}

static void* try_cast_castable(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "castable") == 0) return castable;
    return NULL;
}

bool try_copy_to_castable(struct castable* left, struct castable* right)
{
    return false;
}

bool equal_to_castable(struct castable* left, struct castable* right)
{
    return left == right;
}

int hash_castable(struct castable* castable)
{
    return hash_ptr(castable);
}

const char* get_type_name(struct castable* castable)
{
    return castable->castable_fns_p->get_type_name_p(castable);
}

void* try_cast(struct castable* castable, const char* type_name)
{
    return castable->castable_fns_p->try_cast_p(castable, type_name);
}

void* cast(struct castable* castable, const char* type_name)
{
    void* result = try_cast(castable, type_name);
    if (castable == NULL) fatal_error("Invalid cast.");
    return result;
}

bool try_copy_to(struct castable* left, struct castable* right)
{
    return left->castable_fns_p->try_copy_to_p(left, right);
}

bool equal_to(struct castable* left, struct castable* right)
{
    return left->castable_fns_p->equal_to_p(left, right);
}

int hash(struct castable* castable)
{
    return castable->castable_fns_p->hash_p(castable);
}

void initialize_castable(struct castable* castable, struct castable_fns* castable_fns)
{
    castable->castable_tag_p = CASTABLE_TAG;
    castable->castable_fns_p = castable_fns;
}

///////////////////////////////////////////////////////////////////////////////
/// Casting utility functions.
///////////////////////////////////////////////////////////////////////////////

bool is_castable(void* ptr)
{
    return ((struct castable*)ptr)->castable_tag_p == CASTABLE_TAG;
}

void* up_cast(void* ptr)
{
    if (!is_castable(ptr)) fatal_error("Target for up-cast was not castable.");
    return ptr;
};

int hash_ptr(void* ptr)
{
    long long hash_long = (long long)ptr;
    int hash_int = (int)hash_long ^ (int)(hash_long << sizeof(int));
    return hash_int;
}
