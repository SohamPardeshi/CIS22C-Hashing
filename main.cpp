///////////////////////////////////////////////////////////
//  Main.cpp
//  CIS22C - Group Project Hasing
//  Created on: 2/26/2017 
//  Student: Xu Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Hashing.h"
#include "BloomFilter.h"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                          Welcome to CIS22C-Group Project                                     *" << endl;
    cout << "*                                 Student: Xu Tang                                             *" << endl;
    cout << "*                  Group: Soham Pardeshi, Ben Fong, Samantha Seymour                           *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate following Hashing and Bloom Filter.                            *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Hashing                                                                                  *" << endl;
    cout << "*  2) Bloom Filter                                                                             *" << endl;
    cout << "************************************************************************************************" << endl;

}



void main()
{
    bool exit = false;
    int input;

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-2]:";
        cin >> input;

        if (input == 1)
        {
            HashMap<string, double, int> h;
            h.main();
        }
        else if (input == 2)
        {
            BloomFilter<string> b;
            b.main();
        }
        else
        {
            exit = true;
        }
    } while (exit != true);


    cout << "Going to close application. ";
    system("pause");
}

