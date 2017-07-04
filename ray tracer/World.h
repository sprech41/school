/**************************************************************
 * File:    World.h
 * Author : Jacob Sprecher
 * Date   : 9/5/2016
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
using namespace std;

class World
{
public:
        //default constructor
	World();
	
	//-------------------------------------------------------
	// Name: trace
	// PreCondition: N/A
	// PostCondition: Returns the fill color of the closest polygon.
	//---------------------------------------------------------
	SlVector3 trace(SlVector3 ray);

	//-------------------------------------------------------
	// Name: traceImg
	// PreCondition: N/A
	// PostCondition: Fills the image vector with the color of each pixel
	//---------------------------------------------------------
	void traceImg();

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
	vector<int> l;
	vector<Polygon> polyList;

	//Contains the fill color of every pixel
	vector<SlVector3> image;
};
#endif
