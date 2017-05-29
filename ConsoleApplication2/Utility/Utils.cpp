
#include "Utils.h"
#include "time.h"
#include <iostream>
#include <clocale>
#include <cctype>

namespace extension
{
	std::string ConvertTime(time_t time)
	{
		time /= 1000;
		time_t t = time;
		struct tm *  tstruct;
		tstruct = localtime(&t);
		char buf[80];
		strftime(buf, sizeof(buf), "%Y/%m/%d - %X", tstruct);
		return std::string(buf);
	}


	void replaceAllString(std::string& str, const std::string& from, const std::string& to)
	{
		if (from.empty())
			return;
		std::string::size_type start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}


	std::vector<std::string> split(std::string data, std::string token)
	{
		std::vector<std::string> output;
		size_t pos = std::string::npos; // size_t to avoid improbable overflow
		do
		{
			pos = data.find(token);
			output.push_back(data.substr(0, pos));
			if (std::string::npos != pos)
				data = data.substr(pos + token.size());
		} while (std::string::npos != pos);
		return output;
	}

	void recorrectFilePath(std::wstring & path)
	{
		if (path[path.size() - 1] != (wchar_t)L"/" || path[path.size() - 1] != (wchar_t)L"\\")
		{
			path += L"\\";
		}
	}

	
}
