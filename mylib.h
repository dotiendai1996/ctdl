#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include<fstream>
#include<Windows.h>
#include<ctime>
#include <stdlib.h>
#include <unistd.h>
#include<iostream>
#include<math.h>
#include <limits>

const int ESC =27;
const int dong =13;
const int cot = 40 ;
const int Up = 72;
const int Down = 80;
const int UP =72+128; // 200
const int DOWN =80+128; // 208
const int ENTER =13 ; 
const int BACKSPACE=8;
const int KEY_1 = 49;
const int KEY_2 = 50;
const int KEY_3 = 51;
const int KEY_4 = 52;
using namespace std;
#define Enter 13
// const int WHITE=15;
// #define PASSWORD "abcdef"
#define CYAN 3
#define BLACK 0
#define WHITE 15
#define RED 4
#define YELLOW 14

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_DOWN 80
#define KEY_UP 72 
#define KEY_LEFT 75 
#define KEY_RIGHT 77
#define KEY_DEL 127
// const int WHITE=15;

//char* Pwd () {
//     char S[40]; int i=0;
//     while ((S[i]= getch()) != Enter ) 
//     { printf ("%c", '*') ; i++ ; 
//     }
//     S[i]='\0';
//     return S;
//}
//
//int CheckPwd () {
//    int dem =0; 
//    for ( dem =1 ; dem <=3 ; dem++)
//    { printf( "Password :"); 
//      if (strcmp(Pwd(),PASSWORD) ==0)   return 1;
//      else printf ( "\nPassword sai. Hay nhap lai\n")  ; 
//    }
//    return 0;  
//}


//Hàm dich chuyen con tro den toa do x, y
void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  



int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}

void ReSizeConSole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

string ChuyenSoThanhChuoi(int number)
{
	if(number == 0) return "0";
    string s = "";
	while (number!= 0)
	{
		s = char((number % 10) + 48) + s;
		number = number / 10;
	}
	return s;
}

void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(15);
	SetBGColor(1);
}

void VeVien(int x,int y,int dai,int rong,int mau,string s)
{
	for(int i=1 ;i<=dai; i++)
	{
		gotoxy(x+i,y);
		cout<<char(196); // dau -
	}
	
	for(int i =1 ;i<=rong ;i++)
	{
		gotoxy(x+1,y+i);
		for(int j = 1; j <= dai;j++) 
		{
			SetBGColor(mau);
			cout<<" ";
		}
	}
	gotoxy(x + (dai-s.length())/2,rong/2+y);
	cout<< s;
	SetBGColor(0);
	for(int i=1;i<= dai ;i++)
	{
		gotoxy(x+i,rong+y+1);
		cout<<char(196);
	}
}

void TaoThongBaoVaMat(int x,int y,string s)
{
	gotoxy(x,y);
	cout<<s;
	getch();
	gotoxy(x,y);
	cout<<"                                                                          ";  
	
}

//Ham tinh ngay
string HamTinhNgay(){
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer[80];

  	time (&rawtime);
  	timeinfo = localtime(&rawtime);

  	strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
  	string str(buffer);

  	return str;
}


void multiPut(int x=0,int y=0,char c=(char)178, int color=15){
	gotoxy(x,y);
	SetColor(color);
	cout<<c;
}

void drawNgang(int x1=0,int y1=0,int x2=0,int  y2=0,int color =14){
	for(int i=x1;i<x2-1;i++)
		multiPut(i+1,y1,(char)196,color);
}
void drawDoc(int x1=0,int y1=0,int x2=0,int y2=0,int color=14){
	for(int i=0;i<y2-y1-1;i++)
		multiPut(x1,y1+i+1,(char)179,color);
}
void drawChar(int x1=0,int y1=0,int x2 =0,int y2=0,char c=(char)178,int color=14){
		for(int i=x1;i<x2-1;i++)
			multiPut(i+1,y1,c,color);
}
//Ve mot hình chu nhat có toa do 2 dinh (trên, trái – duoi, phai) là (x1,y1)-(x2,y2), voi tiêu de là ttColor
class cBoard{
	public:int x1,y1,x2,y2,width,height;
 
inline void drawBoard(int x1, int y1, int x2, int y2, int color=14,char *title=NULL,int ttColor=15){
	int i;
	multiPut(x1,y1,(char)218,color); //top-left
	multiPut(x2,y1,(char)191,color); //top-right
	multiPut(x1,y2,(char)192,color); //bottom-left
	multiPut(x2,y2,(char)217,color); //bottom-right
	SetColor(color);
	for(i=x1;i<x2-1;i++) //top border */
		multiPut(i+1,y1,(char)196,color);
	for(i=x1;i<x2-1;i++) //bottom border */
		multiPut(i+1,y2,(char)196,color);
		
	for(i=0;i<y2-y1-1;i++) /* left border */
		multiPut(x1,y1+i+1,(char)179,color);
		
	for(i=0;i<y2-y1-1;i++) /* right border */
		multiPut(x2,y1+i+1,(char)179,color);
		
	if (title!=NULL&&strlen(title)<(x2-x1))
		for(i=0;i<strlen(title);i++)
		multiPut(i+(x2+x1)/2-strlen(title)/2,y1,*(title+i),ttColor);
		}
	};
