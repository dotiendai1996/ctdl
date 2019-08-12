#pragma once
#include "mylib.h"

using namespace std;

#define MAX_VATTU 1000
# define MAX_MENU_VATTU 3

char menuvt[MAX_MENU_VATTU][50] = {
  "1. XEM DANH SACH VAT TU.",
  "2. THEM VAT TU.         ",
  "3. TRO VE MENU CHINH.   "
};

//Khai bao cau truc cua mot phan tu mang
struct vattu {
  char Mavt[11];
  char Tenvt[21];
  char Dvt[11];
  float Soluongton;
};
typedef struct vattu VATTU;

//Danh sach mang con tro chua' vat tu
struct listVattu {
  int n = 0;
  VATTU * nodes[MAX_VATTU];
};
typedef struct listVattu DSVATTU;

//=================== CHECK EMPTY ==========================================
bool checkDsVattuEmpty(DSVATTU ds) {
  return (ds.n == 0 ? true : false);
}

//=================== CHECK FULL ===========================================
bool checkDsVattuFull(DSVATTU ds) {
  return (ds.n == MAX_VATTU ? true : false);
}
// =================== CHECK MAVT EXISTS ====================================
bool checkMavtExist(DSVATTU ds, char *mavt) {
  if (ds.n == 0) return false;
  for (int i = 0; i < ds.n; i++) {
    if (strcmp(ds.nodes[i]->Mavt,mavt) == 0) {
      return true;
    }
  }
  return false;
}

// ==================== NHAP THONG TIN VAT TU ================================
bool nhapThongTinVattu(DSVATTU ds, VATTU & vt, int flg) {
  system("cls");
  cBoard c;
  int x = 3, y = 2; int endchar; 
  c.drawBoard(x, y, 60, 15);
  gotoxy(x + 15, y + 1);
    if (flg == 1) {
    cout << "THEM THONG TIN VAT TU";
    goto NhapMaVattu;
  } else {
    cout << "SUA THONG TIN VAT TU";
    goto NhapTenVattu;
  }

  //Ma vat tu
    NhapMaVattu:
  if (flg == 1) {
   	gotoxy(x + 3, y + 3);
   	cout<<"Nhap ma vat tu:";
	gotoxy(x+23,y+3); cout<<"                                ";
	strcpy(vt.Mavt, Nhap(x+23,y+3,11, endchar));		
	if (endchar==ESC) return false;
	if(!strlen(vt.Mavt)){
	CheckMaRong:	//CheckMaRong
		    SetColor(RED);
    		gotoxy(5,22);
			cout<<"Ma vat tu khong duoc rong. Nhan Enter de nhap lai.";
			endchar = getch();
		if(endchar==ENTER){
			SetColor(YELLOW);
			gotoxy(5,22);
			cout<<"                                                                                 ";
			goto NhapMaVattu;
		}else
			goto CheckMaRong;
	}
	else if (endchar ==ENTER){
		if(checkMavtExist(ds,vt.Mavt) == false){
			goto NhapTenVattu;
		}else{
			CheckMaTrung:	//CheckMaTrung
			    SetColor(RED);
    			gotoxy(5,22);
				cout<<"Ma vat tu da ton tai. Nhan Enter de nhap lai. ";
				endchar = getch();
			if(endchar == ESC) return false;
			if(endchar == ENTER){
				SetColor(YELLOW);
				gotoxy(5,22); 
				cout<<"                                                                               ";
				goto NhapMaVattu;
			}else{
				goto CheckMaTrung;
			}
		}
	}else{
		goto NhapMaVattu;
	}
}else{
	goto NhapTenVattu;
}	
  
  //Ten vat tu		
  NhapTenVattu:
  gotoxy(x + 3, y + 5);
  cout << "Nhap ten vat tu: ";
    gotoxy(x + 23, y + 5);
    cout << "                                ";
    gotoxy(x + 23, y + 5);
    rewind(stdin);
    strcpy(vt.Tenvt, NhapWithSpace(x+23, y+5, 21, endchar));
    if (endchar==ESC) return false;
	if (strlen(vt.Tenvt) == 0) { //CheckTenRong
	CheckTenRong:
		SetColor(RED);
    	gotoxy(5,22);
      	cout<<"Ten vat tu khong duoc rong. Nhan Enter de nhap lai.";
      	endchar = getch();
      	if(endchar == ESC) return false;
      	if(endchar == ENTER){
      		SetColor(YELLOW);
      		gotoxy(5,22);
      		cout<<"                                                                                ";
      		goto NhapTenVattu;
	  }else{
	  	goto CheckTenRong;
	  }
    }else if(endchar == ENTER){
    	goto NhapDonViTinh;
	}
    

  //Don vi tinh
  	NhapDonViTinh:
  	gotoxy(x + 3, y + 7);
  	cout << "Nhap don vi tinh: ";
  	gotoxy(x + 23, y + 7);
    cout << "                                ";
    gotoxy(x + 23, y + 7);
    rewind(stdin);
   	strcpy(vt.Dvt, NhapWithSpace(x+23, y+7, 11, endchar));
    if (endchar==ESC) return false;
    if(strlen(vt.Dvt) == 0){
    	checkDonViTinhRong:
        	SetColor(RED);
    		gotoxy(5,22);
			cout<<"Don vi tinh khong duoc rong. Nhan Enter de nhap lai. ";
			endchar = getch();
			if(endchar == ESC) return false;
			if(endchar==ENTER){
				SetColor(YELLOW);
				gotoxy(5,22); 
				cout<<"                                                                                ";
				goto NhapDonViTinh;
			}else{
				goto checkDonViTinhRong;
			}
	}else if(endchar == ENTER){
		if(flg == 1){
			goto NhapSoLuongTon;
		}else{
			return true;
		}
	}
  //So luong ton
NhapSoLuongTon:
  if (flg == 1) {
    gotoxy(x + 3, y + 9);
    cout << "Nhap so luong ton: ";
     gotoxy(x + 23, y + 9);
      cout << "                                ";
      gotoxy(x + 23, y + 9);
      cin >> vt.Soluongton;
      //	endchar = getch();
      // if (endchar==ESC) return false;
      if(vt.Soluongton < 0 || !cin){
      		checkSoLuongTon: //checkSoLuongTon
      			SetColor(RED);
    			gotoxy(5,22);
				cout<<"So luong ton khong hop le. Nhan Enter de nhap lai. ";
				endchar = getch();
				if(endchar == ESC) return false;
				if(endchar==ENTER){
					cin.clear(); // reset failbit
    				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					gotoxy(5,22);
					cout<<"                                                                                  ";
					goto NhapSoLuongTon;
				}else{
					goto checkSoLuongTon;
				}
	  }else{
	  	return true;
	  }
//	  else if(endchar == ENTER){
//	  	return true;
//	  }else{
//	  	goto NhapSoLuongTon;
//	  }
  }
}

