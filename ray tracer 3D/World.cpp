/**************************************************************
 * File:    World.cpp
 * Author : Jacob Sprecher
 * Date   : 10/5/2016
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
  startRecurse = false;
  recurseCounter = 0;
}

SlVector3 World::shade(HitRecord hit)
{
  //cout << "what\n";
  //cout << hit.vert[0] << endl;
  SlVector3 localcolor(0,0,0);
  for (unsigned int i = 0; i < l.size(); i++)
    {
      //cout << "hello\n";
      bool block = false;

      //fire ray from point of intersection toward light
      SlVector3 dir = (l[i] - hit.interPoint) / mag(l[i] - hit.interPoint);//(hit.interPoint - l[i]) / mag(hit.interPoint - l[i]);
      Ray ray(dir,hit.interPoint);
      
      //find out if it intersects with any polygons
      for (unsigned int j = 0; j < polyList.size(); j++)
	{
	  //cout << "now i'm here\n";
	  if (polyList[j].intersect(ray, 1e-4, hit.T))
	    {
	      //cout << "blocked\n";
	      block = true;
	      break;
	    }
	}
      //cout << "got out\n";
      if (block)
	{
	  //cout << "blocked\n";
	  //SlVector3 color(0,0,0);
	  return localcolor;
	}

      //cout << "we in there" << endl;
      else
	{
	  //cout << "we in there\n";
	  //cout << hit.vert[0] << endl;
	  //SlVector3 H = cross(hit.vert[1] - hit.vert[0], hit.vert[2] - hit.vert[0]) / mag(cross(hit.vert[1] - hit.vert[0], hit.vert[2] - hit.vert[0]));
	  //cout << "test2\n";
	  SlVector3 L = (l[i] - hit.interPoint) / mag(l[i] - hit.interPoint);
	  SlVector3 H = (L + hit.view) / mag(L + hit.view);
	  double diffuse = max(0.0, dot(hit.normal, L));
	  double specular = pow(max(0.0, dot(hit.normal, H)), hit.shine);
	  //if (diffuse > 1.0)
	  //cout << "DIFFUSE " << diffuse << endl;
	  //if (specular > 1.0)
	  //cout << "SPECULAR " << specular << endl;
	  //cout << "TEST\n";
	  //localcolor[0] += (hit.kd * hit.fill[0] * diffuse + hit.ks * specular) * I;
	  //localcolor[1] += (hit.kd * hit.fill[1] * diffuse + hit.ks * specular) * I;
	  //localcolor[2] += (hit.kd * hit.fill[2] * diffuse + hit.ks * specular) * I;
	  localcolor += (hit.kd * diffuse * hit.fill + hit.ks * specular) * I;
	  //cout << "didja do it?\n";
	}
      //cout << "end\n";
    }
  //cout << localcolor << endl;
  return localcolor;
}

HitRecord World::trace(Ray ray)
{
  HitRecord record;
  record.view = ray.d;

  if (startRecurse == false)
    recurseCounter = 0;
  else
    recurseCounter++;
  //This variable ensures we don't try to shade the background
  bool bg = true;
  record.fill = b;
  //by default, the fill is the background color
  //SlVector3 hitRecordFill = b;

  //loop over every polygon, testing for intersection
  for (unsigned int i = 0; i < polyList.size(); i++)
    {
      if (polyList[i].intersect(ray, vhither, record.T))
	{
	  //if the T from that polygon is lower than the current, update hitrecord.
	  if (polyList[i].T < record.T)
	    {
	      record.T = polyList[i].T;
	      record.fill.set(polyList[i].fill[0], polyList[i].fill[1], polyList[i].fill[2]);
	      record.interPoint = polyList[i].point;
	      record.kd = polyList[i].fill[3];
	      record.ks = polyList[i].fill[4];
	      record.shine = polyList[i].fill[5];
	      record.vert.push_back(polyList[i].v[0]);
	      record.vert.push_back(polyList[i].v[1]);
	      record.vert.push_back(polyList[i].v[2]);
	      record.normal = polyList[i].n;
	      bg = false;
	    }
	}
    }
  //cout << record.fill << " " << record.kd << " " << record.normal << endl;
  if (!bg)
    {
      record.fill = shade(record);
      //cout << record.normal << endl;
      //}

      //If you want to see the image without the reflection errors, comment out this section.
      //*************************************************************************
      //reflection
      if (record.ks > 0)
	{
	  //start recursion
	  startRecurse = true;
	  if (recurseCounter < 5)
	    {
	      //for (unsigned int i = 0; i < l.size(); i++)
	      //{
		  //compute light direction
		  //SlVector3 L = (l[i] - record.interPoint) / mag(l[i] - record.interPoint);
	      SlVector3 L = ray.d;
		  //compute reflection direction
		  SlVector3 ref = (-1 * L) + (2 * dot(L, record.normal) * record.normal);
		  Ray reflect(ref,record.interPoint);
		  record.fill = record.ks * trace(reflect).fill;
		  //}
	    }
	  else
	    startRecurse = false;
	}
      /******************************************************************************/
    }
  return record;
}

void World::traceImg()
{
  //First compute all the values needed.
  I = 1 / (l.size() - 1);
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
	  SlVector3 rayTemp(rayx, rayy, rayz);
	  Ray ray(rayTemp, vfrom);

	  //save the pixel colors into a vector
	  image.push_back(trace(ray).fill);
	}
    }
}

void World::writeImg(string name)
{
  //convert image vector into chars, fill the pixel array with them.
  unsigned char *pixels = new unsigned char [vres[0] * vres[1] * 3];
  for (unsigned int i = 0; i < image.size(); i++)
    {
      //cout << image[i];
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
