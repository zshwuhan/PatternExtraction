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

inline dataType cut(dataType data){
    return data & (bit16 << 16);
}

inline int classComparison(dataType c1, dataType c2){
    return cut(c1)==cut(c2);
}

inline int check(sequence_hash prefix, dataType data){
    return cut((*(prefix.tail().rbegin())))<cut(data);
}

container appendProyection( container candidates,       vector <seq_pointer> &database, //
                            int threshold,              sequence_hash &prefix,          //
                            unordered_map <dataType, vector<seq_pointer> > &exit){
    
    container::iterator candStart, candEnd; candStart = candidates.begin(); candEnd = candidates.end();
    container output;
    vector<seq_pointer>::iterator dataStart, dataEnd, reset; dataStart = database.begin(); dataEnd = database.end();
    //Best spot for parallelism, do all of candidate threads and only thread 3 or 4 proyections at a time
    //to not bother with things that fail threshold pretty fast
    int limit = database.size() - threshold;
    while(candStart!=candEnd){
        vector <seq_pointer> projectionResult;
        int complement =0;
        //cerr<<prefix<<" + "<<*candStart<<":\n";////////////////////////////////////////////////////////
        while((complement<=limit) && (dataStart!=dataEnd)){
            //cerr<<"ORIGINAL: ";////////////////////////////////////////////////////////
            //dataStart->__dump__();////////////////////////////////////////////////////////
            seq_pointer p1 = dataStart->proyect(*candStart);
            //p1.__dump__(); ////////////////////////////////////////////////////////
            if (p1.null()){
                ++complement;
                if(p1.matched()) --complement;
            }else{
                projectionResult.push_back(p1);
            }
            ++dataStart;
        }if(complement<=limit){
            sequence_hash printable = prefix.append(*candStart);
            cout<<printable<<" -> Support -> "<<database.size()-complement<<'\n';
            exit.emplace(*candStart, projectionResult);
            //Save projection result alongside the element it was meant for
            output.insert(*candStart);
        }
        dataStart = database.begin();
        ++candStart;
    }
    return output;
}



void assembleProyection(container::iterator &candStart,  container::iterator candEnd,
                            vector <seq_pointer> &database,                             //
                            int threshold,              sequence_hash &prefix,          //
                            unordered_map <dataType, vector<seq_pointer> > &exit){
    vector<seq_pointer>::iterator dataStart, dataEnd, reset; dataStart = database.begin(); dataEnd = database.end();
    //Best spot for parallelism, do all of candidate threads and only thread 3 or 4 proyections at a time
    //to not bother with things that fail threshold pretty fast
    int limit = database.size() - threshold;
    while(candStart!=candEnd){
        vector <seq_pointer> projectionResult;
        int complement =0;
        //cerr<<prefix<<" + "<<*candStart<<":\n";////////////////////////////////////////////////////////
        while((complement<=limit) && (dataStart!=dataEnd)){
            dataType temp = *candStart;
            //cerr<<"ORIGINAL: ";////////////////////////////////////////////////////////
            //dataStart->__dump__();////////////////////////////////////////////////////////
            seq_pointer p1 = dataStart->proyect(temp, prefix);
            //p1.__dump__(); ////////////////////////////////////////////////////////
            if (p1.null()){
                ++complement;
                if(p1.matched()) --complement;
            }else{
                projectionResult.push_back(p1);
            }
            ++dataStart;
        }if(complement<=limit){
            sequence_hash printable = prefix.assemble(*candStart);
            cout<<"Support : "<<database.size()-complement<< " Sequence: " <<printable<<'\n';
            exit.emplace(*candStart, projectionResult);
            //Save projection result alongside the element it was meant for
        }
        dataStart = database.begin();
        ++candStart;
    }
    return;       
} 

