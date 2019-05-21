/********************************************************
*描述：	万年历，在命令行下也能拥有良好的界面
*开发环境： Linux
*输入格式： 日期：yy-mm-dd
*			W：下一年
*			S：上一年
*			A：上个月
*			D：下个月
*			N：输入查询的日期
*			其他：当前日期
*
* ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int Y[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char M[13][5] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
char W[7][5] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};

//显示表头信息
void headline(int month)
{
	printf("\t\t\t%s\n", M[month-1]);

	for(int i=0; i<7; i++)
		printf("%s\t", W[i]);
	printf("\n");

	for(int i=0; i<52; i++)
		printf("=");
	printf("\n");
}

//计算当前月份天数
int monthDays(int year, int month)
{
	if(((year%4==0&&year%100!=0)||year%400==0) && month==2)
		return 29;
	else
		return Y[month-1];
}

//计算当前月份距2019年1月1日有多少天
int cntDays(int year, int month)
{
	int days = 0;
	if(year>=2019)
	{
		for(int y=2019; y<year; y++)
		{
			if((y%4==0&&y%100!=0)||y%400==0)
				days += 366;
			else
				days += 365;
		}
		for(int m=1; m<month; m++)
			days += monthDays(year, m);
	}
	else
	{
		for(int y=2018; y>year; y--)
		{
			if((y%4==0&&y%100!=0)||y%400==0)
				days -= 366;
			else
				days -= 365;
		}
		for(int m=12; m>=month; m--)
			days -= monthDays(year,m);
	}
	return days;
}

//计算1日为星期几
int tabCnt(int year, int month)
{
	int days = cntDays(year,month);
	int tabs = 2;

	if(days > 0)
		tabs += days;
	else 
		tabs = 7-(-days-tabs)%7;
	return tabs%7;
}

//显示日期
void showDate(int year, int month, int day)
{
	printf("Date:%d-%d-%d\n", year, month, day);
	headline(month);		

	int tabs = tabCnt(year,month);
	for(int t=0; t<tabs; t++)
		printf("\t");
	int n = monthDays(year+2019,month);
	for(int d=1; d<=n; d++)
	{
		if(d == day)
			printf("\033[1;42m%d\033[0m\t",d);
		else
			printf("%d\t", d);
		if((d+tabs)%7==0)
			printf("\n");
	}
}

//输入日期
void inputDate(int *year, int *month, int *day)
{
	system("clear");
	printf("Date:");
	scanf("%d-%d-%d", year, month, day);
	while(getchar()!='\n');
}

int main()
{
	struct tm *gm;
	time_t t = time(NULL);
	gm = gmtime(&t);
	int year=2019, month=1, day=1;

	inputDate(&year, &month, &day);
	while(1)
	{
		system("clear");
		showDate(year, month, day);
		printf("\n");

		char choice;
		scanf("%c",&choice);
		while(getchar()!='\n');

		switch(choice)
		{
			case 'W':
				year += 1;
				break;
			case 'S':
				year--;
				break;
			case 'A':
				if(month > 1)
					month -= 1;
				else
				{
					year--;
					month = 12;
				}
				break;
			case 'D':
				if(month < 12)
					month += 1;
				else
				{
					year++;
					month = 1;
				}
				break;
			case 'Q':
				exit(0);
			case 'N':
				inputDate(&year, &month, &day);
				break;
			default:
				year = 1900 + gm->tm_year;
				month = gm->tm_mon + 1;
				day = gm->tm_mday + 1;
				break;
		}
	}

	return 0;
}
