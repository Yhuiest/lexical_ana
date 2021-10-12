#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student//学生信息
{
    int sno;//学号
    char name[30];//姓名
    char sex;//性别
    int age;//年龄
}human,*people;
struct lesson
{
	int lnumber;//课程号 
	char lname[30];//课程名 
	int lscore;//学分 
};
struct grade
{
	int gno;//学号 
	int gnum;//课程号 
	int ggrade;//成绩 
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
void Sno_finds(people p);//学号查找
void Sno_findg(grade *w);//学号查成绩 
void Snofind_detail(grade *w);//学号查信息明细 
void Lnumber_find(lesson *q);//课程号查课程信息 
void Lname_find(lesson *q);//课程名查课程信息 
void Lscore_find(lesson *q);//学分查课程信息 
void Samename_find(people p);//查找姓名相同的人 
void Statistic_man(people p);//统计男生信息 
void Statistic_woman(people p);//统计女生信息
void Age_find(people p,int year1,int year2);//年龄查找
void Snofind_list(grade *w);//学号查排名 
void Average_list(grade *w,people p);//学生平均分排名 
void Information_changes(people p);//学号修改学生信息 
void Information_changel(lesson *q);//课程号修改课程信息 
void Information_changeg(grade *w);//学号课程号修改成绩 
void Information_deletes(people p);//学号删除学生信息 
void Information_deletel(lesson *q);//课程号删除课程信息 
void Information_deleteg(grade *w);//学号课程号删除成绩 
void Information_alldelete(grade *w); //学号删除学生所有成绩 

void Sortl(lesson *q);//课程排序 
void Sortg(grade *w);//成绩按学号排序 
void Sortg_g(grade *w);
int Average_score(grade *w,int a);//平均分 

//void Enter(people p,lesson *q,grade *w);//输入程序 
void Find(people p,lesson *q,grade *w);//查询程序 
void Change(people p,lesson *q,grade *w);//修改程序 
void Delete(people p,lesson *q,grade *w);//删除程序 


int n,n1,n2;
int main()
{
	int x;
	int flag=1;
    people p=(student*)malloc(sizeof(student));
   	lesson *q=(lesson*)malloc(sizeof(lesson));
   	grade *w=(grade*)malloc(sizeof(grade));	
    FILE *streams;
    FILE *streaml;
    FILE *streamg;
    if((streams=fopen("student.dat","r"))!=NULL)
    {
        fread(&n,sizeof(int),1,streams);
        p=(student*)realloc(p, n*sizeof(student));
        fread(p,sizeof(student),n,streams);  
    }	
    if((streaml=fopen("course.dat","r"))!=NULL)
    {
    	fread(&n1,sizeof(int),1,streaml);
    	q=(lesson*)realloc(q,n1*sizeof(lesson));
    	fread(q,sizeof(lesson),n1,streaml);
	}
	if((streamg=fopen("score.dat","r"))!=NULL)
	{
		fread(&n2,sizeof(int),1,streamg);
		w=(grade*)realloc(w,n2*sizeof(grade));
		fread(w,sizeof(grade),n2,streamg);
	}
	fclose(streams);
    fclose(streaml);
    fclose(streamg);
    FILE *fps=fopen("student.dat","w");
    FILE *fpl=fopen("course.dat","w");
    FILE *fpg=fopen("score.dat","w");
    while(1)
    {
        menu();
        scanf("%d",&x);
        flag=1;
        switch(x)
        {
            case 0:    //退出
                printf("写入存档中请稍后...\n");
    			fwrite(&n, sizeof(int), 1, fps);
    			fwrite(p,sizeof(student),n,fps);
    			fwrite(&n1,sizeof(int),1,fpl);
    			fwrite(q,sizeof(lesson),n1,fpl);
    			fwrite(&n2,sizeof(int),1,fpg);
    			fwrite(w,sizeof(grade),n2,fpg);
                return 0;
            case 1:// 输入信息 
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
                break;
            case 2: //查询信息
                Find(p,q,w);
                break;
            case 3://修改信息 
                Change(p,q,w);
                break;
            case 4://修改学生信息 
                Delete(p,q,w);
                break;
            default:
            	printf("错误指令！\n");
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
//自定义函数
void menu(void)
{
    system("cls");
    printf("==========================\n"
		   "      学生管理系统\n\n"
		   "  Developer：计科201侯佳志\n"
		   "==========================\n"
		   "      1.输入学生信息\n"
    	   "      2.查询学生信息\n"
     	   "      3.修改学生信息\n"
           "      4.删除学生信息\n"
   	 	   "      0.保存并退出\n"
    	   "==========================\n"
    	   "请输入(0-4)\n");
}
void menu1(void)
{
	system("cls");
	printf("=======================\n"
		   "      数据输入\n"
		   "======================\n"
		   "1.输入学生信息\n"
		   "2.输入课程信息\n"
		   "3.输入学生选课成绩信息\n"
		   "0.返回上层\n"
		   "=======================\n"
		   "请输入(0-3)");
}
void menu2(void)
{
    system("cls");
    printf("=============================\n"
		   "         查询系统\n"
		   "=============================\n"
	       "1.统计学生人数\n"
	       "2.统计课程信息\n"
		   "3.统计成绩信息\n"
		   "4.按学号查询学生信息\n"
		   "5.按学号和课程号查询成绩\n"
		   "6.按学号查询成绩\n"
		   "7.按课程号查询课程信息\n" 
	       "8.按课程名查询课程信息\n"
	       "9.按课程学分查询课程信息\n"
	       "10.查询姓名相同的人\n"
	       "11.查询所有男生\n"
		   "12.查询所有女生\n"
	       "13.查询某年龄段的学生信息\n"
	       "14.按课程号查询该课程学生排名\n"
	       "0.返回上层\n"
	       "=============================\n"
	       "请输入(0-5)\n");
}
void menu3(void)
{
    system("cls");
    printf("==========================\n"
	  	   "\t修改系统\n"
		   "==========================\n"
		   "1.按学号修改学生信息\n"
  		   "2.按课程号修改课程信息\n"
    	   "3.按学号和课程号修改成绩\n"
   		   "0.返回上层\n"
   		   "请输入(0-3)\n"
   		   "==========================\n");
}
void menu4(void)
{
	system("cls");
	printf("========================================\n"
		   "\t\t删除系统\n"
		   "========================================\n"
		   "1.按学号删除学生信息\n"
		   "2.按课程号删除课程信息\n"
		   "3.按学号和课程号删除学生对应的成绩信息\n"
		   "0.返回上层\n"
		   "========================================\n");
}
people Input_s(people p)//学生信息
{
    int num;
    printf("输入想输入的人数：");
    scanf("%d",&num);
    p=(student*)realloc(p,(n+num)*sizeof(student));
    for(int i=n;i<n+num;i++)
    {
        printf("学号：");
        scanf("%d",&p[i].sno);
        printf("姓名：");
        scanf("%s",p[i].name);
        fflush(stdin);
        printf("性别（输入'M'为男，'F'为女）：");
        scanf("%c",&p[i].sex);
        printf("年龄：");
        scanf("%d",&p[i].age);
        printf("\n");
    }
    n+=num;
    system("cls");
    return p;
}
lesson* Input_l(lesson *q)//课程信息 
{
	int num;
    printf("输入想输入课程数：");
    scanf("%d",&num);
    q=(lesson*)realloc(q,(n1+num)*sizeof(lesson));
    for(int i=n1;i<n1+num;i++)
    {
    	printf("课程号：");
    	scanf("%d",&q[i].lnumber);
    	printf("课程名：");
    	scanf("%s",q[i].lname);
		fflush(stdin); 
    	printf("学分：");
    	scanf("%d",&q[i].lscore);
    	printf("\n");
	}
    n1+=num;
    return q;
}
grade* Input_g(grade *w)//成绩信息 
{
	int num;
	printf("想输入的学生成绩个数：");
	scanf("%d",&num);
	w=(grade*)realloc(w,(n2+num)*sizeof(grade));
	for(int i=n2;i<n2+num;i++)
	{
		printf("学号：");
		scanf("%d",&w[i].gno);
		printf("课程号：");
		scanf("%d",&w[i].gnum);
		printf("成绩：");
		scanf("%d",&w[i].ggrade);
		printf("\n");
	}
	n2+=num;
	return w;
} 
void Output_s(people p)//输出 
{
	system("cls");
	printf("=====================当前学生========================\n");
	printf("学号\t\t姓名\t\t性别\t\t年龄\n"); 
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t",p[i].sno);
        printf("%s\t\t",p[i].name);
        printf("%c\t\t",p[i].sex);
        printf("%d\n",p[i].age);
    }
    printf("=====================================================\n");
}
void Output_l(lesson *q)//课程信息输出 
{
	system("cls");
	Sortl(q);
	printf("===============当前课程=====================\n");
	printf("课程号\t\t课程名\t\t学分\n");
	for(int i=0;i<n1;i++)
	{
		printf("%d\t\t",q[i].lnumber);
		printf("%s\t\t",q[i].lname);
		printf("%d\n",q[i].lscore);
	}
	printf("============================================\n");
}
void Output_g(grade *w)//成绩输出 
{
	system("cls");
	Sortg(w);
	printf("===============当前成绩===========\n");
	printf("学号\t\t课程号\t\t成绩\n");
	for(int i=0;i<n2;i++)
	{
		printf("%d\t\t",w[i].gno);
		printf("%d\t\t",w[i].gnum);
		printf("%d\n",w[i].ggrade);
	}
	printf("==================================\n");
}

void Sno_finds(people p)//学号查询学生信息 
{
	system("cls");
    int a,flag=0; 
    human stu;
    printf("想查询学生的学号：");
    scanf("%d",&a);
    for(int i=0;i<n;i++)
    {
    	if(p[i].sno==a)
    		flag=1;
	}
	if(flag==1)
	{
	    for(int i=0;i<n;i++)
	    {
	        if(p[i].sno==a)
	        {
	        	stu=p[i];
	        	printf("学号：%d\n",stu.sno);
	   			printf("姓名：%s\n",stu.name);
	   			printf("性别：%c\n",stu.sex);
	   			printf("年龄：%d\n",stu.age);
			}
	    }
	}
	else
		printf("无此学生\n"); 
}
void Sno_findg(grade *w)//学号课程号查询成绩 
{
	system("cls");
	int a,b,flag=0;
	printf("学号：");
	scanf("%d",&a);
	printf("课程号：");
	scanf("%d",&b);
	for(int i=0;i<n2;i++)
	{
		if(w[i].gno==a && w[i].gnum==b)
			flag=1;
	}
	if(flag==1)
	{
		
		printf("查找成功\n\n");
		for(int i=0;i<n2;i++)
		{
			if(w[i].gno==a && w[i].gnum==b)
			{
				printf("成绩:%d\n",w[i].ggrade);
			}
		}
	}
	else
		printf("无此成绩\n");
}
void Snofind_detail(grade *w)//学号查询所有成绩 
{
	system("cls");
	int a,count=0,flag=0;
	grade stu[10];
	printf("学号：");
	scanf("%d",&a);

	for(int i=0;i<n2;i++)
	{
		if(w[i].gno==a)
			flag=1;
	}
	if(flag==1)
	{
		for(int i=0;i<n2;i++)
		{
			if(w[i].gno==a)
			{
				stu[count]=w[i];
				count++;
			}	
		}
		printf("查找成功\n\n\n");
		for(int i=0;i<count;i++)
		{
			printf("学号：%d\t\t",stu[i].gno);
			printf("课程号：%d\t\t",stu[i].gnum);
			printf("成绩：%d\t\t\n",stu[i].ggrade);
		}
	}
	else
		printf("无此记录\n"); 
}
void Lnumber_find(lesson *q)//课程号查课程信息 
{
	system("cls");
	int a,flag=0;
	lesson stu;
	printf("输入课程号：");
	scanf("%d",&a);
	for(int i=0;i<n1;i++)
	{
		if(q[i].lnumber==a)
		{
			stu=q[i];
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("查找成功\n"); 
		printf("=======================\n");
		printf("课程号\t课程名\t学分\n");
		printf("-----------------------\n");
		printf("%d\t%s\t%d\n",stu.lnumber,stu.lname,stu.lscore);
		printf("=======================\n");
	}
	else
		printf("无此条记录\n"); 
}
void Lname_find(lesson *q)//课程名查课程信息 
{
	system("cls");
	int count=0;
	lesson stu[10];
	char a[30];
	printf("输入课程名：");
	scanf("%s",a);
	printf("\n");
	//不用加fflush 
	for(int i=0;i<n1;i++)
	{
		if(strcmp(q[i].lname,a)==0)
		{
			stu[count]=q[i];
			count++;
		}
	}
	printf("============查询结果===========\n");
	printf("课程号\t课程名\t学分\n"); 
	if(count==0)
	{
		printf("============共0个==========\n");
	}
	else
	{
		for(int i=0;i<count;i++)
		{
			printf("%d\t%s\t%d\n",stu[i].lnumber,stu[i].lname,stu[i].lscore);
		}
		printf("============共%d个==========\n",count);
	}
}
void Lscore_find(lesson *q)//学分查课程信息 
{
	system("cls");
	int a,count=0;
	lesson stu[10];
	printf("输入学分：");
	scanf("%d",&a);
	printf("\n");
	for(int i=0;i<n1;i++)
	{
		if(q[i].lscore==a)
		{
			stu[count]=q[i];
			count++;
		}
	}
	
	if(count!=0)
	{
		printf("学分相同的课程如下\n");
		printf("=========================================================\n");
		for(int i=0;i<count;i++)
		{
			printf("课程号：%d\t    ",stu[i].lnumber,stu[i].lname,stu[i].lscore);
			printf("课程名：%s\t\t学分：%d\n",stu[i].lname,stu[i].lscore);
			printf("=========================================================\n");
		}
	}
	else
		printf("无此条记录\n");
}
void Samename_find(people p)//查找姓名相同的人 
{
	system("cls");
	int count=0;
	char name[30];
	human stu[10];
	printf("输出想查询的学生姓名：");
	scanf("%s",name);
	for(int i=0;i<n;i++)
	{
		if(strcmp(p[i].name,name)==0)
		{
			stu[count]=p[i];
			count++;
		}
	}
	printf("=================查询结果====================\n");
	printf("学号\t\t姓名\t\t性别\t\t年龄\n"); 
	if(count==0)
	{
		printf("==================共0人================\n");
	}
	else
	{
		for(int i=0;i<count;i++)
		{
			printf("%d\t\t%s\t\t",stu[i].sno,stu[i].name);
			printf("%c\t\t%d\n",stu[i].sex,stu[i].age);
		}
		printf("============共%d人==========\n",count);
	}
}
void Statistic_man(people p)//统计男生信息 
{
	system("cls");
	printf("\n");
	int count=0;
	printf("====================================================\n");
	printf("学号\t\t姓名\t\t性别\t\t年龄\n");
	printf("====================================================\n");
	for(int i=0;i<n;i++)
	{
		if(p[i].sex=='M')
		{
			printf("%d\t\t%s\t\t",p[i].sno,p[i].name);
			printf("%c\t\t%d\n",p[i].sex,p[i].age);
			count++;
		}
	}
	printf("======================共%d人=========================\n",count);
}
void Statistic_woman(people p)//统计女生信息 
{
	system("cls");
	printf("\n");
	int count=0;
	printf("====================================================\n");
	printf("学号\t\t姓名\t\t性别\t\t年龄\n");
	printf("====================================================\n");
	for(int i=0;i<n;i++)
	{
		if(p[i].sex=='F')
		{
			printf("%d\t\t%s\t\t",p[i].sno,p[i].name);
			printf("%c\t\t%d\n",p[i].sex,p[i].age);
			count++;
		}
	}
	printf("======================共%d人=========================\n",count);
}
void Age_find(people p,int year1,int year2)//年龄段查信息
{
	
	int flag=1,count=0;
	for(int i=0;i<n;i++)
    {
    	if(p[i].age<year1 && p[i].age>year2)
    	{
    		flag=0;
		}
	}
	if(flag==1)
	{
		printf("====================================================\n");
		printf("学号\t\t姓名\t\t性别\t\t年龄\n");
		printf("====================================================\n");
    	for(int j=0;j<n;j++)
    	{
       		if(p[j].age>=year1 && p[j].age<=year2)
        	{
        	   	printf("%d\t\t%s\t\t",p[j].sno,p[j].name);
				printf("%c\t\t%d\n",p[j].sex,p[j].age);
				count++;
        	}
   	 	}
   	 	printf("======================共%d人=========================\n",count);
   	 }
	else
		printf("无该年龄段学生\n");	
}
void Snofind_list(grade *w)//课程号查排名 
{
	system("cls");
	printf("\n");
	grade stu[10],t;
	int a,list=1,flag=0,count=0;
	printf("输入课程号：");
	scanf("%d",&a);
	for(int i=0;i<n2;i++)
	{
		if(w[i].gnum==a)
		{
			flag=1;
			stu[count]=w[i];
			count++;
		}	
	}
	for(int i=0;i<count-1;i++)
	{
		for(int j=0;j<count-1-i;j++)
		{
			if(stu[j].ggrade<stu[j+1].ggrade)
			{
				t=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=t;
			}
		}
	}
	if(flag!=0)
	{
		Sortg_g(w);
		printf("\n本科目平均分：%d\n",Average_score(w,a));
		printf("===================当前成绩=====================\n");
		for(int i=0;i<count;i++)
		{
				printf("学号：%d\t\t   ",stu[i].gno);
				printf("成绩：%d\t     ",stu[i].ggrade);
				printf("排名：%d\n",list);
				list++;
		}
		printf("================================================\n");
	}
	else
		printf("无此课程\n");
}						///////////////////////////////////////////////////////////////////
void Average_list(grade *w,people p)//学生平均分排名 
{
	int t,temp,f=0;
	int count=0;
	int ave[n]={0};
	int sno[n];
	for(int i=0;i<n2;i++)
	{
		for(int j=0;i<n2;j++)
		{
			if(p[i].sno==w[i].gno)
			{
				ave[i]+=w[j].ggrade;
				sno[i]=p[i].sno;
				f++;
			}
		}
		for(int k=0;k<n;k++)
		{
			if(f!=0)
			{
				ave[k]/=f;
			}
		}
		f=0;
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(ave[j]<ave[j+1])
			{
				t=ave[j];
				ave[j]=ave[j+1];
				ave[j+1]=t;
				temp=sno[j];
				sno[j]=sno[j+1];
				sno[j+1]=temp;
			}
		}
	}			///////////////////////////////////////////////////////////////////////////////
	printf("===================当前成绩=====================\n");
	for(int i=0;i<n;i++)
	{
		printf("学号：%d\t\t   ",sno[i]);
		printf("成绩：%d\t     ",ave[i]);
		printf("排名：%d\n",count);
	}
	printf("================================================\n");
}
void Information_changes(people p)//学号修改学生信息 
{
	Output_s(p); 
    int sno,flag=0;
    printf("请输入该学生学号：");
    scanf("%d",&sno);
    printf("\n");
    for(int i=0;i<n;i++)
    {
        if(p[i].sno==sno)
        {
            printf("进行修改\n");
            printf("姓名：");
            scanf("%s",p[i].name);
            fflush(stdin);
            printf("性别：");
            scanf("%c",&p[i].sex); 
            printf("年龄：");
            scanf("%d",&p[i].age);
            flag=1;
        }
    }
    if(flag==0)
    {
    	printf("无该学生\n");
	}
    else
	{
		system("pause");
    	Output_s(p);
	} 
}
void Information_changel(lesson *q)//课程号修改课程 
{
	Output_l(q);
	int sno,flag=0;
	printf("请输入课程号：");
	scanf("%d",&sno);
	for(int i=0;i<n1;i++)
    {
        if(q[i].lnumber==sno)
        {
            printf("进行修改\n");
            printf("课程号：");
            scanf("%d",&q[i].lnumber);
            printf("课程名：");
            scanf("%s",q[i].lname);
            fflush(stdin);
            printf("学分：");
            scanf("%d",&q[i].lscore);
            flag=1;
        }
    }
    if(flag==0)
    {
    	printf("无该课程\n");
	}
	else
	{
		system("pause");
		Output_l(q);
	}
}
void Information_changeg(grade *w)//按学号课程号修改成绩 
{
	Output_g(w);
	int sno,number,flag=0;
	printf("请输入学号：");
	scanf("%d",&sno);
	printf("请输入课程号：");
	scanf("%d",&number);
	for(int i=0;i<n2;i++)
	{
		if(w[i].gno==sno && w[i].gnum==number)
		{
			printf("进行修改\n");
			printf("成绩：");
			scanf("%d",&w[i].ggrade);
			flag=1;
		}
	}
	if(flag==0)
	{
		printf("无该成绩\n");
	}
	else 
	{
		system("pause");
		Output_g(w);
	}
}

void Information_deletes(people p)//按学号删学生信息 
{
	Output_s(p);
	int a,f,flag=0;
	printf("输入想删除学生的学生号：");
	scanf("%d",&a);
	for(int i=0;i<n;i++)
	{
		if(p[i].sno==a)
		{
			f=i;
			flag=1;
		}
	}
	if(flag!=0)
	{
		for(int i=f;i<n-1;i++)
		{
			p[i]=p[i+1];
	 	}
	 	p=(student*)realloc(p,(n-1)*sizeof(student));
	    n--;
	    system("pause");
		Output_s(p);
	}
	else 
	{
		printf("无该学生\n"); 
	}
} 
void Information_deletel(lesson *q)//按课程号删课程信息 
{
	Output_l(q);
	int a,f,flag=0;
	printf("请输入课程号：");
	scanf("%d",&a);
	for(int i=0;i<n1;i++)
	{
		if(q[i].lnumber==a)
		{
			f=i;
			flag=1;
		}
	}
	if(flag!=0)
	{
		for(int i=f;i<n1-1;i++)
		{
			q[i]=q[i+1];
		}
		q=(lesson*)realloc(q,(n1-1)*sizeof(lesson));
		n1--;
		system("pause");
		Output_l(q);
	}
	else
	{
		printf("无该课程\n");
	}
}
void Information_deleteg(grade *w)//按学号和课程号删成绩 
{
	Output_g(w);
	int a,b,f,flag=0;
	printf("输入学号：");
	scanf("%d",&a);
	printf("输入课程号：");
	scanf("%d",&b);
	for(int i=0;i<n2;i++)
	{
		if(w[i].gno==a && w[i].gnum==b)
		{
			f=i;
			flag=1;
		}
	}
	if(flag!=0)
	{
		for(int i=f;i<n2-1;i++)
		{
			w[i]=w[i+1];
		} 
		w=(grade*)realloc(w,(n2-1)*sizeof(grade));
	    n2--;
	    system("pause");
		Output_g(w);
	}
	else
	{
		printf("无该成绩\n");
	}
}
void Information_alldelete(grade *w)//按学号删除所有成绩 
{
	char ch='0';
	Output_g(w);
	int a,flag;
	printf("输入学生学号：");
	scanf("%d",&a);
	for(int i=0;i<n2;i++)
	{
		if(w[i].gno==a)
		{
			flag=i;
			ch='1';
			for(int j=flag;j<n2-1;j++)
			{
				w[j]=w[j+1];
			}
			w=(grade*)realloc(w,(n2-1)*sizeof(grade));
			n2--;
		}
	}
	if(ch!='0')
	{
		system("pause");
		Output_g(w);
	}
	else
	{
		printf("无该成绩\n");
	}
}

void Sortl(lesson *q)//课程号排序
{
    lesson t;
    for(int i=0;i<n1-1;i++)
    {
        for(int j=0;j<n1-i-1;j++)
        {
            if(q[j].lnumber>q[j+1].lnumber)
            {
                t=q[j];
               	q[j]=q[j+1];
                q[j+1]=t;
            }
        }
    }
}
void Sortg(grade *w)//成绩排序 
{
	grade t;
	for(int i=0;i<n2-1;i++)
	{
		for(int j=0;j<n2-i-1;j++)
		{
			if(w[j].gno>w[j+1].gno)
			{
				t=w[j];
				w[j]=w[j+1];
				w[j+1]=t;
			}
		}
	}
} 
void Sortg_g(grade *w)
{
	grade t;
	for(int i=0;i<n2-1;i++)
	{
		for(int j=0;j<n2-i-1;j++)
		{
			if(w[j].ggrade>w[j+1].ggrade)
			{
				t=w[j];
				w[j]=w[j+1];
				w[j+1]=t;
			}
		}
	}
}
int Average_score(grade *w,int a)//求平均分 
{
	int sum=0,count=0;
	for(int i=0;i<n2;i++)
	{
		if(w[i].gnum==a)
		{
			sum+=w[i].ggrade;
			count++;
		}
	}
	return sum/count;
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
void Find(people p,lesson *q,grade *w)
{
    int x;
    int flag=1;
    while(flag)
    {
        menu2();
        scanf("%d",&x);
        switch(x)
        {
            case 0://返回上层
                flag=0;
                break;
            case 1://统计学生信息 
                if(p==NULL)
                printf("当前学生信息为空！");
                Output_s(p);
                system("pause");
                break;
            case 2://课程信息 
            	if(q==NULL)
            		printf("当前课程信息为空！");
            		Output_l(q);
            	system("pause");
            	break;
            case 3://成绩信息 
            	if(w==NULL)
            		printf("当前成绩信息为空！");
            		Output_g(w);
            	system("pause");
                break;
			case 4://按学号查询学生的全部信息
                Sno_finds(p);
               	system("pause");
               	break;
            case 5:
				Sno_findg(w);//学号查成绩 
				system("pause");
				break;
			case 6:
				Snofind_detail(w);//学号查成绩明细 
				system("pause");
				break;
			case 7://学号查课程信息 
				Lnumber_find(q);
				system("pause");
				break;
			case 8://课程名查课程信息 
				Lname_find(q);
				system("pause");
				break;
			case 9://学分查课程信息 
				Lscore_find(q);
				system("pause");
				break;	
			case 10://找相同名字的人 
				Samename_find(p);
				system("pause");
				break;
			case 11://统计男生 
				Statistic_man(p);
				system("pause");
				break;
			case 12://统计女生 
				Statistic_woman(p);
				system("pause");
				break;
            case 13://查询某年龄段的学生信息
                int year1,year2;
                system("cls");
                printf("想查询学生的年龄段下限：");
                scanf("%d",&year1);
                printf("想查询学生的年龄段上限：");
                scanf("%d",&year2);
                Age_find(p,year1,year2);
                system("pause");
                break;
            case 14://课程号查成绩排名 
            	Snofind_list(w);
            	system("pause");
				break;
			default:
				printf("错误指令！\n");
				system("pause");
				break;
        }
        fflush(stdin);
    }
}
void Change(people p,lesson *q,grade *w)//修改程序 
{
	int x;
	int flag=1;
	while(flag)
	{
        menu3();
        scanf("%d",&x);
        switch(x)
        {
            case 0:
                flag=0;
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
            	printf("错误指令！\n");
            	system("pause");
            	break;
        }
        fflush(stdin);        
    }
} 
void Delete(people p,lesson *q,grade *w)
{
	int x;
	int flag=1;
	while(flag)
	{
		menu4();
		scanf("%d",&x);
		switch(x)
		{
			case 0:
				flag=0;
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
            	printf("错误指令！\n");
            	system("pause"); 
            	break;
		}
		fflush(stdin);
	} 
}
