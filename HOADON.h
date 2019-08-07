#include "CHITIETHOADON.h"
using namespace std;

// ================== KHAI BAO' DANH SACH LIEN KET DON CAC HOA DON =================================
struct hoadon{
	char SoHD[10];
	string Ngay;
	char Loai[2];
	LISTCTHD dsctdh;
};
typedef struct hoadon HOADON; // thay the struct node thanh NODE

struct nodehoadon{
	HOADON data;
	struct nodehoadon *pNext; // Con tro dung de lk cac node vs nhau
};
typedef struct nodehoadon NODEHOADON;
//Khai bao cau truc cua dslk don
struct listHD{
	NODEHOADON *pHead;
	NODEHOADON *pTail;
};
typedef struct listHD LISTHD;

//Khoi tao cau truc dslk don
void khoiTaoLISTHD(LISTHD &l){
	l.pHead = NULL;
	l.pTail = NULL;
}

//Ham khoi tao 1 cai nodes
NODEHOADON *khoiTaoNODE(HOADON hd){
	NODEHOADON *p = new NODEHOADON; //Cap phat vung nho cho NODE p
	if(p == NULL){
		cout<<"Khong du bo nho de cap phat."<<endl;
		return NULL;
	}
	memcpy(p->data.SoHD,hd.SoHD,sizeof(hd.SoHD)) ;
	p->data.Ngay = hd.Ngay;
	memcpy(p->data.Loai,hd.Loai,sizeof(hd.Loai)) ;
	p->pNext = NULL;
	return p;
}


// =======  Ham them NODE p vao dau danh sach lk =======================================
void themVaoDau(LISTHD &l, NODEHOADON *p){
	//neu ds rong
	if(l.pHead == NULL){
		l.pHead = l.pTail = p; //Node dau cung chinh la node cuoi la p
	}else{
		p->pNext = l.pHead; //Cho con tro cua node can them la node p lien ket vs node dau` - pHead
		l.pHead = p; //Cap nhat lai pHead la p
	}
}

// ====== Ham them NODE p vao cuoi danh sach lk =========================================
void themVaoCuoi(LISTHD &l, NODEHOADON *p){
	//neu ds rong
	if(l.pHead == NULL){
		l.pHead = l.pTail = p; //Node dau cung chinh la node cuoi la p
	}else{
		l.pTail->pNext = p; // Cho con tro cua pTail lien ket voi NODE p
		l.pTail = p; // Cap nhat lai pTail la p
	}
}

// ======= Ham kiem tra so hoa don ton tai hay chua? =====================================
bool checkHoaDonExists(LISTHD l, char *SoHD){
	if(l.pHead == NULL) return false;
	for(NODEHOADON *p = l.pHead; p != NULL; p = p->pNext){
		if(p->data.SoHD == SoHD){
			return true;
		}
	}
	return false;
}

// ======= Ham xoa dau ===================================================================
void xoaDauLISTHD(LISTHD &l){
	if(l.pHead == NULL){
		return;
	}
	NODEHOADON *d = l.pHead;
	l.pHead->pNext = l.pHead;
	delete d;
}

// ======= Ham xoa cuoi
void xoaCuoiLISTHD(LISTHD &l){
	if(l.pHead == NULL){
		return;
	}
	if(l.pHead->pNext == NULL){ // Danh sach chi co 1 phan tu
		xoaDauLISTHD(l);
	}
	for(NODEHOADON *k = l.pHead; k != NULL; k = k->pNext){
		if(k->pNext == l.pTail){
			delete l.pTail;
			k->pNext == NULL;
			l.pTail = k;
			return;
		}
	}
}
// ======= Ham xoa node bat ki (Nhap ma hoa don de xoa)
void xoaViTriBatKiLISTHD(LISTHD &l, char *SoHD){
	if(l.pHead == NULL){
		return;
	}
	if(strcmp(l.pHead->data.SoHD,SoHD) == 0){
		xoaDauLISTHD(l);
	}
	if(strcmp(l.pTail->data.SoHD,SoHD) == 0){
		xoaCuoiLISTHD(l);
	}
	NODEHOADON *g = new NODEHOADON;
	for(NODEHOADON *k = l.pHead; k != NULL; k = k->pNext){
		if(strcmp(l.pHead->data.SoHD,SoHD) == 0){
			g->pNext = k->pNext;
			delete k;
			return;
		}
		g = k;
	}
}

