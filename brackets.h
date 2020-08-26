#pragma once
#include <giac/giac.h>
#include <giac_setup.h>

GIAC_UNARY(bracket, const gen &A, const gen &B, const gen &xA, const gen &xB, const gen &res)

GIAC_UNARY(cost_bracket, const gen &A, const gen &B, const gen &coords, const gen &commutators)

GIAC_UNARY(def_comms, const gen &coords, const gen& commutatorlist)

gen Brsymb(const gen &A, const gen &B, const gen &xp, const gen &xm,
           const gen &yp, const gen &ym, const context* ct);

gen BrZ(const gen &A, const gen &B);

gen BrH(const gen &A, const gen &B);

GIAC_UNARY(br_general, const gen& A, const gen& B, const gen& coords)