#include "forced_rdts.h"
using giac::gen;

IMPL_GIAC_UNARY(get_orders, 2, v[0], v[1])
gen get_orders(const gen& A, const gen& factor, const context* ct) {
    auto coeffs = _coeff(makesequence(A, factor), ct);

    return gen(0);
}

IMPL_GIAC_UNARY(get_line, 5, v[0], v[1], v[2], v[3], v[4])
gen get_line(const gen& h, const gen& nx, const gen& ny, const gen& coords, const gen& max_order, const context* ct) {
    if (!is_integer(nx) || !is_integer(ny) || !is_integer(max_order)) return gentypeerr(ct);
    if(coords.type != gen_unary_types::_VECT) return gentypeerr(ct);

    auto coordinates = *coords.ref_VECTptr();
    int max_ = max_order.to_int();

    gen result;

    for (int j = 0; j < max_; j++)
        for (int k = 0; k < max_; k++)
            for (int l = 0; l < max_; l++)
                for (int m = 0; m < max_; m++)
                    if (j - k == nx.to_int() && l - m == ny.to_int()) {
                        auto nz_coeff = _coeff(makesequence(h, coordinates[0], j), ct);
                        nz_coeff = _coeff(makesequence(nz_coeff, coordinates[1], k), ct);
                        nz_coeff = _coeff(makesequence(nz_coeff, coordinates[2], l), ct);
                        result += _coeff(makesequence(nz_coeff, coordinates[3], m), ct);
                    }
    return result;
}


IMPL_GIAC_UNARY(make_F_orders, 5, v[0], v[1], v[2], v[3],v[4])
gen make_F_orders(const gen& j, const gen& k, const gen& l, const gen& m, const gen& coords, const context* ct) {

    if (!is_integer(j) || !is_integer(k) || !is_integer(l) || !is_integer(m)) return gentypeerr(ct);
    if(coords.type != gen_unary_types::_VECT) return gentypeerr(ct);

    auto _j = j.to_int();
    auto _k = k.to_int();
    auto _l = l.to_int();
    auto _m = m.to_int();

    char buffer[16];

    sprintf(buffer, "f%d%d%d%d", _j, _k, _l, _m);
    return gen(buffer, ct) * _pow(makesequence(coords[0], j), ct)
                           * _pow(makesequence(coords[1], k), ct)
                           * _pow(makesequence(coords[2], l), ct)
                           * _pow(makesequence(coords[3], m), ct);

}

IMPL_GIAC_UNARY(make_F, 2, v[0], v[1])
gen make_F(const gen& orders, const gen& coords, const context* ct) {

    if(coords.type != gen_unary_types::_VECT) return gentypeerr(ct);
    if(orders.type != gen_unary_types::_VECT) return gentypeerr(ct);
    gen result{0};

    for (auto& order : *orders.ref_VECTptr()) {
        if (order.type != gen_unary_types::_VECT) return gentypeerr(ct);
        result += make_F_orders(order[0], order[1], order[2], order[3], coords, ct);
    }
    return result;
}

IMPL_GIAC_UNARY(make_full_F, 2, v[0], v[1])
gen make_full_F(const gen& max_order, const gen& coords, const context* ct) {

    if (!is_integer(max_order)) return gentypeerr(ct);
    int _max = max_order.to_int();
    std::cout << _max << std::endl;
  giac::gen F{0};

  for (int j = 0; j < _max; j++)
    for (int k = 0; k < _max; k++)
        for (int l = 0; l < _max; l++)
            for (int m = 0; m < _max; m++)
            {
                if (j+k+l+m > 1 && j+k+l+m < _max && (j!=k || l!=m)) {
                F += make_F_orders(
                    gen{j}, gen{k}, gen{l}, gen{m},
                    coords,
                    ct);
                }
                //std::cout << "intermediate F: " << F << std::endl;
            }

    return F;

}