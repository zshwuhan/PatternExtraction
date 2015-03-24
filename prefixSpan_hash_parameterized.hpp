/* 
 * File:   sequence_hash.hpp
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
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

void postprocess(sequence_hash prefix, unordered_map<string, int>, int);
pairSet appendProyection( pairSet, vector <seq_pointer_hash> &, int, sequence_hash &, unordered_map <hashConv, vector<seq_pointer_hash> > &, unordered_map<string, int> &);
void assembleProyection(pairSet::iterator&, pairSet::iterator, vector <seq_pointer_hash> &, int, sequence_hash &, unordered_map <hashConv, vector<seq_pointer_hash> > &, unordered_map<string, int> &);
void __prefixSpan__Parameterized(pairSet &, int, sequence_hash &, vector <seq_pointer_hash> &, unordered_map<string, int> &);
void prefixSpanParameterized(int, vector <sequence_hash> &, unordered_map<string, int> &);


#endif	/* PREFIXSPAN_HPP */

