#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <conio.h>
#define N 10
#define HOURROOM 10
#define NORMALROOM 288
#define BIGROOM 388
#define WORTHROOM 588
#define GREATROOM 998

struct room_message{
	int number;		//�����
	int people;		//������ס
	int floor;		//¥��������ͬ¥�㷿�����Ͳ�ͬ��
	time_t time;		//��סʱ�䣬����ס���ÿ�
}ROOM[100];

struct administrator{
	char name[16];
	char password[16];
	int number;
	int age;
	int sex;
}group[25];

int TheUsingAdministrator;

void BuildGroup(){     //���������ļ�
	FILE *fp=NULL;
	int a;
	char b[16]={"0"};
	if((fp=fopen("administrator.dat","r"))==NULL){             //�����ļ�,��ֹ����
		fp=fopen("administrator.dat","w");
		for(a=0;a<25;a++){
			strcpy(group[a].name,b);
			strcpy(group[a].password,b);
			group[a].number=a+1;
			group[a].sex=group[a].age=0;
			fwrite(&group[a],sizeof(struct administrator),1,fp);
			}
	}
	else{
		for(a=0;a<25;a++){
			fread(&group[a],sizeof(struct administrator),1,fp);
		}
	}
	fclose(fp);
}


void BuildRoom(){    //���������ã�����ĺ���
FILE *fp=NULL;
int i,j;//����ѭ��
if((fp=fopen("roommessage.dat","r"))==NULL)
	{
	    fp=fopen("roommessage.dat","w");
		for(i=0;i<N;i++)
			{
				for(j=0;j<N;j++)
					{
						ROOM[i*	10+j].number= j;
						ROOM[i*	10+j].floor= i;
						ROOM[i*	10+j].people= 0;
						ROOM[i*	10+j].time= 0;
						fwrite(&ROOM[i*	10+j],sizeof(struct room_message),1,fp);
					}
			}
	}
else {
	for(i=0;i<N;i++)
			{
				for(j=0;j<N;j++)
					{
						fread(&ROOM[i*	10+j],sizeof(struct room_message),1,fp);
					}
			}
	}
fclose(fp);
}

void PrintFee(int floor,int room,int fee,int people){    //��ӡ�������
	time_t time1,time2;
	int a;
	time1 = ROOM[floor*10+room].time;
	time2 = time(NULL);
	if(people==0){
		printf("�÷���û����\n");
		}
	else {
	if(floor<2){
		a = ((time2-time1)/3600)+1;
		printf("�÷���ķ���Ϊ%dԪ\n",a*fee);
	}
	else{
		a=(((time2-time1)/3600)/24)+1;
		printf("�÷���ķ���Ϊ%dԪ\n",a*fee);
	}
	}
	}

void CheckOut(){	//�˷����������ü�����ú�������������ס���
	int roomnuber,choose,a,b,floor,room,fee;
	FILE *fp=NULL;
	do{
	printf("\n�����������˷��ķ���ķ����:");
	scanf("%d",&roomnuber);
	floor=(roomnuber / 100) - 1;
	room=roomnuber%100;
	floor = (roomnuber/100)-1 ;
	room = (roomnuber%100)-1;
	if(floor>9||floor<0||room<0||room>9){
		printf("����������������������\n");
	}
	}while(floor>9||floor<0||room<0||room>9);
	printf("��Ҫ�˵ķ�Ϊ%d,����",roomnuber);
	if(floor==0||floor==1){			
		printf("�ӵ㷿\n");
		fee=HOURROOM;
	}
	if(floor==2||floor==3){			
		printf("��׼��\n");
		fee=NORMALROOM;
	}
	if(floor==4||floor==5){			
		printf("�󴲷�\n");
		fee=BIGROOM;
	}
	if(floor==6||floor==7){			
		printf("�����׷�\n");
		fee=WORTHROOM;
	}
	if(floor==8||floor==9){			
		printf("�����׷�\n");
		fee=GREATROOM;
	}
	do{
	printf("\n���Ƿ�ȷ��Ҫ�˷���\n");
	printf("1.��\n");
	printf("2.����\n");
	scanf("%d",&choose);
	if(choose!=1&&choose!=2){
		printf("\n����������������������\n");
	}
	}while(choose!=1&&choose!=2);
	if(choose==1){
	PrintFee(floor,room,fee,ROOM[floor*10+room].people);
	ROOM[floor*10+room].people=0;
	ROOM[floor*10+room].time=0;
	fp=fopen("roommessage.dat","w");
		for(a=0;a<N;a++){
			for(b=0;b<N;b++){
				fwrite(&ROOM[a*	10+b],sizeof(struct room_message),1,fp);
			}
		}
		printf("\n�˷��ɹ�\n");
	}
	fclose(fp);
	system("pause");
}

