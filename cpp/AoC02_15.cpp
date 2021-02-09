#include <map>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include "..\hpp\smmComuni.hpp"


std::pair<long long int, long long int> AoC02_15(std::string myFileName)
{
	std::pair<long long int, long long int> myAnsw;
	std::vector<std::string> myFileContent = lineParser(myFileName);
	std::regex lhw("(\\d+)x(\\d+)x(\\d+)");
	std::smatch res;
	std::vector<long long int> sizes(3);

	for (std::string const& aLine : myFileContent)
	{
		std::regex_match(aLine, res, lhw);
		for (int i = 1; i < 4; ++i)
			sizes[i - 1] = stoi(res[i].str());
		std::sort(sizes.begin(), sizes.end());
		myAnsw.first += 3 * (sizes[0] * sizes[1]) +
						2 *	(sizes[0] * sizes[2] +
							 sizes[1] * sizes[2]);
		myAnsw.second += 2 * (sizes[0] + sizes[1]) + (sizes[0] * sizes[1] * sizes[2]);
	}
	return myAnsw;
}