C++ shell
cpp.sh
online C++ compiler
about cpp.sh


1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
#include <iostream>
#include <cstdlib>
using namespace std;
struct gameResultType{
    unsigned int numToss;
    unsigned int cash;
};
gameResultType coinToss(unsigned int initial, unsigned int target){
    gameResultType Result = {
        .numToss = 0,
        .cash = initial
    };
    
    while ( (Result.cash > 0) && (Result.cash < target) ){
        unsigned int toss = rand() % 1024;
        Result.numToss++;
        unsigned int moneyPool = Result.cash / 2;
        
RunGet URL
optionscompilationexecution
17
12156
 
Exit code: 0 (normal program termination)
C++ Shell, 2014-2015
