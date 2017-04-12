/*
 * PrimalityTest.h
 *
 *  Created on: 01 ott 2015
 *      Author: Federico
 */

#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

long long potenzaMod(long long base, long long exponent, long long mod);
long long prodottoMod(long long a, long long b, long long mod);
int simboloJacobi(long long a,long long n);

bool Fermat(long long p, int iterations);
bool MillerRabin(long long p,int iteration);
bool SolovayStrassen(long long p, int iteration);

