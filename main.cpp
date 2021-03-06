#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<conio.h>
#define Max 4

typedef struct book
{
	char book_num[10];
	char book_name[20];
	char book_writer[10];
	int book_xy;
	int book_kc;
	int n;
	struct book *next;
}BK;

typedef struct borrow
{
	char borrow_book_num[10];
	char limit_date[10];
	}BO;

typedef struct reader
{
	char reader_num[10];
	char reader_name[10];
	int right;
	int m;
	BO borrow[Max];
	struct reader *next;
}RD;

BK *h_book;
RD *h_reader;
int n=0;
int m=0;

void Login();
int Menu();
void Init();
void Menu_select();
void Insert_New_Book();
void add_reader();
void Print_reader();
void Print_book();
void Borrow_Book();
void Return_Book();
void Save();
void Save_Book();
void Save_Reader();
void Load();
void Load_Reader();
void Load_Book();

void Login()
{
	system("cls");
	printf("\n\n\n\t\t***************************************\n");
	printf("\n\n\n\t\t**        欢迎使用图书管理系统       **\n");
	printf("\n\n\n\t\t***************************************\n");
	printf("\n\n\n\t\t 按任意键进入系统...");

	getch();
	system("cls");
}

int Menu() /*主菜单*/
{
	int dm;

	printf("\n\t\t图书管理系统主菜单\n");
	printf("=================================================\n");
	printf("*\t1----采编入库          \n");
	printf("*\t2----登记读者          \n");
	printf("*\t3----借阅登记          \n");
	printf("*\t4----还书管理          \n");
	printf("*\t5----查询图书信息      \n");
	printf("*\t6----查询读者信息      \n");
	printf("*\t0----退出系统          \n");
	printf("=================================================\n");
	printf("请选择相应的代码:");

	for(;;)
	{
		scanf("%d",&dm); //dm输入的数字
		if(dm<0||dm>6)
			printf("\n错误!请重新输入:");
		else
			break;
	}

	return dm;
}
void Menu_select()/*主菜单选择函数*/
{
	for(;;)
	{
		switch(Menu()) /*功能选择*/
		{
			case 0:
		     		system("cls");
		   			Save();
					printf("\n\n\t文件保存成功!\n");
					printf("\n\n\t欢迎下次使用本系统!\n");
		 			getch();
					exit(0);
			case 1: Insert_New_Book();break;
			case 2: add_reader();break;
			case 3: Borrow_Book();break;
			case 4: Return_Book();break;
			case 5: Print_book();break;
			case 6: Print_reader();break;
			default:printf("\n错误!");

			exit(0);
		}
	}
}

void Init() /*初始化*/
{
	BK *p0;
	printf("\n图书初始化开始,请输入图书信息..\n包括编号.书名.数量..\n");
	p0=(BK*)malloc(sizeof(BK));
	h_book=p0;

	printf("\n请输入图书信息:\n");
	printf("图书编号:");            /*输入图书编号(唯一)*/
	scanf("%s",p0->book_num);
	printf("图书名称:");           /*输入图书名称*/
	scanf("%s",p0->book_name);
	printf("图书作者:");           /*输入图书作者*/
	scanf("%s",p0->book_writer);
	printf("图书数量:");             /*输入图书数量*/
	scanf("%d",&p0->book_kc);

	p0->book_xy=p0->book_kc;     /*开始时图书现有量和库存量相等*/
	p0->next=NULL;
	p0->n=++n;

	printf("\n图书信息初始化完毕!按任意键继续下一步操作..\n");
	getch();
	system("cls");
}