void CalFee(){		//�ƷѺ�����ͨ��ʱ��������������  
	int roomnuber,floor,room,fee;
	do{
	printf("\n�����������ѯ���õķ���ķ����(����1001):");
	scanf("%d",&roomnuber);
	floor = (roomnuber/100)-1 ;
	room = (roomnuber%100)-1;
	if(floor>9||floor<0||room<0||room>9){
		printf("����������������������\n");
	}
	}while(floor<0||floor>9||room<0||room>9);
	printf("��Ҫ�ҵ�%d�ŷ�Ϊ",roomnuber);
	if(floor==0||floor==1){			
		printf("�ӵ㷿\n");
		fee=HOURROOM;
	}
	if(floor==2||floor==3){			
		printf("��׼��\n");
		fee=NORMALROOM;
	}
	if(floor==4||floor==5){			
		printf("�󴲷�\n");
		fee=BIGROOM;
	}
	if(floor==6||floor==7){			
		printf("�����׷�\n");
		fee=WORTHROOM;
	}
	if(floor==8||floor==9){			
		printf("�����׷�\n");
		fee=GREATROOM;
	}
	PrintFee(floor,room,fee,ROOM[floor*10+room].people);
}

void ScanRoom(){	//��ѯ��������ȡ��ס���
	int a,i,j;
	FILE *fp=NULL;
	void PrintRoomFee(int a);
	printf("\n��ѡ����Ҫ��ѯ�ķ�������\n");
	printf("1.�ӵ㷿\n");
	printf("2.��׼��\n");
	printf("3.Ϊ�󴲷�\n");
	printf("4.Ϊ�����׷�\n");
	printf("5.Ϊ�����׷�\n");
	scanf("%d",&a);
	if((fp=fopen("roommessage.dat","r"))!=NULL){
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
				{
					fread(&ROOM[i*10+j],sizeof(struct room_message),1,fp);
				}
		}
			if(a == 1){
			PrintRoomFee(a);
			for(i=0;i<=1;i++){
				for(j=0;j<10;j++){
					printf("\n��%d��",ROOM[i*10+j].floor+1);
					printf("��%d�ŷ�",ROOM[i*10+j].number+1);
					if(ROOM[i*10+j].people){
						printf("���ˣ�������ס");
					}
					else{
						printf("û���ˣ�������ס");
					}
				}
			}
			}
			if(a == 2){
			PrintRoomFee(a);
			for(i=2;i<=3;i++){
				for(j=0;j<10;j++){
					printf("\n��%d��",ROOM[i*10+j].floor+1);
					printf("��%d�ŷ�",ROOM[i*10+j].number+1);
					if(ROOM[i*10+j].people){
						printf("���ˣ�������ס");
					}
					else{
						printf("û���ˣ�������ס");
					}
				}
			}
			}
			if(a == 3){
			PrintRoomFee(a);
			for(i=4;i<=5;i++){
				for(j=0;j<10;j++){
					printf("\n��%d��",ROOM[i*10+j].floor+1);
					printf("��%d�ŷ�",ROOM[i*10+j].number+1);
					if(ROOM[i*10+j].people){
						printf("���ˣ�������ס");
					}
					else{
						printf("û���ˣ�������ס");
					}
				}
			}
			}
			if(a == 4){
			PrintRoomFee(a);
			for(i=6;i<=7;i++){
				for(j=0;j<10;j++){
					printf("\n��%d��",ROOM[i*10+j].floor+1);
					printf("��%d�ŷ�",ROOM[i*10+j].number+1);
					if(ROOM[i*10+j].people){
						printf("���ˣ�������ס");
					}
					else{
						printf("û���ˣ�������ס");
					}
				}
			}
			}
			if(a == 5){
			PrintRoomFee(a);
			for(i=8;i<=9;i++){
				for(j=0;j<10;j++){
					printf("\n��%d��",ROOM[i*10+j].floor+1);
					printf("��%d�ŷ�",ROOM[i*10+j].number+1);
					if(ROOM[i*10+j].people){
						printf("���ˣ�������ס");
					}
					else{
						printf("û���ˣ�������ס");
					}
				}
			}
		}
	}
}

