
#include <iostream>
#include "audio.h"

using namespace std;


int main(){
	cout<<endl;
	cout<<"* * * Welcome to the Mancala Mini Music Player * * *"<<endl<<endl;
	do {
	int choose;

	cout<<"Use Space or press window close to exit out of present music window to return to selection"<<endl;
	cout<<"1: Daydream"<<endl;
	cout<<"2: 16bit BGM"<<endl;
	cout<<"3: Jazz loop"<<endl;
	cout<<"4: Chill beat mix"<<endl;
	cout<<"5: Lofi bass with keyboard"<<endl;
	cout<<"6: Lofi version 2"<<endl;
	cout<<"Enter a selection from 1-6, 9 for exit: "<<endl;

	cin>>choose;

	if (choose==1){
		backgroundmusic1();}
	else if (choose == 2){
		backgroundmusic2();}
	else if (choose == 3) {
		backgroundmusic3();}
	else if (choose == 4){
		backgroundmusic4();}
	else if (choose == 5) {
		backgroundmusic5();}
	else if (choose == 6) {
		backgroundmusic6();
		}
	else if (choose == 9) {
		exit(0);
		}
	else {
		cout<<"Please enter a valid command!"<<endl;
	}

	} while(true);

    return 0;
}
