/*
 * PrimeGeneration.cpp
 *
 *  Created on: 22 lug 2015
 *      Author: Federico
 */
#include "PrimeGeneration.h"

//Funzione che trova i numeri primi
void RandomPrimeGenerator::find_primes()
{
     prime_list.clear();
     prime_list.push_back(2);

     unsigned int i,j;
     unsigned int size=prime_list.size();
     bool is_prime;
     unsigned int cur_prime;
     for (i=3; max_number==0||i<=max_number; i+=2)
     {
         is_prime=true;
         for (j=0; j<size; j++)
         {
             cur_prime=prime_list[j];
             if (i<cur_prime*cur_prime) break;

             if (i%cur_prime==0) {
            	 is_prime=false; break;
             }
         }
         if (is_prime)
         {
            prime_list.push_back(i);
            size++;
            if (max_prime_count!=0&&size==max_prime_count) break;
         }
     }
}


//Inizializzazione della generazione in modalità "Veloce"
void RandomPrimeGenerator::init_fast(unsigned int _max_number)
{
     max_number=_max_number;
     max_prime_count=0;
     mode=FAST;
     find_primes();
}


//Inizializzazione della generazione in modalità "Lenta"
void RandomPrimeGenerator::init_cheap(unsigned int _max_prime_count)
{
     max_prime_count=_max_prime_count;
     max_number=0;
     mode=CHEAP;
     prime_list.clear();
}

unsigned int RandomPrimeGenerator::get()
{
     if (mode==NONE)
     {
        cerr << "Generatore di numeri primi random non inizializzato!...\n";
        return 1;
     }

     if (mode==FAST)
     {
        unsigned int size=prime_list.size();
        unsigned int index=int(0.5+(size-1)*(rand()/double(RAND_MAX)));
        return prime_list[index];
     }

     if (mode==CHEAP)
     {
        unsigned int index=int(0.5+(max_prime_count-1)*(rand()/double(RAND_MAX)));
        find_primes();
        return prime_list[index];
        prime_list.clear();
     }
}


