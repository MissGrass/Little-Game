/**********************************
*
*	�������ƣ�	�����Ϣ����ϵͳ
*	���뻷����	DEV
*	������أ�	
*	��ʼʱ�䣺	2018��6��8��
*	����޸ģ�	2018��6��8��
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

typedef struct stu {
	int b_No;//ͼ���� 
	string b_Name;//ͼ������ 
	string b_author;//ͼ������ 
	int b_sales = 0;//ͼ�������� 
}; 

typedef struct cus {
	int c_No;//�˿ͱ�� 
	string c_Name;//�˿����� 
	int c_bNo[6] ={'0'};//�˿͹�����鼮
	int c_buyNum[6];//������ 
};


/********����������**********/
void get();//���ļ��� 
void save();//������Ϣ 
void show_bookInfo(stu a[]);//��ʾͼ����Ϣ
void buy_book(cus c[],stu a[]);//��������
void show_shoppingCart(cus c[],stu a[]);//��ʾ���ﳵ��Ϣ
void sort_booksales(stu a[]);//��ѯͼ���������� 
void del_book(int cnum,cus c[],stu a[]); 

bool compare(const stu &x, const stu &y)
{
      return x.b_sales > y.b_sales;   //����

}

vector<stu> v;
vector<cus> p;

int main(){
	
	struct stu a[6];
	a[0].b_No = 111;
	a[0].b_Name = "�����塷";
	a[0].b_author ="������"; 
//	a[0].b_sales = 0;
	
	a[1].b_No = 222;
	a[1].b_Name = "����������";
	a[1].b_author = "���"; 
//	a[1].b_sales = 10;
	
	a[2].b_No = 333;
	a[2].b_Name = "�����¾���";
	a[2].b_author = "����"; 
//	a[2].b_sales = 20;
	
	a[3].b_No = 444;
	a[3].b_Name = "���������ӡ�";
	a[3].b_author = "����"; 
///	a[3].b_sales = 30;
	
	a[4].b_No = 555;
	a[4].b_Name = "��������ƫ����";
	a[4].b_author = "�򡤰�˹͡"; 
//	a[4].b_sales = 40;
	
	a[5].b_No = 666;
	a[5].b_Name = "�������ˣ�������";
	a[5].b_author = "������"; 
//	a[5].b_sales = 50;
	
	
	struct cus c[3];
	c[0].c_No = 0;
	c[0].c_Name = "����";
	c[1].c_No = 1; 
	c[1].c_Name = "С��";
	c[2].c_No = 2; 
	c[2].c_Name = "С��";


	get();
	cout << "��ӭ���룺�����Ϣ����ϵͳ" << endl;
	
	int choice = 9;
	while(choice != 5){
		system("pause");
		system("cls");//����
		cout << "\t\t��ӭ���룺�����Ϣ����ϵͳ" << endl;
		cout << "\t\t\t�����Ϣ����ϵͳ\n";
		cout << "\t\t\t\t1.��ʾͼ����Ϣ\n";
		cout << "\t\t\t\t2.��������\n";
		cout << "\t\t\t\t3.��ʾ���ﳵ��Ϣ\n";
		cout << "\t\t\t\t4.��ѯͼ����������\n";
		cout << "\t\t\t\t5.���沢�˳�\n";
		cout << "���������1-5:";
		
		cin >> choice;
		if(choice < 1 || choice > 5)
			cout << "�Բ������������Ų���1-5�У��������룺\n" ;
		if(choice == 1) show_bookInfo(a);//��ʾͼ����Ϣ
		if(choice == 2) buy_book(c,a);//��������
		if(choice == 3) show_shoppingCart(c,a);//��ʾ���ﳵ��Ϣ
		if(choice == 4) sort_booksales(a);//��ѯͼ����������
		save();
	} 
	return 0;
} 

void get() {
	FILE *fp;
	stu a[6];
	fp = fopen("bookInfo.txt","r");
	
//	while(fread(&a,sizeof(struct stu),1,fp) == 1) {
	for(int i = 0; i < 6; i++){
		
			//while(fread(&a[i],sizeof(struct stu),1,fp) == 1){
			v.push_back(a[i]);
		//	}
		//	v.push_back(a[i]);
	}
		
//	}
	
//	cus c[3]; 
//	fpt = fopen("cusInfo.txt","r");
//
////	while(fread(&c,sizeof(struct cus),1,fpt) == 1) {
//		for(int i = 0; i < 3; i++){
////			while(fread(&c[i],sizeof(struct cus),1,fpt) == 1){
//				p.push_back(c[i]);
////			}
//		//	p.push_back(c[i]);
////		}
//		
//	}
//	//fclose(fp);
}


