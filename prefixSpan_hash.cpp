/* 
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Applied Artificial Intelligence and Pattern Recognition Research Group (GRPIIA)
 *
 */

#include <cstdlib>
#include "seq_pointer_hash.hpp"
#include "sequence_hash.hpp"
#include "prefixSpan_hash.hpp"
#include "helperFunctions_hash.hpp"
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


pairSet appendProyection( pairSet candidates,       vector <seq_pointer_hash> &database, //
                            int threshold,              sequence_hash &prefix,          //
                            unordered_map <hashConv, vector<seq_pointer_hash> > &exit){
    
    pairSet::iterator candStart, candEnd; candStart = candidates.begin(); candEnd = candidates.end();
    pairSet output;
    vector<seq_pointer_hash>::iterator dataStart, dataEnd, reset; dataStart = database.begin(); dataEnd = database.end();
    //Best spot for parallelism, do all of candidate threads and only thread 3 or 4 proyections at a time
    //to not bother with things that fail threshold pretty fast
    int limit = database.size() - threshold;
    while(candStart!=candEnd){
        vector <seq_pointer_hash> projectionResult;
        int complement =0;
        while((complement<=limit) && (dataStart!=dataEnd)){
            seq_pointer_hash p1 = dataStart->proyect(candStart->first, candStart->second);
            if (p1.null()){
                ++complement;
            }else{
                projectionResult.push_back(p1);
            }
            ++dataStart;
        }if(complement<=limit){
            sequence_hash printable = *(prefix.append(candStart->first, candStart->second));
            cout<<"Support : "<<database.size()-complement<< " Sequence: " <<printable<<'\n';
            exit.emplace(convert(*candStart), projectionResult);
            //Save projection result alongside the element it was meant for
            output.insert(*candStart);
        }
        dataStart = database.begin();
        ++candStart;
    }
    return output;
}



void assembleProyection(pairSet::iterator &candStart,  pairSet::iterator candEnd,
                            vector <seq_pointer_hash> &database,                             //
                            int threshold,              sequence_hash &prefix,          //
                            unordered_map <hashConv, vector<seq_pointer_hash> > &exit){
    vector<seq_pointer_hash>::iterator dataStart, dataEnd, reset; dataStart = database.begin(); dataEnd = database.end();
    //Best spot for parallelism, do all of candidate threads and only thread 3 or 4 proyections at a time
    //to not bother with things that fail threshold pretty fast
    int limit = database.size() - threshold;
    while(candStart!=candEnd){
        vector <seq_pointer_hash> projectionResult;
        int complement =0;
        while((complement<=limit) && (dataStart!=dataEnd)){
            seq_pointer_hash p1 = dataStart->proyect(candStart->first, candStart->second, prefix);
            if (p1.null()){
                ++complement;
            }else{
                projectionResult.push_back(p1);
            }
            ++dataStart;
        }if(complement<=limit){
            sequence_hash printable = *(prefix.assemble(candStart->first, candStart->second));
            cout<<"Support : "<<database.size()-complement<< " Sequence: " <<printable<<'\n';
            exit.emplace(convert(*candStart), projectionResult);
        }
        dataStart = database.begin();
        ++candStart;
    }
    return;       
} 

void retrieve(pairSet &items, sequence_hash seq){
    pairSet itemSet = seq.itemList();
    items.insert(itemSet.begin(), itemSet.end());
    return;
}
void dump(unordered_map <hashConv, int> &freq, pairSet items){
    pairSet::iterator start, finish; start=items.begin(); finish=items.end();
    while(start!=finish){ freq[convert(*start)]=++freq[convert(*start)]; ++start;}
    return;
}

//Copy Over Missing revision
void copyOver(unordered_map <hashConv, int> freq, int threshold, pairSet &uniqueElements){
    unordered_map <dataType, int>::iterator start, finish; start=freq.begin(); finish=freq.end();
    while(start!=finish){
        if(start->second>=threshold){
            uniqueElements.insert(deconvert(start->first));
        }++start;
    }
    return;
}


//Checks that appendable field higher than the highest element already in tuple(or just jumps to uniqueCandidates lowest element higher than highest appending
//and then does one check if lower than just move until check works)
void __prefixSpan__(pairSet &uniqueElements, int threshold, sequence_hash &prefix, vector <seq_pointer_hash> &database){
    unordered_map <hashConv, vector<seq_pointer_hash> > projDatabaseApp, projDatabaseAs;
    pairSet newUnique;
    newUnique = appendProyection(uniqueElements, database, threshold, prefix, projDatabaseApp);
    classType temp = prefix.getTailMax();
    pairSet::iterator assemblyStart = uniqueElements.begin();
    while(assemblyStart != uniqueElements.end() && (assemblyStart->first <= temp)){++assemblyStart;}
    assembleProyection(assemblyStart, uniqueElements.end(), database, threshold, prefix, projDatabaseAs);
    unordered_map <hashConv, vector<seq_pointer_hash> >::iterator start, end; start = projDatabaseApp.begin(); end = projDatabaseApp.end();
    while(start!=end){
        sequence_hash appended = prefix;
        appended = *(appended.append(deconvert(start->first)));
        __prefixSpan__(newUnique, threshold, appended, start->second);
        ++start;
    }
    start = projDatabaseAs.begin(); end = projDatabaseAs.end();
    while(start!=end){
        sequence_hash assembled = prefix;
        assembled = *(assembled.assemble(deconvert(start->first)));
        __prefixSpan__(uniqueElements, threshold, assembled, start->second);
        ++start;
    }return;
}

void prefixSpan(int threshold, vector <sequence_hash> &database){
    vector <seq_pointer_hash> newDatabase;
    pairSet uniqueElements;
    unordered_map <hashConv, int> freq;
    vector <sequence_hash>::iterator start, finish; start = database.begin(); finish = database.end();
    while(start!=finish){
        pairSet items;
        retrieve(items, *start);
        seq_pointer_hash p1 = start->begin();
        newDatabase.push_back(p1);
        dump(freq, items);
        ++start;
    }
    copyOver(freq, threshold, uniqueElements);
    //call missing generating the sequences for the first round, parallelisable to some degree
    //INSERT ITERATION OVER uniqueElements and CALL TO PATTERN EXTRACTION HERE |
    //                                                                         V
    unordered_map <hashConv, vector<seq_pointer_hash>> projDatabaseApp;
    sequence_hash ePrefix;
    appendProyection(uniqueElements, newDatabase, threshold, ePrefix, projDatabaseApp);   
    unordered_map <hashConv, vector<seq_pointer_hash> >::iterator starto, endo; starto = projDatabaseApp.begin(); endo = projDatabaseApp.end();
    while(starto!=endo){
        sequence_hash appended;
        appended = *(appended.append(deconvert(starto->first)));
        __prefixSpan__(uniqueElements, threshold, appended, starto->second);
        ++starto;
    }
    return;
}
