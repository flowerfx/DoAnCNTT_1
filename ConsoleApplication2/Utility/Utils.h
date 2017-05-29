#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>


namespace extension
{
	std::string ConvertTime(time_t time);

	void replaceAllString(std::string& str, const std::string& from, const std::string& to);

	std::vector<std::string> split(std::string data, std::string token);

	void recorrectFilePath(std::wstring & path);

};

#endif // __UTILS_H__