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

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                              Welcome to CIS22C-Lab 6                                         *" << endl;
    cout << "*                                 Student: Xu Tang                                             *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Redo the PriorityQueue assignment using your BinaryTree structure from Lab#5.             *" << endl;
    cout << "*  + For each Node in the tree, it has a KEY (character) and a VALUE (frequency).              *" << endl;
    cout << "*  + A tree, constructed this way is called a 'Dictionary'.  Process the speech as in the      *" << endl;
    cout << "*    PriorityQueue lab assignment, and output the frequencies for each character.              *" << endl;
    cout << "*  + Your expectation is the Dictionary will come out in KEY order rather than VALUE order.    *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Import Data                                                                              *" << endl;
    cout << "*  2) Dispaly hash table                                                                       *" << endl;
    cout << "*  3) Find key                                                                                 *" << endl;
    cout << "*  4) Test all                                                                                 *" << endl;
    cout << "*  5) Get current size                                                                         *" << endl;
    cout << "************************************************************************************************" << endl;

}

string trim(string s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p + 1);

    return s;
}


void main()
{
    bool exit = false;
    int input;

    HashMap<string, double, int> h;

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-4]:";
        cin >> input;

        if (input == 1)
        {
            h.importDataFile("UProducts.csv");            
        }
        else if (input == 2)
        {
            h.display();
        }
        else if (input == 3)
        {
            bool cont = true;
            string key;
            double val;

            do
            {
                //cin.ignore(INT_MAX);

                cout << "Find entry by key, please enter a key [Enter x to exit]: ";
                getline(cin, key);
                key = trim(key);

                if (key !="x")
                {
                    if (val = h.get(key))
                    {
                        cout << "Value of " << key << " found: " << val << endl;
                    }
                    else
                    {
                        cout << key << " doen't exist in hash table." << endl;
                    }
                }
                else
                {
                    cont = false;
                }
            } while (cont);
        }
        else if (input == 4)
        {
            h.testAll("UProducts.csv");
        }
        else if (input == 5)
        {
            cout << "Current size: " << h.size() << endl;
        }
        else
        {
            exit = true;
        }


        system("pause");
    } while (exit != true);


    cout << "Going to close application. ";
    system("pause");
}

