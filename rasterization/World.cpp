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
  //startRecurse = false;
  //recurseCounter = 0;
}

SlVector3 World::shade(HitRecord hit)
{
  SlVector3 localcolor(0,0,0);
  for (unsigned int i = 0; i < l.size(); i++)
    {
      bool block = false;

      //fire ray from point of intersection toward light
      SlVector3 dir = (l[i] - hit.interPoint) / mag(l[i] - hit.interPoint);
      Ray ray(dir,hit.interPoint);
      
      //find out if it intersects with any polygons
      //for (unsigned int j = 0; j < polyList.size(); j++)
      //{
	  //if (polyList[j].intersect(ray, 1e-4, hit.T))
	  //{
	  //  block = true;
	  //  break;
	  //}
      //}

      if (block)
	{
	  return localcolor;
	}

      else
	{
	  SlVector3 L = (l[i] - hit.interPoint) / mag(l[i] - hit.interPoint);
	  SlVector3 H = (L + hit.view) / mag(L + hit.view);
	  double diffuse = max(0.0, dot(hit.normal, L));
	  double specular = pow(max(0.0, dot(hit.normal, H)), hit.shine);
	  localcolor += (hit.kd * diffuse * hit.fill + hit.ks * specular) * I;
	}
    }
  return localcolor;
}

double World::triLine(double x, double y, Polygon p, int i1, int i2)
{
  //cout << p.p[i1][1] << endl << p.p[i2][1] << endl << x << endl << p.p[i2][0] << endl << p.p[i1][0] << endl;
  double result = (p.p[i1][1] - p.p[i2][1]) * x + (p.p[i2][0] - p.p[i1][0]) * y + (p.p[i1][0] * p.p[i2][1]) - (p.p[i2][0] * p.p[i1][1]);
  return result;
}

void World::rasterize(Polygon& p)
{
  //cout << "OLD" << p.p[0] << endl;
  for (int i = 0; i < 3; i++)
    p.p[i] /= p.p[i][3];
  //cout << "NEW" << p.p[0] << endl;
  //compute bounding box
  unsigned int bbmin[2];
  unsigned int bbmax[2];
  bbmin[0] = floor(min(min(p.p[0][0], p.p[1][0]), p.p[2][0]));
  bbmin[1] = floor(min(min(p.p[0][1], p.p[1][1]), p.p[2][1]));
  bbmax[0] = ceil(max(max(p.p[0][0], p.p[1][0]), p.p[2][0]));
  bbmax[1] = ceil(max(max(p.p[0][1], p.p[1][1]), p.p[2][1]));
  //cout << "min " <<  bbmin[0] << "," << bbmin[1] << endl << "max " << bbmax[0] << "," << bbmax[1] << endl;

  // HitRecord hit;
  for (unsigned int i = bbmin[1]; i <= bbmax[1]; i++)
    {
      for (unsigned int j = bbmin[0]; j <= bbmax[0]; j++)
	{
	  //Only color pixels inside the resolution
	  if (i < vres[1] && j < vres[0])
	    {
	  //determine if you are inside the triangle;
	  double alpha = triLine(j, i, p, 1, 2) / triLine(p.p[0][0], p.p[0][1], p, 1, 2);
	  double beta = triLine(j, i, p, 2, 0) / triLine(p.p[1][0], p.p[1][1], p, 2, 0); //might have to change interval to 0 2
	  double gamma = triLine(j, i, p, 0, 1) / triLine(p.p[2][0], p.p[2][1], p, 0, 1);
	  if (alpha > 0 && beta > 0 && gamma > 0)
	    {
	      HitRecord hit;
	      hit.fill = alpha * p.colors[0] + beta * p.colors[1] + gamma * p.colors[2];
	      hit.z = alpha * p.p[0][2] + beta * p.p[1][2] + gamma * p.p[2][2];
	      //The z values have a tendency to become negative. This fixes that
	      if (hit.z < 0)
		hit.z *= -1.0;
	      pix[i][j].push_back(hit);)
	    }
	    }
	}
    }
}

void World::vertexProcessing(Polygon& p)
{
  //shading
  //for each vertex
  for (unsigned int j = 0; j < 3; j++)
    {
      SlVector3 localcolor(0,0,0);
      for (unsigned int i = 0; i < l.size(); i++)
	{
	  //for each vertex
	  //for (unsigned int j = 0; j < 3; j++)
	  //{
	  //change v[j] to vat if this doesn't work
	  SlVector3 V = (vfrom - p.v[j]) / mag(vfrom - p.v[j]);
	  SlVector3 L = (l[i] - p.v[j]) / mag(l[i] - p.v[j]);
	  SlVector3 H = (L + V) / mag(L + V);
	  double diffuse = max(0.0, dot(p.vn[j], L));
	  double specular = pow(max(0.0, dot(p.vn[j], H)), p.fill[5]);
	  SlVector3 tempFill(p.fill[0], p.fill[1], p.fill[2]);
	  localcolor += (p.fill[3] * diffuse * tempFill + p.fill[4] * specular) * I;
	  //}
	}
      p.colors.push_back(localcolor);
      //cout << localcolor << endl;
    }

  //homogenize
  SlVector4 vtemp1(p.v[0][0], p.v[0][1], p.v[0][2], 1);
  SlVector4 vtemp2(p.v[1][0], p.v[1][1], p.v[1][2], 1);
  SlVector4 vtemp3(p.v[2][0], p.v[2][1], p.v[2][2], 1);
  vector<SlVector4> vtemp;
  vtemp.push_back(vtemp1);
  vtemp.push_back(vtemp2);
  vtemp.push_back(vtemp3);

  //transform the polygon's vertices
  for (unsigned int i = 0; i < 3; i++)
    {
      p.p.push_back(M * vtemp[i]);
    }
  //cout << p.p.size() << endl;
}

