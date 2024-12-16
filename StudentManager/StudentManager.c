#include "StudentManager.h"
#include<stdio.h>		//�˴�Ҫ�õ�printf��scanf����
#include<malloc.h>
#include<string.h>

static Node* CreateNode()	//Ϊ�����ڵ�дһ����������̬�ڲ��ģ���Ϊ�������Ḵ�ö�Σ�entryStudent��readStudent��,ʹ�������࣬������ͷ�ļ���������Ϊ�˼��ٲ���Ҫ��ȫ�ֱ�¶
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
	printf("*-------------------------------------------------------------------------------*\n");
	printf("*				ѧ���ɼ�����ϵͳ				*\n");
	printf("*-------------------------------------------------------------------------------*\n");
	printf("*				    ѡ����					*\n");
	printf("*-------------------------------------------------------------------------------*\n");
	printf("*			1.���ѧ����Ϣ		6.�༶�ɼ�����			*\n");
	printf("*			2.��ӡѧ����Ϣ		7.����ѧ����Ϣ			*\n");
	printf("*			3.ɾ��ѧ����Ϣ		8.ѧ����������			*\n");
	printf("*			4.�޸�ѧ����Ϣ		9.��ȡѧ����Ϣ			*\n");
	printf("*			5.����ѧ����Ϣ		0.�˳�ϵͳ			*\n");
	printf("*-------------------------------------------------------------------------------*\n");
	
	/*printf("select>");
	int select = -1;
	scanf("%d", &select);*/

	//��ֹ�û����������
	char buffer[Max_length];
	printf("select>");
	scanf("%s", buffer);
	int number = -1;
	sscanf(buffer, "%d", &number);
	return number;
	
	return;
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

	node->stu.sum = node->stu.math + node->stu.english + node->stu.computer;
	node->stu.average = node->stu.sum /3.0f;

	//���뵽������
	node->next = list->front;	//ͷ�壺�½ڵ����Ǳ����뵽�������ǰ�棬��Ϊ�µ�ͷ���ڵ㣬����ĵ�һ���ڵ�һֱ�ڸı䡣frontָ���½�㡣
	list->front = node;
	list->size++;

}

