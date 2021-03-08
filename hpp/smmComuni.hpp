#pragma once

#include <fstream>
#include <iterator> // needed for std::ostream_iterator
#include <regex>
#include <deque>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "..\hpp\smmConsts.hpp"

struct countTrue      //da usare in for_each
{
    void operator()(bool b) { sum += b ? 1 : 0; }
    int sum{ 0 };
};

std::tuple<bool, int, int> findSum(int wantedValue, std::vector<int> v);
std::string CleanWhiteSpace(std::string str);
std::string DeleteThisChar(std::string str, char c);
std::vector<std::string> lineParser(std::istream* is);
std::vector<std::string> lineParser(std::string fileName);
std::vector<std::string> Parser(std::istream* is, char delimiter, std::regex excludeMe = std::regex(".^")); //default regex never match
std::vector<std::string> Parser(std::string fileName, char delimiter, std::regex excludeMe = std::regex(".^")); //default regex never match


//std::pair<size_t, size_t> find_matching_item(std::string searchMe, std::string findMe, char opener, char closer, size_t startPos = 0);

std::vector<std::string> Split(std::string input, std::string delimiter);

void multiLineMerger(std::istream* is, std::ostream* os, char delimiter = ' ' );
void multiLineMerger(std::string iFileName, std::string oFileName, char delimiter = ' '); //default regex never match

//std::vector<int> VString2Int(std::vector <std::string> const& lval);
std::vector<size_t> Vint2Vpos(std::vector<int> const& source);	//lookup for position of positive integers


//template <typename T>
//std::vector<T> const ExtractColumn(std::vector<std::vector<T>> myMatr, unsigned int colNum);
template <typename T>
inline std::ostream& operator<< (std::ostream& out, const std::vector<T>& v)
{

	std::ostringstream preOut;
	std::string aStr;
	for (auto const& itV : v)
		preOut << itV << smmConst::separator;;


	if (!v.empty())
	{
		aStr = preOut.str();
		aStr.erase(aStr.length() - 1, 1);
	}
	out << aStr;
	return out;
}
std::ostream& operator<< (std::ostream& out, const std::vector<bool>& v);	//specialization

template <typename T>
inline std::vector<T> myParser(std::istream* is, T dummy)
{
	std::vector<T> lista;
	T n;
	while (is->good())
	{
		*is >> n;
		lista.push_back(n);
	}
	return lista;
}
template <typename T>
inline std::vector<T> myParser(std::string fileName, T dummy)
{
	std::ifstream myFileInp;
	std::vector<T> lista;
	myFileInp.open(fileName.c_str(), std::ifstream::in);

	lista = myParser(&myFileInp, dummy);
	myFileInp.close();
	return lista;
}

template <typename T>
inline std::vector<T> VectorConverter(std::vector<std::string> const & rVal, T dummy)
{
	std::vector<std::string>::const_iterator theStrings;
	std::vector<T> myAnsw;
	std::istringstream iss;
	myAnsw.reserve(rVal.size());

	for (theStrings = rVal.begin(); theStrings != rVal.end(); ++theStrings)
	{
		iss.clear();
		iss.str(*theStrings);
		iss >> dummy;
		myAnsw.push_back(dummy);
	}
	return myAnsw;
}


template <typename T>
inline std::vector<std::vector<T>> GiveFactorial(std::vector <T> inp)
{
	//give all possible arrangment
	std::deque<T> lastShuffle;
	size_t i;
	std::vector<T> v2;
	std::vector<std::vector<T>> myAnsw, myPartAnsw;
	T anEl;
	if (inp.size() == 1)
	{
		myAnsw.push_back(inp);
	}
	else
	{
		anEl = inp.back();
		inp.pop_back();
		myPartAnsw = GiveFactorial(inp);	//all elements but last;
		for (auto const & v1 : myPartAnsw)	//for each vector
		{
			lastShuffle.clear();
			lastShuffle.insert(lastShuffle.begin(), v1.begin(), v1.end());
			lastShuffle.push_back(anEl);
			for (i = 0; i < inp.size() + 1; ++i)	//+1: before every element and after last!
			{
				v2.clear();
				v2.insert(v2.begin(), lastShuffle.begin(), lastShuffle.end());
				myAnsw.push_back(v2);

				lastShuffle.push_front(lastShuffle.back());//add the same at the beginning
				lastShuffle.pop_back();
			}
		}
	}
	return myAnsw;
}

template <typename T>
inline std::vector<std::vector<T>> GiveCircularFactorial(std::vector <T> inp, bool RepeatFirstAtEnd)
{

	//return factorial "around the table" (relative order, so ABC = BCA = CAB)
	//if RepeatFirstAtEnd, ABC becomes ABCA (easier to check for "neighbours")

	std::vector<std::vector<T>> myAnsw;
	
	T lastEl = inp.back();


	if (inp.size() == 1)
	{
		myAnsw.push_back(std::vector<T>());	//an empty vector!
	}
	else
	{
		inp.pop_back();
		myAnsw = GiveFactorial(inp);
	}
	
	for (std::vector<T> & v : myAnsw)
		v.push_back(lastEl);
	if (RepeatFirstAtEnd)
	{
		for (std::vector<T>& v : myAnsw)
		{
			std::reverse(v.begin(), v.end());
			v.push_back(lastEl);
		}
	}
	return myAnsw;

}