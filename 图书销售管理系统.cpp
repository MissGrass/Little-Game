/**********************************
*
*	程序名称：	书店信息管理系统
*	编译环境：	DEV
*	作者相关：	
*	开始时间：	2018年6月8日
*	最后修改：	2018年6月8日
*
***********************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <conio.h>
using namespace std;

/********结构体声明区**********/

typedef struct stu {
	int b_No;//图书编号 
	string b_Name;//图书名字 
	string b_author;//图书作者 
	int b_sales = 0;//图书销售量 
}; 

typedef struct cus {
	int c_No;//顾客编号 
	string c_Name;//顾客姓名 
	int c_bNo[6] ={'0'};//顾客购买的书籍
	int c_buyNum[6];//购买本数 
};


/********函数声明区**********/
void get();//打开文件件 
void save();//保存信息 
void show_bookInfo(stu a[]);//显示图书信息
void buy_book(cus c[],stu a[]);//购买新书
void show_shoppingCart(cus c[],stu a[]);//显示购物车信息
void sort_booksales(stu a[]);//查询图书销售排行 
void del_book(int cnum,cus c[],stu a[]); 

bool compare(const stu &x, const stu &y)
{
      return x.b_sales > y.b_sales;   //降序

}

vector<stu> v;
vector<cus> p;

int main(){
	
	struct stu a[6];
	a[0].b_No = 111;
	a[0].b_Name = "《三体》";
	a[0].b_author ="刘慈欣"; 
//	a[0].b_sales = 0;
	
	a[1].b_No = 222;
	a[1].b_Name = "《我们三》";
	a[1].b_author = "杨绛"; 
//	a[1].b_sales = 10;
	
	a[2].b_No = 333;
	a[2].b_Name = "《道德经》";
	a[2].b_author = "老子"; 
//	a[2].b_sales = 20;
	
	a[3].b_No = 444;
	a[3].b_Name = "《骆驼祥子》";
	a[3].b_author = "老舍"; 
///	a[3].b_sales = 30;
	
	a[4].b_No = 555;
	a[4].b_Name = "《傲慢与偏见》";
	a[4].b_author = "简·奥斯汀"; 
//	a[4].b_sales = 40;
	
	a[5].b_No = 666;
	a[5].b_Name = "《永别了，武器》";
	a[5].b_author = "海明威"; 
//	a[5].b_sales = 50;
	
	
	struct cus c[3];
	c[0].c_No = 0;
	c[0].c_Name = "大王";
	c[1].c_No = 1; 
	c[1].c_Name = "小聪";
	c[2].c_No = 2; 
	c[2].c_Name = "小张";


	get();
	cout << "欢迎进入：书店信息管理系统" << endl;
	
	int choice = 9;
	while(choice != 5){
		system("pause");
		system("cls");//清屏
		cout << "\t\t欢迎进入：书店信息管理系统" << endl;
		cout << "\t\t\t书店信息管理系统\n";
		cout << "\t\t\t\t1.显示图书信息\n";
		cout << "\t\t\t\t2.购买新书\n";
		cout << "\t\t\t\t3.显示购物车信息\n";
		cout << "\t\t\t\t4.查询图书销售排行\n";
		cout << "\t\t\t\t5.保存并退出\n";
		cout << "请输入序号1-5:";
		
		cin >> choice;
		if(choice < 1 || choice > 5)
			cout << "对不起，您输入的序号不在1-5中，重新输入：\n" ;
		if(choice == 1) show_bookInfo(a);//显示图书信息
		if(choice == 2) buy_book(c,a);//购买新书
		if(choice == 3) show_shoppingCart(c,a);//显示购物车信息
		if(choice == 4) sort_booksales(a);//查询图书销售排行
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
		printf("图书编号：%d\n",a[i].b_No);
		cout << "图书书名："<< a[i].b_Name <<endl;
		cout << "图书作者："<< a[i].b_author <<endl;
		printf("图书销售量：%d\n\n",a[i].b_sales);
	}
}


void buy_book(cus c[3],stu a[6]) {
	int cnum;
	while(1) {
		cout << "顾客编号：";
		scanf("%d",&cnum); 
		cout << "顾客购买需一次性，不叠加" << endl;
		for(int i = 0; i < 6; i++) {
			int bnum, buynum;
			cout << "图书编号：";
			scanf("%d",&bnum);
	
			cout << "购买本数：";
			scanf("%d",&buynum);
		//	cout << bnum  << " " << cnum<<endl;
		//	cout << c[cnum].c_bNo[i];
			
			c[cnum].c_bNo[i] = bnum;
			c[cnum].c_buyNum[i] = buynum;
			a[bnum%10-1].b_sales += buynum;
			p.push_back(c[cnum]);
			v.push_back(a[bnum%10-1]);
			cout << "这位顾客是否要继续购买？（Y/y则继续购买，其他任意键放弃继续购买）" << endl;
			char ch;
			cin >> ch;
			if(ch == 'y' || ch == 'Y') continue;
			else break;
		}
		cout << "是否有其他顾客要购买？（Y/y则继续，其他任意键放弃继续购买）" << endl;
		char ch1;
		cin >> ch1;
		if(ch1 == 'y' || ch1 == 'Y') continue;
		else break;
	} 
}

void del_book(int cnum,cus c[3],stu a[6]){//清空顾客购物车 
	for(int i = 0; i < 6; i++){
		a[c[cnum].c_bNo[i]%10-1].b_sales -= c[cnum].c_buyNum[i];
		c[cnum].c_bNo[i] = 0;
		c[cnum].c_buyNum[i] = 0;
	}
}

void show_shoppingCart(cus c[3],stu a[6]){
	int cnum;
	cout << "顾客编号：";
	scanf("%d",&cnum); 
	
	cout << "顾客姓名："<< c[cnum].c_Name <<endl;
	if(c[cnum].c_bNo[0] != 0){
		for(int i = 0; i < 6; i++){
			if(c[cnum].c_bNo[i] == 0){
				break;
			}
			int t = c[cnum].c_bNo[i] % 10 - 1;
		//	cout << t << endl;
			cout << "图书书名："<< a[t].b_Name <<endl;
			printf("购买本数：%d\n",c[cnum].c_buyNum[i]); 
			
		}
	}
	else  {
		cout << "尚无购买图书！" << endl; 
	}
	
	
	int choi = 9;
	while(choi != 3){
		cout << "\t\t\t\t1.修改\n";		
		cout << "\t\t\t\t2.确认\n";
		cout << "\t\t\t\t3.提交\n";
		cin >> choi;
		if(choi == 1) {
			del_book(cnum,c,a);//购买清空 
			cout << "购买清空，请全部重新购买！"<< endl; 
			buy_book(c,a);//重新购买 
		}
		if(choi == 2) cout << "已确认";
		if(choi == 3) cout << "已提交";
	} 

}


void sort_booksales(stu a[]){
	cout << "图书销售排行\n";
	sort(a,a+6,compare);
	for(int i = 0; i < 6; i++){
		cout << a[i].b_Name << "\t\t";
		printf("图书销售量：%d\n\n",a[i].b_sales);
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
