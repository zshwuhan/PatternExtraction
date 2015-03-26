/* 
 * Author: Agustin Guevara Cogorno
 * Supervisor: Hugo Alatrista Salas
 * Employer: Pontificia Universidad Católica del Perú (PUCP) - Applied Artificial Intelligence and Pattern Recognition Research Group (GRPIAA)
 *
 */
 
#include <cstdlib>
#include "seq_pointer_hash.hpp"
#include "sequence_hash.hpp"
#include "prefixSpan_hash.hpp"
#include "prefixSpan_hash_parameterized.hpp"
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

void postprocess(sequence_hash *prefix, unordered_map<string, int> options, int support){
	if(prefix->valid()){
		if(((size_t)options["-minSseq"]<=(prefix->tail().size())) && (options["-minSize"]<=prefix->getSize())){
					cout<<"Support : "<<support<< " Sequence: " <<*prefix<<'\n';
				}
	}
}
			

pairSet appendProyectionParametrized( pairSet candidates,       vector <seq_pointer_hash> &database, //
                            int threshold,              sequence_hash &prefix,          //
                            unordered_map <hashConv, vector<seq_pointer_hash> > &exit,
							unordered_map <string, int> &options){
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
            if (p1.null()){++complement;}
            else{projectionResult.push_back(p1);}
            ++dataStart;
        }if(complement<=limit){
            exit.emplace(convert(*candStart), projectionResult);
            output.insert(*candStart);
        }
        dataStart = database.begin();
        ++candStart;
    }
    return output;
}



void assembleProyectionParametrized(pairSet::iterator &candStart,  pairSet::iterator candEnd, vector <seq_pointer_hash> &database,
                            int threshold, sequence_hash &prefix, unordered_map <hashConv, vector<seq_pointer_hash> > &exit,
							unordered_map <string, int> &options){
    vector<seq_pointer_hash>::iterator dataStart, dataEnd, reset; dataStart = database.begin(); dataEnd = database.end();
//*>
    int limit = database.size() - threshold;
    while(candStart!=candEnd){
        vector <seq_pointer_hash> projectionResult;
        int complement =0;
        while((complement<=limit) && (dataStart!=dataEnd)){
            seq_pointer_hash p1 = dataStart->proyect(candStart->first, candStart->second, prefix);
            if (p1.null()){++complement;}
            else{projectionResult.push_back(p1);}
            ++dataStart;
        }if(complement<=limit){
            exit.emplace(convert(*candStart), projectionResult);
        }
        dataStart = database.begin();
        ++candStart;
    }
    return;       
}

//Checks that appendable field higher than the highest element already in tuple(or just jumps to uniqueCandidates lowest element higher than highest appending
//and then does one check if lower than just move until check works)
void __prefixSpan__Parameterized(pairSet &uniqueElements, int threshold, sequence_hash *prefix, vector <seq_pointer_hash> &database, unordered_map<string, int> &options){
//PRINT IF CONDITIONS ARE MET
	postprocess(prefix, options, database.size());
//APPEND ONLY IF CURRENT ITEMSET ALREADY MEETS REQUIREMENTS
//APPEND ONLY IF CURRENT CANDIDATE SEQUENCE IS SMALLER THAN REQUIRED SIZE
	if ((size_t)options["-minSseq"] <= prefix->tail().size() && options["-maxSize"]>prefix->getSize()){
		unordered_map <hashConv, vector<seq_pointer_hash> >::iterator start, end; 
		pairSet newUnique;
		unordered_map <hashConv, vector<seq_pointer_hash> > projDatabaseApp;
		newUnique = appendProyectionParametrized(uniqueElements, database, threshold, *((sequence_hash *)prefix), projDatabaseApp, options);
		start = projDatabaseApp.begin(); end = projDatabaseApp.end();
		while(start!=end){
			sequence_hash *appended = prefix;
			appended = (appended->append(deconvert(start->first)));
			__prefixSpan__Parameterized(newUnique, threshold, appended, start->second, options);
			++start;
		}
//ASSEMBLE ONLY IF CURRENT PREFIX IS SMALLER THAN REQUIRED SIZE
	}if ((size_t)options["-maxSseq"] >= prefix->tail().size()){
		unordered_map <hashConv, vector<seq_pointer_hash> > projDatabaseAs;
		classType temp = prefix->getTailMax();
		pairSet::iterator assemblyStart = uniqueElements.begin();
		while(assemblyStart != uniqueElements.end() && (assemblyStart->first <= temp)){++assemblyStart;}
		assembleProyectionParametrized(assemblyStart, uniqueElements.end(), database, threshold, *((sequence_hash *)prefix), projDatabaseAs, options);
		unordered_map <hashConv, vector<seq_pointer_hash> >::iterator start, end;
		start = projDatabaseAs.begin(); end = projDatabaseAs.end();
		while(start!=end){
			sequence_hash *assembled = prefix;
			assembled = (assembled->assemble(deconvert(start->first)));
			__prefixSpan__Parameterized(uniqueElements, threshold, assembled, start->second, options);
			++start;
		}
	}return;
}

void prefixSpanParameterized(int threshold, vector <sequence_hash> &database, unordered_map<string, int> &options, parserTree &tree){
//CONVERT SEQUENCES TO RESPECTIVE POINTERS
//GENERATE CANDIDATE ELEMENTS SET
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
//*>
    unordered_map <hashConv, vector<seq_pointer_hash>> projDatabaseApp;
    sequence_hash ePrefix;
    appendProyectionParametrized(uniqueElements, newDatabase, threshold, ePrefix, projDatabaseApp, options);   
    unordered_map <hashConv, vector<seq_pointer_hash> >::iterator starto, endo; starto = projDatabaseApp.begin(); endo = projDatabaseApp.end();
//START RECURSIVE EVALUATIONS OF PREFIX SPAN
    while(starto!=endo){
//HACK TO WORK AROUND C++ PROBLEMS WITH POLYMORPHISM
        if(options["includeFlag"]){
			sequence_hash_parser *appended = new sequence_hash_parser(tree);
			appended = (sequence_hash_parser *) appended->append(deconvert(starto->first));
			__prefixSpan__Parameterized(uniqueElements, threshold, appended, starto->second, options);
			++starto;
		}else {
			sequence_hash *appended = new sequence_hash;
			*appended = *(appended->append(deconvert(starto->first)));
			__prefixSpan__Parameterized(uniqueElements, threshold, appended, starto->second, options);
			++starto;
		}
    }
    return;
}