void Insert_New_Book()/*新书入库*/
{
	BK *p,*p0,*p1;
	p=p1=h_book;
	printf("\n新书入库模块...\n");
	printf("\n请输入新书信息..\n包括书号.书名.数量..\n");
	p0=(BK *)malloc(sizeof(BK));

	printf("图书编号:");
	scanf("%s",p0->book_num);

	while(strcmp(p0->book_num,p1->book_num)!=0&&p1->next!=NULL)
		p1=p1->next;

	if(strcmp(p0->book_num,p1->book_num)==0) /*此处分两种情况,若图书编号存在,则直接进库,只须输入书的数量*/
	{
		printf("\n此编号图书已存在!!直接入库!\n");
	    printf("图书数量:");
	    scanf("%d",&p0->book_kc);

	    p1->book_kc+=p0->book_kc;
	    p1->book_xy+=p0->book_kc;
	}

	else/*若不存在,则需要输入其他的信息,然后在进行插入操作*/
	{
		printf("图书名称:");
		scanf("%s",p0->book_name);
		printf("图书作者:");
		scanf("%s",p0->book_writer);
		printf("图书数量:");
		scanf("%d",&p0->book_kc);//库存数量

		while(p->next)
			p=p->next;

		if(h_book==NULL)
			h_book=p0;   /*此处分两种情况,链表中没有数据,head直接指向p0处*/

		else
			p->next=p0;               /*此处分两种情况,链表中有数据,链表中最后元素的next指向p0处*/

		p0->next=NULL;
	    p0->book_xy=p0->book_kc;
	    p0->n=++n;
	}

	    printf("\n新书入库完毕!按任意键继续下一步操作..\n");
		getch();
		system("cls");
}

void add_reader()/*添加读者*/
{
	RD *p0;
    int i;
    printf("\n读者初始化开始,请输入读者信息..\n包括书证号.姓名..\n");
	p0=(RD*)malloc(sizeof(RD));     /*申请新结点存储空间*/
	h_reader=p0;

	printf("\n请输入读者的信息:\n");
    printf("读者书证号:");
    scanf("%s",p0->reader_num);
    printf("读者姓名:");
	scanf("%s",p0->reader_name);
    p0->right=0;

    for(i=0;i<Max;i++)
    {
		strcpy(p0->borrow[i].borrow_book_num,"0"); /*所借图书直接置为(即没有借书)*/
		strcpy(p0->borrow[i].limit_date,"0");
	}

	p0->next=NULL;
	p0->m=++m;

	printf("\n读者信息初始化完毕!按任意键继续下一步操作..\n");
	getch();
	system("cls");
}

void Borrow_Book() /*借书模块*/
{
	BK *p0; RD *p1;
	char bo_num[10],rea_num[10],lim_date[8];
	int i;
	p0=h_book; p1=h_reader;

	printf("\n借书模块...\n");
	printf("\n请输入借书的读者书证号:");
	scanf("%s",rea_num);

	while(p1->next!=NULL&&strcmp(rea_num,p1->reader_num)!=0)
	   p1=p1->next;

	if(p1->next==NULL&&strcmp(rea_num,p1->reader_num)!=0)
	{
		printf("\n此读者编号不存在!按任意键返回..\n");
		goto END;
	}

	printf("\n请输入你要借的书的编号:");
	scanf("%s",bo_num);
	while(strcmp(bo_num,p0->book_num)!=0&&p0->next!=NULL)
		p0=p0->next;

	if(p0->next==NULL&&strcmp(bo_num,p0->book_num)!=0)
	{
		printf("\n此图书编号不存在!按任意键返回..\n");
		goto END;
	}

	else if(p0->book_xy<=0)
		{
			printf("\n抱歉,此书已借完!请等待新书的到来!!\n按任意键返回....");
			goto END;
		}

		else if(p1->right>Max||p1->right==Max)
	    	{
				printf("\n不好意思,借书数目已满!不能借书!\n按任意键返回....");
				goto END;
			}

			else if(strcmp(p1->borrow[0].borrow_book_num,"0")!=0)
				{
					for(i=0;i<Max;i++)
					{
						if(strcmp(p1->borrow[i].borrow_book_num,bo_num)==0)
						{
							printf("\n抱歉!同一个读者不能同借两本相同的书!\n按任意键返回....");
							goto END;
						}

						else if(strcmp(p1->borrow[i].borrow_book_num,"0")==0)
							{
								printf("\n请输入你要归还图书的日期:");
						        scanf("%s",lim_date);

						        strcpy(p1->borrow[p1->right++].borrow_book_num,bo_num);
						        strcpy(p1->borrow[p1->right-1].limit_date,lim_date);

						        p0->book_xy--;

						        printf("\n读者编号%s借书完毕!按任意键继续下步操作..",p1->reader_num);
						        goto END;
	       					}
					}
	    		}

				else
	    		{
					printf("\n请输入你要归还图书的日期:");
					scanf("%s",lim_date);

					strcpy(p1->borrow[p1->right++].borrow_book_num,bo_num);
					strcpy(p1->borrow[p1->right-1].limit_date ,lim_date );

					p0->book_xy--;
					p0->book_kc--;

					printf("\n读者编号%s借书完毕!按任意键继续下步操作..",p1->reader_num);

					goto END;
	     		}
	     		END:getch(); system("cls");
}

