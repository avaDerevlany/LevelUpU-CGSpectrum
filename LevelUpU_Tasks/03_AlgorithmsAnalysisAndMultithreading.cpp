// 03_AlgorithmsAnalysisAndMultithreading.cpp : Contains the main function for the third set of challenges.

#include <iostream>
#include "03_AlgorithmsAnalysisAndMultithreading\Section3Header.h"

using namespace std;

#if 0
int main()
{
    // Ch 1
    // Problem 1
    int array1[7] = {20, 10, 5, 30, 35,  0, 50};
    int array2[21] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
    int array3[2] = {100, 2};
    int array4[100];
    for (int i = 0; i < 100; i++)
    {
        array4[i] = rand();
    }
    
    uint32_t startNanos = GetNanos();
    BubbleSort(array1, 7);
    uint32_t endNanos = GetNanos();
    cout << "Bubble sort took: " << (endNanos - startNanos) << "ns to sort Array1 " << ArrayToString(array1, 7) << endl;
    
    startNanos = GetNanos();
    BubbleSort(array2, 21);
    endNanos = GetNanos();
    cout << "Bubble sort took: " << (endNanos - startNanos) << "ns to sort Array2 " << ArrayToString(array2, 21) << endl;

    startNanos = GetNanos();
    BubbleSort(array3, 2);
    endNanos = GetNanos();
    cout << "Bubble sort took: " << (endNanos - startNanos) << "ns to sort Array3 " << ArrayToString(array3, 2) << endl;

    startNanos = GetNanos();
    BubbleSort(array4, 100);
    endNanos = GetNanos();
    cout << "Bubble sort took: " << (endNanos - startNanos) << "ns to sort Array4 " << ArrayToString(array4, 100) << endl;

    std::cout << "\n------------------------------\n" << std::endl;

    // Problem 2 + 3
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");

    Traversal ab(&b, 5);
    Traversal bc(&c, 1);
    Traversal ad(&d, 7);
    Traversal cd(&d, 2);

    a.connections.push_back(ab);
    a.connections.push_back(ad);
    b.connections.push_back(bc);
    c.connections.push_back(cd);

    MapTraversal(a, d);     // (a, d)  cost:7
    MapTraversal(b, a);     // no path

    Node t("t");
    Node u("u");
    Node v("v");
    Node w("w");
    Node x("x");
    Node y("y");
    Node z("z");

    Traversal xz(&z, 3);
    Traversal zy(&y, 2);
    Traversal ty(&y, 1);
    Traversal yw(&w, 1);
    Traversal yv(&v, 8);
    Traversal zv(&v, 20);

    t.connections.push_back(ty);
    x.connections.push_back(xz);
    y.connections.push_back(yw);
    y.connections.push_back(yv);
    z.connections.push_back(zy);
    z.connections.push_back(zv);

    MapTraversal(x, v);     // (x, z, y, v)  cost:13
    MapTraversal(t, v);     // (t, y, v)  cost: 9
    MapTraversal(t, x);     // no path

    std::cout << "\n------------------------------\n" << std::endl;

    // Ch 3
    HelloWorldExample();
}
#endif