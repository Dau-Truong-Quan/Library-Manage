#pragma once
#include "Date.h"
#include <string>
#include <fstream>
#include "MuonTra.h"
#include "DauSach.h"
#include "DanhMucSach.h"
#include "mylib.h"
#include<queue>
#define UP 72 
#define DOWN 80 
#define RIGHT 77 
#define LEFT 75
#define ENER 13 
#define ESC 27
#define MAX_DS 9000
#define F2 60 
#define F4 62
#define F5 63
#define F1 59
using namespace std;




//=====ĐỘC GIẢ=====
struct docgia
{
	int mathe;
	string ho;
	string ten;
	string phai;
	int trangthaithe; // =0 khoa, =1 hoat dong
	listMT mt; // con trỏ sẽ trỏ đến danh sách các cuốn đã và đang mượn
};


struct node_docgia
{
	docgia data;
	node_docgia* left;
	node_docgia* right;
};
typedef struct node_docgia DOCGIA;
typedef struct node_docgia* TREE_DG;

//=====QUÁ HẠN=====
struct quahan
{
	int ma_doc_gia;
	string ma_sach;
	int so_ngay_quahan;
};

struct ds_tamThoi
{
	TREE_DG docGia;
	string ho;
	string ten;
};
typedef ds_tamThoi DS_TAMTHOI;


// ===================== khai báo hàm
void khoiTaoDS(TREE_DG& dsDG);
void khoiTaoMuonTra(listMT& dsMT);
PTR_MT taoNodeMT(muontra x);


// MƯỢN TRẢ
bool kiemTraSachDangMuon(TREE_DG p, string ma_sach);
void khoiTaoThongTinMuonSach(muontra& x);
int demSoSachDocGiaDangMuon(TREE_DG t);
bool kiemTraQuaHan(TREE_DG docGia);
void xuatSachMuon(TREE_DG docGia, LIST_DS l);
void xuatThongTinMuonTra(muontra a, string ten_sach, int tungdo);
void AddHead(listMT& listMT, PTR_MT node);

void quanLiMuonTra(TREE_DG dsDG, LIST_DS l);

// ĐỘC GIẢ
TREE_DG timKiemDocGiaTheoMa(TREE_DG& dsDG, int maDocGia);
void themDG(TREE_DG& dsDG, TREE_DG nodeDocGia);
int xuatDanhSachDocGia(TREE_DG dsDG, bool checkXepTheoTen);
void chuyenCaySangMang(TREE_DG dsDG, docgia* arr, int& index);
void xuatThongTinDocGia(docgia a, int tungdo);
int SoluongDG(TREE_DG dsDG);
bool xac_nhan(int x, int y, const char* s, string temp); 
void ToMau(int x, int y, string a, int color);
void ToMau2(int x, int y, int a, int color);
void ToMau3(int x, int y, Date a, int color);
void duyetCay(TREE_DG ds_docGia, DS_TAMTHOI* nodes[], int& n);
void themDocGia(TREE_DG& dsDG);
int nhapDocGia(docgia& x);
int gioiTinh(int x, int y);
void timKiemPhanTuTheMang(TREE_DG& canXoa, TREE_DG& theMang);
int timKiemDocGiaTheoTen(DS_TAMTHOI* arr[], string tuKhoa, int soLuongDG);
void swapDocGia(DS_TAMTHOI*& tamThoi1, DS_TAMTHOI*& tamThoi2);
void sapXepTheoTen(DS_TAMTHOI* arr[], int slDG);
//DOC VA GHI FILE
void docFileDG(TREE_DG& dsDG);
void ghiFileDanhSachDocGia(TREE_DG t);
void ghiFileDocGia(TREE_DG q, ofstream& fileout);
int demTongSoSachDocGiaTungMuon(docgia x);
// ===================== triển khai hàm

void khoiTaoDS(TREE_DG& dsDG)
{
	dsDG = NULL;
}
// khởi tạo node mượn trả
PTR_MT taoNodeMT(muontra x)
{
	PTR_MT nodeMT = new node_muontra;
	nodeMT->data = x;
	nodeMT->next = NULL;

	return nodeMT;
}
// khởi tạo ds mượn trả
void khoiTaoMuonTra(listMT& dsMT)
{
	dsMT.pHead = NULL;
}

