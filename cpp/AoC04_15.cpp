#include <map>
#include <string>
#include <sstream>
#include "..\hpp\MD5.hpp"

std::pair<long long int, long long int> AoC04_15(std::string secretKey)
{
    //per passare da un puzzle all'altro:
    //cambiare lunghezza shAnsw = answ.substr(0, 6); o shAnsw = answ.substr(0, 5);
    //cambiare uscita while con "000000" oppure "00000";
    int const LEN_1 = 5, LEN_2 = 6;

    std::string const S_1(LEN_1, '0'), S_2(LEN_2, '0');
    std::string const * strPtr;
    std::pair<long long int, long long int> myAnsw;
    std::string answ, shAnsw;
    unsigned int myNum = 0;
    std::ostringstream oss;
    
    for (int i = 0; i <= 1; ++i)        //length of the 0s string
    {
        myNum = 0;
        if (i == 0) 
            strPtr = &S_1; 
        else 
            strPtr = & S_2;
        do
        {
            oss.clear();
            oss.str("");
            oss << secretKey << myNum;
            shAnsw = oss.str();
            answ = str2MD5(shAnsw);
            shAnsw = answ.substr(0, 6);
            if (myNum % 5000 == 0)
            {
                std::cout << myNum << "\t\t" << answ << "\t" << shAnsw << std::endl;;
            }
            myNum++;

        } while (shAnsw.compare(*strPtr) != 0);

        myNum--; //Undo last ++
        if (i == 0) myAnsw.first = myNum; else myAnsw.second = myNum;
    }
    
    return myAnsw;
}