#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//variable
int lots = 0,result = 0;
//struct
struct library
{
	char name[101];
	char code[101];
	int qty;
}data[201];
//open list 
void list()
{
	for (int i=0; i<lots; i++)
	{
		printf("Judul: %-30s Code: %-30s Stock: %d\n", data[i].name,data[i].code,data[i].qty);
	}
	printf("\n");
}
//QUICKSORT
//swap
void swap (library *x, library *y)
{
	library temp = *x;
	*x = *y;
	*y = temp;
}
//partition
int par(int c, int low, int high)
{
	int x = low - 1;
	if(c==1)
	{
		char pivot1[100];
		strcpy(pivot1,data[high].name);
		
		for(int j = low; j<= high-1; j++)
		{
			if(strcmp(data[high].name,pivot1)<0)
			{
				x++;
				swap(&data[x],&data[j]);
			}
		}

	}
	//sort by quantity
	if(c==2)
	{
		int pivot2 = data[high].qty;
		
		for(int j = low; j<=high-1; j++)
		{
			if(data[high].qty<pivot2)
			{
				x++;
				swap(&data[x],&data[j]);
			}
		}
	}
	
	swap(&data[x+1],&data[high]);
	return(x+1);
}
//sort 
void sort(int c,int low,int high)
{
	if(low<high)
	{
		int pi = par(c,low,high);
		sort(c,low,pi-1);
		sort(c,pi+1,high);
	}
}

// search book
 void search ()
 {
 	char namabuku[101];
 	printf("Input Nama/Code buku: ");
 	scanf("%[^\n]", namabuku);
 	getchar();
	 int flag = 0;
 	for(int i =0; i<lots; i++)
 	{
 		if(strcasecmp(namabuku,data[i].name)==0|| strcasecmp(namabuku,data[i].code)==0)
 		{
 			printf("Judul: %-30s Code: %-30s Stock: %d\n", data[i].name,data[i].code,data[i].qty);
 			flag++;
 			result = i;
 			break;
		 }
	 }
	 if(flag == 0)
	 {
	 	printf("Book Not Found!!!!!");
	 }
	 
 }
// borrow book
void borrow()
{
	int flag = 0;
	search();
	if(flag == 1)
	{
		if(data[result].qty > 0)
		{
			data[result].qty--;
			printf("You have borrowed %s\n", data[result].name);
		}
		else
		{
			printf ("OUT OF STOCK!!!\n");
			flag =0;
		}
	}
	FILE *fw = fopen("library.txt","w");
	
	for(int j=0; j<lots;j++)
	{
		fprintf(fw,"%s#%s#%d\n", data[j].name,data[j].code,data[j].qty);
	}
	fclose(fw);
	
}
// close menu 
void close()
{
	printf("THANK YOU!");
}
//menu
void menu()
{
	int tasks;
	printf("===========================================\n");
	printf("WELCOME\n");
	printf("1. Sort book by name\n");
	printf("2. sort book by quantity\n");
	printf("3. search for book\n");
	printf("4. borrow a book\n");
	printf("5. Exit\n");
	printf("===========================================\n");
	printf(">>");
	scanf("%d", &tasks);
	getchar();
	
	
	if (tasks == 1)
	{sort(2,0,lots-1);list();}
	if(tasks == 2)
	{sort(1,0,lots-1);list();}
	if(tasks == 3)
	{search();}
	if(tasks == 4)
	{borrow();}
	if(tasks == 4)
	{close();}
	
	printf("press any button to get back\n");
	getch();
	system("cls");
	
	menu();
}

int main()
{
	int x=0;
	FILE *f;
	f = fopen("library.txt", "r");
	
	if (f == NULL)
	{return 1;}
	
	while(fscanf(f,"%[^#]#%[^#]#%d\n", data[x].name,data[x].code,&data[x].qty) != EOF)
	{
		x++;
	}
	fclose(f);
	lots = x;
	menu();
	return 0;
}