// ======================= THONG TIN HOA DON ================================================
void themThongTinHoaDon(HOADON &hd, LISTHD l){
	system("cls");
	cBoard c;
	int x = 3, y = 2; int endchar; 
	c.drawBoard(x, y, 60, 15);
	gotoxy(x + 15, y + 1);
	cout<<"NHAP HOA DON";
	
NhapSoHD:	
	gotoxy(x + 3, y + 3);
   	cout<<"Nhap so hoa don:";
	gotoxy(x+23,y+3); cout<<"                                ";
	strcpy(hd.SoHD, Nhap(x+23,y+3,10, endchar));		
	if (endchar==ESC) return;
	if(!strlen(hd.SoHD)){
	CheckMaRong:	//CheckMaRong
		gotoxy(5,20);
			cout<<"Ma so hoa don khong duoc rong! Bam ENTER de nhap lai";
		endchar =getch();
		if(endchar==ENTER){
			gotoxy(5,20);
			cout<<"                                          ";
			goto NhapSoHD;
		}else
			goto CheckMaRong;
	}
	else if (endchar == ENTER){
		if(!checkHoaDonExists(l,hd.SoHD)){
			goto NhapNgay;	
		}else
		CheckMaTrung:	//CheckMaTrung
			gotoxy(5,20);
			cout<<"Ma so hoa don bi trung! Bam ENTER de nhap lai";
			endchar =getch();
			if(endchar==ENTER){
				gotoxy(55,5);
				cout<<"                                          ";
				goto NhapSoHD;
			}else
				goto CheckMaTrung;
	}
NhapNgay:
hd.Ngay = HamTinhNgay();
goto NhapLoai;
		
NhapLoai:	
	gotoxy(x + 3, y + 5);
	cout<<"Nhap loai: ";
	gotoxy(x + 23, y + 5);
	cout<<"                      ";
	strcpy(hd.Loai, Nhap(x+23,y+5,2, endchar));
	if (endchar==ESC) return; 
	
	if(!strlen(hd.Loai)){
	CheckTenRong:	//CheckTenRong
		gotoxy(5,20);
		cout<<"Loai khong duoc rong! Bam ENTER de nhap lai";
		endchar =getch();
		if(endchar==ENTER){
			gotoxy(5,20);
			cout<<"                                             ";
			goto NhapLoai;
		}else{
			goto CheckTenRong;
		}
	}else if (endchar==ENTER){
		getch();
		if((strcmp(hd.Loai,"X") != 0) && (strcmp(hd.Loai,"N") != 0)){
			CheckLoaiHopLe:
			gotoxy(5,20);
			cout<<"Loai khong hop le! Bam ENTER de nhap lai";
			endchar =getch();
			if(endchar==ENTER){
				gotoxy(5,20);
				cout<<"                                           ";
				goto NhapLoai;
			}else
				goto CheckLoaiHopLe;
		}else return;
	}
}

// ================ XUAT DANH SACH HOA DON ===========================================================

void khungXuatHoaDon() {
  int x = 8, y = 5;
  cBoard c;
  c.drawBoard(x, y, 112, 18);
  gotoxy(x + 11, y + 1);
  cout << "SO HOA DON";
  drawDoc(42, y, 42, 18);
  gotoxy(wherex() + 11, y + 1);
  cout << "NGAY CAP";
  drawDoc(76, y, 76, 18);
  gotoxy(wherex() + 11, y + 1);
  cout << "LOAI";
}


