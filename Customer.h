/**Name: Xuechun Cao - 100271794
 **course: CPSC 2150 - 001
 **Asign 2
 ** This program is used to create a customer object
*/
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer{
	private:
		string ID;
		int numOfBedRequested;
		string checkInDate;
		int duration;
	public:
		//constructor with no argument
		Customer();
		//constructor with argument
		Customer(string newID, int bed, string checkInDate, int duration);
		//accessor functions
		string getID() const;
		int getNumOfBed() const;
		string getCheckInDate() const;
		int getDuration() const;
};
#endif
Customer::Customer(){
	ID = "";
	numOfBedRequested = 0;
	checkInDate = "";
	duration = 0;
}
Customer::Customer(string newID, int bed, string newCheckInDate, int newDuration){
	ID = newID;
	numOfBedRequested = bed;
	checkInDate = newCheckInDate;
	duration = newDuration;
}
string Customer::getID() const{
	return ID;
}
int Customer::getNumOfBed() const{
	return numOfBedRequested;
}
string Customer::getCheckInDate() const{
	return checkInDate;
}
int Customer::getDuration() const{
	return duration;
}