#pragma once
#include <string>
#include "mylib.h"
#include "Date.h"
#define MAX_DMS 9000
using namespace std;

const int topLeft = 201;
const int topRight = 187;
const int botLeft = 200;
const int botRight = 188;

int trangDMSHienTai = 1;
int soLuongTrangDMS = 0;
string cotDMS[4] = { "STT", "Ma sach", "Trang thai", "Vi tri" };
int xKeyDisplay1[5] = { 51, 58, 75, 95, 123 };
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
void veBang1(string content[], int nContent);
void luuChiSoCuaDMS(PTR_DMS First, PTR_DMS nodes[]);
void xoaNoiDungBiDu1(int count, int nContent);
void xoaNoiDungCu1(int nContent, int locate);
void inMotDMS(node_DMS* s, int position, int StartIndex);
void inMotTrangDMS(PTR_DMS nodes[], int StartIndex, int n);
void VeDuongThang_Ngang(int hang, int FirstCot, int LastCot);
void VeDuongThang_Doc(int cot, int FirstHang, int LastHang);
void veKhung(int x, int y, int ngang, int doc);
int xoaDMSTheoMa(PTR_DMS& First, string ma);
void NormalLine();
void HighlightLine();
int suaDMS(PTR_DMS x);
int menu_xoa(int x, int y);
void huongDan1();
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

void VeDuongThang_Ngang(int hang, int FirstCot, int LastCot)
{

	while (FirstCot <= LastCot)
	{
		gotoxy(FirstCot++, hang);
		//cout << "_";
		putchar(205);
	}
}

void VeDuongThang_Doc(int cot, int FirstHang, int LastHang)
{

	while (FirstHang <= LastHang)
	{
		gotoxy(cot, FirstHang++);
		//cout << "|";
		putchar(186);
	}
}

void veKhung(int x, int y, int ngang, int doc)
{

	int firstNgang = x + 1;
	int endNgang = x + ngang - 1;
	int firstDoc = y + 1;
	int endDoc = y + doc - 1;
	VeDuongThang_Ngang(y, firstNgang, endNgang);
	VeDuongThang_Ngang(endDoc + 1, firstNgang, endNgang);
	VeDuongThang_Doc(x, firstDoc, endDoc);
	VeDuongThang_Doc(endNgang + 1, firstDoc, endDoc);
	// 4 goc;
	gotoxy(x, y);
	putchar(topLeft);
	gotoxy(endNgang + 1, y);
	putchar(topRight);
	gotoxy(x, endDoc + 1);
	putchar(botLeft);
	gotoxy(endNgang + 1, endDoc + 1);
	putchar(botRight);

}

void xoa(int x, int y, int ngang, int doc)
{
	for (int i = y; i <= y + doc; i++)
	{
		gotoxy(x, i);
		cout << setw(ngang) << setfill(' ') << "";
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

//flag = true : ve, flag = false : xoa
void veXoaBang1(string content[], int nContent, bool flag)
{
	//cout << setfill(char(176)) << setw(80) << "" << endl;
	//cout << char(176) << setfill(' ') << left << setw(5) << "STT" << char(176) << setw(20) << "Ma sach" << char(176) << setw(30) << "Trang thai" << char(176) << setw(20) << "Vi tri" << char(176) << endl;
	//cout << setfill(char(176)) << setw(80) << "" << endl;
	//the hien ra noi dung cua cac cot
	for (int i = 0; i < nContent; i++)
	{// Y_Display 3
		gotoxy(xKeyDisplay1[i] + 3, Y_Display + 1);
		if (flag)
			cout << content[i];
		else
		{
			cout << setw(xKeyDisplay1[i + 1] - xKeyDisplay1[i] - 3) << setfill(' ') << "";
			gotoxy(xKeyDisplay1[i] + 3, Y_Display + 3);
			cout << setw(xKeyDisplay1[i + 1] - xKeyDisplay1[i] - 3) << setfill(' ') << "";
		}
			
		
	}
	//ve cac duong thang de phan chia cac cot
	for (int j = Y_Display; j <= Y_Display + 20; j++)
	{
		for (int i = 0; i < nContent + 1; i++)
		{
			gotoxy(xKeyDisplay1[i], j);
			if (flag)
				cout << char(176);
			else
				cout << " ";
		}
	}
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay1[0]; i <= xKeyDisplay1[nContent]; i++)
	{
		if (flag)
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
		else
		{
			//ve thanh ngang ben tren so 1
			gotoxy(i, Y_Display);
			cout << " ";

			// ve thanh ngang ben tren so 2
			gotoxy(i, Y_Display + 2);
			cout << " ";

			//ve thanh ngang ben duoi
			gotoxy(i, Y_Display + 20);
			cout << " ";
		}
		
	}
}

void luuChiSoCuaDMS(PTR_DMS First, PTR_DMS nodes[])
{
	int i = 0;
	for (PTR_DMS p = First; p != NULL; p = p->next)
	{
		nodes[i] = p;
		i++;
	}
}

void xoaNoiDungBiDu1(int count, int nContent)
{
	if (count < NumberPerPageDMS)
	{
		for (int i = count; i < NumberPerPageDMS; i++)
		{
			for (int y = 0; y < nContent; y++)
			{
				gotoxy(xKeyDisplay1[y] + 3, Y_Display + 3 + i * 3);
				cout << setw(xKeyDisplay1[y + 1] - xKeyDisplay1[y] - 3) << setfill(' ') << "";
			}
		}
	}
}

//Xóa nội dung trang trước
void xoaNoiDungCu1(int nContent, int locate)
{
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay1[i] + 3, Y_Display + 3 + locate * 3);
		cout << setw(xKeyDisplay1[i + 1] - xKeyDisplay1[i] - 3) << setfill(' ') << "";
	}
}