void Return_Book() /*还书模块*/
{
	BK *p; RD *q;
	int i,j,find=0;
	char return_book_num[10],return_reader_num[10];
	p=h_book; q=h_reader;

	printf("\n还书模块...\n");
	printf("\n请输入要还书的读者编号:");
	scanf("%s",return_reader_num);

	while(q->next!=NULL&&strcmp(return_reader_num,q->reader_num)!=0)
	    q=q->next;

	if(q->next==NULL&&strcmp(return_reader_num,q->reader_num)!=0)
	{
		find=2;
		printf("\n此读者编号不存在!按任意键返回..\n");
		goto end;
	}

	printf("\n请输入读者还书的编号:");
	scanf("%s",return_book_num);

	while(p->next!=NULL&&strcmp(return_book_num,p->book_num)!=0)
		p=p->next;

	if(p->next==NULL&&strcmp(return_book_num,p->book_num)!=0)
	{
		find=2;
		printf("\n错误!此图书编号不存在!按任意键返回..\n");
		goto end;
	}

	for(i=0;i<Max;i++)
		if(strcmp(return_book_num,q->borrow[i].borrow_book_num)==0)     /*如果此读者借了此书*/
		{
			find=1;
	        for(j=i;j<Max-1;j++)
	   		{
	        	strcpy(q->borrow[j].borrow_book_num,q->borrow[j+1].borrow_book_num);
	    		strcpy(q->borrow[j].limit_date,q->borrow[j+1].limit_date);
   			}

			strcpy(q->borrow[Max-1].borrow_book_num,"0");
			strcpy(q->borrow[Max-1].limit_date,"0");

	        p->book_xy++;
	        q->right--;

	        printf("\n编号%s的读者还书完毕!按任意键继续下步操作..",return_reader_num);

	        goto end;
	     }

   	if(find==0)
		printf("\n错误!此读者未借此书!按任意键返回..\n");

	end: getch(); system("cls");
}

void Print_book() /*查询图书信息*/
{
	BK *p;
	int i;
	char e[10];
	p=h_book;

	printf("输入查询的图书编号:");
	scanf("%s", e);
	for(i=0;i<n;i++)
	{
		if(strcmp(p->book_num,e)==0)
		{
			printf("\n图书信息如下:\n\n");
			printf("图书编号\t图书名称\t图书作者\t现有\t库存\n");
			printf("%s\t\t%s\t\t%s\t\t%d\t%d\n",p->book_num,p->book_name,p->book_writer,p->book_xy,p->book_kc);
		break;
		}
		else
			p=p->next;
	}

	printf("\n图书信息打印完毕!按任意键继续下一步操作..");

	getch();
	system("cls");
}