// số lượng sách độc giả đã và đang mượn
int demTongSoSachDocGiaTungMuon(docgia x)
{
	int n = 0;
	for (PTR_MT p = x.mt.pHead; p != NULL; p = p->next)
		n++;
	return n;
}
// GHI FILE ĐỘC GIẢ
void ghiFileDanhSachDocGia(TREE_DG t)
{
	ofstream fileout("DOCGIA.txt");
	int n = SoluongDG(t);
	fileout << n << endl;
	ghiFileDocGia(t, fileout);
	fileout.close();
}
// ĐẠO HÀM GHI THÔNG TIN ĐỘC GIẢ VÀO FILE
void ghiFileDocGia(TREE_DG nodeDocGia, ofstream& fileout)
{
	//if (nodeDocGia != NULL)
	//{
	//	fileout << nodeDocGia->data.mathe << ',';
	//	fileout << nodeDocGia->data.ho << ',';
	//	fileout << nodeDocGia->data.ten << ',';
	//	fileout << nodeDocGia->data.phai << ',';
	//	fileout << nodeDocGia->data.trangthaithe << endl;
	//	fileout << demTongSoSachDocGiaTungMuon(nodeDocGia->data) << endl;
	//	for (PTR_MT p = nodeDocGia->data.mt.pHead; p != NULL; p = p->next)
	//	{
	//		fileout << p->data.masach << ',';
	//		fileout << p->data.trangthai << ',';
	//		fileout << p->data.ngaymuon.ngay << '/';
	//		fileout << p->data.ngaymuon.thang << '/';
	//		fileout << p->data.ngaymuon.nam << ',';
	//		fileout << p->data.ngaytra.ngay << '/';
	//		fileout << p->data.ngaytra.thang << '/';
	//		fileout << p->data.ngaytra.nam << endl;
	//	}
	//	ghiFileDocGia(nodeDocGia->left, fileout);
	//	ghiFileDocGia(nodeDocGia->right, fileout);
	//}

	queue<TREE_DG> bf_queue;

	bf_queue.push(nodeDocGia);

	/* Vòng lặp kết thúc khi queue rỗng */
	while (!bf_queue.empty()) {
		TREE_DG current = bf_queue.front(); // Tham chiếu trực tiếp đến phần tử đầu tiên của vùng chứa hàng đợi.
		bf_queue.pop(); /* Lấy phần tử đầu tiên ra khỏi queue */
		/*cout << current->data << ", ";*/
		// GHI VÀO FILE ĐỘC GIẢ HIỆN TẠI
		fileout << current->data.mathe << ',';
		fileout << current->data.ho << ',';
		fileout << current->data.ten << ',';
		fileout << current->data.phai << ',';
		fileout << current->data.trangthaithe << endl;
		fileout << demTongSoSachDocGiaTungMuon(current->data) << endl;
		for (PTR_MT p = current->data.mt.pHead; p != NULL; p = p->next)
		{
			fileout << p->data.masach << ',';
			fileout << p->data.trangthai << ',';
			fileout << p->data.ngaymuon.ngay << '/';
			fileout << p->data.ngaymuon.thang << '/';
			fileout << p->data.ngaymuon.nam << ',';
			fileout << p->data.ngaytra.ngay << '/';
			fileout << p->data.ngaytra.thang << '/';
			fileout << p->data.ngaytra.nam << endl;
		}

		/* Enqueue con trái và con phải của current vào bf_queue.*/
		if (current->left != NULL) {
			bf_queue.push(current->left);
		
		}
		if (current->right != NULL) {
			bf_queue.push(current->right);
			
		}
	}
}
// ĐỌC FILE ĐỘC GIẢ
void docFileDG(TREE_DG& dsDG)
{
	ifstream f("DOCGIA.txt", ios::in);
	muontra muonTra;
	docgia docGia;
	int n = 0;
	int temp = 0;
	f >> n;
	for (int j = 0; j < n; j++)
	{
		f >> docGia.mathe;
		f.ignore();
		getline(f, docGia.ho, ',');
		getline(f, docGia.ten, ',');
		getline(f, docGia.phai, ',');
		f >> docGia.trangthaithe;
		f.ignore();
		f >> temp;
		f.ignore();
		// khởi tạo nocde độc giả
		DOCGIA* nodeDocGia = new DOCGIA;
		nodeDocGia->data = docGia;
		nodeDocGia->left = nodeDocGia->right = NULL;
		khoiTaoMuonTra(nodeDocGia->data.mt); // khoi tao danh sach muon tra

		themDG(dsDG, nodeDocGia); // thêm node độc giả vào danh sách


		for (int i = 0; i < temp; i++)
		{
			getline(f, muonTra.masach, ',');
			f >> muonTra.trangthai;      f.ignore();
			f >> muonTra.ngaymuon.ngay;  f.ignore();
			f >> muonTra.ngaymuon.thang; f.ignore();
			f >> muonTra.ngaymuon.nam;   f.ignore();
			f >> muonTra.ngaytra.ngay;   f.ignore();
			f >> muonTra.ngaytra.thang;  f.ignore();
			f >> muonTra.ngaytra.nam;    f.ignore();
			AddHead(nodeDocGia->data.mt, taoNodeMT(muonTra));
		}
	}
	f.close();
}

// thêm một độc giả vào cây
void themDG(TREE_DG& dsDG, TREE_DG nodeDocGia)
{
	if (dsDG == NULL)
	{
		dsDG = nodeDocGia;
	}
	else
	{
		if (nodeDocGia->data.mathe < dsDG->data.mathe)
			themDG(dsDG->left, nodeDocGia);
		else if (nodeDocGia->data.mathe > dsDG->data.mathe)
			themDG(dsDG->right, nodeDocGia);
	}
}


// thêm mượn trả
void AddHead(listMT& listMT, PTR_MT node)
{
	if (listMT.pHead == NULL)
	{
		listMT.pHead = node;
	}
	else
	{
		node->next = listMT.pHead;
		listMT.pHead = node;
	}
}

