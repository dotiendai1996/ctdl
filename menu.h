#pragma once
#include "vattu.h"
#include "nhanvien.h"
#define MAX_MENU_MAIN 3
using namespace std;

char menumain [MAX_MENU_MAIN][50] = {
							  "1. QUAN LY VAT TU.",
			                  "2. QUAN LY NHAN VIEN.      ",
			                  "3. KET THUC CHUONG TRINH  "};
			                  
// ========================= XU LY MENU VAT TU ======================================
void xuLyMenuVattu(DSVATTU &dsvt){
				int endchar;
				int chonVt = MenuDong(menuvt,MAX_MENU_VATTU);
			switch(chonVt){
				case 1: {
					Normal();
					xuatDanhSachVattu(dsvt);
					break;
				}
				case 2:{
					Normal();
					fflush(stdin);
					VATTU *vt = new VATTU;
					if(nhapThongTinVattu(dsvt,*vt,1)){
					themVattuVaoCuoi(dsvt, *vt);
					ghiFileVATTU(dsvt);
					xuatDanhSachVattu(dsvt);
					}
					break;
				}
				case 3:{
					Normal();
					system("cls");
					return;
				}
				
			}
}

// ================================ XU LY MENU NHAN VIEN ===================================
//void xuLyMenuNhanvien(TREE &t, DSNHANVIEN &dsnv, LISTHD &l, DSVATTU &dsvt){
void xuLyMenuNhanvien(TREE &t, DSNHANVIEN &dsnv, DSVATTU &dsvt){
	int endchar;
				int chonNv = MenuDong(menunv,MAX_MENU_NHANVIEN);
			switch(chonNv){
				case 1: {
					Normal(); //xem lai doc file dang loi x2 nv
//					xuatDanhSachNhanvienTheoMang(t, l, dsvt);
					xuatDanhSachNhanvienTheoMang(t, dsvt);
					break;
				}
				case 2:{
					Normal();
					NHANVIEN x;
					if(nhapThongTinNhanVien(t, x, 1)){
						themPhanTuVaoTree(t,x);
						// ghiFileNHANVIEN(t);
					}
//					xuatDanhSachNhanvienTheoMang(t, l, dsvt);
					xuatDanhSachNhanvienTheoMang(t, dsvt);
					break;
				}
				case 3:{
					Normal();
					system("cls");
					return;
				}
				
			}
}

// ================================ XU LY MENU ====================================
//void xuLyMenu(DSVATTU &dsvt, TREE &t, DSNHANVIEN &dsnv, LISTHD &l){
void xuLyMenu(DSVATTU &dsvt, TREE &t, DSNHANVIEN &dsnv){
while(1){
	int endchar;
		title();
	int chon= MenuDong(menumain,MAX_MENU_MAIN);
	switch(chon){
		case 1:{
			Normal();
			xuLyMenuVattu(dsvt);
			system("cls");
			break;
		}
		case 2:{
			Normal();
//			xuLyMenuNhanvien(t, dsnv, l, dsvt);
			xuLyMenuNhanvien(t, dsnv, dsvt);
			system("cls");
			break;
		}
		case 3:{
			Normal();
			return;
		}
		default:
			break;
		}
	}
}



