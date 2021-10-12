typedef struct student//ѧ����Ϣ
{
	int sno;//ѧ��
	char name[30];//����
	char sex;//�Ա�
	int age;//����
}human, *people;
struct lesson
{
	int lnumber;//�γ̺� 
	char lname[30];//�γ��� 
	int lscore;//ѧ�� 
};
struct grade
{
	int gno;//ѧ�� 
	int gnum;//�γ̺� 
	int ggrade;//�ɼ� 
};


void menu(void);
void menu1(void);
void menu2(void);
void menu3(void);
void menu4(void);
people Input_s(people p);//
lesson* Input_l(lesson *q);
grade* Input_g(grade *w);
void Output_s(people p);// 
void Output_l(lesson *q);
void Output_g(grade *w);
void Sno_finds(people p);//ѧ�Ų���
void Sno_findg(grade *w);//ѧ�Ų�ɼ� 
void Snofind_detail(grade *w);//ѧ�Ų���Ϣ��ϸ 
void Lnumber_find(lesson *q);//�γ̺Ų�γ���Ϣ 
void Lname_find(lesson *q);//�γ�����γ���Ϣ 
void Lscore_find(lesson *q);//ѧ�ֲ�γ���Ϣ 
void Samename_find(people p);//����������ͬ���� 
void Statistic_man(people p);//ͳ��������Ϣ 
void Statistic_woman(people p);//ͳ��Ů����Ϣ
void Age_find(people p, int year1, int year2);//�������
void Snofind_list(grade *w);//ѧ�Ų����� 
void Average_list(grade *w, people p);//ѧ��ƽ�������� 
void Information_changes(people p);//ѧ���޸�ѧ����Ϣ 
void Information_changel(lesson *q);//�γ̺��޸Ŀγ���Ϣ 
void Information_changeg(grade *w);//ѧ�ſγ̺��޸ĳɼ� 
void Information_deletes(people p);//ѧ��ɾ��ѧ����Ϣ 
void Information_deletel(lesson *q);//�γ̺�ɾ���γ���Ϣ 
void Information_deleteg(grade *w);//ѧ�ſγ̺�ɾ���ɼ� 
void Information_alldelete(grade *w); //ѧ��ɾ��ѧ�����гɼ� 

void Sortl(lesson *q);//�γ����� 
void Sortg(grade *w);//�ɼ���ѧ������ 
void Sortg_g(grade *w);
int Average_score(grade *w, int a);//ƽ���� 

//void Enter(people p,lesson *q,grade *w);//������� 
void Find(people p, lesson *q, grade *w);//��ѯ���� 
void Change(people p, lesson *q, grade *w);//�޸ĳ��� 
void Delete(people p, lesson *q, grade *w);//ɾ������ 