void PrintRoomFee(int a){                 //��ӡ����۸�
	if(a==1||a==2){
		printf("\n�ӵ㷿�ķ���ΪÿСʱ%dԪ\n",HOURROOM);
	}
	if(a==3||a==4){
		printf("\n��׼��ķ���Ϊÿ��%dԪ\n",NORMALROOM);
	}
	if(a==5||a==6){
		printf("\n�󴲷��ķ���Ϊÿ��%dԪ\n",BIGROOM);
	}
	if(a==7||a==8){
		printf("\n�����׷��ķ���Ϊÿ��%dԪ\n",WORTHROOM);
	}
	if(a==9||a==10){
		printf("\n�����׷��ķ���Ϊÿ��%dԪ\n",GREATROOM);
	}

}

void CheckIn(){      //��ס��������¼ʱ�䣬������ס���
	int a,b,c,i,j;
	FILE *fp=NULL;
	do{
	printf("\n������������ס�ķ������(1~10)");
	printf("\n1~2Ϊ�ӵ㷿");
	printf("\n3~4Ϊ��׼��");
	printf("\n5~6Ϊ�󴲷�");
	printf("\n7~8Ϊ�����׷�");
	printf("\n9~10Ϊ�����׷�\n");
	scanf("%d",&a);
	if(a<1||a>10){
		printf("����������������������\n");
	}
	}while(a<1||a>10);
	PrintRoomFee(a);
	do{
	printf("\n������������ס�ķ����(1~10)��");
	scanf("%d",&b);
	if(b<1||b>10){
		printf("����������������������\n");
	}
	}while(b<1||b>10);
	if((fp=fopen("roommessage.dat","rb"))!=NULL){			//���ļ�
	if(ROOM[(a-1)*10+(b-1)].people==0){		//�жϷ����Ƿ��ס
	for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
				{
					fread(&ROOM[i*10+j],sizeof(struct room_message),1,fp);
				}
		}
		fclose(fp);
		printf("\n��������ס������:");
		scanf("%d",&c);
		ROOM[(a-1)*10+b-1].people=c;
		ROOM[(a-1)*10+b-1].time=time(NULL);
		fp=fopen("roommessage.dat","w");
		for(a=0;a<N;a++){
			for(b=0;b<N;b++){
				fwrite(&ROOM[a*	10+b],sizeof(struct room_message),1,fp);
			}
		}
	}
	else{
		printf("\n�÷����Ѿ�������\n");
		printf("��ѡ�������ķ�����ס\n");
	}
	}
	fclose(fp);
}

