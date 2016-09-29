#ifndef INTERNALS_H

#define INTERNALS_H

typedef char * string_t;

#define ASSERT(expr, ...)   \
    if(!(expr))             \
    {                       \
        return __VA_ARGS__; \
    }

#define ENSURE(expr, ...)   \
    if(!(expr))             \
    {                       \
        return __VA_ARGS__; \
    }

#endif /* end of include guard: INTERNALS_H */