// xuất danh sách độc giả
int xuatDanhSachDocGia(TREE_DG dsDG, bool checkXepTheoTen)
{
	int n = SoluongDG(dsDG); // số lượng độc giả trong mảng
	int t_sotrang = (n - 1) / 40 + 1;
	DS_TAMTHOI *arr[MAX_DS] ; // khai bao mảng bằng số lượng độc giả
	int index = 0; // số lượng phần tử trong mảng
	duyetCay(dsDG, arr, index);

	if (checkXepTheoTen == true)
	{
		sapXepTheoTen(arr, n);
	}
	int tungdo = 1; // dòng đâu tiên trong danh sách
	for (int i = 0; i < t_sotrang; i++)
	{
		for (int j = i * 40; j < (40 * i) + 40 && j < n && tungdo < 40; j++)
			xuatThongTinDocGia(arr[j]->docGia->data, tungdo++); 

		gotoxy(105, 42); cout << i + 1 << "/" << t_sotrang;


	
		char c = _getch();
		if (c == -32 || c == 0 )
			c = _getch();
		if (c == 77)
		{
	
			tungdo = 1;
			if (i == t_sotrang - 1)
				i = -1;
		}
		else if (c == 75)
		{

			tungdo = 1;
			if (i == 0)
				i = t_sotrang - 2;
			else
			{
				i -= 2;
				continue;
			}
		}
		if (c == F2)
		{
			return F2;
		}
		if (c == F4)
		{
			return F4;
		}
		if (c == F1)
		{
			return F1;
		}
		if (c == ESC)
		{
			return ESC;
		}
		if (c == ENTER)
		{
			return ENTER;
		}
		else
		{

			delete[] arr;
			return 0;
		}
	}
	delete[] arr;
	return 0;
}
// đếm số đọc giả trong cây
int SoluongDG(TREE_DG dsDG)
{
	int n = 1;
	if (dsDG)
	{
		n += SoluongDG(dsDG->left);
		n += SoluongDG(dsDG->right);
		return n;
	}
	else return 0;
}
// duyệt cây copy dữ liệu vào mảng
void chuyenCaySangMang(TREE_DG dsDG, docgia* arr, int& index)
{
	if (dsDG != NULL)
	{
		chuyenCaySangMang(dsDG->left, arr, index);
		arr[index++] = dsDG->data;
		chuyenCaySangMang(dsDG->right, arr, index);
	}// nếu cây rỗng thoát hàm
	else
		return;
}
// Xuất thông tin của 1 độc giả
void xuatThongTinDocGia(docgia a, int tungdo)
{
	int x = wherex();
	int y = wherey();
	SetColor(14);
	gotoxy(50, 0);
	cout << "MA DOC GIA";
	gotoxy(65, 0);
	cout << "HO";
	gotoxy(90, 0);
	cout << "TEN";
	gotoxy(120, 0);
	cout << "PHAI";
	gotoxy(135, 0);
	cout << "TRANG THAI THE";
	SetColor(15);
	gotoxy(50, tungdo);
	cout << a.mathe;
	gotoxy(65, tungdo);
	cout << a.ho;
	gotoxy(90, tungdo);
	cout << a.ten;
	gotoxy(120, tungdo);
	cout << a.phai;
	gotoxy(137, tungdo);
	if (a.trangthaithe == 1)
		cout << "HOAT DONG";
	else
		cout << "KHOA";
	SetColor(7);
	gotoxy(x, y);
}
// tìm kiếm độc giả trong danh sách với mã độc giả
TREE_DG timKiemDocGiaTheoMa(TREE_DG& dsDG, int maDocGia)
{
	if (dsDG != NULL)
	{
		if (dsDG->data.mathe == maDocGia)
			return dsDG;
		else if (dsDG->data.mathe < maDocGia)
			return timKiemDocGiaTheoMa(dsDG->right, maDocGia);
		else
			return timKiemDocGiaTheoMa(dsDG->left, maDocGia);
	}
	else
		return NULL;
}
void xuatSachMuon(TREE_DG docGia, LIST_DS l)
{
	int kt = 0; // kiểm tra nếu độc giả có sách đang mượn thì tăng. nếu không có sách đang mượn =0
	int tungdo = 0;
	SetColor(15);
	int x = wherex();
	int y = wherey();
	gotoxy(45, tungdo);
	cout << "Ma Sach";
	gotoxy(60, tungdo);
	cout << "Ten Sach";
	gotoxy(100, tungdo);
	cout << "Ngay Muon";
	gotoxy(130, tungdo);
	cout << "Ngay Tra";
	gotoxy(160, tungdo);
	cout << "Trang Thai";
	for (PTR_MT p = docGia->data.mt.pHead; p != NULL; p = p->next)
	{
		for (int i = 0; i < l.n; i++)
		{
			/*for (PTR_DMS k = l.ds[i]->dms; k != NULL; k = k->next)
			{
				if (p->data.masach == k->data.masach)
				{
					if (p->data.trangthai == 0 || p->data.trangthai == 2)
					{
						kt++;
						XUAT_THONG_TIN_MT(p->data, l.ds_dausach[i]->tensach, ++tungdo);
					}
				}
			}*/

			if (l.ds[i]->ISBN == tachMaSach(p->data.masach)) {
				if (p->data.trangthai == 0 || p->data.trangthai == 2)
				{
					kt++;
					xuatThongTinMuonTra(p->data, l.ds[i]->tensach, ++tungdo);
				}
			}
		}
	}	

}