// ============ THEM VAT TU VAO CUOI =======================================
void themVattuVaoCuoi(DSVATTU & ds, VATTU vt) {
  if (!checkDsVattuFull(ds)) {
    ds.nodes[ds.n] = new VATTU;
    *ds.nodes[ds.n] = vt;
    ds.n++;
  } else {
  	    SetColor(RED);
    	gotoxy(5,22);
    	cout<<"Danh sach day, khong the them.";
    	getch();
    	return;
  	}
}

// =============== Hoan vi ===================================================
void hoanViVattu(VATTU *vt1, VATTU *vt2){
	VATTU tmp = *vt1;
	*vt1 = *vt2;
	*vt2 = tmp;
}

// ============== SAP XEP TEN VAT TU =========================================
void sapXepTenVattu(DSVATTU &ds){
	for(int i = 0; i< ds.n-1; i++){
		for(int j = i+1; j <ds.n; j++){
			if(strcmp(ds.nodes[i]->Tenvt,ds.nodes[j]->Tenvt) > 0){
				hoanViVattu(ds.nodes[i], ds.nodes[j]);
			}
		}
	}
}

// ====================== XUAT THONG TIN VAT TU ============================
void xuatThongTinVattu(VATTU vt, int y) {
  gotoxy(9, y);
  cout << vt.Mavt;
  gotoxy(37, y);
  cout << vt.Tenvt;
  gotoxy(63, y);
  cout << vt.Dvt;
  gotoxy(89, y);
  cout << vt.Soluongton;
}

