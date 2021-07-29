#pragma once
#include "HamNhap.h"
#include "HangSo.h"
#include "HienThi.h"
#include "DanhMucSach.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define MAX 300 //số lượng đầu sách tối đa

// thong tin vi tri hien tai
int trangDSHienTai = 1;
int soLuongTrangDS = 0;
// thong tin vi tri hien tai khi tim kiem dau sach
int trangDSTimKiemHienTai = 1;
int soLuongTrangDSTimKiem = 0;
//int xKeyDisplay[8] = { 1, 8, 23, 58, 73, 98, 118, 140 };// toa do X cac diem nut
int xKeyDisplay[8] = { 39, 45, 59, 92, 105, 127, 137, 159 };
string thongTinDS[8] = { "STT", "ISBN", "Ten sach", "So trang", "Tac gia", "Nam xb", "The loai", "SLM" };
string thongTinDMS[4] = { "ISBN", "So luong sach can them", "Ma sach", "Vi tri" };

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

struct indexSoLuotMuon
{
	int chiso;
	int soluotmuon;
};

//=====Khai bao cac thuat toan=====
void khoiTaoDS(LIST_DS& l);
int themMotDS(LIST_DS& l, dausach s);
int nhapDS(LIST_DS& l, int cs, int flag);
int timKiemDauSachTheoMa(LIST_DS l, string maDauSach);
void xoaNoiDungCu(int nContent, int locate);
void inMotDS(dausach* s, int position, int StartIndex);
void veBang(string content[], int nContent);
void xoaNoiDungBiDu(int count, int nContent);
void inMotTrangDS(LIST_DS l, listTheLoai listTL, int StartIndex);
void chuyenTrangDS(LIST_DS l);
void docFileDS(LIST_DS& l);
void ghiFileDS(LIST_DS l);
void menuDauSach(LIST_DS& l);
int demSoLuongSach(dausach x);
void sapXepGiuNguyenIndex(LIST_DS& l, listTheLoai& listIndex);
string tachMaSach(string masach);
PTR_DMS timKiemDanhMucSach(LIST_DS l, string masach);
int timKiemDSTheoTen(LIST_DS& l, string tuKhoa, int flag, string& masach, int& ktxoanhap);
void huongDan();
void top10SachMuon(LIST_DS l);

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

void xoaDSTheoMa(LIST_DS& l, string ma) {
	int i = timKiemDauSachTheoMa(l, ma);
	if (i == -1) return;
	else
	{
		delete l.ds[i];
		for (int j = i + 1; j < l.n; j++)
			l.ds[j - 1] = l.ds[j];

		l.n--;
	}
}

