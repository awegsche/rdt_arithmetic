#pragma once

#include <iostream>

#include <giac/config.h>
#include <giac/giac.h>
#include <giac/unary.h>

using namespace giac;

// global context
inline context CT;

inline const gen ZXP("zxp", &CT);
inline const gen ZXM("zxm", &CT);
inline const gen ZYP("zyp", &CT);
inline const gen ZYM("zym", &CT);
inline const gen HXP("hxp", &CT);
inline const gen HXM("hxm", &CT);
inline const gen HYP("hyp", &CT);
inline const gen HYM("hym", &CT);

inline const gen TWO_I("2*i", &CT);
inline const gen II("i", &CT);
inline const gen EE("e", &CT);

inline const gen BETX("beta_x", &CT);
inline const gen BETY("beta_y", &CT);

inline const gen SBETX("sqrt(beta_x)", &CT);
inline const gen SBETY("sqrt(beta_y)", &CT);

inline const gen COMM_RES("[0,-2*i,0,0,2*i,0,0,0,0,0,0,-2*i,0,0,2*i,0]", &CT);

#define GIAC_UNARY(name, ...) \
    gen name(__VA_ARGS__, const context* ct); \
    gen _##name(const gen& args, const context* ct); \
    extern const unary_function_ptr* const at_##name;

#define IMPL_GIAC_UNARY(name, _size, ...) \
    gen _##name(const gen& args, const context* ct) {\
        if ((args.type != _VECT || args._VECTptr->size() != _size)) \
        {\
            std::cout << "wrong number of args" << std::endl;\
            return gensizeerr(ct); \
        }\
        vecteur& v = *args._VECTptr; \
        return name(__VA_ARGS__, ct); \
    } \
    const std::string _##name##_s(#name); \
    static define_unary_function_eval (__##name, &_##name, _##name##_s); \
    define_unary_function_ptr5(at_##name, alias_at_##name, &__##name, 0, true);
    
