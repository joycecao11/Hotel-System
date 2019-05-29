/**Name: Xuechun Cao - 100271794
 **course: CPSC 2150 - 001
 **Asign 2
 ** This program is used to create a priority queue
*/
#include <iostream>
#include <stdexcept>
#include "Room.h"
#include "DLL.h"
using namespace std;
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
class PriorityQueue{
	//data field
	private:
		DLL<Room> list;
	public:
		//constructor with no argument
		PriorityQueue();
		//add room in order
		void enqueue(Room r);
		//remove the first room
		Room dequeue();
		//get the first room
		Room front();
		//get size
		int getSize();
		//check whether the queue is empty
		bool isEmpty();
		//static function to check which day is earlier
		static bool isEarlier(int minY, int minM, int minD, int year, int mon, int day);
};
PriorityQueue::PriorityQueue(){
	
}
bool PriorityQueue::isEarlier(int minY, int minM, int minD, int year, int mon, int day){
	if(minY > year){
		return true;
	}
	else if(minY == year){
		if(minM > mon){
			return true;
		}
		else if(minM == mon){
			if(minD >= day){
				return true;
			}
		}
	}
	return false;
}
void PriorityQueue::enqueue(Room r){
	if(list.size == 0){
		list.addLast(r);
		//cout << "add last 1" << endl;
	}
	else{
		Node<Room>* temp = list.head;
		Node<Room>* newNode = new Node<Room>(r);
		bool add = false;
		int year = r.getCOY();
		int mon = r.getCOM();
		int day = r.getCOD();
		for(int i = 0; i < list.size; i ++){
			int tempY = temp->info.getCOY();
			int tempM = temp->info.getCOM();
			int tempD = temp->info.getCOD();
			if(isEarlier(tempY, tempM, tempD, year, mon, day)){
				if(i == 0){
					list.addFirst(r);
					//cout << "add first" << endl;
					add = true;
					break;
				}
				else{
					temp->prev->next = newNode;
					newNode->prev = temp->prev;
					temp->prev = newNode;
					newNode->next = temp;
					add = true;
					list.size ++;
					//cout << "add " << endl;
					break;
				}
			}
		}
		if(!add){
			list.addLast(r);
			//cout << "add last 2" << endl;
		}
	}
}
Room PriorityQueue::dequeue(){
	return list.removeFirst();
}
Room PriorityQueue::front(){
	return list.get(0);
}
int PriorityQueue::getSize(){
	return list.getSize();
}
#endif