#pragma once
#include <vector>
#include <string>

#include "giac_setup.h"

using std::string, std::vector;

const size_t GiacBufSize = 512;

class GiacConsole {
    giac::context _ct;
    vector<string> _history;
    vector<string> _answers;
    char _inputbuf[GiacBufSize] = "";
    string _name;

public:
    GiacConsole();

    /**
     * @brief Assigns gen `g` to variable with name `name`.
     * This function is used to register a variable in the context for later usage through command
     * line
     * 
     * @param name the variable name
     * @param g the gen to be assign to the variable
     */
    void assign(const char* name, const gen& g);

    /**
     * @brief Evaluates the given command. This function is primarily used to perform computation in
     * the context of the console from code.
     * 
     * @param command a valid giac command ex: `a := taylor(sin(x), x);`
     * @param silent if `true` the command will not be added to the history and its result will not
     * be displayed in the output window
     */
    giac::gen evaluate(const char* command, bool silent=false);

    const context* context_ptr() const { return &_ct; }
};