// in thong tin của 1 phiếu mượn trả
void xuatThongTinMuonTra(muontra a, string ten_sach, int tungdo)
{
	SetColor(15);
	int x = wherex();
	int y = wherey();
	gotoxy(45, 0);
	cout << "Ma Sach";
	gotoxy(60, 0);
	cout << "Ten Sach";
	gotoxy(100, 0);
	cout << "Ngay Muon";
	gotoxy(130, 0);
	cout << "Ngay Tra";
	gotoxy(160, 0);
	cout << "Trang Thai";
	gotoxy(45, tungdo);
	cout << a.masach;
	gotoxy(60, tungdo);
	cout << ten_sach;
	gotoxy(100, tungdo);
	cout << a.ngaymuon.ngay << "/" << a.ngaymuon.thang << "/" << a.ngaymuon.nam;
	gotoxy(130, tungdo);
	cout << a.ngaytra.ngay << "/" << a.ngaytra.thang << "/" << a.ngaytra.nam;
	gotoxy(160, tungdo);
	if (a.trangthai == 0)
		cout << "DANG MUON";
	else if (a.trangthai == 1)
		cout << "DA TRA";
	else
		cout << "LAM MAT";
	gotoxy(x, y);
	SetColor(7);
}

// Muon sach
void MUON_SACH(TREE_DG& t, LIST_DS& l, TREE_DG& nodeDG)
{
	int bienThaoTac = 0; // biến kiem tra ESC cua ham nhap
	int dem; // dem sách độc giả đang mượn
	while (1)
	{
		dem = 0;

		

		if (nodeDG->data.trangthaithe == 0) // thẻ bị khóa
		{
			inThongBao("THE DOC GIA BI KHOA.TRA SACH DE TIEP TUC");
			Sleep(1000);
			xoaThongBao();
			break;
		}
		if (kiemTraQuaHan(nodeDG) == true) // độc giả mượn sách quá hạn
		{
			
			inThongBao("DOC GIA MUON SACH QUA HAN. KHONG THE MUON");
			Sleep(1000);
			xoaThongBao();
			break;
		}

		dem = demSoSachDocGiaDangMuon(nodeDG); // kiểm tra số lượng sách độc giả đã mượn nếu > 3 không mượn được
		if (dem >= 3)
		{
			
			inThongBao("! DOC GIA MUON QUA 3 CUON. !TRA SACH DE MUON THEM");
			Sleep(1000);
			xoaThongBao();
			break;
		}
		else if(dem == 0){
			inThongBao("HIEN TAI DOC GIA CHUA MUON SACH");
			Sleep(1000);
			xoaThongBao();
		}
		PTR_DMS k = NULL;
		string ma_sach;
		string ma_dau_sach;
		
		int indexDS = 0;
		gotoxy(99, 42); cout << "                         ";
		while (1) // vòng while dừng khi số lượng sách hơn 3 hoặc nhấn phím ESC
		{
			bool check = false; // kiem tra co tim thay ma sach hay ko
			if (dem >= 3) break; // mượn đến khi nào sách bằng 3 cuốn thì dừng 
			system("cls");
			gotoxy(20, 5);
			cout << "CHE DO MUON SACH";
			xuatSachMuon(nodeDG, l);
			ma_sach = ""; // mỗi lần nhập là reset mã sách
			gotoxy(35, 30);
			cout << "NHAP MA SACH";
			bienThaoTac = nhap_ki_tu(ma_sach, 1 , 0, 0);
			

			if (bienThaoTac == -1) // ESC 
				return;
			bool checkExistDMS = false;
			ma_dau_sach = tachMaSach(ma_sach); // tách mã sách thành mã đầu sách
			indexDS = timKiemDauSachTheoMa(l, ma_dau_sach); // tìm kiếm sách theo mã trả về vị trí của đầu sách
			if (indexDS == -1) // khoong tim thay
			{

				inThongBao("MA SACH KHONG DUNG");
				Sleep(1000);
				xoaThongBao();
				continue;
			}
			else // tim thay lay vi tri cua i
			{
				if (kiemTraSachDangMuon(nodeDG, ma_sach) == true) // ĐANG MƯỢN SÁCH THUỘC ĐS TƯƠNG TỰ
				{
					
					inThongBao("DOC GIA DANG MUON SACH NAY");
					Sleep(1000);
					xoaThongBao();
					continue;
				}
				// TRƯỜNG HỢP TÌM RA SÁCH NHƯNG KO CÓ BẢN DANH MỤC SÁCH MÀ CHI CÓ MỖI ĐẦU SÁCH
				if (l.ds[indexDS]->dms == NULL) {
					
					inThongBao("SACH NAY CHI CON BAN GOC, VUI LONG MUON SACH KHAC");
					Sleep(1000);
					xoaThongBao();
					continue;
				}
				for (k = l.ds[indexDS]->dms; k != NULL; k = k->next) // vòng lặp kiểm tra tình trạng sách và cập nhật tình trạng sách
				{
					if (k->data.masach == ma_sach)
					{
						if (k->data.trangthai == 0)
						{
							dem++; // thay đổi số lượng sách mượn để tí nữa kiểm tra 
							check = true; // đánh dấu là mượn thành công để chuẩn bị vào bước ghi file lưu thông tin
							k->data.trangthai = 1; // cap nhat sach co nguoi muon
							checkExistDMS = true;
							break;
						}
						else if (k->data.trangthai == 1)
						{
							
							inThongBao("SACH DA CO NGUOI MUON");
							Sleep(1000);
							xoaThongBao();
							break;
						}
						else if (k->data.trangthai == 2)
						{
							
							inThongBao("SACH DA THANH LI");
							Sleep(1000);
							xoaThongBao();
							break;
						}
					}
				}
				if (checkExistDMS == false) {
					inThongBao("DANH MUC SACH KHONG TON TAI");
					Sleep(1000);
					xoaThongBao;
				}
				if (check == true)
				{
					// -------------- cập nhật thông tin mượn trả ----------
					muontra x;  // khai báo một struct mượn trả
					x.masach = ma_sach;
					l.ds[indexDS]->soluotmuon++; // tăng số lượng mượn cuốn sách
					khoiTaoThongTinMuonSach(x); // khởi tạo thông tin mượn trả
					AddHead(nodeDG->data.mt, taoNodeMT(x)); // tạo node mượn trả rồi thêm vào cuối
					inThongBao("MUON THANH CONG"); // thông báo thêm thành công 
					Sleep(1000);
					xoaThongBao();
					//GhiFileDS(l); // ghi lại gile cập nhật độc giả mượn sách
					//GHI_FILE_DS_DG(t); // ghi lại file cập nhật sách đã có người mượn
				}
				

			}
		}
	}
}


