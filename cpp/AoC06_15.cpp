#include <regex>
#include <string>
#include <vector>
#include "../hpp/smmComuni.hpp"
size_t const LIGHT_SIZE = 1000;

std::vector<size_t> GivePositions(size_t lowR, size_t lowC, size_t highR, size_t highC)
{
	std::vector<size_t> myAnsw;
	size_t i, j;
	myAnsw.reserve((highR - lowR + 1) * (highC - lowC + 1)); //not sure about "+1", just in case
	
	for (i = lowR; i <= highR; ++i)
		for (j = lowC; j <= highC; ++j)
			myAnsw.push_back(i * LIGHT_SIZE + j);

	return myAnsw;
}


std::pair<long long int, long long int> AoC06_15(std::string myFileName)
{
	std::vector<std::string> fileContent = lineParser(myFileName);
	std::regex turnON("turn on (\\d+),(\\d+) through (\\d+),(\\d+)");
	std::regex turnOFF("turn off (\\d+),(\\d+) through (\\d+),(\\d+)");
	std::regex toggle("toggle (\\d+),(\\d+) through (\\d+),(\\d+)");
	std::vector<bool> lights;
	std::vector<int> brightness;	//for part 2!
	std::vector <size_t> changes;
	size_t lr, lc, hr, hc;
	std::regex * ptRegex;
	std::pair<long long int, long long int> myAnsw;

	lights.resize(LIGHT_SIZE * LIGHT_SIZE);
	brightness.resize(LIGHT_SIZE * LIGHT_SIZE);		//should be all 0s

	for (std::string const& aLine : fileContent)
	{
		ptRegex = NULL;
		if (std::regex_match(aLine, turnON)) ptRegex = &turnON;
		else if (std::regex_match(aLine, turnOFF)) ptRegex = &turnOFF;
		else if (std::regex_match(aLine, toggle)) ptRegex = &toggle;
		if (ptRegex == NULL) throw new std::out_of_range("Dereferencing null pointer!");
		lr = stoi(std::regex_replace(aLine, *ptRegex, "$1"));
		lc = stoi(std::regex_replace(aLine, *ptRegex, "$2"));
		hr = stoi(std::regex_replace(aLine, *ptRegex, "$3"));
		hc = stoi(std::regex_replace(aLine, *ptRegex, "$4"));
		changes = GivePositions(lr, lc, hr, hc);
		if (ptRegex == &turnON)
			for (size_t const& pos : changes)
			{
				lights[pos] = true;
				brightness[pos]++;
			}
		else if (ptRegex == &turnOFF)
			for (size_t const& pos : changes)
			{
				lights[pos] = false;
				brightness[pos]--;
				if (brightness[pos] < 0) brightness[pos] = 0;

			}
		else if (ptRegex == &toggle)
			for (size_t const& pos : changes)
			{
				lights[pos] = !lights[pos];
				brightness[pos] += 2;
			}
	}


	for (bool const& isOn : lights)
		myAnsw.first += isOn ? 1 : 0;

	for (int const& br : brightness)
		myAnsw.second += br;

	return myAnsw;

}