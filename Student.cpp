//#include"Student.h"
//#include"StudentDeal.h"
//#include"Studentlnterface.h"
#include<bits/stdc++.h>
using namespace std;
#ifndef STUDENT_H
#define STUDENT_H
#include<string>
#include<iostream>
using namespace std;
const int subject_num=5;
class Student{
	public:
		string num;
		string name;
		string sex;
		float score[subject_num];
		static char*subject_name[];
		float totalSum;
		float averageScore;
		int index;
		public:
			Student(){};
			Student(string num0,string name0,string sex0,float score[subject_num]);
			virtual void Input();
			virtual void Print();
			void Tablehead();
};
struct NodeType{
	Student data;
	NodeType*next;
};
#endif
#include<iostream>
#include<iomanip>
//#include"Student.h"
using namespace std;
char*Student::subject_name[]={"语文","数学","英语","科学","信息技术"};
Student::Student(string num0,string name0,string sex0,float score0[subject_num]){
	float floats;
	num=num0;
	name=name0;
	sex=sex0;
	floats=0;
	cout<<subject_num;
	for(int i=0;i<subject_num;i++)
		score[i]=score0[i],totalSum+=score0[i];
	averageScore=totalSum/subject_num;
}
void Student::Input(){
	float sum=0;
	char choi[5];
	cout<<"请输入学号：";
	cin>>num;
	cout<<"请输入姓名：";
	cin>>name;
	cout<<"请输入性别（0：女，1：男）";
	cin>>choi;
	if(choi[0]=='0')
		sex="女";
	if(choi[0]=='1')
		sex="男";
	totalSum=0;
	for(int i=0;i<subject_num;i++){
		cout<<"请输入"<<Student::subject_name[i]<<"成绩：";
		cin>>score[i];
		totalSum+=score[i];
	}
	averageScore=totalSum/subject_num;
}
void Student::Tablehead(){
	cout<<setw(10)<<"学号"<<setw(8)<<"姓名"<<setw(6)<<"性别";
	for(int i=0;i<subject_num;i++)
		cout<<setw(6)<<subject_name[i]<<' ';
	cout<<setw(8)<<"总分";
	cout<<setw(8)<<"平均分";
	cout<<endl;
	cout<<"=========================="<<endl;
}
void Student::Print(){
	cout<<setw(10)<<num;
	cout<<setw(8)<<name;
	cout<<setw(6)<<sex;
	for(int i=0;i<subject_num;i++)
		cout<<setw(6)<<score[i]<<' ';
	cout<<setw(8)<<totalSum<<' ';
	cout<<setw(8)<<averageScore<<endl;
	cout<<"-------------------------------"<<endl; 
}
#ifndef STUDENT_DEAL_H
#define STUDENT_DEAL_H
//#include"Student.h"
class StudentDeal{
	NodeType*head;
	public:
	StudentDeal();
	virtual ~StudentDeal();
	int getNodeCount();
	NodeType*Create();
	NodeType*GetLink();
	NodeType*Add();
	virtual void Del();
	virtual int Search();
	virtual void Modify();
	virtual int Sort();
	virtual void Save();
	virtual void Load();
	void swap_data(NodeType*a,NodeType*b);
	void Delay();
};
#endif
#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>
//#include"Student.h"
//#include"StudentDeal.h"
StudentDeal::StudentDeal(){head=NULL;}
NodeType*StudentDeal::GetLink(){return head;}
StudentDeal::~StudentDeal(){delete head;}
int StudentDeal::getNodeCount(){
	NodeType*current;
	current=head;
	int count=0;
	while(current){
		count++;
		current=current->next;
	}
	return count;
}
void StudentDeal::Save(){
	if(head==NULL){
		cout<<"记录为空，退出保存操作";
		return;
	}
	char filename[50];
	cout<<"请输入保存的文件名："<<endl;
	cin>>filename;
	ofstream fout;
	fout.open(filename,ios::app);
	if(fout.fail()){
		cout<<"打不开文件！"<<endl;
		return ;
	}
	NodeType*p;
	p=head;
	for(;p!=NULL;p=p->next){
		fout<<p->data.num<<endl;
		fout<<p->data.name<<endl;
		fout<<p->data.sex<<endl;
		for(int i=0;i<subject_num;i++)
			fout<<p->data.score[i]<<endl;
		fout<<p->data.totalSum<<endl;
		fout<<p->data.averageScore<<endl;
	}
	cout<<"正在保存，请稍等";
	Delay();
	cout<<"文件"<<filename<<"保存成功！"<<endl;
}
void StudentDeal::Load(){
	ifstream fin;
	char filename[50];
	NodeType*p1,*p2;
	int count=0;
	cout<<"请输入要读取的文件名.";
	cout<<"（测试文件为test.txt）"<<endl;
	cout<<endl;
	cin>>filename;
	fin.open(filename);
	if(fin.fail()){
		cout<<"找不到文件！请重试！"<<endl;
		return;
	}
	if(fin.peek()==EOF){
		cout<<"记录为空！";
		cout<<endl;
		fin.close();
		return; 
	}
	while(!fin.eof()){
		float s=0;
		p1=new NodeType;
		p1->data.num="";
		p1->next=NULL;
		fin>>p1->data.num>>p1->data.name>>p1->data.sex;
		for(int i=0;i<subject_num;i++){
			fin>>p1->data.score[i];
			s=s+p1->data.score[i];
		}
		fin>>p1->data.totalSum;
		fin>>p1->data.averageScore;
		p1->data.totalSum=s;
		p1->data.averageScore=s/5.0;
		if(p1->data.num==""){
			delete p1;
			fin.close();
			break;
		}
		count++;
		if(count==1)
			head=p1,p2=p1;
		else
			p2->next=p1,p2=p1;
	}
	fin.close();
	cout<<"\n正在读取";
	Delay();
	cout<<endl;
	cout<<"现在一共有"<<count<<"条记录"<<endl;
}
NodeType*StudentDeal::Create(){
	NodeType*p1,*p2;
	int count=0;
	float sum=0;
	char choi[5];
	if(getNodeCount()==0){
		cout<<"目前没有记录.确定要添加新纪录吗？(y/n)"<<endl;
		cin>>choi;
		if(choi[0]=='n'||choi[0]=='N')
			return 0;
	}
	else{
		cout<<"确定要覆盖当前记录中的内容吗？(y/n)"<<endl;
		cin>>choi;
		if(choi[0]=='n'||choi[0]=='N')
			return 0;
		else{
			cout<<"目前记录为空，请添加.\n\n";
			cout<<endl;
		}
	}
	p1=p2=new NodeType;
	p1->data.Input();
	do{
		count++;
		if(count==1)
			head=p1;
		else
			p2->next=p1,p2=p1;
		cout<<"继续添加一组信息，确定吗？(y/n)"<<endl;
		cin>>choi;
		if(choi[0]=='n'||choi[0]=='N')
			break;
		p1=new NodeType;
		p1->data.Input();
	}while(choi[0]!='n'&&choi[0]!='N');
	p2->next=NULL;
	cout<<"正在添加";
	Delay();
	cout<<"共新增了"<<count<<"条信息\n"<<endl;
	cout<<"目前共有"<<getNodeCount()<<"条信息."<<endl;
	return head; 
}
NodeType*StudentDeal::Add(){
	char choi[5];
	int cnt=getNodeCount();
	int count=0;
	if(cnt==0){
		cout<<"原来没有记录，现在建立新表.";
		cout<<endl;
		cout<<"您将要添加一组信息.";
		cout<<endl<<"——"<<endl;
		Create();
	}
	else{
		cout<<"下面在当前记录的末尾追加新信息."<<endl;
		cout<<endl;
		cout<<"您将要添加一组信息，确定吗？(y/n)";
		cin>>choi;
		if((choi[0]=='n')||(choi[0]=='N'))
			return 0;
		NodeType*newRec,*tmp;
		newRec=new NodeType;
		tmp=head;
		while(tmp->next!=NULL)
			tmp=tmp->next;
		newRec->data.Input();
		newRec->next=NULL;
		tmp->next=newRec;
		count++;
		cout<<endl;
		cout<<"新增"<<count<<"条信息."<<endl;
		cout<<"目前共有"<<getNodeCount()<<"条信息."<<endl;
	}
	return head;
}
int StudentDeal::Search(){
	if(head==NULL){
		cout<<"记录为空，退出查询";
		return 0;
	}
	int cnt=0;
	NodeType*current;
	current=head;
	string number;
	string stuName;
	char choi[5];
	cout<<"请输入查询的方法：（直接输入回车则结束查询）\n"<<"1.按学号\n"<<"2.按姓名\n";
	cin>>choi;
	if(choi[0]=='\0')
		return 0;
	if(choi[0]=='1'){
		cin>>number;
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		while(current){
			cnt++;
			if(current->data.num==number){
				cout<<"下面是您查询的结果."<<endl;
				cout<<endl;
				cout<<"学号 "<<current->data.num<<endl;
				cout<<"姓名 "<<current->data.name<<endl;
				cout<<"性别 "<<current->data.sex<<endl;
				for(int i=0;i<subject_num;i++)
					cout<<current->data.subject_name[i]<<' '<<current->data.score[i]<<endl;
				cout<<"总分 "<<current->data.totalSum<<endl;
				cout<<"平均分 "<<current->data.averageScore<<endl;
				cout<<endl;
				return cnt;
			}
			current=current->next;
		}
		cout<<"未找到关于"<<number<<"的记录"<<endl;
		cout<<endl; 
	}
	if(choi[0]=='2'){
		cout<<"请输入欲查询学生的姓名：";
		cin>>stuName;
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		while(current){
			cnt++;
			if(current->data.name==stuName){
				cout<<"下面是您查询的结果."<<endl;
				cout<<"下面是您查询的结果."<<endl;
				cout<<endl;
				cout<<"学号 "<<current->data.num<<endl;
				cout<<"姓名 "<<current->data.name<<endl;
				cout<<"性别 "<<current->data.sex<<endl;
				for(int i=0;i<subject_num;i++)
					cout<<current->data.subject_name[i]<<' '<<current->data.score[i]<<endl;
				cout<<"总分 "<<current->data.totalSum<<endl;
				cout<<"平均分 "<<current->data.averageScore<<endl;
				cout<<endl;
				return cnt;
			}
		}
		cout<<"未找到关于"<<stuName<<"的记录！"<<endl; 
	}
	return 0;
}
void StudentDeal::Del(){
	NodeType*p1,*p2;
	p1=head;
	string number;
	string Name;
	char choi[5];
	int cnt=getNodeCount();
	if(head==NULL){
		cout<<"记录为空，退出删除操作";
		return;
	}
	cout<<"请输入删除的方式：（直接输入回车则结束删除）\n"<<"1.按学号\n"<<"2.按姓名\n";
	cin>>choi;
	if(choi[0]=='\0')
		return;
	if(choi[0]=='1'){
		cout<<"请输入学号：";
		cin>>number;
		cout<<endl;
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		while(number!=p1->data.num&&p1->next!=NULL)
			p2=p1,p1=p1->next;
		if(number==p1->data.num){
			if(p1==head){
				head=p1->next;
				delete p1;
			}
			else{
				p2->next=p1->next;
				delete p1;
			}
			cnt--;
			cout<<"关于"<<number<<"的记录已经删除！"<<endl;
			cout<<endl;
			cout<<"还剩"<<cnt<<"条记录！"<<endl; 
		}
		else
			cout<<"未找到关于"<<number<<"的记录."<<endl;
	}
	if(choi[0]=='2'){
		cout<<"请输入要删除的姓名：";
		cin>>Name;
		cout<<endl;
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		while(Name!=p1->data.name&&p1->next!=NULL)
			p2=p1,p1=p1->next;
		if(Name==p1->data.name){
			if(p1==head){
				head=p1->next;
				delete p1;
			}
			else{
				p2->next=p1->next;
				delete p1;
			}
			cnt--;
			cout<<"关于"<<Name<<"的记录已经删除！"<<endl;
			cout<<endl;
			cout<<"还剩"<<cnt<<"条记录！"<<endl;
		}
		else
			cout<<"未找到关于"<<Name<<"的记录."<<endl;
	}
}
void StudentDeal::Modify(){
	NodeType*p1;
	float sum=0;
	p1=head;
	string number;
	string stuName;
	char choi[5];
	if(head==NULL){
		cout<<"记录为空，退出修改操作";
		return;
	}
	cout<<"请输入修改方式（直接输入回车则结束修改）\n"<<"1.按学号\n"<<"2.按姓名\n";
	cin>>choi;
	if(choi[0]=='\0')
		return;
	if(choi[0]=='1'){
		cout<<"请输入要修改学生的学号:";
		cin>>number;
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		while(p1)
			if(p1->data.num==number)
				break;
			else if(p1->data.num!=number)
				p1=p1->next;
		if(p1->data.num==number){
			cout<<"匹配记录如下>>>>>"<<endl;
			cout<<endl;
			cout<<"下面是您查询的结果."<<endl;
			cout<<endl;
			p1->data.Print();
			cout<<"请按照一下的修改格式修改："<<endl;
			p1->data.Input();
			cout<<endl;
			cout<<"修改成功！";
			cout<<"目前共有"<<getNodeCount()<<"条记录."<<endl; 
		}
		else{
			cout<<endl;
			cout<<"没有找到与"<<number<<"匹配的记录."<<endl;
		}
	}
	if(choi[0]=='2'){
		cout<<"请输入要修改学生的姓名：";
		cin>>stuName;
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		while(p1)
			if(p1->data.name==stuName)
				break;
			else if(p1->data.name!=stuName)
				p1=p1->next;
		if(p1->data.num==number){
			cout<<"匹配记录如下>>>>>"<<endl;
			cout<<endl;
			cout<<"下面是您查询的结果."<<endl;
			cout<<endl;
			p1->data.Print();
			cout<<"请按照一下的修改格式修改："<<endl;
			p1->data.Input();
			cout<<endl;
			cout<<"修改成功！";
			cout<<"目前共有"<<getNodeCount()<<"条记录."<<endl; 
		}
		else{
			cout<<endl;
			cout<<"没有找到与"<<stuName<<"匹配的记录."<<endl;
		}
	}
}
void StudentDeal::swap_data(NodeType*a,NodeType*b){
	string stuName;
	stuName=a->data.name;
	a->data.name=b->data.name;
	b->data.name=stuName;
	string stuNum;
	stuNum=a->data.num;
	a->data.num=b->data.num;
	b->data.num=stuNum;
	string stuSex;
	stuSex=a->data.sex;
	a->data.sex=b->data.sex;
	b->data.sex=stuSex;
	float stuScore;
	for(int i=0;i<subject_num;i++){
		stuScore=a->data.score[i];
		a->data.score[i]=b->data.score[i];
		b->data.score[i]=stuScore;
	}
	float stuSum;
	stuSum=a->data.totalSum;
	a->data.totalSum=b->data.totalSum;
	b->data.totalSum=stuSum;
	float stuAverage;
	stuAverage=a->data.averageScore;
	a->data.averageScore=b->data.averageScore;
	b->data.averageScore=stuAverage;
}
int StudentDeal::Sort(){
	int cnt=getNodeCount();
	NodeType*p,*q;
	int numStus=cnt;
	string str;
	if(head==NULL){
		cout<<"记录为空，退出排序操作";
		return 0;
	}
	cout<<"请输入您希望进行排序的方式：\n"<<"1.按学号从小到大\n"<<"2.按学号从大到小\n"<<"3.按总成绩从小到大\n"<<"4.按总成绩从大到小\n"<<"5.按平均分从小到大\n"<<"6.按平均分从大到小\n"<<"7.按错了，我不想排序\n";
	cin>>str;
	if(str[0]<'1'||str[0]>'6')
		return 0;
	else
		switch(str[0]){
			case '1' : 
				
				for(p=head;p->next!=NULL;p=p->next)
					for(q=p->next;q!=NULL;q=q->next)
						if(p->data.num>q->data.num)
							swap_data(p,q);
				/*
				NodeType*tempMax;
				for(p=head;p->next!=NULL;p=p->next){
					tempMax=p;
					for(q=p->next;q!=NULL;q=q->next)
						if(tempMax->data.num>p->data.num)
							tempMax=q;
					if(p!=tempMax)
						swap_data(p,tempMax);
				}
				*/
				break;
			case '2' : 
				for(p=head;p->next!=NULL;p=p->next)
					for(q=p->next;q!=NULL;q=q->next)
						if(p->data.num<q->data.num)
							swap_data(p,q);
				/*
				NodeType*tempMax;
				for(p=head;p->next!=NULL;p=p->next){
					tempMax=p;
					for(q=p->next;q!=NULL;q=q->next)
						if(tempMax->data.num<q->data.num)
							tempMax=q;
					if(p!=tempMax)
						swap_data(p,tempMax);
				}
				*/
				break;
			case '3' : 
				for(p=head;p->next!=NULL;p=p->next)
					for(q=p->next;q!=NULL;q=q->next)
						if(p->data.totalSum>q->data.totalSum)
							swap_data(q,p);
				/*
				NodeType*tempMax;
				for(p=head;p->next!=NULL;p=p->next){
					tempMax=p;
					for(q=p->next;q!=NULL;q=q->next)
						if(tempMax->data.totalSum>q->data.totalSum)
							tempMax=q;
					if(p!=tempMax)
						swap_data(p,tempMax);
				}
				*/
				break;
			case '4' : 
				for(p=head;p->next!=NULL;p=p->next)
					for(q=p->next;q!=NULL;q=q->next)
						if(p->data.totalSum<q->data.totalSum)
							swap_data(q,p);
				/*
				NodeType*tempMax;
				for(p=head;p->next!=NULL;p=p->next){
					tempMax=p;
					for(q=p->next;q!=NULL;q=q->next)
						if(tempMax->data.totalSum<q->data.totalSum)
							tempMax=q;
					if(p!=tempMax)
						swap_data(p,tempMax);
				}
				*/
				break;
			case '5' :
				for(p=head;p->next!=NULL;p=p->next)
					for(q=p->next;q!=NULL;q=q->next)
						if(p->data.averageScore>q->data.averageScore)
							swap_data(p,q);
				/*
				NodeType*tempMax;
				for(p=head;p->next!=NULL;p=p->next){
					tempMax=p;
					for(q=p->next;q!=NULL;q=q->next)
						if(tempMax->data.data.averageSum>q->data.data.averageSum)
							tempMax=q;
					if(p!=tempMax)
						swap_data(p,tempMax);
				}
				*/
				break;
			case '6' : 
				for(p=head;p->next!=NULL;p=p->next)
					for(q=p->next;q!=NULL;q=q->next)
						if(p->data.averageScore<q->data.averageScore)
							swap_data(p,q);
				/*
				NodeType*tempMax;
				for(p=head;p->next!=NULL;p=p->next){
					tempMax=p;
					for(q=p->next;q!=NULL;q=q->next)
						if(tempMax->data.data.averageSum<q->data.data.averageSum)
							tempMax=q;
					if(p!=tempMax)
						swap_data(p,tempMax);
				}
				*/
				break;
			default:;
		}
		cout<<"正在排序";
		Delay();
		cout<<endl;
		cout<<"排序已经完成！"<<endl;
		return 0;
}
void StudentDeal::Delay(){
	for(int i=0;i<5;i++){
		cout<<'.';
		Sleep(250);
	}
	cout<<endl;
}
#ifndef STUDENT_INTER_FACE_H
#define STUDENT_INTER_FACE_H
//#include"Student.h"
class StudentInterface:public StudentDeal{
	public:
		void inputInfo();
		void outputInfo();
		public:
			char MenuSelect();
			void Start();
			void MenuDeal();
}stulnterface;
#endif
#include<iostream>
#include<string>
#include<windows.h>
#include<iomanip>
//#include"Student.h"
//#include"StudentDeal.h"
//#include"StudentInterface.h"
using namespace std;
void StudentInterface::Start(){
	cout<<'\n'<<"\t\t***************************\n"<<"\t\t*这是一个*\n"<<"\t\t*学生成绩管理程序*\n"<<"\t\t*可以对学生成绩进行管理*\n"<<"\t\t*欢迎使用管理程序*\n"<<"\t\t***************************\n"<<"\n";
}
char StudentInterface::MenuSelect(){
	cout<<endl<<"\t###############################################\n"<<"\t1.显示记录\n"<<"\t2.查询记录\n"<<"\t3.增加记录\n"<<"\t4.删除记录\n"<<"\t5.修改记录\n"<<"\t6.记录排序\n"<<"\t7.保存记录\n"<<"\t8.读取文件\n"<<"\t9.新建学生系统\n"<<"\t0.退出系统\n"<<"\t###############################################\n"<<"\t左边数字对应功能选择，请选择0~9:";
	string str;
	char choice;
	while(true){
		cin>>str;
		cin.ignore();
		choice=str[0];
		if(choice<'0'||choice>'9'){
			cout<<"\n输入错误，请重选";
			continue;
		}
		else{
			cout<<endl;
			break;
		}
	}
	return choice;
}
void StudentInterface::MenuDeal(){
	char menuItem;
	bool flag=true;
	while(flag){
		//system("color 0A");
		switch(MenuSelect()){
			case '1' : 
				outputInfo();
				break;
			
			case '2' : 
				Search();
				break;
			
			case '3' : 
				inputInfo();
				break;
			
			case '4' : 
				Del();
				break;
			
			case '5' : 
				Modify();
				break;
			
			case '6' : 
				Sort();
				break;
			
			case '7' : 
				Save();
				break;
			
			case '8' : 
				Load();
				break;
			
			case '9' : 
				Create();
				break;
			
			case '0' : 
				flag=false;
				system("cls");
				cout<<endl<<endl;
				cout<<"感谢使用！系统即将关闭";
				Delay();
				cout<<endl;
				break;
			
		}
	}
}
void StudentInterface::outputInfo(){
	NodeType*p;
	p=GetLink();
	if(p==NULL){
		cout<<"没有记录，请添加！"<<endl;
		return;
	}
	else{
		cout<<"正在查询，请稍等";
		Delay();
		cout<<endl;
		p->data.Tablehead();
		do{
			p->data.Print();
			p=p->next;
			cout<<endl;
		}while(p!=NULL);
	}
	cout<<"共有记录"<<getNodeCount()<<"条."<<endl;
}
void StudentInterface::inputInfo(){
	Add();
}
int main(){
	stulnterface.Start();
	stulnterface.MenuDeal();
	return 0;
}
