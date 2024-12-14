#include<stdio.h>                                                                              
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include "StudentManager.h"		//���´���Ҫ�õ�ͷ�ļ�StudentManager.h�е�menu����˰Ѹ�ͷ�ļ���������

int main(int argc, char* arv[])
{
	if (!identify())
	{
		// �����֤ʧ�ܣ�ֱ���˳�����
		return 1;
	}
	
	//��������
	List list = { 0 };
	//�ڴ�����
	memset(&list, 0, sizeof(List));
	//02 10m	//��list�ĵ�ַ��ʼ����������sizeof(s)���ֽ�ȫ����Ϊ0��ȷ���ṹ���ʼ����Ҳ��ֹҰָ�����

	int isRunning = true;
	while (isRunning)	//ʵ�ֶ�ι���ѡ�񣬶���ѡ��һ�ξ��˳�
	{

		switch (menu())	//���Ӵ���ɶ���
		{
		case Quit:
			isRunning = false;
			system("cls");
			printf("���˳�ѧ���ɼ�����ϵͳ\n");
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
			printf("�����ѡ�����\n");
			//isRunning = false;	//������ٽ���˵���
			break;
		}

		if (isRunning)
		{
			//�ó�����ͣһ���
			system("pause");
			//����������ɾ��ѭ����ӡ�Ķ���˵�
			system("cls");
		}	
		}

		return 0;
	
}

