/* 
 * File:   main.cpp
 * Author: Agustin
 *
 * Created on 11 February 2015, 23:58
 */

#include <cstdlib>
#include "sequence_hash.hpp"
#include "seq_pointer.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#define dataType int
#define container set<dataType>
#define bit16 65535

using namespace std;

inline dataType cut(dataType data){
    return data & (bit16 << 16);
}

inline int check(sequence_hash prefix, dataType data){
    return cut((*(prefix.tail().rbegin())))<cut(data);
}

container appendProyection(container candidates, vector <seq_pointer> &database, int threshold, sequence_hash &prefix){
    container::iterator candStart, candEnd; candStart = candidates.begin(); candEnd = candidates.end();
    container output;
    vector<seq_pointer>::iterator dataStart, dataEnd, reset; dataStart = database.begin(); dataEnd = database.end();
    //Best spot for parallelism, do all of candidate threads and only thread 3 or 4 proyections at a time
    //to not bother with things that fail threshold pretty fast
    int limit = database.size() - threshold;
    
    while(candStart!=candEnd){
        vector <seq_pointer> projectionResult;
        int complement =0;
        while((complement<limit) && (dataStart!=dataEnd)){
            seq_pointer p1 = dataStart->proyect(*candStart);
            if (p1.null()){
                ++complement;
            }else{
                projectionResult.push_back(p1);
            }
        }if(complement<limit){
            sequence_hash printable = prefix.append(*candStart);
            cout<<printable<<" -> Support -> "<<database.size()-complement<<'\n';
        }
        dataStart = database.begin();
    }
    return output;
}

void assembleProyection(){
    
} 

//Separate function for empty initial sequence for efficiencyy (removes null prefix checks).
//Also builds uniqueElements set.
void patternExtraction(int threshold, vector <seq_pointer> &database){
}
//Checks that appendable field higher than the highest element already in tuple(or just jumps to uniqueCandidates lowest element higher than highest appending
//and then does one check if lower than just move until check works)
void patternExtraction(container &uniqueElements, int threshold, sequence_hash &prefix, vector <seq_pointer> &database){
    
}
/*
 * 
 */
int main(int argc, char** argv) {
    sequence_hash test;
    cout<<"Test Created"<<'\n';
    test = test.assemble(3);
    cout<<"Test Append 1"<<'\n';
    test = test.assemble(15);
    cout<<"Test Assemble 1"<<'\n';
    test = test.append(14);
    cout<<"Test Append 2"<<'\n';
    test = test.assemble(9);
    cout<<"Test Assemble 2"<<'\n';
    cout<<test.getSize()<<'\n';
    cout<<test<<'\n';
    seq_pointer p1 = test.begin();
    cout<<*p1<<'\n';
    ++p1;
    cout<<*p1<<'\n';
    ++p1;
    cout<<*p1<<'\n';
    p1.__dump__();
    ++p1; ++p1;
    seq_pointer p2 = (test.end());
    cout<<"p1 == p2: "<<(p1==p2)<<'\n';
    cout<<"p1 != p2: "<<(p1!=p2)<<'\n';
    seq_pointer p3 = test.begin();
    (p3.proyect(14)).__dump__();
    cout<<(p3.proyect(14)).null();
    return 0;
}

