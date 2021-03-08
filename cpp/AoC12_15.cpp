#ifndef DEBUG
#define DEBUG
#endif
#include <vector>
#include <iostream>
#include <sstream>
#include "../hpp/AoC2015.hpp"
#include "../hpp/smmComuni.hpp"

//std::vector<std::pair<size_t, size_t>> LargerIntervals(std::vector<std::pair<size_t, size_t>> const & origV)
//{
//	size_t i, j;
//	bool deleteMe;
//	std::vector<bool> addMeVect;
//	std::vector<std::pair<size_t, size_t>> myAnsw;
//	for (i = 0; i < origV.size(); i++)
//	{
//		
//		deleteMe = false;
//		for (j = 0; (j < origV.size()) && !deleteMe; j++)
//		{
//			if (i == j) continue;
//			deleteMe = (origV[i].first >= origV[j].first) && (origV[i].second <= origV[j].second);
//		}
//		addMeVect.push_back(!deleteMe);
//	}
//	
//	for (i = 0; i < origV.size(); i++)
//	{
//		if (addMeVect[i]) myAnsw.push_back(origV[i]);
//	}
//
//	return myAnsw;
//}



std::pair<size_t, size_t> MatchingParenthesis(std::string searchMe, size_t startPos)
{
	int numOpenParQ, numOpenParG;	//Q = [, G = {
	numOpenParG = numOpenParQ = 1;	//assume forward
	size_t f = startPos , b = startPos;
	
	while ((numOpenParG * numOpenParQ != 0) && (f != searchMe.length()))
	{
		switch (searchMe[f])
		{
		case '{':
			numOpenParG++;
			break;
		case '}':
			numOpenParG--;
			break;
		case '[':
			numOpenParQ++;
			break;
		case ']':
			numOpenParQ--;
			break;
		}
		f++;
	}

	if (f == searchMe.length()) f = 0;//place npos if not found
	f--;	//becomes npos if not found
	numOpenParG = numOpenParQ = -1;	//assume backward

	while ((numOpenParG * numOpenParQ != 0) && (b != std::string::npos))
	{
		switch (searchMe[b])
		{
		case '{':
			numOpenParG++;
			break;
		case '}':
			numOpenParG--;
			break;
		case '[':
			numOpenParQ++;
			break;
		case ']':
			numOpenParQ--;
			break;
		}
		b--;
	}

	if (b != std::string::npos)	b++;

#ifdef DEBUG

	if ((b == std::string::npos) || (f == std::string::npos))
		std::cout << "NPOS!" << std::endl;
	else if ((searchMe[b] == '{') && (searchMe[f] == '}'))
		std::cout << "GOOD!" << std::endl;
	else if ((searchMe[b] == '[') && (searchMe[f] == ']'))
		std::cout << "GOOD!" << std::endl;
	else
		std::cout << "BAD!" << std::endl;

#endif

	return std::make_pair(b, f);
}



std::string RemoveExtraReds(std::string searchMe)

{

	std::string findMe = "\"red\"";
	size_t found_val = 0, l;

	std::pair<size_t, size_t> myAnsw;
	std::vector<std::pair<size_t, size_t>> myRemove;
	std::vector<std::pair<size_t, size_t>>::iterator last;
	found_val--;	//string::npos?
	while (true)
	{
		found_val = searchMe.find(findMe, found_val + 1);
		if (found_val == std::string::npos) break;
		myAnsw = MatchingParenthesis(searchMe, found_val);
		
		if ((myAnsw.first == std::string::npos) || (myAnsw.second == std::string::npos)) break;
		
		if (searchMe[myAnsw.first] == '{') myRemove.push_back(myAnsw);
	} 
	
	
	//last = std::unique(myRemove.begin(), myRemove.end());	//multiple reds in the same parenthesis must be skipped
	//myRemove.erase(last, myRemove.end());
//	myRemove = LargerIntervals(myRemove);

	//check if indipendent! could be that one element is 5 100 and second in 77 92; second
	//no need to reverse!
	


	for (last = myRemove.begin(); last != myRemove.end(); ++last)
	{
#ifdef DEBUG
		std::cout << "*\t" << searchMe.substr(last->first, last->second - last->first + 1) << '\n' << std::endl;
#endif
		l = last->second - last->first + 1;	//
		searchMe.replace(last->first, l , l, ' ' );//fill with blanks!

	}
	return searchMe;
	

}




std::pair<long long int, long long int> AoC12_15(std::string fileName)
{
	std::pair<long long int, long long int> myAnsw;
	std::stringstream ss;
	std::string aStr;
	std::vector<std::string> fContent = Parser(fileName, ',', std::regex("[^+\\-0-9]*"));//whatever is not one of those!
	std::vector<std::pair<size_t, size_t>> myPos;
	size_t nextStart;
	long long int dummy = 0;
	std::vector<long long int> vInt;
	

	std::regex captureMe("[^+\\-0-9]*([+\\-]?[0-9]+)[^+\\-0-9]*");
	//[^+\\-0-9]*		not a + or - or a digit as long as you like
	//(					then capture
	//[+\\-]?			optional + or -
	//[0-9]+			at least one digit
	//)					end capture
	//[^+\\-0-9]*		not a + or - or a digit as long as you like


	std::regex redInside("\\{[^\\{\\}]*red[^\\{\\}]*\\}");  //whatever is not red! 

	//break it down:
	//	what is there			what it is in regex			what it means
	//	\\{						\{							An open {	followed by
	//	[^						[^							any char which is not
	//	\\{						\{								An open {			or
	//	\\}]					\}]								A close }
	//	\\}]					\}]								A close }
	//	*						*							as long as possible
	//	red						red							followed by the string "red"
	//  [^\\{\\}]*				[^\{\}]*					Not a bracket for as long as possible
	//	\\}						\}							the closing bracket

	//PART 1
	for (std::string & l : fContent)
		l = std::regex_replace(l, captureMe, "$1");

	vInt = VectorConverter(fContent, dummy);

	for (long long int i : vInt)
		myAnsw.first += i;


	//PART 2

	fContent = lineParser(fileName);//everything is in [0]
	aStr = fContent[0];
	
	aStr = RemoveExtraReds(aStr);

	
	ss.str(aStr);
	fContent = Parser(&ss, ',', std::regex("[^+\\-0-9]*"));	//from here, same as before; use default separatore (smmConst::separator)
	
	for (std::string& l : fContent)
		l = std::regex_replace(l, captureMe, "$1");

	vInt = VectorConverter(fContent, dummy);

	for (long long int i : vInt)
		myAnsw.second += i;

	return myAnsw;
}