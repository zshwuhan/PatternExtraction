/* 
 * File:   helperFunctions.cpp
 * Author: Agustin
 * 
 * Created on 24 February 2015, 13:55
 */

#include "helperFunctions_hash.hpp"
#include <string>
#include "sequence_hash.hpp"
#include <vector>
#include <iostream>
#include <sstream>

void vectorPrint(vector <sequence_hash> v){
    vector <sequence_hash>::iterator it1,it2;
    it1=v.begin(), it2=v.end();
    while(it1!=it2){
        cerr<<*it1;
        ++it1;
    }
}

sequence_hash sequencer(string input){
    sequence_hash output;
    bool assembleMode = false;
    int low, high;
    stringstream inputStreamed(input);
    while(inputStreamed){
        if(inputStreamed.peek()=='('){
            inputStreamed.ignore();
            inputStreamed>>high;
            inputStreamed.ignore();
            inputStreamed>>low;
                        output = output.append(high, low);
                        assembleMode=true;
        }else if(inputStreamed.peek()==')'){
            assembleMode=false;
            inputStreamed.ignore();
        }else if(inputStreamed.peek()==','){
            inputStreamed.ignore();
        }else if(inputStreamed.peek()!=-1){
            if(assembleMode){
                inputStreamed>>high;
                inputStreamed.ignore();
                inputStreamed>>low;
                                output = output.assemble(high,low);
                            }else{
                inputStreamed>>high;
                inputStreamed.ignore();
                inputStreamed>>low;
                                output = output.append(high, low);
                            }
        }else{
            inputStreamed.ignore();
        }
    }
    return output;
}
#include <fstream>

vector <sequence_hash> massSequencer(ifstream &input){
    vector <sequence_hash> output;
    while(input){
        string temp;
        getline(input, temp);
        sequence_hash helper;
        helper = sequencer(temp);
        if (!helper.empty())output.push_back(helper);
    }
    return output;
}
