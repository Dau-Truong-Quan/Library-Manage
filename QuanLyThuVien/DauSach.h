﻿#pragma once
#include "HamNhap.h"
#include "HangSo.h"
#include "HienThi.h"
#include "DanhMucSach.h"
#include "mylib.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define MAX 300 //số lượng đầu sách tối đa

// thong tin vi tri hien tai
int trangDSHienTai = 1;
int soLuongTrangDS = 0;
int xKeyDisplay[8] = { 1, 8, 23, 58, 73, 93, 113, 135 };// toa do X cac diem nut
string thongTinDS[7] = { "STT", "ISBN", "Ten sach", "So trang", "Tac gia", "Nam xuat ban", "The loai" };
string thongTinDMS[4] = { "ISBN", "So luong sach can them", "Ma sach", "Vi tri"};

//=====ĐẦU SÁCH=====
struct dausach
{
	string ISBN; // mã sách theo chuẩn quốc tế
	string tensach;
	int sotrang;
	string tacgia;
	int namxuatban;
	string theloai;
	int soluotmuon; // biến lưu trữ số lần mượn sách của độc giả dùng để thống kê sách mượn nhiều nhất
	PTR_DMS dms; // con trỏ trỏ đến các sách thuộc đầu sách tương ứng
};

struct list_dausach
{
	int n;
	dausach* ds[MAX];
};
typedef struct list_dausach LIST_DS;

//Khai bao de sap xep giu nguyen index
struct indexTheLoai
{
	int chiso;
	char theloai[50];
	char tensach[50];
};

struct listTheLoai {
	int n;
	indexTheLoai* nodes;
};

//=====Khai bao cac thuat toan=====
void khoiTaoDS(LIST_DS& l);
int themMotDS(LIST_DS& l, dausach s);
void nhapDS(LIST_DS& l);
int timKiemDauSachTheoMa(LIST_DS l, string maDauSach);
void xoaNoiDungCu(int nContent, int locate);
void inMotDS(dausach* s, int position, int StartIndex);
void veBang(string content[], int nContent);
void xoaNoiDungBiDu(int count, int nContent);
void inMotTrangDS(LIST_DS l, int StartIndex);
void chuyenTrangDS(LIST_DS l);
void docFileDS(LIST_DS& l);
void ghiFileDS(LIST_DS l);
void menuDauSach(LIST_DS& l);
int demSoLuongSach(dausach x);
int menu_xoa(int x, int y);
void sapXepGiuNguyenIndex(LIST_DS& l, listTheLoai& listIndex);
string tachMaSach(string masach);
PTR_DMS timKiemDanhMucSach(LIST_DS l, string masach);

//=====CÁC THUẬT TOÁN=====

//Khởi tạo danh sách đầu sách
void khoiTaoDS(LIST_DS& l)
{
	l.n = 0;
}
//Thêm một đầu sách
int themMotDS(LIST_DS& l, dausach s)
{
	// nếu còn thêm được
	if (l.n < MAX)
	{
		l.ds[l.n] = new dausach;
		*l.ds[l.n] = s;
		khoiTaoDMS(l.ds[l.n]->dms);
		l.n++;
		return 1;
	}
	else return 0;
}
void NormalLine()
{
	SetColor(11);// aqua
	SetBGColor(0);// black
}
// dong dang chon
void HighlightLine()
{
	SetColor(0);// black
	SetBGColor(11);// aqua     
}
int menu_xoa(int x, int y)
{
	// return 0 la yes - dong y, return 1 la no - tu choi
	ShowCur(false);
	NormalLine();

	gotoxy(x, y);
	cout << "Ban co chac chan muon xoa khong?";

	char Option[2][10] = { "Co   ",
						   "Khong" };
	for (int i = 0; i < 2; i++)
	{
		gotoxy(x, y + i * 2 + 2);
		cout << Option[i];
	}
	int pointer = 0;

	gotoxy(x, y + pointer * 2 + 2);
	HighlightLine();
	cout << Option[pointer];
	char signal;

	while (true)
	{
		signal = _getch();
		if (signal == 224)
			signal = _getch();
		switch (signal)
		{
		case KEY_UP:
			if (pointer > 0)
			{
				NormalLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
				pointer--;
				HighlightLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
			}
			break;
		case KEY_DOWN:
			if (pointer < 1)
			{
				NormalLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
				pointer++;
				HighlightLine();
				gotoxy(x, y + pointer * 2 + 2);
				cout << Option[pointer];
			}
			break;
		case ENTER:
			NormalLine();
			for (int i = 0; i < 3; i++)
			{
				gotoxy(x, y + i * 2);
				cout << setw(50) << setfill(' ') << "";
			}
			return pointer;
		}
	}// while(true)
}