void Print_reader()     /*查询读者信息*/
{
	RD *p;
	int i, j;
	char e[10];
	p=h_reader;

	printf("输入查询的读者编号:");
	scanf("%s", e);

	for(j=0;j<m;j++)
	{
		if(strcmp(p->reader_num,e)==0)
		{
			printf("\n读者信息如下:\n\n");
			printf("读者书证号\t读者姓名\n");
			printf("%s\t\t%s",p->reader_num,p->reader_name);

			for(i=0;i<Max;i++)
			{
				printf("\n");
				printf("图书编号",i+1);
				printf("\t还书日期",i+1);
				printf("\n");
				printf("\t%s",p->borrow[i].borrow_book_num);
				printf("\t\t%s",p->borrow[i].limit_date);
			}
			printf("\n");
			break;
		}

		else
			p=p->next;
		}

	printf("\n读者信息打印完毕!按任意键继续下一步操作..");
	getch();
	system("cls");
}

void Save() /*保存信息*/
{
	Save_Reader();
	Save_Book();
}

void Save_Reader()   /*保存读者信息*/
{
	FILE *fp_reader;
	RD *p,*p0;
	p=h_reader;

	if((fp_reader=fopen("Reader.txt","wb"))==NULL)   /*创建文件,进行保存*/
	{
		printf("\n文件保存失败!\n请重新启动本系统...\n");
		exit(0);
	}

	while(p!=NULL)
	{
		if(fwrite(p,sizeof(RD),1,fp_reader)!=1)   /*将链表中的信息写入文件中*/
		printf("\n写入文件失败!\n请重新启动本系统!\n");
		p0=p;
		p=p->next;
		free(p0); /*释放所有结点*/
	}

	h_reader=NULL;
	fclose(fp_reader);    /*关闭文件*/
}

void Save_Book() /*保存图书信息*/
{
	FILE *fp_book;     /*创建文件型指针*/
	BK *p,*p0;
	p=h_book;
	if((fp_book=fopen("Book.txt","wb"))==NULL)      /*创建文件,进行保存*/
	{
		printf("\n文件保存失败!\n请重新启动本系统...\n");
		exit(0);
	}

	while(p!=NULL)
	{
		if(fwrite(p,sizeof(BK),1,fp_book)!=1)                /*将链表中的信息写入文件中*/
	    printf("\n写入文件失败!\n请重新启动本系统!\n");
		p0=p;
		p=p->next;
		free(p0);
	}

	h_book=NULL;
	fclose(fp_book);   /*关闭文件*/
}

void Load() /*加载信息*/
{
	Load_Reader();
	Load_Book();
}

void Load_Reader()   /*加载读者信息*/
{
   RD *p1,*p2,*p3;
   FILE *fp;           /*创建文件型指针*/
   fp=fopen("Reader.txt","rb");       /*打开文件*/
   p1=(RD *)malloc(sizeof(RD));
   fread(p1,sizeof(RD),1,fp);
   h_reader=p3=p2=p1;

   while(! feof(fp))   /*读出信息,重新链入链表*/
   {
		p1=(RD *)malloc(sizeof(RD));
		fread(p1,sizeof(RD),1,fp);
		p2->next=p1;
		p3=p2;
		p2=p1;
   }

   p3->next=NULL;
   free(p1);
   fclose(fp); /*关闭文件*/
}

void Load_Book() /*加载图书信息*/
{
	BK *p1,*p2,*p3;
	FILE *fp;            /*创建文件型指针*/
	fp=fopen("Book.txt","rb");   /*打开文件*/
	p1=(BK *)malloc(sizeof(BK));
	fread(p1,sizeof(BK),1,fp);
	h_book=p3=p2=p1;

	while(! feof(fp))   /*读出信息,重新链入链表*/
	{
		p1=(BK *)malloc(sizeof(BK));
		fread(p1,sizeof(BK),1,fp);
		p2->next=p1;
		p3=p2;
		p2=p1;
	}

	p3->next=NULL;
	free(p1);
	fclose(fp);   /*关闭文件*/
}

int main()
{
    FILE *fp_book,*fp_reader;              /*创建文件型指针*/

    Login();

    if((fp_book=fopen("Book.txt","rb"))==NULL||(fp_reader=fopen("Reader.txt","rb"))==NULL)
		Init();
    else
		Load();

   Menu_select(); /*调用主菜单*/
}


