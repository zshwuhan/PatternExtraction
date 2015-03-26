/* 
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Applied Artificial Intelligence and Pattern Recognition Research Group (GRPIAA)
 *
 */

#ifndef SEQUENCE_HASH_HPP
#define	SEQUENCE_HASH_HPP

#include <map>
#include <bitset>
#include <vector>
#include <unordered_map>
#include "seq_pointer_hash.hpp"
#include <set>

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
    sequence_hash(vector <container>);
    sequence_hash(const sequence_hash& orig);
    virtual ~sequence_hash();
//    sequence proyection(int item);
//    sequence proyection(int item, sequence prefix);
    virtual sequence_hash *append(classType var, dataType item);
    virtual sequence_hash *append(pair<classType, dataType> pare){return this->append(pare.first, pare.second);}
    virtual sequence_hash *assemble(classType var, dataType item);
    virtual sequence_hash *assemble(pair<classType, dataType> pare){return this->assemble(pare.first, pare.second);}
    container tail();
    int in(int);
    int getSize(){return size;}
    int empty();
    virtual pairSet itemList();
    int getTailMax(){return tailMax;}
	virtual bool valid(){return true;}
    seq_pointer_hash begin();
    seq_pointer_hash end();
protected:
    vector <container> elements;
    int size;
    int tailMax;
};
#include "parserTree.hpp"

class sequence_hash_parser: public sequence_hash{
public:
	sequence_hash_parser(){validity = false;}
	sequence_hash_parser(parserTree parser){evaluator = parser; validity = false;}
	//MISSING IMPLEMENTATION
    sequence_hash_parser(const sequence_hash_parser& orig);
	//MISSING IMPLEMENTATION
    sequence_hash *append(classType var, dataType item);
    sequence_hash *append(pair<classType, dataType> pare){return this->append(pare.first, pare.second);}
    sequence_hash *assemble(classType var, dataType item);
    sequence_hash *assemble(pair<classType, dataType> pare){return this->assemble(pare.first, pare.second);}
	bool valid(){return validity;}
protected:
	bool validity;
	//Pointer to Tree should warrant consideration (after finishing cleanup)
	parserTree evaluator;
	unordered_map <hashConv, bool> tokenSet;
};
#endif	/* SEQUENCE_HASH_HPP */

