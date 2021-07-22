#pragma once
#include"DocGia.h"
using namespace std;


struct bien
{
	TREE_DG giaTri; // queue đang chứa các số nguyên
	struct bien* pNext; // con trỏ liên kết giữa các DATA với nhau
};
typedef struct bien DATA;

// khai báo cấu trúc của queue
struct queue
{
	DATA* pHead; //  con trỏ đầu
	DATA* pTail; // con trỏ cuối 
};
typedef struct queue QUEUE;

void KhoiTaoQueue(QUEUE& q);
DATA* KhoiTaoNodeQueue(TREE_DG x);
bool IsEmpty(QUEUE q);
bool Push(QUEUE& q, DATA* p);
bool Pop(QUEUE& q, TREE_DG& x); // x chính là giá trị cần lấy trong DATA

// hàm khởi tạo queue
void KhoiTaoQueue(QUEUE& q)
{
	q.pHead = NULL;
	q.pTail = NULL;
}

// hàm khởi tạo 1 cái DATA
DATA* KhoiTaoNodeQueue(TREE_DG x)
{
	DATA* p = new DATA();
	if (p == NULL)
	{
		cout << "\nKhong du bo nho de cap phat !!!";
		return NULL;
	}
	p->giaTri = x; // thêm giá trị của biến x vào trong data của cái DATA
	p->pNext = NULL;
	return p;
}

// =============== KIỂM TRA QUEUE CÓ RỖNG HAY KHÔNG ===============
bool IsEmpty(QUEUE q)
{
	// nếu danh sách rỗng
	if (q.pHead == NULL)
	{
		return true;
	}
	return false;// danh sách có phần tử
}

// =============== THÊM 1 PHẦN TỬ VÀO CUỐI QUEUE- FIFO ===============
bool Push(QUEUE& q, DATA* p)
{
	if (p == NULL)
	{
		return false;
	}

	// nếu danh sách rỗng
	if (IsEmpty(q) == true)
	{
		q.pHead = q.pTail = p; // DATA p chính là DATA đầu và DATA cuối
	}
	else // danh sách đã có phần tử
	{
		q.pTail->pNext = p; // liên kết con trỏ cuối của danh sách với phần tử p cần thêm vào
		q.pTail = p; // cập nhật lại con trỏ cuối là DATA p
	}
	return true;
}

// =============== LẤY PHẦN TỬ ĐẦU QUEUE VÀ HỦY NÓ ĐI - FIFO ===============
bool Pop(QUEUE& q, TREE_DG& x) // x chính là giá trị cần lấy trong DATA
{
	// nếu danh sách rỗng
	if (IsEmpty(q) == true)
	{
		return false;
	}
	else
	{
		DATA* p = q.pHead; // DATA p chính là DATA thế mạng để tí nữa chúng ta xóa nó đi
		x = p->giaTri; // gán giá trị của DATA đầu stack vào biến x	
		q.pHead = q.pHead->pNext; // cập nhật DATA đầu queue là DATA tiếp theo	
		delete p; // xóa DATA đầu queue vừa lấy 

	}
	return true;// lấy phần tử đầu queue thành công
}
