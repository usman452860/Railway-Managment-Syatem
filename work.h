#ifndef WORK_H
#define WORK_H

#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<algorithm>

using namespace std;

class Auth{
	private:
		string username, password, name;
		ifstream fin;
		ofstream fout;
		void InputData() {
		fout.open("Authentication.dat",ios::in|ios::app);
		fout << "Passenger name: " << name << endl;
		fout << "Username: " << username;
		fout << "  Password: " << password << endl;
		fout.close();
	}
	public:
	bool signup(){
		fin.open("Authentication.dat",ios::out);
		cout<<"\n\n\t\t\t\t\tEnter Passenger name: ";
		cin>>name;
		label:
		cout<<"\t\t\t\t\tEnter username: ";
		cin>>username;
		string x;
		while(fin>>x){
			if(x==username){
				cout<<"\n\t\t\t\t\tThis username already exists please enter unique one."<<endl;
				goto label;
			}
		}
		cout<<"\n\t\t\t\t\tEnter password: ";
		cin>>password;
		fout.close();
		InputData();
		return true;		
	}

	bool login(){
		system("CLS");
		fin.open("Authentication.dat",ios::out);

		cout << "\n\n\n\t\t\t\t\tLOGIN" << endl;
		cout << "\t\t\t\t\tPlease enter username and password" << endl;
		cout << "\n\n\t\t\t\t\tEnter username: ";
		cin>>username;
		cout<<"\t\t\t\t\tEnter password: ";
		cin>>password;
		string x;
		while(getline(fin,x)){
			if(x=="Username: "+username+"  Password: "+password){
				fin.close();
				return true;
			}
		}
		fin.close();
		return false;
	}
};


class TrainOperations{
	private:
		friend class TicketBooking;
		ofstream input;
		ifstream output;
	protected:
		string trainName;
		string route;
		string timing;
		string fare;
	public:
		TrainOperations() {
			trainName="";
			route="";
			timing="";
			fare="";
		}
	void storeIninput(){

		input.open("TrainFile.dat",ios::in|ios::app);
		input<<"\t\t\t\t\tRoute: "<<route<<endl;
		input << "\t\t\t\t\tTrain name: " << trainName << endl;
		input<<"\t\t\t\t\tTiming: "<<timing<<endl;
		input<<"\t\t\t\t\tFare: "<<fare<<endl;
		input<<"\t\t\t\t\t__________________"<<endl;
		input.close();
	}
	void addNewTrain(){
			cout<<"\n\n\t\t\t\t\tEnter train name: ";
			cin>>trainName;
			transform(trainName.begin(), trainName.end(), trainName.begin(), ::toupper);
			cout<<"\t\t\t\t\tEnter route: ";
			cin>>route;
			transform(route.begin(), route.end(), route.begin(), ::toupper);
			cout<<"\t\t\t\t\tEnter timings: ";
			cin>>timing;
			cout<<"\t\t\t\t\tEnter Fare: ";
			cin>>fare;
			storeIninput();
		}
	void viewTrains(){
			cout << "\n\n";
			output.open("TrainFile.dat",ios::out);
			string x;
			bool flag = true;
			while(getline(output,x)){
				flag = false;
				cout<<x<<endl;
			}
			if (flag == true) {
				cout << "\t\t\t\t\tNothing to show!!!\n";
			}
			cout << "\t\t\t\t\t";
			output.close();
	}

	void deltrain() {
		cout << "\n\n";
		output.open("TrainFile.dat");
		input.open("temp.dat");
		if (!output)
		{
			cout << "\t\t\t\t\tFile could not be open !! \n\t\t\t\t\tPress any key to continue...";
			return;
		}
		bool flag = false;
		string searc;
		int x=0;
		cout << "\t\t\t\t\tEnter train name: ";
		cin >> searc;
		transform(searc.begin(), searc.end(), searc.begin(), ::toupper);
		string arr[5];
		while (getline(output, arr[x])) {
			if (x == 4) {
				x = 0;
				if (arr[1] == ("\t\t\t\t\tTrain name: " + searc)) {
					flag = true;
					while (getline(output, arr[x])) {
						if (arr[4] == "\t\t\t\t\t__________________") {
							break;
						}
						x += 1;
					}
					x = 0;
				}
				else {
					input << arr[0] << endl;
					input << arr[1] << endl;
					input << arr[2] << endl;
					input << arr[3] << endl;
					input << arr[4] << endl;
					x = 0;
				}
			}
			else {
				x += 1;
			}
			
		}
		cout << "\n\n\t\t\t\t\t";

		output.close();
		input.close();
		remove("TrainFile.dat");
		rename("temp.dat", "TrainFile.dat");
		if (flag == true) {
			cout << "Train deleted successfully!" << endl;
		}
		else if(flag == false)
			cout << "No Record Found!!" << endl;
	}

	void searchTrain(){
			cout << "\n\n";
			output.open("TrainFile.dat",ios::out);
			string search;
			bool flag = false;
			cout<<"\t\t\t\t\tEnter Route: ";
			cin>>search;
			transform(search.begin(), search.end(), search.begin(), ::toupper);
			string y;
			while(getline(output,y)){
				if (y == ("\t\t\t\t\tRoute: " + search)) {
					flag = true;
					while (getline(output, y)) {
						cout << y << endl;
						if (y == "\t\t\t\t\t__________________") {
							break;
						}
					}
				}
			}
			output.close();
			cout << "\t\t\t\t\t";
			if (flag == false) {
				cout << "\n\n\t\t\t\t\tNo Train Found!!" << endl;
				cout << "\t\t\t\t\t";
			}
	}
};

