/**************************************************************
 * File:    Main.h
 * Author : Jacob Sprecher
 * Date   : 10/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Reads data from NFF file and feeds it to other classes.
 *
 *************************************************************/

#include <fstream>
#include <iostream>
#include "World.h"
#include "slVector.cpp"
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
  cout << "3 arguments required. Please refer to readme.txt" << endl;
  return 0;
  }
	World myWorld;
	ifstream file (argv[1]);
	string output = argv[2];
	string line;
	double a, b, c, d, j, k, l, m, n, x, y, z;
	double e, f;
	char name;
	vector<double> ftemp;

	if (file.is_open())
	{
		while (getline(file,line))
		{
			if (line.at(0) == 'b')
			{
				sscanf(line.c_str(), "%c %lf %lf %lf", &name, &a, &b, &c);
				myWorld.b.set(a, b, c);
			}
			else if (line.at(0) == 'v')
			{
				for (int i = 0; i < 6; i++)
				{
					getline(file,line);
					if (i == 0)
					{
						sscanf(line.c_str(), "%s %lf %lf %lf", &name, &a, &b, &c);
						myWorld.vfrom.set(a, b, c);
					}
					else if (i == 1)
					{
					  sscanf(line.c_str(), "%s %lf %lf %lf", &name, &a, &b, &c);
						myWorld.vat.set(a, b, c);
					}
					else if (i == 2)
					{
						sscanf(line.c_str(), "%s %lf %lf %lf", &name, &a, &b, &c);
						myWorld.vup.set(a, b, c);
					}
					else if (i == 3)
					{
						sscanf(line.c_str(), "%s %lf", &name, &d);
						myWorld.vangle = d;
					}
					else if (i == 4)
					{
						sscanf(line.c_str(), "%s %lf", &name, &d);
						myWorld.vhither = d;
					}
					else
					{
						sscanf(line.c_str(), "%s %lf %lf", &name, &e, &f);
						myWorld.vres.push_back(e);
						myWorld.vres.push_back(f);
					}
				}
			}
			
			else if (line.at(0) == 'l')
			{
			  //SlVector3 light;
				sscanf(line.c_str(), "%s %lf %lf %lf", &name, &x, &y, &z);
				//light.push_back(x);
				//light.push_back(y);
				//light.push_back(z);
				SlVector3 light(x,y,z);
				myWorld.l.push_back(light);
			}

			else if (line.at(0) == 'f')
			{
			        ftemp.clear();
				sscanf(line.c_str(), "%s %lf %lf %lf %lf %lf %lf %lf %lf", &name, &a, &b, &c, &j, &k, &l, &m, &n);
				ftemp.push_back(a);
				ftemp.push_back(b);
				ftemp.push_back(c);
				ftemp.push_back(j);
				ftemp.push_back(k);
				ftemp.push_back(l);
				ftemp.push_back(m);
				ftemp.push_back(n);
			}
			
			else if (line.at(0) == 'p')
			  {
			    if (line.at(2) == '4')
			      {
				Polygon poly1;
				Polygon poly2;
                                for (int i = 0; i < 4; i++)
                                  {
                                    getline(file,line);
                                    sscanf(line.c_str(), "%lf %lf %lf", &a, &b, &c);
                                    SlVector3 vertex(a,b,c);
				    if (i == 1)
				      poly1.v.push_back(vertex);
				    else if (i == 3)
				      poly2.v.push_back(vertex);
				    else
				      {
					poly1.v.push_back(vertex);
					poly2.v.push_back(vertex);
				      }
                                    poly1.fill = ftemp;
				    poly2.fill = ftemp;
                                  }
				//compute normal
				poly1.n = cross(poly1.v[1] - poly1.v[0], poly1.v[2] - poly1.v[0]) / mag(cross(poly1.v[1] - poly1.v[0], poly1.v[2] - poly1.v[0]));
				poly2.n = cross(poly2.v[1] - poly2.v[0], poly2.v[2] - poly2.v[0]) / mag(cross(poly2.v[1] - poly2.v[0], poly2.v[2] - poly2.v[0]));

                                myWorld.polyList.push_back(poly1);
				myWorld.polyList.push_back(poly2);
			      }
			    else
			      {
				Polygon poly;
				for (int i = 0; i < 3; i++)
				  {
				    getline(file,line);
				    sscanf(line.c_str(), "%lf %lf %lf", &a, &b, &c);
				    SlVector3 vertex(a,b,c);
				    poly.v.push_back(vertex);
				    poly.fill = ftemp;
				  }
				poly.n = cross(poly.v[1] - poly.v[0], poly.v[2] - poly.v[0]) / mag(cross(poly.v[1] - poly.v[0], poly.v[2] - poly.v[0]));

				myWorld.polyList.push_back(poly);
			      }
			  }
		}
	}
	else
		cout << "Error: file not opened." << endl;

	cout << "Creating image... " << endl;
	myWorld.traceImg();
	myWorld.writeImg(output);
	file.close();
	cout << "done." << endl;
	return 0;
}
