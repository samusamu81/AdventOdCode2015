#include <vector>
#include <sstream>
#include "../hpp/AoC2015.hpp"
#include "../hpp/smmComuni.hpp"

std::string giveNextSequence(std::string sequence)
{
	int count;
	char c;
	std::stringstream myRevAnsw;
	std::string aStr;

	do
	{
		//insert new char
		c = sequence.back();
		count = 1;
		sequence.pop_back();	//consume last char
		
		while (sequence.length() > 0 && c == sequence.back())	//there is something I can "eat"
		{
			sequence.pop_back();	//consume last char
			count++;
		}
		myRevAnsw <<c;	//I know what I am looking for;
		myRevAnsw <<count;
	} while (sequence.length() > 0);
	
	aStr = myRevAnsw.str();
	std::reverse(aStr.begin(), aStr.end());
	return aStr;

}


std::pair<long long int, long long int> AoC10_15(std::string sequence)
{

	std::pair<long long int, long long int> myAnsw;
	const int NCYCLE = 40;
	const int NCYCLE_EXTRA = 10;
	std::stringstream myConv;
	std::string rollingString = sequence;

	for (int i = 0; i < NCYCLE; i++)
		rollingString = giveNextSequence(rollingString);

	myAnsw.first = rollingString.length();

	for (int i = 0; i < NCYCLE_EXTRA; i++)
		rollingString = giveNextSequence(rollingString);
	myAnsw.second = rollingString.length();

	return myAnsw;
}