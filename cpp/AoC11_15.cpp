#include <vector>
#include <sstream>
#include "../hpp/AoC2015.hpp"
#include "../hpp/smmComuni.hpp"

bool isGoodPassword(std::string sequence)
{
	//rule 1: a "straight" abc, bcd etc
	//rule 2: no i, l, o
	//rule 3: must contain double pair
	//first check rule 2 and exit if found;

	std::string seqCopy = sequence;
	bool break_me;
	int p;
	char x;
	if (seqCopy.find_first_of('i') != std::string::npos) return false;
	if (seqCopy.find_first_of('o') != std::string::npos) return false;
	if (seqCopy.find_first_of('l') != std::string::npos) return false;

	//look for straight
	do
	{
		x = seqCopy.back();
		p = seqCopy.length() - 1;

		break_me = seqCopy[p] -1 == seqCopy[p - 1];
		break_me = break_me && seqCopy[p] -2 == seqCopy[p - 2];
		if (break_me) break;
		seqCopy.pop_back();

	} while (seqCopy.length() > 2);

	if (!break_me) return false;	//rule was not ok
	
	p = 0;

	while (sequence.length() > 1)
	{
		//
		x = sequence.back();
		sequence.pop_back();
		if (x == sequence.back())
		{
			sequence.pop_back();
			p++;
		}//
	}
	return p >= 2;
}

std::string IncrementLastLetter(std::string sequence)
{
	char c;
	//std::string answ;
	
	//if you are here, there is no carry!
	c = sequence.back();
	sequence.pop_back();
	if (c == 'z')
	{
		sequence = IncrementLastLetter(sequence);
		c = 'a';
	}
	else
	{
		c = c++;
	}
	sequence.push_back(c);

	return sequence;

}


std::pair<std::string, std::string> AoC11_15(std::string sequence)
{
	std::pair<std::string, std::string> myAnsw;
	myAnsw.second = sequence;
//	myAnsw.first = "hxbxxyzy";
	do
	{
		myAnsw.second = IncrementLastLetter(myAnsw.second);
	}while (!isGoodPassword(myAnsw.second));

	myAnsw.first = myAnsw.second;

	do			//same identical loop
	{
		myAnsw.second = IncrementLastLetter(myAnsw.second);
	} while (!isGoodPassword(myAnsw.second));



	return myAnsw;
}