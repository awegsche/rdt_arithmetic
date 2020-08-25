#include "giac_setup.h"
#include "brackets.h"

IMPL_GIAC_UNARY(bracket, 4, v[0], v[1], v[2], v[3])
gen bracket(const gen &A, const gen &B, const gen &xA, const gen &xB, const context* ct) {

  auto coeffA = _coeff(makesequence(A, xA), ct);
  auto coeffB = _coeff(makesequence(B, xB), ct);

  // can we safely assume the result of _coeff to be always a vector?
  auto vecA = *coeffA.ref_VECTptr();
  auto vecB = *coeffB.ref_VECTptr();
  auto result = gen(0);

  for (int iA = 0; iA < vecA.size() - 1; iA++)
    for (int iB = 0; iB < vecB.size() - 1; iB++) {
      result = result + gen("2*i", ct) * gen(vecA.size() - iA - 1) *
                            gen(vecB.size() - iB - 1) * vecA[iA] * vecB[iB] *
                            _pow(makesequence(xA, vecA.size() - iA - 2), ct) *
                            _pow(makesequence(xB, vecB.size() - iB - 2), ct);
    }

  return result;
}

gen Brsymb(const gen &A, const gen &B, const gen &xp, const gen &xm,
           const gen &yp, const gen &ym, const context* ct) {
  return bracket(A, B, xm, xp, ct) - bracket(A, B, xp, xm, ct) + bracket(A, B, ym, yp, ct) -
         bracket(A, B, yp, ym, ct);
}

gen BrZ(const gen &A, const gen &B) {
    //log << "[" << A << ", " << B << "]\n";
    return Brsymb(A, B, ZXP, ZXM, ZYP, ZYM, &CT);
}

gen BrH(const gen &A, const gen &B) { return Brsymb(A, B, HXP, HXM, HYP, HYM, &CT); }


IMPL_GIAC_UNARY(br_general, 3, v[0], v[1], v[2])
gen br_general(const gen& A, const gen& B, const gen& coords, const context* ct) {
    gen result{0};
    if (coords.type != gen_unary_types::_VECT) 
        return gentypeerr(ct);
    auto coords_vect = *coords.ref_VECTptr();
    for (const auto& coord : coords_vect) {
        if (coord.type != gen_unary_types::_VECT)
            return gentypeerr(ct);
        auto v = *coord.ref_VECTptr();

        result += Brsymb(A, B, v[0], v[1], v[2], v[3], ct);
    }
    return result;
}