/**Name: Xuechun Cao - 100271794
 **course: CPSC 2150 - 001
 **Asign 2
 ** This program is used to create a doubly linked list
*/
#include <iostream>
#include <stdexcept>
#include "Room.h"
#include "Customer.h"

using namespace std;
#ifndef DLL_H
#define DLL_H
//Node class
template<typename T>
class Node {
	public:
		T info;
		Node<T>* next;
		Node<T>* prev;
		//nonparameter constructor
		Node(){
			next = nullptr;
			prev = nullptr;
		}
		//constuctor with parameter
		Node(T element){
			info = element;
			next = nullptr;
			prev = nullptr;
		}
};
//iterator class
template<typename T>
class Iterator{
	private:
		Node<T>* current;
	public:
		//constructor
		Iterator(Node<T>* p){
			current = p;
		}
		//get next iterator
		Iterator next(){
			current = current->next;
			return *this;
		}
		//get the content of the iterator
		T& content(){
			return current->info;
		}
		//check whether the two iterators are the same
		bool isEqual(const Iterator<T>& iterator){
			return current == iterator.current;
		}
};
template<typename T>
class DLL{
	friend class Iterator<T>;
	public:
		Node<T>* head;
		Node<T>* tail;
		int size;
		//constructor
		DLL();
		//copy constructor
		DLL(const DLL<T>& list);
		//destructor
		~DLL();
		//get the size of the list
		int getSize() const;
		//add a new node at the front of the list
		void addFirst(T element);
		//add a new node at the end of the list
		void addLast(T element);
		//remove the first node
		T removeFirst() throw (runtime_error);
		//get information at the specific index
		T get(int index) const;
		//check empty
		bool isEmpty();
		//get the iterator for the head
		Iterator<T> begin() const;
		//get the iterator for tail-> next
		Iterator<T> end() const;
};
#endif
template<typename T>
DLL<T>::DLL(){
	head = tail = nullptr;
	size = 0;
}
template<typename T>
DLL<T>::DLL(const DLL<T>& list){
	head = tail = nullptr;
	size = 0;
	for(int i = 0; i < list.getSize(); i ++){
		this->addLast(list.get(i));
	}
}
template<typename T>
DLL<T>::~DLL(){
	while (head != nullptr){
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	size = 0;
}
template<typename T>
bool DLL<T>::isEmpty(){
	if(size == 0){
		return true;
	}
	return false;
}
template<typename T>
int DLL<T>::getSize() const{
	return size;
}
template<typename T>
void DLL<T>::addFirst(T element){
	Node<T>* newNode = new Node<T>(element);
	if(size == 0){
		head = tail = newNode;
		size ++;
	}
	else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		size ++;
	}
}
template<typename T>
void DLL<T>::addLast(T element){
	Node<T>* newNode = new Node<T>(element);
	if(size == 0){
		head = tail = newNode;
		size ++;
	}
	else{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		size ++;
	}
}
template<typename T>
T DLL<T>::removeFirst() throw (runtime_error){
	if(size == 0){
		throw runtime_error("No elements in the list");
	}
	else{
		Node<T>* tmp = head;
		head = head->next;
		if(head == nullptr){
			tail = nullptr;
		}
		else{
			head->prev = nullptr;
		}
		size --;
		T element = tmp->info;
		delete tmp;
		return element;
	}
}
template<typename T>
T DLL<T>::get(int index) const{
	if (index < 0 || index >= size){
		throw runtime_error("Index out of range");
	}
	Node<T>* current = head;
	for(int i = 0; i < index; i ++){
		current = current->next;
	}
	return current->info;
}
template<typename T>
Iterator<T> DLL<T>::begin() const{
	return Iterator<T>(head);
}
template<typename T>
Iterator<T> DLL<T>::end() const{
	return Iterator<T>(tail->next);
}