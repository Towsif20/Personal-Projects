#include<iostream>
#include<cstring>
#include<cstdlib>

#define INF 999999;
#define available 0
#define taken 1
#define deleted -1

#define c1 9
#define c2 20

using namespace std;

bool isTaken(string * s, string t, int index)
{
    for(int i=0;i<=index;i++)
    {
        if(t.compare(s[i]) == 0)
            return true;
    }

    return false;
}

string * RandomGenerator()
{
    string * s = new string[10000];

    for(int i=0;i<10000;i++)
        s[i] ="";

    char alphabet[52];

    for(int i=0;i<26;i++)
    {
        alphabet[i] = '\n';
    }

    for(int i=0;i<26;i++)
    {
        alphabet[i] = 'a' + i;
        alphabet[26+i] = 'A' + i;
    }



    char temp[7];

    for(int i=0;i<10000;)
    {
        for(int j=0;j<7;j++)
        {
            //cout<<rand()<<endl;
            temp[j] = alphabet[rand()%52];
        }

        string t = temp;

        if(isTaken(s, t, i))
            continue;

        else
        {
            s[i] = t;
            i++;
        }


    }

    return s;
}

struct SearchOutput
{
    int result;
    int hit;
};

int hash1(string s, int m)
{
   int h = 0, a = 127;

   for(int i=0;i<7;i++)
   {
       h = ( a*h + s[i] ) % m;
   }

   return h;
}

int hash2(string s, int m)
{
    unsigned long h = 5381;

    for(int i=0;i<7;i++)
    {
        h = (h<<5) + h + s[i];
    }

    return h%m;
}

int auxHash(string s, int m)
{
    int sum = 0;

    for(int i=0;i<7;i++)
    {
        sum += (int) s[i];
    }

    return sum%m;
}

struct HashNode
{
    string key;
    int value;
};

struct ListNode
{
    HashNode item;
    ListNode * next;
};

class LinkedList
{
    ListNode * list;
    int length;

public:

    LinkedList()
    {
        list = 0;
        length = 0;
    }

    void insert(HashNode h)
    {
        ListNode * node = new ListNode;
        node->item.key = h.key;
        node->item.value = h.value;

        node->next = NULL;

        if(list == NULL)
        {
            //cout<<"insert first of list\n";
            list = node;
            length++;
            return;
        }

        ListNode * temp = list;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = node;
        length++;

        //cout<<"insert list\n";

    }

    SearchOutput search(string k)
    {
        ListNode * temp = list;
        int hits = 1;

        SearchOutput out;

        out.result = -INF;

        while(temp != NULL)
        {
            if(temp->item.key.compare(k) == 0)
            {
                out.result = temp->item.value;
                break;
            }
            temp = temp->next;
            hits++;
        }

        out.hit = hits;

        return out;
    }

    void Delete(string k)
    {
        ListNode * temp = list;
        ListNode * prev = NULL;

        while(temp != NULL)
        {
            if(temp->item.key.compare(k) == 0)
            {
                break;
            }
            prev = temp;
            temp = temp->next;
        }

        if(temp == NULL)
            return;

        if(temp == list)
        {
            list = list->next;
            delete temp;
            length--;
        }

        else
        {
            prev->next = temp->next;
            delete temp;
            length--;
        }
    }

    int getLength()
    {
        return length;
    }
};

class HashTableChaining1
{
    LinkedList * table;
    int size;

    int collisions;
    int hits;

public:

    HashTableChaining1(int s)
    {
        size = s;

        table = new LinkedList[size];

        collisions = 0;
        hits = 0;
    }

    void insert(string k, int v)
    {
        //cout<<"insert table\n";
        HashNode h;
        h.key = k;
        h.value = v;

        int index = hash1(k, size);
        //cout<<index<<endl;
        table[index].insert(h);

        collisions += (table[index].getLength()-1);
    }

    int search(string k)
    {
        int index = hash1(k, size);

        SearchOutput out = table[index].search(k);

        hits += out.hit;

        return out.result;
    }

    void Delete(string k)
    {
        int index = hash1(k, size);

        table[index].Delete(k);
    }

    int getCollissions()
    {
        return collisions;
    }

    int getHits()
    {
        return hits;
    }

    double averageHits(double srch)
    {
        double d = (double) hits;

        return d/srch;
    }
};

class HashTableChaining2
{
    LinkedList * table;
    int size;

    int collisions;
    int hits;

public:

    HashTableChaining2(int s)
    {
        size = s;

        table = new LinkedList[size];

        collisions = 0;
        hits = 0;
    }

    void insert(string k, int v)
    {
        //cout<<"insert table\n";
        HashNode h;
        h.key = k;
        h.value = v;

        int index = hash2(k, size);
        //cout<<index<<endl;
        table[index].insert(h);

        collisions += table[index].getLength();
    }

