#include "hoadon.h"

using namespace std;

#define MAX_MENU_NHANVIEN 4
const string FEMALE = "Nu";
const string MALE = "Nam";
char menunv[MAX_MENU_NHANVIEN][50] = {
  "1. XEM DANH SACH NHANVIEN.",
  "2. THEM NHAN VIEN.         ",
  "3. SUA NHAN VIEN.          ",
  "4. TRO VE MENU CHINH.   "
};

struct nhanvien {
  int Manv;
  char Ho[11];
  char Ten[11];
  char Phai[2]; // 0 la nu, 1 la nam
  LISTHD *dshd = NULL;
};
typedef struct nhanvien NHANVIEN;

struct nodeNhanVien {
  NHANVIEN data;
  struct nodeNhanVien * pLeft;
  struct nodeNhanVien * pRight;
};
typedef struct nodeNhanVien NODENHANVIEN;
typedef NODENHANVIEN *TREE;

void khoiTaoTree(TREE & t) {
  t = NULL;
}

struct mangtam {
  TREE node;
  int manv;
};
typedef struct mangtam MANGTAM;
struct dsmangtam //Dung mang de xuat danh sach vat tu va lam nhiem vu xoa va sua
{
  int n = 0;

  MANGTAM node[50];
};
typedef struct dsmangtam DSNHANVIEN;

void chuyenCaySangMang(TREE t, DSNHANVIEN & ds) // chuyen tu cay nhi phan sang mang mot chieu de lam danh sách
{
if(t == NULL){
	return;
}
  if (t != NULL) {
  	ds.node[ds.n].node = t;
    ds.node[ds.n].manv = t->data.Manv;
    ds.n++;
    chuyenCaySangMang(t->pLeft, ds);
    chuyenCaySangMang(t->pRight, ds);
  }
}

void HoanVi(MANGTAM & x, MANGTAM & y) {
  MANGTAM temp = x;
  x = y;
  y = temp;
}

void sapXepTheoTen(DSNHANVIEN & ds) {
  for (int i = 0; i < ds.n - 1; i++) {
    for (int j = i + 1; j < ds.n; j++) {
      if (strcmp(ds.node[i].node->data.Ten, ds.node[j].node->data.Ten) == 1) {
        HoanVi(ds.node[i], ds.node[j]);
      } else if (strcmp(ds.node[i].node->data.Ten, ds.node[j].node->data.Ten) == 0) {
        if (strcmp(ds.node[i].node->data.Ho, ds.node[j].node->data.Ho) == 1) {
          HoanVi(ds.node[i], ds.node[j]);
        }
      }
    }
  }
}

bool checkKeyExists(TREE t, int key) {
  if (t == NULL) {
    return false;
  } else {
  	
    if (key < t->data.Manv) {
      checkKeyExists(t -> pLeft, key);
    } else if (key > t->data.Manv) {
      checkKeyExists(t -> pRight, key);
    } else {
      return true;
    }
  }
}

// =================THEM NHAN VIEN VAO TREE ========================================
void themPhanTuVaoTree(TREE & t, NHANVIEN x) {
  if (t == NULL) {
    NODENHANVIEN * p = new NODENHANVIEN;
    p -> data = x;
    p -> pLeft = NULL;
    p -> pRight = NULL;
    t = p;
  } else {
    if (x.Manv < t->data.Manv) {
      themPhanTuVaoTree(t->pLeft, x);
    } else if (x.Manv > t->data.Manv) {
      themPhanTuVaoTree(t->pRight, x);
    }
  }
}

