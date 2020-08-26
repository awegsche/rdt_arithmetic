
#include "giac_setup.h"
#include "brackets.h"


IMPL_GIAC_UNARY(bracket, 5, v[0], v[1], v[2], v[3], v[4])
gen bracket(const gen &A, const gen &B, const gen &xA, const gen &xB, const gen &res, const context* ct) {

  auto coeffA = _coeff(makesequence(A, xA), ct);
  auto coeffB = _coeff(makesequence(B, xB), ct);

  // can we safely assume the result of _coeff to be always a vector?
  auto vecA = *coeffA.ref_VECTptr();
  auto vecB = *coeffB.ref_VECTptr();
  auto result = gen(0);

  for (int iA = 0; iA < vecA.size() - 1; iA++)
    for (int iB = 0; iB < vecB.size() - 1; iB++) {
      result = result + res * gen(vecA.size() - iA - 1) *
                            gen(vecB.size() - iB - 1) * vecA[iA] * vecB[iB] *
                            _pow(makesequence(xA, vecA.size() - iA - 2), ct) *
                            _pow(makesequence(xB, vecB.size() - iB - 2), ct);
    }

  return result;
}

gen Brsymb(const gen &A, const gen &B, const gen &xp, const gen &xm,
           const gen &yp, const gen &ym, const context* ct) {
  return bracket(A, B, xm, xp, gen("2*i", ct), ct) - bracket(A, B, xp, xm, gen("2*i", ct), ct)
    + bracket(A, B, ym, yp, gen("2*i", ct), ct) - bracket(A, B, yp, ym, gen("2*i", ct), ct);
}

IMPL_GIAC_UNARY(def_comms, 2, v[0], v[1])
gen def_comms(const gen &coords, const gen& commutatorlist, const context* ct) {
    if (coords.type != gen_unary_types::_VECT)
        return gentypeerr("coords must be a vector of coordinate symbols");
    if (commutatorlist.type != gen_unary_types::_VECT)
        return gentypeerr("commutators must be a vector of commutator results");
    auto commutator_vec = commutatorlist.ref_VECTptr();
    auto coords_vec = coords.ref_VECTptr();

    auto comms = makevecteur(0);
    auto n = coords_vec->size();
    for (int i = 1; i < n*n; i++)
        comms.push_back(0);


    for (auto com: *commutator_vec) {
        if (com.type != gen_unary_types::_VECT)
            return gentypeerr("the entries of the commutatorlist must be vectors [coordA, coordB, result]");
        auto com_vec = com.ref_VECTptr();
        for (int i = 0; i < n; i++) {
            if ((*coords_vec)[i] == (*com_vec)[0]) {
                for (int j = 0; j < n; j++) {
                    if ((*coords_vec)[j] == (*com_vec)[1]) {
                        comms[i*n+j] = (*com_vec)[2];
                        break;
                    }
                }
                break;
            }
        }
    }

    return comms;
}

IMPL_GIAC_UNARY(cost_bracket, 4, v[0], v[1], v[2], v[3])
gen cost_bracket(const gen &A, const gen &B, const gen& coords, const gen& commutators, const context* ct) {
    if (coords.type != gen_unary_types::_VECT)
        return gentypeerr("coords must be a vector of coordinate symbols");
    if (commutators.type != gen_unary_types::_VECT)
        return gentypeerr("commutators must be a vector of commutator results");
    auto &coord_vec = *coords.ref_VECTptr();
    auto &comm_vec = *commutators.ref_VECTptr();
    auto n = coord_vec.size();
    gen ret{0};
    if (comm_vec.size() != n*n) 
    {
        char buf[256];
        std::snprintf(buf, 256, "for n coords we need n^2 commutators, n=%ld, got %ld", n, comm_vec.size());
        return gentypeerr(buf);
    }
    for (int j =0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            ret += bracket(A, B, coord_vec[i], coord_vec[j], comm_vec[j*n+i], ct);
        }
    } 
    return ret;
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