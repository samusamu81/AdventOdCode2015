#include <string>
#include <algorithm>
#include <regex>
#include <vector>
#include "..\hpp\smmComuni.hpp"
//A nice string is one with all of the following properties :
//
//It contains at least three vowels(aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
//It contains at least one letter that appears twice in a row, like xx, abcdde(dd), or aabbccdd(aa, bb, cc, or dd).
//It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.

bool isNiceString_partA(std::string const & inpStr)
{
	std::regex vowels("([aeiou])"), r1("ab"), r2("cd"), r3("pq"), r4("xy");

	std::smatch res;
	std::string inpCopy = inpStr;
	std::string::iterator strIter;
	std::regex_search(inpStr, res, vowels);
	while (res.size() > 0)
	{
		inpCopy = res.prefix().str() + res.suffix().str();
		std::regex_search(inpCopy, res, vowels);
	}
	if (inpStr.length() - inpCopy.length() < 3 ) return false;
	inpCopy = inpStr;
	strIter = std::unique(inpCopy.begin(), inpCopy.end());
	if (strIter == inpCopy.end()) return false;

	std::regex_search(inpStr, res, r1);
	if (res.size() > 0) return false;
	std::regex_search(inpStr, res, r2);
	if (res.size() > 0) return false;
	std::regex_search(inpStr, res, r3);
	if (res.size() > 0) return false;
	std::regex_search(inpStr, res, r4);
	if (res.size() > 0) return false;

	return true;
	
}

bool isNiceString_partB(std::string const & inpStr)
{
	//pick 2 letters in the string; find a matching pattern
	std::string::const_iterator it1, it2, it3, it4;
	bool found_2 = false;
	if (inpStr.length() < 4) return false;
	for (it1 = inpStr.begin(); (it1 + 3 != inpStr.end() && !found_2); ++it1)
	{
		it2 = it1 + 1;
		for (it3 = it2 + 1; (it3 + 1 != inpStr.end() && !found_2); ++it3)
		{
			it4 = it3 + 1;
			found_2 = (*(it1._Ptr) == *(it3._Ptr)) && (*(it2._Ptr) == *(it4._Ptr));
		}

	}
	//if you get here, so far it is good

	if (!found_2) return false;
	for (it1 = inpStr.begin(); it1 + 2 != inpStr.end() ; ++it1)
	{
		it3 = it1 + 2;
		if (*it3 == *it1) return true;
	}
	
	return false;
}

std::pair<long long int, long long int> AoC05_15(std::string myFileName)
{
	std::vector<std::string> myFile = lineParser(myFileName);
	std::pair<long long int, long long int> myAnsw;
	
	bool x = isNiceString_partB("uurcxstgmygtbstg");
	for (std::string const& aLine : myFile)
	{
		myAnsw.first += isNiceString_partA(aLine) ? 1 : 0;
		myAnsw.second += isNiceString_partB(aLine) ? 1 : 0;
	}

	
	return myAnsw;
}