//hiện thông tin đầu sách vào bảng nhập
void hienThongTinDS(dausach s)
{
	gotoxy(X_Add + 12, 0 * 2 + Y_Add);
	cout << s.ISBN;
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
int nhapDS(LIST_DS& l, int cs, int flag)
{
	xoaThongBao();
	dausach s;
	string soTrang;
	string namxb;
	int viTri = 0;// so thu tu bat dau nhap
	int kt;
	int khoangCach = 12;
	int stt = -2;
	char c; //biến bắt phím nhập
	ShowCur(true);
	while (true)
	{
		switch (viTri)
		{
		case 0:
		{
			if (flag == 0 || flag == 2)
			{
				gotoxy(X_Add + 12, 6 * 2 + Y_Add);
				cout << "ENTER";
			}
			if (flag == 0) //trường hợp nhập mới
			{
				kt = nhap_ki_tu(s.ISBN, 2, viTri, khoangCach);
				if (kt == -1)
				{
					xoaBangNhap();
					xoaThongBao();
					return 0;
				}
				if (kt == KEY_UP) break;
				stt = timKiemDauSachTheoMa(l, s.ISBN);
				xoaThongBao();
				if (stt != -1)
				{
					inThongBao("Ma ISBN bi trung!");
					break;
				}
			}
			if (flag == 1) //trường hợp xóa đầu sách
			{
				if (demSoLuongSach(*l.ds[cs]) == 0)
				{
					xoaThongBao();
					taoBangNhap("Xoa dau sach", thongTinDS, 1, 7, 50);
					hienThongTinDS(*l.ds[cs]);
					int luaChon = menu_xoa(X_Notification, Y_Notification + 1);
					if (luaChon == 0) // Có
					{
						xoaDSTheoMa(l, l.ds[cs]->ISBN);
						ghiFileDS(l);
						xoaBangNhap();
						soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);


						inThongBao("Xoa thanh cong!");
						return 1;
					}
					else
					{
						xoaBangNhap();
						ShowCur(false);
						return 0;
					}
				}
				else
				{
					xoaThongBao();
					xoaBangNhap();
					inThongBao("Dau sach nay dang co sach, khong the xoa!");
					ShowCur(false);
					return 0;
				}
			}
			if (flag == 2) //chỉnh sửa
			{
				s = *l.ds[cs];
				soTrang = to_string(l.ds[cs]->sotrang);
				namxb = to_string(l.ds[cs]->namxuatban);
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
				return 0;
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
				return 0;
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
				return 0;
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
				return 0;
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
				return 0;
			}
			if (kt == KEY_UP)
			{
				viTri--;
				break;
			}
			viTri++;
			break;
		}
		case 6:
		{
			ShowCur(false);
			HighlightLine();
			gotoxy(X_Add + 12, 6 * 2 + Y_Add);
			cout << "ENTER";
			NormalLine();
			c = _getch();
			if (c == 27) //ESC
			{
				xoaBangNhap();
				xoaThongBao();
				return 0;
			}
			if (c == KEY_UP)
			{
				gotoxy(X_Add + 12, 6 * 2 + Y_Add);
				NormalLine();
				cout << "ENTER";
				viTri--;
				ShowCur(true);
				break;
			}
			if (c == ENTER)
			{
				s.sotrang = atoi(soTrang.c_str());
				s.namxuatban = atoi(namxb.c_str());
				if (flag == 0) //trường hợp nhập mới đầu sách
				{
					s.soluotmuon = 0;
					themMotDS(l, s);
					xoaThongBao();
					inThongBao("Them dau sach thanh cong");
					soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
				}
				if (flag == 2) //trường hợp chỉnh sửa đầu sách
				{
					*l.ds[cs] = s;
					xoaThongBao();
					inThongBao("Sua dau sach thanh cong");
				}
				xoaBangNhap();
				ghiFileDS(l);
				return 1;
			}
		}
		}
	}
}

//Nhập thông tin sách
void nhapDMS(LIST_DS& l, int cs)
{
	int n = 0; //số lượng sách cần thêm mà người dùng nhập vào	
	string chuoinhap; //chuỗi người dùng nhập vào
	int viTri = 1;// so thu tu bat dau nhap	
	int kt;
	int khoangCach = 25;
	int pos;
	string str;
	danhmucsach x;
	int stt = 1; //stt mã sách
	ShowCur(true);
	gotoxy(X_Add + 25, 0 * 2 + Y_Add);
	cout << l.ds[cs]->ISBN;
	while (true)
	{
		switch (viTri)
		{
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

			if (l.ds[cs]->dms != NULL)
			{
				PTR_DMS q = l.ds[cs]->dms;
				while (q->next != NULL)
				{
					q = q->next;
				}
				x.vitri = q->data.vitri; // lấy vị trí cuối cùng của sách đã tồn tại
				pos = q->data.masach.find("-"); // lấy vị trí của kí tự - trong chuỗi
				str = q->data.masach.substr(pos + 1); //  lấy chuỗi con của q->data.masach bắt đầu sau kí tự '-'
				stt += atoi(str.c_str()); //chuyển chuỗi sang số
			}
			for (int j = 0; j < n; j++)
			{
				x.masach = l.ds[cs]->ISBN + "-" + to_string(stt + j);
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
				themLastDMS(l.ds[cs]->dms, taoNodeDMS(x));
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

void swap(indexSoLuotMuon& x, indexSoLuotMuon& y)
{
	indexSoLuotMuon temp = x;
	x = y;
	y = temp;
}

void sapxep(indexSoLuotMuon a[], int l, int r)
{
	int x;
	int i, j;
	i = l;
	j = r;
	x = a[(l + r) / 2].soluotmuon;
	do
	{
		while (a[i].soluotmuon > x)i++;
		while (a[j].soluotmuon < x)j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j) sapxep(a, l, j);
	if (i < r) sapxep(a, i, r);
}

//sắp xếp số lượt mượn giảm dần
void quickSort(indexSoLuotMuon a[], int n)
{
	sapxep(a, 0, n - 1);
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
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3); cout << position + StartIndex + 1;
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3); cout << s->ISBN;
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3); cout << s->tensach;
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3); cout << s->sotrang;
	gotoxy(xKeyDisplay[4] + 3, Y_Display + 3 + position * 3); cout << s->tacgia;
	gotoxy(xKeyDisplay[5] + 3, Y_Display + 3 + position * 3); cout << s->namxuatban;
	gotoxy(xKeyDisplay[6] + 3, Y_Display + 3 + position * 3); cout << s->theloai;
	/*
	for (int i = 0; i < 7 + 1; i++)
	{
		gotoxy(xKeyDisplay[i], Y_Display + 1 + position * 3);
		cout << char(176);
		gotoxy(xKeyDisplay[i], Y_Display + 2 + position * 3);
		cout << char(176);
		gotoxy(xKeyDisplay[i], Y_Display + 3 + position * 3);
		cout << char(176);
	}
	*/
}