    int search(string k)
    {
        int index = hash2(k, size);

        SearchOutput out = table[index].search(k);

        hits += out.hit;

        return out.result;
    }

    void Delete(string k)
    {
        int index = hash2(k, size);

        table[index].Delete(k);
    }

    int getCollissions()
    {
        return collisions;
    }

    double averageHits(double srch)
    {
        double d = (double) hits;

        return d/srch;
    }
};

class HashTableDoublehashing1
{
    HashNode * table;
    int * status;
    int size;
    int collisions, hits;

public:

    HashTableDoublehashing1(int s)
    {
        size = s;
        table = new HashNode[size];
        status = new int[size];

        for(int i=0;i<size;i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = hits = 0;
    }

    void insert(string k, int v)
    {
        int i = 0, index;
        int start = hash1(k, size);

        while(1)
        {
            index = (hash1(k, size) + i*auxHash(k, size)) % size;

            if(status[index] == 1) collisions++;

            else
            {
                table[index].key = k;
                table[index].value = v;
                status[index] = 1;

                return;
            }

            if(i>0 && index == start)
            {
                    return;
            }

            i++;

        }

        table[index].key = k;
        table[index].value = v;
        status[index] = 1;
    }

    int search(string k)
    {
        int i = 0, index;
        int start = hash1(k, size);

        hits++;

        while(1)
        {
            index = (hash1(k, size) + i*auxHash(k, size)) % size;

            if(table[index].key.compare(k) != 0) hits++;

            else
            {
                return table[index].value;
            }

            if(i>0 && index == start)
            {
                return -INF;
            }

            i++;

        }

    }

    void Delete(string k)
    {
        int i = 0, index;
        int start = hash1(k, size);

        while(1)
        {
            index = (hash1(k, size) + i*auxHash(k, size)) % size;

            if(table[index].key.compare(k) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;
            }

            if(i>0 && index == start)
            {
                return;
            }

            i++;

        }
    }

    int getCollissions()
    {
        return collisions;
    }

    int getHits()
    {
        return hits;
    }

    double averageHits(double srch)
    {
        double d = (double) hits;

        return d/srch;
    }
};

class HashTableDoublehashing2
{
    HashNode * table;
    int * status;
    int size;
    int collisions, hits;

public:

    HashTableDoublehashing2(int s)
    {
        size = s;
        table = new HashNode[size];
        status = new int[size];

        for(int i=0;i<size;i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = hits = 0;
    }

    void insert(string k, int v)
    {
        int i = 0, index;
        int start = hash2(k, size);

        while(1)
        {
            index = (hash2(k, size) + i*auxHash(k, size)) % size;

            if(status[index] == 1) collisions++;

            else
            {
                table[index].key = k;
                table[index].value = v;
                status[index] = 1;

                return;
            }

            if(i>0 && index == start)
            {
                    return;
            }

            i++;

        }

        table[index].key = k;
        table[index].value = v;
        status[index] = 1;
    }

    int search(string k)
    {
        int i = 0, index;
        int start = hash2(k, size);

        hits++;

        while(1)
        {
            index = (hash2(k, size) + i*auxHash(k, size)) % size;

            if(table[index].key.compare(k) != 0) hits++;

            else
            {
                return table[index].value;
            }

            if(i>0 && index == start)
            {
                return -INF;
            }

            i++;

        }

    }

    void Delete(string k)
    {
        int i = 0, index;
        int start = hash2(k, size);

        while(1)
        {
            index = (hash2(k, size) + i*auxHash(k, size)) % size;

            if(table[index].key.compare(k) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;
            }

            if(i>0 && index == start)
            {
                return;
            }

            i++;

        }
    }

    int getCollissions()
    {
        return collisions;
    }

    int getHits()
    {
        return hits;
    }

    double averageHits(double srch)
    {
        double d = (double) hits;

        return d/srch;
    }
};

class HashTableCustomProbing1
{
    HashNode * table;
    int * status;
    int size;
    int collisions, hits;

public:

