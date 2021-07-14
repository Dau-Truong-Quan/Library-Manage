﻿#pragma once
#include <string>
#include "Date.h"
#include "DauSach.h"
using namespace std;

int trangDMSHienTai = 1;
int soLuongTrangDMS = 0;
string cotDMS[4] = { "STT", "Ma sach", "Trang thai", "Vi tri" };
//=====DANH MỤC SÁCH=====
struct danhmucsach
{
	string masach;
	int trangthai; // =0 cho mượn được, =1 đã có độc giả mượn, =2 sách đã thanh lí
	string vitri;
};

struct node_DMS
{
	danhmucsach data;
	node_DMS* next;
};
typedef node_DMS* PTR_DMS;

//=====Khai báo các thuật toán=====
void khoiTaoDMS(PTR_DMS& First);
node_DMS* taoNodeDMS(danhmucsach& x);
void themLastDMS(PTR_DMS& First, node_DMS* p);
void inDMS(PTR_DMS First);
void taoHangNhap(int x, int y, string content, int length);
void taoBangNhap(string title, string content[], int StartIndex, int nContent, int length);
void menuDanhMucSach(PTR_DMS First, int slsach);
void menuChonDanhMucSach(PTR_DMS First, int slsach);

//=====CÁC THUẬT TOÁN=====

//Khởi tạo danh sách danh mục sách
void khoiTaoDMS(PTR_DMS& First)
{
	First = NULL;
}
// tạo 1 node mới 
node_DMS* taoNodeDMS(danhmucsach& x)
{
	node_DMS* p = new node_DMS;
	p->data = x;
	p->next = NULL;
	return p;
}
//Thêm sách vào danh mục sách để quản lí
void themLastDMS(PTR_DMS& First, node_DMS* p)
{
	if (First == NULL)
	{
		First = p;
	}
	else
	{
		PTR_DMS q = First;
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
	}
}
void inDMS(PTR_DMS First)
{
	int stt = 0;
	string trangThai = "";
	for (PTR_DMS q = First; q != NULL; q = q->next)
	{
		cout << setfill(' ') << char(176) << setw(5) << left << ++stt;
		cout << char(176) << setw(20) << left << q->data.masach;
		if (q->data.trangthai == 0)
			trangThai = "Cho muon duoc";
		else if (q->data.trangthai == 1)
			trangThai = "Da co nguoi muon";
		else trangThai = "Da thanh ly";
		cout << char(176) << setw(30) << left << trangThai;
		cout << char(176) << setw(20) << left << q->data.vitri << char(176) << endl;
	}
}

//Tao 1 hang nhap thong tin
void taoHangNhap(int x, int y, string content, int length)
{
	gotoxy(x - 2, y - 1);
	cout << char(176) << setw(length) << setfill(char(176)) << char(176) << char(176);

	gotoxy(x - 2, y);
	cout << char(176) << content << setw(length - content.length() + 1) << setfill(' ') << char(176);
}
//Tao 1 bang nhap thong tin
void taoBangNhap(string title, string content[], int StartIndex, int nContent, int length)
{
	gotoxy(X_Add - 2, Y_Add - 2);
	cout << title;
	int yAdd = Y_Add;
	for (int i = StartIndex; i < nContent; i++)
	{
		taoHangNhap(X_Add, yAdd, content[i], length);
		yAdd += 2;
	}
	gotoxy(X_Add - 2, yAdd - 1);
	cout << char(176) << setw(length) << setfill(char(176)) << char(176) << char(176);
}

void menuXemDanhMucSach(PTR_DMS First, int slsach)
{
	soLuongTrangDMS = (int)ceil((double)slsach / NumberPerPage);
	cout << setfill(char(176)) << setw(80) << "" << endl;
	cout << char(176) << setfill(' ') << left << setw(5) << "STT" << char(176) << setw(20) << "Ma sach" << char(176) << setw(30) << "Trang thai" << char(176) << setw(20) << "Vi tri" << char(176) << endl;
	cout << setfill(char(176)) << setw(80) << "" << endl;
	//veBang(cotDMS, 4);
	inDMS(First);
	int signal;
	while (true)
	{
		while (_kbhit())
		{
			signal = _getch();
			if (signal == ESC)
				return;
		}
	}
}

void menuChonDanhMucSach(PTR_DMS First, int slsach)
{
	
}