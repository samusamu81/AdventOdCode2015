//// AdventOfCode1_15.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
////
//
//#include <iostream>
//#include <fstream>
//#include <map>
//#include <set>
//#include <vector>
//#include <sstream>
//#include "./hpp/MD5.hpp"
//#include <deque>
//#include <algorithm>
//#include "smmComplex.hpp"
//#include "AoC20.hpp"
//#include "smmComuni.hpp"
//#include "smmMatrix.hpp"
//
//int  AoC1_15A()
//{
//    std::ifstream myFileInp;
//    char c;
//    int counter = 0;
//    myFileInp.open(".\\Test1_15.txt", std::ifstream::in);
//    myFileInp >> c;
//    while (myFileInp.good())
//    {
//        switch (c)
//        {
//        case '(':
//            counter++;
//            break;
//        case ')':
//            counter--;
//            break;
//        default:
//            throw new std::exception;
//        }
//        myFileInp >> c;
//    }
//    myFileInp.close();
//    return counter;
//
//}
//int  AoC1_15B()
//{
//    std::ifstream myFileInp;
//    char c;
//    int counter = 0, pos = 1;
//    myFileInp.open(".\\Test1_15.txt", std::ifstream::in);
//    myFileInp >> c;
//    while (myFileInp.good())
//    {
//        switch (c)
//        {
//        case '(':
//            counter++;
//            break;
//        case ')':
//            counter--;
//            break;
//        default:
//            throw new std::exception;
//        }
//        if (counter == -1) return pos;
//        myFileInp >> c;
//        pos++;
//    }
//    myFileInp.close();
//    return 0;
//
//}
//std::pair<int,int> AoC2_15()
//{
//     std::ifstream myFileInp;
//    char x;
//    int RunningArea = 0, area, miniPerim, volume, runningPerim = 0;
//    myFileInp.open(".\\Test2_15.txt", std::ifstream::in);
//    int a, b, c, large;
//    while (myFileInp.good())
//    {
//        myFileInp >> a >> x >> b >> x >> c;
//        large = (a > b ? a : b);
//        large = (large > c ? large : c);
//        
//        volume = a * b * c;
//        area = (a * b + a * c + b * c) * 2 + volume / large;
//        RunningArea += area;
//
//        miniPerim = 2 * (a + b + c - large);
//        runningPerim += volume;
//        runningPerim += miniPerim;
//
//    }
//    myFileInp.close();
//    return std::make_pair(RunningArea, runningPerim);
//}
// int AoC3_15A()
// {
//     std::ifstream myFileInp;
//     char c;
//     myFileInp.open(".\\Test3_15.txt", std::ifstream::in);
//     std::set<std::pair<int, int>> visitedHouses;
//     std::pair <int, int> currHouse = std::make_pair(0, 0);
//
//     visitedHouses.insert(currHouse); //prima casa
//     myFileInp >> c;
//     while (myFileInp.good())
//     {
//         switch (c)
//         {
//         case '^':
//             currHouse.first++;
//             break;
//         case 'v':
//             currHouse.first--;
//             break;
//         case '>':
//             currHouse.second++;
//             break;
//         case '<':
//             currHouse.second--;
//             break;
//         default:
//             throw new std::exception;
//         }
//
//         visitedHouses.insert(currHouse);
//
//         myFileInp >> c;
//     }
//     myFileInp.close();
//     return (int) visitedHouses.size();
// }
// int AoC3_15B()
// {
//     std::ifstream myFileInp;
//     char c;
//     myFileInp.open(".\\Test3_15.txt", std::ifstream::in);
//     bool isRealSanta = true;
//     std::set<std::pair<int, int>> visitedHousesSanta, visitedHousesRoboSanta;
//     std::pair <int, int> currHouseSanta = std::make_pair(0, 0), currHouseRoboSanta = std::make_pair(0, 0);
//
//     visitedHousesSanta.insert(currHouseSanta); //prima casa
//     visitedHousesRoboSanta.insert(currHouseRoboSanta);
//     std::pair<int, int>* ptrCurrHouse;
//     std::set<std::pair<int, int>>* ptrVisitedHouse;
//
//
//
//     myFileInp >> c;
//     while (myFileInp.good())
//     {
//         ptrCurrHouse = (isRealSanta ? &currHouseSanta : &currHouseRoboSanta);
//         ptrVisitedHouse = (isRealSanta ? &visitedHousesSanta : &visitedHousesRoboSanta);
//         isRealSanta=!isRealSanta;
//         
//
//         switch (c)
//         {
//         case '^':
//             ptrCurrHouse->first++;
//             break;
//         case 'v':
//             ptrCurrHouse->first--;
//             break;
//         case '>':
//             ptrCurrHouse->second++;
//             break;
//         case '<':
//             ptrCurrHouse->second--;
//             break;
//         default:
//             throw new std::exception;
//         }
//         ptrVisitedHouse->insert(*ptrCurrHouse);
//
//         myFileInp >> c;
//     }
//     myFileInp.close();
//     visitedHousesSanta.insert(visitedHousesRoboSanta.begin(), visitedHousesRoboSanta.end());
//     
//     return (int) visitedHousesSanta.size();
// }
//
//
// unsigned int AoC4_15()
// {
//    //per passare da un puzzle all'altro:
//    //cambiare lunghezza shAnsw = answ.substr(0, 6); o shAnsw = answ.substr(0, 5);
//    //cambiare uscita while con "000000" oppure "00000";
//
//     std::string secretKey = "yzbqklnj", answ, shAnsw;
//    unsigned int myNum = 0;
//    std::ostringstream oss;
//    
//    
//    do
//    {
//        oss.clear();
//        oss.str("");
//        oss << secretKey << myNum;
//        shAnsw = oss.str();
//        answ = str2MD5(shAnsw);
//        shAnsw = answ.substr(0, 6);
//        if (myNum %5000 ==0)
//        {
//            std::cout << myNum << "\t\t" << answ << "\t" << shAnsw << std::endl;;
//        }
//        myNum++;
//        
//    } while (shAnsw.compare("000000") != 0);
//    
//    myNum--; //Undo last ++
//    return myNum;
// }
// bool twoLetters(const std::string &x)
// {
//     size_t i;
//     for (i = 0; i < x.length() - 1; i++)
//         if (x.at(i) == x.at(i + (size_t) 1)) return true;
//     return false;
// }
// unsigned int countVowels(const std::string& x)
// {
//
//     unsigned int i, tot = 0;
//     for (i = 0; i < x.length(); i++)
//     {
//         switch (x.at(i))
//         {
//         case 'a':
//         case 'e':
//         case 'i':
//         case 'o':
//         case 'u':
//             tot++;
//         }
//     }
//     return tot;
// }
// bool forbiddenSequence(const std::string& x)
// {
//     
//     size_t i, beg;
//     std::vector<std::string> forb = { "ab", "cd", "pq", "xy" };
//     for (i = 0; i < forb.size(); i++)
//     {
//         beg = x.find_first_of(forb[i].at(0));
//         if (beg != std::string::npos && beg < x.length() - 1)
//             if (x.at(beg + (size_t) 1) == forb[i].at(1)) return true;
//     }
//     return false;
// }
// bool isNice(std::string x, bool printTrue = false, bool printFalse = false)
// {
//     bool t1 , t2, t3, p= (printTrue || printFalse);
//     int nVow;
//     t1 = !forbiddenSequence(x);
//     nVow = countVowels(x);
//     t2 = nVow >= 3;
//     t3 = twoLetters(x);
//     /*/if (printTrue || printFalse)
//     {
//         cout << x << "\t";
//         cout << printTrue ? t1 : "";
//         cout << printFalse ? t1 : "";
//         cout << "\t";
//         cout << printTrue ? t2 : "";
//         cout << printFalse ? t2 : "";
//         cout << "\t";
//         cout << printTrue ? t3 : "";
//         cout << printFalse ? t3 : "";
//         cout << endl;
//     }*/
//     return t1 && t2 && t3;
// }
// unsigned int AoC5_15()
// {
//     std::ifstream myFileInp;
//     std::string str;
//     unsigned int total = 0;
//     myFileInp.open(".\\Test5_15.txt", std::ifstream::in);
//     myFileInp >> str;
//     while (myFileInp.good())
//     {
//         total+= isNice(str) ? 1 : 0;
//         myFileInp >> str;
//     }
//     myFileInp.close();
//     return total;
// }
//
//
//
// 
//
//
// std::pair<unsigned int, unsigned int> countFullEmptySeat(std::vector<std::vector<char>> seats, size_t x, size_t y)
// {
//     const char  VUOTO = 'L',
//         PIENO = '#',
//         PAV = '.';
//     unsigned int answ1 = 0, answ2 = 0 ;
//     size_t ITER = 0;
//     x--, y--;
//     for (ITER = 0; ITER < 9; ITER++)
//     {
//         answ1 += seats[x + (ITER % 3)][y + ITER / 3] == PIENO ? 1 : 0;
//         answ2 += seats[x + (ITER % 3)][y + ITER / 3] == VUOTO ? 1 : 0;
//         answ2 += seats[x + (ITER % 3)][y + ITER / 3] == PAV ? 1 : 0;
//     }
//     
//     x++, y++;
//     answ1 -= seats[x][y] == PIENO ? 1 : 0;
//     answ2 -= seats[x][y] == VUOTO ? 1 : 0;
//     return std::make_pair(answ1, answ2);
// }
//
// void printTable(std::vector<std::vector<char>> tab)
// {
//     unsigned int i, j;
//     for (i = 0; i < tab.size(); i++)
//     {
//         for (j = 0; j < tab[i].size(); j++)
//             std::cout << tab[i][j];
//         std::cout << std::endl;
//     }
//     std::cout << std::endl<< std::endl;
// }
//
//
//
//
//
//
// void genericReader()
// {
//     std::ifstream myFileInp;
//     std::vector<int> lista;
//    int n;
//    myFileInp.open(".\\Test9_20.txt", std::ifstream::in);
//    myFileInp >> n;
//    while (myFileInp.good())
//    {
//
//        lista.push_back(n);
//        myFileInp >> n;
//    }
//    myFileInp.close();
//    
// }
// int main(int argc, char* argv[])
// {
//     std::pair <size_t, size_t> myAnsw;
//     std::pair <size_t, std::string> myAnsw2;
//
//     //std::cout << "Problema 1 Anno 2020:" << std::endl;
//     //myAnsw = AoC1_20();
//     //std::cout<< myAnsw.first<<"\t"<<myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 2 Anno 2020:" << std::endl;
//     //myAnsw = AoC2_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 3 Anno 2020:" << std::endl;
//     //myAnsw = AoC3_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//     //
//     //std::cout << "Problema 4 Anno 2020:" << std::endl;
//     //myAnsw = AoC4_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 5 Anno 2020:" << std::endl;
//     //myAnsw = AoC5_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 6 Anno 2020:" << std::endl;
//     //myAnsw = AoC6_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 7 Anno 2020:" << std::endl;
//     //myAnsw = AoC7_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//     
//     //std::cout << "Problema 8 Anno 2020:" << std::endl;
//     //myAnsw = AoC8_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//     //
//     //std::cout << "Problema 9 Anno 2020:" << std::endl;
//     //myAnsw = AoC9_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 10 Anno 2020:" << std::endl;
//     //myAnsw = AoC10_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 11 Anno 2020:" << std::endl;
//     //myAnsw = AoC11_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 12 Anno 2020:" << std::endl;
//     //myAnsw = AoC12_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 13 Anno 2020:" << std::endl;
//     //myAnsw = AoC13_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 14 Anno 2020:" << std::endl;
//     //myAnsw = AoC14_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 15 Anno 2020:" << std::endl;
//     //std::cout << "Ci mette molto (qualche minuto). Pazientare" << std::endl;
//     //myAnsw = AoC15_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 16 Anno 2020:" << std::endl;
//     //myAnsw = AoC16_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 17 Anno 2020:" << std::endl;
//     //myAnsw = AoC17_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 18 Anno 2020:" << std::endl;
//     //myAnsw = AoC18_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     std::cout << "Problema 19 Anno 2020:" << std::endl;
//     myAnsw = AoC19_20();
//     std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//          
//     //std::cout << "Problema 20 Anno 2020:" << std::endl;
//     //myAnsw = AoC20_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 21 Anno 2020:" << std::endl;
//     //myAnsw2 = AoC21_20();
//     //std::cout << myAnsw2.first << "\t" << myAnsw2.second << std::endl << std::endl;
//     
//     //std::cout << "Problema 22 Anno 2020:" << std::endl;
//     //myAnsw = AoC22_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 23 Anno 2020:" << std::endl;
//     //myAnsw = AoC23_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     //std::cout << "Problema 24 Anno 2020:" << std::endl;
//     //myAnsw = AoC24_20();
//     //std::cout << myAnsw.first << "\t" << myAnsw.second << std::endl << std::endl;
//
//     return 0;
// }
