/* 
 * File:   sequence_hash.hpp
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
 */

#ifndef HELPERFUNCTIONS_HASH_HPP
#define	HELPERFUNCTIONS_HASH_HPP
#include <string>
#include "sequence_hash.hpp"
#include <vector>
#include <iostream>
using namespace std;

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

void manageTime(int);
void vectorPrint(vector <sequence_hash>);
hashConv convert(pair<classType, dataType>);
pair<classType, dataType> deconvert(hashConv);
void sequencer(sequence_hash &, string);
vector <sequence_hash> massSequencer(ifstream &, char *, int &);
vector <sequence_hash> massSequencer(ifstream &);


#endif	/* HELPERFUNCTIONS_HPP */

