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
#include <set>
#include "seq_pointer.hpp"
using namespace std;
#define dataType int
#define container set<dataType>
class seq_pointer;

class sequence_hash {
    friend ostream &operator << (ostream &, sequence_hash &);
    friend class seq_pointer;
public:
    sequence_hash();
    sequence_hash(vector <container>);
    sequence_hash(const sequence_hash& orig);
    virtual ~sequence_hash();
//    sequence_hash proyection(int item);
//    sequence_hash proyection(int item, sequence_hash prefix);
    sequence_hash append(int item);
    sequence_hash assemble(int item);
    container tail();
    seq_pointer tail_pointer();
    int in(int);
    int getSize(){return size;}
    int empty();
    seq_pointer begin();
    seq_pointer end();
private:
    vector <container> elements;
    int size;
};

#endif	/* SEQUENCE_HASH_HPP */

