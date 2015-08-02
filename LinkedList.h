/*
Copyright 2015 Jeff Hamm <jeff.hamm@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// a simple singly-linked-list with dynamic memory allocation (careful!)
template<typename T>
class LinkedListNode
{
public:
	LinkedListNode * next;
	T * value;

	LinkedListNode(T * firstItem);
	~LinkedListNode();
	// clears the list and frees any dynamically allocated items.
	void deleteRest();
	// adds a new item to this list and returns the item's node
	LinkedListNode * add(T * item);
	// Note: be sure to use the re-assigned node pointer after this 
	// method, as your original pointer may be invalid
	LinkedListNode<T> * remove(T * item);
	// determines if a sequence with the specified range already exists
	bool contains(T * item);
	// gets the current node for the specified value
	LinkedListNode * getNode(T * section);

protected:
	bool dynamic;
};


template<typename T>
LinkedListNode<T>::LinkedListNode(T * thisValue) : next(NULL), value(thisValue), dynamic(false)
{

}

template<typename T>
LinkedListNode<T>::~LinkedListNode()
{
	if (dynamic)
		delete this;
}

template<typename T>
void LinkedListNode<T>::deleteRest()
{
	// delete backwards down the list
	if (next) {
		deleteRest();
		if (next->dynamic)
			delete next;
	}
}

template<typename T>
LinkedListNode<T> * LinkedListNode<T>::add(T * item)
{
	if (!next) {
		this->next = new LinkedListNode<T>(item);
		this->next->dynamic = true;
		return this->next;
	}
	else {
		return this->next->add(item);
	}
}

// removes a range from the list, returns the modified list.

template<typename T>
LinkedListNode<T> * LinkedListNode<T>::remove(T * item) {
	if (this->value == item) {
		LinkedListNode<T> * saved = this->next;
		if (this->dynamic)
			delete this;
		return saved;
	}
	// recur
	else if (this->next) {
		this->next = this->next->remove(item);
	}
	// end of list, didn't find it to remove
	else {
		return this;
	}
}

template<typename T>
LinkedListNode<T> * LinkedListNode<T>::getNode(T * item)
{
	if (this->value == item) {
		return this;
	}
	else if (this->next) {
		return this->next->getNode(item);
	}
	else
		return NULL;
}

template<typename T>
bool LinkedListNode<T>::contains(T * item) {
	return getNode(item) != NULL;
}
#endif