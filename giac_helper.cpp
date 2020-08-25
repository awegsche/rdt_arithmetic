#include "giac_helper.h"

using std::string;

const size_t MAX_OUT = 2048;

std::map<unsigned int, std::string> gen_types_map =  {
    // immediate type (without mem allocation) should be < _ZINT
    {0, "_INT_"}, // int val
    {1, "_DOUBLE_"}, // double _DOUBLE_val
    // all type below or equal to _DOUBLE_ must be non pointers
    {2, "_ZINT"}, // mpz_t * _ZINTptr
    {3, "_REAL"}, // mpf_t * _REALptr
    // all type strictly below _CPLX must be real types
    {4, "_CPLX"}, // gen * _CPLXptr
    {5, "_POLY"}, // polynome * _POLYptr
    {6, "_IDNT"}, // identificateur * _IDNTptr
    {7, "_VECT"}, // vecteur * _VECTptr
    {8, "_SYMB"}, // symbolic * _SYMBptr
    {9, "_SPOL1"}, // sparse_poly1 * _SPOL1ptr
    {10, "_FRAC"}, // fraction * _FRACptr
    {11, "_EXT"}, // gen * _EXTptr
    {12, "_STRNG"}, // string * _STRNGptr
    {13, "_FUNC"}, // unary_fonction_ptr * _FUNCptr
    {14, "_ROOT"}, // real_complex_rootof *_ROOTptr
    {15, "_MOD"}, // gen * _MODptr
    {16, "_USER"}, // gen_user * _USERptr
    {17, "_MAP"}, // map<gen.gen> * _MAPptr
    {18, "_EQW"}, // eqwdata * _EQWptr
    {19, "_GROB"}, // grob * _GROBptr
    {20, "_POINTER_"}, // void * _POINTER_val
    {21, "_FLOAT_"} // immediate, _FLOAT_val
  } ;

std::map<unsigned int, std::string> gen_subtypes_map =  {
    {1, "_SEQ__VECT"},
    {2, "_SET__VECT"},
    {3, "_RPN_FUNC__VECT"},
    {4, "_RPN_STACK__VECT"},
    {5, "_GROUP__VECT"},
    {6, "_LINE__VECT"},
    {7, "_VECTOR__VECT"},
    {8, "_PNT__VECT"},
    {8, "_CURVE__VECT"},
    {9, "_HALFLINE__VECT"},
    {10, "_POLY1__VECT"},
    {11, "_MATRIX__VECT"},
    {12, "_RUNFILE__VECT"},
    {13, "_ASSUME__VECT"},
    {14, "_SPREAD__VECT"},
    {15, "_CELL__VECT"},
    {16, "_EQW__VECT"},
    {17, "_HIST__VECT"},
    {0, "_TILIST__VECT"},
    {18, "_FOLDER__VECT"},
    {19, "_SORTED__VECT"},
    {20, "_POINT__VECT"},
    {21, "_POLYEDRE__VECT"},
    {22, "_RGBA__VECT"},
    {23, "_LIST__VECT"},
    {24, "_LOGO__VECT"},
    {25, "_GGB__VECT"},
    {26, "_INTERVAL__VECT"},
    {27, "_GGBVECT"},
    {28, "_PRINT__VECT"},
    {29, "_TUPLE__VECT"},
    {30, "_TABLE__VECT"},
    {31, "_GRAPH__VECT"},
    {32, "_PRG__VECT"},
};

namespace colors {
string Symb{"\33[38;2;128;128;255m"};
string Op{"\33[38;2;255;128;128m"};
string Reset{"\33[0m"};
}


std::ostream& operator<<(std::ostream& os, const GenDebug& gd) {


    os << indentendl{gd._indent} << "\33[38;2;128;128;128m"
        << gen_types_map[gd.__g->type] << ":\33[38;2;128;128;160m"
        << gen_subtypes_map[gd.__g->subtype]
        <<  "\33[0m ";
    switch (gd.__g->type) {
    case giac::gen_unary_types::_VECT:
    {
        os << indentendl{gd._indent} << "{\n";
        auto vec = *gd.__g->ref_VECTptr();
        for (int i = 0; i < vec.size(); i++) {
            os  << GenDebug(vec[i], gd._indent+2) << ",\n";
            if (os.tellp() > MAX_OUT) {
                os << "...\n";
                break;
            }

        }
        os << indentendl{gd._indent} << "}\n";
        break;
    }
    case giac::gen_unary_types::_SYMB:
    {
        giac::symbolic symb = *gd.__g->ref_SYMBptr();

        os << GenDebug(symb.sommet, gd._indent + 2) << ",\n";
        os << GenDebug(symb.feuille, gd._indent + 2) << ",\n";
        break;
    }
    default:
        os  << *gd.__g ;
    }
    return os;
}

std::string GenDisplay::display() const {
    std::stringstream s{};
    switch (__g->type) {
        case giac::gen_unary_types::_IDNT:
        {
            s << colors::Symb << *__g << colors::Reset; // f 
            break;
        }
        case giac::gen_unary_types::_SYMB:
        {
            auto symb = __g->ref_SYMBptr();
            const char* name = symb->sommet._ptr->s;

            if (name[1] == '\0') {
                int new_level = 0;
                if (name[0] == '*' || name[0] == '/') new_level = 2;
                if (name[0] == '-') new_level = 1;
                if (new_level < _level)
                    s << "(";
                switch(symb->feuille.type){
                case giac::gen_unary_types::_VECT: {
                    auto feuille = *symb->feuille.ref_VECTptr();
                    s <<  GenDisplay(feuille[0], new_level).display();
                    for (int i = 1; i < feuille.size(); i++) 
                        s << colors::Op << name << colors::Reset
                            << GenDisplay(feuille[i], new_level).display();
                    break;
                }
                case giac::gen_unary_types::_SYMB: {
                    s << name << GenDisplay(symb->feuille, new_level).display();
                    break;
                }
                case giac::gen_unary_types::_IDNT: {
                    s << "(" << name << GenDisplay(symb->feuille, new_level).display() << ")";
                    break;
                }
                default:
                    s << GenDebug(symb->feuille, new_level);
                    break;
                }
                
                if (new_level < _level)
                    s << ")";
            }
            else {
                s << colors::Op << __g->ref_SYMBptr()->sommet._ptr->s << "\33[0m(";
                s << GenDisplay(__g->ref_SYMBptr()->feuille).display() << ")";
            }
            break;
        }
        default:
            s << *__g;
            break;
    }
    return s.str(); 
}