void ChangePassword(){          //�޸�����
	FILE *fp=NULL;
	char password1[16]={'0'},password2[16]={'0'},password[16]={'0'},c;
	int a=0,b=0;                            //aΪ������
	printf("\n������������:");
	while((c=getch())!='\r')  
	{  
		if(c!='\b'){
			password1[a]=c;
			password[a]=c;
			putchar('*');  
			a++;
		}
		else{
			a--;
			if(a<0){
				a++;
				putchar(' ');
			}
			else{
				password1[a+1]='\0';
				password[a+1]='\0';
			}
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		if (a > 15)  
		{  
			break;  
		}
	}
	printf("\n���ٴ�����������:");
	a=0;
	while((c=getch())!='\r')  
	{  
		if(c!='\b'){
			password2[a]=c;  
			putchar('*');  
			a++; 
		}
		else{
			a--;
			if(a<0){
				a++;
				putchar(' ');
			}
			else{
				password2[a+1]='\0';
			}
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		if (a > 15)  
		{  
			break;  
		}
	}
	if(strcmp(password1,password2)){    //�ȶ������Ƿ�һ��
		printf("\n�������벻һ�����޸�����ʧ��\n");
	}
	else{
		strcpy(group[TheUsingAdministrator-1].password,password);
		printf("\n�޸�����ɹ�!\n");
		fp=fopen("administrator.dat","wb");
		for(b=0;b<25;b++){
			fwrite(&group[b],sizeof(struct administrator),1,fp);
		}
		fclose(fp);
	}
	system("pause");
}

void PrintAdministrator(){      //��ӡ���е��ʺ���Ϣ
	char b[16]={'0'};
	int a;
	printf("���\t�û���\t\t����\t\t����\t�Ա�\n");
	for(a=0;a<25;a++){
		if(strcmp(b,group[a].name)){
			printf("%d\t",a+1);
			printf("%s\t",group[a].name);
			if(strlen(group[a].name)<8){
				printf("\t");
			}
			printf("%s\t",group[a].password);
			if(strlen(group[a].password)<8){
				printf("\t");
			}
			printf("%d\t",group[a].age);
			switch(group[a].sex){
				case 0:printf("δ�޸��Ա�");break;
				case 1:printf("��");break;
				case 2:printf("Ů");break;
				case 3:printf("˵����");break;
			}
			printf("\n");
		}
	}
	system("pause");
}

int ChangeRoom(){    //�Ƶ����ϵͳ�Ĳ˵�
	int step;
	BuildRoom();
	do{				//������ѭ��
	do{				//ѡ�����ѭ��
		system("cls");
		printf("\n����������ִ�еĲ������\n");
		printf("1.�Ǽ���ס\n");
		printf("2.��ѯ��ס���\n");
		printf("3.��ѯ��ǰ����\n");
		printf("4.�˷�\n");
		printf("5.�ص�������\n");
		scanf("%d",&step);
		if(step<1||step>5)
			{
			printf("\n����������������������\n");
			system("pause");
			}
		}while(step<1||step>5);
		switch(step){
		case 1:CheckIn();break;
	    case 2:ScanRoom();break;
		case 3:CalFee();break;
		case 4:CheckOut();break;
		case 5:return 0;
	}
	printf("\n�����㻹��ִ���������������\n");
	printf("1.��\n");
	printf("2.��\n");
	do{
		scanf("%d",&step);
		if(step<1||step>2)
			{
				printf("\n����������������������\n");
			}
	}while(step<1||step>2);
	}while(step==1);
	return 0;
}

void ChangeGroup(){   //д���ʺ���Ϣ
	FILE *fp=NULL;
	int a;
	fp=fopen("administrator.dat","w");
	for(a=0;a<25;a++){
		fwrite(&group[a],sizeof(struct administrator),1,fp);
	}
	fclose(fp);
}

void DeleteAdministrator(){   //ɾ���ʺ�
	int a;
	char b[16]={'0'};
	PrintAdministrator();
	do{
	printf("\n��������Ҫɾ�����˻������:");
	scanf("%d",&a);
	if(a==TheUsingAdministrator){
		printf("����ɾ��������ʹ�õ��ʺ�\n");
		}
	}while(a==TheUsingAdministrator);
	strcpy(group[a-1].name,b);
	strcpy(group[a-1].password,b);
	group[a-1].sex=group[a-1].age=0;
	ChangeGroup();		//д����Ϣ
	printf("ɾ���ɹ�\n");
	system("pause");
}
void ChangeAge(){    //�޸�����
	int a;
	printf("\n����������:\n");
	scanf("%d",&a);
	group[TheUsingAdministrator-1].age=a;
	printf("�޸ĳɹ�\n");
	system("pause");
	ChangeGroup();
}

void ChangeSex(){  //�޸��Ա�
	int a;
	do{
	printf("\n��ѡ���Ա�:\n");
	printf("1.��\n");
	printf("2.Ů\n");
	printf("3.˵����\n");
	scanf("%d",&a);
	if(a<1||a>3){
		printf("����������������������\n");
		system("pause");
		system("cls");
	}
	}while(a<1||a>3);
	group[TheUsingAdministrator-1].sex=a;
	printf("�޸ĳɹ�\n");
	system("pause");
	ChangeGroup();
}

void ControlAdministrator(){   //�ʺŹ���˵�
	int step;
	system("cls");
	printf("\n��ѡ������ִ�еĲ���\n");
	printf("1.�鿴�����˻���Ϣ\n");
	printf("2.ɾ��һ���˻�\n");
	printf("3.�޸ĵ�ǰ�˻�����\n");
	printf("4.�޸ĵ�ǰ�˻�����\n");
	printf("5.�޸ĵ�ǰ�˻��Ա�\n");
	scanf("%d",&step);
	switch(step){
		case 1:PrintAdministrator();break;
		case 2:DeleteAdministrator();break;
		case 3:ChangePassword();break;
		case 4:ChangeAge();break;
		case 5:ChangeSex();break;
	}
}

int Logadministrator(){   //��¼�ʺ�
	char name[16]={'0'},password[16]={'0'},wrong[16]={'\r'};
	char c;
	int a,d,right,empty;                              //aΪ������,rightΪ�ж��Ƿ���ȷ,empty�ж��û����Ƿ����,b����������¼
	system("cls");
	printf("\n�����������û���:");
	d=0;
	while((c=getch())!='\r'){
		if(c!='\b'){
			name[d]=c;
			putchar(c);
			d++;
		}
		else{
			d--;
			if(d<0){
				d++;
				putchar(' ');
			}
			else{
				name[d+1]='\0';
			}
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		if(d>15)
		{
			break;
		}
	}
	if(strcmp(name,wrong)==0){
		printf("�û�������Ϊ�գ�����������\n");
		system("pause");
		return 0;
	}
	printf("\n��������������:");
	d=0;
	while((c=getch())!='\r')  
	{  
		if(c!='\b'){
			password[d]=c;  
			putchar('*');  
			d++;
		}
		else{
			d--;
			if(d<0){
				d++;
				putchar(' ');
			}
			else{
				password[d+1]='\0';
			}
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		if (d > 15||d<0)  
		{  
			break;  
		}
	}
	for(a=0,right=0;a<25;a++){
		if(strcmp(name,group[a].name)==0)
		{
			if(strcmp(password,group[a].password)==0){
				right=1;
			}
			break;
		}
		if(a==24){
			empty=1;
		}
	}
	if(empty!=1){                  //������󣬷�ֹ�벻�����������
		if(right==0){
			printf("\n��������������������������\n");
			system("pause");
			return 0;
		}
	}
	else{
		printf("\n��������û��������ڣ�����������\n");
		system("pause");
		return 0;
	}
	system("cls");
	printf("\n��ӭ����%s!\n",group[a].name);
	TheUsingAdministrator=group[a].number;
	system("pause");
	return 1;
}

int Newadministrator(){   //ע���ʺ�
	char d[16]={'0'},name[16]={'0'};
	FILE *fp=NULL;
	char c;
	int a,b;
	system("cls");
	do{
	printf("\n����������ʹ�õ��û���:");
	b=0;
	strcpy(name,d);
	while((c=getch())!='\r'){
		if(c!='\b'){
			name[b]=c;
			putchar(c);
			b++;
		}
		else{
			b--;
			if(b<0){
				b++;
				putchar(' ');
			}
			else{
				name[b+1]='\0';
			}
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		if(b>15)
		{
			break;
		}
	}
	printf("\n");
		for(a=0;a<25;a++){
		if(strcmp(name,group[a].name)==0){
			printf("\n����û����Ѿ���ʹ���ˣ��뻻һ���û���\n");
			break;
		}
		if(strcmp(d,group[a].name)==0){
			break;
		}
	}
	}while(strcmp(name,group[a].name)==0);
	if(a<25){
	strcpy(group[a].name,name);
	printf("����������:");
	b=0;
	while((c=getch())!='\r')  
	{  
		if(c!='\b'){
		group[a].password[b]=c;  
		putchar('*');  
		b++;
		}
		else{
			b--;
			if(b<0){
				b++;
				putchar(' ');
			}
			else{
				group[a].password[b+1]='\0';
			}
			putchar('\b');   //����ɾ����ӡ�����ַ�
			putchar(' ');
			putchar('\b');
		}
		if (b > 15)  
		{  
			break;  
		}
	}
	fp=fopen("administrator.dat","wb");
	for(b=0;b<25;b++){
		fwrite(&group[b],sizeof(struct administrator),1,fp);
		}
	fclose(fp);
	system("cls");
	printf("\n��ӭ����%s!\n",group[a].name);
	TheUsingAdministrator=group[a].number;
	system("pause");
	return 1;
	}
	else{
		printf("�ѵ���ע�����ޣ�����ע��\n");
		return 0;
	}
}


int Admin(){   //��¼�˵�
	int a=0,b,choose;             //a�Ǵ��͵�
	do{
	do{
	system("cls");
	b=0;
	printf("\n��������Ҫ��ʲô\n");
	printf("1.��¼�����ʺ�\n");
	printf("2.ע���µ��ʺ�\n");
	scanf("%d",&choose);
	if(choose!=1&&choose!=2){
		system("pause");
		printf("����������������������\n");
	}
	}while(choose!=1&&choose!=2);
	switch(choose){
		case 1:a=Logadministrator();break;
		case 2:a=Newadministrator();break;
	}
	if(a==0){
	system("cls");
	printf("\n�Ƿ���������:\n");
	printf("1.��(����ѡ���¼����ע��)\n");
	printf("2.��(���˳�����)\n");
	scanf("%d",&b);
	}
	}while(b==1);
	return a;
}

int LogIn(){   //��ӭ����
	system("cls");
	printf("**********************");
	printf("\n*��ӭʹ�þƵ����ϵͳ*\n");
	printf("**********************\n\n");
	printf("�뽫���뷨תΪӢ��\n");
	system("pause");
	BuildGroup();
	return Admin();
}

//system("cls")��������  
void main()
{
	int step;
	if(LogIn()){
		do{
		system("cls");
		printf("\n��ѡ��������������:\n");
		printf("1.����Ƶ���Ϣ\n");
		printf("2.�����˻���Ϣ\n");
		printf("3.ע���˻�\n");
		printf("4.�˳�ϵͳ\n");
		scanf("%d",&step);
		switch(step){
		case 1:ChangeRoom();break;
		case 2:ControlAdministrator();break;
		case 3:if(LogIn()==0){
				step=4;
			   };break;
		}
		}while(step!=4);
		system("cls");
		printf("\n��л����ʹ�ã������˳�...\n");
		printf("�˳��ɹ�\n");
		system("pause");
	}
	else{
		printf("\n��¼ʧ�ܣ����򼴽��˳�\n");
		printf("�������˳�\n");
		system("pause");
	}
}