// kiem tra xem doc gia co muon sach qua han hay ko neu qua han rt true <> false
bool kiemTraQuaHan(TREE_DG docGia)
{
	int n = 0;
	for (PTR_MT q = docGia->data.mt.pHead; q != NULL; q = q->next)
	{
		if (q->data.trangthai == 0) // dang muon sach
		{
			n = tinhSoNgay(q->data.ngaymuon);
			cout << n;
			if (n >= 7)
				return true;
		}
	}
	return false;
}

// đếm số sách độc giả đang mượn dùng để kiểm tra điều kiện mượn sách ( chỉ đếm sách có tình trạng đang đọc)
int demSoSachDocGiaDangMuon(TREE_DG t)
{
	int so_sach_muon = 0;
	for (PTR_MT p = t->data.mt.pHead; p != NULL; p = p->next)
	{
		if (p->data.trangthai == 0 || p->data.trangthai == 2) // sách chưa trả
			so_sach_muon++;
	}
	return so_sach_muon;
}

bool kiemTraSachDangMuon(TREE_DG p, string ma_sach)
{
	string s = tachMaSach(ma_sach);
	string temp;
	for (PTR_MT q = p->data.mt.pHead; q != NULL; q = q->next)
	{
		if (q->data.trangthai == 0) // đang mượn sách
		{
			temp = tachMaSach(q->data.masach);
			if (temp == s) // đang mượn cuốn sách có đầu sách tương tự
				return true;
		}
	}
	return false;
}

// lập phiếu mượn sách
void khoiTaoThongTinMuonSach(muontra& x)
{
	// phiếu mượn trả chỉ cần nhập mã sách . ngày mượn sẽ được cập nhật từ hệ thống thời gian thực, trạng thái sẽ mặc định = 0 nghĩa là sách đó đang mượn
	thoiGianThuc(x.ngaymuon);
	x.ngaytra.ngay = 0;
	x.ngaytra.thang = 0;
	x.ngaytra.nam = 0;
	x.trangthai = 0; // trạng thái mặc định =0 độc giả đang mượn cuốn sách
}