void huongDan1()
{
	//SetColor(6);
	xoa(X_Tutorial, Y_Tutorial, 15, 10);
	cout << endl;
	gotoxy(X_Tutorial, Y_Tutorial);
	cout << " Huong dan ";
	gotoxy(X_Tutorial, Y_Tutorial + 2);
	cout << " Page Up: Len";
	gotoxy(X_Tutorial, Y_Tutorial + 3);
	cout << " Page Down: Xuong";
	gotoxy(X_Tutorial, Y_Tutorial + 4);
	cout << " Insert: Them sach";
	gotoxy(X_Tutorial, Y_Tutorial + 5);
	cout << " Delete: Xoa sach";
	gotoxy(X_Tutorial, Y_Tutorial + 6);
	cout << " F2: Sua sach";
	gotoxy(X_Tutorial, Y_Tutorial + 7);
	cout << " ESC: Tro ve";

	//SetColor(12);
	gotoxy(X_Notification, Y_Notification);
	cout << " Thong Bao ";
	//NormalLine();
}

void inMotDMS(node_DMS* s, int position, int StartIndex)
{
	string trangThai = "";
	if (s->data.trangthai == 0)
		trangThai = "Cho muon duoc";
	else if (s->data.trangthai == 1)
		trangThai = "Da co nguoi muon";
	else trangThai = "Da thanh ly";
	xoaNoiDungCu1(sizeof(cotDMS) / sizeof(string), position);// xoa dong noi dung cu truoc do
	gotoxy(xKeyDisplay1[0] + 3, Y_Display + 3 + position * 3); cout << position + StartIndex + 1;
	gotoxy(xKeyDisplay1[1] + 3, Y_Display + 3 + position * 3); cout << s->data.masach;
	gotoxy(xKeyDisplay1[2] + 3, Y_Display + 3 + position * 3); cout << trangThai;
	gotoxy(xKeyDisplay1[3] + 3, Y_Display + 3 + position * 3); cout << s->data.vitri;
}

void inMotTrangDMS(PTR_DMS nodes[], int StartIndex, int n)
{
	gotoxy(xKeyDisplay1[0], 2);
	cout << " So luong sach : " << n << "    ";
	int i;
	for (i = 0; i + StartIndex < n && i < NumberPerPageDMS; i++)
	{
		inMotDMS(nodes[i + StartIndex], i, StartIndex);
	}
	xoaNoiDungBiDu1(i, sizeof(cotDMS) / sizeof(string)); //hàm này để xóa những nội dung cũ ở trang trước trang cuối cùng, nếu trang cuối cùng không đầy
	gotoxy(X_PageDMS, Y_PageDMS);
	cout << setw(20) << setfill(' ') << "";
	gotoxy(X_PageDMS, Y_PageDMS);
	cout << " Trang " << trangDMSHienTai << "/" << soLuongTrangDMS;
}

int xoaDMSTheoMa(PTR_DMS& First, string ma)
{
	PTR_DMS p = First;
	if (First == NULL) return 0;
	if (First->data.masach.compare(ma) == 0)
	{
		p = First;
		First = p->next;
		delete p;
		return 1;
	}

	for (p = First; p->next != NULL && p->next->data.masach.compare(ma) != 0; p = p->next);
	if (p->next != NULL)
	{
		PTR_DMS q = p->next;
		p->next = q->next;
		delete q; return 1;
	}
	return 0;
}

int suaDMS(PTR_DMS x)
{
	danhmucsach s;
	int kt;
	string trangThai = "";
	int viTri = 2;
	s = x->data;
	if (s.trangthai == 0)
		trangThai = "Cho muon duoc";
	else if (s.trangthai == 1)
		trangThai = "Da co nguoi muon";
	else trangThai = "Da thanh ly";
	gotoxy(X_Add + 12, 0 * 2 + Y_Add);
	cout << s.masach;
	gotoxy(X_Add + 12, 1 * 2 + Y_Add);
	cout << trangThai;
	gotoxy(X_Add + 12, 2 * 2 + Y_Add);
	cout << s.vitri;
	gotoxy(X_Add + 12, 3 * 2 + Y_Add);
	cout << "ENTER";
	while (true)
	{
		switch (viTri)
		{
			case 2:
			{
				kt = nhap_ki_tu(s.vitri, 1, viTri, 12);
				if (kt == -1) //ESC
				{
					xoaBangNhap();
					xoaThongBao();
					return 0;
				}
				if (kt == KEY_UP) break;
				viTri++;
				break;
			}
			case 3:
			{
				ShowCur(false);
				HighlightLine();
				gotoxy(X_Add + 12, viTri * 2 + Y_Add);
				cout << "ENTER";
				NormalLine();
				kt = _getch();
				if (kt == 27) //ESC
				{
					xoaBangNhap();
					xoaThongBao();
					return 0;
				}
				if (kt == KEY_UP)
				{
					gotoxy(X_Add + 12, viTri * 2 + Y_Add);
					NormalLine();
					cout << "ENTER";
					viTri--;
					ShowCur(true);
					break;
				}
				if (kt == ENTER)
				{
					x->data.vitri = s.vitri;
					inThongBao("Sua sach thanh cong!");
					xoaBangNhap();
					return 1;
				}
			}
		}
	}
}

void menuChonDanhMucSach(PTR_DMS First, int slsach)
{

}