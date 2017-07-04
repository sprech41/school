/**************************************************************
 * File:    Main.h
 * Author : Jacob Sprecher
 * Date   : 9/5/2016
 * E-mail:  sprech1@umbc.edu
 *
 * Reads data from NFF file and feeds it to other classes. All functions work properly.
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
	double a, b, c, d, j, k, l, m, n;
	int e, f, g;
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
						sscanf(line.c_str(), "%s %d %d", &name, &e, &f);
						myWorld.vres.push_back(e);
						myWorld.vres.push_back(f);
					}
				}
			}
			
			else if (line.at(0) == 'l')
			{
				sscanf(line.c_str(), "%s %d %d %d", &name, &e, &f, &g);
				myWorld.l.push_back(e);
				myWorld.l.push_back(f);
				myWorld.l.push_back(g);
			}

			else if (line.at(0) == 'f')
			{
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
			    Polygon poly;
			    for (int i = 0; i < 3; i++)
			      {
				getline(file,line);
				sscanf(line.c_str(), "%lf %lf %lf", &a, &b, &c);
				SlVector3 vertex(a,b,c);
				poly.v.push_back(vertex);
				poly.fill = ftemp;
			      }
			    myWorld.polyList.push_back(poly);
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