void traSach(TREE_DG docGia, LIST_DS l, bool modeTraSach)
{
	int phimThaoTac;
	do
	{
		int n = demSoSachDocGiaDangMuon(docGia);
		if (n < 1)
		{
			inThongBao(modeTraSach == true ? " CHUA MUON SACH MA DOI TRA" : "CHUA MUON SACH MA DOI MAT");
			Sleep(1000);
			xoaThongBao();
			break;
		}
		bool check = false;
		muontra* arr = new muontra[n];
		int indexNow = 0;
		int indexArr = 0;
		for (PTR_MT p = docGia->data.mt.pHead; p != NULL; p = p->next)
		{
			if (p->data.trangthai == 0 || p->data.trangthai == 2)
			{
				arr[indexArr++] = p->data;
			}
		}
		if (indexArr > 0)
		{
			while (!check)
			{
				system("cls"); // xoá màn hình
				gotoxy(20, 5);
				cout << (modeTraSach == true ? "CHE DO TRA SACH" : "CHE DO MAT SACH");
				for (int i = 0; i < n; i++) {  // tô màu hiện thị chọn sách cần trả trong thư viện

					string temp = tachMaSach(arr[i].masach); // tách mã sách thành mã đầu sách 

					int index = timKiemDauSachTheoMa(l, temp); // return vị trí của đầu sách trong mảng

					if (i == indexNow) { // nếu i bằng trạng thái được chọn thì hiện màu vàng

						ToMau(45, i + 1, arr[i].masach, 14); // tô màu mã sách

						// tô màu ngày
						ToMau3(100, i + 1, arr[i].ngaymuon, 14);
						ToMau3(130, i + 1, arr[i].ngaytra, 14);

						ToMau(60, i + 1, l.ds[index]->tensach, 14); // to mau ten sACH

						// tô màu trạng thái
						if (arr[i].trangthai == 0) {
							ToMau(160, i + 1, "DANG MUON", 14);
						}
						else if (arr[i].trangthai == 1) {
							ToMau(160, i + 1, "DA TRA", 14);
						}
						else
							ToMau(160, i + 1, "LAM MAT", 14);
					}
					else { //  nếu i KHÔNG bằng trạng thái được chọn thì hiện màu trắng
						ToMau(45, i + 1, arr[i].masach, 7);
						// tô màu ngày
						ToMau3(100, i + 1, arr[i].ngaymuon, 7);
						ToMau3(130, i + 1, arr[i].ngaytra, 7);
						ToMau(60, i + 1, l.ds[index]->tensach, 7);
						if (arr[i].trangthai == 0) {
							ToMau(160, i + 1, "DANG MUON", 7);
						}
						else if (arr[i].trangthai == 1) {
							ToMau(160, i + 1, "DA TRA", 7);
						}
						else
							ToMau(160, i + 1, "LAM MAT", 7);
					}
				}
				gotoxy(59, indexNow);
				char c = _getch();
				if (c == -32 || c == 0) { 
					c = _getch();
					switch (c)
					{
					case UP:
					case LEFT:
					{
						if (indexNow == 0)
							indexNow =( indexArr -1) ;
						else
							indexNow--;
						break;
					}
					case DOWN:
					case RIGHT:
					{
						if (indexNow == (indexArr - 1))
							indexNow = 0;
						else
							indexNow++;
						break;
					}
					
					}
				}
				if (c == ESC) {
					return;
				}
				if (c == ENTER) {
					// kiểm tra sách này đã được bật trạng thái mất hay chưa?
					bool kiemTraMatSach = false;
					for (PTR_MT p = docGia->data.mt.pHead; p != NULL; p = p->next) {
						if (p->data.masach == arr[indexNow].masach) {
							if (p->data.trangthai == 2 && modeTraSach == false) {
								inThongBao("SACH NAY DA BI MAT TRUOC DO");
								Sleep(1000);
								xoaThongBao();
								kiemTraMatSach = true;
							}
						
						
						}
						
					}
					if (kiemTraMatSach == true) {
						continue;
					}

					// hộp thoại xác nhận trả hoặc mất sách
					if (xac_nhan(80, 15, modeTraSach == true ? "XAC NHAN TRA SACH " : "XAC NHAN MAT SACH ", arr[indexNow].masach) == true)
						check = true;
					else check = false;
					
				}

				if (check) {
					if (modeTraSach == true) {
						int dem = 0;
						PTR_DMS dms = timKiemDanhMucSach(l, arr[indexNow].masach);
						for (PTR_MT p = docGia->data.mt.pHead; p != NULL; p = p->next) {
							if (p->data.masach == arr[indexNow].masach) {
								p->data.trangthai = 1;
								dms->data.trangthai = 0;
								thoiGianThuc(p->data.ngaytra);
							}
							if (p->data.trangthai == 2) dem++;
						}
						if (dem != 0) // còn sách làm mất -> khóa thẻ
							docGia->data.trangthaithe = 0;
						else
							docGia->data.trangthaithe = 1; // mở thẻ nếu trả được sách đã mất

						
					}
					else {
						PTR_DMS dms = timKiemDanhMucSach(l, arr[indexNow].masach);
						for (PTR_MT p = docGia->data.mt.pHead; p != NULL; p = p->next) {
							if (p->data.masach == arr[indexNow].masach) {
								p->data.trangthai = 2;
								dms->data.trangthai = 2;
								docGia->data.trangthaithe = 0;
								
							}
							
						}
					}
				}
				
				system("cls"); // xong các thao tác vừa mới làm
			}
		}


	} while (true);
}
// XÁC NHẬN mượn trả
bool xac_nhan(int x, int y, const char* s, string temp)
{
	char c;
	// hiện khung xác nhận trả sach

	gotoxy(x, y);
	cout << s << ": " << temp;

	while (1)
	{
		// hiện thị đang ở lưa chọn có
		gotoxy(x + 25, y + 2); SetColor(252); cout << "CO";
		gotoxy(x + 30, y + 2); SetColor(247); cout << "HUY";
		c = _getch();
		// nếu nhấn enter thì trả về true để xóa
		if (c == 13) {
		
			return true;
		}
		else if (c == 27)
		{
			
			return false;
		}
		if (c == -32) c = _getch();
		if (c == 77 || c == 75)
		{
			// nhấn di chuyển thì chuyển qua hủy ( nếu tiếp tục di chuyển thì quay về vòng lặp)
			gotoxy(x + 25, y + 2); SetColor(247); cout << "CO";
			gotoxy(x + 30, y + 2); SetColor(252); cout << "HUY";
			c = _getch(); if (c == -32) c = _getch();
			if (c == 13 || c == 27) {
				system("cls");
				return false;
			}
		}
	}
}

// các hàm tô màu thông tin mượn và mất sách
void ToMau(int x, int y, string a, int color)
{
	SetColor(color);
	gotoxy(x, y);
	cout << a;
	SetColor(7);
}
void ToMau2(int x, int y, int a, int color)
{
	SetColor(color);
	gotoxy(x, y);
	cout << a;
	SetColor(7);
}
void ToMau3(int x, int y, Date a, int color)
{
	SetColor(color);
	gotoxy(x, y);
	cout << a.ngay << "/" << a.thang << "/" << a.nam;
	SetColor(7);
}

