#include"CalcoliAritmetici.h"

/*
  Calcolo del massimo comun divisore con l'algoritmo di Euclide.
*/
long long mcd(long long a, long long b) {

  // I valori assoluti assicurano che i calcoli contengono solo numeri
  // non negativi
  long long unsigned n = llabs(b);
  long long unsigned m = llabs(a);
  long long unsigned r = n;
  while(r != 0) {
    r = m % n;
    m = n;
    n = r;
  }
  return(m);
}

/*
  Calcolo del massimo comun divisore con l'algoritmo di Euclide esteso
  ritorna due valori "lambda" e "mi" in modo che sia soddisfatta
  l'uguaglianza "mcd = lambda * a + mi * b".
*/
long long mcd_est(long long a, long long b, long long &lambda, long long &mi) {

  long long a1 = 1;
  long long a2 = 0;
  long long b1 = 0;
  long long b2 = 1;
  long long m = a;
  long long n = b;
  long long r = n;
  while(r != 0) {
    long long q = m / n;
    r = m % n;
    long long a3 = a1 - q * a2;
    long long b3 = b1 - q * b2;
    a1 = a2;
    a2 = a3;
    b1 = b2;
    b2 = b3;
    m = n;
    n = r;
  }
  lambda = a1;
  mi = b1;
  return(m);
}

/*
  Moltiplicazione "a * m mod n" usando il procedimento del raddoppiamento
  e dimezzamento dei due fattori.
*/
long long moltiplicazione_mod_n(long long a, long long m, long long n) {

  long long S = 0;
  long long M = m;
  long long A = a;
  long long r, q;
  do {
    r = M % 2;
    q = M / 2;
    if (r == 1) {
      S += A;
      S  = S % n;
    }
    A += A;
    A  = A % n;
    M  = q;
  } while(q > 0);
  return(S);
}

/*
  Calcolo di "a^m mod n" con il metodo dei quadrati ripetuti.
*/
long long potenze_mod_n(long long a, long long m, long long n) {

  long long P = 1;
  long long M = m;
  long long A = a;
  long long r;
  long long q;
  do {
    r = M % 2;
    q = M / 2;
    if (r == 1)
      P = moltiplicazione_mod_n(P,A,n);
    A = moltiplicazione_mod_n(A,A,n);
    M  = q;
  } while(q > 0);
  return(P);
}

/*
  Calcolo del quoziente "q" e del resto "r" della divisione di "N" per
  "M" sfruttando la divisione per "m = M - d", dove "d" è piccolo in
  valore assoluto (supponendo che, per qualche motivo, dividere per
  "m" sia efficiente).
*/
void divisione(long long N, long long M, long long d, long long& q,
	  long long& r) {

  long long m = M - d;
  long long max = d > 0 ? M : m;
  q = N / M;
  r = d * q + (N % M);
  long long qq;

  // Ripeti il ciclo finché il resto non è nell'intervallo corretto
  do {
    qq = r / M;
    if (r < 0)
      --qq;
    long long rr = r - M * qq;
    q += qq;
    r = d * qq + rr;
  } while ((r < 0) || (r >= max));

  // Correggi il risultato, se necessario
  while (r >= m) {
    r -= m;
    ++q;
  }
}

/*
  Radice quadrata intera.
  Dato il numero intero non negativo "n", restituisce il massimo
  intero non negativo "m" tale che "m^2 <= n", cioè la radice
  quadrata intera approssimata per difetto.
*/
long long radice_quadrata(long long n) {
	  if (n < 0)
	    return(-1);
	  long long m = int(sqrt((double) n));
	  return(m);
}


bool isPrime(long long numero)
{
    int iterazioni = 50;
    bool testresult;
    testresult = Fermat(numero, iterazioni);
	/*
    for (long long a = 2; a < numero; a++) {
        if (numero % a == 0) {
            return false;
        }
    }*/
    return testresult;
}

