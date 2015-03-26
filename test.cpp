#include <iostream>
using namespace std;
#include <cstring>
#include <cstdlib>
#include "prefixSpan_hash.hpp"
#include "prefixSpan_hash_parameterized.hpp"
#include "sequence_hash.hpp"
#include "seq_pointer_hash.hpp"
#include "helperFunctions_hash.hpp"
#include "parserTree.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

int main(){
	string t1 = "3:2v2:x";
	parserTree tree = shuntingYard(t1);
/*	unordered_map<int, bool> testCase;
	testCase[convert(make_pair(3,3))]=true;
	testCase[convert(make_pair(1,2))]=true;
	testCase[convert(make_pair(3,0))]=true;
	testCase[convert(make_pair(1,0))]=true;
	testCase[convert(make_pair(3,1))]=true;
	testCase[convert(make_pair(2,0))]=true;
	testCase[convert(make_pair(2,2))]=true;
	tree.print();
	cout<<tree.eval(testCase)<<'\n';
*/
	string test;
	cin>>test;
	tree = shuntingYard(test);
	sequence_hash_parser * jormungand = new sequence_hash_parser(tree);
	sequence_hash_parser *alt = new sequence_hash_parser;
	*alt = *jormungand;
	alt =  (sequence_hash_parser *)(alt->append(3,3)->append(1,2)->append(3,1)->assemble(2,2));
	cout<<alt->valid()<<'\n';
	cout<<*alt<<'\n';
	cin>>test;
	sequencer(jormungand, test, true);
	cout<<jormungand->valid()<<'\n';
	cout<<*jormungand<<'\n';	
}