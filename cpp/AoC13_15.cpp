#ifndef DEBUG
#define DEBUG
#endif

#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "../hpp/AoC2015.hpp"
#include "../hpp/smmComuni.hpp"

size_t myMatrIndex(size_t i, size_t j, size_t NC)
{return i * NC + j;}

std::pair<long long int, long long int> AoC13_15(std::string fileName)
{
	const int N_EL = 11, SUBJECT = 0, LOSE_GAIN = 2, HAPPINESS = 3, OTHER = 10;
	std::pair<long long int, long long int> myAnsw;
	std::vector<std::string> vString = lineParser(fileName);
	std::vector < std::vector<std::string>> possibilities;
	std::map <std::string, size_t> nameMap;
	std::vector <long long int> myV, myDeltaTable, myV2, myDeltaTable2;
	int plus_or_minus, howMuch;
	size_t i, NUM_PEOPLE, NUM_PEOPLE_2;
	long long int s;
	std::string str, sog, ogg;

	std::stringstream ioss;
	for (auto& s : vString)
		s.pop_back();	//remove last '.'

	ioss << vString;

	vString = myParser(&ioss, str);
	//0		1		2	3	4		5	6		7	8	9	10
	//Alice would lose 2 happiness units by sitting next to Bob
	//Alice would gain 65 happiness units by sitting next to David

	for (i = 0; i < vString.size(); i += N_EL)
		if (nameMap.find(vString[i]) == nameMap.end())
			nameMap.insert(std::make_pair(vString[i], nameMap.size()));

	NUM_PEOPLE = nameMap.size();


	myV.resize(NUM_PEOPLE * NUM_PEOPLE);//matr quadrata
	myV2.resize(NUM_PEOPLE * NUM_PEOPLE + 2 * NUM_PEOPLE + 1);

	for (i = 0; i < vString.size(); ++i)
	{
		switch (i % N_EL)
		{
		case SUBJECT:
			sog = vString[i];
			break;
		case LOSE_GAIN:
			plus_or_minus = vString[i].compare("lose") == 0 ? -1 : 1;
			break;
		case HAPPINESS:
			howMuch = stoi(vString[i]);
			howMuch *= plus_or_minus;
			break;
		case OTHER:
			ogg = vString[i];
			//insert the new element! 

			myV[myMatrIndex(nameMap[sog], nameMap[ogg], NUM_PEOPLE)] = howMuch;
			myV2[myMatrIndex(nameMap[sog], nameMap[ogg], NUM_PEOPLE + 1)] = howMuch;	//2nd part!
			break;
		}
	}

	myDeltaTable.resize(NUM_PEOPLE * NUM_PEOPLE);//matr quadrata
	vString.clear();

	//1st part
	for (auto const & p1 : nameMap)
	{
		vString.push_back(p1.first);// add Names
		for (auto const & p2 : nameMap)
		{
			myDeltaTable[myMatrIndex(p1.second, p2.second, NUM_PEOPLE)] = myV[myMatrIndex(p1.second, p2.second, NUM_PEOPLE)];
			myDeltaTable[myMatrIndex(p1.second, p2.second, NUM_PEOPLE)] += myV[myMatrIndex(p2.second, p1.second, NUM_PEOPLE)];
		}
	}

	possibilities = GiveCircularFactorial(vString, true);
	myV.clear();
	myV.reserve(possibilities.size());
	for (auto const& p : possibilities)
	{
		s = 0;
		for (i = 0; i < p.size() - 1; ++i)
			s += myDeltaTable[myMatrIndex(nameMap[p[i]], nameMap[p[i + 1]], NUM_PEOPLE)];
		myV.push_back(s);
	}

	myAnsw.first = *std::max_element(myV.begin(), myV.end());

	
	//2nd part
	nameMap.insert(std::make_pair("me", nameMap.size()));
	NUM_PEOPLE_2 = nameMap.size();
	myDeltaTable2.resize(NUM_PEOPLE_2 * NUM_PEOPLE_2);//matr quadrata
	//build table
	vString.clear();
	for (auto const& p1 : nameMap)
	{
		vString.push_back(p1.first);// add Names
		for (auto const& p2 : nameMap)
		{
			myDeltaTable2[myMatrIndex(p1.second, p2.second, NUM_PEOPLE_2)] = myV2[myMatrIndex(p1.second, p2.second, NUM_PEOPLE_2)];
			myDeltaTable2[myMatrIndex(p1.second, p2.second, NUM_PEOPLE_2)] += myV2[myMatrIndex(p2.second, p1.second, NUM_PEOPLE_2)];
		}
	}

	possibilities = GiveCircularFactorial(vString, true);
	myV.clear();
	myV.reserve(possibilities.size());
	for (auto const& p : possibilities)
	{
		s = 0;
		for (i = 0; i < p.size() - 1; ++i)
			s += myDeltaTable2[myMatrIndex(nameMap[p[i]], nameMap[p[i + 1]], NUM_PEOPLE_2)];
		myV.push_back(s);
	}

	myAnsw.second = *std::max_element(myV.begin(), myV.end());



	return myAnsw;
	


}