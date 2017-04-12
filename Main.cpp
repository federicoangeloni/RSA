/*
 * Main.cpp
 *
 *  Created on: 05 ott 2015
 *      Author: Federico
 */

#include "Main.h"

int main() {
	int uscita = 1;
	while (uscita == 1 ){
		int scelta = 0;
		int sceltatest = 0;
		int iteration = 50; //Ogni test di primalità farà 50 "tentativi"...regola l'accuratezza!!!
		long long p;
		long long q;
		uint64 StartTimePrime;
		uint64 EndTimePrime = 0;
		uint64 ElapsedTimePrime;
		RandomPrimeGenerator rpg;
		while (scelta!=1 && scelta!=2){
			cout << "Scegliere la modalita di generazione dei numeri primi p e q: " << endl;
			cout << " - Digita 1 per la generazione automatica" << endl;
			cout << " - Digita 2 per l'inserimento manuale" << endl;
			cin >> scelta;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		switch (scelta){
			case 1: //Sezione relativa alla ricerca automatica di p e q
				cout << "\nSto calcolando due numeri primi..." << endl;
				StartTimePrime = GetTimeMs64();
				rpg.init_fast(10000000); //Numeri primi fino a 10 milioni
				cout << "Numeri primi trovati!" << endl;
				p=  rpg.get();
				q = rpg.get();
				while (p == q){
					p=  rpg.get();
					q = rpg.get();
				}
				EndTimePrime = GetTimeMs64();
				ElapsedTimePrime = EndTimePrime - StartTimePrime;
				break;
			case 2:  //Sezione relativa all'inserimento manuale di p e q
				while (sceltatest!=1 && sceltatest!=2 && sceltatest!=3){
						cout << "Scegliere il test di primalità per la verifica del numero inserito: " << endl;
						cout << " - Digita 1 per il test di primalità di Fermat" << endl;
						cout << " - Digita 2 per il test di primalità di Miller-Rabin" << endl;
						cout << " - Digita 3 per il test di primalità di Solovay-Strassen" << endl;
						cin >> sceltatest;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				switch (sceltatest){
					case 1:
						//iteration = rand() % (p-1) + 20; numero di iterazioni che fa Fermat (accuratezza del risultato variabile tra 20 e p-1)
						cout << "Inserire un numero primo (p) grande: ";
						cin >> p;
						while (!Fermat(p,iteration)){
							cout << "Il numero p inserito NON E' PRIMO" << endl;
							cout << "Reinserisci un numero primo (p) grande: ";
							cin >> p;
						}
						cout << "Inserire un numero primo (q) grande: ";
						cin >> q;
						while (q == p){
							cout << "I numeri p e q devono essere distinti!" << endl;
							cout << "Reinserisci un numero primo (q) grande: ";
							cin >> q;
						}
						while (!Fermat(q,iteration)){
								cout << "Il numero q inserito NON E' PRIMO" << endl;
								cout << "Reinserisci un numero primo (q) grande: ";
								cin >> q;
						}
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					case 2:
						//iteration = rand() % (p-1) + 20; numero di iterazioni che fa Miller-Rabin (accuratezza del risultato variabile tra 20 e p-1)
						cout << "Inserire un numero primo (p) grande: ";
						cin >> p;
						while (!MillerRabin(p,iteration)){
							cout << "Il numero p inserito NON E' PRIMO" << endl;
							cout << "Reinserisci un numero primo (p) grande: ";
							cin >> p;
						}
						cout << "Inserire un numero primo (q) grande: ";
						cin >> q;
						while (q == p){
							cout << "I numeri p e q devono essere distinti!" << endl;
							cout << "Reinserisci un numero primo (q) grande: ";
							cin >> q;
						}
						while (!MillerRabin(q,iteration)){
							cout << "Il numero q inserito NON E' PRIMO" << endl;
							cout << "Reinserisci un numero primo (q) grande: ";
							cin >> q;
						}
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					case 3:
						//iteration = rand() % (p-1) + 20; numero di iterazioni che fa Solovoy-Strassen (accuratezza del risultato variabile tra 20 e p-1)
						cout << "Inserire un numero primo (p) grande: ";
						cin >> p;
						while (!SolovayStrassen(p,iteration)){
							cout << "Il numero p inserito NON E' PRIMO" << endl;
							cout << "Reinserisci un numero primo (p) grande: ";
							cin >> p;
						}
						cout << "Inserire un numero primo (q) grande: ";
						cin >> q;
						while (q == p){
							cout << "I numeri p e q devono essere distinti!" << endl;
							cout << "Reinserisci un numero primo (q) grande: ";
							cin >> q;
						}
						while (!SolovayStrassen(q,iteration)){
							cout << "Il numero q inserito NON E' PRIMO" << endl;
							cout << "Reinserisci un numero primo (q) grande: ";
							cin >> q;
						}
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
				}
		}

		//Generazione dei parametri dell'algoritmo RSA
		long long n;
		long long e;
		long long d;
		parameterGeneration(p,q,n,e,d);

		// Inserimento del messaggio da cifrare per mezzo di RSA
		cout << "\nINSERIRE IL MESSAGGIO DA CODIFICARE: ";
		string messaggio;
		getline(cin, messaggio);
		int num_car = messaggio.size()-1;
		cout << "\nNumero di caratteri: " << num_car <<  endl;
		cout << "\nMESSAGGIO IN CHIARO: " << messaggio << endl;
		uint64 StartTime1 = GetTimeMs64();
		int dimensione = messaggio.size();

		// Codifichiamo "messaggio" ottenendo "crypt"
		// Si usa solo la chiave pubblica "(n,e)"
		cout << "\nINIZIO CODIFICA:" << endl;
		long long crypt[dimensione];
		codifica_messaggio(n, e, messaggio, crypt);
		uint64 EndTime1 = GetTimeMs64();
		uint64 ElapsedTime1 = EndTime1 - StartTime1;
		std::cout << "\nMESSAGGIO CODIFICATO: ";
		for (int i=0; i < dimensione-1; i++){
			cout << crypt[i];
		}
		cout << std::endl;

		// Decodifichiamo "crypt" ottenendo "decrypt" ed il corrispondente testo originario "messaggioottenuto"
		// Qui si usa la chiave privata "(n,d)"
		cout << "\nINIZIO DECODIFICA" << endl;
		uint64 StartTime2 = GetTimeMs64();
		long long decrypt[dimensione];
		string messaggioottenuto;
		decodifica_messaggio(n, d, crypt, decrypt, messaggioottenuto, dimensione);
		cout << "\nMESSAGGIO DECODIFICATO: ";
		for (int i=0; i < dimensione-1; i++){
			cout << messaggioottenuto[i];
		}
		cout << endl;
		uint64 EndTime2 = GetTimeMs64();
		uint64 ElapsedTime2 = EndTime2 - StartTime2;

		//Stampa dei risultati dell'analisi dei tempi di elaborazione
		cout << "\nANALISI DEI TEMPI DI ELABORAZIONE" << endl;
		cout << "-----------------------------------" << endl;
		if (scelta == 1){
			cout << "Tempo impiegato per la ricerca dei numeri primi: circa " << ElapsedTimePrime << " millisecondi" << endl;
		}
		cout << "Tempo di Esecuzione Codifica: circa " << ElapsedTime1 <<  " millisecondi" << endl;
		cout << "Tempo di Esecuzione Decodifica: circa " << ElapsedTime2 << " millisecondi" <<  endl;
		uint64 ElapsedTimeTot = EndTime2 - StartTime1;
		cout << "Tempo di Esecuzione Totale (Codifica+Decodifica): circa " << ElapsedTimeTot << " millisecondi" << endl;

		//Calcolo dell'ordine di grandezza delle chiavi generate
		int ord = 1;
		long long res = n;
		while(res > 10){
			res = res/10;
			ord++;
		}
		cout << "Le chiavi erano formate da numeri con ordine max di 10^" << ord << endl;
		cout << "\nInserire 1 per codificare un'altra stringa tramite RSA oppure un carattere qualsiasi per uscire: ";
		cin >> uscita;
		cout << endl;
	}
}
