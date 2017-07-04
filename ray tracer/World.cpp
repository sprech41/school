/**************************************************************
 * File:    World.cpp
 * Author : Jacob Sprecher
 * Date   : 9/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Contains the implementation of World.h
 *
 *************************************************************/

#include "World.h"
#include <algorithm>
#include <cmath>
using namespace std;

World::World()
{
}

SlVector3 World::trace(SlVector3 ray)
{
  //A very large default, representing infinity.
  double hitRecordT = 10000;

  //by default, the fill is the background color
  SlVector3 hitRecordFill = b;

  //loop over every polygon, testing for intersection
  for (unsigned int i = 0; i < polyList.size(); i++)
    {
      if (polyList[i].intersect(vfrom, ray, vhither, hitRecordT))
	{
	  //if the T from that polygon is lower than the current, update it and the fill color.
	  if (polyList[i].T < hitRecordT)
	    {
	      hitRecordT = polyList[i].T;
	      hitRecordFill.set(polyList[i].fill[0], polyList[i].fill[1], polyList[i].fill[2]);
	    }
	}
    }
  return hitRecordFill;
}

void World::traceImg()
{
  //First compute all the values needed.
  double d = .5 * mag(vfrom - vat);
  double h = tan((vangle / 2.0) * (3.1415926535897 / 180)) * d;
  double x, y, z;
  SlVector3 u, v, w;

  //convert to world space
  w = (vfrom - vat) / mag(vfrom - vat);
  u = cross(vup, w) / mag(cross(vup,w));
  v = cross(w, u);

  //Loop through all pixels, casting a ray for each. Because of how the ppm file is written, the j loop is reversed.
  for (int j = vres[1]; j > 0; j--)
    {
      for (int i = 0; i < vres[0]; i++)
	{
	  x = ((i + .5) / vres[0]) * (2 * h) - h;
	  y = ((j + .5) / vres[1]) * (2 * h) - h;
	  z = -1 * d;
	  
	  double rayx = (x * u[0]) + (y * v[0]) + (z * w[0]);
	  double rayy = (x * u[1]) + (y * v[1]) + (z * w[1]);
	  double rayz = (x * u[2]) + (y * v[2]) + (z * w[2]);
	  SlVector3 ray(rayx, rayy, rayz);

	  //save the pixel colors into a vector
	  image.push_back(trace(ray));
	}
    }
}

void World::writeImg(string name)
{
  //convert image vector into chars, fill the pixel array with them.
  unsigned char *pixels = new unsigned char [vres[0] * vres[1] * 3];
  for (unsigned int i = 0; i < image.size(); i++)
    {
      for (int j = 0; j < 3; j++)
	{
	  unsigned char temp = (unsigned char)(min(1.0, max(0.0, image[i][j])) * 255.0);
	  pixels[3*i+j] = temp;
	}
    }

  //Output the file
  FILE *f = fopen(name.c_str(), "wb");
  fprintf(f, "P6\n%d %d\n%d\n", vres[0], vres[1], 255);
  fwrite(pixels, 1, vres[0]*vres[1]*3, f);
  fclose(f);
  delete pixels;
}
