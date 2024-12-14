#include<stdio.h>                                                                              
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include "StudentManager.h"		//以下代码要用到头文件StudentManager.h中的menu，因此把该头文件包含进来

int main(int argc, char* arv[])
{
	if (!identify())
	{
		// 如果认证失败，直接退出程序。
		return 1;
	}
	
	//创建链表
	List list = { 0 };
	//内存设置
	memset(&list, 0, sizeof(List));
	//02 10m	//从list的地址开始，将接下来sizeof(s)个字节全部设为0，确保结构体初始化，也防止野指针出现

	int isRunning = true;
	while (isRunning)	//实现多次功能选择，而非选择一次就退出
	{

		switch (menu())	//增加代码可读性
		{
		case Quit:
			isRunning = false;
			system("cls");
			printf("已退出学生成绩管理系统\n");
			system("pause");
			return 1;
			break;
		case Entry:
			entryStudent(&list);
			break;
		case Print:
			printStudent(&list);
			break;
		case Remove:
			removeStudent(&list);
			break;
		case Alter:
			alterStudent(&list);
			break;
		case Save:
			saveStudentHuman(&list);
			break;
		case Analyse:
			analyseStudent(&list);
			break;
		case Find:
			findStudent(&list);
			break;
		case Rank:
			rankStudent(&list);
			break;
		case Read:
			readStudentHuman(&list);
			break;

		default:
			printf("输入的选项错误\n");
			//isRunning = false;	//但如何再进入菜单呢
			break;
		}

		if (isRunning)
		{
			//让程序暂停一会儿
			system("pause");
			//清屏，用以删除循环打印的多个菜单
			system("cls");
		}	
		}

		return 0;
	
}

