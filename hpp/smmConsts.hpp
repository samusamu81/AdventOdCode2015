#pragma once
namespace smmConst      //da usare in for_each
{
	extern char separator;
	extern char trueSym;
	extern char falseSym;
	extern int not_found;
    enum direction
    {
        //todo: update failed with failed_dir
        FAILED = -1,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    enum bitw_op
    {
        FAILED_OP = -1,
        NOT,
        OR,
        AND,
        LSHIFT,
        RSHIFT
    };
}
