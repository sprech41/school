/**************************************************************
 * File:    Ray.h
 * Author : Jacob Sprecher
 * Date   : 10/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Contains the Ray and HitRecord classes
 *
 *************************************************************/


#ifndef RAY_H
#define RAY_H
#include <vector>
#include <string>
#include <stdio.h>
#include "slVector.H"
using namespace std;

class Ray
{
 public:
  inline Ray(SlVector3 direction, SlVector3 origin) {
    d = direction;
    e = origin;
  }
  SlVector3 d;
  SlVector3 e;
};

class HitRecord
{
 public:
  inline HitRecord() {
    T = 1000;
    z = 10000;
  }
  
  inline HitRecord(SlVector3 color)
  {
    z = 10000;
    fill = color;
  }
  double T;
  SlVector3 fill;
  SlVector3 normal;
  SlVector3 interPoint;
  double kd;
  double ks;
  double shine;
  vector<SlVector3> vert;
  SlVector3 view;
  double z;
};
#endif
