/**Name: Xuechun Cao - 100271794
 **course: CPSC 2150 - 001
 **Asign 2
 ** This program is used to arrange customers in a hotel
*/
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Room.h"
//#include "Customer.h"
//#include "DLL.h"
#include "PriorityQueue.h"
using namespace std;
int getCheckInDay(string newCheckInDate);
int getCheckInMonth(string newCheckInDate);
int getCheckInYear(string newCheckInDate);
int getDayNumOfMonth(int month);
string getRidOfComma(string temp);
int getNumber(string s);
/*generate number by givin a string
 * @input s the string
 * @return nothing
*/
int getNumber(string s){
	int i;
	stringstream ss;
	ss << s;
	ss >> i;
	return i;
}
/*generate string without comma as the last character
 * @input temp the string
 * @return string
*/
string getRidOfComma(string temp){
	string real = "";
	for(int i = 0; i < temp.length()-1; i ++){
		real += temp[i];
	}
	return real;
}
/*get check in day of the customer based on the string of infomation in txt file
 * @input newCheckInDate the string
 * @return int
*/
int getCheckInDay(string newCheckInDate){
	int indexOfFirstDash = newCheckInDate.find('/');
	string dayS = "";
	for(int i = 0; i < indexOfFirstDash; i ++){
		dayS += newCheckInDate[i];
	}
	stringstream s1;
	s1 << dayS;
	int dayInt;
	s1 >> dayInt;
	return dayInt;
}
/*get check in month of the customer based on the string of infomation in txt file
 * @input newCheckInDate the string
 * @return int
*/
int getCheckInMonth(string newCheckInDate){
	int indexOfFirstDash = newCheckInDate.find('/');
	string subMY = newCheckInDate.substr(indexOfFirstDash+1);
	int indexOfSecDash = subMY.find('/');
	string monS = "";
	for(int i = 0; i < indexOfSecDash; i ++){
		monS += subMY[i];
	}
	stringstream s1;
	s1 << monS;
	int monInt;
	s1 >> monInt;
	return monInt;
}
/*get check in year of the customer based on the string of infomation in txt file
 * @input newCheckInDate the string
 * @return int
*/
int getCheckInYear(string newCheckInDate){
	int indexOfFirstDash = newCheckInDate.find('/');
	string subMY = newCheckInDate.substr(indexOfFirstDash+1);
	int indexOfSecDash = subMY.find('/');
	string subY = subMY.substr(indexOfSecDash+1);
	stringstream s1;
	s1 << subY;
	int yearInt;
	s1 >> yearInt;
	return yearInt;
}
/*get day number based on the month number
 * @input month the month number
 * @return int
*/
int getDayNumOfMonth(int month){
	if(month==2){
		return 28;
	}
	else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
		return 31;
	}
	else{
		return 30;
	}
}
/*check whether the room has already been checked out before the next customer check in
 * @input checkInDate the check in date string
 * @input outYear the number of the check out year for the room
 * @input outMonth the number of the check out month for the room
 * @input outDay the number of the check out day for the room
 * @return boolean
*/
bool checkOutBefore(string checkInDate,int outYear,int outMonth,int outDay){
	int inYear = getCheckInYear(checkInDate);
	int inMonth = getCheckInMonth(checkInDate);
	int inDay = getCheckInDay(checkInDate);
	if(inYear > outYear){
		return true;
	}
	else if(inYear == outYear){
		if(inMonth > outMonth){
			return true;
		}
		else if(inMonth == outMonth){
			if(inDay >= outDay){
				return true;
			}
		}	
	}
	return false;	
}
/*to make the rooms that have aleady checked out available
 * @input roomListOne the room list with one bed
 * @input roomListTwo the room list with two bed
 * @input roomListThree the room list with three bed
 * @input checkInDate the check in date of the customer
 * @input count to count comparisons
 * @return nothing
*/
void clearCheckOut(DLL<Room>& roomListOne,DLL<Room>& roomListTwo,DLL<Room>& roomListThree,string checkInDate,int& count){
	//clear first room list
	for(Iterator<Room> itr = roomListOne.begin(); !itr.isEqual(roomListOne.end()); itr.next()){
		if(!itr.content().getAvailability()){
			int cOY = itr.content().getCOY();
			int cOM = itr.content().getCOM();
			int cOD = itr.content().getCOD();
			if(checkOutBefore(checkInDate,cOY,cOM,cOD)){
				itr.content().setAvailable();
			}
		}
		count ++;
	}
	//clear the room list with 2 beds
	for(Iterator<Room> itr = roomListTwo.begin(); !itr.isEqual(roomListTwo.end()); itr.next()){
		if(!itr.content().getAvailability()){
			int cOY = itr.content().getCOY();
			int cOM = itr.content().getCOM();
			int cOD = itr.content().getCOD();
			if(checkOutBefore(checkInDate,cOY,cOM,cOD)){
				itr.content().setAvailable();
			}
		}
		count ++;
	}
	//clear the room list with 3 beds
	for(Iterator<Room> itr = roomListThree.begin(); !itr.isEqual(roomListThree.end()); itr.next()){
		if(!itr.content().getAvailability()){
			int cOY = itr.content().getCOY();
			int cOM = itr.content().getCOM();
			int cOD = itr.content().getCOD();
			if(checkOutBefore(checkInDate,cOY,cOM,cOD)){
				itr.content().setAvailable();
			}
		}
		count ++;
	}
}
/*to check which date is earlier
 * @input minY the year of the first date
 * @input minM the month of the first date
 * @input minD the day of the first date
 * @input year the year of the second date
 * @input mon the month of the second date
 * @input day the day of the second date
 * @return boolean
*/
bool isEarlier(int minY, int minM, int minD, int year, int mon, int day){
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
/*to get the earliest date that customer can check in
 * @input roomListOne the room list with one bed
 * @input roomListTwo the room list with two bed
 * @input roomListThree the room list with three bed
 * @input checkInDate the check in date of the customer
 * @input bedNum the number of bed that customer requested
 * @input count to count comparisons
 * @return nothing
*/
void getEarliestRoom(DLL<Room>& roomListOne,DLL<Room>& roomListTwo,DLL<Room>& roomListThree,string checkInDate,int bedNum,int& count){
	int minY;
	int minM;
	int minD;
	int y;
	int m;
	int d;
	if(bedNum == 1){
		//set the date of the first room to be the minimum
		Iterator<Room> iterator = roomListOne.begin();
		minY = iterator.content().getCOY();
		minM = iterator.content().getCOM();
		minD = iterator.content().getCOD();
		//go through each room and get the earliest one
		for(Iterator<Room> itr = roomListOne.begin(); !itr.isEqual(roomListOne.end()); itr.next()){
			y = itr.content().getCOY();
			m = itr.content().getCOM();
			d = itr.content().getCOD();
			if(isEarlier(minY,minM,minD,y,m,d)){
				minY = y;
				minM = m;
				minD = d;
			}
			count ++;
		}
	}
	else if(bedNum == 2){
		//set the date of the first room to be the minimum
		Iterator<Room> iterator = roomListTwo.begin();
		minY = iterator.content().getCOY();
		minM = iterator.content().getCOM();
		minD = iterator.content().getCOD();
		//go through each room and get the earliest one
		for(Iterator<Room> itr = roomListTwo.begin(); !itr.isEqual(roomListTwo.end()); itr.next()){
			y = itr.content().getCOY();
			m = itr.content().getCOM();
			d = itr.content().getCOD();
			if(isEarlier(minY,minM,minD,y,m,d)){
				minY = y;
				minM = m;
				minD = d;
			}
			count ++;
		}
	}
	else{
		//set the date of the first room to be the minimum
		Iterator<Room> iterator = roomListThree.begin();
		minY = iterator.content().getCOY();
		minM = iterator.content().getCOM();
		minD = iterator.content().getCOD();
		//go through each room and get the earliest one
		for(Iterator<Room> itr = roomListThree.begin(); !itr.isEqual(roomListThree.end()); itr.next()){
			y = itr.content().getCOY();
			m = itr.content().getCOM();
			d = itr.content().getCOD();
			if(isEarlier(minY,minM,minD,y,m,d)){
				minY = y;
				minM = m;
				minD = d;
			}
			count ++;
		}
	}
	cout << "	Come back at " << minY << " " << minM << " " << minD << endl;
}
/*to check whether there is an available room in the hotel
 * @input roomListOne the room list with one bed
 * @input roomListTwo the room list with two bed
 * @input roomListThree the room list with three bed
 * @input bedNum the number of beds that customer requested
 * @input checkInDate the check in date of the customer
 * @input duration  the number of days that customer will stay
 * @input count to count comparisons
 * @return nothing
*/
void checkRoomAvailable(DLL<Room>& roomListOne,DLL<Room>& roomListTwo,DLL<Room>& roomListThree,int bedNum,string checkInDate,int duration, int& count){
	bool getRoom = false;
	//clear up lists first
	clearCheckOut(roomListOne,roomListTwo,roomListThree,checkInDate,count);
	//if the number of beds requested is one, we need to check all three lists
	if(bedNum == 1){
		//go through each room in the list until find an empty one
		for(Iterator<Room> itr = roomListOne.begin(); !itr.isEqual(roomListOne.end()); itr.next()){
			count ++;
			if(itr.content().getAvailability()){
				itr.content().setUnavailable();
				itr.content().bookRoom(checkInDate, duration);
				getRoom = true;
				break;
			}
		}
		if(!getRoom){
		for(Iterator<Room> itr = roomListTwo.begin(); !itr.isEqual(roomListTwo.end()); itr.next()){
			count ++;
			if(itr.content().getAvailability()){
				itr.content().setUnavailable();
				itr.content().bookRoom(checkInDate, duration);
				getRoom = true;
				break;
			}
		}
		}
		if(!getRoom){
		for(Iterator<Room> itr = roomListThree.begin(); !itr.isEqual(roomListThree.end()); itr.next()){
			count ++;
			if(itr.content().getAvailability()){
				itr.content().setUnavailable();
				itr.content().bookRoom(checkInDate, duration);
				getRoom = true;
				break;
			}
		}
		}
	}
	//if th enumber of beds requested is 2, we need to check the room lists with 2 beds and 3 beds
	else if(bedNum == 2){
		//go through each room until we find an empty one
		for(Iterator<Room> itr = roomListTwo.begin(); !itr.isEqual(roomListTwo.end()); itr.next()){
			count ++;
			if(itr.content().getAvailability()){
				itr.content().setUnavailable();
				itr.content().bookRoom(checkInDate, duration);
				getRoom = true;
				break;
			}
		}
		if(!getRoom){
		for(Iterator<Room> itr = roomListThree.begin(); !itr.isEqual(roomListThree.end()); itr.next()){
			count ++;
			if(itr.content().getAvailability()){
				itr.content().setUnavailable();
				itr.content().bookRoom(checkInDate, duration);
				getRoom = true;
				break;
			}
		}
		}
	}
	//if the number of beds requested is 3, we only need to check room list with 3 beds
	else if(bedNum == 3){
		//go through each room until we find an empty one
		for(Iterator<Room> itr = roomListThree.begin(); !itr.isEqual(roomListThree.end()); itr.next()){
			count ++;
			if(itr.content().getAvailability()){
				itr.content().setUnavailable();
				itr.content().bookRoom(checkInDate, duration);
				getRoom = true;
				break;
			}
		}
	}
	if(!getRoom){
		//if we cannot find an available room, we look for the earliest room that has the number of beds that they requested for
		getEarliestRoom(roomListOne,roomListTwo,roomListThree,checkInDate,bedNum,count);
	}
	else{
		cout << "	Check in successfully" << endl;
	}
}
/*Efficient version: to get the earliest date that customer can check in
 * @input unOne the priority queue of unavailable rooms with one bed
 * @input unTwo the priority queue of unavailable rooms with two beds
 * @input unThree the priority queue of unavailable rooms with three beds
 * @input bedNum the number of bed that customer requested
 * @input count to count comparisons
 * @return nothing
*/
void getEarliestRoom_EF(PriorityQueue& unOne, PriorityQueue& unTwo, PriorityQueue& unThree,int bedNum,int& count){
	//whatever the number of beds is, we can simply get the first room in the priority queueas the earliest
	if(bedNum == 1){
		count ++;
		int minY = unOne.front().getCOY();
		int minM = unOne.front().getCOM();
		int minD = unOne.front().getCOD();
		cout << "	Come back at " << minY << " " << minM << " " << minD << endl;
	}
	else if(bedNum == 2){
		count ++;
		int minY = unTwo.front().getCOY();
		int minM = unTwo.front().getCOM();
		int minD = unTwo.front().getCOD();
		cout << "	Come back at " << minY << " " << minM << " " << minD << endl;
	}
	else{
		count ++;
		int minY = unThree.front().getCOY();
		int minM = unThree.front().getCOM();
		int minD = unThree.front().getCOD();
		cout << "	Come back at " << minY << " " << minM << " " << minD << endl;
	}
}
/*Efficient version: to make the rooms that have aleady checked out available
 * @input roomListOne the room list with one bed
 * @input roomListTwo the room list with two bed
 * @input roomListThree the room list with three bed
 * @input unOne the priority queue of unavailable rooms with one bed
 * @input unTwo the priority queue of unavailable rooms with two beds 
 * @input unThree the priority queue of unavailable rooms with three beds 
 * @input checkInDate the check in date of the customer 
 * @input count to count comparisons
 * @return nothing
*/
void clearCheckOut_EF(DLL<Room>& roomListOne,DLL<Room>& roomListTwo,DLL<Room>& roomListThree,PriorityQueue& unOne, PriorityQueue& unTwo, PriorityQueue& unThree,string checkInDate,int& count){
	bool oneOk = false;
	bool twoOk = false;
	bool threeOk = false;
	if(unOne.getSize()!=0){
		//use loop to make every room that checked out available
		while((!oneOk) && (unOne.getSize()!=0)){
			int cOY = unOne.front().getCOY();
			int cOM = unOne.front().getCOM();
			int cOD = unOne.front().getCOD();
			if(checkOutBefore(checkInDate,cOY,cOM,cOD)){
				Room temp = unOne.dequeue();
				temp.setAvailable();
				roomListOne.addLast(temp);
			}
			else{
				oneOk = true;
			}
			count ++;
		}
	}
	if(unTwo.getSize()!=0){
		//use loop to make every room that checked out available
		while((!twoOk) && (unTwo.getSize()!=0)){
			int cOY = unTwo.front().getCOY();
			int cOM = unTwo.front().getCOM();
			int cOD = unTwo.front().getCOD();
			if(checkOutBefore(checkInDate,cOY,cOM,cOD)){
				Room temp = unTwo.dequeue();
				temp.setAvailable();
				roomListTwo.addLast(temp);
			}
			else{
				twoOk = true;
			}
			count ++;
		}
	}
	if(unThree.getSize()!=0){
		//use loop to make every room that checked out available
		while((!threeOk) && (unThree.getSize()!=0)){
			int cOY = unThree.front().getCOY();
			int cOM = unThree.front().getCOM();
			int cOD = unThree.front().getCOD();
			if(checkOutBefore(checkInDate,cOY,cOM,cOD)){
				Room temp = unThree.dequeue();
				temp.setAvailable();
				roomListThree.addLast(temp);
			}
			else{
				threeOk = true;
			}
			count ++;
		}
	}
}
/*Efficient version: to check whether there is an available room in the hotel
 * @input roomListOne the room list with one bed
 * @input roomListTwo the room list with two bed
 * @input roomListThree the room list with three bed
 * @input unOne the priority queue of unavailable rooms with one bed
 * @input unTwo the priority queue of unavailable rooms with two beds 
 * @input unThree the priority queue of unavailable rooms with three beds
 * @input bedNum the number of beds that customer requested
 * @input checkInDate the check in date of the customer
 * @input duration  the number of days that customer will stay
 * @input count to count comparisons
 * @return nothing
*/
void checkRoomAvailable_EF(DLL<Room>& roomListOne,DLL<Room>& roomListTwo,DLL<Room>& roomListThree,PriorityQueue& unOne, PriorityQueue& unTwo, PriorityQueue& unThree, int bedNum,string checkInDate,int duration,int& count){
	bool getRoom = false;
	//clear up queues that store unavailable rooms first
	clearCheckOut_EF(roomListOne,roomListTwo,roomListThree,unOne,unTwo,unThree,checkInDate,count);
	//if the number of beds requested is one, we need to check all three lists
	if(bedNum == 1){
		if(roomListOne.getSize()!=0){
		 	Iterator<Room> itr = roomListOne.begin();
			if(itr.content().getAvailability()){
				Room temp = itr.content();
				temp.setUnavailable();
				temp.bookRoom(checkInDate, duration);
				unOne.enqueue(temp);
				Room r = roomListOne.removeFirst();
				cout << "getRoom in roomlistone" << endl;
				getRoom = true;
				count ++;
			}
		}
		if(!getRoom){
			if(roomListTwo.getSize()!=0){
		 		Iterator<Room> itr = roomListTwo.begin();
				if(itr.content().getAvailability()){
					Room temp = itr.content();
					temp.setUnavailable();
					temp.bookRoom(checkInDate, duration);
					unTwo.enqueue(temp);
					Room r = roomListTwo.removeFirst();
					cout << "getRoom in roomlisttwo" << endl;
					getRoom = true;
					count ++;
				}
			}
		}
		if(!getRoom){
			if(roomListThree.getSize()!=0){
		 		Iterator<Room> itr = roomListThree.begin();
				if(itr.content().getAvailability()){
					Room temp = itr.content();
					temp.setUnavailable();
					temp.bookRoom(checkInDate, duration);
					unThree.enqueue(temp);
					Room r = roomListThree.removeFirst();
					cout << "getRoom in roomlistthree" << endl;
					getRoom = true;
					count ++;
				}
			}
		}
	}
	else if(bedNum == 2){
		if(roomListTwo.getSize()!=0){
	 		Iterator<Room> itr = roomListTwo.begin();
			if(itr.content().getAvailability()){
				Room temp = itr.content();
				temp.setUnavailable();
				temp.bookRoom(checkInDate, duration);
				unTwo.enqueue(temp);
				Room r = roomListTwo.removeFirst();
				cout << "getRoom in roomlisttwo" << endl;
				getRoom = true;
				count ++;
			}
		}
		if(!getRoom){
			if(roomListThree.getSize()!=0){
		 		Iterator<Room> itr = roomListThree.begin();
				if(itr.content().getAvailability()){
					Room temp = itr.content();
					temp.setUnavailable();
					temp.bookRoom(checkInDate, duration);
					unThree.enqueue(temp);
					Room r = roomListThree.removeFirst();
					cout << "getRoom in roomlistthree" << endl;
					getRoom = true;
					count ++;
				}
			}
		}
	}
	else if(bedNum == 3){
		if(roomListThree.getSize()!=0){
	 		Iterator<Room> itr = roomListThree.begin();
			if(itr.content().getAvailability()){
				Room temp = itr.content();
				temp.setUnavailable();
				temp.bookRoom(checkInDate, duration);
				unThree.enqueue(temp);
				Room r = roomListThree.removeFirst();
				cout << "getRoom in roomlistthree" << endl;
				getRoom = true;
				count ++;
			}
		}
	}
	if(!getRoom){
		//if there is no available room, we try to get the earliest date that customer can have the room that has the number of beds they requested for
		getEarliestRoom_EF(unOne,unTwo,unThree,bedNum,count);
	}
	else{
		cout << "	Check in successfully" << endl;
	}
}
int main() {
	//this th eoriginal idea to store the rooms in arrays
	//Room roomListOne[100];
	//Room roomListTwo[50];
	//Room roomListThree[30];
	//in order to be able to extent the size of rooms, i changed it to use linkedList
	DLL<Room> roomListOne;
	DLL<Room> roomListTwo;
	DLL<Room> roomListThree;
	//the priority queue are added for efficient version
	PriorityQueue unavailableOne;
	PriorityQueue unavailableTwo;
	PriorityQueue unavailableThree;
	//initialize the room lists
	for(int i = 0; i < 100; i ++){
		roomListOne.addLast(Room(1));
	}
	for(int i = 0; i < 50; i ++){
		roomListTwo.addLast(Room(2));
	}
	for(int i = 0; i < 30; i ++){
		roomListThree.addLast(Room(3));
	}
	//use vector to store customer infomation
	vector<Customer> listOfCustomer;
	//read file
	ifstream input;
	input.open("test.txt");
	string checkInDate;
	string ID;
	string numOfBed;
	int bedNum;
	int duration;
	int count = 0;
	while(!input.eof()){
		input >> checkInDate;
		input >> ID;
		input >> numOfBed;
		input >> duration;
		checkInDate = getRidOfComma(checkInDate);
		ID = getRidOfComma(ID);
		numOfBed = getRidOfComma(numOfBed);
		bedNum = getNumber(numOfBed);
		cout << checkInDate << " " << ID << " " << bedNum << " " << duration << endl;
		listOfCustomer.push_back(Customer(ID,bedNum,checkInDate,duration));
		//if you want to see unefficient version please uncomment the next line and comment the line after the next line
		//checkRoomAvailable(roomListOne,roomListTwo,roomListThree,bedNum,checkInDate,duration,count);
		//the line below is the efficient version
	checkRoomAvailable_EF(roomListOne,roomListTwo,roomListThree,unavailableOne,unavailableTwo,unavailableThree,bedNum,checkInDate,duration,count);
	}
	cout << "count: " << count << endl;
	return 0;
}