/**Name: Xuechun Cao - 100271794
 **course: CPSC 2150 - 001
 **Asign 2
 ** This program is used to create a room object
*/
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;
#ifndef ROOM_H
#define ROOM_H
class Room{
	//data fields
	private:
		int numOfBed;
		bool available;
		string checkInDate;
		int checkOutYear;
		int checkOutMonth;
		int checkOutDay;
		
	public:
		//constructor with no argument
		Room();
		//constructor with number of bed
		Room(int newNumOfBed);
		//copy constructor
		Room(const Room& another);
		//mutator
		void setNumOfBed(int newNumOfBed);
		void setAvailable();
		void setUnavailable();
		//book the room with check in date and duration
		void bookRoom(string newCheckInDate, int duration);
		//accesor
		string getCheckInDate() const;
		int getNumOfBed() const;
		int getCOY() const;
		int getCOM() const;
		int getCOD() const;
		bool getAvailability() const;
		//static function to calculate check out date
		static int getCheckOutYear(int year,int month, int day,int duration);
		static int getCheckOutMonth(int year,int month, int day,int duration);
		static int getCheckOutDay(int year,int month, int day,int duration);
		//static function to get check in date
		static int getCheckInDay(string newCheckInDate);
		static int getCheckInMonth(string newCheckInDate);
		static int getCheckInYear(string newCheckInDate);
		static int getDayNumOfMonth(int month);
};
Room::Room(){
	numOfBed = 0;
	available = true;
}
Room::Room(int newNumOfBed){
	numOfBed = newNumOfBed;
	available = true;
}
Room::Room(const Room& another){
	numOfBed = another.getNumOfBed();
	available = another.getAvailability();
	checkInDate = another.getCheckInDate();
	checkOutYear = another.getCOY();
	checkOutMonth = another.getCOM();
	checkOutDay = another.getCOD();
}
string Room::getCheckInDate() const{
	return checkInDate;
}
void Room::setNumOfBed(int newNumOfBed){
	numOfBed = newNumOfBed;
}
void Room::setUnavailable(){
	available = false;
}
void Room::setAvailable(){
	available = true;
}
int Room::getCheckInDay(string newCheckInDate){
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
int Room::getCheckInMonth(string newCheckInDate){
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
int Room::getCheckInYear(string newCheckInDate){
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
int Room::getDayNumOfMonth(int month){
	if(month==2){
		return 28;
	}
	else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
		return 31;
	}
	return 30;
}
int Room::getCheckOutDay(int year,int month, int day,int duration){
	day = day + duration;
	if(day <= getDayNumOfMonth(month)){
		return day;
	}
	while(day-getDayNumOfMonth(month) > 0){
		day = day-getDayNumOfMonth(month);
		if(month+1 > 12){
			month = month + 1 - 12;
		}
		else{
			month = month + 1;
		}
	}
	return day;
}
int Room::getCheckOutMonth(int year,int month, int day,int duration){
	day = day + duration;
	if(day <= getDayNumOfMonth(month)){
		return month;
	}
	while(day-getDayNumOfMonth(month) > 0){
		day = day-getDayNumOfMonth(month);
		if(month+1 > 12){
			month = month + 1 - 12;
		}
		else{
			month = month + 1;
		}
	}
	return month;
}
int Room::getCheckOutYear(int year,int month, int day,int duration){
	day = day + duration;
	if(day <= getDayNumOfMonth(month)){
		return year;
	}
	while(day-getDayNumOfMonth(month) > 0){
		day = day-getDayNumOfMonth(month);
		if(month+1 > 12){
			month = month + 1 - 12;
			year = year + 1;
		}
		else{
			month = month + 1;
		}
	}
	return year;
}
void Room::bookRoom(string newCheckInDate, int duration){
	checkInDate = newCheckInDate;
	available = false;
	int inDayInt = getCheckInDay(newCheckInDate);
	int inMonInt = getCheckInMonth(newCheckInDate);
	int inYearInt = getCheckInYear(newCheckInDate);
	checkOutYear = getCheckOutYear(inYearInt,inMonInt,inDayInt,duration);
	checkOutMonth = getCheckOutMonth(inYearInt,inMonInt,inDayInt,duration);
	checkOutDay = getCheckOutDay(inYearInt,inMonInt,inDayInt,duration);
}
int Room::getNumOfBed() const{
	return numOfBed;
}
int Room::getCOY() const{
	return checkOutYear;
}
int Room::getCOM() const{
	return checkOutMonth;
}
int Room::getCOD() const{
	return checkOutDay;
}
bool Room::getAvailability() const{
	return available;
}
#endif