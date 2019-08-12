#pragma once
#include <iostream>
#include "menu.h"
using namespace std;

int main() {
	remove("main.o");
	DSVATTU dsvt;
	docFileVattu(dsvt);
	TREE t;
	khoiTaoTree(t);
	DSNHANVIEN dsnv;
//	LISTHD l;
//	khoiTaoLISTHD(l);
	docFileNhanvien(t);
//	xuLyMenu(dsvt, t, dsnv, l);
	xuLyMenu(dsvt, t, dsnv);
	giaiPhong(dsvt);
	return 0;
}
