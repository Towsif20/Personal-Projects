#include<iostream>

using namespace std;

void swap(int & a, int & b)
{
    int t = a;
    a = b;
    b = t;
}

class MaxHeap
{
    int capacity;
    int * arr;
    int len;

public:

    int* getArr(){ return arr; }

    int getItem(int i){ return arr[i]; }

    int leftChildIndex(int i)
    {
        return 2*i + 1;
    }

    int rightChildIndex(int i)
    {
        return 2*i + 2;
    }

    int parentIndex(int i)
    {
        return (i - 1) / 2;
    }

    bool hasLeftChild(int i)
    {
        return leftChildIndex(i) < len;
    }

    bool hasRightChild(int i)
    {
        return rightChildIndex(i) < len;
    }

    bool hasParent(int i)
    {
        return parentIndex(i) >= 0;
    }

    int leftChild(int i)
    {
        if(hasLeftChild(i)) return arr[2*i + 1];

        else return INT_MAX;
    }

    int rightChild(int i)
    {
        if(hasRightChild(i)) return arr[2*i + 2];

        else return INT_MAX;
    }

    int parent(int i)
    {
       if(hasParent(i)) return arr[(i-1)/2];
    }
    MaxHeap(int cap);
    int findMaxItem();
    void insert(int item);
    int extractMax();
    void deleteMax();
    void replace(int item);
    void heapify(int * elem, int length);
    int size();
    bool isEmpty();
    void decreaseKey(int old, int val);
    void increaseKey(int old, int val);
    void deleteItem(int item);
    void siftUp(int);
    void siftDown(int);
    void print();
    ~MaxHeap();

};

MaxHeap::MaxHeap(int cap)
{
    capacity = cap;
    len = 0;
    arr = new int[capacity];
}

int MaxHeap::size()
{
    return len;
}

bool MaxHeap::isEmpty()
{
    return len == 0;
}

int MaxHeap::findMaxItem()
{
    if(len == 0) return INT_MAX;

    return arr[0];
}

void MaxHeap::siftDown(int i)
{
  int left = leftChildIndex(i);
  int right = rightChildIndex(i);

  int largest = i;

  if(left<len && arr[left] > arr[largest])
    largest = left;

  if(right<len && arr[right] > arr[largest])
    largest = right;

  if(largest != i)
  {
      swap(arr[largest], arr[i]);
      siftDown(largest);
  }
}

void MaxHeap::siftUp(int i)
{
    if(i && arr[parentIndex(i)] < arr[i])
    {
        swap(arr[i], arr[parentIndex(i)]);

        siftUp(parentIndex(i));
    }
}

void MaxHeap::insert(int item)
{
    if(len == capacity) return;

    arr[len] = item;
    len++;
    int index = len-1;

    siftUp(index);
}

int MaxHeap::extractMax()
{
    if(len == 0) return INT_MIN;

    int t = arr[0];
    deleteMax();

    return t;
}

void MaxHeap::deleteMax()
{
    if(len == 0) return;

    arr[0] = arr[len-1];
    len--;

    siftDown(0);
}

void MaxHeap::replace(int item)
{
    extractMax();

    insert(item);
}

void MaxHeap::heapify(int * elem, int length)
{
    if(length > capacity) return;

    for(int i=0;i<length;i++)
    {
        arr[i] = elem[i];
        len++;

        siftUp(len - 1);
    }
}



void MaxHeap::deleteItem(int item)
{
    int t = -1;
    for(int i=0;i<len;i++)
    {
        if(arr[i] == item)
        {
            t = i;
            break;
        }
    }

    if(t == -1) return;

    arr[t] = arr[len-1];

    len--;

    siftDown(0);

}

void MaxHeap::decreaseKey(int old, int val)
{
    int index = -1;
    for(int i=0;i<len;i++)
    {
        if(arr[i] == old)
        {
            index = i;
        }
    }

    if(index != -1)
    {
        arr[index] = val;
        siftDown(index);
    }
}

void MaxHeap::increaseKey(int old, int val)
{
    int index = -1;
    for(int i=0;i<len;i++)
    {
        if(arr[i] == old)
        {
            index = i;
        }
    }

    if(index != -1)
    {
        arr[index] = val;
        siftUp(index);
    }
}

void MaxHeap::print()
{
    for(int i=0;i<len;i++)
    {
        cout<<arr[i]<<" ";
        //if(isPower(i+1)) cout<<"\n";                //to show each level differently
    }
    cout<<"\n";
}

MaxHeap::~MaxHeap()
{
    len = 0;
    delete[] arr;
}

MaxHeap* merge(MaxHeap * m1, MaxHeap * m2);
MaxHeap* meld(MaxHeap* m1, MaxHeap * m2);

MaxHeap* merge(MaxHeap * m1, MaxHeap * m2)
{
    int len1 = m1->size();
    int len2 = m2->size();

    MaxHeap * m = new MaxHeap(len1 + len2);

    for(int i=0;i<len1;i++)
    {
        m->insert(m1->getItem(i));
    }

    for(int i=0;i<len2;i++)
    {
        m->insert(m2->getItem(i));
    }

    return m;
}

MaxHeap* meld(MaxHeap * m1, MaxHeap * m2)
{
    MaxHeap * t = merge(m1, m2);

    delete m1;
    delete m2;

    return t;
}

int main()
{
    int n;
    cin>>n;
    int * arr;
    arr = new int[n];
    int * arr2 = new int[5];

    MaxHeap *m = new MaxHeap(100);
    MaxHeap *m2 = new MaxHeap(100);

    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
        //m.insert(arr[i]);
    }

    for(int i=0;i<5;i++)
    {
        cin>>arr2[i];
    }

    m->heapify(arr, n);
    m2->heapify(arr2, 5);
    m->print();
    m->deleteItem(4);
    //m.siftDown(0);
    //m.siftUp(n-1);
    m->print();

    MaxHeap * m3 = merge(m, m2);

    m3->print();
    m->print();
    m2->print();

    m3->decreaseKey(5, 0);
    m3->print();

    m3->increaseKey(6, 10);
    m3->print();

    m3 = meld(m, m2);

    m3->print();
    m->print();
    m2->print();

    return 0;
}

