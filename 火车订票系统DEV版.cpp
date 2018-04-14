/**********************************
*
*	�������ƣ�	�𳵶�Ʊϵͳ
*	���뻷����	DEV
*	������أ�	����
*	��ʼʱ�䣺	2018��4��6��
*	����޸ģ�	2018��4��6��
*
***********************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <conio.h>
using namespace std;

/********�ṹ��������**********/
struct date {
	int year;
	int month;
	int day;
};
struct stu {
	char startcity[20], endcity[20], starttime[20], endtime[20], serialnum[20];
	struct date data;
	int money;
	int ordernum = 0;
};


vector<stu> v;

/********����������**********/
void get();//���ļ��� 
void save();//������Ϣ 
void out(stu a);//�����Ϣ 
void add_trainformation();//�����Ϣ 
void delete_trainformation();//ɾ����Ϣ 
void modify_trainformation();//�޸���Ϣ 
void query_trainformation();//��ѯ��Ϣ 


int main() {
	get();
	cout << "��ӭ���룺�𳵶�Ʊϵͳ" << endl;
	
	int choice = 9;
	while(choice != 5) {
		system("pause");
		system("cls");//���� 
		cout << "\t\t��ӭ���룺�𳵶�Ʊϵͳ" << endl;
		printf("\n���������\t\t!!!����Ҫ��ʹ�ã��Ų�����o(���أ�o��)��\n");
		printf("�������У��Ͼ�\n");
		printf("������У��Ϻ�\n");
		printf("�꣺2018\n");
		printf("�£�5\n");
		printf("�գ�10\n");
		printf("����ʱ�䣺8:30\n");
		printf("����ʱ��:11:30\n");
		printf("�����кţ�0X529\n");
		printf("�۸�50\n\n");
		cout << "\t\t\t�𳵶�Ʊϵͳ\n";
		cout << "\t\t\t\t1.�����г���Ϣ\n";
		cout << "\t\t\t\t2.ɾ���г���Ϣ\n";
		cout << "\t\t\t\t3.�޸��г���Ϣ\n";
		cout << "\t\t\t\t4.��ѯ�г���Ϣ\n";
		cout << "\t\t\t\t5.���沢�˳�\n";
		cout << "���������1-5:";
		cin >> choice;
		if(choice < 1 || choice > 5)
			cout << "�Բ������������Ų���1-5�У��������룺\n";
		if(choice == 1) add_trainformation();
		if(choice == 2) delete_trainformation();
		if(choice == 3) modify_trainformation();
		if(choice == 4) query_trainformation();
		save();
	} 
    return 0;
}

void get() {
	FILE *fp;
	struct stu a;
	fp = fopen("trainformation.txt","r");
	while(fread(&a,sizeof(struct stu),1,fp) == 1) {
		v.push_back(a);
	}
	//fclose(fp);
}

void add_trainformation(){
	stu a;
	cout << "�������� ������� ���� ����ʱ�� ����ʱ��  �����к�\n\n";
	
	cout << "����������У�";
	scanf("%s",a.startcity);

	cout << "���뵽����У�";
	scanf("%s",a.endcity);

	cout << "��������꣺";
	scanf("%d",&a.data.year);
	
	cout << "��������£�";
	scanf("%d",&a.data.month);
	
	cout << "��������գ�";
	scanf("%d",&a.data.day);

	cout << "�������ʱ�䣺";
	scanf("%s",a.starttime);

	cout << "���뵽��ʱ�䣺";
	scanf("%s",a.endtime);

	cout << "��������кţ�";
	scanf("%s",a.serialnum);

	cout << "������г��۸�";
	scanf("%d",&a.money);
	
	cout << "��Ʊ����" << a.ordernum << endl;
	
	v.push_back(a);
}

void delete_trainformation(){
	string s;
	cout  << "����������кţ�";
	cin >> s;
	int flag = 1;
	if(flag == 1){
		for(int i = 0; i < v.size(); i++) {
			if(s == v[i].serialnum) {//��ѯ�г���� 
				flag = 0;
				out(v[i]);
				cout << "ȷ��ɾ����y,��ɾ����n:";
				char c;
				cin >> c;
				if(c == 'y'){
					v.erase(v.begin() + i);
					cout << "��ɾ��\n";
				}
				break;
			}
		}
		if(flag == 1)
			cout << "���޴��л�\n"; 
	} 
}

