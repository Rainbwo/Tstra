/**
 * @file Utilities.h
 * @author zhang tao (zhang_tao123@foxmail.com)
 * @brief 字符串处理
 * @version 0.1
 * @date 2023-11-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _INC_TSTRA_UTILITIES
#define _INC_TSTRA_UTILITIES

#include <string>
#include <vector>
#include <map>
#include <exception>

#include "Globals.h"

namespace tstra
{
    namespace StringUtil
    {
        class bad_cast : public std::exception
        {
        public:
            bad_cast(){};
        };

        /// 将字符串解析为int
        _TstraExport int stringToInt(const std::string &s);
        /// 将字符串解析为int
        _TstraExport int stringToInt(const std::string &s, int fallback);
        /// 将字符串解析为float
        _TstraExport float stringToFloat(const std::string &s);
        /// 将字符串解析为Double
        _TstraExport double stringToDouble(const std::string &s);
        template <typename T>
        _TstraExport T stringTo(const std::string &s);

        _TstraExport std::vector<float> stringToFloatVector(const std::string &s);

        _TstraExport std::vector<double> stringToDoubleVector(const std::string &s);

        template <typename T>
        _TstraExport std::vector<T> stringToVector(const std::string &s);

        _TstraExport std::string floatToString(float f);

        template <typename T>
        _TstraExport std::string toString(T f);

        _TstraExport void splitString(std::vector<std::string> &items, const std::string &s, const char *delim);
    }
}

template <typename T, typename S>
std::map<T, S> mergeMap(std::map<T, S> _mMap1, std::map<T, S> _mMap2)
{
    std::map<T, S> result = _mMap1;
    for (typename std::map<T, S>::iterator it = _mMap2.begin(), it != _mMap2.end(); it++)
    {
        result[(*it).first] = (*it).second;
    }
    return result;
}

#endif