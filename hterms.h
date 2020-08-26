#pragma once
#include <iostream>
#include "giac_setup.h"
#include <vector>
using giac::gen;

using std::ostream, std::vector;

struct RdtIndex {
  int j, k, l, m;
};

ostream& operator<<(ostream& os, const RdtIndex& i);

class Hijkl {
public:
    static gen to_gen(const RdtIndex& term, char id);
};

class Hsymb {
public:
    static gen to_gen(const RdtIndex& term, char id) {
    char buffer[32];
    sprintf(buffer, "h_%d%d%d%d_%c", term.j, term.k, term.l, term.m, id);
    return gen(buffer, &CT);
    }
};

template <typename Hterm>
gen hamiltonian(const vector<RdtIndex> &terms, char id) {
  gen result(0);
  char buffer_phix[16];
  char buffer_phiy[16];
  sprintf(buffer_phix, "phi_x%c", id);
  sprintf(buffer_phiy, "phi_y%c", id);
  for (auto term : terms) {
    gen h = Hterm::to_gen(term, id);
    gen exponent = (term.j - term.k) * gen(buffer_phix, &CT) +
                   (term.l - term.m) * gen(buffer_phiy, &CT);
    result = result + _simplify(h * _pow(makesequence(EE, exponent * II), &CT) *
                                    _pow(makesequence(HXP, term.j), &CT) *
                                    _pow(makesequence(HXM, term.k), &CT) *
                                    _pow(makesequence(HYP, term.l), &CT) *
                                    _pow(makesequence(HYM, term.m), &CT),
                                &CT);
  }

  return result;
}

GIAC_UNARY(hamil, const gen &terms, const gen& id)

//gen h_from_z(const gen &F, const gen &z, int order);
GIAC_UNARY(h_from_z, const gen& F, const gen& z, const gen& order, const gen& coords, const gen& commutators)

//gen get_coord_term(const gen &H, int j, int k, int l, int m);
GIAC_UNARY(get_coord_term, const gen& H, const gen& j, const gen& k, const gen& l, const gen& m)

gen get_2nd_order_terms(const vector<RdtIndex> &first_order_terms);
//GIAC_UNARY(get_2nd_order_terms, const vector)