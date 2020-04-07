#include<bits/stdc++.h>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<windows.h>
using namespace std;
void Begin();
bool Login();
bool Ver(const char,const char);
bool Register();
//bool Ver(const string Pas1,const string Pas2){
//	for(int i=0;i<=max(Pas1.length(),Pas2.length())-1;i++)
//		if(Pas1[i]!=Pas2[i])return false;
//	return true;
//}
bool Login(){
    system("cls");
    COORD c;
    string Acc1,Acc2,Pas1,Pas2;
    printf("©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n");
    printf("©ÀAccount Name:                 ©È");
    c.X=16;
    c.Y=1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cin>>Acc1;
    printf("©ÀPassword:                     ©È\n");
    c.X=12;
    c.Y=2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cin>>Pas1;
    printf("©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n");
//    freopen("C:\\UserData\\login.user","r",stdin);
//    cin>>Acc>>Pas2;
//    freopen("CON", "r", stdin);
	ifstream fin;
	fin.open("registration.out");
	if(fin.fail()||fin.peek()==EOF){
		printf("No User!");
		return false;
	}
	while(!fin.eof()){
		fin>>Acc2>>Pas2;
		if(Acc2==Acc1){
			if(Pas1==Pas2){
				printf("Login success!\n");
				Sleep(250);
				return true;
			}
			else{
				printf("Login failure!\n");
				Sleep(250);
				return false;
			}
		}
	}
//    if(Ver(Pas1,Pas2)) {
//        printf("Login success!\n"),Sleep(250);
//        return true;
//    }else{
//        printf("Login failure!\n"),Sleep(250);
//        return false;
//    }
    return false;
}
bool Register(){
    system("cls");
    COORD c;
    string Acc,Pas;
    printf("©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n");
    printf("©ÀAccount Name:                 ©È");
    c.X=16;
    c.Y=1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cin>>Acc;
    if(Acc.length()>=20){
    	printf("Account Name length cannot exceed 20.\n");
    	Sleep(3000);
    	Register();
	}
    printf("©ÀPassword:                     ©È\n");
    c.X=12;
    c.Y=2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cin>>Pas;
    if(Pas.length()>=15){
    	printf("Password length cannot exceed 15.\n");
    	Sleep(3000);
    	Register();
	}
    printf("©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n");
//    freopen("C:\\UserData\\login.user","w",stdout);
//    cout<<Acc<<endl<<Pas;
//    freopen("CON","w",stdout);
	ofstream fout;
	fout.open("registration.out",ios::app);
	if(fout.fail()){
		printf("Cannot!");
		return false;
	}
	fout<<Acc<<' '<<Pas<<'\n';
	fout.close();
    printf("Successful registration!\n");
    Sleep(250);
    return true;
}
void Begin() {
    char ch;
    bool flag=true;
    while(flag) {
        system("cls");
        printf("©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´\n");
        printf("©À1.[Login]                                                         ©È\n");
        printf("©À©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©È\n");
        printf("©À2.[Registration](Note that you need to log in after registering.) ©È\n");
        printf("©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼\n");
        do{
            ch=getch();
            if(ch=='1')if(Login())flag=false;
            if(ch=='2')if(Register())flag=true;//flag=false;
        }while(ch!='1'&&ch!='2');
    }
}
int main(){
    Begin();
    system("cls");
    printf("\n Welcome! \n");
    return 0;
}
