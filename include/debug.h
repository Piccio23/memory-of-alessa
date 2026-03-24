#ifndef SH_DEBUG_H
#define SH_DEBUG_H

#define STR(x) #x
#define ASSTR(X) STR(X)

/**
 * A general assertion macro.
 */
#define ASSERT(cond) \
if (!(cond)) { \
    printf(ASSTR(__FILE__) ":" ASSTR(__LINE__) "> assert:(%s)\n", #cond); \
    do {} while (1); \
}

/**
 * Same as ASSERT, but lets you pass in the line number. Useful for matching
 * without fully matching line numbers.
 */
#define ASSERT_ON_LINE(cond, line) \
if (!(cond)) { \
    printf(ASSTR(__FILE__) ":" #line "> assert:(%s)\n", #cond); \
    do {} while (1); \
}

#endif