﻿#pragma once
#include "mylib.h"
#include "HangSo.h"
#include "DauSach.h"
#include "DocGia.h"
#include <iostream>
#include <conio.h> //hàm getch()
#include <iomanip> //setw và setfill
#include <fstream>
#include <string.h>
#include <string>
//void NormalLine();
//void HighlightLine();
void DrawTable();
int menu_dong(string ThucDon[], int n, int x, int y);
void introduce();
void CenterMenu();

using namespace std;
string ThucDon[MaxItem] = {
					   "1. Quan ly doc gia               ",
					   "2. Quan ly dau sach              ",
					   "3. Quan ly muon tra              ",
					   "4. Danh sach doc gia muon qua han",
					   "5. Top 10 sach muon nhieu nhat   ",
					   "0. Thoat Chuong Trinh            "
};
string MenuDG[slItemDG] = {
					   "1. XUAT DANH SACH THEO MA               ",
					   "2. XUAT DANH SACH THEO TEN              ",
					   "0. THOAT                                "
};


/*============== CENTER MENU =============*/

//Ve vien bang menu
void DrawTable()
{
	gotoxy(X_TitlePage, Y_TitlePage + 1);
	cout << "CHUC NANG CHINH";
	/*      "HOC VIEN CONG NGHE BUU CHINH VIEN THONG CO SO THANH PHO HO CHI MINH"*/
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[2] - 12; i < 122; i++)
	{

		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display - 2);
		cout << char(176);

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 1);
		cout << char(176);

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 19 + 3);
		cout << char(176);
	}

	for (int j = Y_Display; j < Y_Display + 25; j++)
	{
		gotoxy(xKeyDisplay[2] - 12, j - 2);
		cout << char(176);

		gotoxy(122, j - 2);
		cout << char(176);
	}
}

void introduce()
{
	ShowCur(false);
	string temp;
	ifstream file("introduce.txt", ios::in);
	SetColor(ColorCode_Blue);
	if (file.good())
	{
		while (file.eof() == false)
		{
			getline(file, temp);
			//Sleep(80);
			cout << temp << endl;
		}
	}
	else
	{
		cout << " \n Liet ket file that bai " << endl;
	}

	ShowCur(false);
	gotoxy(50, 34);
	SetBGColor(ColorCode_Black);
	SetColor(ColorCode_Red);
	cout << "Nhan ENTER de tiep tuc!!!! ";
	SetBGColor(ColorCode_Black);

	string content[] = { "Dau Truong Quan          | N18DCCN162",
						 "Nguyen Ngoc Phuong Trinh | N18DCCN231" };

	int x = 100;
	int y = 4;
	int length = 40;
	for (int i = 0; i < 2; i++)
	{

		gotoxy(x - 2, y - 1);
		cout << char(176) << setw(length) << setfill(char(176)) << char(176) << char(176);

		gotoxy(x - 2, y);
		cout << char(176) << content[i] << setw(length - content[i].length() + 1) << setfill(' ') << char(176);
		y += 2;
	}
	gotoxy(x - 2, y - 1);
	cout << char(176) << setw(length) << setfill(char(176)) << char(176) << char(176);
	gotoxy(98, 2);
	cout << "Thanh vien gia dinh";
	while (!_kbhit()) {
		gotoxy(45, 32);
		SetColor(1 + rand() % 15);
		Sleep(100);
		cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG CO SO TP HO CHI MINH";
	}

	cin.ignore();
	return;
}

//tao menu dong, ThucDon: các lựa chọn, n: số lượng các lựa chọn, x, y: vị trí đặt menu
int menu_dong(string ThucDon[], int n, int x, int y)
{
	// xuat menu
	ShowCur(false);// an con tro nhap nhay di
	NormalLine();
	system("cls");
	DrawTable();
	for (int i = 0; i < n; i++)
	{

		gotoxy(x, y + i * 2);
		cout << ThucDon[i];
	}
	// to mau cho dong duoc chon
	int pointer = 0; // vi tri hien tai cua thanh sang
	gotoxy(x, y + pointer * 2);
	HighlightLine();
	cout << ThucDon[pointer];
	NormalLine();
	// dieu khien chuc nang
	char signal;
	while (true)
	{
		signal = _getch();// kiem tra xem co nhap gi tu ban phim khong
		if (signal == -32)
		{
			signal = _getch();
		}
		// dieu huong
		switch (signal)
		{
		case KEY_UP:
			if (pointer + 1 > 1)
			{
				// tro ve mau cu
				NormalLine();
				gotoxy(x, y + pointer * 2);
				cout << ThucDon[pointer];
				pointer--;// cap nhat lai vi tri 
				// vi tri thanh sang
				HighlightLine();
				gotoxy(x, y + pointer * 2);
				cout << ThucDon[pointer];
				NormalLine();
			}
			break;
		case KEY_DOWN:
			if (pointer + 1 < n)
			{
				NormalLine();
				gotoxy(x, y + pointer * 2);
				cout << ThucDon[pointer];
				pointer++;
				HighlightLine();
				gotoxy(x, y + pointer * 2);
				cout << ThucDon[pointer];
				NormalLine();
			}
			break;
		case ENTER:// lua lai ket qua de thuc hien lenh tuong ung voi CenterMenu
			return pointer + 1;
		case ESC:
			return -1;
		}
	}
}

void CenterMenu()
{
	LIST_DS l;
	TREE_DG dsDG;
	khoiTaoDS(l);
	khoiTaoDG(dsDG);
	docFileDS(l);
	docFileDG(dsDG);
	introduce();

	system("cls");
	int pointer;

	bool Exit = false;// false nghia la chua thoat, van dang dung
	
	while (Exit == false)
	{		
		pointer = menu_dong(ThucDon, MaxItem, X_CenterMenu, Y_CenterMenu);
		system("cls");
		switch (pointer)
		{
			case 1:
			{
				bool vongLap = true;
				while (vongLap)
				{
					int luaChon = menu_dong(MenuDG, slItemDG, X_CenterMenu, Y_CenterMenu);					
					system("cls");
					system("color 0B");
					switch (luaChon)
					{
					case 1:
					{
						dieuChinhDocGia(dsDG,false);
					}
					break;
					case 2:
					{
						dieuChinhDocGia(dsDG, true);
					}
					break;
					default:
						vongLap = false;
						break;						
					}
				}
				break;
			}
			case 2:
				SetColor(11);
				menuDauSach(l, dsDG);
				break;
			case 3:
			{
				system("color 0B");
				quanLiMuonTra(dsDG, l,true);
				break;
			}
			case 4:
			{
				system("color 0B");
				quanLiMuonTra(dsDG, l, false);		// danh sách độc giả mượn quá hạn
				break;
			}
			case 5:
				system("color 0B");
				top10SachMuon(l);
				break;
			case MaxItem:
				giaiphong_cay(dsDG);
				giaiphong_dausach(l);
				system("color 0B");
				Exit = true;
				system("cls");
				break;
		}
	}
}
/* ========== END CENTER MENU =========== */
