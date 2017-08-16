/******************
 *File: Driver.cpp
 *Project: Project 4
 *Author: Jacob Sprecher
 *Date: 4/21/2016
 *Email: sprech1@umbc.edu
 *
 *This file tests all MMheap functions. All functions work properly.
 ***********************/

#include "MMheap.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <cstdlib>
using namespace std;
int main(int argc, char *argv[])
{
  MMheap<int> theHeap;
  MMheap<int> theHeap2;
  MMheap<int> emptyHeap;
  vector<int> numbers;
  string filename;

  if(argc == 2)
    {
      filename = argv[1];
    }
  else
    {
      cout << "Not enough command line arguments." << endl;
      return 0;
    }

  ifstream file(filename.c_str());

  if (file.is_open())
    {
      string line;

      while(getline(file, line))
	{
	  numbers.push_back(atoi(line.c_str()));
	}
    }
  else
    {
      cout << "File was not opened." << endl;
      return 0;
    }
  
  cout << "*** Test exception handling ***" << endl;
  try
    {
      emptyHeap.dump();
    }
  catch (MyException &e)
    {
      cout << e.getMessage() << endl;
    }
  try
    {
      emptyHeap.getMin();
    }
  catch (MyException &e)
    {
      cout << e.getMessage() << endl;
    }
  try
    {
      emptyHeap.getMax();
    }
  catch (MyException &e)
    {
      cout << e.getMessage() << endl;
    }
  try
    {
      emptyHeap.deleteMin();
    }
  catch (MyException &e)
    {
      cout << e.getMessage() << endl;
    }
  try
    {
      emptyHeap.deleteMax();
    }
  catch (MyException &e)
    {
      cout << e.getMessage() << endl;
    }

  cout << "-------------------" << endl;
  cout << "*** Insert 18, 94, 74. ***" << endl;
  cout << "--------------------" << endl;
  theHeap2.insert(18);
  theHeap2.insert(94);
  theHeap2.insert(74);
  theHeap2.dump();

  cout << "--------------------" << endl;
  cout << "*** Then deleteMax. ***" << endl;
  cout << "--------------------" << endl;

  theHeap2.deleteMax();
  theHeap2.dump();


  cout << "--------------------" << endl;
  cout << "*** Make the min-max heap in Figure 6.57. ***" << endl;
  cout << "--------------------" << endl;
  
  for (unsigned int i = 0; i < numbers.size(); i++)
    {
      theHeap.insert(numbers[i]);
    }
  theHeap.dump();
    
  cout << "--------------------" << endl;
  cout << "*** Then insert 53, 57, 13, 12, 9, 10. ***" << endl;
  cout << "--------------------" << endl;

  theHeap.insert(53);
  theHeap.insert(57);
  theHeap.insert(13);
  theHeap.insert(12);
  theHeap.insert(9);
  theHeap.insert(10);
  theHeap.dump();

  cout << "--------------------" << endl;
  cout << "*** Then call deleteMin 3 times. ***" << endl; 
  cout << "--------------------" << endl;

  theHeap.deleteMin();
  theHeap.deleteMin();
  theHeap.deleteMin();
  theHeap.dump();

  cout << "--------------------" << endl;
  cout << "*** Then call deleteMax 3 times. ***"<<endl;
  cout << "--------------------" << endl;

  theHeap.deleteMax();
  theHeap.deleteMax();
  theHeap.deleteMax();
  theHeap.dump();

  cout << "--------------------" << endl;  


  return 0;
}
