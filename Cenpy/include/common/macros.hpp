#define PARENS () // Note space before (), so object-like macro

#define EXPAND(arg) EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg) EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg) EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg) EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg) arg

#define FOR_EACH(macro, ...) \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...) \
    macro(a1)                           \
        __VA_OPT__(FOR_EACH_AGAIN PARENS(macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define FOR_EACH_1_FIX_ARG(macro, T, ...) \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER_1_FIX_ARG(macro, T, __VA_ARGS__)))
#define FOR_EACH_HELPER_1_FIX_ARG(macro, T, a1, ...) \
    macro(T, a1)                                     \
        __VA_OPT__(FOR_EACH_AGAIN_1_FIX_ARG PARENS(macro, T, __VA_ARGS__))
#define FOR_EACH_AGAIN_1_FIX_ARG() FOR_EACH_HELPER_1_FIX_ARG

#define COMMA ,