void show_bookInfo(stu a[6]){
	for(int i = 0; i < 6; i++){
		printf("ͼ���ţ�%d\n",a[i].b_No);
		cout << "ͼ��������"<< a[i].b_Name <<endl;
		cout << "ͼ�����ߣ�"<< a[i].b_author <<endl;
		printf("ͼ����������%d\n\n",a[i].b_sales);
	}
}


void buy_book(cus c[3],stu a[6]) {
	int cnum;
	while(1) {
		cout << "�˿ͱ�ţ�";
		scanf("%d",&cnum); 
		cout << "�˿͹�����һ���ԣ�������" << endl;
		for(int i = 0; i < 6; i++) {
			int bnum, buynum;
			cout << "ͼ���ţ�";
			scanf("%d",&bnum);
	
			cout << "��������";
			scanf("%d",&buynum);
		//	cout << bnum  << " " << cnum<<endl;
		//	cout << c[cnum].c_bNo[i];
			
			c[cnum].c_bNo[i] = bnum;
			c[cnum].c_buyNum[i] = buynum;
			a[bnum%10-1].b_sales += buynum;
			p.push_back(c[cnum]);
			v.push_back(a[bnum%10-1]);
			cout << "��λ�˿��Ƿ�Ҫ�������򣿣�Y/y������������������������������" << endl;
			char ch;
			cin >> ch;
			if(ch == 'y' || ch == 'Y') continue;
			else break;
		}
		cout << "�Ƿ��������˿�Ҫ���򣿣�Y/y����������������������������" << endl;
		char ch1;
		cin >> ch1;
		if(ch1 == 'y' || ch1 == 'Y') continue;
		else break;
	} 
}

void del_book(int cnum,cus c[3],stu a[6]){//��չ˿͹��ﳵ 
	for(int i = 0; i < 6; i++){
		a[c[cnum].c_bNo[i]%10-1].b_sales -= c[cnum].c_buyNum[i];
		c[cnum].c_bNo[i] = 0;
		c[cnum].c_buyNum[i] = 0;
	}
}

void show_shoppingCart(cus c[3],stu a[6]){
	int cnum;
	cout << "�˿ͱ�ţ�";
	scanf("%d",&cnum); 
	
	cout << "�˿�������"<< c[cnum].c_Name <<endl;
	if(c[cnum].c_bNo[0] != 0){
		for(int i = 0; i < 6; i++){
			if(c[cnum].c_bNo[i] == 0){
				break;
			}
			int t = c[cnum].c_bNo[i] % 10 - 1;
		//	cout << t << endl;
			cout << "ͼ��������"<< a[t].b_Name <<endl;
			printf("��������%d\n",c[cnum].c_buyNum[i]); 
			
		}
	}
	else  {
		cout << "���޹���ͼ�飡" << endl; 
	}
	
	
	int choi = 9;
	while(choi != 3){
		cout << "\t\t\t\t1.�޸�\n";		
		cout << "\t\t\t\t2.ȷ��\n";
		cout << "\t\t\t\t3.�ύ\n";
		cin >> choi;
		if(choi == 1) {
			del_book(cnum,c,a);//������� 
			cout << "������գ���ȫ�����¹���"<< endl; 
			buy_book(c,a);//���¹��� 
		}
		if(choi == 2) cout << "��ȷ��";
		if(choi == 3) cout << "���ύ";
	} 

}


void sort_booksales(stu a[]){
	cout << "ͼ����������\n";
	sort(a,a+6,compare);
	for(int i = 0; i < 6; i++){
		cout << a[i].b_Name << "\t\t";
		printf("ͼ����������%d\n\n",a[i].b_sales);
	}
}



void save(){
	FILE *fp;
	struct stu a[6];
	int size = sizeof(stu);
	fp = fopen("bookInfo.txt","w");
	fclose(fp);
	fp = fopen("bookInfo.txt","a+");
	for(stu i : v) {
		fwrite(&i,sizeof(struct stu),1,fp);
	}
	fclose(fp);
//	struct cus c[3];
//	int sizet = sizeof(cus);
//	fpt = fopen("cusInfo.txt","w");
//	fclose(fpt);
//	fpt = fopen("cusInfo.txt","a+");
//	for(cus i : p) {
//		fwrite(&i,sizeof(struct stu),1,fpt);
//	}
//	fclose(fpt);	
} 
