/**************************************************************
 * File:    Polygon.h
 * Author : Jacob Sprecher
 * Date   : 10/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Contains the prototypes for all data relating to the polygons (triangles)
 *
 *************************************************************/

#ifndef POLY_H
#define POLY_H
#include <vector>
#include <string>
#include "slVector.H"
#include "Ray.h"
using namespace std;

class Polygon
{
 public:
  //Defaut constructor
  Polygon();

  //-------------------------------------------------------
  // Name: intersect
  // PreCondition: N/A
  // PostCondition: Returns true if the given ray intersects this polygon. False otherwise.
  //---------------------------------------------------------
  bool intersect(Ray ray, double t0, double t1);

  //the polygon's fill color
  vector<double> fill;

  //the last calculated t value
  double T;

  //contains this polygon's vertices
  vector<SlVector3> v;

  //This polygon's normal
  SlVector3 n;

  //The latest point of intersection
  SlVector3 point;
};
#endif
