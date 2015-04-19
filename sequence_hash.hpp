/* 
 * File:   sequence_hash.hpp
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
 * Created on 12 February 2015, 00:00
 */

#ifndef SEQUENCE_HASH_HPP
#define	SEQUENCE_HASH_HPP

#include <map>
#include <bitset>
#include <vector>
#include <unordered_map>
#include "seq_pointer_hash.hpp"
#include "parserTree.hpp"
#include <set>
#include "parserTree.hpp"

#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif

using namespace std;

class seq_pointer_hash;

class sequence_hash {
    friend ostream &operator << (ostream &, sequence_hash &);
    friend class seq_pointer_hash;
public:
    sequence_hash();
	sequence_hash(parserTree *tree);
    sequence_hash(const sequence_hash& orig);
    sequence_hash append(classType var, dataType item);
    sequence_hash append(pair<classType, dataType> pare){return this->append(pare.first, pare.second);}
    sequence_hash assemble(classType var, dataType item);
    sequence_hash assemble(pair<classType, dataType> pare){return this->assemble(pare.first, pare.second);}
    container tail();
    int in(int);
    int getSize(){return size;}
    int empty();
    virtual pairSet itemList();
    int getTailMax(){return tailMax;}
	virtual bool valid(){return validity;}
    seq_pointer_hash begin();
    seq_pointer_hash end();
	bool hasEval(){return evaluator != NULL;}
protected:
    vector <container> elements;
    int size;
    int tailMax;
	bool validity;
	parserTree *evaluator;
	unordered_map <hashConv, bool> tokenSet;
};
#endif	/* SEQUENCE_HASH_HPP */

