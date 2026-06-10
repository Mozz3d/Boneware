#pragma once

#define MACRO_OVERLOAD_EXPAND(x) x
#define MACRO_OVERLOAD_PICK(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define MACRO_OVERLOAD(base, ...) \
    MACRO_OVERLOAD_EXPAND( \
        MACRO_OVERLOAD_PICK(__VA_ARGS__, \
            base##_8, base##_7, base##_6, base##_5, \
            base##_4, base##_3, base##_2, base##_1) \
        (__VA_ARGS__))