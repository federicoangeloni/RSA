/*
 * PrimeGeneration.h
 *
 *  Created on: 22 lug 2015
 *      Author: Federico
 */

#ifndef PRIMEGENERATION_H_
#define PRIMEGENERATION_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include "PrimalityTest.h"
using namespace std;

class RandomPrimeGenerator
{
      public:
      RandomPrimeGenerator(){mode=NONE; srand(time(0));}
      ~RandomPrimeGenerator(){}

      void init_fast(unsigned int _max_number);
      void init_cheap(unsigned int _max_prime_count);

      unsigned int get();

      private:
      unsigned int max_number;
      unsigned int max_prime_count;
      enum {NONE=0,FAST=1,CHEAP=2} mode;
      vector<unsigned int> prime_list;
      void find_primes();
};

/* ESEMPIO DI UTILIZZO
int main()
{
    RandomPrimeGenerator rpg;
    int i;

    cout << "initializing fast way...\n";
    rpg.init_fast(1000000); //numeri primi a partire da 1000000

    cout << "Generazione numeri primi veloce!\n";
    for (i=0; i<10; i++)
    {
        cout << rpg.get() << endl;
    }

    cout << "initializing cheap way...\n";
    rpg.init_cheap(75000); //i primi 75000 numeri primi

    cout << "Generazione numer primi lenta!\n";
    for (i=0; i<10; i++)
    {
        cout << rpg.get() << endl;
    }

    system("pause");
    return 0;
}*/

#endif /* PRIMEGENERATION_H_ */
