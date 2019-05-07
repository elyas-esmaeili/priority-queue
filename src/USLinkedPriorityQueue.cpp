/*
* CS 106X Priority Queue
* a PQ implementation using a unsorted linked list as internal storage
*
* Author : Elyas Esmaeili
*/


#include "USLinkedPriorityQueue.h"

USLinkedPriorityQueue::USLinkedPriorityQueue() {
    front = NULL;
}

USLinkedPriorityQueue::~USLinkedPriorityQueue() {
	clear();
}

void USLinkedPriorityQueue::changePriority(string value, int newPriority) {
	ListNode* current = front;

	while (current != NULL && current->value != value) {
		current = current->next;
	}

	if (current == NULL) {
		throw("Value Not Found!");
	}
	else if (current->priority < newPriority) {
        throw("This Value already is more urgent!");
	}
	current->priority = newPriority;
}

void USLinkedPriorityQueue::clear() {

	while (front != NULL) {
        ListNode* next = front->next;
		delete front;
		front = next;
	}
}

string USLinkedPriorityQueue::dequeue() {
	if (front == NULL) {
		throw("There is no element to be dequeued!");
	}

	ListNode* urgent, *current;
	current = urgent = front;
    ListNode* previous = NULL;

	while (current->next != NULL) {
		if (current->next->priority < urgent->priority) {
			urgent = current->next;
			previous = current;
		}
		current = current->next;
	}

	if (previous == NULL) {
		front = urgent->next;
	}
	else {
		previous->next = urgent->next;
	}

	string value = urgent->value;
	delete urgent;

	return value;
}

void USLinkedPriorityQueue::enqueue(string value, int priority) {
	front = new ListNode(value, priority, front);
}

bool USLinkedPriorityQueue::isEmpty() const {
	return front == NULL;
}

string USLinkedPriorityQueue::peek() const {
	if (front == NULL) {
        throw("The Priority Queue is Empty!");
	}
	
	ListNode *urgent = findMostUrgent();
	return urgent->value;
}

int USLinkedPriorityQueue::peekPriority() const {
	if (front == NULL) {
        throw("The Priority Queue is Empty!");
	}

	ListNode* urgent = findMostUrgent();	
	return urgent->priority;
}

int USLinkedPriorityQueue::size() const {
	int len = 0;
	ListNode* current = front;

	while (current != NULL) {
		len++;
		current = current->next;
	}
	return len;
}

ListNode* USLinkedPriorityQueue::findMostUrgent() const {
	ListNode* urgent = front;
	ListNode* current = front;

	while (current != NULL) {
		if (current->priority < urgent->priority) {
			urgent = current;
		}
		current = current->next;
	}

	return urgent;
}

ostream& operator<<(ostream& out, const USLinkedPriorityQueue& queue) {
    ListNode* current = queue.front;
	out << "{";
    if (current != NULL) {
        out << *current;
        while (current->next != NULL) {
            current = current->next;
            out << ", " << *current;
        }
    }
    out << "}";
    return out;
}
