#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#ifndef _CIS22C_HASHING
#define _CIS22C_HASHING

// definition begin **********************************************************************************
// Node class
template <class K, class V>
class Entry
{
    K key;
    V value;

public:
    Entry<K, V> *left;
    Entry<K, V> *right;
    
    // Constructors
    Entry()
    {
        left = nullptr;
        right = nullptr;
    }

    Entry(K aKey, V aVal)
    {
        key = aKey;
        value = aVal;

        left = nullptr;
        right = nullptr;
    }

    K getKey()
    {
        return this->key;
    }


    V getValue()
    {
        return this->value;
    }

    //friend class HashMap;
};


// Interface of Hash Tree
template <class K, class V, class H>
class HashMap {
private:
    int capacity = 500;
    int num;                    // number of entries
    Entry<K, V> ** table;       // bucket array


public: 
    //typedef Entry<const K, V> Entry;    // a (key,value) pair

    HashMap()    // constructor
    {
        table = new Entry<K, V>*[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    }

    void menu()
    {
        cout << "************************************************************************************************" << endl;
        cout << "*                              Welcome to CIS22C-Group Project                                 *" << endl;
        cout << "*                                 Student: Xu Tang                                             *" << endl;
        cout << "*                  Group: Soham Pardeshi, Ben Fong, Samantha Seymour                           *" << endl;
        cout << "*                                                                                              *" << endl;
        cout << "* This program will demonstrate:                                                               *" << endl;
        cout << "*  + Hashing                                                                                   *" << endl;
        cout << "*                                                                                              *" << endl;
        cout << "* Choices:                                                                                     *" << endl;
        cout << "*  0) Back to main menu                                                                        *" << endl;
        cout << "*  1) Import Data                                                                              *" << endl;
        cout << "*  2) Display hash tree                                                                        *" << endl;
        cout << "*  3) Find key                                                                                 *" << endl;
        cout << "*  4) Test all                                                                                 *" << endl;
        cout << "*  5) Get current size                                                                         *" << endl;
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
            cout << "Please enter your choice [0-4]:";
            cin >> input;

            if (input == 1)
            {
                importDataFile("UProducts.csv");
                system("pause");
            }
            else if (input == 2)
            {
                display();
                system("pause");
            }
            else if (input == 3)
            {
                bool cont = true;
                string key;
                double val;
                //cin.clear();
                cin.ignore(INT_MAX, '\n');

                do
                {
                    cout << "Find entry by key, please enter a key [Enter x to exit]: ";
                    getline(cin, key);
                    key = trim(key);

                    if (key != "x")
                    {
                        if (val = get(key))
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
                system("pause");
            }
            else if (input == 4)
            {
                testAll("UProducts.csv");
                system("pause");
            }
            else if (input == 5)
            {
                cout << "Current size: " << size() << endl;
                system("pause");
            }
            else
            {
                exit = true;
            }
        } while (exit != true);
    }

    int string2ascii(string s)
    {
        int sum = 0;
        for (unsigned int i = 0; i < s.size(); i++)
        {
            sum += s[i];
        }

        return sum;
    }

    string trim(string s)
    {
        // Find absence of character in string
        size_t p = s.find_first_not_of(" \t");

        // Erase characters from string
        s.erase(0, p);

        // Finds the last character equal to none of the 
        // characters in the given character sequence. 
        p = s.find_last_not_of(" \t");

        if (string::npos != p)
        {
            s.erase(p + 1);
        }


        return s;
    }


    H hashFunc(K& k) // hash function
    {
        int k_ascii = string2ascii(k);
        //cout << k << " to int : " << k_ascii << endl;
        return (k_ascii % capacity);
    }

    void put(K key, V value) // insert/replace (k,v)
    {
        H hash = hashFunc(key);
        //cout << "hash: " << hash << endl; system("pause");

        if (table[hash] == NULL)
        {
            table[hash] = new Entry<K, V>(key, value);
            num++;
        }
        else
        {
            //cout << "collection happened at " << hash << " for " << key << " with " << table[hash]->getKey() << endl; system("pause");
            Entry<K, V> * entryPtr = table[hash];

            bool cont = true;

            do
            {
                if (entryPtr->getKey() < key) //  To left
                {
                    if (entryPtr->left == NULL)
                    {
                        entryPtr->left = new Entry<K, V>(key, value);
                        num++;
                        cont = false;
                    }
                    else
                    {
                        entryPtr = entryPtr->left;
                    }
                }
                else// To right
                {
                    if (entryPtr->right == NULL)
                    {
                        entryPtr->right = new Entry<K, V>(key, value);
                        num++;
                        cont = false;
                    }
                    else
                    {
                        entryPtr = entryPtr->right;
                    }
                }
            } while (cont && entryPtr != NULL);            
            
        }
    }

    V get(K key)               // find entry with key k
    {
        H hash = hashFunc(key);
        if (table[hash] != NULL)
        {
            Entry<K, V> * entryPtr = table[hash];

            bool cont = true;
            K entryKey;

            do
            {
                entryKey = entryPtr->getKey();

                if (entryKey == key)
                {
                    return entryPtr->getValue();
                }
                else if (entryKey < key) //  To left
                {
                    entryPtr = entryPtr->left;
                }
                else// To right
                {
                    entryPtr = entryPtr->right;
                }

            } while (entryPtr != NULL);
        }

        return NULL;
    }

    void display()              // Print hash table
    {
        for (int i = 0; i < capacity; i++)
        {
            cout << "| " << i << " | ";

            if (table[i] == NULL)
            {
                 cout << "NULL" << endl;
            }
            else
            {
                cout << "(root)";
                traversal(table[i]);
                cout << endl;
            }
            
        }
    }

    void traversal(Entry<K,V> * entryPtr)
    {
        if (entryPtr)
        {            
            cout << entryPtr->getKey() << ":" << entryPtr->getValue() << " | ";

            if (entryPtr->left != NULL)
            {
                cout << "(<<< left)";
                traversal(entryPtr->left);
            }
                       
            if (entryPtr->right != NULL)
            {
                cout << "(right >>>)";
                traversal(entryPtr->right);
            }
            
        }
    }

    int size() const               // number of entries
    {
        return num;
    }

    bool empty() const             // is the map empty
    {
        return num == 0;
    }

    void clear()                    // clear hash table
    {
        for (int i = 0; i < capacity; i++)
        {
            if (table[i] != NULL)
            {
                removeTree(table[i]);
            }
        }
    }


    void removeTree(Entry<K,V> * entryPtr)
    {
        if (entryPtr)
        {
            removeTree(entryPtr->left);
            removeTree(entryPtr->right);
        }
        
        
        delete entryPtr;
        num--;
        //cout << "current size: " << num << endl;
    }

    string* csv2arr(string line)
    {
        char delimiter = ',';
        const int SIZE = 2;
        string str, *ret = new string[SIZE];

        istringstream is(line); // Input string stream

        int i = 0;
        while (getline(is, str, delimiter))
        {
            ret[i] = str;
            i++;
        }

        return ret;
    }

    void importDataFile(string file)
    {
        fstream datafile;
        string line, *item;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;

        datafile.open(file);
        if (datafile.fail())
        {
            cout << "Error: couldn't open the data file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            int row = 0;
            V v;
            while (getline(datafile, line))
            {
                item = csv2arr(line); // parse csv string to array
                v = atof(item[1].c_str()); 
                // typeid(v).name()
                put(item[0], v);
                cout << item[0] << "\t" << v << endl;
                row++;
            }

            //cout << "\t " << List.getCurrentSize() << " words imported." << endl; //system("pause");
        }
    }

    void testAll(string file)
    {
        fstream datafile;
        string line, *item;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;

        datafile.open(file);
        if (datafile.fail())
        {
            cout << "Error: couldn't open the data file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            int errorNum = 0;
            V v, v2;
            while (getline(datafile, line))
            {
                item = csv2arr(line); // parse csv string to array
                v = atof(item[1].c_str());
                v2 = this->get(item[0]);

                cout << setw(20) << item[0] << setw(10) << v << setw(10) << v2 << endl;

                if (v != v2)
                {
                    errorNum++;
                }
                
                
            }

            cout << "Total rows of error: " << errorNum << endl;
        }
    }

    ~HashMap()
    {
        clear();
    }
};

#endif
// definition end **********************************************************************************

