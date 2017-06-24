/********************
*File: rsa.h
*Project: Project 2
*Author: Jacob Sprecher
*Date: 4/16/2017
*Email: sprech1@umbc.edu
*
*This file contains prototypes for all rsa functions.
*******************/

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;
namespace mp = boost::multiprecision;

/*****************
* Name: generatePrimes
* Preconditions: N/A
* Postcondition: Generates a random prime
*******************/
mp::cpp_int generatePrimes(boost::random::mt19937 rng, int b);

/*****************
* Name: witness
* Preconditions: N/A
* Postcondition: Returns false if the number is composite. Returns true otherwise.
*                True does not necessarily mean the number is prime.
*******************/
bool witness(mp::cpp_int r, mp::cpp_int x);

/*****************
* Name: millerRabin
* Preconditions: N/A
* Postcondition: Returns false if x is composite, true if x is prime.
*******************/
bool millerRabin(mp::cpp_int x, int s);

/*****************
* Name: extEuclid
* Preconditions: N/A
* Postcondition: Returns the gcd of a and b. The corresponding x and y value are saved
*                to the out parameters x and y.
*******************/
mp::cpp_int extEuclid(mp::cpp_int a, mp::cpp_int b, mp::cpp_int *x, mp::cpp_int *y);
