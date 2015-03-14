/* 
 * File:   prefixSpan.hpp
 * Author: Agustin
 *
 * Created on 24 February 2015, 13:36
 */

#ifndef PREFIXSPAN_HASH_HPP
#define	PREFIXSPAN_HASH_HPP

#include <cstdlib>
#include "sequence_hash.hpp"
#include "seq_pointer_hash.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#define dataType int
#define classType int
#define hashConv int
#define pairSet set<pair<classType, dataType>>
#define container unordered_map<classType, dataType>
#define bit16 65535

using namespace std;

container appendProyection( pairSet, vector <seq_pointer_hash> &, int, sequence_hash &, unordered_map <hashConv, vector<seq_pointer_hash> >);
void assembleProyection(pairSet::iterator, pairSet::iterator, vector <seq_pointer_hash> &, int, sequence_hash &, unordered_map <hashConv, vector<seq_pointer_hash> >);
void retrieve(pairSet &, sequence_hash);
void dump(unordered_map <hashConv, int> &, pairSet);
void copyOver(unordered_map <hashConv, int>, int, pairSet &);
void __prefixSpan__(pairSet &, int, sequence_hash &, vector <seq_pointer_hash> &);
void prefixSpan(int, vector <sequence_hash> &);


#endif	/* PREFIXSPAN_HPP */

