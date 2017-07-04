/**************************************************************
 * File:    World.h
 * Author : Jacob Sprecher
 * Date   : 10/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Contains the prototypes for everything involving the scene, such as background and camera data
 *
 *************************************************************/

#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <string>
#include <stdio.h>
#include "Polygon.h"
#include "slTransform.cpp"
using namespace std;

class World
{
public:
        //default constructor
	World();
	
        //-------------------------------------------------------
        // Name: shade
        // PreCondition: hitrecord is not empty
        // PostCondition: computes diffuse and specular component, returns a color
        //---------------------------------------------------------
	SlVector3 shade(HitRecord hit);

	//-------------------------------------------------------
        // Name: triLine
        // PreCondition: N/A
        // PostCondition: function that returns alpha beta or gamma in rasterize
        //---------------------------------------------------------
	double triLine(double x, double y, Polygon p, int i1, int i2);

        //-------------------------------------------------------
        // Name: vertexProcessing
        // PreCondition: N/A
        // PostCondition: shades and transforms vertices of a triangle.
        //---------------------------------------------------------
	void vertexProcessing(Polygon& p);

        //-------------------------------------------------------
        // Name: rasterize
        // PreCondition: N/A
        // PostCondition: rasterizes a given triangle
        //---------------------------------------------------------
	void rasterize(Polygon& p);

	//-------------------------------------------------------
        // Name: makeImg
        // PreCondition: N/A
        // PostCondition: Fills the image vector with the color of each pixel
        //---------------------------------------------------------
	void makeImg();

	//-------------------------------------------------------
	// Name: trace
	// PreCondition: N/A
	// PostCondition: Returns the fill color of the closest polygon.
	//---------------------------------------------------------
	//HitRecord trace(Ray ray);

	//-------------------------------------------------------
	// Name: traceImg
	// PreCondition: N/A
	// PostCondition: Fills the image vector with the color of each pixel
	//---------------------------------------------------------
	//void traceImg();

	//-------------------------------------------------------
	// Name: writeImg
	// PreCondition: image vector is not empty
	// PostCondition: Writes a new ppm image using the image vector
	//---------------------------------------------------------
	void writeImg(string name);
	
	//values parsed from nff file
	SlVector3 b;
	SlVector3 vfrom;
	SlVector3 vat;
	SlVector3 vup;
	double vangle;
	double vhither;
	vector<int> vres;
	vector<SlVector3> l;
	vector<Polygon> polyList;
	double top, bottom, right, left, near, far;
	//Contains the fill color of every pixel
	vector<SlVector3> image;
	
	vector<vector<vector <HitRecord> > > pix;

	//Matrices
	SlTransform Mvp;
	SlTransform Mpersp;
	SlTransform Mcam;
	SlTransform M;
	double I;
	//bool startRecurse;
	//int recurseCounter;
};
#endif
