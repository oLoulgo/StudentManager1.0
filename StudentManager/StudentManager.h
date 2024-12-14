#pragma once
#define MAX 101
#define MIN -1
#define Max_length 50
#define true 1
#define false -1
#define Password "1"
#define Manager "1"

/*ѧ���ṹ*/
typedef struct Student
{
	unsigned long long number;	//ѧ��
	char name[Max_length];		//����
	char class[Max_length];		//�༶
	float math;					//��ѧ�ɼ�
	float english;				//Ӣ��ɼ�
	float computer;				//������ɼ�
	float sum;					//�����ܳɼ�
	float average;				//����ƽ����
}Student;

/*�ڵ� Node*/
typedef struct Node
{
	Student stu;		//ѧ��
	struct Node* next;	//ָ����һ���ڵ��ָ��
}Node;	//����ֱ��ʹ�������������Ϊʹ��ʱδ�����������ں���

/*����*/
typedef struct List
{
	Node* front;	//ָ���һ���ڵ�
	int size;		//��ǰ�ڵ�����
}List;

/*�˵�����*/
typedef enum MenuOptions
{
	Quit,		//�˳�ϵͳ
	Entry,		//¼��ѧ��
	Print,		//��ӡѧ��
	Remove,		//ɾ��ѧ��
	Alter,		//�޸�ѧ��
	Save,		//����ѧ��
	Analyse,	//�ɼ�����
	Find,		//����ѧ��
	Rank,		//ѧ������
	Read,		//��ȡѧ��
}MenuOptions;

/*��ӡ�˵�������ʾ�û�ѡ����*/
int menu();

/*ѧ��¼��*/
void entryStudent(List* list);

/*ѧ����ӡ*/
void printStudent(List* list);

/*����ѧ��*/
void saveStudentHuman(List* list);

/*��ȡѧ��*/
void readStudentHuman(List* list);

/*����ѧ��*/
void findStudent(List* list);

/*�޸�ѧ��*/
void alterStudent(List* list);

/*ɾ��ѧ��*/
void removeStudent(List* list);

/*��ƽ���ɼ�����*/
void rankStudent(List* list);

/*�༶�ɼ�����*/
void analyseStudent(List* list);

/*�����֤*/
int identify();