void huongDan()
{
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
	cout << " Delete: Xoa dau sach";
	gotoxy(X_Tutorial, Y_Tutorial + 6);
	cout << " F2: Sua dau sach";
	gotoxy(X_Tutorial, Y_Tutorial + 7);
	cout << " F1: Tim kiem";
	gotoxy(X_Tutorial, Y_Tutorial + 8);
	cout << " F3: Them sach";
	gotoxy(X_Tutorial, Y_Tutorial + 9);
	cout << " Enter: Chon dau sach";
	gotoxy(X_Tutorial, Y_Tutorial + 10);
	cout << " ESC: Tro ve";
	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Quan ly dau sach";

	//SetColor(12);
	gotoxy(X_Notification, Y_Notification);
	cout << " Thong Bao ";
	//NormalLine();
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
	for (int j = Y_Display; j <= Y_Display + 20; j++)
	{
		for (int i = 0; i < nContent + 1; i++)
		{
			gotoxy(xKeyDisplay[i], j);
			cout << char(176);
		}
	}
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
		gotoxy(i, Y_Display + 20);
		cout << char(176);
	}
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

void inMotTrangDS(LIST_DS l, listTheLoai listTL, int StartIndex)
{
	int cs;
	gotoxy(xKeyDisplay[0], 2);
	cout << " So luong dau sach : " << l.n << "    ";
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
}

void inMotTrangDSTimKiem(LIST_DS l, int arr[], int n, int StartIndex)
{
	int cs;
	gotoxy(xKeyDisplay[0], 2);
	cout << " So luong dau sach tim duoc: " << n;
	int i;
	for (i = 0; i + StartIndex < n && i < NumberPerPage1; i++)
	{
		cs = arr[i + StartIndex];
		inMotDS(l.ds[cs], i, StartIndex);
	}
	xoaNoiDungBiDu(i, sizeof(thongTinDS) / sizeof(string)); //hàm này để xóa những nội dung cũ ở trang trước trang cuối cùng, nếu trang cuối cùng không đầy
	gotoxy(X_Page, Y_Page);
	cout << setw(20) << setfill(' ') << "";
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << trangDSTimKiemHienTai << "/" << soLuongTrangDSTimKiem;
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

void top10SachMuon(LIST_DS l)
{

	indexSoLuotMuon* a = new indexSoLuotMuon[l.n];
	for (int i = 0; i < l.n; i++)
	{
		a[i].chiso = i;
		a[i].soluotmuon = l.ds[i]->soluotmuon;
	}
	quickSort(a, l.n); //sắp xếp số lượt mượn giảm dần
	int cs;
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < 8; i++)
	{// Y_Display 3
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 1);
		cout << thongTinDS[i];
	}
	int dem = 0;
	for (int i = 0; i < 10; i++)
	{
		if (a[i].soluotmuon > 0)
		{
			cs = a[i].chiso;
			inMotDS(l.ds[cs], i, 0);
			gotoxy(xKeyDisplay[7] + 3, Y_Display + 3 + i * 3);
			cout << a[i].soluotmuon;
			dem++;
		}
	}
	veKhung(xKeyDisplay[0], Y_Display, 128, dem * 3 + 1);
	VeDuongThang_Ngang(Y_Display + 2, xKeyDisplay[0] + 1, xKeyDisplay[0] + 128 - 1);
	for (int i = 1; i < 8; i++)
	{
		VeDuongThang_Doc(xKeyDisplay[i], Y_Display + 1, Y_Display + dem * 3);
	}

	char c;
	while (true)
	{
		c = _getch();
		if (c == ESC) return;
	}
}