int n, n1, n2;
int main()
{
	int x;
	int flag = 1;
	people p = (student*)malloc(sizeof(student));
	lesson *q = (lesson*)malloc(sizeof(lesson));
	grade *w = (grade*)malloc(sizeof(grade));
	FILE *streams;
	FILE *streaml;
	FILE *streamg;
	if ((streams = fopen("student.dat", "r")) != NULL)
	{
		fread(&n, sizeof(int), 1, streams);
		p = (student*)realloc(p, n * sizeof(student));
		fread(p, sizeof(student), n, streams);
	}
	if ((streaml = fopen("course.dat", "r")) != NULL)
	{
		fread(&n1, sizeof(int), 1, streaml);
		q = (lesson*)realloc(q, n1 * sizeof(lesson));
		fread(q, sizeof(lesson), n1, streaml);
	}
	if ((streamg = fopen("score.dat", "r")) != NULL)
	{
		fread(&n2, sizeof(int), 1, streamg);
		w = (grade*)realloc(w, n2 * sizeof(grade));
		fread(w, sizeof(grade), n2, streamg);
	}
	fclose(streams);
	fclose(streaml);
	fclose(streamg);
	FILE *fps = fopen("student.dat", "w");
	FILE *fpl = fopen("course.dat", "w");
	FILE *fpg = fopen("score.dat", "w");
	while (1)
	{
		menu();
		scanf("%d", &x);
		flag = 1;
		switch (x)
		{
		case 0:    //�˳�
			printf("д��浵�����Ժ�...\n");
			fwrite(&n, sizeof(int), 1, fps);
			fwrite(p, sizeof(student), n, fps);
			fwrite(&n1, sizeof(int), 1, fpl);
			fwrite(q, sizeof(lesson), n1, fpl);
			fwrite(&n2, sizeof(int), 1, fpg);
			fwrite(w, sizeof(grade), n2, fpg);
			return 0;
		case 1:// ������Ϣ 
			while (flag)
			{
				menu1();
				scanf("%d", &x);
				switch (x)
				{
				case 0:
					flag = 0;
					break;
				case 1:
					system("cls");
					p = Input_s(p);
					Output_s(p);
					system("pause");
					break;
				case 2:
					system("cls");
					q = Input_l(q);
					Output_l(q);
					system("pause");
					break;
				case 3:
					system("cls");
					w = Input_g(w);
					Output_g(w);
					system("pause");
					break;
				}
				fflush(stdin);
			}
			break;
		case 2: //��ѯ��Ϣ
			Find(p, q, w);
			break;
		case 3://�޸���Ϣ 
			Change(p, q, w);
			break;
		case 4://�޸�ѧ����Ϣ 
			Delete(p, q, w);
			break;
		default:
			printf("����ָ�\n");
			system("pause");
			break;
		}
		fflush(stdin);
	}
	fclose(fps);
	fclose(fpl);
	fclose(fpg);
	free(p);
	free(q);
	free(w);
	return 0;
}
//�Զ��庯��
void menu(void)
{
	system("cls");
	printf("==========================\n"
		"      ѧ������ϵͳ\n\n"
		"  Developer���ƿ�201���־\n"
		"==========================\n"
		"      1.����ѧ����Ϣ\n"
		"      2.��ѯѧ����Ϣ\n"
		"      3.�޸�ѧ����Ϣ\n"
		"      4.ɾ��ѧ����Ϣ\n"
		"      0.���沢�˳�\n"
		"==========================\n"
		"������(0-4)\n");
}
void menu1(void)
{
	system("cls");
	printf("=======================\n"
		"      ��������\n"
		"======================\n"
		"1.����ѧ����Ϣ\n"
		"2.����γ���Ϣ\n"
		"3.����ѧ��ѡ�γɼ���Ϣ\n"
		"0.�����ϲ�\n"
		"=======================\n"
		"������(0-3)");
}
void menu2(void)
{
	system("cls");
	printf("=============================\n"
		"         ��ѯϵͳ\n"
		"=============================\n"
		"1.ͳ��ѧ������\n"
		"2.ͳ�ƿγ���Ϣ\n"
		"3.ͳ�Ƴɼ���Ϣ\n"
		"4.��ѧ�Ų�ѯѧ����Ϣ\n"
		"5.��ѧ�źͿγ̺Ų�ѯ�ɼ�\n"
		"6.��ѧ�Ų�ѯ�ɼ�\n"
		"7.���γ̺Ų�ѯ�γ���Ϣ\n"
		"8.���γ�����ѯ�γ���Ϣ\n"
		"9.���γ�ѧ�ֲ�ѯ�γ���Ϣ\n"
		"10.��ѯ������ͬ����\n"
		"11.��ѯ��������\n"
		"12.��ѯ����Ů��\n"
		"13.��ѯĳ����ε�ѧ����Ϣ\n"
		"14.���γ̺Ų�ѯ�ÿγ�ѧ������\n"
		"0.�����ϲ�\n"
		"=============================\n"
		"������(0-5)\n");
}
void menu3(void)
{
	system("cls");
	printf("==========================\n"
		"\t�޸�ϵͳ\n"
		"==========================\n"
		"1.��ѧ���޸�ѧ����Ϣ\n"
		"2.���γ̺��޸Ŀγ���Ϣ\n"
		"3.��ѧ�źͿγ̺��޸ĳɼ�\n"
		"0.�����ϲ�\n"
		"������(0-3)\n"
		"==========================\n");
}
void menu4(void)
{
	system("cls");
	printf("========================================\n"
		"\t\tɾ��ϵͳ\n"
		"========================================\n"
		"1.��ѧ��ɾ��ѧ����Ϣ\n"
		"2.���γ̺�ɾ���γ���Ϣ\n"
		"3.��ѧ�źͿγ̺�ɾ��ѧ����Ӧ�ĳɼ���Ϣ\n"
		"0.�����ϲ�\n"
		"========================================\n");
}
people Input_s(people p)//ѧ����Ϣ
{
	int num;
	printf("�����������������");
	scanf("%d", &num);
	p = (student*)realloc(p, (n + num) * sizeof(student));
	for (int i = n; i < n + num; i++)
	{
		printf("ѧ�ţ�");
		scanf("%d", &p[i].sno);
		printf("������");
		scanf("%s", p[i].name);
		fflush(stdin);
		printf("�Ա�����'M'Ϊ�У�'F'ΪŮ����");
		scanf("%c", &p[i].sex);
		printf("���䣺");
		scanf("%d", &p[i].age);
		printf("\n");
	}
	n += num;
	system("cls");
	return p;
}
lesson* Input_l(lesson *q)//�γ���Ϣ 
{
	int num;
	printf("����������γ�����");
	scanf("%d", &num);
	q = (lesson*)realloc(q, (n1 + num) * sizeof(lesson));
	for (int i = n1; i < n1 + num; i++)
	{
		printf("�γ̺ţ�");
		scanf("%d", &q[i].lnumber);
		printf("�γ�����");
		scanf("%s", q[i].lname);
		fflush(stdin);
		printf("ѧ�֣�");
		scanf("%d", &q[i].lscore);
		printf("\n");
	}
	n1 += num;
	return q;
}
grade* Input_g(grade *w)//�ɼ���Ϣ 
{
	int num;
	printf("�������ѧ���ɼ�������");
	scanf("%d", &num);
	w = (grade*)realloc(w, (n2 + num) * sizeof(grade));
	for (int i = n2; i < n2 + num; i++)
	{
		printf("ѧ�ţ�");
		scanf("%d", &w[i].gno);
		printf("�γ̺ţ�");
		scanf("%d", &w[i].gnum);
		printf("�ɼ���");
		scanf("%d", &w[i].ggrade);
		printf("\n");
	}
	n2 += num;
	return w;
}
void Output_s(people p)//��� 
{
	system("cls");
	printf("=====================��ǰѧ��========================\n");
	printf("ѧ��\t\t����\t\t�Ա�\t\t����\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\t\t", p[i].sno);
		printf("%s\t\t", p[i].name);
		printf("%c\t\t", p[i].sex);
		printf("%d\n", p[i].age);
	}
	printf("=====================================================\n");
}
void Output_l(lesson *q)//�γ���Ϣ��� 
{
	system("cls");
	Sortl(q);
	printf("===============��ǰ�γ�=====================\n");
	printf("�γ̺�\t\t�γ���\t\tѧ��\n");
	for (int i = 0; i < n1; i++)
	{
		printf("%d\t\t", q[i].lnumber);
		printf("%s\t\t", q[i].lname);
		printf("%d\n", q[i].lscore);
	}
	printf("============================================\n");
}
void Output_g(grade *w)//�ɼ���� 
{
	system("cls");
	Sortg(w);
	printf("===============��ǰ�ɼ�===========\n");
	printf("ѧ��\t\t�γ̺�\t\t�ɼ�\n");
	for (int i = 0; i < n2; i++)
	{
		printf("%d\t\t", w[i].gno);
		printf("%d\t\t", w[i].gnum);
		printf("%d\n", w[i].ggrade);
	}
	printf("==================================\n");
}

