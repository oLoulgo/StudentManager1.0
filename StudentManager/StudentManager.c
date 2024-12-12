#include "StudentManager.h"
#include<stdio.h>		//此处要用到printf和scanf函数
#include<malloc.h>
#include<string.h>

int class_count = 0; // 初始化已记录的班级数量

static Node* CreateNode()	//为创建节点写一个函数，静态内部的？，因为这个代码会复用多次（entryStudent和readStudent）,使代码更简洁
{
	//创建节点
	Node* node = malloc(sizeof(Node));
	if (!node)	//内存不足就分配失败
	{
		printf("malloc failed\n");
		return NULL;
	}
	node->next = NULL;
	return node;
}



int menu()
{
	printf("*-----------------------------------------------------------------------*\n");
	printf("*			   学生成绩管理系统				*\n");
	printf("*-----------------------------------------------------------------------*\n");
	printf("*				选择功能				*\n");
	printf("*-----------------------------------------------------------------------*\n");
	printf("*		1.添加学生信息		6.班级成绩分析			*\n");
	printf("*		2.打印学生信息		7.查找学生信息			*\n");
	printf("*		3.删除学生信息		8.学生数据排序			*\n");
	printf("*		4.修改学生信息		9.读取学生信息			*\n");
	printf("*		5.保存学生信息		0.退出系统			*\n");
	printf("*-----------------------------------------------------------------------*\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entryStudent(List* list)
{
	//创建头结点
	Node* node = CreateNode();	//复用了创建节点

	//输入学生信息
	printf("请输入学生学号>");
	scanf("%llu", &node->stu.number);	//因为是个整型(长整型)，必须取地址&

	printf("请输入学生姓名>");
	scanf("%s", node->stu.name);		//姓名是字符串，是字符数组,数组名就是首地址，因此不用&

	printf("请输入学生班级>");
	scanf("%s", node->stu.class);

	printf("请输入学生数学成绩>");
	scanf("%f", &node->stu.math);

	printf("请输入学生英语成绩>");
	scanf("%f", &node->stu.english);

	printf("请输入学生计算机成绩>");
	scanf("%f", &node->stu.computer);

	node->stu.average = (node->stu.math + node->stu.english + node->stu.computer) /3.0f;

	//插入到链表中
	node->next = list->front;	//头插：新结点指向原链表最后一个，front指向新结点
	list->front = node;
	list->size++;

}

void printStudent(List* list)
{
	int i = 0;
	char className[Max_length] = "";
	printf("请选择显示方式:\n1.显示全部学生信息\n2.按班级显示学生信息\n");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
	{
		printf("*-----------------------------------------------------------------------*\n");
		printf("*	学号	姓名	班级		数学	英语	计算机	平均成绩*\n");
		printf("*-----------------------------------------------------------------------*\n");

		//遍历链表	//04  4m
		Node* curNode = list->front;

		if (curNode == NULL)
		{
			printf("系统中无学生信息\n");
		}

		while (curNode != NULL)
		{
			printf("* %llu\t\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			curNode = curNode->next;
		}
		break;
	}
	case 2:
	{
		printf("请输入班级名字>");
		scanf("%s", className);
		printf("*-----------------------------------------------------------------------*\n");
		printf("*	学号	姓名	班级		数学	英语	计算机	平均成绩*\n");
		printf("*-----------------------------------------------------------------------*\n");

		Node* curNode = list->front;

		if (curNode == NULL)
		{
			printf("系统中无学生信息\n");
		}
		while (curNode != NULL)
		{
			if (strcmp(curNode->stu.class,className)==0)
			{
				printf("* %llu\t\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
					curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			}
			curNode = curNode->next;
		}
		break;
	}
	}

	
}

void saveStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("test_students.txt", "w");	//wb指用二进制写入，因此文件中看不懂
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		fprintf(fp,"%llu\t%s\t%s\t%.lf\t%.lf\t%.lf\t%.lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
		curNode = curNode->next;
	}

	//关闭文件
	fclose(fp);
}

void readStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("test_students.txt", "r");	//r,读的方式
	if (!fp)
	{
		perror("file open failed");
		return;
	}

		//读取学生信息
	while (!feof(fp))	//未读完就一直读
	{
		Node* node = CreateNode();
		if (!node)
			break;
		fscanf(fp,"%llu\t%s\t%s\t%f\t%f\t%f\t%f\n", &node->stu.number, node->stu.name, node->stu.class,
			&node->stu.math, &node->stu.english, &node->stu.computer, &node->stu.average);	//为什么%.lf改成了%f	/原有if （7 ！=）
		//{
		//	free(node);
		//	break;
		//}

		//插入链表
		node->next = list->front;
		list->front = node;
		list->size++;
	}

		//关闭文件
		fclose(fp);

}

void findStudent(List* list)
{
	if (list->size == 0)
	{
		printf("系统中无学生信息\n");
		return;
	}

	char buffer[32];
	printf("请输入学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("*-----------------------------------------------------------------------*\n");
			printf("*	学号	姓名	班级		数学	英语	计算机	平均成绩*\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("* %llu\t\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			printf("*-----------------------------------------------------------------------*\n");
			break;
		}
		curNode = curNode->next;
	}
	if(!curNode)
		{
			printf("未找到所查询学生\n");
		}
	
}

void alterStudent(List* list)	//先查找再修改
{
	if (list->size == 0)
	{
		printf("系统中无学生信息\n");
		return;
	}

	int i = 0;
	int j = 0;

	char buffer[Max_length];
	printf("请输入要修改的学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("*-----------------------------------------------------------------------*\n");
			printf("*				选择功能				*\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("*		1.修改学号		5.修改英语成绩			*\n");
			printf("*		2.修改学生姓名		6.修改计算机成绩		*\n");
			printf("*		3.修改班级		0.停止修改			*\n");
			printf("*		4.修改数学成绩						*\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("\n");
			printf("			    该学生修改前信息				\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("*	学号	姓名	班级		数学	英语	计算机	平均成绩*\n");
			
			printf("* %llu\t\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			printf("\n");
			printf("请选择要修改内容>");
			scanf("%d", &i);

			int isRunning2 = true;
			while (isRunning2)
			{
				switch(i)
				{
					case 1:
						printf("把学号改成：");
						scanf("%llu", &curNode->stu.number);
						break;
					case 2:
						printf("把姓名改成：");
						scanf("%s", curNode->stu.name);
						break;
					case 3:
						printf("把班级改成：");
						scanf("%s", curNode->stu.class);
						break;
					case 4:
						printf("把数学改成：");
						scanf("%f", &curNode->stu.math);
						curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
						break;
					case 5:
						printf("把英语改成：");
						scanf("%f", &curNode->stu.english);
						curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
						break;
					case 6:
						printf("把计算机改成：");
						scanf("%f", &curNode->stu.computer);
						curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
						break;
					case 0:
						isRunning2 = false;
						break;
					default:
						printf("输入的选项错误\n");
						break;
				}

				if (i != 0)
				{
					printf("请选择其它要修改内容>");
					scanf("%d", &i);
					printf("\n");
				}
				else
					break;
			}

			break;
		}
		curNode = curNode->next;
	}

	if (curNode == NULL)
		printf("未找到该学生，修改失败\n");
	else
	{

		printf("			    该学生修改后信息				\n");
		printf("*-----------------------------------------------------------------------*\n");
		printf("*	学号	姓名	班级		数学	英语	计算机	平均成绩*\n");

		printf("* %llu\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.2lf*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
	}

}

void removeStudent(List* list)	//移除前先找到
{
	if (list->size == 0)
	{
		printf("系统中无学生信息\n");
		return;
	}

	char buffer[32];
	printf("请输入要删除的学生的学号或姓名>");
	scanf("%s", buffer);

	//把buffer转成整型
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	Node* prevNode = NULL;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;

	}

	//是否找到
	if (curNode)
	{
		//要删除的是第一个节点
		if (prevNode == NULL)
		{
			list->front = curNode->next;
		}
		else
		{
			prevNode->next = curNode->next;
		}
		free(curNode);
		list->size--;
		printf("删除成功\n");
	}
	else
		printf("未找到该学生，修改失败\n");
}

void rankStudent(List* list) {
	if (list->size == 0)
	{
		printf("系统中无学生信息\n");
		return;
	}  // 如果链表为空或只有一个节点，不需要排序

	Node* sorted = NULL;  // 排序后的链表
	Node* current = list->front;

	while (current != NULL) {
		Node* next = current->next;
		if (sorted == NULL || (current->stu.math + current->stu.english + current->stu.computer) >= (sorted->stu.math + sorted->stu.english + sorted->stu.computer)) {
			current->next = sorted;
			sorted = current;
		}
		else {
			Node* temp = sorted;
			while (temp->next != NULL && (current->stu.math + current->stu.english + current->stu.computer) < (temp->next->stu.math + temp->next->stu.english + temp->next->stu.computer)) {
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
		current = next;
	}

	list->front = sorted;
}

void analyseStudent(List* list) 
{

	if (list->size == 0) 
	{
		printf("系统中无学生信息。\n");
		return;
	}

	char className[Max_length] = "";
	printf("请输入所要分析的班级名字>");
	scanf("%s", className);

	// 初始化统计变量
	int acount = 0;
	float pass_math = 0, pass_english = 0, pass_computer = 0;
	float sum_math = 0, sum_english = 0, sum_computer = 0;
	float max_math = MIN, max_english = MIN, max_computer = MIN;
	float min_math = MAX, min_english = MAX, min_computer = MAX;

	Node* curNode = list->front;
	while (curNode != NULL) 
	{
		if (strcmp(curNode->stu.class, className) == 0)
		{// 累加总分
			sum_math += curNode->stu.math;
			sum_english += curNode->stu.english;
			sum_computer += curNode->stu.computer;

			// 更新最高分
			if (curNode->stu.math > max_math)
				max_math = curNode->stu.math;
			if (curNode->stu.english > max_english)
				max_english = curNode->stu.english;
			if (curNode->stu.computer > max_computer)
				max_computer = curNode->stu.computer;

			// 更新最低分
			if (curNode->stu.math < min_math)
				min_math = curNode->stu.math;
			if (curNode->stu.english < min_english)
				min_english = curNode->stu.english;
			if (curNode->stu.computer < min_computer)
				min_computer = curNode->stu.computer;

			// 统计及格人数
			if (curNode->stu.math >= 60)
				pass_math++;
			if (curNode->stu.english >= 60)
				pass_english++;
			if (curNode->stu.computer >= 60)
				pass_computer++;

			acount++;
		}
		curNode = curNode->next;
	}
	if (acount)
	{
		// 计算平均分
		float ave_math = sum_math / acount;
		float ave_english = sum_english / acount;
		float ave_computer = sum_computer / acount;

		// 计算及格率
		float pass_rate_math = pass_math / acount * 100;
		float pass_rate_english = pass_english / acount * 100;
		float pass_rate_computer = pass_computer / acount * 100;

		// 输出结果
		printf("*-----------------------------------------------------------------------*\n");
		printf("*			    %s班级成绩分析				*\n",className);
		printf("*-----------------------------------------------------------------------*\n");
		printf("*学科		平均分		最高分		最低分		及格率	*\n");
		printf("*-----------------------------------------------------------------------*\n");
		printf("*数学		%.2f		%.2f		%.2f		%.2f%%	*\n", ave_math, max_math, min_math, pass_rate_math);
		printf("*英语		%.2f		%.2f		%.2f		%.2f%%	*\n", ave_english, max_english, min_english, pass_rate_english);
		printf("*计算机		%.2f		%.2f		%.2f		%.2f%%	*\n", ave_computer, max_computer, min_computer, pass_rate_computer);
		printf("*-----------------------------------------------------------------------*\n");


	}
	else
		printf("系统中无该班级学生\n");
}