void title();
int MenuDong(char td [][50],int so_item){
  Normal();
  system("cls");   int chon =0;
  	title();
  	SetColor(WHITE);
  int i; 
  for ( i=0; i< so_item ; i++)
  { gotoxy(cot, dong +i);
    cout << td[i];
  }
  HighLight();
  gotoxy(cot,dong+chon);
  cout << td[chon];
  char kytu;
do {
  kytu = getch();
  if (kytu==0) kytu = getch();
  switch (kytu) {
    case Up :if (chon+1 >1)
  			  {
  		              	Normal();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon --;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon ++;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case 13 : return chon+1;
  	case ESC: Normal(); return 0;
  }  // end switch
  } while (1);
}

char* Nhap(int x, int y, int n , int &endchar) { 
	char *S=new char [n]; 
	int i=0; 
	int c;
	gotoxy (x, y);
	while (1) { 
	    endchar =' ';
		c=getch(); 		
		c=toupper(c);
		if (c==224 || c==0) { 
		 c=getch() ;		 c+=128;
		}
		if ((c ==ENTER || c==ESC) ) 
		{ 
			endchar = c ; 
			break ;
		}
		if(c==BACKSPACE&&i)
			printf("\b \b"),i--;
		if (!(isalnum(c))||i>=n-1) 
		{continue;}
		cout <<char(c);// printf(("%s",char(c));
		S[i++]=c;
		if (i==n) 
			break ;
	}
	S[i]=NULL; 
	return S;
}

char* NhapSo(int x, int y, int n , int &endchar) { 
	char *S=new char [n]; 
	int i=0; 
	int c;
	gotoxy (x, y);
	while (1) { 
	    endchar =' ';
		c=getch(); 		
		c=toupper(c);
		if (c==224 || c==0) { 
		 c=getch() ;		 c+=128;
		}
		if ((c ==ENTER || c==ESC) ) 
		{ 
			endchar = c ; 
			break ;
		}
		if(c==BACKSPACE&&i)
			printf("\b \b"),i--;
		if (!(isdigit(c))||i>=n-1) 
		{continue;}
		cout <<char(c);// printf(("%s",char(c));
		S[i++]=c;
		if (i==n) 
			break ;
	}
	S[i]=NULL; 
	return S;
}

char* NhapWithSpace(int x, int y, int n , int &endchar) { 
	char *S=new char [n]; 
	int i=0; 
	int c;
	gotoxy (x, y);
	while (1) { 
	    endchar =' ';
		c=getch(); 		
		c=toupper(c);
		if (c==224 || c==0) { 
		 c=getch() ;		 c+=128;
		}
		if ((c ==ENTER || c==ESC) ) 
		{ 
			endchar = c ; 
			break ;
		}
//		if(c==BACKSPACE&&i)
//			printf("\b \b"),i--;
//		if (!(isalnum(c))||i>=n-1) 
//		{continue;}
	if (i>=n-1) 
		{continue;}
		cout <<char(c);// printf(("%s",char(c));
		S[i++]=c;
		if (i==n) 
			break ;
	}
	S[i]=NULL; 
	return S;
}

int random(){
	srand(time(0)); //can NULL
	int a = rand() % 100 + 1;
	return a;
}

void title(){ 
	SetColor(5);
	gotoxy(35,5);
	cout<<" _______  ___      __   __  _______ ";
	gotoxy(35,6);
	cout<<"|       ||   |    |  | |  ||       |";
	gotoxy(35,7);
	cout<<"|   _   ||   |    |  |_|  ||_     _|";
	gotoxy(35,8);
	cout<<"|  | |  ||   |    |       |  |   |  ";
	gotoxy(35,9);
	cout<<"|  |_|  ||   |___ |       |  |   |  ";
	gotoxy(35,10);
	cout<<"|      | |       | |     |   |   |  ";
	gotoxy(35,11);
	cout<<"|____||_||_______|  |___|    |___|  ";
}
