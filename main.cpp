//#include "giac_helper.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

#include "giac_console.h"
#include "brackets.h"
//#include "hterms.h"
#include "forced_rdts.h"


using std::endl;
using std::vector;
using namespace giac;

const size_t MULTLINE_SIZE = 65536;
const size_t INPUT_SIZE = 2048;
char giac_context_buf[MULTLINE_SIZE];
char input_buf[INPUT_SIZE];

GiacConsole* gc = nullptr;

void MainLoop() {

    int count = 0;
    while(true) {
        std::cout << "[in  " << count << "] ";
        std::cout.flush();
        std::cin >> input_buf;

        if(strcmp("q", input_buf) == 0)
            break;

        std::cout << "[out " << count++ << "] " << gc->evaluate(input_buf) << std::endl; 
    }

}

std::istream& readline(std::istream &file, std::string &line) {
    bool comment = true;
    while (comment && std::getline(file, line)) {
        if (line[0] != '/')
            comment = false;
    }
    return file;
}

int main(int argc, char **argv) {
    gc = new GiacConsole;

    if (argc > 1) {
        std::ifstream file(argv[1]);
        std::string line;
        char* bufptr = giac_context_buf;
        while(readline(file, line)) {
            //std::cout << "file: " << line << std::endl;
            while(line.back() == '\\')
            {
                line.pop_back();
                std::string nextline;
                readline(file,line);
                line += nextline; 
            }

            std::cout << "[file: ] " << gc->evaluate(line.c_str()) << "\n";
            memcpy(bufptr, line.c_str(), line.size());
            bufptr += line.size();
            *bufptr = '\n';
            bufptr++;
        }
        *bufptr = '\0';
        std::cout << std::endl;
        file.close();
    }

    MainLoop();
    /*
    std::ofstream ofile(argv[1], std::ios::trunc);
    ofile << giac_context_buf;
    ofile.close();
    */
    delete gc;
}