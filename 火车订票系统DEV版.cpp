/**********************************
*
*	程序名称：	火车订票系统
*	编译环境：	DEV
*	作者相关：	沉香
*	开始时间：	2018年4月6日
*	最后修改：	2018年4月6日
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

/********函数声明区**********/
void get();//打开文件件 
void save();//保存信息 
void out(stu a);//输出信息 
void add_trainformation();//添加信息 
void delete_trainformation();//删除信息 
void modify_trainformation();//修改信息 
void query_trainformation();//查询信息 


int main() {
	get();
	cout << "欢迎进入：火车订票系统" << endl;
	
	int choice = 9;
	while(choice != 5) {
		system("pause");
		system("cls");//清屏 
		cout << "\t\t欢迎进入：火车订票系统" << endl;
		printf("\n添加样例：\t\t!!!不按要求使用，概不负责，o(￣ヘ￣o＃)哼\n");
		printf("出发城市：南京\n");
		printf("到达城市：上海\n");
		printf("年：2018\n");
		printf("月：5\n");
		printf("日：10\n");
		printf("出发时间：8:30\n");
		printf("到达时间:11:30\n");
		printf("火车序列号：0X529\n");
		printf("价格：50\n\n");
		cout << "\t\t\t火车订票系统\n";
		cout << "\t\t\t\t1.增添列车信息\n";
		cout << "\t\t\t\t2.删除列车信息\n";
		cout << "\t\t\t\t3.修改列车信息\n";
		cout << "\t\t\t\t4.查询列车信息\n";
		cout << "\t\t\t\t5.保存并退出\n";
		cout << "请输入序号1-5:";
		cin >> choice;
		if(choice < 1 || choice > 5)
			cout << "对不起，您输入的序号不在1-5中，重新输入：\n";
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
	cout << "出发城市 到达城市 日期 出发时间 到达时间  火车序列号\n\n";
	
	cout << "输入出发城市：";
	scanf("%s",a.startcity);

	cout << "输入到达城市：";
	scanf("%s",a.endcity);

	cout << "输入出发年：";
	scanf("%d",&a.data.year);
	
	cout << "输入出发月：";
	scanf("%d",&a.data.month);
	
	cout << "输入出发日：";
	scanf("%d",&a.data.day);

	cout << "输入出发时间：";
	scanf("%s",a.starttime);

	cout << "输入到达时间：";
	scanf("%s",a.endtime);

	cout << "输入火车序列号：";
	scanf("%s",a.serialnum);

	cout << "输入此列车价格：";
	scanf("%d",&a.money);
	
	cout << "订票数：" << a.ordernum << endl;
	
	v.push_back(a);
}

void delete_trainformation(){
	string s;
	cout  << "请输入火车序列号：";
	cin >> s;
	int flag = 1;
	if(flag == 1){
		for(int i = 0; i < v.size(); i++) {
			if(s == v[i].serialnum) {//查询列车序号 
				flag = 0;
				out(v[i]);
				cout << "确认删除按y,不删除按n:";
				char c;
				cin >> c;
				if(c == 'y'){
					v.erase(v.begin() + i);
					cout << "已删除\n";
				}
				break;
			}
		}
		if(flag == 1)
			cout << "查无此列火车\n"; 
	} 
}

void modify_trainformation(){
	string s;
	char news[20];
	cout  << "请输入火车序列号：";
	cin >> s;
	int flag = 1;
	if(flag == 1){
		for(int i = 0; i < v.size(); i++) {
			if(s == v[i].serialnum) {
				flag = 0;
				stu a = v[i];
				out(v[i]);
				cout << "\n火车序列号为不可修改项!!!\n" ;
				char c;
				cout << "修改出发城市y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新出发城市:";
					scanf("%s",news);
					strcpy(a.startcity, news);
				}
			
				cout << "修改到达城市y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新到达城市:";
					scanf("%s",news);
					strcpy(a.endcity, news);
				}
	
				cout << "修改日期年y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新日期年:";
					int newt;
					scanf("%d",&newt);
					a.data.year = newt;
				}
				
				cout << "修改日期月y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新日期月:";
					int newt;
					scanf("%d",&newt);
					a.data.month = newt;
				}
				
				cout << "修改日期日y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新日期日:";
					int newt;
					scanf("%d",&newt);
					a.data.day = newt;
				}

				cout << "修改出发时间y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新出发时间:";
					scanf("%s",news);
					strcpy(a.starttime, news);
				}

				cout << "修改到达时间y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新到达时间:";
					scanf("%s",news);
					strcpy(a.endtime, news);
				}
				
				cout << "修改价格y/n?:";
				cin >> c;
				if(c == 'y') {
					cout << "请输入新价格:";
					int newt;
					scanf("%d",&newt);
					a.money = newt;
				}
				v[i] = a;
				break;
			}
		}
		if(flag == 1){
			cout << "查无此列火车\n";
		}
	}
}

void query_trainformation(){
	char s[20], e[20];
	cout << "输入出发城市：";
	scanf("%s",s);
	cout << "输入到达城市：";
	scanf("%s",e);
	int i = 0;
	int flag = 0;
	for(i = 0; i < v.size(); i++) {
		if(strcmp(s, v[i].startcity) == 0 && strcmp(e, v[i].endcity) == 0) {
			cout << "查询信息如下：" << endl; 
			out(v[i]);
			flag = 1;
			break; 
		}
	}
	if(flag == 0) 
		cout << "查无此列火车\n";
	else {
		cout << endl << "请输入序号1-3：" << endl; 
		cout << "1.订票" << endl; 
		cout << "2.退票" << endl;
		cout << "3.返回" << endl; 
		cout << "您需要："; 
		int t;
		cin >> t;
		if(t == 1) {
			v[i].ordernum++;
			cout << "已订票数：" << v[i].ordernum << endl;  
			cout << "----------温馨提醒----------" << endl;
			printf("    请您于%d年%d月%d日%s之前凭取票通知和帐单交款取票。\n\n",v[i].data.year,v[i].data.month,v[i].data.day,v[i].starttime);
			cout << "----------您的账单收据----------" << endl;
			cout << "	您好，您此次票价为"  << v[i].money << "元。" << endl;
		}else if(t == 2){
			if(v[i].ordernum > 0) {
				v[i].ordernum--;
				cout << "退票成功！" << endl;
				cout << "现订票数：" << v[i].ordernum << endl;
			}else{
				cout << "对不起，你还没有订过票" << endl; 
			}
		}else {
			cout << "返回成功！" << endl; 
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
	printf("出发城市：%s\n",a.startcity);
	printf("到达城市：%s\n",a.endcity);
	printf("日期：%d年%d月%d日\n",a.data.year,a.data.month,a.data.day);
	printf("出发时间：%s\n",a.starttime);
	printf("到达时间:%s\n",a.endtime);
	printf("火车序列号：%s\n",a.serialnum);
	printf("价格：%d\n",a.money);
	printf("订票数：%d\n",a.ordernum);
}

