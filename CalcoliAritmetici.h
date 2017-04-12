/*
 * CalcoliAritmetici.h
 *
 *  Created on: 21 lug 2015
 *      Author: Federico
 */

#include "PrimalityTest.h"
#include <cmath>
using namespace std;

long long mcd(long long a, long long b);
long long mcd_est(long long a, long long b, long long &lambda, long long &mi);
long long moltiplicazione_mod_n(long long a, long long m, long long n);
long long potenze_mod_n(long long a, long long m, long long n);
void divisione(long long N, long long M, long long d, long long& q, long long& r);
long long radice_quadrata(long long n);
bool isPrime(long long numero);