class admin : public TrainOperations , public Auth{
private:
	string ad;
public:
	string x;
	admin() {
		ad = "admin";
	}

	bool login() {
		cout << "\n\n\t\t\t\t\tEnter password: ";
		cin >> x;
		if (x == ad) {
			return true;
		}
		return false;
	}
};

class TicketBooking {
	private:
		string bookingId,nameOfPassenger,numberOfTickes,seatNumbers;
		TrainOperations operation;		//Friend Class
		ifstream fin;
		ofstream fout;
		void storeInFile(){
			fout.open("Tickets.dat",ios::in|ios::app);
			fin.open("TrainFile.dat",ios::out);
			fout<<"\t\t\t\t\tBooking id: "<<bookingId<<endl;
			fout<<"\t\t\t\t\tPassenger name: "<<nameOfPassenger<<endl;
			fout<<"\t\t\t\t\tNumber of tickets: "<<numberOfTickes<<endl;
			fout<<"\t\t\t\t\tRoute: "<<operation.route<<endl;
			string x;
			while(getline(fin,x)){
				if(x=="\t\t\t\t\tRoute: "+operation.route){
					while(getline(fin,x)){
						if(x=="\t\t\t\t\t_______________"){
							break;
						}
						fout<<x<<endl;
						cout<<"\t\t\t\t\t"<<x<<endl;
					}
				}
			}
			fout<<"\t\t\t\t\t_______________"<<endl;
			fout.close();
			fin.close();
		}
	public:
		void bookTicket(){
			bool flag = false;
			string x,z;
			system("CLS");
			fin.open("TrainFile.dat",ios::out);
			cout<<"\n\n\t\t\t\t\tEnter booking id: ";
			cin>>bookingId;
			cout<<"\t\t\t\t\tEnter name of passenger: ";
			cin>>nameOfPassenger;
			cout<<"\t\t\t\t\tEnter number of tickets: ";
			cin>>numberOfTickes;
		label:
			cout<<"\t\t\t\t\tEnter route: ";
			cin>>operation.route;
			transform(operation.route.begin(), operation.route.end(), operation.route.begin(), ::toupper);
			while(getline(fin,x)){
				if (x == "\t\t\t\t\tRoute: " + operation.route) {
					flag = true;
					cout << "\n\t\t\t\t\t*****Ticket Booked Successfully*****" << endl;
					Sleep(2000);
				label2:
					system("CLS");
					cout << "\n\n\t\t\t\t\tDo you again want to book ticket (y/n)?\n";
					cout << "\t\t\t\t\t";
					cin >> z;
					try {
						if (z == "y") {
							fin.close();
							storeInFile();
							bookTicket();
						}
						else if (z == "n") {
							fin.close();
							storeInFile();
							break;
						}

						else{
							throw 505;
						}
					}
					catch (...) {
						cout << "Invalid Input!!!";
						goto label2;
					}
				}
			}
			if(flag==false){
				fin.close();
				cout<<"\t\t\t\t\tNo such route found...";
				Sleep(2000);
				cout<<endl;
				fin.open("TrainFile.dat",ios::out);
				goto label;
			}
		}
		void cancelBookings(){
			cout << "\n\n";
			fin.open("Tickets.dat");
			fout.open("temp1.dat");
			if (!fin)
			{
				cout << "File could not be open !! \n\t\t\t\t\t";
				return;
			}

			string search;
			string x;
			bool flag = false;

			cout << "\t\t\t\t\tEnter booking id: ";
			cin >> search;
			while (getline(fin, x)) {
				if (x == ("\t\t\t\t\tBooking id: " + search)) {
					flag = true;
					while (getline(fin, x)) {
						if (x == "\t\t\t\t\t_______________") {
							break;
						}
					}
				}
				else {
					fout << x << endl;
				}

			}
			cout << "\n\n\t\t\t\t\t";

			fin.close();
			fout.close();

			remove("Tickets.dat");
			rename("temp1.dat", "Tickets.dat");
			if (flag == true) {
				cout << "Ticket Cancel successfully!" << endl;
				Sleep(2000);
			}
			else
				cout << "No Record Found!!" << endl;
				Sleep(2000);
		}

		void searchBooking(){
			cout << "\n\n";
			fin.open("Tickets.dat",ios::out);
			bool flag = false;
			string search;
			string y;
			cout<<"\t\t\t\t\tEnter booking id: ";
			cin>>search;
			while(getline(fin,y)){
				if(y==("\t\t\t\t\tBooking id: "+search)){
					flag = true;
					while(getline(fin,y)){
						cout<<y<<endl;
						if(y=="\t\t\t\t\t_______________"){
							break;
						}
					}
				}
			}
			cout << "\t\t\t\t\t";
			fin.close();
			if (flag == false) {
				cout << "\n\t\t\t\t\tNo Ticket found!!!\n";
				cout << "\t\t\t\t\t";
			}
		}
		void viewBookings() {
			cout << "\n\n";
			fin.open("Tickets.dat", ios::out);
			string x;
			bool flag = true;

			while (getline(fin, x)) {
				flag = false;
				cout << x << endl;
			}
			if (flag == true) {
				cout << "\t\t\t\t\tNothing to show!!!\n";
			}
			cout << "\t\t\t\t\t";
			fin.close();

		}
};
#endif

