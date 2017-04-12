/*
 * RSA.cpp
 *
 *  Created on: 16 lug 2015
 *      Author: Federico Angeloni
 */

#include "RSA.h"

/*
  Generazione dei parametri e delle chiavi pubblica e privata
  // "p" e "q" sono i fattori primi di "n"
  // Bisogna fare in modo che gli interi risultanti dalla codifica non siano multipli di p o q
  // Si scelgono grandi, altrimenti la decodifica potrebbe fallire
*/
void parameterGeneration(long long p1, long long q1, long long &n1, long long &e1, long long &d1){
  n1  = p1 * q1; //Calcoliamo n=p*q
  long long fi = n1 - p1 - q1 + 1; //Calcoliamo fi=(p-1)*(q-1)
  cout << "\nValori dei parametri" << endl;
  cout << "--------------------" << endl;
  cout << "p = " << p1 << endl;
  cout << "q = " << q1 << endl;
  cout << "n = p*q = " << n1 << endl;
  cout<< "fi = (p-1)(q-1) = " << fi <<endl;
  long long i;
  long long lambda, mi;
  long long j;
  while (j != 1){      //Si ricerca un intero e minore di fi che sia primo con fi
	i = rand() % fi + 1;
    j = mcd_est(i, fi, lambda, mi);
  }
  e1 = i;
  d1 = lambda;  //Calcoliamo un intero d tale che d*e sia congruente con 1 (modulo fi)
  if (d1 < 0)
    d1 += fi;
  cout << "e = " << e1 << " ---> MCD(e,fi)=1" << endl;
  cout << "d = " << d1 << " ---> d*e congruente 1[mod fi]" << endl;
  cout << "PUBLIC KEY ---> (n,e) = (" << n1 << "," << e1 << ")" << endl;
  cout << "PRIVATE KEY --> (n,d) = (" << n1 << "," << d1 << ")" << endl;
}


/*
  Codifica del messaggio con RSA
*/
void codifica_messaggio(long long n, long long e, std::string messaggioinchiaro, long long messaggiocriptato[]){
	int dimensione = messaggioinchiaro.size();
	long long m;
	for(int i = 0; i < dimensione-1; i++) {
	    m = (int) messaggioinchiaro[i]; //Operazione di cast:a k assegno il codice ascii della lettera
	    long long C = potenze_mod_n(m, e, n);
	    messaggiocriptato[i] = C;
	    std::cout << messaggioinchiaro[i] << "  ------>  " << m << "  ------>  " << C << std::endl;
	  }
}


/*
  Decodifica del messaggio con RSA
*/
void decodifica_messaggio (long long n, long long d, long long messaggiocriptato[], long long messaggiodecriptato[], std::string testodecifrato, long long dimension){
	int dimensione = dimension;
	for(int i = 0; i < dimensione-1; i++) {
	    long long C = messaggiocriptato[i];
	    long long m = potenze_mod_n(C, d, n);
	    messaggiodecriptato[i] = m;
	    testodecifrato[i] = (char) messaggiodecriptato[i]; //Operazione di cast: a testodecifrato assegno il carattere corrispondente al valore contenuto in messaggiodecriptato
	    std::cout << messaggiocriptato[i] << "   ------>   " << messaggiodecriptato[i] << "   ------>   " << testodecifrato[i] << std::endl;
	  }
}

