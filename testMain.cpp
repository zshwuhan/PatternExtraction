#include "parserTree.hpp"
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main(){
	string test;
	cin>>test;
	parserTree tree = shuntingYard(test);
	unordered_map<int, bool> testMap;
	testMap[1]=1;
	testMap[2]=1;
	testMap[3]=1;
	cout<<tree.eval(testMap);
	return 0;
}