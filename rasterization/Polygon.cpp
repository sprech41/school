/**************************************************************
 * File:    World.cpp
 * Author : Jacob Sprecher
 * Date   : 10/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Implements all polygon operations.
 *
 *************************************************************/

#include "Polygon.h"
using namespace std;

Polygon::Polygon()
{
  T = 0;
}
/**
bool Polygon::intersect(Ray ray, double t0, double t1)
{
  double A, alpha, beta, t;
  double xa = v[0][0], xb = v[1][0], xc = v[2][0], ya = v[0][1], yb = v[1][1], yc = v[2][1], za = v[0][2], zb = v[1][2], zc = v[2][2];
  double xd = ray.d[0], yd = ray.d[1], zd = ray.d[2], xe = ray.e[0], ye = ray.e[1], ze = ray.e[2];
  //v[0][0] represents the x coordinate of point a, v[0][1] represents the y coordinate of point a, etc

  A = ((xa - xb) * (((ya - yc) * zd) - (yd * (za - zc)))) -
    ((xa - xc) * (((ya - yb) * zd) - (yd * (za - zb)))) +
    (xd * (((ya - yb) * (za - zc)) - ((ya - yc) * (za - zb))));

  alpha = (((xa - xe) * (((ya - yc) * zd) - (yd * (za - zc)))) -
    ((xa - xc) * (((ya - ye) * zd) - (yd * (za - ze)))) +
    (xd * (((ya - ye) * (za - zc)) - ((ya - yc) * (za - ze))))) / A;

  beta = (((xa - xb) * (((ya - ye) * zd) - (yd * (za - ze)))) -
    ((xa - xe) * (((ya - yb) * zd) - (yd * (za - zb)))) +
    (xd * (((ya - yb) * (za - ze)) - ((ya - ye) * (za - zb))))) / A;

  t = (((xa - xb) * (((ya - yc) * (za - ze)) - ((ya - ye) * (za - zc)))) -
    ((xa - xc) * (((ya - yb) * (za - ze)) - ((ya - ye) * (za - zb)))) +
    ((xa - xe) * (((ya - yb) * (za - zc)) - ((ya - yc) * (za - zb))))) / A;

  //Must pass these tests for intersection
  if ((t < t0) || (t > t1))
    return false;
  if ((alpha < 0) || (alpha > 1))
    return false;
  if ((beta < 0) || (beta > 1 - alpha))
    return false;

  //Update T
  T = t;

  //update point of intersection
  point = ray.e + t * ray.d;
  return true;
}
*/
