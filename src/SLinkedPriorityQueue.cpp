/*
* CS 106X Priority Queue
* a PQ implementation using a sorted linked list as internal storage
*
* Author : Elyas Esmaeili
*/


#include "SLinkedPriorityQueue.h"

SLinkedPriorityQueue::SLinkedPriorityQueue() {
	
	front = NULL;
}

SLinkedPriorityQueue::~SLinkedPriorityQueue() {
	
	clear();	
}

void SLinkedPriorityQueue::changePriority(string value, int newPriority) {
	
	ListNode* current = front;
	ListNode * previous = NULL;

	while (current != NULL && current->value != value) {
		previous = current;
		current = current->next;
	}

	if (current == NULL) {
		throw("Value Not Found!");
	}
	else if (current->priority < newPriority) {
		throw("This Value already is more urgent!");
	}

	if (previous != NULL) {
		previous->next = current->next;
		delete current;
		enqueue(value, newPriority);
	}
	else {
		current->priority = newPriority;
	}
}

void SLinkedPriorityQueue::clear() {
	
	while (front != NULL) {
		ListNode* next = front->next;
		delete front;
		front = next;
	}
}

string SLinkedPriorityQueue::dequeue() {
	
	ListNode* urgent = front;
	front = front->next;

	string value = urgent->value;
	delete urgent;

	return value;
}

void SLinkedPriorityQueue::enqueue(string value, int priority) {
	
	ListNode* current = front;
	ListNode* previous = NULL;

	while (current != NULL && priority >= current->priority) {
		previous = current;
		current = current->next;
	}
	if (previous == NULL) {
		front = new ListNode(value, priority, front);
	}
	else {
		previous->next = new ListNode(value, priority, current);
	}
}

bool SLinkedPriorityQueue::isEmpty() const {
	
	return front == NULL;
}

string SLinkedPriorityQueue::peek() const {
	
	if (front == NULL) {
		throw("The Priority Queue is Empty!");
	}

	return front->value;
}

int SLinkedPriorityQueue::peekPriority() const {
	
	if (front == NULL) {
		throw("The Priority Queue is Empty!");
	}

	return front->priority;
}

int SLinkedPriorityQueue::size() const {
	
	int len = 0;
	ListNode* current = front;

	while (current != NULL) {
		len++;
		current = current->next;
	}
	return len;
}

ostream& operator<<(ostream& out, const SLinkedPriorityQueue& queue) {
	
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