    HashTableCustomProbing1(int s)
    {
        size = s;
        table = new HashNode[size];
        status = new int[size];

        for(int i=0;i<size;i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = hits = 0;
    }

    void insert(string k, int v)
    {
        int i = 0, index;
        int start = hash1(k, size);

        while(1)
        {
            index = (hash1(k, size) + c1*i*auxHash(k, size) + c2*i*i) % size;

            if(status[index] == 1) collisions++;

            else
            {
                table[index].key = k;
                table[index].value = v;
                status[index] = 1;

                return;
            }

            if(i>0 && index == start)
            {
                    return;
            }

            i++;

        }

        table[index].key = k;
        table[index].value = v;
        status[index] = 1;
    }

    int search(string k)
    {
        int i = 0, index;
        int start = hash1(k, size);

        hits++;

        while(1)
        {
            index = (hash1(k, size) + c1*i*auxHash(k, size) + c2*i*i) % size;

            if(table[index].key.compare(k) != 0) hits++;

            else
            {
                return table[index].value;
            }

            if(i>0 && index == start)
            {
                return -INF;
            }

            i++;

        }

    }

    void Delete(string k)
    {
        int i = 0, index;
        int start = hash1(k, size);

        while(1)
        {
            index = (hash1(k, size) + c1*i*auxHash(k, size) + c2*i*i) % size;

            if(table[index].key.compare(k) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;
            }

            if(i>0 && index == start)
            {
                return;
            }

            i++;

        }
    }

    int getCollissions()
    {
        return collisions;
    }

    int getHits()
    {
        return hits;
    }

    double averageHits(double srch)
    {
        double d = (double) hits;

        return d/srch;
    }
};

class HashTableCustomProbing2
{
    HashNode * table;
    int * status;
    int size;
    int collisions, hits;

public:

    HashTableCustomProbing2(int s)
    {
        size = s;
        table = new HashNode[size];
        status = new int[size];

        for(int i=0;i<size;i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = hits = 0;
    }

    void insert(string k, int v)
    {
        int i = 0, index;
        int start = hash2(k, size);

        while(1)
        {
            index = (hash2(k, size) + c1*i*auxHash(k, size) + c2*i*i) % size;

            if(status[index] == 1) collisions++;

            else
            {
                table[index].key = k;
                table[index].value = v;
                status[index] = 1;

                return;
            }

            if(i>0 && index == start)
            {
                    return;
            }

            i++;

        }

        table[index].key = k;
        table[index].value = v;
        status[index] = 1;
    }

    int search(string k)
    {
        int i = 0, index;
        int start = hash2(k, size);

        hits++;

        while(1)
        {
            index = (hash2(k, size) + c1*i*auxHash(k, size) + c2*i*i) % size;

            if(table[index].key.compare(k) != 0) hits++;

            else
            {
                return table[index].value;
            }

            if(i>0 && index == start)
            {
                return -INF;
            }

            i++;

        }

    }

    void Delete(string k)
    {
        int i = 0, index;
        int start = hash2(k, size);

        while(1)
        {
            index = (hash2(k, size) + c1*i*auxHash(k, size) + c2*i*i) % size;

            if(table[index].key.compare(k) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;
            }

            if(i>0 && index == start)
            {
                return;
            }

            i++;

        }
    }

    int getCollissions()
    {
        return collisions;
    }

    int getHits()
    {
        return hits;
    }

    double averageHits(double srch)
    {
        double d = (double) hits;

        return d/srch;
    }
};


int main()
{
    int size;

    //size = 10000;
    cin>>size;

    HashTableChaining1 HTC1(size);
    HashTableChaining2 HTC2(size);
    HashTableDoublehashing1 HTD1(size);
    HashTableDoublehashing2 HTD2(size);
    HashTableCustomProbing1 HTCP1(size);
    HashTableCustomProbing2 HTCP2(size);
    //HashTableDoublehashing2 HT(10000);
    //HashTableCustomProbing2 HT(10000);


    string * s;

    s = RandomGenerator();

    for(int i=0;i<10000;i++)
    {
        //cout<<s[i]<<endl;
        HTC1.insert(s[i], i+1);
        HTC2.insert(s[i], i+1);
        HTD1.insert(s[i], i+1);
        HTD2.insert(s[i], i+1);
        HTCP1.insert(s[i], i+1);
        HTCP2.insert(s[i], i+1);

    }

    int count = 0;

    while(count<1000)
    {
        int i = rand() % 10000;

        HTC1.search(s[i]);
        HTC2.search(s[i]);
        HTD1.search(s[i]);
        HTD2.search(s[i]);
        HTCP1.search(s[i]);
        HTCP2.search(s[i]);

        count++;
    }



    cout<<"                                Hash1                                       Hash2\n\n";

    cout<<"                   Collisions            avg hits              collisions               avg hits\n";

    cout<<"chaining method:     "<<HTC1.getCollissions()<<"                "<<HTC1.averageHits(1000);
    cout<<"                     "<<HTC2.getCollissions()<<"                   "<<HTC2.averageHits(1000)<<endl;

    cout<<"Double Hashing:    "<<HTD1.getCollissions()<<"               "<<HTD1.averageHits(1000);
    cout<<"                  "<<HTD2.getCollissions()<<"                 "<<HTD2.averageHits(1000)<<endl;

    cout<<"Custom probing:    "<<HTCP1.getCollissions()<<"               "<<HTCP1.averageHits(1000);
    cout<<"                  "<<HTCP2.getCollissions()<<"                 "<<HTCP2.averageHits(1000)<<endl;

    return 0;
}
