#pragma once
#include <iostream>
#include "menu.h"
using namespace std;

void LRN(TREE t, int manv){
	if(manv < t->data.Manv){
		LRN(t->pLeft, manv);
	}
	if(manv > t->data.Manv){
		LRN(t->pRight, manv);
	}
						 for(NODEHOADON* k = t->data.dshd->pHead;k != NULL; k=k->pNext){
					 cout<<"for "<<k->data.SoHD<<endl;	//Test ra data nhung ket thuc ham` thi` mat'
					 }
}

int main() {
	remove("main.o");
	DSVATTU dsvt;
	docFileVattu(dsvt);
	TREE t;
	khoiTaoTree(t);
	DSNHANVIEN dsnv;
	LISTHD l;
	khoiTaoLISTHD(l);
	docFileNhanvien(t);
	xuLyMenu(dsvt, t, dsnv, l);
	giaiPhong(dsvt);
	return 0;
}
