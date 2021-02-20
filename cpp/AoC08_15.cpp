#include <vector>
#include <string>
#include <regex>
#include "../hpp/AoC2015.hpp"
#include "../hpp/smmComuni.hpp"

std::pair<long long int, long long int> AoC08_15(std::string myFileName) 
{
	std::vector<std::string> fContent = lineParser(myFileName);
	std::pair<long long int, long long int> myAnsw;
	size_t st, f;
	long long int esc_quotes = 0, slash = 0, ics = 0, norm_quotes = 0;

	for (auto const& l : fContent)		
	{
		st = 0;
		f = l.find('\\', st);
		while (f != std::string::npos)
		{
			switch (l[f + 1])
			{
			case ('x'):
				ics++;
				break;
			case ('\\'):
				slash++;
				break;
			case ('\"'):
				esc_quotes++;
				break;
			}
			st = f + 2;				//next possibility: if there is \\\x the 2nd \ shall be skipped
			f = l.find('\\', st);
		}
		norm_quotes += 2;
	}

	//it is asked the length of the string excluding the encoding
	//every \xab becomes a single char, so it goes from "raw" length 4 to length 1; delta is 3
	//every \\ becomes \; delta is 1
	//every \" becomes "; delta is 1
	//every "" at beginning and at end should not be counted
	myAnsw.first = 3 * ics + slash + norm_quotes+ esc_quotes;

	//it is asked the length of the string if re_encoded
	//every "----" at beginning and at end becomes "\"---\"", so + 4 (or 2 each)
	//every \" becomes \\\", so +2
	//every \\ becomes \\\\, so +2
	//every \x becomes \\x, so + 1

	myAnsw.second = 2 * norm_quotes + 2 * esc_quotes + 2 * slash + ics;

	return myAnsw;
}