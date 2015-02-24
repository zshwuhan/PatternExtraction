/* 
 * File:   helperFunctions.cpp
 * Author: Agustin
 * 
 * Created on 24 February 2015, 13:55
 */

#include "helperFunctions.hpp"
#include <string>
#include "sequence_hash.hpp"
#include <vector>
#include <iostream>
#include <sstream>

sequence_hash sequencer(string input){
    sequence_hash output;
    bool assembleMode = false;
    int low, high, net;
    stringstream inputStreamed(input);
    while(inputStreamed){
        if(inputStreamed.peek()=='('){
            inputStreamed>>low;
            inputStreamed>>high;
            net = low | (high<<16);
            output.append(net);
            assembleMode=true;
        }else if(inputStreamed.peek()==')'){
            assembleMode=false;
            inputStreamed.ignore();
        }else{
            if(assembleMode){
                inputStreamed>>low;
                inputStreamed>>high;
                net = low | (high<<16);
                output.assemble(net);
            }else{
                inputStreamed>>low;
                inputStreamed>>high;
                net = low | (high<<16);
                output.append(net);
            }
        }
        
    }
    return output;
}

vector <sequence_hash> massSequencer(istream input){
    vector <sequence_hash> output;
    while(input){
        string temp;
        getline(input, temp);
        sequence_hash helper;
        helper = sequencer(temp);
        output.push_back(helper);
    }
    return output;
}
