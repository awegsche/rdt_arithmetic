#include <iostream>
#include <sstream>
struct indentendl {int indent;};

////template<typename T>
//class PrettyStream {
//private:
    //std::ostream &__stream = std::cout;
    //int _indent;
     
//public:
    //PrettyStream() : _indent(0), /*__stream()*/ {}

    //friend std::ostream& operator<<(std::ostream& os, const PrettyStream& ps);
    //friend PrettyStream& operator<<(PrettyStream& os, const pendl& _);
    //friend PrettyStream& operator<<(PrettyStream& os, const indentendl& _);
    //friend PrettyStream& operator<<(PrettyStream& os, const outdentendl& _);

    //template<typename T>
    //friend PrettyStream& operator<<(PrettyStream& os, const T& t);
//};

//template<typename T>
//PrettyStream& operator<<(PrettyStream& os, const T& t) {
    //cout <<"[" << t << "]";
    //return os;
//}

std::ostream& operator<<(std::ostream& os, const indentendl& _);