void World::makeImg()
{
  //compute all necessary values
  right = tan((vangle / 2.0) * (3.1415926535897 / 180));
  top = right;
  left = -1 * right;
  bottom = left;
  near = -1 * vhither;
  far = 1000 * near;
  I = 1 / (l.size() - 1);
  SlVector3 u, v, w;

  //convert to world space
  w = (vfrom - vat) / mag(vfrom - vat);
  u = cross(vup, w) / mag(cross(vup,w));
  v = cross(w, u);
  
  //viewpoint matrix
  Mvp.set(vres[0]/2.0, 0, 0, (vres[0] - 1.0)/2.0,
	  0, vres[1]/2.0, 0, (vres[1] - 1.0)/2.0,
	  0, 0, 1, 0,
	  0, 0, 0, 1);

  SlTransform Morth(2.0/(right - left), 0, 0, -1.0 * ((right + left)/(right - left)),
		    0, 2.0/(top - bottom), 0, -1.0 * ((top + bottom)/(top - bottom)),
		    0, 0, 2.0/(near - far), -1.0 * ((near + far)/(near - far)),
		    0, 0, 0, 1);

  SlTransform Mp(near, 0, 0, 0,
		 0, near, 0, 0,
		 0, 0, near + far, -1.0 * far * near,
		 0, 0, 1, 0);

  Mpersp = Morth * Mp;
  //Mpersp(0,0) = -1 * Mpersp(0,0);
  //Mpersp(1,1) = -1 * Mpersp(1,1);
  //Mpersp(2,3) = -1 * Mpersp(2,3);
  //perspective matrix
  //Mpersp.set((2 * near)/(right - left), 0, (left + right)/(left - right), 0,
  //	     0, (2 * near)/(top - bottom), (bottom + top)/(bottom - top), 0,
  //	     0, 0, (far + near)/(near - far), (2 * far * near)/(far - near),
  //	     0, 0, 1, 0);

  //camera matrix
  SlTransform Mtemp1(u[0], u[1], u[2], 0,
		     v[0], v[1], v[2], 0,
		     w[0], w[1], w[2], 0,
		     0, 0, 0, 1);
  SlTransform Mtemp2(1, 0, 0, -1.0 * vfrom[0],
		     0, 1, 0, -1.0 * vfrom[1],
		     0, 0, 1, -1.0 * vfrom[2],
		     0, 0, 0, 1);
  Mcam = Mtemp1 * Mtemp2;

  //Mcam.set(u[0], v[0], w[0], vfrom[0],
  //	   u[1], v[1], w[1], vfrom[1],
  //	   u[2], v[2], w[2], vfrom[2],
  //	   0, 0, 0, 1);

  M = Mvp * Mpersp * Mcam;
  cout << Mvp << endl << Mpersp << endl << Mcam << endl << M << endl;

  //Since I already have a class set up, HitRecord will be used to store the colors and z values found at each pixel
  //vector<HitRecord> pixels[vres[0]][vres[1]];

  //by default, all pixels are the background
  pix.resize(vres[0]);
  for (int i = 0; i < vres[0]; i++)
    pix[i].resize(vres[1]);

  //cout << pix.size() << endl << pix[100].size() << endl << pix[100][100][0].fill << endl;
  //for (int i = 0; i < vres[0]; i++)
  //{
  //  for (int j = 0; j < vres[1]; j++)
  //    {
  //      HitRecord bg;
  //      bg.fill = b;
  //      bg.z = 10000;
  //      pix[i][j].push_back(bg);
  //    }
  //}

  for (unsigned int i = 0; i < polyList.size(); i++)
    {
      vertexProcessing(polyList[i]);
      rasterize(polyList[i]);
    }

  for (unsigned int i = pix.size() - 1; i > 0; i--)
    {
      for (unsigned int j = 0; j < pix[0].size(); j++)
	{
	  //if there were no hits, pixel is background color
	  if (pix[i][j].size() == 0)
	    image.push_back(b);
	  else
	    {
	      double lowest = 10000;
	      //cout << lowest << endl;
	      unsigned int lowestK = 0;
 	      //go through all the hits, choose the color with the smallest z
	      for (unsigned int k = 0; k < pix[i][j].size(); k++)
		{
		  //cout << pix[i][j][k].z << endl;
		  if (pix[i][j][k].z < lowest)
		    {
		      lowest = pix[i][j][k].z;
		      lowestK = k;
		    }
		}
	      cout << lowest << endl;
	      image.push_back(pix[i][j][lowestK].fill);
	    }
	}
    }
}
/**
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

  if (!bg)
    {
      record.fill = shade(record);

      //If you want to s3ee the image without the reflection errors, comment out this section.
      //*************************************************************************
      //reflection
      if (record.ks > 0)
	{
	  //start recursion
	  startRecurse = true;
	  if (recurseCounter < 5)
	    {
	      //View direction
	      SlVector3 L = ray.d;
	      //compute reflection direction
	      SlVector3 ref = (-1 * L) + (2 * dot(L, record.normal) * record.normal);
	      Ray reflect(ref,record.interPoint);
	      record.fill = record.ks * trace(reflect).fill;
	    }
	  else
	    startRecurse = false;
	}
      /******************************************************************************
    }
  return record;
}
**/

/**
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
**/

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