void Sno_finds(people p)//ѧ�Ų�ѯѧ����Ϣ 
{
	system("cls");
	int a, flag = 0;
	human stu;
	printf("���ѯѧ����ѧ�ţ�");
	scanf("%d", &a);
	for (int i = 0; i < n; i++)
	{
		if (p[i].sno == a)
			flag = 1;
	}
	if (flag == 1)
	{
		for (int i = 0; i < n; i++)
		{
			if (p[i].sno == a)
			{
				stu = p[i];
				printf("ѧ�ţ�%d\n", stu.sno);
				printf("������%s\n", stu.name);
				printf("�Ա�%c\n", stu.sex);
				printf("���䣺%d\n", stu.age);
			}
		}
	}
	else
		printf("�޴�ѧ��\n");
}
void Sno_findg(grade *w)//ѧ�ſγ̺Ų�ѯ�ɼ� 
{
	system("cls");
	int a, b, flag = 0;
	printf("ѧ�ţ�");
	scanf("%d", &a);
	printf("�γ̺ţ�");
	scanf("%d", &b);
	for (int i = 0; i < n2; i++)
	{
		if (w[i].gno == a && w[i].gnum == b)
			flag = 1;
	}
	if (flag == 1)
	{

		printf("���ҳɹ�\n\n");
		for (int i = 0; i < n2; i++)
		{
			if (w[i].gno == a && w[i].gnum == b)
			{
				printf("�ɼ�:%d\n", w[i].ggrade);
			}
		}
	}
	else
		printf("�޴˳ɼ�\n");
}
void Snofind_detail(grade *w)//ѧ�Ų�ѯ���гɼ� 
{
	system("cls");
	int a, count = 0, flag = 0;
	grade stu[10];
	printf("ѧ�ţ�");
	scanf("%d", &a);

	for (int i = 0; i < n2; i++)
	{
		if (w[i].gno == a)
			flag = 1;
	}
	if (flag == 1)
	{
		for (int i = 0; i < n2; i++)
		{
			if (w[i].gno == a)
			{
				stu[count] = w[i];
				count++;
			}
		}
		printf("���ҳɹ�\n\n\n");
		for (int i = 0; i < count; i++)
		{
			printf("ѧ�ţ�%d\t\t", stu[i].gno);
			printf("�γ̺ţ�%d\t\t", stu[i].gnum);
			printf("�ɼ���%d\t\t\n", stu[i].ggrade);
		}
	}
	else
		printf("�޴˼�¼\n");
}
void Lnumber_find(lesson *q)//�γ̺Ų�γ���Ϣ 
{
	system("cls");
	int a, flag = 0;
	lesson stu;
	printf("����γ̺ţ�");
	scanf("%d", &a);
	for (int i = 0; i < n1; i++)
	{
		if (q[i].lnumber == a)
		{
			stu = q[i];
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		printf("���ҳɹ�\n");
		printf("=======================\n");
		printf("�γ̺�\t�γ���\tѧ��\n");
		printf("-----------------------\n");
		printf("%d\t%s\t%d\n", stu.lnumber, stu.lname, stu.lscore);
		printf("=======================\n");
	}
	else
		printf("�޴�����¼\n");
}
void Lname_find(lesson *q)//�γ�����γ���Ϣ 
{
	system("cls");
	int count = 0;
	lesson stu[10];
	char a[30];
	printf("����γ�����");
	scanf("%s", a);
	printf("\n");
	//���ü�fflush 
	for (int i = 0; i < n1; i++)
	{
		if (strcmp(q[i].lname, a) == 0)
		{
			stu[count] = q[i];
			count++;
		}
	}
	printf("============��ѯ���===========\n");
	printf("�γ̺�\t�γ���\tѧ��\n");
	if (count == 0)
	{
		printf("============��0��==========\n");
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			printf("%d\t%s\t%d\n", stu[i].lnumber, stu[i].lname, stu[i].lscore);
		}
		printf("============��%d��==========\n", count);
	}
}
void Lscore_find(lesson *q)//ѧ�ֲ�γ���Ϣ 
{
	system("cls");
	int a, count = 0;
	lesson stu[10];
	printf("����ѧ�֣�");
	scanf("%d", &a);
	printf("\n");
	for (int i = 0; i < n1; i++)
	{
		if (q[i].lscore == a)
		{
			stu[count] = q[i];
			count++;
		}
	}

	if (count != 0)
	{
		printf("ѧ����ͬ�Ŀγ�����\n");
		printf("=========================================================\n");
		for (int i = 0; i < count; i++)
		{
			printf("�γ̺ţ�%d\t    ", stu[i].lnumber, stu[i].lname, stu[i].lscore);
			printf("�γ�����%s\t\tѧ�֣�%d\n", stu[i].lname, stu[i].lscore);
			printf("=========================================================\n");
		}
	}
	else
		printf("�޴�����¼\n");
}
void Samename_find(people p)//����������ͬ���� 
{
	system("cls");
	int count = 0;
	char name[30];
	human stu[10];
	printf("������ѯ��ѧ��������");
	scanf("%s", name);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(p[i].name, name) == 0)
		{
			stu[count] = p[i];
			count++;
		}
	}
	printf("=================��ѯ���====================\n");
	printf("ѧ��\t\t����\t\t�Ա�\t\t����\n");
	if (count == 0)
	{
		printf("==================��0��================\n");
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			printf("%d\t\t%s\t\t", stu[i].sno, stu[i].name);
			printf("%c\t\t%d\n", stu[i].sex, stu[i].age);
		}
		printf("============��%d��==========\n", count);
	}
}
void Statistic_man(people p)//ͳ��������Ϣ 
{
	system("cls");
	printf("\n");
	int count = 0;
	printf("====================================================\n");
	printf("ѧ��\t\t����\t\t�Ա�\t\t����\n");
	printf("====================================================\n");
	for (int i = 0; i < n; i++)
	{
		if (p[i].sex == 'M')
		{
			printf("%d\t\t%s\t\t", p[i].sno, p[i].name);
			printf("%c\t\t%d\n", p[i].sex, p[i].age);
			count++;
		}
	}
	printf("======================��%d��=========================\n", count);
}
void Statistic_woman(people p)//ͳ��Ů����Ϣ 
{
	system("cls");
	printf("\n");
	int count = 0;
	printf("====================================================\n");
	printf("ѧ��\t\t����\t\t�Ա�\t\t����\n");
	printf("====================================================\n");
	for (int i = 0; i < n; i++)
	{
		if (p[i].sex == 'F')
		{
			printf("%d\t\t%s\t\t", p[i].sno, p[i].name);
			printf("%c\t\t%d\n", p[i].sex, p[i].age);
			count++;
		}
	}
	printf("======================��%d��=========================\n", count);
}
void Age_find(people p, int year1, int year2)//����β���Ϣ
{

	int flag = 1, count = 0;
	for (int i = 0; i < n; i++)
	{
		if (p[i].age<year1 && p[i].age>year2)
		{
			flag = 0;
		}
	}
	if (flag == 1)
	{
		printf("====================================================\n");
		printf("ѧ��\t\t����\t\t�Ա�\t\t����\n");
		printf("====================================================\n");
		for (int j = 0; j < n; j++)
		{
			if (p[j].age >= year1 && p[j].age <= year2)
			{
				printf("%d\t\t%s\t\t", p[j].sno, p[j].name);
				printf("%c\t\t%d\n", p[j].sex, p[j].age);
				count++;
			}
		}
		printf("======================��%d��=========================\n", count);
	}
	else
		printf("�޸������ѧ��\n");
}
void Snofind_list(grade *w)//�γ̺Ų����� 
{
	system("cls");
	printf("\n");
	grade stu[10], t;
	int a, list = 1, flag = 0, count = 0;
	printf("����γ̺ţ�");
	scanf("%d", &a);
	for (int i = 0; i < n2; i++)
	{
		if (w[i].gnum == a)
		{
			flag = 1;
			stu[count] = w[i];
			count++;
		}
	}
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (stu[j].ggrade < stu[j + 1].ggrade)
			{
				t = stu[j];
				stu[j] = stu[j + 1];
				stu[j + 1] = t;
			}
		}
	}
	if (flag != 0)
	{
		Sortg_g(w);
		printf("\n����Ŀƽ���֣�%d\n", Average_score(w, a));
		printf("===================��ǰ�ɼ�=====================\n");
		for (int i = 0; i < count; i++)
		{
			printf("ѧ�ţ�%d\t\t   ", stu[i].gno);
			printf("�ɼ���%d\t     ", stu[i].ggrade);
			printf("������%d\n", list);
			list++;
		}
		printf("================================================\n");
	}
	else
		printf("�޴˿γ�\n");
}						///////////////////////////////////////////////////////////////////
void Average_list(grade *w, people p)//ѧ��ƽ�������� 
{
	int t, temp, f = 0;
	int count = 0;
	int ave[n] = { 0 };
	int sno[n];
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; i < n2; j++)
		{
			if (p[i].sno == w[i].gno)
			{
				ave[i] += w[j].ggrade;
				sno[i] = p[i].sno;
				f++;
			}
		}
		for (int k = 0; k < n; k++)
		{
			if (f != 0)
			{
				ave[k] /= f;
			}
		}
		f = 0;
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (ave[j] < ave[j + 1])
			{
				t = ave[j];
				ave[j] = ave[j + 1];
				ave[j + 1] = t;
				temp = sno[j];
				sno[j] = sno[j + 1];
				sno[j + 1] = temp;
			}
		}
	}			///////////////////////////////////////////////////////////////////////////////
	printf("===================��ǰ�ɼ�=====================\n");
	for (int i = 0; i < n; i++)
	{
		printf("ѧ�ţ�%d\t\t   ", sno[i]);
		printf("�ɼ���%d\t     ", ave[i]);
		printf("������%d\n", count);
	}
	printf("================================================\n");
}
void Information_changes(people p)//ѧ���޸�ѧ����Ϣ 
{
	Output_s(p);
	int sno, flag = 0;
	printf("�������ѧ��ѧ�ţ�");
	scanf("%d", &sno);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (p[i].sno == sno)
		{
			printf("�����޸�\n");
			printf("������");
			scanf("%s", p[i].name);
			fflush(stdin);
			printf("�Ա�");
			scanf("%c", &p[i].sex);
			printf("���䣺");
			scanf("%d", &p[i].age);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("�޸�ѧ��\n");
	}
	else
	{
		system("pause");
		Output_s(p);
	}
}
void Information_changel(lesson *q)//�γ̺��޸Ŀγ� 
{
	Output_l(q);
	int sno, flag = 0;
	printf("������γ̺ţ�");
	scanf("%d", &sno);
	for (int i = 0; i < n1; i++)
	{
		if (q[i].lnumber == sno)
		{
			printf("�����޸�\n");
			printf("�γ̺ţ�");
			scanf("%d", &q[i].lnumber);
			printf("�γ�����");
			scanf("%s", q[i].lname);
			fflush(stdin);
			printf("ѧ�֣�");
			scanf("%d", &q[i].lscore);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("�޸ÿγ�\n");
	}
	else
	{
		system("pause");
		Output_l(q);
	}
}
void Information_changeg(grade *w)//��ѧ�ſγ̺��޸ĳɼ� 
{
	Output_g(w);
	int sno, number, flag = 0;
	printf("������ѧ�ţ�");
	scanf("%d", &sno);
	printf("������γ̺ţ�");
	scanf("%d", &number);
	for (int i = 0; i < n2; i++)
	{
		if (w[i].gno == sno && w[i].gnum == number)
		{
			printf("�����޸�\n");
			printf("�ɼ���");
			scanf("%d", &w[i].ggrade);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("�޸óɼ�\n");
	}
	else
	{
		system("pause");
		Output_g(w);
	}
}

void Information_deletes(people p)//��ѧ��ɾѧ����Ϣ 
{
	Output_s(p);
	int a, f, flag = 0;
	printf("������ɾ��ѧ����ѧ���ţ�");
	scanf("%d", &a);
	for (int i = 0; i < n; i++)
	{
		if (p[i].sno == a)
		{
			f = i;
			flag = 1;
		}
	}
	if (flag != 0)
	{
		for (int i = f; i < n - 1; i++)
		{
			p[i] = p[i + 1];
		}
		p = (student*)realloc(p, (n - 1) * sizeof(student));
		n--;
		system("pause");
		Output_s(p);
	}
	else
	{
		printf("�޸�ѧ��\n");
	}
}
void Information_deletel(lesson *q)//���γ̺�ɾ�γ���Ϣ 
{
	Output_l(q);
	int a, f, flag = 0;
	printf("������γ̺ţ�");
	scanf("%d", &a);
	for (int i = 0; i < n1; i++)
	{
		if (q[i].lnumber == a)
		{
			f = i;
			flag = 1;
		}
	}
	if (flag != 0)
	{
		for (int i = f; i < n1 - 1; i++)
		{
			q[i] = q[i + 1];
		}
		q = (lesson*)realloc(q, (n1 - 1) * sizeof(lesson));
		n1--;
		system("pause");
		Output_l(q);
	}
	else
	{
		printf("�޸ÿγ�\n");
	}
}
void Information_deleteg(grade *w)//��ѧ�źͿγ̺�ɾ�ɼ� 
{
	Output_g(w);
	int a, b, f, flag = 0;
	printf("����ѧ�ţ�");
	scanf("%d", &a);
	printf("����γ̺ţ�");
	scanf("%d", &b);
	for (int i = 0; i < n2; i++)
	{
		if (w[i].gno == a && w[i].gnum == b)
		{
			f = i;
			flag = 1;
		}
	}
	if (flag != 0)
	{
		for (int i = f; i < n2 - 1; i++)
		{
			w[i] = w[i + 1];
		}
		w = (grade*)realloc(w, (n2 - 1) * sizeof(grade));
		n2--;
		system("pause");
		Output_g(w);
	}
	else
	{
		printf("�޸óɼ�\n");
	}
}
void Information_alldelete(grade *w)//��ѧ��ɾ�����гɼ� 
{
	char ch = '0';
	Output_g(w);
	int a, flag;
	printf("����ѧ��ѧ�ţ�");
	scanf("%d", &a);
	for (int i = 0; i < n2; i++)
	{
		if (w[i].gno == a)
		{
			flag = i;
			ch = '1';
			for (int j = flag; j < n2 - 1; j++)
			{
				w[j] = w[j + 1];
			}
			w = (grade*)realloc(w, (n2 - 1) * sizeof(grade));
			n2--;
		}
	}
	if (ch != '0')
	{
		system("pause");
		Output_g(w);
	}
	else
	{
		printf("�޸óɼ�\n");
	}
}

void Sortl(lesson *q)//�γ̺�����
{
	lesson t;
	for (int i = 0; i < n1 - 1; i++)
	{
		for (int j = 0; j < n1 - i - 1; j++)
		{
			if (q[j].lnumber > q[j + 1].lnumber)
			{
				t = q[j];
				q[j] = q[j + 1];
				q[j + 1] = t;
			}
		}
	}
}
void Sortg(grade *w)//�ɼ����� 
{
	grade t;
	for (int i = 0; i < n2 - 1; i++)
	{
		for (int j = 0; j < n2 - i - 1; j++)
		{
			if (w[j].gno > w[j + 1].gno)
			{
				t = w[j];
				w[j] = w[j + 1];
				w[j + 1] = t;
			}
		}
	}
}
void Sortg_g(grade *w)
{
	grade t;
	for (int i = 0; i < n2 - 1; i++)
	{
		for (int j = 0; j < n2 - i - 1; j++)
		{
			if (w[j].ggrade > w[j + 1].ggrade)
			{
				t = w[j];
				w[j] = w[j + 1];
				w[j + 1] = t;
			}
		}
	}
}
int Average_score(grade *w, int a)//��ƽ���� 
{
	int sum = 0, count = 0;
	for (int i = 0; i < n2; i++)
	{
		if (w[i].gnum == a)
		{
			sum += w[i].ggrade;
			count++;
		}
	}
	return sum / count;
}


/*void Enter(people p,lesson *q,grade *w)
{
	int x;
	int flag=1;
	while(flag)
	{
		menu1();
		scanf("%d",&x);
		switch(x)
		{
			case 0:
				flag=0;
				break;
			case 1:
				system("cls");
				p=Input_s(p);
				Output_s(p);
				system("pause");
				break;
			case 2:
				system("cls");
				q=Input_l(q);
				Output_l(q);
				system("pause");
				break;
			case 3:
				system("cls");
				w=Input_g(w);
				Output_g(w);
				system("pause");
				break;
		}
		fflush(stdin);
	}
}*/
void Find(people p, lesson *q, grade *w)
{
	int x;
	int flag = 1;
	while (flag)
	{
		menu2();
		scanf("%d", &x);
		switch (x)
		{
		case 0://�����ϲ�
			flag = 0;
			break;
		case 1://ͳ��ѧ����Ϣ 
			if (p == NULL)
				printf("��ǰѧ����ϢΪ�գ�");
			Output_s(p);
			system("pause");
			break;
		case 2://�γ���Ϣ 
			if (q == NULL)
				printf("��ǰ�γ���ϢΪ�գ�");
			Output_l(q);
			system("pause");
			break;
		case 3://�ɼ���Ϣ 
			if (w == NULL)
				printf("��ǰ�ɼ���ϢΪ�գ�");
			Output_g(w);
			system("pause");
			break;
		case 4://��ѧ�Ų�ѯѧ����ȫ����Ϣ
			Sno_finds(p);
			system("pause");
			break;
		case 5:
			Sno_findg(w);//ѧ�Ų�ɼ� 
			system("pause");
			break;
		case 6:
			Snofind_detail(w);//ѧ�Ų�ɼ���ϸ 
			system("pause");
			break;
		case 7://ѧ�Ų�γ���Ϣ 
			Lnumber_find(q);
			system("pause");
			break;
		case 8://�γ�����γ���Ϣ 
			Lname_find(q);
			system("pause");
			break;
		case 9://ѧ�ֲ�γ���Ϣ 
			Lscore_find(q);
			system("pause");
			break;
		case 10://����ͬ���ֵ��� 
			Samename_find(p);
			system("pause");
			break;
		case 11://ͳ������ 
			Statistic_man(p);
			system("pause");
			break;
		case 12://ͳ��Ů�� 
			Statistic_woman(p);
			system("pause");
			break;
		case 13://��ѯĳ����ε�ѧ����Ϣ
			int year1, year2;
			system("cls");
			printf("���ѯѧ������������ޣ�");
			scanf("%d", &year1);
			printf("���ѯѧ������������ޣ�");
			scanf("%d", &year2);
			Age_find(p, year1, year2);
			system("pause");
			break;
		case 14://�γ̺Ų�ɼ����� 
			Snofind_list(w);
			system("pause");
			break;
		default:
			printf("����ָ�\n");
			system("pause");
			break;
		}
		fflush(stdin);
	}
}
void Change(people p, lesson *q, grade *w)//�޸ĳ��� 
{
	int x;
	int flag = 1;
	while (flag)
	{
		menu3();
		scanf("%d", &x);
		switch (x)
		{
		case 0:
			flag = 0;
			break;
		case 1:
			Information_changes(p);
			system("pause");
			break;
		case 2:
			Information_changel(q);
			system("pause");
			break;
		case 3:
			Information_changeg(w);
			system("pause");
			break;
		default:
			printf("����ָ�\n");
			system("pause");
			break;
		}
		fflush(stdin);
	}
}
void Delete(people p, lesson *q, grade *w)
	int x;
	int flag = 1;
	while (flag)
		menu4();
		scanf("%d", &x);
		switch (x)
		{
		case 0:
			flag = 0;
			break;
		case 1:
			Information_deletes(p);
			system("pause");
			break;
		case 2:
			Information_deletel(q);
			system("pause");
			break;
		case 3:
			Information_deleteg(w);
			system("pause");
			break;
		case 4:
			Information_alldelete(w);
			system("pause");
			break;
		default:
			printf("����ָ�\n");
			system("pause");
			break;
		}
		fflush(stdin);
	}
}