void xoaDSTheoMa(LIST_DS& l, string ma) {
	int i = timKiemDauSachTheoMa(l, ma);
	if (i == -1) return;
	else
	{
		delete  l.ds[i];
		for (int j = i + 1; j < l.n; j++)
			l.ds[j - 1] = l.ds[j];

		l.n--;
	}
}

void xoaThongTinBangNhap()
{
	gotoxy(X_Add + 12, 1 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 2 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 3 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 4 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
	gotoxy(X_Add + 12, 5 * 2 + Y_Add);
	cout << setw(30) << setfill(' ') << "";
}

//hiện thông tin đầu sách vào bảng nhập
void hienThongTinDS(dausach s)
{
	gotoxy(X_Add + 12, 1 * 2 + Y_Add);
	cout << s.tensach;
	gotoxy(X_Add + 12, 2 * 2 + Y_Add);
	cout << s.sotrang;
	gotoxy(X_Add + 12, 3 * 2 + Y_Add);
	cout << s.tacgia;
	gotoxy(X_Add + 12, 4 * 2 + Y_Add);
	cout << s.namxuatban;
	gotoxy(X_Add + 12, 5 * 2 + Y_Add);
	cout << s.theloai;
}

//Nhập thông tin đầu sách, flag = 0 : thêm mới, flag = 1 : xóa, flag = 2: chỉnh sửa
void nhapDS(LIST_DS& l, int flag)
{
	dausach s;	
	string soTrang;
	string namxb;
	int viTri = 0;// so thu tu bat dau nhap
	int kt;
	int khoangCach = 12;
	int stt = -2;
	ShowCur(true);
	while (true)
	{
		switch (viTri)
		{
			case 0:
			{			
				kt = nhap_ki_tu(s.ISBN, 2, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (kt == KEY_UP) break;
				stt = timKiemDauSachTheoMa(l, s.ISBN);
				if (flag == 0) //trường hợp nhập mới
				{
					xoaThongBao();
					if (stt != -1)
					{						
						inThongBao("Ma ISBN bi trung!");
						break;
					}					
				}
				if (flag == 1) //trường hợp xóa đầu sách
				{					
					xoaThongBao();
					if (stt == -1)
					{						
						inThongBao("Dau sach khong ton tai!");
						break;
					}		
					xoaThongTinBangNhap();
					hienThongTinDS(*l.ds[stt]);
					if (demSoLuongSach(*l.ds[stt]) == 0)
					{
						int luaChon = menu_xoa(X_Notification, Y_Notification + 1);
						if (luaChon == 0) // Có
						{
							xoaDSTheoMa(l, s.ISBN);
							ghiFileDS(l);
							xoaBangNhap();
							soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
							inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
							inThongBao("Xoa thanh cong!");
							return;
						}
						else
						{
							ShowCur(true);
							break;
						}
					}
					else
					{
						xoaThongBao();
						inThongBao("Dau sach nay dang co sach, khong the xoa!");
						ShowCur(true);
						break;
					}
				}
				if (flag == 2)
				{					
					xoaThongBao();
					if (stt == -1)
					{
						inThongBao("Dau sach khong ton tai!");
						break;
					}
					xoaThongTinBangNhap();
					s = *l.ds[stt];
					soTrang = to_string(l.ds[stt]->sotrang);
					namxb = to_string(l.ds[stt]->namxuatban);
					hienThongTinDS(s);					
				}
				viTri++;
				break;
			}
			case 1:
			{
				xoaThongBao();
				kt = nhap_ki_tu(s.tensach, 1, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (flag == 0 && kt == KEY_UP)
				{
					xoaThongBao();
					viTri--;
					break;
				}
				else if (flag == 2 && kt == KEY_UP) break;
				else
				{
					viTri++;
					break;
				}
			}
			case 2:
			{
				xoaThongBao();
				kt = nhap_ki_tu(soTrang, 2, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (kt == KEY_UP)
				{
					viTri--;
					break;
				}
				viTri++;				
				break;
			}
			case 3:
			{
				xoaThongBao();
				kt = nhap_ki_tu(s.tacgia, 0, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (kt == KEY_UP)
				{
					viTri--;
					break;
				}
				viTri++;
				break;
			}
			case 4:
			{
				xoaThongBao();
				kt = nhap_ki_tu(namxb, 2, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (kt == KEY_UP)
				{
					viTri--;
					break;
				}				
				viTri++;
				break;
			}
			case 5:
			{
				xoaThongBao();
				kt = nhap_ki_tu(s.theloai, 0, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				if (kt == KEY_UP)
				{
					viTri--;
					break;
				}
				s.sotrang = atoi(soTrang.c_str());
				s.namxuatban = atoi(namxb.c_str());
				if (flag == 0) //trường hợp nhập mới đầu sách
				{
					s.soluotmuon = 0;
					themMotDS(l, s);					
					xoaThongBao();
					inThongBao("Them dau sach thanh cong");
					
				}
				if (flag == 2) //trường hợp chỉnh sửa đầu sách
				{
					*l.ds[stt] = s;
					xoaThongBao();
					inThongBao("Sua dau sach thanh cong");
				}	
				xoaBangNhap();
				ghiFileDS(l);
				soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
				inMotTrangDS(l, (trangDSHienTai - 1)* NumberPerPage);
				return;
			}
		}
	}
}

//Nhập thông tin sách
void nhapDMS(LIST_DS& l)
{	
	int i; //vị trí đầu sách trong mảng
	int n = 0; //số lượng sách cần thêm mà người dùng nhập vào	
	string chuoinhap; //chuỗi người dùng nhập vào
	int viTri = 0;// so thu tu bat dau nhap	
	int kt;
	int khoangCach = 25;
	ShowCur(true);
	while (true)
	{
		switch (viTri)
		{
			case 0:
			{
				kt = nhap_ki_tu(chuoinhap, 2, viTri, khoangCach);//nhập mã isbn
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				i = timKiemDauSachTheoMa(l, chuoinhap);
				if (i == -1)
				{
					xoaThongBao();
					inThongBao("Dau sach nay khong ton tai!");
					break;
				}					
				xoaThongBao();
				viTri++;
				chuoinhap = "";
				break;
			}
			case 1:
			{
				kt = nhap_ki_tu(chuoinhap, 2, viTri, khoangCach); //nhập số lượng
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return;
				}
				n = atoi(chuoinhap.c_str());
				viTri++;
				break;
			}
			case 2:
			{
				danhmucsach x;
				int stt = 1; //stt mã sách
				if (l.ds[i]->dms != NULL)
				{
					PTR_DMS q = l.ds[i]->dms;
					while (q->next != NULL)
					{
						q = q->next;
					}
					x.vitri = q->data.vitri; // lấy vị trí cuối cùng của sách đã tồn tại
					int pos = q->data.masach.find("-"); // lấy vị trí của kí tự - trong chuỗi
					string str = q->data.masach.substr(pos + 1); //  lấy chuỗi con của q->data.masach bắt đầu sau kí tự '-'
					stt += atoi(str.c_str()); //chuyển chuỗi sang số
				}
				for (int j = 0; j < n; j++)
				{
					x.masach = l.ds[i]->ISBN + "-" + to_string(stt + j);
					gotoxy(X_Add + khoangCach, viTri * 2 + Y_Add);
					cout << x.masach;
					kt = nhap_ki_tu(x.vitri, 1, viTri + 1, khoangCach); //chỉ nhập kí tự và số
					if (kt == -1) // ESC
					{
						xoaBangNhap();
						xoaThongBao();
						return;
					}
					x.trangthai = 0; // mặc định sách có thể mượn được
					themLastDMS(l.ds[i]->dms, taoNodeDMS(x));
				}
				ghiFileDS(l);
				xoaThongBao();
				inThongBao("Them sach thanh cong!");
				xoaBangNhap();
				return;
			}			
		}
	}
}

//Tìm kiếm đầu sách theo mã đầu sách nếu có trả về vị trí, nếu không trả về -1
int timKiemDauSachTheoMa(LIST_DS l, string maDauSach)
{ 
	for (int i = 0; i < l.n; i++)
	{
		if (maDauSach.compare(l.ds[i]->ISBN) == 0)
			return i;
	}
	return -1;
}

//Xóa nội dung trang trước
void xoaNoiDungCu(int nContent, int locate)
{
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 3 + locate * 3);
		cout << setw(xKeyDisplay[i + 1] - xKeyDisplay[i] - 3) << setfill(' ') << "";
	}
}

void swap(indexTheLoai& x, indexTheLoai& y)
{
	indexTheLoai temp = x;
	x = y;
	y = temp;
}

void sapxep(listTheLoai& list, int l, int r)
{
	string x;
	int i, j;
	i = l;
	j = r;
	x = list.nodes[(l + r) / 2].theloai;
	do
	{
		while (list.nodes[i].theloai < x)i++;
		while (list.nodes[j].theloai > x)j--;
		if (i <= j)
		{
			swap(list.nodes[i], list.nodes[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j)sapxep(list, l, j);
	if (i < r)sapxep(list, i, r);
}
void quickSort(listTheLoai& list, int n)
{
	sapxep(list, 0, n - 1);
}
void Insertion_sort(listTheLoai& list, int n)
{
	indexTheLoai x;
	int i, j;
	for (i = 1; i < n; i++)
	{
		x = list.nodes[i];
		for (j = i - 1; j >= 0 && x.theloai < list.nodes[j].theloai; j--)
			list.nodes[j + 1] = list.nodes[j];
		list.nodes[j + 1] = x;
	}
}


//sắp xếp đầu sách giữ nguyên index
void sapXepGiuNguyenIndex(LIST_DS& l, listTheLoai& listIndex)
{
	listIndex.nodes = new indexTheLoai[l.n];
	listIndex.n = l.n;
	for (int i = 0; i < l.n; i++)
	{
		listIndex.nodes[i].chiso = i;
		strcpy(listIndex.nodes[i].theloai, l.ds[i]->theloai.c_str());
		strcpy(listIndex.nodes[i].tensach, l.ds[i]->tensach.c_str());
	}
	for (int i = 0; i < l.n - 1; i++)
		for (int j = i + 1; j < l.n; j++)
			if (strcmp(listIndex.nodes[j].theloai, listIndex.nodes[i].theloai) < 0)
				swap(listIndex.nodes[j], listIndex.nodes[i]);
			else if (strcmp(listIndex.nodes[j].theloai, listIndex.nodes[i].theloai) == 0)
				if (strcmp(listIndex.nodes[j].tensach, listIndex.nodes[i].tensach) < 0)
					swap(listIndex.nodes[j], listIndex.nodes[i]);
}

//in đầu sách
void inMotDS(dausach* s, int position, int StartIndex)
{
	xoaNoiDungCu(sizeof(thongTinDS) / sizeof(string), position);// xoa dong noi dung cu truoc do
	gotoxy(xKeyDisplay[0], Y_Display + 3 + position * 3); cout << char(176) << "  " << position + StartIndex + 1;
	gotoxy(xKeyDisplay[1], Y_Display + 3 + position * 3); cout << char(176) << "  " << s->ISBN;
	gotoxy(xKeyDisplay[2], Y_Display + 3 + position * 3); cout << char(176) << "  " << s->tensach;
	gotoxy(xKeyDisplay[3], Y_Display + 3 + position * 3); cout << char(176) << "  " << s->sotrang;
	gotoxy(xKeyDisplay[4], Y_Display + 3 + position * 3); cout << char(176) << "  " << s->tacgia;
	gotoxy(xKeyDisplay[5], Y_Display + 3 + position * 3); cout << char(176) << "  " << s->namxuatban;
	gotoxy(xKeyDisplay[6], Y_Display + 3 + position * 3); cout << char(176) << "  " << s->theloai;
	for (int i = 0; i < 7 + 1; i++)
	{
		gotoxy(xKeyDisplay[i], Y_Display + 1 + position * 3);
		cout << char(176);
		gotoxy(xKeyDisplay[i], Y_Display + 2 + position * 3);
		cout << char(176);
		gotoxy(xKeyDisplay[i], Y_Display + 3 + position * 3);
		cout << char(176);
	}
}

void veBang(string content[], int nContent)// ve bang 
{
	system("color 0B");
	SetColor(11);
	SetBGColor(0);
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < nContent; i++)
	{// Y_Display 3
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 1);
		cout << content[i];
	}

	//ve cac duong thang de phan chia cac cot
	/*for (int j = Y_Display; j <= Y_Display + 20; j++)
	{
		for (int i = 0; i < nContent + 1; i++)
		{
			gotoxy(xKeyDisplay[i], j);
			cout << char(176);
		}
	}*/
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display);
		cout << char(176);

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		cout << char(176);

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 19);
		cout << char(176);
	}

	//SetColor(6);
	cout << endl;
	gotoxy(X_Tutorial, Y_Tutorial);
	cout << " Huong dan ";
	gotoxy(X_Tutorial, Y_Tutorial + 2);
	cout << " Page Up: Len";
	gotoxy(X_Tutorial, Y_Tutorial + 3);
	cout << " Page Down: Xuong";
	gotoxy(X_Tutorial, Y_Tutorial + 4);
	cout << " Insert: Them dau sach";
	gotoxy(X_Tutorial, Y_Tutorial + 5);
	cout << " Delete: Xoa";
	gotoxy(X_Tutorial, Y_Tutorial + 6);
	cout << " F4: Sua dau sach";
	gotoxy(X_Tutorial, Y_Tutorial + 7);
	cout << " F1: Tim kiem";
	gotoxy(X_Tutorial, Y_Tutorial + 8);
	cout << " Home: Them sach";
	gotoxy(X_Tutorial, Y_Tutorial + 9);
	cout << " ESC: Tro ve";
	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Quan ly dau sach";

	//SetColor(12);
	gotoxy(X_Notification, Y_Notification);	
	cout << " Thong Bao ";
	//NormalLine();
}

//Xóa nội dung bị dư trong bảng cuối cùng, nContent - so luong cột có trong bang do
void xoaNoiDungBiDu(int count, int nContent)
{
	if (count < NumberPerPage)
	{
		for (int i = count; i < NumberPerPage; i++)
		{
			for (int y = 0; y < nContent; y++)
			{
				gotoxy(xKeyDisplay[y] + 3, Y_Display + 3 + i * 3);
				cout << setw(xKeyDisplay[y + 1] - xKeyDisplay[y] - 3) << setfill(' ') << "";
			}
		}
	}
}

void inMotTrangDS (LIST_DS l, int StartIndex)
{
	int cs;
	listTheLoai listTL;
	sapXepGiuNguyenIndex(l, listTL);
	gotoxy(1, 2);
	cout << " So luong dau sach : " << l.n;
	int i;
	for (i = 0; i + StartIndex < l.n && i < NumberPerPage; i++)
	{
		cs = listTL.nodes[i + StartIndex].chiso;
		inMotDS(l.ds[cs], i, StartIndex);
	}
	xoaNoiDungBiDu(i, sizeof(thongTinDS) / sizeof(string)); //hàm này để xóa những nội dung cũ ở trang trước trang cuối cùng, nếu trang cuối cùng không đầy
	gotoxy(X_Page, Y_Page);
	cout << setw(20) << setfill(' ') << "";
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << trangDSHienTai << "/" << soLuongTrangDS;
	delete[] listTL.nodes;
}

// đếm số lượng sách có thuộc 1 đầu sách
int demSoLuongSach(dausach x)
{
	int n = 0;
	for (PTR_DMS p = x.dms; p != NULL; p = p->next)
		n++;
	return n;
}

void ghiFileDS(LIST_DS l)
{
	ofstream f("DAUSACH.txt");
	f << l.n << endl;
	for (int i = 0; i < l.n; i++)
	{
		f << l.ds[i]->ISBN << ',';
		f << l.ds[i]->tensach << ',';
		f << l.ds[i]->sotrang << ',';
		f << l.ds[i]->tacgia << ',';
		f << l.ds[i]->namxuatban << ',';
		f << l.ds[i]->theloai << ',';
		f << l.ds[i]->soluotmuon << endl;
		f << demSoLuongSach(*l.ds[i]) << endl;
		for (PTR_DMS p = l.ds[i]->dms; p != NULL; p = p->next)
		{
			f << p->data.masach << ',';
			f << p->data.trangthai << ',';
			f << p->data.vitri << endl;
		}
	}
	f.close();
}

void docFileDS(LIST_DS& l)
{
	dausach data;
	danhmucsach x;
	ifstream file("DAUSACH.txt");
	int sl_dausach;
	int sl_dms;	
	file >> sl_dausach;
	file.ignore();
	for (int i = 0; i < sl_dausach; i++)
	{
		getline(file, data.ISBN, ',');
		getline(file, data.tensach, ',');
		file >> data.sotrang;
		file.ignore();
		getline(file, data.tacgia, ',');
		file >> data.namxuatban;
		file.ignore();
		getline(file, data.theloai, ',');
		file >> data.soluotmuon;
		file.ignore();
		file >> sl_dms;
		file.ignore();
		themMotDS(l, data);
		int vitri = timKiemDauSachTheoMa(l, data.ISBN);
		for (int i = 0; i < sl_dms; i++)
		{
			getline(file, x.masach, ',');
			file >> x.trangthai;
			file.ignore();
			getline(file, x.vitri);
			themLastDMS(l.ds[vitri]->dms, taoNodeDMS(x));
		}
	}
	file.close();
}
//Tách mã sách để lấy mã ISBN
string tachMaSach(string masach)
{
	string temp;
	int n = masach.length();
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		if (masach[i] == '-')
			dem = i;
	}
	temp = masach.substr(0, dem);

	return temp;
}

node_DMS* timKiemDanhMucSach(LIST_DS l, string masach)
{
	string isbn = tachMaSach(masach);
	int i = timKiemDauSachTheoMa(l, isbn);
	if (i != -1)
		for (node_DMS* p = l.ds[i]->dms; p != NULL; p = p->next)
		{
			if (p->data.masach.compare(masach) == 0)
				return p;
		}
	return NULL;
}
//Trả về số lượng đầu sách tìm được, flag = 0: in sách để xem, flag = 1: in sách để click chọn
int timKiemDSTheoTen(LIST_DS l, string tuKhoa, int flag)
{	
	system("cls");
	ShowCur(false);
	int* a = new int[l.n]; //mảng lưu chỉ số đầu sách được tìm thấy
	int dem; //biến lưu số lượng đầu sách được tìm thấy
	int vitri_timthay;
	bool KT; //biến vòng while nhỏ
	char signal; //biến bắt phím
	int pointer = 0; //biến thanh sáng đầu sách
	int slsach = 0; //biến lưu số lượng sách của đầu sách được chọn
	while (true)
	{
		system("cls");
		dem = 0;
		for (int i = 0; i < l.n; i++) //duyệt từ đầu đến cuối danh sách đầu sách
		{
			//tìm vị trí của chuỗi con tuKhoa trong tên đầu sách
			vitri_timthay = l.ds[i]->tensach.find(tuKhoa);
			if (vitri_timthay != string::npos) //npos - tương tự như null
			{
				inMotDS(l.ds[i], dem, 0);
				a[dem] = i; //lưu lại vị trí đầu sách này
				dem++;
			}
		}
		if (dem != 0) //Nếu tìm thấy đầu sách thích hợp
		{
			for (int i = 0; i < 7; i++) //in tiêu đề
			{// Y_Display 3
				gotoxy(xKeyDisplay[i] + 3, Y_Display + 1);
				cout << thongTinDS[i];
			}		
			for (int i = xKeyDisplay[0]; i <= xKeyDisplay[7]; i++)
			{
				//ve thanh ngang tieu de so 1
				gotoxy(i, Y_Display);
				cout << char(176);

				//ve thanh ngang tieu de so 2
				gotoxy(i, Y_Display + 2);
				cout << char(176);
			}
			gotoxy(xKeyDisplay[0], Y_Display + 1 + dem * 3); cout << setw(135) << setfill(char(176)) << "";
			// to mau cho dong duoc chon
			KT = true;
			
			gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + pointer * 3);
			HighlightLine();
			cout << l.ds[a[pointer]]->tensach;
			NormalLine(); // tro ve mau cu
			// dieu khien chuc nang
			while (KT)
			{
				signal = _getch();// kiem tra xem co nhap gi tu ban phim khong
				if (signal == ESC)
				{
					delete[] a;
					return dem;
				}
				if (signal == -32)
				{
					signal = _getch();
				}
				// dieu huong
				switch (signal)
				{
					case KEY_UP:
						gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + pointer * 3);
						cout << l.ds[a[pointer]]->tensach;
						if (pointer > 0)
							pointer--;// cap nhat lai vi tri	
						else if (pointer == 0)
							pointer = dem - 1;
						HighlightLine(); // to mau thanh sang
						gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + pointer * 3);
						cout << l.ds[a[pointer]]->tensach;
						NormalLine(); // tro ve mau cu
						break;
					case KEY_DOWN:
						NormalLine(); // tro ve mau cu
						gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + pointer * 3);
						cout << l.ds[a[pointer]]->tensach;
						if (pointer < dem - 1)
							pointer++;// cap nhat lai vi tri	
						else if (pointer == dem - 1)
							pointer = 0;
						HighlightLine(); // to mau thanh sang
						gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + pointer * 3);
						cout << l.ds[a[pointer]]->tensach;
						NormalLine(); // tro ve mau cu
						break;
					case ENTER:// luu lai ket qua bien pointer va thoat
						KT = false;
						break;
				}
			}			
			slsach = demSoLuongSach(*l.ds[a[pointer]]);
			if (slsach == 0)
			{
				inThongBao("Dau sach nay khong co sach!");
				continue;
			}
			system("cls");
			gotoxy(X_TitlePage, Y_TitlePage);
			cout << "CAC SACH THUOC DAU SACH: " << l.ds[a[pointer]]->tensach << "\n\n";
			if (flag == 0)
				menuXemDanhMucSach(l.ds[a[pointer]]->dms, slsach);
			else
				menuChonDanhMucSach(l.ds[a[pointer]]->dms, slsach);
		}
		else //Không tìm thấy đầu sách nào cả
		{
			delete[] a;
			return dem;
		}
	}
}

