/*
* CS 106X Priority Queue
* a PQ implementation using a heap as internal storage
*
* Author : Elyas Esmaeili
*/


#include "HeapPriorityQueue.h"

HeapPriorityQueue::HeapPriorityQueue() {
	mySize = 0;
	myCapacity = 10;
	heapArray = new PQEntry[myCapacity];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] heapArray;
}

void HeapPriorityQueue::changePriority(string value, int newPriority) {
	int i = 0;
	for (i = 0; i < mySize; i++) {
		if (heapArray[i].value == value) {
			if (heapArray[i].priority < newPriority) {
				throw("This Element already has more urgent priority!");
			}

			if (i == 0) {
				heapArray[i].priority = newPriority;
			}
			else {
				swap(heapArray[i], heapArray[mySize - 1]);
				mySize--;
				enqueue(value, newPriority);
			}
			break;
		}
	}
	if (i == mySize) {
		throw("Value NOT FOUND!");
	}
}

void HeapPriorityQueue::clear() {
	mySize = 0;
}

string HeapPriorityQueue::dequeue() {
    if (isEmpty()) {
        throw("The Priority Queue is Empty!");
    }

	string value = heapArray[0].value;

    heapArray[0] = heapArray[mySize - 1];
	mySize--;

	int index, minChildIndex;
	index = minChildIndex = 0;

    while(1) {
        if (checkIndex(2 * index + 2)) {
            if (heapArray[2 * index + 2] < heapArray[2 * index + 1]) {
                minChildIndex = 2 * index + 2;
            }
            else {
                minChildIndex = 2 * index + 1;
            }
        }

        else if (checkIndex(2 * index + 1)) {
            minChildIndex = 2 * index + 1;
        }

        if (heapArray[minChildIndex] < heapArray[index]) {
            swap(heapArray[minChildIndex], heapArray[index]);
			index = minChildIndex;
        }
		else {
			break;
		}
    }
	return value;
}

void HeapPriorityQueue::enqueue(string value, int priority) {
	int index = mySize;
	if (myCapacity == mySize) {
        resize();
	}
	
	heapArray[index] = PQEntry(value, priority);
    mySize++;

    while (checkIndex((index - 1) / 2) &&
        heapArray[index] < heapArray[(index - 1) / 2]) {
        swap(heapArray[index], heapArray[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

bool HeapPriorityQueue::isEmpty() const {
	return mySize == 0;
}

string HeapPriorityQueue::peek() const {
    if (isEmpty()) {
        throw("The Priority Queue is Empty!");
    }

    return heapArray[0].value;
}

int HeapPriorityQueue::peekPriority() const {
    if (isEmpty()) {
        throw("The Priority Queue is Empty!");
    }

    return heapArray[0].priority;
}

int HeapPriorityQueue::size() const {
	return mySize;
}

bool HeapPriorityQueue::checkIndex(int index) const
{
    return (index >= 0 && index < mySize);
}

void HeapPriorityQueue::resize()
{
	PQEntry* bigger = new PQEntry[myCapacity * 2];
	for (int i = 0; i < mySize; i++) {
		bigger[i] = heapArray[i];
	}
	
	delete[] heapArray;
	heapArray = bigger;
	myCapacity *= 2;
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
	out << "{";
	if (!queue.isEmpty()) {
		cout << queue.heapArray[0];
		for (int i = 1; i < queue.mySize; i++) {
			cout << ", " << queue.heapArray[i];
		}
	}
	out << "}";

    return out;
}
