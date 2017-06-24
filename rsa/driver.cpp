/********************
*File: driver.cpp
*Project: Project 2
*Author: Jacob Sprecher
*Date: 4/16/2017
*Email: sprech1@umbc.edu
*
*This file executes all rsa functions to generate keys and encrypt a message.
*This program takes approximately 1 minute to complete for size B = 2048
*
******************************* BUILD INSTRUCTIONS *******************************
*To compile this program, use the command g++ -I path/to/boost -std=c++11 -o driver driver.cpp rsa.cpp
*Replace path/to/boost with the file path to your version of boost.
*To run the program, use the command ./driver B
*Replace B with the maximum number of bits for n.
*******************/

#include "rsa.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./driver B\n";
        return 0;
    }
    cout << "Generating, please wait...\n";
    string message = "I deserve an A";

    int MAX_BITS = atoi(argv[1]);

    mp::cpp_int p, q, n, phi, d, useless, x;
    mp::cpp_int e = mp::pow(mp::cpp_int(2),16) + 1;

    cout << endl << "E = " << endl << e << endl;

    //Select random primes p and q
    boost::random::mt19937 rng(time(0));
    p = generatePrimes(rng, MAX_BITS);
    boost::random::mt19937 rng2(time(0));
    q = generatePrimes(rng2, MAX_BITS);

    //compute n
    n = p * q;
    cout << endl << "N = " << endl << n << endl;

    //compute phi(n)
    phi = (p-1) * (q-1);

    //compute d using extended euclid
    //NOTE: in my implementation of this function, the value we want is actually stored in the y parameter. This has no adverse affect on the end result.
    extEuclid(phi, e, &useless, &d);
    d = d % phi;
    if (d < 0)
    {
        d += phi;
        d = d % phi;
    }
    cout << endl << "D = " << endl << d << endl;

    cout << endl << "Message = " << endl << message << endl;
    //encrypt message
    x = 0;
    for (char& c : message)
    {
        x = x << 8;
        x = x ^ c;
    }
    cout << endl << "Encrypting..." << endl;
    mp::cpp_int crypt = mp::powm(x,e,n);
    cout << endl << "Encrypted Message = " << endl << crypt << endl;


    return 0;
}
