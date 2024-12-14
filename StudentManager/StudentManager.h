#pragma once
#define MAX 101
#define MIN -1
#define Max_length 50
#define true 1
#define false -1
#define Password "1"
#define Manager "1"

/*学生结构*/
typedef struct Student
{
	unsigned long long number;	//学号
	char name[Max_length];		//姓名
	char class[Max_length];		//班级
	float math;					//数学成绩
	float english;				//英语成绩
	float computer;				//计算机成绩
	float sum;					//三科总成绩
	float average;				//三科平均分
}Student;

/*节点 Node*/
typedef struct Node
{
	Student stu;		//学生
	struct Node* next;	//指向下一个节点的指针
}Node;	//不能直接使用这个别名，因为使用时未出来，定义在后面

/*链表*/
typedef struct List
{
	Node* front;	//指向第一个节点
	int size;		//当前节点数量
}List;

/*菜单功能*/
typedef enum MenuOptions
{
	Quit,		//退出系统
	Entry,		//录入学生
	Print,		//打印学生
	Remove,		//删除学生
	Alter,		//修改学生
	Save,		//保存学生
	Analyse,	//成绩分析
	Find,		//查找学生
	Rank,		//学生排序
	Read,		//读取学生
}MenuOptions;

/*打印菜单，并提示用户选择功能*/
int menu();

/*学生录入*/
void entryStudent(List* list);

/*学生打印*/
void printStudent(List* list);

/*保存学生*/
void saveStudentHuman(List* list);

/*读取学生*/
void readStudentHuman(List* list);

/*查找学生*/
void findStudent(List* list);

/*修改学生*/
void alterStudent(List* list);

/*删除学生*/
void removeStudent(List* list);

/*按平均成绩排序*/
void rankStudent(List* list);

/*班级成绩分析*/
void analyseStudent(List* list);

/*身份验证*/
int identify();