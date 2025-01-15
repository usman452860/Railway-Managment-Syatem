#include "work.h"
#include<conio.h>
#include<ctime>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

static char choice;
void trainChoiceFun(){
	cout << ("\n\n");
	cout << ("\t\t\t          <<<<<<<<<<<<<<< WELCOME ADMIN >>>>>>>>>>>>>>\n");
	cout << ("\n\n");
	cout << ("\t\t\t              ************************************\n");
	cout << ("\t\t\t              ||      CHOOSE YOUR OPERATION     ||\n");
	cout << ("\t\t\t              ||--------------------------------||\n");
	cout << ("\t\t\t              ||      [1] ADD TRAIN             ||\n");
	cout << ("\t\t\t              ||      [2] DELETE TRAIN          ||\n");
	cout << ("\t\t\t              ||      [3] TRAIN DETAILS         ||\n");
	cout << ("\t\t\t              ||      [4] PASSENGER DETAILS     ||\n");
	cout << ("\t\t\t              ||      [5] LOGOUT                ||\n");
	cout << ("\t\t\t              ||                                ||\n");
	cout << ("\t\t\t              ************************************\n\n");
	cout << ("\t\t\t     **********************************************************\n");
	cout << ("\n\t\t\t\t\tENTER YOUR CHOICE: ");
}
void dashboard(){
	cout << ("\n\n");
	cout << ("\t\t\t          <<<<<<<<<<<<<<< WELCOME USERS >>>>>>>>>>>>>>\n");
	cout << ("\n\n");
	cout << ("\t\t\t              ************************************\n");
	cout << ("\t\t\t              ||      CHOOSE YOUR OPERATION     ||\n");
	cout << ("\t\t\t              ||--------------------------------||\n");
	cout << ("\t\t\t              ||      [1] BOOKING OPTIONS       ||\n");
	cout << ("\t\t\t              ||      [2] SEARCH TRAIN          ||\n");
	cout << ("\t\t\t              ||      [3] LOG OUT               ||\n");
	cout << ("\t\t\t              ||                                ||\n");
	cout << ("\t\t\t              ************************************\n\n");
	cout << ("\t\t\t     **********************************************************\n");
	cout << ("\n\t\t\t\t\t   ENTER YOUR CHOICE: ");
}
void bookingChoiceFun(){
	cout << ("\n\n");
	cout << ("\t\t\t          <<<<<<<<<<<<<<< WELCOME USERS >>>>>>>>>>>>>>\n");
	cout << ("\n\n");
	cout << ("\t\t\t              ************************************\n");
	cout << ("\t\t\t              ||      CHOOSE YOUR OPERATION     ||\n");
	cout << ("\t\t\t              ||--------------------------------||\n");
	cout << ("\t\t\t              ||      [1] BOOK TICKET           ||\n");
	cout << ("\t\t\t              ||      [2] CANCEL TICKET         ||\n");
	cout << ("\t\t\t              ||      [3] SEARCH BOOKING        ||\n");
	cout << ("\t\t\t              ||      [4] BACK                  ||\n");
	cout << ("\t\t\t              ||                                ||\n");
	cout << ("\t\t\t              ************************************\n\n");
	cout << ("\t\t\t     **********************************************************\n");
	cout << ("\n\t\t\t\t\t   ENTER YOUR CHOICE: ");
}
void menu() {
	cout << ("\n\t\t\t    ===========================================================");
	cout << ("\n\t\t\t    **************  RAILWAY RESERVATION SYSTEM  ***************");
	cout << ("\n\t\t\t    ===========================================================");
	cout << ("\n\n");
	cout << ("\t\t\t              <<<<<<<<<<<<<<< WELCOME >>>>>>>>>>>>>>>\n");
	cout << ("\n\n");
	cout << ("\t\t\t              ***************************************\n");
	cout << ("\t\t\t              ||      CHOOSE YOUR OPERATION        ||\n");
	cout << ("\t\t\t              ||-----------------------------------||\n");
	cout << ("\t\t\t              ||      [1] CREATE NEW ACCOUNT       ||\n");
	cout << ("\t\t\t              ||      [2] LOGIN EXISTING ACCOUNT   ||\n");
	cout << ("\t\t\t              ||      [3] ADMIN MODE               ||\n");
	cout << ("\t\t\t              ||      [4] EXIT                     ||\n");
	cout << ("\t\t\t              ||                                   ||\n");
	cout << ("\t\t\t              ***************************************\n\n");
	cout << ("\t\t\t     **********************************************************\n");
	cout << ("\n\t\t\t\t\t   ENTER YOUR CHOICE: ");
	choice = _getch();
}
int main(){
	Auth auth;
	admin admin;
	TicketBooking booking;
	TrainOperations operation;
	system("CLS");
	time_t currentTime;
	time(&currentTime);
	cout<< ("\n\t\t\t\t\t\t") << asctime(localtime(&currentTime));
	menu();
	system("CLS");
	switch(choice){
		case '1':
			cout<<"\n\n\n\t\t\t\t\tSIGNUP"<<endl;
			if(auth.signup()){
				cout<<"\n\t\t\t\t\tYour account has been created successfully"<<endl;
				cout<<"\t\t\t\t\tPress any key to continue.....";
				_getch();
				main();
			}
			break;
		case '2':
			bool check;
			for(int i=0;i<2;i++){
			check = auth.login();
			if(check){
				system("CLS");
				goto dashboard;
			}
			else {
				cout << "\n\t\t\t\t\t\aInvalid username and password" << endl;
				cout << "\n\t\t\t\t\tPlease try again....";
				Sleep(1000);
			}					
			}
			cout << "\n\t\t\t\t\tToo many attempts!!!";
			Sleep(2000);
			main();
		case '3':
		label1:
			system("CLS");
			cout << "\n\n\n\t\t\t\t\tLOGIN" << endl;
			try {
				if (admin.login()) {
				label2:
					system("CLS");
					trainChoiceFun();
					choice = _getch();
					cout << endl;
					if (choice == '1') {
						system("CLS");
						admin.addNewTrain();
						cout << "\n\t\t\t\t\tNew train added...";
						Sleep(2000);
						system("CLS");
						goto label2;
					}
					else if (choice == '2') {
						system("CLS");
						admin.deltrain();
						Sleep(2000);
						goto label2;
					}
					else if (choice == '3') {
						system("CLS");
						admin.viewTrains();
						system("pause");
						goto label2;
					}
					else if (choice == '4') {
						system("CLS");
						booking.viewBookings();
						system("pause");
						goto label2;
					}
					else if (choice == '5') {
						main();
					}
					else {
						_getch();
						system("CLS");
						goto label2;
					}
				}
				else {
					throw 505;
				}
			}
			catch (...) {
				cout << "\n\n\t\t\t\t\t\aInvalid password" << endl;
				cout << "\n\n\t\t\t\t\tPlease try again....";
				Sleep(2000);
				goto label1;
				}
			break;

		case '4':
			system("CLS");
			_getch();
			exit(0);
			break;

		default:
			main();
	}


	while(true){
		dashboard:
		system("CLS");
		dashboard();
		choice = _getch();
		system("CLS");
		switch(choice){		
			case '1':
				label5:
				system("CLS");
				bookingChoiceFun();
				choice = _getch();
				cout<<endl;
				if (choice == '1') {
					system("CLS");
					booking.bookTicket();
					goto label5;
				}
				else if (choice == '2') {
					system("CLS");
					booking.cancelBookings();
					goto label5;
				}
				else if (choice == '3') {
					system("CLS");
					booking.searchBooking();
					system("pause");
					goto label5;
				}
				else if (choice == '4') {
					goto dashboard;
				}
				else
					system("CLS");
					goto label5;
			case '2':
				system("CLS");
				operation.searchTrain();
				system("pause");
				break;
			case '3':
				main();
		}
		
	}
	return 0;
}