void printStudent(List* list)
{
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	int i = 0;
	char className[Max_length] = "";
	
	printf("\n��ʾ��ʽ:\n1.��ʾȫ��ѧ����Ϣ\n2.���༶��ʾѧ����Ϣ\n");
	printf("��ѡ����ʾ��ʽ>");
	scanf("%d", &i);
	switch (i)
	{
	case 1:	//ȫ��ѧ����ӡ
	{
		printf("*-------------------------------------------------------------------------------*\n");
		printf("*ѧ��		����	�༶		��ѧ	Ӣ��	�����	ƽ����	�ܳɼ�  *\n");
		printf("*-------------------------------------------------------------------------------*\n");

		//��������	
		Node* curNode = list->front;	//������ͷ����ʼ����

		if (curNode == NULL)
		{
			printf("ϵͳ����ѧ����Ϣ\n");
		}

		while (curNode != NULL)	//����ֱ�����һ���ڵ㣬���һ���ڵ�ָ��NULL
		{
			printf("*%llu\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t%.2lf  *\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average,curNode->stu.sum);
			curNode = curNode->next;	//�����굱ǰ�ڵ��ָ����һ���ڵ�
		}
		break;
	}
	case 2:	//���༶��ӡ
	{
		printf("������༶����>");
		scanf("%s", className);	
		printf("*-------------------------------------------------------------------------------*\n");
		printf("*ѧ��		����	�༶		��ѧ	Ӣ��	�����	ƽ����	�ܳɼ�  *\n");
		printf("*-------------------------------------------------------------------------------*\n");

		Node* curNode = list->front;

		if (curNode == NULL)
		{
			printf("ϵͳ����ѧ����Ϣ\n");
		}
		while (curNode != NULL)
		{
			if (strcmp(curNode->stu.class,className)==0)
			{
				printf("*%llu\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t%.2lf  *\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
					curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average, curNode->stu.sum);
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
		fprintf(fp,"%llu\t%s\t%s\t%.lf\t%.lf\t%.lf\t%.lf\t%.lf\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average,curNode->stu.sum);
		curNode = curNode->next;
	}

	//�ر��ļ�
	fclose(fp);
}

void readStudentHuman(List* list)	//���ļ��ж�ȡѧ����Ϣ��������뵽�����С�ͷ�巨��
{
	//���ļ�
	FILE* fp = fopen("test_students.txt", "r");	//r,���ķ�ʽ
	if (!fp)
	{
		perror("file open failed");
		return;
	}

		//��ȡѧ����Ϣ
	while (!feof(fp))	//feof������ļ�ָ���Ƿ��Ѿ������ļ�ĩβ�����ܻᵼ�����һ�ζ�ȡ������ִ��һ����Ч�Ķ�ȡ��
	{
		Node* node = CreateNode();
		if (!node)
			break;
		fscanf(fp,"%llu\t%s\t%s\t%f\t%f\t%f\t%f\t%f\n", &node->stu.number, node->stu.name, node->stu.class,
			&node->stu.math, &node->stu.english, &node->stu.computer, &node->stu.average,&node->stu.sum);	//���ڴ��ļ����ж�ȡ��ʽ�������롣

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

	char buffer[Max_length];
	printf("������ѧ����ѧ�Ż�����>");
	scanf("%s", buffer);

	//��bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);	//���Խ�buffer�е����ݽ���Ϊ�޷��ų��������֣���������洢�� number �����С������ܽ�����%llu����number��Ϊ-1

	Node* curNode = list->front;
	while (curNode != NULL)
	{
		//���buffer�����������Ǿͽ���ʧ�ܣ�number��Ϊ-1,ѧ�Ų����ܸ��������if�Ұ벿��һ������������벿�ֱȽ����ֲ��п��ܳ�����
		//���buffer����ѧ�ţ��Ǿͽ����ɹ���number��ѧ�ţ����������������֣������벿��һ�����������Ұ벿�ֱȽ�ѧ�Ų��п��ܳ�����
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)	//����������ѧ�Ų���
		{
			printf("*-------------------------------------------------------------------------------*\n");
			printf("*ѧ��		����	�༶		��ѧ	Ӣ��	�����	ƽ����	�ܳɼ�  *\n");
			printf("*-------------------------------------------------------------------------------*\n");
			printf("*%llu\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t%.2lf  *\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average, curNode->stu.sum);
			printf("*-------------------------------------------------------------------------------*\n");
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
			printf("*-------------------------------------------------------------------------------*\n");
			printf("*				    ѡ����					*\n");
			printf("*-------------------------------------------------------------------------------*\n");
			printf("*			1.�޸�ѧ��		5.�޸�Ӣ��ɼ�			*\n");
			printf("*			2.�޸�ѧ������		6.�޸ļ�����ɼ�		*\n");
			printf("*			3.�޸İ༶		0.ֹͣ�޸�			*\n");
			printf("*			4.�޸���ѧ�ɼ�						*\n");
			printf("*-------------------------------------------------------------------------------*\n");
			printf("\n");
			printf("			        ��ѧ���޸�ǰ��Ϣ					\n");
			printf("*-------------------------------------------------------------------------------*\n");
			printf("*ѧ��		����	�༶		��ѧ	Ӣ��	�����	ƽ����	�ܳɼ�  *\n");
			printf("*%llu\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t%.2lf  *\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
				curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average, curNode->stu.sum);
			printf("\n");
			
			printf("��ѡ��Ҫ�޸�����>");
			scanf("%d", &i);

			int isRunning2 = true;
			while (isRunning2)
			{
				//�˵�ѡ��Ҫ�޸ĵĲ���
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
						curNode->stu.sum = curNode->stu.math + curNode->stu.english + curNode->stu.computer;
						curNode->stu.average = curNode->stu.sum/ 3.0f;
						break;
					case 5:
						printf("��Ӣ��ĳɣ�");
						scanf("%f", &curNode->stu.english);
						curNode->stu.sum = curNode->stu.math + curNode->stu.english + curNode->stu.computer;
						curNode->stu.average = curNode->stu.sum / 3.0f;
						break;
					case 6:
						printf("�Ѽ�����ĳɣ�");
						scanf("%f", &curNode->stu.computer);
						curNode->stu.sum = curNode->stu.math + curNode->stu.english + curNode->stu.computer;
						curNode->stu.average = curNode->stu.sum / 3.0f;
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

		printf("			        ��ѧ���޸ĺ���Ϣ					\n");
		printf("*-------------------------------------------------------------------------------*\n");
		printf("*ѧ��		����	�༶		��ѧ	Ӣ��	�����	ƽ����	�ܳɼ�  *\n");

		printf("*%llu\t%s\t%s\t\t%.1lf\t%.1lf\t%.1lf\t%.2lf\t%.2lf  *\n", curNode->stu.number, curNode->stu.name, curNode->stu.class,
			curNode->stu.math, curNode->stu.english, curNode->stu.computer, curNode->stu.average, curNode->stu.sum);
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
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number)	//ѧ�Ż�����ƥ��
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
			//Ҫɾ������curNode,�����curNode����һ���ڵ㣨prevNode����nextָ��curNode����һ���ڵ㣨curNode->next��
			prevNode->next = curNode->next;	
		}
		free(curNode);
		list->size--;
		printf("ɾ���ɹ�\n");
	}
	else
		printf("δ�ҵ���ѧ����ɾ��ʧ��\n");
}

void rankStudent(List* list) {
	if (list->size == 0)
	{
		printf("ϵͳ����ѧ����Ϣ\n");
		return;
	}

	Node* sorted = NULL;  // ����������
	Node* curNode = list->front;	

	while (curNode != NULL) {
		Node* next = curNode->next;	//���浱ǰ�ڵ����һ���ڵ�ָ�룬�Ա����޸ĵ�ǰ�ڵ�����Ӻ����������
		if (sorted == NULL || (curNode->stu.math + curNode->stu.english + curNode->stu.computer) >= (sorted->stu.math + sorted->stu.english + sorted->stu.computer)) 
		{
			//ͷ��,�����ǰ�ڵ���󣬵�ǰ�ڵ�ָ��sortedͷ����Խ����ͷ����Խ��
			curNode->next = sorted;	
			sorted = curNode;	//����ͷ���ڵ�Ϊ�µ����Ľڵ�
		}
		else 
		{
			Node* temp = sorted;	//�ٴ�����tempʱ������Node* temp = sorted����Ϊָ��ͷ�������
			while (temp->next != NULL && (curNode->stu.math + curNode->stu.english + curNode->stu.computer) < (temp->next->stu.math + temp->next->stu.english + temp->next->stu.computer))	//temp->nextΪ�վ�˵��curNode����С�ģ�ֱ�Ӳ���������β��
			{
				temp = temp->next;	//һֱ����ֱ��curNode����
			}

			//�ҵ�curNode����λ�ú󣬽������sorted����λ�÷�ͷ����
			curNode->next = temp->next;
			temp->next = curNode;	//temp��ǰλ����curNodeҪ����ģ�curNode->nextͬ��ָ��temp->next,����temp->nextָ������curNode��
		}
		curNode = next;	//��ǰ�ڵ��Ѳ�����ϣ�ʹ��ָ����һ��������Ľڵ㣬��������ԭʼ����
	}

	list->front = sorted;	//����ԭʼ�����ͷָ�룬ʹ����ӳ�µ���������
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
		printf("*-------------------------------------------------------------------------------*\n");
		printf("*			        %s�༶�ɼ�����				*\n",className);
		printf("*-------------------------------------------------------------------------------*\n");
		printf("*ѧ��		ƽ����		��߷�		��ͷ�		������		*\n");
		printf("*-------------------------------------------------------------------------------*\n");
		printf("*��ѧ		%.2f		%.2f		%.2f		%.2f%%		*\n", ave_math, max_math, min_math, pass_rate_math);
		printf("*Ӣ��		%.2f		%.2f		%.2f		%.2f%%		*\n", ave_english, max_english, min_english, pass_rate_english);
		printf("*�����		%.2f		%.2f		%.2f		%.2f%%		*\n", ave_computer, max_computer, min_computer, pass_rate_computer);
		printf("*-------------------------------------------------------------------------------*\n");


	}
	else
		printf("ϵͳ���޸ð༶ѧ��\n");
}

int identify(void)
{

	printf("*-------------------------------------------------------------------------------*\n");
	printf("*			       ѧ���ɼ�����ϵͳ					*\n");
	printf("*-------------------------------------------------------------------------------*\n");
	printf("*				    ��¼����					*\n");
	printf("*-------------------------------------------------------------------------------*\n");
		char inputManager[Max_length];
		char inputPassword[Max_length];
		int chances = 3;

		while (chances > 0) 
		{
			printf("*�������û���:");
			scanf("%s", inputManager);
			printf("*����������: ");
			scanf("%s", inputPassword);

			if (strcmp(inputManager, Manager) == 0 && strcmp(inputPassword, Password) == 0) 
			{
				printf("�����֤�ɹ���ϵͳ��¼��...\n");
				system("pause");
				system("cls");
				return 1; // ��¼�ɹ�
			}
			else {
				chances--;
				if (chances > 0) 
				{
					printf("�û�����������������ԡ��㻹ʣ %d �γ��ԡ�\n", chances);
				}
				else {
					printf("���Ѿ����������еĳ��Դ�����ϵͳ���˳���\n");
					return 0; // ��¼ʧ��
				}
			}
		}

		return 0;
}
