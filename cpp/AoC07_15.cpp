#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <regex>
#include "../hpp/smmComuni.hpp"


smmConst::bitw_op whichOp(std::string const& myStr)
{//note: add extra " " at the end
	if (myStr.compare("NOT ") == 0) return smmConst::NOT;
	if (myStr.compare("OR ") == 0) return smmConst::OR;
	if (myStr.compare("AND ") == 0) return smmConst::AND;
	if (myStr.compare("LSHIFT ") == 0) return smmConst::LSHIFT;
	if (myStr.compare("RSHIFT ") == 0) return smmConst::RSHIFT;
	return smmConst::FAILED_OP;
}


std::pair<unsigned short, bool> DoOperation(smmConst::bitw_op op, std::string& var1, std::string& var2) //var 1 is optional: "NOT xy -> ab will hav var1 = ""
{
	unsigned short x = 0, y = 0;	//x will contain the answer
	bool found = false;
	std::regex integer_reg("\\d+");
	switch (op)
	{
	case (smmConst::FAILED):	//acceptable if only 1 number
	{
		if (std::regex_match(var2, integer_reg))	//could be "aa -> bb"
		{
			if (var1.length() > 0) throw new std::invalid_argument("var1 should be empty");
			x = (unsigned short)std::stoi(var2);
			found = true;
		}
		break;
		
	}
	case (smmConst::NOT):
	{
		if (std::regex_match(var2, integer_reg))	 //could be "NOT aa -> bb"
		{
			if (std::regex_match(var2, integer_reg)) //I can convert!
			{
				x = (unsigned short)std::stoi(var2);
				x = ~x;
				found = true;
			}
		}
		break;
	}
	case (smmConst::OR):
	{
		if (std::regex_match(var2, integer_reg) && std::regex_match(var1, integer_reg)) //I can convert!
		{
			x = (unsigned short)std::stoi(var1);
			y = (unsigned short)std::stoi(var2);
			x = x | y;
			found = true;
		}
		break;
	}
	case (smmConst::AND):
	{
		if (std::regex_match(var2, integer_reg) && std::regex_match(var1, integer_reg)) //I can convert!
		{
			x = (unsigned short)std::stoi(var1);
			y = (unsigned short)std::stoi(var2);
			x = x & y;
			found = true;
		}
		break;
	}
	case (smmConst::LSHIFT):
	{
		if (std::regex_match(var2, integer_reg) && std::regex_match(var1, integer_reg)) //I can convert!
		{
			x = (unsigned short)std::stoi(var1);
			y = (unsigned short)std::stoi(var2);
			x = x << y;
			found = true;
		}
		break;
	}
	case (smmConst::RSHIFT):
	{
		if (std::regex_match(var2, integer_reg) && std::regex_match(var1, integer_reg)) //I can convert!
		{
			x = (unsigned short)std::stoi(var1);
			y = (unsigned short)std::stoi(var2);
			x = x >> y;
			found = true;
		}
		break;
	}
	}
	return std::make_pair(x, found);
}

std::pair<long long int, long long int> AoC07_15(std::string myFileName)
{
	/// <summary>
	/// Solve the AoC07_15
	/// </summary>
	/// <param name="myFileName"></param>
	/// <returns></returns>
	const int MAP_VALUE = 0, MAP_OPERAT = 1, MAP_INP1 = 2, MAP_INP2 = 3, MAP_OUT = 4;
	const std::string VAR1 = "$1", VAR2 = "$3", OP = "$2", OUT = "$4";
	std::string v1, v2, v3;
	std::vector<std::string> fileContent = lineParser(myFileName);
	std::map <std::string, std::tuple<smmConst::bitw_op, std::string, std::string>> myMap, myMapCopy;	//output, 
	auto iter = myMap.begin();	//output, 

	std::regex doItAll("([a-z]{1,2} |\\d+ )?(NOT |OR |AND |LSHIFT |RSHIFT )?([a-z]{1,2} |\\d+ )-> ([a-z]{1,2})");
	smmConst::bitw_op myOp;
	std::tuple<smmConst::bitw_op, std::string, std::string> aTuple;	//value if known, operation, var 1
	std::pair<unsigned short, bool> calcVal;
	std::map <std::string, unsigned short> myValSet;
	
	std::pair<long long int, long long int> myAnsw;

	for (std::string const& aLine : fileContent)
	{
		myOp = whichOp(std::regex_replace(aLine, doItAll, OP));
		v1 = std::regex_replace(aLine, doItAll, VAR1);
		if (v1.length() >= 2 && v1[v1.length() - 1] == ' ') v1 = v1.substr(0, v1.length() - 1);
		v2 = std::regex_replace(aLine, doItAll, VAR2);
		if (v2.length() >= 2 && v2[v2.length() - 1] == ' ') v2 = v2.substr(0, v2.length() - 1);
		v3 = std::regex_replace(aLine, doItAll, OUT);
		if (v3.length() >= 2 && v3[v3.length() - 1] == ' ') v3 = v3.substr(0, v3.length() - 1);
		myMap.insert(std::make_pair(v3, std::make_tuple (myOp, v1, v2)));

	}

	//map is completed!
	fileContent.clear();	

	//CUT AND REDO!
	myMapCopy = myMap;

	iter = myMap.begin();

	while (myMap.size() > 0)	//while not empty
	{
		if (iter == myMap.end()) iter = myMap.begin();
		calcVal = DoOperation(std::get<0>(iter->second), std::get<1>(iter->second), std::get<2>(iter->second));
		if (!calcVal.second)	//was not computed, next element!
		{
			++iter;
		}
		else					//was computed!
		{
			v1 = iter->first;
			myValSet.insert(std::make_pair(iter->first, calcVal.first));
			myMap.erase(iter); //consider it done; iter points to end
			iter = myMap.end();
			//update all values!
			for (auto & innerIter  : myMap)
			{
				if (v1.compare(std::get<1>(innerIter.second)) == 0)
					std::get<1>(innerIter.second) = std::to_string(calcVal.first);
				if (v1.compare(std::get<2>(innerIter.second)) == 0)
					std::get<2>(innerIter.second) = std::to_string(calcVal.first);
			}
		}
	}
	myAnsw.first = myValSet["a"];

	myValSet.clear();
	//CUT AND REDO!
	myMap = myMapCopy;	//restore!


	iter = myMap.begin();	//output, 
	
	myMap.erase("b");
	myMap.insert(std::make_pair("b", std::make_tuple(smmConst::FAILED_OP, "", std::to_string(myAnsw.first))));

	while (myMap.size() > 0)	//while not empty
	{
		if (iter == myMap.end()) iter = myMap.begin();
		calcVal = DoOperation(std::get<0>(iter->second), std::get<1>(iter->second), std::get<2>(iter->second));
		if (!calcVal.second)	//was not computed, next element!
		{
			++iter;
		}
		else					//was computed!
		{
			v1 = iter->first;
			myValSet.insert(std::make_pair(iter->first, calcVal.first));
			myMap.erase(iter); //consider it done; iter points to end
			iter = myMap.end();
			//update all values!
			for (auto& innerIter : myMap)
			{
				if (v1.compare(std::get<1>(innerIter.second)) == 0)
					std::get<1>(innerIter.second) = std::to_string(calcVal.first);
				if (v1.compare(std::get<2>(innerIter.second)) == 0)
					std::get<2>(innerIter.second) = std::to_string(calcVal.first);
			}
		}
	}
	myAnsw.second = myValSet["a"];


	return myAnsw;
}