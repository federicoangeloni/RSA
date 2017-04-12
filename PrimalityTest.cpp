/*
 * PrimalityTest.cpp
 *
 *  Created on: 01 ott 2015
 *      Author: Federico
 */
#include "PrimalityTest.h"

//Calcolo di [(base^exponent) % mod] (
//ELEVAMENTO A POTENZA MODULARE
long long potenzaMod(long long base, long long exponent, long long mod)
{
    long long x = 1;
    long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

// Calcolo di [(a*b) % mod] tenendo conto del fatto che (a*b) potrebbe essere soggetto ad overflow
// PRODOTTO MODULARE
long long prodottoMod(long long a, long long b, long long mod)
{
    long long x = 0;
    long long y = a % mod;
    while (b > 0)
    {
    	if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

/*
 * Calcola il simbolo di Jacobi (a/n) dove n>0 ed n dispari
 */
int simboloJacobi(long long a,long long n)
{
    if (!a)
        return 0;
    int ans = 1;
    if (a < 0)
    {
        a = -a;
        if (n % 4 == 3)
            ans=-ans;
    }
    if (a == 1)
        return ans;
    while (a)
    {
        if (a < 0)
        {
            a = -a;
            if (n % 4 == 3)
                ans = -ans;
        }
        while (a % 2 == 0)
        {
            a = a / 2;
            if (n % 8 == 3 || n % 8 == 5)
                ans = -ans;
        }
        swap(a, n);
        if (a % 4 == 3 && n % 4 == 3)
            ans = -ans;
        a = a % n;
        if (a > n / 2)
            a = a - n;
    }
    if (n == 1)
        return ans;
    return 0;
}

/*
 * Test di primalità di Fermat
 */
bool Fermat(long long n, int iteration)
{
	if ( n <= 1 )
    {
        return false;
    }
    for (int i = 0; i < iteration; i++)
    {
        long long a = rand() % (n - 1) + 1; //sceglie un numero random da 1 a n-1
        if (potenzaMod(a, n - 1, n) != 1)
        {
            return false;
        }
    }
    return true;
}


/*
 * Test di primalità di Miller-Rabin, iteration indica l'accuratezza
 */
bool MillerRabin(long long n,int iteration)
{
	if (n < 2)
    	return false;
    if (n != 2 && n % 2==0)
    	return false;
    long long m = n - 1;
    while (m % 2 == 0)
    {
        m /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        long long a = rand() % (n - 1) + 1;  //sceglie un numero random da 1 a n-1
        long long temp = m;
        long long b0 = potenzaMod(a, temp, n);
        while (temp != n - 1 && b0 != 1 && b0 != n - 1)
        {
        	b0 = prodottoMod(b0, b0, n);
            temp *= 2;
        }
        if (b0 != n - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

/*
 * Solovay-Strassen Primality Test
 * Iiteration indica l'accuratezza
 */
bool SolovayStrassen(long long n, int iteration)
{
	if (n < 2)
        return false;
    if (n != 2 && n % 2 == 0)
        return false;
    for (int i = 0; i < iteration; i++)
    {
        long long a = rand() % (n - 1) + 1;
        long long jacobiano = (n + simboloJacobi(a, n)) % n;
        long long mod = potenzaMod(a, (n - 1) / 2, n);
        if (!jacobiano || mod != jacobiano)
        {
            return false;
        }
    }
    return true;
}
