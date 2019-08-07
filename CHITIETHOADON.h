#include "VATTU.h"
using namespace std;
#define MAX_VATTU_TRENMOT_HOADON 20
//Khai bao mot phan tu cua mang
struct cthd{
	char Mavt[10];
	float Soluong;
	float Dongia;
	int VAT;
	int status = 1;	
};
typedef struct cthd CTHD;

struct listCTHD
{	int n=0;					// s? n�t c?a danh s�ch
	cthd nodesCTDH[MAX_VATTU_TRENMOT_HOADON];		// nodes l� m�ng 1 chi?u c?p ph�t t?nh
};
typedef struct listCTHD LISTCTHD;

bool checkListCthdEmpty(LISTCTHD l){
	return (l.n == 0 ? true : false);
}

bool checkListCthdFull(LISTCTHD l){
	return (l.n == MAX_VATTU_TRENMOT_HOADON ? true : false);
}

void themCthd(LISTCTHD &l, int vitri, CTHD ct){
	if(checkListCthdFull(l) || vitri < 0 || vitri > l.n){
		cout<<"Danh sach day hoac vi tri them khong hop le";
		return;
	}
	for(int i = l.n-1; i>=vitri; i--){
		l.nodesCTDH[i+1] = l.nodesCTDH[i];
	}
	l.nodesCTDH[vitri] = ct;
	l.n++;
	return;
}

void xoaCthd(LISTCTHD &l, int vitri){
	if(checkListCthdEmpty(l) || vitri < 0 || vitri >= l.n){
		cout<<"Vi tri xoa khong hop le, hoac danh sach rong";
	}
	for(int i = vitri+1; i < l.n; i++){
		l.nodesCTDH[i-1] = l.nodesCTDH[i];
	}
	l.n--;
	return;
}

void nhapThongTinCTHD(CTHD &cthd, char *mavt, DSVATTU ds, char *Loai){
	system("cls");

	cBoard c;
	int x = 3, y = 2; int endchar; 
	c.drawBoard(x, y, 60, 15);
	gotoxy(x + 15, y + 1);
	cout<<"NHAP CHI TIET HOA DON";
	
	NhapMaVattu:
		gotoxy(x + 3, y + 3);
	   	cout<<"Nhap ma vat tu:";
		gotoxy(x+23,y+3); cout<<"                                ";
		strcpy(cthd.Mavt, Nhap(x+23,y+3,10, endchar));		
		if (endchar==ESC) return;
		if(strlen(cthd.Mavt) == 0){
			checkMaVattuRong:
				gotoxy(5,20);
				cout<<"Ma vat tu khong duoc rong.";
				endchar = getch();
				if(endchar == ENTER){
					gotoxy(5,22);
					cout<<"                                    ";
					goto NhapMaVattu;
				}else{
					goto checkMaVattuRong;
				}
		}else if (endchar == ENTER){
			if(!checkMavtExist(ds, cthd.Mavt)){
				checkMavtTonTai:
					gotoxy(5,22);
					cout<<"Ma vat tu khong duoc rong.";
					endchar = getch();
					if(endchar == ENTER){
						gotoxy(5,22);
						cout<<"                                 ";
						goto NhapMaVattu;
					}else{
						goto checkMavtTonTai;
					}
			}else if (endchar == ENTER){
				goto nhapSoLuong;
			}
		}
	
	nhapSoLuong:
		gotoxy(x + 3, y + 5);
	   	cout<<"Nhap so luong:";
		gotoxy(x+23,y+5); cout<<"                                ";
		cin >> cthd.Soluong;
		if(cthd.Soluong < 0 || !cin){
			checkNhapSoLuong:
				gotoxy(5,20);
				cout<<"So luong nhap khong hop le. Nhan ENTER de nhap lai.";
				endchar == getch();
				if(endchar == ENTER){
					gotoxy(5,20);
					cin.clear(); // reset failbit
    				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    				cout<<"                                                      ";
    				goto nhapSoLuong;
				}else{
					goto checkNhapSoLuong;
				}
		}else if(endchar == ENTER){
			if(strcmp(Loai,"X") == 0){
				float slt = laySlt(ds, mavt);
				if(slt < cthd.Soluong){
					checkSlt:
						gotoxy(5,20);
						cout<<"So luong ton khong du, trong kho con "<<slt<<" vat tu";
						endchar == getch();
						if(endchar == ENTER){
							gotoxy(5,20);
							cout<<"                                                               ";
							goto nhapSoLuong;
						}else{
							goto checkSlt;
						}
				}
				goto nhapDonGia;
			}
		}
		
	nhapDonGia:
		gotoxy(x + 3, y + 5);
	   	cout<<"Nhap so luong:";
		gotoxy(x+23,y+5); cout<<"                                ";
		cin >> cthd.Dongia;
		if(cthd.Dongia < 0 || !cin){
			checkNhapDonGia:
				gotoxy(5,20);
				cout<<"Don gia khong hop le. Nhan ENTER de nhap lai.";
				endchar == getch();
				if(endchar == ENTER){
					gotoxy(5,20);
					cin.clear(); // reset failbit
    				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    				cout<<"                                                      ";
    				goto nhapDonGia;
				}else{
					goto checkNhapDonGia;
				}
		}else if(endchar == ENTER){
			goto nhapVAT;
		}
		
	nhapVAT:
				gotoxy(x + 3, y + 5);
	   	cout<<"Nhap VAT:";
		gotoxy(x+23,y+5); cout<<"                                ";
		cin >> cthd.VAT;
		if(cthd.VAT < 0 || !cin){
			
		}else if(endchar == ENTER){
			goto setTrangThai;
		}
		
	setTrangThai:
		cthd.status = 1;
		return;
}



