#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TABLE_SIZE = 128;

struct TableList {
    string key;
    int value;
    struct TableList *next;
};

unsigned hash_function(string);
unsigned rehash(unsigned);

class HashMap
{
private:
    TableList **table;
public:
    HashMap()
    {
        table = new TableList*[TABLE_SIZE];
        for(int i = 0; i < TABLE_SIZE; i++) table[i] = NULL;
    }

    struct TableList* lookup(string s)
    {
        struct TableList *tp;
        for(tp = table[hash_function(s)]; tp != NULL; tp = tp->next)
            if((tp->key).compare(s) == 0) return tp;  // found
        return NULL;  // not found
    }

    void put(string key, int value) {
        struct TableList *tp;
        unsigned hash;

        // not found
        if(!(tp = lookup(key))) {
            tp = new TableList;
            tp->key = key;
            tp->value = value;
            hash = hash_function(key);
            tp->next = table[hash];
            table[hash] = tp;
            // it's already there
        } else {
            tp->key = key;
            tp->value = value;
            hash = hash_function(key);
            table[hash] = tp;
        }
    }

    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL) delete table[i];
        delete[] table;
    }

    void showMap()
    {
        struct TableList *tp;
        for (int i = 0; i < TABLE_SIZE; i++) {
            tp = table[i];
            if(tp)
                cout << "table[" << i << "] " << tp->key << "(" << tp->value << ")";
            else
                continue;
            while(tp) {
                cout << "->" << tp->key << "(" << tp->value << ")";
                tp = tp->next;
            }
            cout << endl;
        }
    }
};

unsigned hash_function(string s)
{
    unsigned hash = 0;

    for (int i = 0; i < s.length(); i++)
        hash = s[i] + 31*hash;
    return hash % TABLE_SIZE;
}

int main()
{
    HashMap m;

    string line;

    //ifstream dict_reader("/usr/share/dict/words");
    ifstream dict_reader("C:/TEST/linux.words");
    if( !dict_reader ) {
        cout << "Error opening input file - dict  " << endl ;
        exit(1) ;
    }

    int count = 0;
    while(getline(dict_reader,line)) {
        if((line[0] >= 'x' && line[0] < 'y') || (line[0] >= 'X' && line[0] < 'Y') ) {
            m.put(line,count++);
        }
    }

    m.showMap();
    return 0;
}



#include <iostream>
using namespace std;

class HashEntry
{
private:
    int key;
    int value;
public:
    HashEntry(int key, int value)
    {
        this->key = key;
        this->value = value;
    }

    int getKey()
    {
        return key;
    }

    int getValue()
    {
        return value;
    }
};

const int TABLE_SIZE = 5;

class HashMap
{
private:
    HashEntry **table;
public:
    HashMap()
    {
        table = new HashEntry*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    int get(int key)
    {
        int hash = (key % TABLE_SIZE);
        while (table[hash] != NULL && table[hash]->getKey() != key)
            hash = (hash + 1) % TABLE_SIZE;
        if (table[hash] == NULL)
            return -1;
        else
            return table[hash]->getValue();
    }

    void put(int key, int value)
    {
        int hash = (key % TABLE_SIZE);
        int hashCount = 0;
        if(table[hash] != NULL)
            // Same hash, but the key is different, use another hash
            while (table[hash] != NULL && table[hash]->getKey() != key) {
                hash = (hash + 1) % TABLE_SIZE;
                // if not found, give up
                if(hashCount++ == TABLE_SIZE) break;
            }
        // Same hash, delele old and make a new one
        if (table[hash] != NULL)
            delete table[hash];
        table[hash] = new HashEntry(key, value);
    }

    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
};

int main()
{
    HashMap *myMap = new HashMap;
    int key;
    for(int i = 0; i < TABLE_SIZE; i++) {
        key = i*10;
        myMap->put(key, key*10);
        cout << key << ": " << myMap->get(key) << endl;
    }

    for(int i = 0; i < TABLE_SIZE; i++) {
        key = i*20;
        myMap->put(key, key*100);
        cout << key << ": " << myMap->get(key) << endl;
    }

    return 0;
}
