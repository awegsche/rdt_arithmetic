#include <sstream>
#include "giac_console.h"
#include "giac_helper.h"

const string LOG{"\33[33m[giac]\33[0m "};

GiacConsole::GiacConsole() 
{
}

void GiacConsole::assign(const char* name, const gen& g) {
    _assign(makesequence(gen(name, &_ct), g), &_ct);
}

giac::gen GiacConsole::evaluate(const char* command, bool silent) {
    _history.push_back(string{command});
    try
    {
        giac::gen com = giac::eval(gen{command, &_ct}, &_ct);
        std::stringstream ss;
        ss << com;
        //ss << giac::_simplify(command, &_ct);
        if (!silent) {
            _answers.push_back(
                //GenDisplay(com).display()
                //+ "\n\33[38;2;128;128;128m[raw] " +
                ss.str()
                //+ "\33[0m"
            );
        }
        return com;
    }
    catch(const std::exception& e)
    {
        std::stringstream emess;
        emess << "\33[31m ERROR: " << e.what() << "\33[0m\n";
        _answers.push_back( emess.str());
        std::cout << command << "\n" << e.what() << std::endl;
    }
    catch(...) {
        std::cout << "unknown exception" << std::endl;
    }
    return gen{0}; 
}
