#include <map>
#include <set>
#include <fstream>

#include "..\hpp\smmComuni.hpp"


std::pair<long long int, long long int> AoC03_15(std::string myFileName)
{
	std::pair<long long int, long long int> myAnsw;
	std::vector<std::pair<long long int, long long int>> myHouses, secondSanta, secondRobo;
	std::vector<std::pair<long long int, long long int>>::iterator itPos;
	std::pair<long long int, long long int> lastVisited, lvSS, lvSR , *lv2ptr;	//last visited 2nd santa and 2nd robot; a pointer
	bool even = true;
	std::ifstream ifs(myFileName);
	char c;
	lastVisited = std::make_pair(0, 0);
	lvSS = std::make_pair(0, 0);
	lvSR = std::make_pair(0, 0);
	myHouses.push_back(lastVisited);
	secondSanta.push_back(lastVisited);
	secondRobo.push_back(lastVisited);;

	ifs >> c;
	while (ifs.good())							//get the input and create the path; for 2nd step (Santa and RoboSanta), pick which one you are using
	{
		lv2ptr = even ? &lvSS : &lvSR;			//choose which one to use
		switch (c)
		{
		case '>':
			lastVisited.first++;
			lv2ptr->first++;
			break;
		case '<':
			lastVisited.first--;
			lv2ptr->first--;
			break;
		case '^':
			lastVisited.second++;
			lv2ptr->second++;
			break;
		case 'v':
			lastVisited.second--;
			lv2ptr->second--;
			break;
		default:
			break;
		}
		myHouses.push_back(lastVisited);

		if (even) secondSanta.push_back(*lv2ptr); else secondRobo.push_back(*lv2ptr);
		even = !even;
		ifs >> c;

	}

	ifs.close();

	std::sort(myHouses.begin(), myHouses.end());
	itPos = std::unique(myHouses.begin(), myHouses.end());
	myAnsw.first = std::distance(myHouses.begin(), itPos);

	secondSanta.insert(secondSanta.end(), secondRobo.begin(), secondRobo.end());	//combine the houses

	std::sort(secondSanta.begin(), secondSanta.end());
	itPos = std::unique(secondSanta.begin(), secondSanta.end());
	myAnsw.second = std::distance(secondSanta.begin(), itPos);

	return myAnsw;
}