// ============= NHAP THONG TIN NHAN VIEN ==============================
void nhapThongTinNhanVien(TREE t, NHANVIEN & nv, int flg) {
  system("cls");
  cBoard c;
  int x = 3, y = 2;
  int endchar;
  c.drawBoard(x, y, 70, 15);
  gotoxy(x + 20, y + 1);
  if (flg == 1) {
    cout << "THEM THONG TIN NHAN VIEN";
  } else {
    cout << "SUA THONG TIN NHAN VIEN";
  }

  //Nhap ma nhan vien
  if (flg == 1) {
  	NhapMaNhanVien:
    gotoxy(x + 3, y + 3);
    cout << "Nhap ma nhan vien: ";
      gotoxy(x + 26, y + 3);
      cout << "                                ";
      gotoxy(x + 26, y + 3);
      rewind(stdin);
      cin >> nv.Manv;
      if (!cin || nv.Manv < 0) {
      	checkManvHopLe:
      	gotoxy(5,10);
        cout<<("Ma nhan vien khong hop le. Nhan Enter de nhap lai.");
        endchar = getch();
        if(endchar == ENTER){
        	cin.clear(); // reset failbit
    		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
        	gotoxy(5,10);
        	cout<<("                                                         ");
        	goto NhapMaNhanVien;
		}else{
			goto checkManvHopLe;
		}
//        cin.clear(); // reset failbit
//        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n'); //skip bad input
      } else if (endchar == ENTER) {
        if(checkKeyExists(t, nv.Manv)){
        	checkManvExists:
        	gotoxy(5,20);
        	cout<<"Ma nhan vien ton tai. Nhan Enter de nhap lai.";
        	endchar = getch();
        	if(endchar == ENTER){
        		gotoxy(5,20);
        		cout<<"                                              ";
        		goto NhapMaNhanVien;
			}else{
				goto checkManvExists;
			}
		}else{
			goto NhapHo;
		}
      }
  }

  //Nhap ho 
  NhapHo:
  gotoxy(x + 3, y + 5);
  cout << "Nhap ho nhan vien: ";
    gotoxy(x + 26, y + 5);
    cout << "                                ";
    gotoxy(x + 26, y + 5);
    rewind(stdin);
    strcpy(nv.Ho, Nhap(x+26, y+5, 11, endchar));
    if (strlen(nv.Ho) == 0) {
    	checkHoRong:
    		gotoxy(5,20);
        	cout<<"Ho nhan vien khong duoc rong. Nhan Enter de nhap lai.";
        	endchar = getch();
        	if(endchar == ENTER){
        		gotoxy(5,20);
        		cout<<"                                                            ";
        		goto NhapHo;
			}else{
				goto checkHoRong;
			}
    }else if(endchar == ENTER){
    	goto NhapTen;
	}

  //Nhap ten
  NhapTen:
  gotoxy(x + 3, y + 7);
  cout << "Nhap ten nhan vien: ";
    gotoxy(x + 26, y + 7);
    cout << "                                ";
    gotoxy(x + 26, y + 7);
    rewind(stdin);
    strcpy(nv.Ten, Nhap(x+26, y+7, 11, endchar));
    if (strlen(nv.Ten) == 0) {
      	checkTenRong:
      	gotoxy(5,20);
      	cout<<"Ten nhan vien khong duoc rong. Nhan Enter de nhap lai.";
      	endchar = getch();
      	if(endchar == ENTER){
      		gotoxy(5,20);
      		cout<<"                                                               ";
      		goto NhapTen;
		}else{
			goto checkTenRong;
		}
    } else if(endchar == ENTER){
    	goto NhapPhai;
	}

  //Nhap phai
  NhapPhai:
  gotoxy(x + 3, y + 9);
  cout << "Nhap phai (Chi duoc nhap 0 hoac 1):";
    gotoxy(x + 26, y + 10);
    cout << "                                ";
    gotoxy(x + 26, y + 10);
    rewind(stdin);
   strcpy(nv.Phai, NhapSo(x+26,y+10,2, endchar));	
    if(endchar == ESC) return;
    if (strcmp(nv.Phai,"0") < 0 || strcmp(nv.Phai,"1") > 0) {
//    	cin.clear(); // reset failbit
//    	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    	checkPhai:
   		gotoxy(5,20); cout<<"Phai khong hop le. Nhan Enter de nhap lai.";
   		endchar = getch();
   		if(endchar == ENTER){
   			gotoxy(5,20); cout<<"                                           ";
      		goto NhapPhai;	
		}else{
			goto checkPhai;
		}
    } else if(endchar == ENTER){
		return;
	}
  
}

// ============== XUAT DANH SACH NHAN VIEN ===================================

