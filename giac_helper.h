#pragma once
#include "common.h"
#include <giac/dispatch.h>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include "pretty_stream.h"


extern std::map<unsigned int, std::string> gen_types_map;

extern std::map<unsigned int, std::string> gen_subtypes_map;


struct GenDebug {
private:
    const giac::gen* __g;
    int _indent;

public:
    GenDebug(const giac::gen g, int indent=0) : __g(&g), _indent(indent) {}

    friend std::ostream& operator<<(std::ostream& os, const GenDebug& gd);

    std::string to_string() const {
        std::ostringstream out;
        out << *this;
        return out.str();
    }
};


std::ostream& operator<<(std::ostream& os, const GenDebug& gd);

class gen_vec{
    giac::context* _ct;
    giac::vecteur _v;

    public:
    gen_vec(giac::context* context) : _ct(context) { }

    template<typename T>
    friend gen_vec& operator<<(gen_vec& v, const T& el);

    giac::gen get_vec_ptr() const {
        return giac::gen(_v);
    }
};

template<typename T>
gen_vec& operator<<(gen_vec& v, const T& el) {
    v._v.push_back(el);
    return v;
}

struct GenDisplay {
private:
    const giac::gen* __g;
    int _level;

public:
    GenDisplay(const giac::gen g, int level = 0): __g(&g), _level(level) {}

    std::string display() const;
};