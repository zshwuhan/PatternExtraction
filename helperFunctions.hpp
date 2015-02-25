/* 
 * File:   helperFunctions.hpp
 * Author: Agustin
 *
 * Created on 24 February 2015, 13:55
 */

#ifndef HELPERFUNCTIONS_HPP
#define	HELPERFUNCTIONS_HPP
#include <string>
#include "sequence_hash.hpp"
#include <vector>
#include <iostream>

sequence_hash sequencer(string);
vector <sequence_hash> massSequencer(ifstream &);


#endif	/* HELPERFUNCTIONS_HPP */