//Trả về số lượng đầu sách tìm được, flag = 0: in sách để xem, xóa, sửa; flag = 1: in sách để mượn
int timKiemDSTheoTen(LIST_DS& l, string tuKhoa, int flag, string& masach, int& ktxoasua)
{
	ShowCur(false);
	int* a = new int[l.n]; //mảng lưu chỉ số đầu sách được tìm thấy
	int dem; //biến lưu số lượng đầu sách được tìm thấy
	int vitri_timthay;
	int kt; //biến kiểm tra giá trị trả về
	char signal; //biến bắt phím
	int pointer = 0; //biến thanh sáng đầu sách
	int slsach = 0; //biến lưu số lượng sách của đầu sách được chọn

timKiem:
	dem = 0;
	for (int i = 0; i < l.n; i++) //duyệt từ đầu đến cuối danh sách đầu sách để tìm
	{
		//tìm vị trí của chuỗi con tuKhoa trong tên đầu sách
		vitri_timthay = l.ds[i]->tensach.find(tuKhoa);
		if (vitri_timthay != string::npos) //npos - tương tự như null
		{
			a[dem] = i; //lưu lại vị trí đầu sách này
			dem++;
		}
	}

	if (dem == 0) //không tìm thấy đầu sách thích hợp
	{
		delete[] a;
		return dem;
	}

	//nếu tìm thấy
	//system("cls");
	xoaNoiDungBiDu(0, 7);
	trangDSTimKiemHienTai = 1;
	// ceil lam tron len
	soLuongTrangDSTimKiem = (int)ceil((double)dem / NumberPerPage1);
	inMotTrangDSTimKiem(l, a, dem, 0);
	veBang(thongTinDS, 7);
	int chiSoBatDau = (trangDSTimKiemHienTai - 1) * NumberPerPage1;
	int cs = a[pointer + chiSoBatDau];
	bool ktxoasuasach = false; //biến kiểm tra xem có xóa hay sửa sách không, nếu có thì ghi file

	while (true)
	{
		//tô màu dòng đầu tiên
		HighlightLine();
		inMotDS(l.ds[cs], pointer, chiSoBatDau);
		NormalLine();
		//=========================
		signal = _getch();// kiem tra xem co nhap gi tu ban phim khong
		if (signal == ESC)
		{
			delete[] a;
			xoaBangNhap();
			return dem;
		}
		else if (signal == -32)
		{
			signal = _getch();

		}
		else if (signal == 0)
		{
			signal = _getch();
		}
		// dieu huong
		switch (signal)
		{
		case PAGE_UP:
			if (trangDSTimKiemHienTai > 1)
				trangDSTimKiemHienTai--;
			else trangDSTimKiemHienTai = soLuongTrangDSTimKiem;
			chiSoBatDau = (trangDSTimKiemHienTai - 1) * NumberPerPage1;
			inMotTrangDSTimKiem(l, a, dem, chiSoBatDau);
			pointer = 0;
			cs = a[pointer + chiSoBatDau];

			break;
		case PAGE_DOWN:
			if (trangDSTimKiemHienTai < soLuongTrangDSTimKiem)
				trangDSTimKiemHienTai++;
			else trangDSTimKiemHienTai = 1;
			chiSoBatDau = (trangDSTimKiemHienTai - 1) * NumberPerPage1;
			inMotTrangDSTimKiem(l, a, dem, chiSoBatDau);
			pointer = 0;
			cs = a[pointer + chiSoBatDau];
			break;
		case KEY_UP:
			if (pointer > 0)
			{
				NormalLine();
				inMotDS(l.ds[cs], pointer, chiSoBatDau);
				pointer--;
				cs = a[pointer + chiSoBatDau];
			}
			break;
		case KEY_DOWN:
			if ((pointer < NumberPerPage1 - 1) && (pointer + chiSoBatDau < dem - 1))
			{
				NormalLine();
				inMotDS(l.ds[cs], pointer, chiSoBatDau);
				pointer++;
				cs = a[pointer + chiSoBatDau];
			}
			break;
		case DEL:
			if (flag == 0)
			{
				kt = nhapDS(l, cs, 1);
				if (kt == 1)
				{
					ktxoasua++;
					if (dem > 1)
						goto timKiem;
					return dem;
				}
			}
			break;
		case KEY_F2:
			if (flag == 0)
			{
				taoBangNhap("Nhap moi dau sach", thongTinDS, 1, 7, 50);
				kt = nhapDS(l, cs, 2);
				if (kt == 1)
				{
					ktxoasua++;
					//return dem;
					goto timKiem;
				}
			}
			break;
		case KEY_F3:
			if (flag == 0)
			{
				taoBangNhap("Nhap moi sach", thongTinDMS, 0, 4, 50);
				nhapDMS(l, cs);
				ShowCur(false);
			}
			break;
		case ENTER:// chọn đầu sách để xem sách
			slsach = demSoLuongSach(*l.ds[cs]);
			if (slsach == 0)
			{
				inThongBao("Dau sach nay chi co ban goc!");
			}
			else
			{
				system("cls");
				//xoa(39, 0, 128, 40);
				gotoxy(X_TitlePage, Y_TitlePage);
				cout << "SACH THUOC DAU SACH: " << l.ds[cs]->tensach << "\n\n";
				if (flag == 0)
				{
					menuXemDanhMucSach(l.ds[cs]->dms, slsach, ktxoasuasach);
				}
				else
				{
					menuChonDanhMucSach(l.ds[cs]->dms, slsach);
				}
				if (ktxoasuasach)
					ghiFileDS(l);
				system("cls");
				//xoa(39, 0, 128, 40);
				inMotTrangDSTimKiem(l, a, dem, chiSoBatDau);
				veBang(thongTinDS, 7);
				huongDan();
			}
			break;
		}
	}
}

