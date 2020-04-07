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
char*Student::subject_name[]={"����","��ѧ","Ӣ��","��ѧ","��Ϣ����"};
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
	cout<<"������ѧ�ţ�";
	cin>>num;
	cout<<"������������";
	cin>>name;
	cout<<"�������Ա�0��Ů��1���У�";
	cin>>choi;
	if(choi[0]=='0')
		sex="Ů";
	if(choi[0]=='1')
		sex="��";
	totalSum=0;
	for(int i=0;i<subject_num;i++){
		cout<<"������"<<Student::subject_name[i]<<"�ɼ���";
		cin>>score[i];
		totalSum+=score[i];
	}
	averageScore=totalSum/subject_num;
}
void Student::Tablehead(){
	cout<<setw(10)<<"ѧ��"<<setw(8)<<"����"<<setw(6)<<"�Ա�";
	for(int i=0;i<subject_num;i++)
		cout<<setw(6)<<subject_name[i]<<' ';
	cout<<setw(8)<<"�ܷ�";
	cout<<setw(8)<<"ƽ����";
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
		cout<<"��¼Ϊ�գ��˳��������";
		return;
	}
	char filename[50];
	cout<<"�����뱣����ļ�����"<<endl;
	cin>>filename;
	ofstream fout;
	fout.open(filename,ios::app);
	if(fout.fail()){
		cout<<"�򲻿��ļ���"<<endl;
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
	cout<<"���ڱ��棬���Ե�";
	Delay();
	cout<<"�ļ�"<<filename<<"����ɹ���"<<endl;
}
void StudentDeal::Load(){
	ifstream fin;
	char filename[50];
	NodeType*p1,*p2;
	int count=0;
	cout<<"������Ҫ��ȡ���ļ���.";
	cout<<"�������ļ�Ϊtest.txt��"<<endl;
	cout<<endl;
	cin>>filename;
	fin.open(filename);
	if(fin.fail()){
		cout<<"�Ҳ����ļ��������ԣ�"<<endl;
		return;
	}
	if(fin.peek()==EOF){
		cout<<"��¼Ϊ�գ�";
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
	cout<<"\n���ڶ�ȡ";
	Delay();
	cout<<endl;
	cout<<"����һ����"<<count<<"����¼"<<endl;
}
NodeType*StudentDeal::Create(){
	NodeType*p1,*p2;
	int count=0;
	float sum=0;
	char choi[5];
	if(getNodeCount()==0){
		cout<<"Ŀǰû�м�¼.ȷ��Ҫ����¼�¼��(y/n)"<<endl;
		cin>>choi;
		if(choi[0]=='n'||choi[0]=='N')
			return 0;
	}
	else{
		cout<<"ȷ��Ҫ���ǵ�ǰ��¼�е�������(y/n)"<<endl;
		cin>>choi;
		if(choi[0]=='n'||choi[0]=='N')
			return 0;
		else{
			cout<<"Ŀǰ��¼Ϊ�գ������.\n\n";
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
		cout<<"�������һ����Ϣ��ȷ����(y/n)"<<endl;
		cin>>choi;
		if(choi[0]=='n'||choi[0]=='N')
			break;
		p1=new NodeType;
		p1->data.Input();
	}while(choi[0]!='n'&&choi[0]!='N');
	p2->next=NULL;
	cout<<"�������";
	Delay();
	cout<<"��������"<<count<<"����Ϣ\n"<<endl;
	cout<<"Ŀǰ����"<<getNodeCount()<<"����Ϣ."<<endl;
	return head; 
}
NodeType*StudentDeal::Add(){
	char choi[5];
	int cnt=getNodeCount();
	int count=0;
	if(cnt==0){
		cout<<"ԭ��û�м�¼�����ڽ����±�.";
		cout<<endl;
		cout<<"����Ҫ���һ����Ϣ.";
		cout<<endl<<"����"<<endl;
		Create();
	}
	else{
		cout<<"�����ڵ�ǰ��¼��ĩβ׷������Ϣ."<<endl;
		cout<<endl;
		cout<<"����Ҫ���һ����Ϣ��ȷ����(y/n)";
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
		cout<<"����"<<count<<"����Ϣ."<<endl;
		cout<<"Ŀǰ����"<<getNodeCount()<<"����Ϣ."<<endl;
	}
	return head;
}
int StudentDeal::Search(){
	if(head==NULL){
		cout<<"��¼Ϊ�գ��˳���ѯ";
		return 0;
	}
	int cnt=0;
	NodeType*current;
	current=head;
	string number;
	string stuName;
	char choi[5];
	cout<<"�������ѯ�ķ�������ֱ������س��������ѯ��\n"<<"1.��ѧ��\n"<<"2.������\n";
	cin>>choi;
	if(choi[0]=='\0')
		return 0;
	if(choi[0]=='1'){
		cin>>number;
		cout<<"���ڲ�ѯ�����Ե�";
		Delay();
		cout<<endl;
		while(current){
			cnt++;
			if(current->data.num==number){
				cout<<"����������ѯ�Ľ��."<<endl;
				cout<<endl;
				cout<<"ѧ�� "<<current->data.num<<endl;
				cout<<"���� "<<current->data.name<<endl;
				cout<<"�Ա� "<<current->data.sex<<endl;
				for(int i=0;i<subject_num;i++)
					cout<<current->data.subject_name[i]<<' '<<current->data.score[i]<<endl;
				cout<<"�ܷ� "<<current->data.totalSum<<endl;
				cout<<"ƽ���� "<<current->data.averageScore<<endl;
				cout<<endl;
				return cnt;
			}
			current=current->next;
		}
		cout<<"δ�ҵ�����"<<number<<"�ļ�¼"<<endl;
		cout<<endl; 
	}
	if(choi[0]=='2'){
		cout<<"����������ѯѧ����������";
		cin>>stuName;
		cout<<"���ڲ�ѯ�����Ե�";
		Delay();
		cout<<endl;
		while(current){
			cnt++;
			if(current->data.name==stuName){
				cout<<"����������ѯ�Ľ��."<<endl;
				cout<<"����������ѯ�Ľ��."<<endl;
				cout<<endl;
				cout<<"ѧ�� "<<current->data.num<<endl;
				cout<<"���� "<<current->data.name<<endl;
				cout<<"�Ա� "<<current->data.sex<<endl;
				for(int i=0;i<subject_num;i++)
					cout<<current->data.subject_name[i]<<' '<<current->data.score[i]<<endl;
				cout<<"�ܷ� "<<current->data.totalSum<<endl;
				cout<<"ƽ���� "<<current->data.averageScore<<endl;
				cout<<endl;
				return cnt;
			}
		}
		cout<<"δ�ҵ�����"<<stuName<<"�ļ�¼��"<<endl; 
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
		cout<<"��¼Ϊ�գ��˳�ɾ������";
		return;
	}
	cout<<"������ɾ���ķ�ʽ����ֱ������س������ɾ����\n"<<"1.��ѧ��\n"<<"2.������\n";
	cin>>choi;
	if(choi[0]=='\0')
		return;
	if(choi[0]=='1'){
		cout<<"������ѧ�ţ�";
		cin>>number;
		cout<<endl;
		cout<<"���ڲ�ѯ�����Ե�";
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
			cout<<"����"<<number<<"�ļ�¼�Ѿ�ɾ����"<<endl;
			cout<<endl;
			cout<<"��ʣ"<<cnt<<"����¼��"<<endl; 
		}
		else
			cout<<"δ�ҵ�����"<<number<<"�ļ�¼."<<endl;
	}
	if(choi[0]=='2'){
		cout<<"������Ҫɾ����������";
		cin>>Name;
		cout<<endl;
		cout<<"���ڲ�ѯ�����Ե�";
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
			cout<<"����"<<Name<<"�ļ�¼�Ѿ�ɾ����"<<endl;
			cout<<endl;
			cout<<"��ʣ"<<cnt<<"����¼��"<<endl;
		}
		else
			cout<<"δ�ҵ�����"<<Name<<"�ļ�¼."<<endl;
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
		cout<<"��¼Ϊ�գ��˳��޸Ĳ���";
		return;
	}
	cout<<"�������޸ķ�ʽ��ֱ������س�������޸ģ�\n"<<"1.��ѧ��\n"<<"2.������\n";
	cin>>choi;
	if(choi[0]=='\0')
		return;
	if(choi[0]=='1'){
		cout<<"������Ҫ�޸�ѧ����ѧ��:";
		cin>>number;
		cout<<"���ڲ�ѯ�����Ե�";
		Delay();
		cout<<endl;
		while(p1)
			if(p1->data.num==number)
				break;
			else if(p1->data.num!=number)
				p1=p1->next;
		if(p1->data.num==number){
			cout<<"ƥ���¼����>>>>>"<<endl;
			cout<<endl;
			cout<<"����������ѯ�Ľ��."<<endl;
			cout<<endl;
			p1->data.Print();
			cout<<"�밴��һ�µ��޸ĸ�ʽ�޸ģ�"<<endl;
			p1->data.Input();
			cout<<endl;
			cout<<"�޸ĳɹ���";
			cout<<"Ŀǰ����"<<getNodeCount()<<"����¼."<<endl; 
		}
		else{
			cout<<endl;
			cout<<"û���ҵ���"<<number<<"ƥ��ļ�¼."<<endl;
		}
	}
	if(choi[0]=='2'){
		cout<<"������Ҫ�޸�ѧ����������";
		cin>>stuName;
		cout<<"���ڲ�ѯ�����Ե�";
		Delay();
		cout<<endl;
		while(p1)
			if(p1->data.name==stuName)
				break;
			else if(p1->data.name!=stuName)
				p1=p1->next;
		if(p1->data.num==number){
			cout<<"ƥ���¼����>>>>>"<<endl;
			cout<<endl;
			cout<<"����������ѯ�Ľ��."<<endl;
			cout<<endl;
			p1->data.Print();
			cout<<"�밴��һ�µ��޸ĸ�ʽ�޸ģ�"<<endl;
			p1->data.Input();
			cout<<endl;
			cout<<"�޸ĳɹ���";
			cout<<"Ŀǰ����"<<getNodeCount()<<"����¼."<<endl; 
		}
		else{
			cout<<endl;
			cout<<"û���ҵ���"<<stuName<<"ƥ��ļ�¼."<<endl;
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
		cout<<"��¼Ϊ�գ��˳��������";
		return 0;
	}
	cout<<"��������ϣ����������ķ�ʽ��\n"<<"1.��ѧ�Ŵ�С����\n"<<"2.��ѧ�ŴӴ�С\n"<<"3.���ܳɼ���С����\n"<<"4.���ܳɼ��Ӵ�С\n"<<"5.��ƽ���ִ�С����\n"<<"6.��ƽ���ִӴ�С\n"<<"7.�����ˣ��Ҳ�������\n";
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
		cout<<"��������";
		Delay();
		cout<<endl;
		cout<<"�����Ѿ���ɣ�"<<endl;
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
	cout<<'\n'<<"\t\t***************************\n"<<"\t\t*����һ��*\n"<<"\t\t*ѧ���ɼ��������*\n"<<"\t\t*���Զ�ѧ���ɼ����й���*\n"<<"\t\t*��ӭʹ�ù������*\n"<<"\t\t***************************\n"<<"\n";
}
char StudentInterface::MenuSelect(){
	cout<<endl<<"\t###############################################\n"<<"\t1.��ʾ��¼\n"<<"\t2.��ѯ��¼\n"<<"\t3.���Ӽ�¼\n"<<"\t4.ɾ����¼\n"<<"\t5.�޸ļ�¼\n"<<"\t6.��¼����\n"<<"\t7.�����¼\n"<<"\t8.��ȡ�ļ�\n"<<"\t9.�½�ѧ��ϵͳ\n"<<"\t0.�˳�ϵͳ\n"<<"\t###############################################\n"<<"\t������ֶ�Ӧ����ѡ����ѡ��0~9:";
	string str;
	char choice;
	while(true){
		cin>>str;
		cin.ignore();
		choice=str[0];
		if(choice<'0'||choice>'9'){
			cout<<"\n�����������ѡ";
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
				cout<<"��лʹ�ã�ϵͳ�����ر�";
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
		cout<<"û�м�¼������ӣ�"<<endl;
		return;
	}
	else{
		cout<<"���ڲ�ѯ�����Ե�";
		Delay();
		cout<<endl;
		p->data.Tablehead();
		do{
			p->data.Print();
			p=p->next;
			cout<<endl;
		}while(p!=NULL);
	}
	cout<<"���м�¼"<<getNodeCount()<<"��."<<endl;
}
void StudentInterface::inputInfo(){
	Add();
}
int main(){
	stulnterface.Start();
	stulnterface.MenuDeal();
	return 0;
}
