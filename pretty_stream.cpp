
#include "pretty_stream.h"
#include <iostream>

//PrettyStream& operator<<(PrettyStream& ps, const indentendl& _) {
//    ps.__stream << "\n";
//    ps._indent += 2;
//    for (int i = 0; i < ps._indent; i++)
//        ps.__stream << " ";
//
//    return ps;
//}
//
//PrettyStream& operator<<(PrettyStream& ps, const outdentendl& _) {
//    ps.__stream << "\n";
//    ps._indent -= 2;
//    for (int i = 0; i < ps._indent; i++)
//        ps.__stream << " ";
//
//    return ps;
//}
//
//PrettyStream& operator<<(PrettyStream& ps, const pendl& _) {
//    ps.__stream << "\n";
//    for (int i = 0; i < ps._indent; i++)
//        ps.__stream << " ";
//
//    return ps;
//}
//
//std::ostream& operator<<(std::ostream& os, const PrettyStream& ps) {
//    return os << ps.__stream.str();
//}
//
//std::ostream& operator<<(std::ostream& os, const pendl& _) {
//    return os;// << "\n";
//}
std::ostream& operator<<(std::ostream& os, const indentendl& ie) {
    for (int i = 0; i < ie.indent; i++)
        os << " ";
    return os;
}
//std::ostream& operator<<(std::ostream& os, const outdentendl& _) {
//    return os;// << "\n";
//}