void khungXuatNhanvien() {
  int x = 8, y = 5;
  cBoard c;
  c.drawBoard(x, y, 112, 20);
  gotoxy(x + 3, y + 1);
  cout << "Ma nhan vien";
  drawDoc(34, y, 34, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "Ho nhan vien";
  drawDoc(60, y, 60, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "Ten nhan vien";
  drawDoc(86, y, 86, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "Phai";
  drawNgang(8, y + 2, 112, y + 2);

}
TREE timTree(TREE t, int manv);
void xemDanhSachHoaDon(TREE &t, int manv, LISTHD &l, DSVATTU dsvt) {
	
	if(t!=NULL){
		if(t->data.Manv < manv){
			xemDanhSachHoaDon(t->pLeft, manv, l, dsvt);
		}else if(t->data.Manv > manv){
			xemDanhSachHoaDon(t->pRight, manv, l, dsvt);
		}

		system("cls");
		if(t->data.dshd == NULL){
			cout<<"Nhan vien nay chua co hoa don";
		}else{
			khungXuatHoaDon();
			int x = 8; int y = 5;
			for(NODEHOADON *k = t->data.dshd->pHead; k != NULL; k = k->pNext){
				gotoxy(x+2, y+3);
				cout<<k->data.SoHD;
				gotoxy(x+36, y+3);
				cout<<k->data.Ngay;
				gotoxy(x+78, y+3);
				cout<<k->data.Loai;
				y++;
			}
		}
	    gotoxy(3, 20);
	  	cout << "Nhan 1: Them don hang     Nhan ESC: Thoat";
	  	fflush(stdin);
		while(true){
			
			 Normal();
		    char c = getch();
		    if (c == 0 || c == 224) {
		      c = getch();
		      c += 128;
		    } else if (c == ESC) {
		      return;
			}else if (c == KEY_1){
				gotoxy(3,2);
				HOADON hd;
				themThongTinHoaDon(hd,l);
				NODEHOADON *p = khoiTaoNODE(hd);
				themVaoCuoi(l, p);
				t->data.dshd = &l;
				CTHD cthd;
				nhapThongTinCTHD(cthd, dsvt, hd.Loai);
				xemDanhSachHoaDon(t, manv, l, dsvt);
			}else if(c == KEY_2){
				char SoHD[10];
				gotoxy(2,2);
				cout<<"Nhap so hoa don: ";
				cin>>SoHD;
				checkHoaDonExist(l, SoHD);
			}
		}
	}
}

void xuatThongTinNhanvien(NHANVIEN x, int y) {
  gotoxy(9, y);
  cout << x.Manv;
  gotoxy(37, y);
  cout << x.Ho;
  gotoxy(63, y);
  cout << x.Ten;
  gotoxy(89, y);
  if (strcmp(x.Phai,"0") == 0) {
    cout << FEMALE;
  } else {
    cout << MALE;
  }

}
void xuatDanhSachNhanvienTheoMang(TREE &t, LISTHD &l, DSVATTU dsvt) {
	DSNHANVIEN ds;
  chuyenCaySangMang(t, ds);
  sapXepTheoTen(ds);
  system("cls");
  khungXuatNhanvien();
  gotoxy(50, 3);
  int x = 11, y = 7;
  for (int i = 0; i < ds.n; i++) {
    gotoxy(x, y + 1);
    y++;
    xuatThongTinNhanvien(ds.node[i].node -> data, y);
  }

  gotoxy(3, 25);
  cout << "Nhan 1: Them nhanvien      Nhan 2: Sua nhanvien     Nhan 3: Xoa nhanvien      ";
  gotoxy(3, 26);
  cout << "Nhan 4: Xem danh sach don hang     Nhan ESC: Thoat" << endl;
  fflush(stdin);

  while (1) {
    Normal();
    char c = getch();
    if (c == 0 || c == 224) {
      c = getch();
      c += 128;
    } else if (c == ESC) {
      return;
    } else if (c == KEY_1) {
      Normal();
      NHANVIEN x;
      nhapThongTinNhanVien(t, x, 1);
      themPhanTuVaoTree(t, x);
      getch();
      break;
    } else if (c == KEY_2) {

      getch();
      break;
    } else if (c == KEY_3) {

      getch();
      break;
    } else if (c == KEY_4) {
      	gotoxy(5, 1);
      	int manv;
      	cout << "Nhap ma nhan vien: ";
      	cin >> manv;
		xemDanhSachHoaDon(t, manv, l, dsvt);
      	break;
    }
  }

}

void timNodeTheMang(TREE & X, TREE & Y) {
  if (Y -> pLeft != NULL) {
    timNodeTheMang(X, Y -> pLeft);
  } else {
    X -> data = Y -> data;
    X = Y;
    Y = Y -> pRight;
  }
}

void xoaPhanTuTrongTree(TREE &t, int manv) {
  if (t == NULL) {
    TaoThongBaoVaMat(5, 15, "Danh sach nhan vien rong. Vui long kiem tra lai.");
    return;
  } else {
    if (manv < t->data.Manv) {
      xoaPhanTuTrongTree(t -> pLeft, manv);
    } else if (manv > t->data.Manv) {
      xoaPhanTuTrongTree(t -> pRight, manv);
    } else {
      NODENHANVIEN * X = t;
      if (t -> pLeft == NULL) {
        t = t -> pRight;
      } else if (t -> pRight == NULL) {
        t = t -> pLeft;
      } else {
        timNodeTheMang(X, t -> pRight);
      }
      delete X;
    }
  }
}

//test
void NLR(TREE t) {
  if (t != NULL) {
    cout << t -> data.Manv << " ";
    NLR(t -> pLeft);
    NLR(t -> pRight);
  }
}

TREE timTree(TREE t, int manv) {
  if (t == NULL)
    return NULL;
  if (manv < t->data.Manv) {
    timTree(t->pLeft, manv);
  } else if (manv > t->data.Manv) {
    timTree(t->pRight, manv);
  }
  else return t;
}

void luuDanhSachHoaDonVaoTree(TREE &t, LISTHD &l, int manv){
	if (t == NULL) return;
	if(t != NULL){
		if(manv < t->data.Manv){
			luuDanhSachHoaDonVaoTree(t->pLeft,l,manv);
		}else if(manv > t->data.Manv){
			luuDanhSachHoaDonVaoTree(t->pRight,l,manv);
		}else{
			t->data.dshd = &l;
		}
	}
}

void docMotNhanvien(ifstream &filein, NHANVIEN & x) {
	string tmp;
  	filein >> x.Manv;
  	getline(filein, tmp);
  	filein >>  x.Ho;
	getline(filein, tmp);
  	filein >>  x.Ten;
	getline(filein, tmp);
  	filein >> x.Phai;
  	getline(filein, tmp);
}

void docFileNhanvien(TREE &t) {
  ifstream filein;
  filein.open("NHANVIEN.txt", ios_base:: in );
  if (filein.fail()) {
    cout << "File khong mo duoc. Vui long kiem tra lai.";
    getch();
    return;
  }

  while (filein.eof() == false) {
    NHANVIEN x;
    docMotNhanvien(filein, x);
    themPhanTuVaoTree(t, x);
  }
  filein.close();
  
  //Doc file hoa don
  filein.open("HOADON.txt", ios_base:: in );
  if (filein.fail()) {
    cout << "File khong mo duoc. Vui long kiem tra lai.";
    getch();
    return;
  }
//  while (filein.eof() == false) {
//  		string xuongHang;
//    	int manv;
//	    filein >> manv;
//	   	getline(filein, xuongHang);
//	    int n;
//	    filein >> n;
//	  	getline(filein,xuongHang);
//	  	LISTHD l;
//	  	khoiTaoLISTHD(l); //Khoitao ListHD
//	  	//TREE tmp = timTree(t, manv);
//	    for(int i = 0; i < n; i++){
//	   		NODEHOADON *p = new NODEHOADON; //Cap phat vung nho cho NODEHOADON
//	   		filein >> p->data.SoHD; //char
//	  		getline(filein, xuongHang);
//	   		getline(filein, p->data.Ngay); //string
//	   		filein >> p->data.Loai; //char
//	   		getline(filein, xuongHang);
//	   		themVaoCuoi(l,p);
//		}
//		luuDanhSachHoaDonVaoTree(t, l, manv);
//		
////			if(tmp != NULL){ // Kiem tra neu cay khac null (Co' ma nhan vien)
////	   			tmp->data.dshd = &l; // Tro con tro dshd den dia chi LISTHD
////				// for(NODEHOADON* k = tmp->data.dshd->pHead;k != NULL; k=k->pNext){
////				// cout<<"for "<<k->data.SoHD<<endl;	//Test ra data nhung ket thuc ham` thi` mat'
////				// }
////			}
//	}
	filein.close();
}
