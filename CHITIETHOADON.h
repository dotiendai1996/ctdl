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
{	int n=0;					// s? nút c?a danh sách
	cthd nodesCTDH[MAX_VATTU_TRENMOT_HOADON];		// nodes là mãng 1 chi?u c?p phát t?nh
};
typedef struct listCTHD LISTCTHD;

bool checkListCthdEmpty(LISTCTHD l){
	return (l.n == 0 ? true : false);
}

bool checkListCthdFull(LISTCTHD l){
	return (l.n == MAX_VATTU_TRENMOT_HOADON ? true : false);
}

void themCthd(LISTCTHD &l, int vitri, CTHD ct){
	if(checkListCthdFull(l)){
		cout<<"Danh sach day, khong the them.";
		return;
	}
	if(vitri < 0 || vitri > l.n){
		cout<<"Vi tri them khong hop le.";
		return;
	}
	for(int i = l.n-1; i>=vitri; i--){
		l.nodesCTDH[i+1] = l.nodesCTDH[i];
	}
	l.nodesCTDH[vitri] = ct;
	l.n++;
	return;
}

void themCthdVaoCuoi(LISTCTHD &l, CTHD ct){
	if(checkListCthdFull(l)){
		cout<<"Danh sach day, khong the them.";
		return;
	}
	l.nodesCTDH[l.n] = ct;
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

void nhapThongTinCTHD(CTHD &cthd, DSVATTU &ds, char *Loai){
	
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
				cout<<"Ma vat tu khong duoc rong. Nhan ENTER de nhap lai.";
				endchar = getch();
				if(endchar == ENTER){
					gotoxy(5,20);
					cout<<"                                    ";
					goto NhapMaVattu;
				}else{
					goto checkMaVattuRong;
				}
		}else if (endchar == ENTER){
			if(!checkMavtExist(ds, cthd.Mavt)){
				checkMavtTonTai:
					gotoxy(5,20);
					cout<<"Ma vat tu khong ton tai trong danh sach. Nhan ENTER de nhap lai.";
					endchar = getch();
					if(endchar == ENTER){
						gotoxy(5,20);
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
		gotoxy(x+23,y+5); 
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
				float slt = laySlt(ds, cthd.Mavt);
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
		gotoxy(x + 3, y + 7);
	   	cout<<"Nhap don gia:";
		gotoxy(x+23,y+7); cout<<"                                ";
		gotoxy(x + 23, y + 7);
		cin >> cthd.Dongia;
		if(cthd.Dongia < 0 || !cin){
			checkNhapDonGia:
				gotoxy(5,20);
				cout<<"Don gia khong hop le. Nhan ENTER de nhap lai.";
				endchar == getch();
				if(endchar == ENTER){
					cin.clear(); // reset failbit
    				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					gotoxy(5,20);
    				cout<<"                                                      ";
    				goto nhapDonGia;
				}else{
					goto checkNhapDonGia;
				}
		}else if(endchar == ENTER){
			goto nhapVAT;
		}
		
	nhapVAT:
		gotoxy(x + 3, y + 9);
	   	cout<<"Nhap VAT:";
	   	gotoxy(x+27, y+9);
	   	cout<<" %";
		gotoxy(x+23,y+9); cout<<"                                ";
		gotoxy(x+27, y+9);
	   	cout<<" %";
		gotoxy(x + 23, y + 9);
		cin >> cthd.VAT;

		if(cthd.VAT < 0 || !cin){
			checkRongVAT:
				gotoxy(5,20);
				cout<<"VAT khong hop le. Nhan ENTER de tiep tuc.";
				endchar = getch();
				if(endchar == ENTER){
					cin.clear(); // reset failbit
    				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					gotoxy(5,20);
					cout<<"                                                   ";
					goto nhapVAT;
				}else{
					goto checkRongVAT;
				}
		}else if(endchar == ENTER){
			goto setTrangThai;
		}
		
	setTrangThai:
		if(strcmp(Loai,"X") == 0){
			cthd.status = 1;
			capNhatSoLuongTon(cthd.Mavt, ds,cthd.Soluong, 2);
			return;
		}else if(strcmp(Loai,"N") == 0){
			capNhatSoLuongTon(cthd.Mavt, ds,cthd.Soluong, 1);
			return;
		}
		return;
}


// ============ XUAT THONG TIN CHI TIET HOA DON =====================================================
void khungXuatCthd() {
  int x = 6, y = 5;
  cBoard c;
  c.drawBoard(x, y, 112, 20);
  gotoxy(x + 3, y + 1);
  cout << "MA VAT TU";
  drawDoc(27, y, 27, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "SO LUONG";
  drawDoc(49, y, 49, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "DON GIA";
  drawDoc(71, y, 71, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "VAT";
  drawDoc(93, y, 93, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "TRANG THAI";
  drawNgang(6, y + 2, 112, y + 2);
}




