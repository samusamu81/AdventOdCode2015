#include <map>
#include <string>
#include <fstream>

std::pair<long long int, long long int> AoC01_15(std::string myFileName)
{
	std::pair<long long int, long long int> myAnsw;
	long long int currFloor = 0;
	std::ifstream ifs(myFileName);
	char c;
	
	ifs >> c;
	while (ifs.good())
	{
		if (c == '(') myAnsw.first++;
		else myAnsw.first--;
		ifs >> c;
	}
	ifs.close();
	
	ifs.open(myFileName);
	
	ifs >> c;
	
	while (currFloor != -1)
	{
		if (c == '(') currFloor++;
		else currFloor--;
		ifs >> c;
		myAnsw.second++;
	}
	ifs.close();



	return myAnsw;
}