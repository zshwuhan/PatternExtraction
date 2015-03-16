/* 
 * File:   sequence_hash.hpp
 * Author: Agustin
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
#include <set>
using namespace std;
#ifndef dataType
    #define dataType int
    #define classType int
    #define hashConv int
    #define pairSet set<pair<classType, dataType>>
    #define container unordered_map<classType, dataType>
    #define bit16 65535
#endif
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
    sequence_hash append(classType var, dataType item);
    sequence_hash append(pair<classType, dataType> pare){return this->append(pare.first, pare.second);}
    sequence_hash assemble(classType var, dataType item);
    sequence_hash assemble(pair<classType, dataType> pare){return this->assemble(pare.first, pare.second);}
    container tail();
    int in(int);
    int getSize(){return size;}
    int empty();
    pairSet itemList();
    int getTailMax(){return tailMax;}
    seq_pointer_hash begin();
    seq_pointer_hash end();
private:
    vector <container> elements;
    int size;
    int tailMax;
};

#endif	/* SEQUENCE_HASH_HPP */

