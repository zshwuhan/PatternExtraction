/* 
 * File:   seq_pointer.hpp
 * Author: Agustin
 *
 * Created on 22 February 2015, 14:05
 */
//UNFINISHED
#ifndef SEQ_POINTER_HASH_HPP
#define	SEQ_POINTER_HASH_HPP

#include <map>
#include <bitset>
#include <vector>
#include <unordered_map>
#include "sequence_hash.hpp"
using namespace std;
#define dataType int
#define classType int
#define container unordered_map<classType, dataType>

class sequence_hash;

class seq_pointer_hash {
    friend int match(seq_pointer_hash &, seq_pointer_hash &);
public:
    seq_pointer_hash();
    seq_pointer_hash(sequence_hash *, vector<container>::iterator, vector<container>::iterator);
    seq_pointer_hash(const seq_pointer_hash& orig);
    int operator ==(seq_pointer_hash &);
    int operator !=(seq_pointer_hash &);
    void skip();
    bool getWildcard(){return wildcard;}
    bool null(){return current==end;}
    seq_pointer_hash proyect(classType, dataType);
    seq_pointer_hash proyect(classType, dataType, sequence_hash &);
    virtual ~seq_pointer_hash();
    void __dump__();
private:
    bool wildcard;
    vector<container>::iterator current;
    vector<container>::iterator end;
    sequence_hash * source;
    //int seqID;
    
};

#endif	/* SEQ_POINTER_HPP */

