/* 
 * File:   prefixSpan.hpp
 * Author: Agustin
 *
 * Created on 24 February 2015, 13:36
 */

#ifndef PREFIXSPAN_HASH_GAPPED_HPP
#define	PREFIXSPAN_HASH_GAPPED_HPP

#include <cstdlib>
#include "sequence_hash.hpp"
#include "seq_pointer_hash.hpp"
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

void __prefixSpan__Parameterized(pairSet &, int, sequence_hash &, vector <seq_pointer_hash> &, int);
void prefixSpanParameterized(int, vector <sequence_hash> &, int);


#endif	/* PREFIXSPAN_HPP */