//Separate function for empty initial sequence for efficiencyy (removes null prefix checks).
//Also builds uniqueElements set.
void retrieve(container &items, sequence_hash seq){
    seq_pointer pstart = seq.begin();
    seq_pointer pend = seq.end();
    while(pstart!=pend) {items.insert(*pstart); ++pstart;}
    return;
}
void dump(unordered_map <dataType, int> &freq, container items){
    container::iterator start, finish; start=items.begin(); finish=items.end();
    while(start!=finish){ freq[*start]=++freq[*start]; ++start;}
    return;
}
void copyOver(unordered_map <dataType, int> freq, int threshold,container &uniqueElements){
    unordered_map <dataType, int>::iterator start, finish; start=freq.begin(); finish=freq.end();
    while(start!=finish){
        if(start->second>=threshold){
            uniqueElements.insert(start->first);
        }++start;
    }
    return;
}


//Checks that appendable field higher than the highest element already in tuple(or just jumps to uniqueCandidates lowest element higher than highest appending
//and then does one check if lower than just move until check works)
void __prefixSpan__(container &uniqueElements, int threshold, sequence_hash &prefix, vector <seq_pointer> &database){
    //cerr<<"__________________________________________________________________________________________________________"<<'\n';/////////////////
    //cin.ignore(); ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unordered_map <dataType, vector<seq_pointer> > projDatabaseApp, projDatabaseAs;
    container newUnique;
    newUnique = appendProyection(uniqueElements, database, threshold, prefix, projDatabaseApp);
    dataType temp = *(prefix.tail().rbegin());
    container::iterator assemblyStart = upper_bound(uniqueElements.begin(), uniqueElements.end(),temp);  
    while(assemblyStart != uniqueElements.end() && classComparison(*assemblyStart, temp)){++assemblyStart;}
    assembleProyection(assemblyStart, uniqueElements.end(), database, threshold, prefix, projDatabaseAs);
    unordered_map <dataType, vector<seq_pointer> >::iterator start, end; start = projDatabaseApp.begin(); end = projDatabaseApp.end();
    //cerr<<"Append Size:" <<projDatabaseApp.size() <<"\n";///////////////////////////////////////////////////////////////////////
    while(start!=end){
        sequence_hash appended = prefix;
        appended = appended.append(start->first);
        __prefixSpan__(newUnique, threshold, appended, start->second);
        ++start;
    }
    start = projDatabaseAs.begin(); end = projDatabaseAs.end();
    //cerr<< "Assemble Size" <<projDatabaseAs.size() <<"\n"; ///////////////////////////////////////////////////////////////////////
    while(start!=end){
        sequence_hash assembled = prefix;
        assembled = assembled.assemble(start->first);
        __prefixSpan__(uniqueElements, threshold, assembled, start->second);
        ++start;
    }return;
}

void prefixSpan(int threshold, vector <sequence_hash> &database){
    //Potential for threading from sequence to pointer
    vector <seq_pointer> newDatabase;
    container uniqueElements;
    unordered_map <dataType, int> freq;
    vector <sequence_hash>::iterator start, finish; start = database.begin(); finish = database.end();
    while(start!=finish){
    //Potential for threading from sequence to pointer
        container items;
        retrieve(items, *start);
        seq_pointer p1 = start->begin();
        newDatabase.push_back(p1);
        dump(freq, items);
        ++start;
    }
    copyOver(freq, threshold, uniqueElements);
    //call missing generating the sequences for the first round, parallelisable to some degree
    //INSERT ITERATION OVER uniqueElements and CALL TO PATTERN EXTRACTION HERE |
    //                                                                         V
    unordered_map <int, vector<seq_pointer>> projDatabaseApp;
    sequence_hash ePrefix;
    appendProyection(uniqueElements, newDatabase, threshold, ePrefix, projDatabaseApp);   
    unordered_map <dataType, vector<seq_pointer> >::iterator starto, endo; starto = projDatabaseApp.begin(); endo = projDatabaseApp.end();
    while(starto!=endo){
        sequence_hash appended;
        appended = appended.append(starto->first);
        __prefixSpan__(uniqueElements, threshold, appended, starto->second);
        ++starto;
    }
    return;
}
