
#pragma once
#include <iostream>
#include "giac_setup.h"
#include <vector>
using giac::gen;

GIAC_UNARY(get_orders, const gen& A, const gen& factor)

GIAC_UNARY(get_line, const gen& h, const gen& nx, const gen& ny, const gen& coords, const gen& max_order)

GIAC_UNARY(make_F_orders, const gen& j, const gen& k, const gen& l, const gen& m, const gen& coords)

GIAC_UNARY(make_F, const gen& orders, const gen& coords)

GIAC_UNARY(make_full_F, const gen& max_order, const gen& coords)