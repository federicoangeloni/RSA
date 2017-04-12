/*
 * ElapsedTime.h
 *
 *  Created on: 17 lug 2015
 *      Author: Federico
 */

#ifndef ELAPSEDTIME_H_
#define ELAPSEDTIME_H_
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

typedef long long int64;
typedef unsigned long long uint64;

uint64 GetTimeMs64();

#endif /* ELAPSEDTIME_H_ */
