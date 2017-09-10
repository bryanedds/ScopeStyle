#include "category.h"

#include <string.h>

#include "error.h"

// struct equatable

static bool equal_to_equatable(struct equatable* left, struct equatable* right)
{
    return left == right;
}

static bool try_copy_to_equatable(struct equatable* left, struct equatable* right)
{
    return false;
}

static int hash_equatable(struct equatable* equatable)
{
    return hash_ptr(equatable);
}

bool equal_to(struct equatable* left, struct equatable* right)
{
    return left->equal_to_c(left, right);
}

bool try_copy_to(struct equatable* left, struct equatable* right)
{
    return left->try_copy_to_c(left, right);
}

int hash(struct equatable* equatable)
{
    return equatable->hash_c(equatable);
}

void initialize_equatable(struct equatable* equatable)
{
    equatable->equal_to_c = equal_to_equatable;
    equatable->hash_c = hash_equatable;
}

// struct castable

static const char* get_type_name_castable(struct castable* _)
{
    return "castable";
}

static void* try_cast_castable(struct castable* castable, const char* type_name)
{
    if (strcmp(type_name, "equatable") == 0) return castable;
    if (strcmp(type_name, "castable") == 0) return castable;
    return NULL;
}

const char* get_type_name(struct castable* castable)
{
    return castable->get_type_name_c(castable);
}

void* try_cast(struct castable* castable, const char* type_name)
{
    return castable->try_cast_c(castable, type_name);
}

void* cast(struct castable* castable, const char* type_name)
{
    void* result = try_cast(castable, type_name);
    if (castable == NULL) fatal_error("Invalid cast.");
    return result;
}

void initialize_castable(struct castable* castable)
{
    initialize_equatable(&castable->equatable_p);
    castable->get_type_name_c = get_type_name_castable;
    castable->try_cast_c = try_cast_castable;
}

// utility functions

int hash_ptr(void* ptr)
{
    long long hash_long = (long long)ptr;
    int hash_int = (int)hash_long ^ (int)(hash_long << sizeof(int));
    return hash_int;
}
