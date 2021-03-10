#ifndef DEBUG
#define DEBUG
#endif

#include<algorithm>
#include<map>
#include<string>
#include<vector>
#include <iostream>
#include "../hpp/smmComuni.hpp"

std::pair<long long int, long long int> AoC14_15(long long int TAU_RACE, std::string fileName)
{
	const size_t VEL = 0, TAU_RUN = 1, TAU_TOT = 2, POINTS = 3, DISTANCE = 4;
	const size_t NAME_STR = 0, SPEED_STR = 3, TAU_RUN_STR = 6, TAU_STOP_STR = 13;
	long long int t_tot, nLeg, remaining, d;
	std::pair<long long int, long long int> myAnsw;
	
	std::map<std::string, std::vector<long long int>> myReindeer;
	
	std::vector <long long int> vLong;
	std::vector <std::string> myLines, myTok;


	//lettura
	myLines = lineParser(fileName);

	//0		  1	 2	  3 4	 5	 6	7		8	9	10		11	12	13	14
 	//Dancer can fly 27 km/s for 5 seconds, but then must rest for 132 seconds.

	for (auto const& l : myLines)
	{
		vLong.clear();
		myTok = Split(l, " ");
		vLong.push_back(stoi(myTok[SPEED_STR]));
		vLong.push_back(stoi(myTok[TAU_RUN_STR]));
		vLong.push_back(stoi(myTok[TAU_STOP_STR])+vLong[1]);	//tempo totale
		vLong.push_back(0);	//for points, part 2
		vLong.push_back(0);	//for distance, part 2

		myReindeer.insert(std::make_pair(myTok[NAME_STR], vLong));
	}


	//part 1
	for (auto& r : myReindeer)
	{
		//t_tot = r.second[TAU_RUN] + r.second[TAU_STOP];
		nLeg = TAU_RACE / r.second[TAU_TOT];	//integer division! It works!
		remaining = TAU_RACE % r.second[TAU_TOT];

		if (remaining > r.second[TAU_RUN]) remaining = r.second[TAU_RUN];	//cap!
		d = 0;
		for (; remaining > 0; --remaining)
			d += r.second[VEL];
		d += nLeg * (r.second[VEL] * r.second[TAU_RUN]);

		vLong.push_back(d);
	}



	myAnsw.first = *std::max_element(vLong.begin(), vLong.end());

	//part two:
	//step every second
	//increase distance as needed
	//check who is the first, and give a point (could be multiple winners in theory; that is why there is an external loop)
	//find the overall winner
	d = 0;

	for (t_tot = 0; t_tot < TAU_RACE; t_tot++)
	{
		for (auto& r : myReindeer)
		{
			//step and increase distance
			if ((t_tot % r.second[TAU_TOT]) < r.second[TAU_RUN])
				r.second[DISTANCE] += r.second[VEL];
			//define first position (= max distance)
			d = d > r.second[DISTANCE] ? d : r.second[DISTANCE];
		}

			//find which Reindeer is 1st;
		for (auto& r : myReindeer)
			if (d == r.second[DISTANCE])
				r.second[POINTS]++;

	}

	myAnsw.second = 0;
	for (auto& r : myReindeer)
		myAnsw.second = myAnsw.second < r.second[POINTS] ? r.second[POINTS] : myAnsw.second;

	
	return myAnsw;
	


}