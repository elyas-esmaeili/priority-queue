/*
* CS 106X Priority Queue
* a PQ implementation using a heap as internal storage
*
* Author : Elyas Esmaeili
*/

#ifndef _heappriorityqueue_h
#define _heappriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
using namespace std;

/*
 * For documentation of each member, see VectorPriorityQueue.h.
 */
class HeapPriorityQueue {
public:
    HeapPriorityQueue();
    ~HeapPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const HeapPriorityQueue& queue);

private:
	bool checkIndex(int index) const;
	void resize();

private:
	PQEntry* heapArray;
	int mySize;
    int myCapacity;
};

#endif
