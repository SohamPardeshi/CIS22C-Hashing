
#ifndef _CIS22C_HASHING
#define _CIS22C_HASHING

#include <iostream>
using namespace std;

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


// Interface of PriorityQueue
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

    int string2ascii(string s)
    {
        int sum = 0;
        for (unsigned int i = 0; i < s.size(); i++)
        {
            sum += s[i];
        }

        return sum;
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
        cout << "current size: " << num << endl;
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

