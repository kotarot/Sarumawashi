/**
 * utils.cpp
 * 
 * Definitions of utils.h
 * 
 * @author kotarot
 * @version 2014-10-20
 */

#include <string>
#include <vector>
#include "utils.h"

namespace Sarumawashi {

/** Splits a string. Refference:
    http://qiita.com/iseki-masaya@github/items/70b4ee6e0877d12dafa8 */
std::vector<std::string> split(const std::string &s, const char delim) {
    std::vector<std::string> elems;
    std::string item;
    for (int i = 0; i < (int)s.length(); i++) {
        char ch = s.at(i);
        if (ch == delim) {
            if (!item.empty()) {
                elems.push_back(item);
            }
            item.clear();
        } else {
            item += ch;
        }
    }
    if (!item.empty()) {
        elems.push_back(item);
    }
    return elems;
}

} // end of namespace
