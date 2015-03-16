#include <cstdlib>
#include "seq_pointer_hash.hpp"
#include "sequence_hash.hpp"
#include "prefixSpan_hash.hpp"
#include "prefixSpan_hash_parameterized.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

using namespace std;

//Checks that appendable field higher than the highest element already in tuple(or just jumps to uniqueCandidates lowest element higher than highest appending
//and then does one check if lower than just move until check works)
void __prefixSpan__Parameterized(pairSet &uniqueElements, int threshold, sequence_hash &prefix, vector <seq_pointer_hash> &database, int parameter){
    unordered_map <hashConv, vector<seq_pointer_hash> > projDatabaseAs;
    classType temp = prefix.getTailMax();
    pairSet::iterator assemblyStart = uniqueElements.begin();
    while(assemblyStart != uniqueElements.end() && (assemblyStart->first <= temp)){++assemblyStart;}
    assembleProyection(assemblyStart, uniqueElements.end(), database, threshold, prefix, projDatabaseAs);
	unordered_map <hashConv, vector<seq_pointer_hash> >::iterator start, end; 
	if ((size_t)parameter < prefix.tail().size()){
		pairSet newUnique;
		unordered_map <hashConv, vector<seq_pointer_hash> > projDatabaseApp;
		newUnique = appendProyection(uniqueElements, database, threshold, prefix, projDatabaseApp);
		start = projDatabaseApp.begin(); end = projDatabaseApp.end();
		while(start!=end){
			sequence_hash appended = prefix;
			appended = appended.append(deconvert(start->first));
			__prefixSpan__Parameterized(newUnique, threshold, appended, start->second, parameter);
			++start;
		}
	}
    start = projDatabaseAs.begin(); end = projDatabaseAs.end();
    while(start!=end){
        sequence_hash assembled = prefix;
        assembled = assembled.assemble(deconvert(start->first));
        __prefixSpan__Parameterized(uniqueElements, threshold, assembled, start->second, parameter);
        ++start;
    }return;
}

void prefixSpanParameterized(int threshold, vector <sequence_hash> &database, int parameter){
    vector <seq_pointer_hash> newDatabase;
    pairSet uniqueElements;
    unordered_map <hashConv, int> freq;
    vector <sequence_hash>::iterator start, finish; start = database.begin(); finish = database.end();
    while(start!=finish){
        pairSet items;
        retrieve(items, *start);
        seq_pointer_hash p1 = start->begin();
        newDatabase.push_back(p1);
        dump(freq, items);
        ++start;
    }
    copyOver(freq, threshold, uniqueElements);
    //call missing generating the sequences for the first round, parallelisable to some degree
    //INSERT ITERATION OVER uniqueElements and CALL TO PATTERN EXTRACTION HERE |
    //                                                                         V
    unordered_map <hashConv, vector<seq_pointer_hash>> projDatabaseApp;
    sequence_hash ePrefix;
    appendProyection(uniqueElements, newDatabase, threshold, ePrefix, projDatabaseApp);   
    unordered_map <hashConv, vector<seq_pointer_hash> >::iterator starto, endo; starto = projDatabaseApp.begin(); endo = projDatabaseApp.end();
    while(starto!=endo){
        sequence_hash appended;
        appended = appended.append(deconvert(starto->first));
        __prefixSpan__Parameterized(uniqueElements, threshold, appended, starto->second, parameter);
        ++starto;
    }
    return;
}
