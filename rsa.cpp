/********************
*File: rsa.cpp
*Project: Project 2
*Author: Jacob Sprecher
*Date: 4/16/2017
*Email: sprech1@umbc.edu
*
*This file contains implementation of all rsa functions. It contains all functions necessary
*for RSA encryption.
*******************/

#include "rsa.h"

mp::cpp_int generatePrimes(boost::random::mt19937 rng, int b)
{
    int s = 50;

    //generate random 1024 bit number
    mp::cpp_int temp = mp::pow(mp::cpp_int(2),b/2);
    boost::random::uniform_int_distribution<mp::cpp_int> gen(1, temp);
    mp::cpp_int x = gen(rng);

    //make sure it is odd
    if (x % 2 == 0)
        x += 1;

    while (millerRabin(x, s) == false)
        x += 2;
    return x;
}
bool witness(mp::cpp_int r, mp::cpp_int x)
{
        //select random a
        boost::random::mt19937 rng(time(0));
        boost::random::uniform_int_distribution<mp::cpp_int> gen(1, x);
        mp::cpp_int a = gen(rng);

        //modular exponentiation
        mp::cpp_int b = powm(a, r, x);

        if (b == 1 || b == x-1)
            return true;

        while (r != x-1)
        {
            b = (b * b) % x;
            r *= 2;

            if (b == 1)
                return false;
            if (b == x-1)
                return true;
        }

        return false;
}
bool millerRabin(mp::cpp_int x, int s)
{
    //base cases
    if (x <= 1)
        return false;
    if (x == 2)
        return true;

    //find r for x-1 = 2^t * r
    mp::cpp_int r = x - 1;
    while (r%2 == 0)
        r /= 2;

    //witness loop
    for (int i = 0; i < s; i++)
    {
        if (witness(r, x) == false)
            return false;
    }
    return true;
}

mp::cpp_int extEuclid(mp::cpp_int a, mp::cpp_int b, mp::cpp_int *x, mp::cpp_int *y)
{
    //base case
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    //these are x' and y' from our class algorithm
    mp::cpp_int x1, y1;
    mp::cpp_int gcd = extEuclid(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a/b) * y1;
    return gcd;
}