// ============== Khung xuat vat tu =====================================
void khungXuatVattu() {
  int x = 8, y = 5;
  cBoard c;
  c.drawBoard(x, y, 112, 20);
  gotoxy(x + 3, y + 1);
  cout << "Ma vat tu";
  drawDoc(34, y, 34, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "Ten vat tu";
  drawDoc(60, y, 60, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "Don vi tinh";
  drawDoc(86, y, 86, 20);
  gotoxy(wherex() + 3, y + 1);
  cout << "So luong ton";
  drawNgang(8, y + 2, 112, y + 2);

}

// ============== TIM VI TRI VAT TU =====================================
int timViTriVattu(DSVATTU ds, string Mavt) {
  if (!checkDsVattuEmpty(ds)) {
    for (int i = 0; i < ds.n; i++) {
      if (ds.nodes[i] -> Mavt == Mavt) {
        return i;
      }
    }
    SetColor(RED);
    gotoxy(5,22);
    cout<<"Khong tim thay vat tu ban nhap. Vui long kiem tra lai.";
    getch();
    return -1;
  } else {
    SetColor(RED);
    gotoxy(5,22);
    cout<<"Danh sach rong. Vui long kiem tra lai.";
    getch();
    return -1;
  }
}

// ================ XOA VAT TU ====================================
void xoaVattu(DSVATTU & ds, int vitri) {
  	if (!checkDsVattuEmpty(ds)) {
    	for (int i = vitri; i < ds.n - 1; i++) {
      		*ds.nodes[i] = *ds.nodes[i + 1];
    	}
    	delete ds.nodes[ds.n - 1];
    	ds.n--;
    	return;
  	}else {
  		SetColor(RED);
    	gotoxy(5,22);
    	cout<<"Hien khong co vat tu nao. Vui long kiem tra lai.";
    	getch();
    	return;
  	}
}

// =================== SUA VAT TU ==========================================
void suaVattu(DSVATTU & ds, int vitri, VATTU vt) {
  // ds.nodes[vitri]->Mavt = vt.Mavt;
  strcpy(ds.nodes[vitri]->Tenvt, vt.Tenvt);
  strcpy(ds.nodes[vitri]->Dvt, vt.Dvt);
  // ds.nodes[vitri]->Soluongton = vt.Soluongton;
}

// ===================== XUAT DANH SACH VAT TU ===========================================
void ghiFileVATTU(DSVATTU ds);
void xuatDanhSachVattu(DSVATTU &ds) {
  system("cls");
  khungXuatVattu();
  gotoxy(50, 3);
  int x = 11, y = 7;
  sapXepTenVattu(ds);
  for (int i = 0; i < ds.n; i++) {
    gotoxy(x, y + 1);
    y++;
    xuatThongTinVattu(*ds.nodes[i], y); //Con tro nen co * de xuat gia tri ben trong con tro
  }

  gotoxy(3, 25);
  cout << "Nhan 1: Them vat tu      Nhan 2: Sua vat tu     Nhan 3: Xoa vat tu      Nhan ESC: Thoat" << endl;
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
      VATTU * vt = new VATTU;
    	if(nhapThongTinVattu(ds, * vt, 1)){
    		themVattuVaoCuoi(ds, * vt);
    		ghiFileVATTU(ds);
		}
		xuatDanhSachVattu(ds);
      break;
    } else if (c == KEY_2) {
      string Mavt;
      int vitri;
      gotoxy(5, 1);
      cout << "Nhap ma vat tu can sua:";
      getline(cin, Mavt);
      vitri = timViTriVattu(ds, Mavt);
      if (vitri > -1) {
        VATTU * vt = new VATTU;
      	if(nhapThongTinVattu(ds, *vt, 2)){
    		suaVattu(ds, vitri, *vt);
		}
      }
      xuatDanhSachVattu(ds);
      break;
    } else if (c == KEY_3) {
      string Mavt;
      gotoxy(5, 1);
      cout << "Nhap ma vat tu can xoa: ";
      getline(cin, Mavt);
      int vt = timViTriVattu(ds, Mavt);
      if (vt > -1) {
        xoaVattu(ds, vt);
        xuatDanhSachVattu(ds);
      }
      break;
    }
  }
}

// ========== LAY SO LUONG TON ==============================================
int laySlt(DSVATTU ds, char *mavt){
	if(ds.n == 0) return -1;
	for(int i = 0; i<ds.n; i++){
		if(strcmp(mavt, ds.nodes[i]->Mavt) == 0){
			return ds.nodes[i]->Soluongton;
		}
	}
	return -1;
}

// ============ CAP NHAT SO LUONG TON =========================================
void capNhatSoLuongTon(char *mavt, DSVATTU &ds, float sl, int flg){
	if(flg == 1){
		for(int i = 0; i < ds.n; i++){
			if(strcmp(ds.nodes[i]->Mavt,mavt) == 0){
				ds.nodes[i]->Soluongton = ds.nodes[i]->Soluongton + sl;
			}
		}
	}else if(flg == 2){
				for(int i = 0; i < ds.n; i++){
			if(strcmp(ds.nodes[i]->Mavt,mavt) == 0){
				ds.nodes[i]->Soluongton = ds.nodes[i]->Soluongton - sl;
			}
		}
	}
}

// ================== DOC FILE ===========================================
void docFileVattu(DSVATTU & ds) {
  ifstream filein;
  filein.open("VATTU.txt", ios_base:: in );
  if (filein.fail()) {
  	SetColor(RED);
    gotoxy(5,22);
    cout << "File khong mo duoc. Vui long kiem tra lai.";
    getch();
    return;
  }
  while (true) {
    VATTU vt;
    string tmp;
    filein >> vt.Mavt;
    getline(filein, tmp);
   	filein >> vt.Tenvt;
    getline(filein, tmp);
    filein >> vt.Dvt;
    getline(filein, tmp);
    filein >> vt.Soluongton;
    getline(filein, tmp);
    themVattuVaoCuoi(ds, vt);
    if (filein.eof() == true) {
      break;
    }
  }
  filein.close();
}

void ghiFileVATTU(DSVATTU ds){
	fstream f("VATTU.txt", ios::out | ios::trunc);
	string xuongHang;
	for(int i = 0; i<ds.n; i++){
		f << ds.nodes[i]->Mavt << endl;
		f << ds.nodes[i]->Tenvt << endl;
		f << ds.nodes[i]->Dvt << endl;
		if(i < ds.n-1){
			f << ds.nodes[i]->Soluongton<<endl;
		}else if(i == ds.n-1){
			f << ds.nodes[i]->Soluongton;
		}
	}
	f.close();
}

//Ham giai phong vung nho
void giaiPhong(DSVATTU & ds) {
  for (int i = 0; i < ds.n; i++) {
    delete ds.nodes[i];
  }
}