// -------------- duyệt cây theo NLR và đưa vào mảng
void duyetCay(TREE_DG ds_docGia, DS_TAMTHOI* nodes[], int& n)
{
	if (ds_docGia != NULL)
	{
		duyetCay(ds_docGia->left, nodes, n);
		nodes[n] = new DS_TAMTHOI;
		nodes[n]->docGia = ds_docGia;
		nodes[n]->ho = ds_docGia->data.ho;
		nodes[n]->ten = ds_docGia->data.ten;
		n++;
		duyetCay(ds_docGia->right, nodes, n);
	}
}

// thêm độc giả
void themDocGia(TREE_DG &dsDG)
{
	
	docgia docgia;
	ifstream filein("MADOCGIA.txt");
	ofstream filetemp("Temp.txt");
	filein >> docgia.mathe;
	int checkESC = nhapDocGia(docgia);
	if (checkESC < 0) {
		return;
	}
	// khởi tạo nocde độc giả
	DOCGIA* nodeDocGia = new DOCGIA;
	nodeDocGia->data = docgia;
	nodeDocGia->left = nodeDocGia->right = NULL;
	khoiTaoMuonTra(nodeDocGia->data.mt);
	themDG(dsDG, nodeDocGia);
	int temp;
	while (filein >> temp)
	{
		if (temp != docgia.mathe)
			filetemp << temp << endl;
	}
	filein.close();
	filetemp.close();
	remove("MADOCGIA.txt");
	rename("Temp.txt", "MADOCGIA.txt");
	inThongBao("THEM THANH CONG");
	Sleep(1000);
	xoaThongBao();
	ghiFileDanhSachDocGia(dsDG);


}
// hàm nhập độc giả nếu thêm hoàn chỉnh return 1, nhấn esc return -2
int nhapDocGia(docgia &x)
{
	ShowCur(true);
	int khoangCach = 8;
	int k = 0; // check ESC nhap
	x.trangthaithe = 1; // trạng thái lúc thêm độc giả auto =1. có thể mượn sách
	gotoxy(X_Add , Y_Add);
	cout << "TINH TRANG:  HOAT DONG";
	gotoxy(X_Add , Y_Add + 2);
	cout << "MA THE: ";
	cout << x.mathe;
	x.ho = "";
	gotoxy(X_Add , Y_Add + 4);
	cout << "HO: ";
	k = nhap_ki_tu(x.ho, 0 , 2, khoangCach);
	if (k == -1) // ESC
		return -2;
	x.ten = "";
	gotoxy(X_Add , Y_Add + 6);
	cout << "TEN: ";
	k = nhap_ki_tu(x.ten, 0 , 3, khoangCach);
	if (k == -1) // ESC
		return -2;
	
	int checkGioiTinh = gioiTinh(X_Add, 38);
	if (checkGioiTinh == 1) {
		x.phai = "NAM";
	}
	else if (checkGioiTinh == 2) {
		x.phai = "NU";
	}
	else return -2;
	ShowCur(false);
	
}

// lựa chọn giới tính
int gioiTinh(int x, int y)
{
	ShowCur(false);
	char c;
	// hiện khung xác nhận trả sach

	gotoxy(x, y);
	cout << "GIOI TINH: ";

	while (1)
	{
		// hiện thị đang ở lưa chọn có
		gotoxy(x + 15, y ); SetColor(252); cout << "NAM";
		gotoxy(x + 20, y ); SetColor(247); cout << "NU";
		c = _getch();
		// nếu nhấn enter thì trả về true để xóa
		if (c == 13) {

			return 1;
		}
		else if (c == 27)
		{

			return -1;
		}
		if (c == -32) c = _getch();
		if (c == 77 || c == 75)
		{
			// nhấn di chuyển thì chuyển qua hủy ( nếu tiếp tục di chuyển thì quay về vòng lặp)
			gotoxy(x + 15, y ); SetColor(247); cout << "NAM";
			gotoxy(x + 20, y ); SetColor(252); cout << "NU";
			c = _getch(); if (c == -32) c = _getch();
			if (c == 13 ) {				
				return 2;
			}
			else if (c == 27) {
				return -1;
			}
		}
	}
}