void modify_trainformation(){
	string s;
	char news[20];
	cout  << "����������кţ�";
	cin >> s;
	int flag = 1;
	if(flag == 1){
		for(int i = 0; i < v.size(); i++) {
			if(s == v[i].serialnum) {
				flag = 0;
				stu a = v[i];
				out(v[i]);
				cout << "\n�����к�Ϊ�����޸���!!!\n" ;
				char c;
				cout << "�޸ĳ�������y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "�������³�������:";
					scanf("%s",news);
					strcpy(a.startcity, news);
				}
			
				cout << "�޸ĵ������y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "�������µ������:";
					scanf("%s",news);
					strcpy(a.endcity, news);
				}
	
				cout << "�޸�������y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "��������������:";
					int newt;
					scanf("%d",&newt);
					a.data.year = newt;
				}
				
				cout << "�޸�������y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "��������������:";
					int newt;
					scanf("%d",&newt);
					a.data.month = newt;
				}
				
				cout << "�޸�������y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "��������������:";
					int newt;
					scanf("%d",&newt);
					a.data.day = newt;
				}

				cout << "�޸ĳ���ʱ��y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "�������³���ʱ��:";
					scanf("%s",news);
					strcpy(a.starttime, news);
				}

				cout << "�޸ĵ���ʱ��y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "�������µ���ʱ��:";
					scanf("%s",news);
					strcpy(a.endtime, news);
				}
				
				cout << "�޸ļ۸�y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "�������¼۸�:";
					int newt;
					scanf("%d",&newt);
					a.money = newt;
				}
				v[i] = a;
				break;
			}
		}
		if(flag == 1){
			cout << "���޴��л�\n";
		}
	}
}

void query_trainformation(){
	char s[20], e[20];
	cout << "����������У�";
	scanf("%s",s);
	cout << "���뵽����У�";
	scanf("%s",e);
	int i = 0;
	int flag = 0;
	for(i = 0; i < v.size(); i++) {
		if(strcmp(s, v[i].startcity) == 0 && strcmp(e, v[i].endcity) == 0) {
			cout << "��ѯ��Ϣ���£�" << endl; 
			out(v[i]);
			flag = 1;
			break; 
		}
	}
	if(flag == 0) 
		cout << "���޴��л�\n";
	else {
		cout << endl << "���������1-3��" << endl; 
		cout << "1.��Ʊ" << endl; 
		cout << "2.��Ʊ" << endl;
		cout << "3.����" << endl; 
		cout << "����Ҫ��"; 
		int t;
		cin >> t;
		if(t == 1) {
			v[i].ordernum++;
			cout << "�Ѷ�Ʊ����" << v[i].ordernum << endl;  
			cout << "----------��ܰ����----------" << endl;
			printf("    ������%d��%d��%d��%s֮ǰƾȡƱ֪ͨ���ʵ�����ȡƱ��\n\n",v[i].data.year,v[i].data.month,v[i].data.day,v[i].starttime);
			cout << "----------�����˵��վ�----------" << endl;
			cout << "	���ã����˴�Ʊ��Ϊ"  << v[i].money << "Ԫ��" << endl;
		}else if(t == 2){
			if(v[i].ordernum > 0) {
				v[i].ordernum--;
				cout << "��Ʊ�ɹ���" << endl;
				cout << "�ֶ�Ʊ����" << v[i].ordernum << endl;
			}else{
				cout << "�Բ����㻹û�ж���Ʊ" << endl; 
			}
		}else {
			cout << "���سɹ���" << endl; 
		}
	} 	 
}


void save(){
	FILE *fp;
	struct stu a;
	int size = sizeof(stu);
	fp = fopen("trainformation.txt","w");
	fclose(fp);
	fp = fopen("trainformation.txt","a+");
	for(stu i : v) {
		fwrite(&i,sizeof(struct stu),1,fp);
	}
	fclose(fp);	
}

void out(stu a){
	printf("�������У�%s\n",a.startcity);
	printf("������У�%s\n",a.endcity);
	printf("���ڣ�%d��%d��%d��\n",a.data.year,a.data.month,a.data.day);
	printf("����ʱ�䣺%s\n",a.starttime);
	printf("����ʱ��:%s\n",a.endtime);
	printf("�����кţ�%s\n",a.serialnum);
	printf("�۸�%d\n",a.money);
	printf("��Ʊ����%d\n",a.ordernum);
}

