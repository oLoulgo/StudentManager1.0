#include "StudentManager.h"
#include<stdio.h>		//�˴�Ҫ�õ�printf��scanf����
#include<malloc.h>
#include<string.h>

int class_count = 0; // ��ʼ���Ѽ�¼�İ༶����

static Node* CreateNode()	//Ϊ�����ڵ�дһ����������̬�ڲ��ģ�����Ϊ�������Ḵ�ö�Σ�entryStudent��readStudent��,ʹ��������
{
	//�����ڵ�
	Node* node = malloc(sizeof(Node));
	if (!node)	//�ڴ治��ͷ���ʧ��
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
	printf("*			   ѧ���ɼ�����ϵͳ				*\n");
	printf("*-----------------------------------------------------------------------*\n");
	printf("*				ѡ����				*\n");
	printf("*-----------------------------------------------------------------------*\n");
	printf("*		1.���ѧ����Ϣ		6.�༶�ɼ�����			*\n");
	printf("*		2.��ӡѧ����Ϣ		7.����ѧ����Ϣ			*\n");
	printf("*		3.ɾ��ѧ����Ϣ		8.ѧ����������			*\n");
	printf("*		4.�޸�ѧ����Ϣ		9.��ȡѧ����Ϣ			*\n");
	printf("*		5.����ѧ����Ϣ		0.�˳�ϵͳ			*\n");
	printf("*-----------------------------------------------------------------------*\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entryStudent(List* list)
{
	//����ͷ���
	Node* node = CreateNode();	//�����˴����ڵ�

	//����ѧ����Ϣ
	printf("������ѧ��ѧ��>");
	scanf("%llu", &node->stu.number);	//��Ϊ�Ǹ�����(������)������ȡ��ַ&

	printf("������ѧ������>");
	scanf("%s", node->stu.name);		//�������ַ��������ַ�����,�����������׵�ַ����˲���&

	printf("������ѧ���༶>");
	scanf("%s", node->stu.class);

	printf("������ѧ����ѧ�ɼ�>");
	scanf("%f", &node->stu.math);

	printf("������ѧ��Ӣ��ɼ�>");
	scanf("%f", &node->stu.english);

	printf("������ѧ��������ɼ�>");
	scanf("%f", &node->stu.computer);

	node->stu.average = (node->stu.math + node->stu.english + node->stu.computer) /3.0f;

	//���뵽������
	node->next = list->front;	//ͷ�壺�½��ָ��ԭ�������һ����frontָ���½��
	list->front = node;
	list->size++;

}

void printStudent(List* list)
{
	int i = 0;
	char className[Max_length] = "";
	printf("��ѡ����ʾ��ʽ:\n1.��ʾȫ��ѧ����Ϣ\n2.���༶��ʾѧ����Ϣ\n");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
	{
		printf("*-----------------------------------------------------------------------*\n");
		printf("*	ѧ��	����	�༶		��ѧ	Ӣ��	�����	ƽ���ɼ�*\n");
		printf("*-----------------------------------------------------------------------*\n");

		//��������	//04  4m
		Node* curNode = list->front;

		if (curNode == NULL)
		{
			printf("ϵͳ����ѧ����Ϣ\n");
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
		printf("������༶����>");
		scanf("%s", className);
		printf("*-----------------------------------------------------------------------*\n");
		printf("*	ѧ��	����	�༶		��ѧ	Ӣ��	�����	ƽ���ɼ�*\n");
		printf("*-----------------------------------------------------------------------*\n");

		Node* curNode = list->front;

		if (curNode == NULL)
		{
			printf("ϵͳ����ѧ����Ϣ\n");
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
	//���ļ�
	FILE* fp = fopen("test_students.txt", "w");	//wbָ�ö�����д�룬����ļ��п�����
	if (!fp)
	{
		perror("file open failed");
		return;
	}

	//д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL)
	{
		fprintf(fp,"%llu\t%s\t%s\t%.lf\t%.lf\t%.lf\t%.lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
		curNode = curNode->next;
	}

	//�ر��ļ�
	fclose(fp);
}

void readStudentHuman(List* list)
{
	//���ļ�
	FILE* fp = fopen("test_students.txt", "r");	//r,���ķ�ʽ
	if (!fp)
	{
		perror("file open failed");
		return;
	}

		//��ȡѧ����Ϣ
	while (!feof(fp))	//δ�����һֱ��
	{
		Node* node = CreateNode();
		if (!node)
			break;
		fscanf(fp,"%llu\t%s\t%s\t%f\t%f\t%f\t%f\n", &node->stu.number, node->stu.name, node->stu.class,
			&node->stu.math, &node->stu.english, &node->stu.computer, &node->stu.average);	//Ϊʲô%.lf�ĳ���%f	/ԭ��if ��7 ��=��
		//{
		//	free(node);
		//	break;
		//}

		//��������
		node->next = list->front;
		list->front = node;
		list->size++;
	}

		//�ر��ļ�
		fclose(fp);

}

void findStudent(List* list)
{
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	char buffer[32];
	printf("������ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("*-----------------------------------------------------------------------*\n");
			printf("*	ѧ��	����	�༶		��ѧ	Ӣ��	�����	ƽ���ɼ�*\n");
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
			printf("δ�ҵ�����ѯѧ��\n");
		}
	
}

void alterStudent(List* list)	//�Ȳ������޸�
{
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	int i = 0;
	int j = 0;

	char buffer[Max_length];
	printf("������Ҫ�޸ĵ�ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)
		{
			printf("*-----------------------------------------------------------------------*\n");
			printf("*				ѡ����				*\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("*		1.�޸�ѧ��		5.�޸�Ӣ��ɼ�			*\n");
			printf("*		2.�޸�ѧ������		6.�޸ļ�����ɼ�		*\n");
			printf("*		3.�޸İ༶		0.ֹͣ�޸�			*\n");
			printf("*		4.�޸���ѧ�ɼ�						*\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("\n");
			printf("			    ��ѧ���޸�ǰ��Ϣ				\n");
			printf("*-----------------------------------------------------------------------*\n");
			printf("*	ѧ��	����	�༶		��ѧ	Ӣ��	�����	ƽ���ɼ�*\n");
			
			printf("* %llu\t\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
			printf("\n");
			printf("��ѡ��Ҫ�޸�����>");
			scanf("%d", &i);

			int isRunning2 = true;
			while (isRunning2)
			{
				switch(i)
				{
					case 1:
						printf("��ѧ�Ÿĳɣ�");
						scanf("%llu", &curNode->stu.number);
						break;
					case 2:
						printf("�������ĳɣ�");
						scanf("%s", curNode->stu.name);
						break;
					case 3:
						printf("�Ѱ༶�ĳɣ�");
						scanf("%s", curNode->stu.class);
						break;
					case 4:
						printf("����ѧ�ĳɣ�");
						scanf("%f", &curNode->stu.math);
						curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
						break;
					case 5:
						printf("��Ӣ��ĳɣ�");
						scanf("%f", &curNode->stu.english);
						curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
						break;
					case 6:
						printf("�Ѽ�����ĳɣ�");
						scanf("%f", &curNode->stu.computer);
						curNode->stu.average = (curNode->stu.math + curNode->stu.english + curNode->stu.computer) / 3.0f;
						break;
					case 0:
						isRunning2 = false;
						break;
					default:
						printf("�����ѡ�����\n");
						break;
				}

				if (i != 0)
				{
					printf("��ѡ������Ҫ�޸�����>");
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
		printf("δ�ҵ���ѧ�����޸�ʧ��\n");
	else
	{

		printf("			    ��ѧ���޸ĺ���Ϣ				\n");
		printf("*-----------------------------------------------------------------------*\n");
		printf("*	ѧ��	����	�༶		��ѧ	Ӣ��	�����	ƽ���ɼ�*\n");

		printf("* %llu\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.2lf*\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average);
	}

}

void removeStudent(List* list)	//�Ƴ�ǰ���ҵ�
{
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	char buffer[32];
	printf("������Ҫɾ����ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
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

	//�Ƿ��ҵ�
	if (curNode)
	{
		//Ҫɾ�����ǵ�һ���ڵ�
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
		printf("ɾ���ɹ�\n");
	}
	else
		printf("δ�ҵ���ѧ�����޸�ʧ��\n");
}

void rankStudent(List* list) {
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}  // �������Ϊ�ջ�ֻ��һ���ڵ㣬����Ҫ����

	Node* sorted = NULL;  // ����������
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
		printf("ϵͳ����ѧ����Ϣ��\n");
		return;
	}

	char className[Max_length] = "";
	printf("��������Ҫ�����İ༶����>");
	scanf("%s", className);

	// ��ʼ��ͳ�Ʊ���
	int acount = 0;
	float pass_math = 0, pass_english = 0, pass_computer = 0;
	float sum_math = 0, sum_english = 0, sum_computer = 0;
	float max_math = MIN, max_english = MIN, max_computer = MIN;
	float min_math = MAX, min_english = MAX, min_computer = MAX;

	Node* curNode = list->front;
	while (curNode != NULL) 
	{
		if (strcmp(curNode->stu.class, className) == 0)
		{// �ۼ��ܷ�
			sum_math += curNode->stu.math;
			sum_english += curNode->stu.english;
			sum_computer += curNode->stu.computer;

			// ������߷�
			if (curNode->stu.math > max_math)
				max_math = curNode->stu.math;
			if (curNode->stu.english > max_english)
				max_english = curNode->stu.english;
			if (curNode->stu.computer > max_computer)
				max_computer = curNode->stu.computer;

			// ������ͷ�
			if (curNode->stu.math < min_math)
				min_math = curNode->stu.math;
			if (curNode->stu.english < min_english)
				min_english = curNode->stu.english;
			if (curNode->stu.computer < min_computer)
				min_computer = curNode->stu.computer;

			// ͳ�Ƽ�������
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
		// ����ƽ����
		float ave_math = sum_math / acount;
		float ave_english = sum_english / acount;
		float ave_computer = sum_computer / acount;

		// ���㼰����
		float pass_rate_math = pass_math / acount * 100;
		float pass_rate_english = pass_english / acount * 100;
		float pass_rate_computer = pass_computer / acount * 100;

		// ������
		printf("*-----------------------------------------------------------------------*\n");
		printf("*			    %s�༶�ɼ�����				*\n",className);
		printf("*-----------------------------------------------------------------------*\n");
		printf("*ѧ��		ƽ����		��߷�		��ͷ�		������	*\n");
		printf("*-----------------------------------------------------------------------*\n");
		printf("*��ѧ		%.2f		%.2f		%.2f		%.2f%%	*\n", ave_math, max_math, min_math, pass_rate_math);
		printf("*Ӣ��		%.2f		%.2f		%.2f		%.2f%%	*\n", ave_english, max_english, min_english, pass_rate_english);
		printf("*�����		%.2f		%.2f		%.2f		%.2f%%	*\n", ave_computer, max_computer, min_computer, pass_rate_computer);
		printf("*-----------------------------------------------------------------------*\n");


	}
	else
		printf("ϵͳ���޸ð༶ѧ��\n");
}