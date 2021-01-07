#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct Point
{
    int x, y;
};

struct pointSet
{
    Point p1;
    Point p2;
    float dis;
};

int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

pointSet directMethod(Point P[], int n)
{
    float min = FLT_MAX;
    pointSet ps;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (dist(P[i], P[j]) < min)
                {
                    min = dist(P[i], P[j]);
                    ps.dis = min;
                    ps.p1 = P[i];
                    ps.p2 = P[j];
                }
    return ps;
}

float min(float x, float y)
{
    return (x < y)? x : y;
}

pointSet bounded(Point strip[], int size, pointSet p)
{
    float min = p.dis;
    pointSet ps = p;

    qsort(strip, size, sizeof(Point), compareY);

    for (int i = 0; i < size; i++)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; j++)
            if (dist(strip[i],strip[j]) < min)
            {
                min = dist(strip[i], strip[j]);
                ps.dis = min;
                ps.p1 = strip[i];
                ps.p2 = strip[j];
                printf("\n%d\n",ps.p1.x);
            }

    return ps;
}

pointSet closestUtil(Point P[], int n)
{
    if (n <= 3)
        return directMethod(P, n);

    int mid = n/2;
    Point midPoint = P[mid];

    pointSet dl = closestUtil(P, mid);
    pointSet dr = closestUtil(P + mid, n-mid);

    float d = min(dl.dis, dr.dis);
    pointSet temp;
    if(dl.dis == d) temp = dl;
    else temp = dr;

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;

    pointSet ps = bounded(strip, j, temp);
    float m = min(d, ps.dis );
    ps.dis = m;

    return ps;
}

pointSet closestPair(Point P[], int n)
{
    qsort(P, n, sizeof(Point), compareX);

    return closestUtil(P, n);
}

int main()
{
    /*
    Point * P;
    int size;
    scanf("%d",&size);
    P = new Point[size];

    int x,y;
    for(int i=0;i<size;i++)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        P[i] = {x,y};
    }

    for(int i=0;i<size;i++)
    {
        printf("%d ",P[i].x);
        printf("%d \n",P[i].y);
    }
    */
    Point P[] = {{0,0}, {-4,1},{-7,-2},{4,5},{1,1}};
    int n = sizeof(P) / sizeof(P[0]);
    pointSet ps = closestPair(P, n);
    printf("%d %d\n%d %d\n",ps.p1.x,ps.p1.y,ps.p2.x,ps.p2.y);
    printf("%f\n ", ps.dis);
    return 0;
}
