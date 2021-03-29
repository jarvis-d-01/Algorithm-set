#include <iostream>
#include "Sort.h"
#include "DynamicPlanning.h"
#include <string>

using namespace N;
using namespace DynamicPlanning;
using std::string;

int main()
{
    vector<int> v = { 1,2,3,-9,3,9,0,11 };
    
    DP dp;

    int n = 5, V = 8;
    vector<int> w = { 3,5,1,2,2 };
    vector<int> c = { 4,5,2,1,3 };

    int val = dp.bag_full(n, w,c,V);

    std::cout << val << std::endl;
    
}
