
#define MSTR(x) stringify(x) // Stringify a macro
#if defined __clang__
#define COMPILER_STR "CLANG " __clang_version__
#elif defined __GNUC__
#define COMPILER_STR "GCC " MSTR(__GNUC__) "." MSTR(__GNUC_MINOR__) "." MSTR(__GNUC_PATCHLEVEL__)
#elif defined _MSC_VER
#define COMPILER_STR "MSC " MSTR(_MSC_FULL_VER)
#else
#define COMPILER_STR "UNKNOWN COMPILER"
#endif

#define SMARTMHA_VERSION "v1.0.0"

#ifndef NDEBUG
#define SMARTMHA_VERSION_STR "smartmha " SMARTMHA_VERSION " (debug)" " (" COMPILER_STR ")"
#else
#define SMARTMHA_VERSION_STR "smartmha " SMARTMHA_VERSION " (" COMPILER_STR ")"
#endif