// quản lí mượn, trả và mất sách 
void quanLiMuonTra(TREE_DG dsDG, LIST_DS l)
{
	int bienThaoTac = 0; // biến kiem tra ESC cua ham nhap

	do {

		string maDocGiaString = "";  // mã độc giả để tí tìm kiếm thông tin độc giả
		TREE_DG nodeDG;// lưu  độc giả tìm được


		khoiTaoDS(nodeDG);
		int check = xuatDanhSachDocGia(dsDG, false); // xuất danh sách độc giả
		int tungdo = 0;
		gotoxy(40, 30);
		cout << "NHAP MA DG: ";
		bienThaoTac = nhap_ki_tu(maDocGiaString, 2, 0, 3); // mã độc giả dạng string
	
		int maDocGia = 0; // mã độc giả dạng số
		maDocGia = stringToNumber(maDocGiaString);  // hàm chuyển đổi mã độc giả



		if (bienThaoTac == -1) // ESC
			break;
		nodeDG = timKiemDocGiaTheoMa(dsDG, maDocGia);
		if (nodeDG == NULL)
		{

			inThongBao("MA DOC GIA KHONG DUNG");
			Sleep(1000);
			xoaThongBao();
			continue;
		}
		else
		{
		DC:
			// hiện số sách mà độc giả đang mượn
			system("cls");
			gotoxy(20, 5);
			cout << "CHE DO XEM";
			xuatSachMuon(nodeDG, l);
			gotoxy(20, 20);
			cout << "F2: MUON SACH -- F4: TRA SACH -- F5: MAT SACH";

			// dừng màn hinh chờ phím
			char phimThaoTac = _getch();
			if (phimThaoTac == 0) {
				phimThaoTac = _getch();
				if (phimThaoTac == 60) { // muon sach
					MUON_SACH(dsDG, l, nodeDG);
					ghiFileDanhSachDocGia(dsDG);
					ghiFileDS(l);
				}
				else if (phimThaoTac == 62) { // tra sach
					traSach(nodeDG, l, true);
					ghiFileDanhSachDocGia(dsDG);
					ghiFileDS(l);
				}
				else if (phimThaoTac == 63) {
					traSach(nodeDG, l, false);
					ghiFileDanhSachDocGia(dsDG);
					ghiFileDS(l);
				}

			}
			if (phimThaoTac == 27) {
				break;
			}

			goto DC;



		}
	} while (1);
}

// hàm có chức năng xóa 1 độc giả bất kì theo mã độc giả
void xoaDocGia(TREE_DG& dsDG, int maDocGia)
{
	if (dsDG != NULL)
	{
		// duyệt cây để tìm phần tử cần xóa
		if (dsDG->data.mathe < maDocGia)
		{
			xoaDocGia(dsDG->right, maDocGia);
		}
		else if (dsDG->data.mathe > maDocGia)
		{
			xoaDocGia(dsDG->left, maDocGia);
		}
		// đã tìm được mã độc giả
		else
		{
			int temp = demSoSachDocGiaDangMuon(dsDG);
			if (temp > 0)
			{
				inThongBao("DOC GIA DANG MUON SACH, VUI LONG TRA SACH TRUOC KHI XOA");
				Sleep(1000);
				xoaThongBao();
				return;
			}
			DOCGIA* nodeTheMang = dsDG;
			// xóa node có 1 con hoặc không có con nào
			if (dsDG->left == NULL) // cây con phải
			{
				dsDG = dsDG->right;
			}
			else if (dsDG->right == NULL) // cây con trái
			{
				dsDG = dsDG->left;
			}
			// xóa node có 2 con.Trái nhất của cây con phải
			else
			{
				// trái nhất của cây con phải
				timKiemPhanTuTheMang(nodeTheMang, dsDG->right);
			}
			delete nodeTheMang;
			inThongBao("XOA THANH CONG");
			Sleep(1000);
			xoaThongBao();
		}
	}
}


// TÌM PHÂN TỬ THẾ MẠNG TRONG CÂY NHỊ PHÂN TÌM KIẾM
void timKiemPhanTuTheMang(TREE_DG& canXoa, TREE_DG &theMang )
{
	// duyệt đến phần tử trái nhất của cây
	if (theMang->left != NULL)
	{
		timKiemPhanTuTheMang(canXoa, theMang->left);
	}
	// đã tìm được phần tử thế mạng
	else
	{
		canXoa->data = theMang->data;
		canXoa = theMang;
		theMang = theMang->right;
	}
}

// hóa đoán vị trí trong mảng con trỏ
void swapDocGia(DS_TAMTHOI* &tamThoi1, DS_TAMTHOI* &tamThoi2)
{
	DS_TAMTHOI* tamThoi;
	tamThoi = tamThoi1;
	tamThoi1 = tamThoi2;
	tamThoi2 = tamThoi;
	

}

// sắp xếp độc giả theo tên + họ tăng dần
void sapXepTheoTen(DS_TAMTHOI* arr[], int slDG)
{
	for (int i = 0; i < slDG - 1; i++)
	{
		for (int j = i + 1; j < slDG; j++)
		{  // kiểm tra tên 2 đg
			if (arr[i]->ten > arr[j]->ten)
			{
				// hoán đổi vị trí
				swapDocGia(arr[i], arr[j]);
			} // ngược lại
			else if (arr[i]->ten == arr[j]->ten)
			{ // kiểm tra họ 2 đg
				if (arr[i]->ho < arr[j]->ho)
				{ // hoán đổi vị trí
					swapDocGia(arr[i], arr[j]);
				}
			}
		}
	}
}

// tìm kiếm độc giả theo tên
int timKiemDocGiaTheoTen(DS_TAMTHOI* arr[], string tuKhoa, int soLuongDG)
{


	system("cls");
	ShowCur(false);
		
	
	int vitri_timthay;
	bool KT; //biến vòng while nhỏ
	char signal; //biến bắt phím
	
		for (int i = 0; i < soLuongDG; i++) //duyệt từ đầu đến cuối danh sách đầu sách
		{
			//tìm vị trí của chuỗi con tuKhoa trong tên độc giả
			vitri_timthay = arr[i]->ten.find(tuKhoa);
			if (vitri_timthay != string::npos) //npos - tương tự như null
			{
				xuatThongTinDocGia(arr[i]->docGia->data, 1);

			}
		}
		 signal = _getch();
		return 0;

}