#include "hterms.h"
#include "brackets.h"

using std::endl;

ostream& operator<<(ostream& os, const RdtIndex& i) {
    return os << i.j << i.k << i.l << i.m;
}

gen Hijkl::to_gen(const RdtIndex &term, char id) {
  auto j = term.j;
  auto k = term.k;
  auto l = term.l;
  auto m = term.m;
  auto n = j + k + l + m;

  char buffer[16];
  sprintf(buffer, "K_%d%c", n - 1, id);
  char buffer2[128];
  sprintf(buffer2, "%d!*%d!*%d!*%d!*2^%d", j, k, l, m, j + k + l + m);

  return _simplify(-gen(buffer, &CT) * _pow(makesequence(II, l + m), &CT) *
                       _pow(makesequence(SBETX, (j + k)), &CT) *
                       _pow(makesequence(SBETY, (l + m)), &CT) /
                       _simplify(gen(buffer2, &CT), &CT),
                   &CT);
}

gen _h_from_z(const gen& args, const context* ct) {
    if (args.type != _VECT) 
    {
        std::cout << "wrong number of args" << std::endl;
        return gensizeerr(ct);
    }
    vecteur& v = *args._VECTptr;
    if (v.size() == 4)
        return h_from_z(v[0], v[1], v[2], v[3], COMM_RES, ct);
    else if (v.size() == 5)
        return h_from_z(v[0], v[1], v[2], v[3], v[4], ct);
    else 
        return gensizeerr("wrong number of arguments");
}
const std::string _h_from_z_s("h_from_z"); 
static define_unary_function_eval (__h_from_z, &_h_from_z, _h_from_z_s);
define_unary_function_ptr5(at_h_from_z, alias_at_h_from_z, &__h_from_z, 0, true);

gen h_from_z(const gen &F, const gen &z, const gen& order, const gen& coords, const gen& commutators,
    const context* ct) {
    //log << "calculating h from z\n"
    //    << "F = " << F << "\n"
    //    << "z = " << z << "\n";
  auto h = gen(z);
  auto brack = gen(z);
  for (int index = 0; index < order; index++) {
    brack = _simplify(cost_bracket(F, brack, coords, commutators, ct), ct);
    h = h + brack;
  }

    //log << "h = " << h << endl;
  return h;
}

IMPL_GIAC_UNARY(get_coord_term, 5, v[0], v[1], v[2], v[3], v[4])
gen get_coord_term(const gen &H, const gen& j, const gen& k, const gen& l, const gen& m, const context* ct) {
    if (!(is_integer(j) && is_integer(k) && is_integer(l) && is_integer(m)))
        return gentypeerr(ct);
  auto hxp_coeff = _coeff(makesequence(H, HXP, j), ct);
  auto hxm_coeff = _coeff(makesequence(hxp_coeff, HXM, k), ct);
  auto hyp_coeff = _coeff(makesequence(hxm_coeff, HYP, l), ct);
  return _simplify(_coeff(makesequence(hyp_coeff, HYM, m), ct), ct);
}

IMPL_GIAC_UNARY(hamil, 2, v[0], v[1])
gen hamil(const gen& terms, const gen& id, const context* ct) {
    //if()
    //return hamiltonian<Hijkl>()
    return gen(0);
}

gen get_2nd_order_terms(const vector<RdtIndex> &first_order_terms) {
  auto Hw = hamiltonian<Hsymb>(first_order_terms, 'w');
  auto Hu = hamiltonian<Hsymb>(first_order_terms, 'u');

  auto H2 = _simplify(BrH(Hw, Hu), &CT);

  for (int j : {0, 1, 2})
    for (int k : {0, 1, 2})
      if (j + k > 0) {

        auto term = get_coord_term(H2, j, k, 0, 0, &CT);
        //log << "H_" << j << k << "00 = " << term << endl;
      }
  return H2;
}