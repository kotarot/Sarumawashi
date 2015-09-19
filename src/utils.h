/**
 * utils.h
 * 
 * Some util functions.
 * 
 * @author kotarot
 * @version 2014-10-20
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>

namespace Sarumawashi {

/** Splits a string. Refference:
    http://qiita.com/iseki-masaya@github/items/70b4ee6e0877d12dafa8 */
std::vector<std::string> split(const std::string &s, const char delim);

} // end of namespace

#endif
