#pragma once
#include <ctime>
using namespace std;
//=====NGÀY THÁNG NĂM=====
struct Date
{
	int ngay;
	int thang;
	int nam;
};



// lấy thời gian thực hệ thống
void thoiGianThuc(Date& x)
{
	time_t t = time(NULL); // trả về thời gian theo dương lịch dưới dạng giây tính theo dương lịch 1/1/1970
	tm* now = localtime(&t);// trả về con trỏ chuỗi thời gian dạng cấu trúc
	x.ngay = now->tm_mday;
	x.thang = now->tm_mon + 1;
	x.nam = now->tm_year + 1900;
}
// tính ngày chênh lệch giữa 2 mốc thời gian
int tinhSoNgay(Date n1)
{
	Date n2;
	thoiGianThuc(n2);
	int sum = 0;
	while (n2.nam >= n1.nam)
	{
		if (n1.nam == n2.nam && n2.thang == n1.thang)
		{
			sum += n2.ngay - n1.ngay;
			break;
		}
		else
		{
			// các tháng 4 6 9 11 có 30 ngày
			if (n1.thang == 4 || n1.thang == 6 || n1.thang == 9 || n1.thang == 11)
			{
				sum += 30 - n1.ngay;
			}
			if (n1.thang == 1 || n1.thang == 3 || n1.thang == 5 || n1.thang == 7 || n1.thang == 8 || n1.thang == 10 || n1.thang == 12)
			{
				sum += 31 - n1.ngay;
			}
			if (n1.thang == 2)
			{
				if (n1.nam % 4 == 0 && n1.nam % 100 != 0 || n1.nam % 400 == 0)
				{
					sum += 29 - n1.ngay;
				}
				else
					sum += 28 - n1.ngay;
			}
			n1.thang++; n1.ngay = 0;
			if (n1.thang == 13)
			{
				// tăng năm lên 1
				n1.nam++;
				n1.thang = 1;
			}
		}
	}
	return sum;
}
