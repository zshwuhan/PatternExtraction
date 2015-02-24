/* 
 * File:   prefixSpan.hpp
 * Author: Agustin
 *
 * Created on 24 February 2015, 13:36
 */

#ifndef PREFIXSPAN_HPP
#define	PREFIXSPAN_HPP

#include <cstdlib>
#include "sequence_hash.hpp"
#include "seq_pointer.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#define dataType int
#define container set<dataType>
#define bit16 65535

using namespace std;

inline dataType cut(dataType data);
inline int classComparison(dataType, dataType);
inline int check(sequence_hash, dataType);
container appendProyection( container, vector <seq_pointer> &, int, sequence_hash &, unordered_map <dataType, vector<seq_pointer> >);
void assembleProyection(container::iterator, container::iterator, vector <seq_pointer> &, int, sequence_hash &, unordered_map <dataType, vector<seq_pointer> >);
void retrieve(container &, sequence_hash);
void dump(unordered_map <dataType, int> &, container);
void copyOver(unordered_map <dataType, int>, int, container &);
void __prefixSpan__(container &, int, sequence_hash &, vector <seq_pointer> &);
void prefixSpan(int, vector <sequence_hash> &);


#endif	/* PREFIXSPAN_HPP */

