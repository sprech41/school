/**************************************************************
 * File:    Polygon.h
 * Author : Jacob Sprecher
 * Date   : 9/5/2016
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
  bool intersect(SlVector3 e, SlVector3 d, int t0, int t1);

  //the polygon's fill color
  vector<double> fill;

  //the last calculated t value
  double T;

  //contains this polygon's vertices
  vector<SlVector3> v;
};
#endif
