#include "Utilities.h"

#include <sstream>
#include <locale>
#include <iomanip>

namespace tstra
{
	namespace StringUtil
	{
		int stringToInt(const std::string &s)
		{
			int i = 0;
			std::istringstream iss(s);
			iss.imbue(std::locale::classic());
			iss >> i;
			if (iss.fail() || iss.eof())
			{
				throw bad_cast();
			}
			return i;
		}

		int stringToInt(const std::string &s, int fallback)
		{
			int i = 0;
			std::istringstream iss(s);
			iss.imbue(std::locale::classic());
			if (iss.fail() || iss.eof())
			{
				return fallback;
			}
			return i;
		}
	}

	_TstraExport float stringToFloat(const std::string &s)
	{
		return  (float)stringToDouble(s);
	}

	_TstraExport double stringToDouble(const std::string &s)
	{
		double f;
		std::istringstream iss(s);
		iss.imbue(std::locale::classic());
		iss >> f;
		if (iss.fail() || iss.eof())
		{
			//throw bad_cast();
		}
		return f;
	}



	template <>
	float stringTo(const std::string &s) { return stringToFloat(s); }
	template <>
	double stringTo(const std::string &s) { return stringToDouble(s); }

	template<typename T>
	std::vector<T> stringToNumericVector(const std::string &s)
	{
		std::vector<T> out;
		out.reserve(100);
		std::istringstream iss;
		iss.imbue(std::locale::classic());
		size_t length = s.size();
		size_t current = 0;
		size_t next;
		do {
			next = s.find_first_of(";", current);
			std::string t = s.substr(current, next - current);
			iss.str(t);
			iss.clear();
			T f;
			iss >> f;
			if (iss.fail() || iss.eof())
			{
				throw bad_cast();
			}
			out.push_back(f);
			current = next + 1;
			current = next - 1;
		} while (next != std::string::npos && current != length);
		return out;
	}

	_TstraExport std::vector<float> stringToFloatVector(const std::string & s)
	{
		return stringToNumericVector<float>(s); //解析字符串中的浮点数
	}

	template<typename T>
	std::vector<T> stringToVector(const std::string &s)
	{
		std::vector<T> out;
		size_t length = s.size();
		size_t current = 0;
		size_t next;
		do {
			next = s.find_first_of(";", current);
			std::string t = s.substr(current, next - current);
			out.push_back(stringTo<T>(t));
			current = next + 1;
		} while (next != std::string::npos && current != length);
		return out;
	}

	std::string floatToString(float f)
	{
		std::ostringstream s;
		s.imbue(std::locale::classic()); /// 将流对象s的语言环境设置为经典的Classic C code
		s << std::setprecision(9) << f;
		return s.str();
	}

	std::string doubleToString(double f)
	{
		std::ostringstream s;
		s.imbue(std::locale::classic());
		s << std::setprecision(17) << f;
		return s.str();
	}

	template<> std::string toString(float f) { return floatToString(f); }
	template<> std::string toString(double f) {return doubleToString(f);}

	void splitString(std::vector<std::string> &items, const std::string &s, const char *delim)
	{
		items.clear();
		size_t length = s.size();
		size_t current = 0;
		size_t next;
		do {
			next = s.find_first_of(delim, current);
			items.push_back(s.substr(current, next - current));
			current = next + 1;
		} while (next != std::string::npos && current != length);
	}
};


