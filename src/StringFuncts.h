/*
 * StringFuncts.h
 *
 *  Created on: May 30, 2016
 *      Author: Diogo
 */

#ifndef SRC_STRINGFUNCTS_H_
#define SRC_STRINGFUNCTS_H_

#include <string>
#include <vector>

using namespace std;

void preExactCmp(string pattern, vector<int> & prefix);

int exactCmp(string text, string pattern);

int editDistance(string pattern, string text);


#endif /* SRC_STRINGFUNCTS_H_ */