void menuDauSach(LIST_DS& l)
{
	ShowCur(false);
	system("cls");
	trangDSHienTai = 1;
	// ceil lam tron len
	soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
	inMotTrangDS(l, 0);
	veBang(thongTinDS, sizeof(thongTinDS) / sizeof(string));	

	int signal;
	while (true)
	{
		while (_kbhit())
		{
			xoaThongBao();
			signal = _getch();
			if (signal == ESC)
				return;
			if (signal == 224)
			{
				signal = _getch();
				if (signal == PAGE_UP)
				{
					if (trangDSHienTai > 1)
						trangDSHienTai--;
					else trangDSHienTai = soLuongTrangDS;
					inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
				}
				else if (signal == PAGE_DOWN)
				{
					if (trangDSHienTai < soLuongTrangDS)
						trangDSHienTai++;
					else trangDSHienTai = 1;
					inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
				}
				// them moi
				else if (signal == INSERT) //Thêm đầu sách
				{
					if (l.n == MAX)
					{
						inThongBao("Danh sach day, khong the them");
						break;
					}
					taoBangNhap("Nhap moi dau sach", thongTinDS, 1, 7, 50);
					nhapDS(l, 0);					
					ShowCur(false);
				}// endif signal == INSERT

				// xoa di
				else if (signal == DEL) //Xóa đầu sách
				{
					if (l.n == 0)
					{
						inThongBao("Danh sach rong");
						return;
					}
					taoBangNhap("Xoa dau sach", thongTinDS, 1, 7, 50);
					nhapDS(l, 1);
					ShowCur(false);
				}//else if( signal == DEL)
				// HOME == chinh sua
				else if (signal == HOME) //Thêm sách
				{
					taoBangNhap("Nhap moi sach", thongTinDMS, 0, 4, 50);
					nhapDMS(l);
					ShowCur(false);
				}// signal == HOME
			}
			if (signal == 0)
			{
				signal = _getch();
				if (signal == KEY_F4)
				{
					taoBangNhap("Chinh sua thong tin dau sach", thongTinDS, 1, 7, 50);
					nhapDS(l, 2);
					ShowCur(false);
				}
				if (signal == 59)
				{	
					//system("cls");
					taoBangNhap("Tim sach theo ten", thongTinDS, 2, 3, 50);
					string tuKhoa = "";
					int kt;
					ShowCur(true);
					kt = nhap_ki_tu(tuKhoa, 1, 0, 15);
					if (kt == -1) //ESC
					{
						xoaBangNhap();
						xoaThongBao();
						break;
					}
					int dem = timKiemDSTheoTen(l, tuKhoa, 0);
					if (dem == 0)
						inThongBao("Khong tim thay dau sach thich hop!");
					gotoxy(xKeyDisplay[0], Y_Display + 1 + dem * 3); cout << setw(135) << setfill(' ') << "";
					NormalLine();
					inMotTrangDS(l, (trangDSHienTai - 1) * NumberPerPage);
					veBang(thongTinDS, sizeof(thongTinDS) / sizeof(string));
					ShowCur(false);
				}
			}
		}//while(_kbhit)
	}// while(true)
}
