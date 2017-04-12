/*
 * RSA.h
 *
 *  Created on: 21 lug 2015
 *      Author: Federico
 */

#ifndef RSA_H_
#define RSA_H_


#include "CalcoliAritmetici.h"

void parameterGeneration(long long p1, long long q1, long long &n1, long long &e1, long long &d1);
void codifica_messaggio(long long n, long long e, std::string messaggioinchiaro, long long messaggiocriptato[]);
void decodifica_messaggio (long long n, long long d, long long messaggiocriptato[], long long messaggiodecriptato[], std::string testodecifrato, long long dimension);


#endif /* RSA_H_ */