void menuDauSach(LIST_DS& l)
{
	ShowCur(false);
	//system("cls");
	listTheLoai listTL;
	listTL.nodes = new indexTheLoai[l.n + 20];
	sapXepGiuNguyenIndex(l, listTL);
	int slDSThem = 0; //biến đếm số lượng đầu sách đã thêm

	trangDSHienTai = 1;
	// ceil lam tron len
	soLuongTrangDS = (int)ceil((double)l.n / NumberPerPage);
	inMotTrangDS(l, listTL, 0);
	veBang(thongTinDS, 7);
	huongDan();
	string tuKhoa = ""; //biến để tìm kiếm sách
	int kt; //biến kiểm tra giá trị trả về
	string masach;
	int sldausach; //số lượng đầu sách tìm được
	int slsach; //số lượng sách của đầu sách được chọn
	int signal; //biến bắt phím
	int thanhSang = 0; //thanh sáng để chọn đầu sách
	int chiSoBatDau = (trangDSHienTai - 1) * NumberPerPage;
	int cs = listTL.nodes[thanhSang + chiSoBatDau].chiso; //index của đầu sách đang được chọn
	int ktxoasua;
	bool ktxoasuasach = false;
	while (true)
	{
		//tô màu dòng được chọn
		HighlightLine();
		inMotDS(l.ds[cs], thanhSang, chiSoBatDau);
		NormalLine();
		//====================
		signal = _getch();
		if (signal == ENTER)
		{
			slsach = demSoLuongSach(*l.ds[cs]);
			if (slsach == 0)
			{
				inThongBao("Dau sach nay chi co ban goc!");
			}
			else
			{
				system("cls");
				//xoa(39, 0, 128, 40);
				gotoxy(X_TitlePage, Y_TitlePage);
				cout << "SACH THUOC DAU SACH : " << l.ds[cs]->tensach << "\n\n";
				menuXemDanhMucSach(l.ds[cs]->dms, slsach, ktxoasuasach);
				if (ktxoasuasach)
					ghiFileDS(l);
				system("cls");
				//xoa(39, 0, 128, 40);
				inMotTrangDS(l, listTL, chiSoBatDau);
				veBang(thongTinDS, 7);
				huongDan();
			}
		}
		if (signal == ESC)
		{
			delete[] listTL.nodes;
			return;
		}
		if (signal == 224)
		{
			signal = _getch();
			if (signal == PAGE_UP)
			{
				if (trangDSHienTai > 1)
					trangDSHienTai--;
				else trangDSHienTai = soLuongTrangDS;
				chiSoBatDau = (trangDSHienTai - 1) * NumberPerPage;
				inMotTrangDS(l, listTL, chiSoBatDau);
				thanhSang = 0;
				cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;

			}
			else if (signal == PAGE_DOWN)
			{
				if (trangDSHienTai < soLuongTrangDS)
					trangDSHienTai++;
				else trangDSHienTai = 1;
				chiSoBatDau = (trangDSHienTai - 1) * NumberPerPage;
				inMotTrangDS(l, listTL, chiSoBatDau);
				thanhSang = 0;
				cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;

			}
			if (signal == KEY_UP)
			{
				if (thanhSang > 0)
				{
					NormalLine();
					inMotDS(l.ds[cs], thanhSang, chiSoBatDau);
					thanhSang--;
					cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;

				}

			}
			else if (signal == KEY_DOWN)
			{
				if ((thanhSang < NumberPerPage - 1) && (thanhSang + chiSoBatDau < l.n - 1))
				{
					NormalLine();
					inMotDS(l.ds[cs], thanhSang, chiSoBatDau);
					thanhSang++;
					cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;

				}
			}
			// them moi
			else if (signal == INSERT) //Thêm đầu sách
			{
				if (l.n == MAX)
				{
					inThongBao("Danh sach day, khong the them");
					continue;
				}
				if (slDSThem == 20)
				{
					inThongBao("Da them sach 20 lan, hay ve trang chu de reset lai so lan");
					continue;
				}
				taoBangNhap("Nhap moi dau sach", thongTinDS, 1, 7, 50);
				kt = nhapDS(l, cs, 0);
				if (kt == 1)
				{
					sapXepGiuNguyenIndex(l, listTL);
					inMotTrangDS(l, listTL, chiSoBatDau);
					cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;
					slDSThem++;
				}
				ShowCur(false);
			}// endif signal == INSERT

			// xoa di
			else if (signal == DEL) //Xóa đầu sách
			{
				if (l.n == 0)
				{
					inThongBao("Danh sach rong");
					continue;
				}

				kt = nhapDS(l, cs, 1);
				if (kt == 1)
				{
					sapXepGiuNguyenIndex(l, listTL);
					inMotTrangDS(l, listTL, chiSoBatDau);
					cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;
				}

				ShowCur(false);
			}//else if( signal == DEL)

		}
		if (signal == 0)
		{
			signal = _getch();
			if (signal == KEY_F3) //Thêm sách
			{
				taoBangNhap("Nhap moi sach", thongTinDMS, 0, 4, 50);
				nhapDMS(l, cs);

				ShowCur(false);
			}
			else if (signal == KEY_F2)
			{
				taoBangNhap("Chinh sua thong tin dau sach", thongTinDS, 1, 7, 50);
				kt = nhapDS(l, cs, 2);
				if (kt == 1)
				{
					sapXepGiuNguyenIndex(l, listTL);
					inMotTrangDS(l, listTL, chiSoBatDau);
					cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;
				}

				ShowCur(false);
			}
			else if (signal == KEY_F1)
			{
				ktxoasua = 0;
				//system("cls");
				taoBangNhap("Tim sach theo ten", thongTinDS, 2, 3, 50);

				ShowCur(true);
				kt = nhap_ki_tu(tuKhoa, 1, 0, 15);
				if (kt == -1) //ESC
				{
					xoaBangNhap();
					xoaThongBao();
					continue;
				}
				sldausach = timKiemDSTheoTen(l, tuKhoa, 0, masach, ktxoasua);

				if (sldausach == 0)
				{
					xoaThongBao();
					inThongBao("Khong tim thay dau sach thich hop!");
					xoaBangNhap();
					continue;
				}
				if (ktxoasua != 0)
				{
					sapXepGiuNguyenIndex(l, listTL);
					cs = listTL.nodes[thanhSang + chiSoBatDau].chiso;
				}
				gotoxy(1, 2);
				cout << setw(40) << setfill(' ') << "";
				NormalLine();
				inMotTrangDS(l, listTL, chiSoBatDau);
				veBang(thongTinDS, 7);
				huongDan();

				ShowCur(false);
			}
		}
	}// while(true)
}