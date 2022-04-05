#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

fstream in,out;

class dt
{
	private:
		int day;
		int month;
		int year;
		int hour;
	public:
		dt(int day=0,int month=0,int year=0,int hour=0)
		{this->day=day; this->month=month; this->year=year; this->hour=hour;}
		void setdt(int day,int month,int year,int hour)
		{this->day=day; this->month=month; this->year=year; this->hour=hour;}
		void setd(int day,int month,int year)
		{this->day=day; this->month=month; this->year=year;}
		int getDay()
		{return day;}
		int getMonth()
		{return month;}
		int getYear()
		{return year;}
		int getHour()
		{return hour;}
};

class booking
{
	private:
		int type;
		dt from, to;
		int price;
		
	public:
		booking() {}
		booking(int type,dt from, dt to)
		{this->type=type; this->from=from; this->to=to;}
		int getType()
		{return type;}
		int getPrice();
		int getDayfr()
		{return from.getDay();}
		int getMonthfr()
		{return from.getMonth();}
		int getYearfr()
		{return from.getYear();}
		int getHourfr()
		{return from.getHour();}
		int getHourT()
		{return to.getHour();}
		void printDnT();
};

void booking::printDnT()
{
	if(from.getHour()<10 && to.getHour()<10)
		cout<<"0"<<from.getHour()<<":00 - 0"<<to.getHour()<<":00";
	else if(from.getHour()<10 && to.getHour()>=10)
		cout<<"0"<<from.getHour()<<":00 - "<<to.getHour()<<":00";
	else if(from.getHour()>=10 && to.getHour()<10)
		cout<<from.getHour()<<":00 - 0"<<to.getHour()<<":00";
	else if(from.getHour()>=10 && to.getHour()>=10)
		cout<<from.getHour()<<":00 - "<<to.getHour()<<":00";
		
	cout<<"    "<<from.getDay()<<"-"<<from.getMonth()<<"-"<<from.getYear();
}

int booking::getPrice()
{
	int dur= to.getHour()-from.getHour();
	
	if(type==1)
	{
		price= 100*dur;
	}
	else if(type==2)
	{
		price=150*dur;
	}
	else if(type==3)
	{
		price=200*dur;
	}
	
	return price;
}

struct node;

class customer
{
	private:
		string name;
		string institution;
		booking *pesan;
	
	public:
		customer(){}
		customer(string name,string institution,booking *p)
		{this->name=name;this->institution=institution; pesan=p;}
		void input();
		void removeBook()
		{delete pesan; pesan=NULL;}
		string getName()
		{return name;}
		string getInstitution()
		{return institution;}
		void print();
		friend node* SortedMerge(node* a, node* b);
		friend void save(node *pri);
		friend void search(node* heaad);
		friend void searchTillHour(node* &hed, node* &til);
};

struct node{
	customer *data;
	node *next= NULL;
};

void customer::input()
{
	int a,b,c,d,e;
	int tipe;
	dt temp1, temp2;
	char confirm[1];
	
	cin.ignore();
	cout<<"Please enter your name: ";
	getline(cin, name);
	cout<<"Please enter your institution (type NONE if there no institution):  ";
	getline(cin, institution);

	cout<<"What type of meeting room do you want to book?\n";
	cout<<"1. Small\n";
	cout<<"2. Medium\n";
	cout<<"3. Large\n\n";
	cin>>tipe;
	cout<<"\nWhen will you use the meeting room? \n";
	cout<<"Date  : ";
	cin>>a;
	cout<<"Month : ";
	cin>>b;
	cout<<"Year  : ";
	cin>>c;
	cout<<"Time only available per hour\n";
	cout<<"From  : ";
	cin>>d;
	cout<<"To    : ";
	cin>>e;
	temp1.setdt(a,b,c,d);
	temp2.setdt(a,b,c,e);
		
	pesan= new booking(tipe,temp1,temp2);
		
	cout<<"\n\nThe cost will be "<<pesan->getPrice()<<endl;
	cout<<"Continue the booking? [Y/N]\n";
	cin>>confirm;
	cout<<"\n\n";
	if(confirm=="N")
		removeBook();

}

void customer::print()
{
	int t;
	
	cout<<"Name         : "<<name<<endl;
	cout<<"Institution  : "<<institution<<endl;
	cout<<"Type         : ";
	t= pesan->getType();
	if(t==1)
	{
		cout<<"Small\n";
	}
	else if(t==2)
	{
		cout<<"Medium\n";
	}
	else if(t==3)
	{
		cout<<"Large\n";
	}
	cout<<"Date/Time    : ";
	pesan->printDnT();
	cout<<endl<<endl;
}

node* SortedMerge(node* a, node* b); 
void FrontBackSplit(node* source, node** last, node** mid); 
  
void MergeSort(node** headRef) 
{ 
    node* head = *headRef; 
    node* a; 
    node* b; 
  
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    FrontBackSplit(head, &a, &b); 
  
    MergeSort(&a); 
    MergeSort(&b); 
  
    *headRef = SortedMerge(a, b); 
} 
  
node* SortedMerge(node* a, node* b) 
{ 
    node* fin = NULL; 
  
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    if (a->data->pesan->getYearfr() < b->data->pesan->getYearfr()) { 
        fin = a; 
        fin->next = SortedMerge(a->next, b); 
    } 
    else if (a->data->pesan->getYearfr() == b->data->pesan->getYearfr() && a->data->pesan->getMonthfr() < b->data->pesan->getMonthfr()) { 
        fin = a; 
        fin->next = SortedMerge(a->next, b); 
    }
    else if (a->data->pesan->getYearfr() == b->data->pesan->getYearfr() && a->data->pesan->getMonthfr() == b->data->pesan->getMonthfr() && a->data->pesan->getDayfr() < b->data->pesan->getDayfr()) { 
        fin = a; 
        fin->next = SortedMerge(a->next, b); 
    }
    else if (a->data->pesan->getYearfr() == b->data->pesan->getYearfr() && a->data->pesan->getMonthfr() == b->data->pesan->getMonthfr() && a->data->pesan->getDayfr() == b->data->pesan->getDayfr() && a->data->pesan->getHourfr() < b->data->pesan->getHourfr()) { 
        fin = a; 
        fin->next = SortedMerge(a->next, b); 
    }
    else { 
        fin = b; 
        fin->next = SortedMerge(a, b->next); 
    } 
    return (fin); 
} 
  
void FrontBackSplit(node* source, node** last, node** mid) 
{ 
    node* fast; 
    node* slow; 
    slow = source; 
    fast = source->next; 
  
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    *last = source; 
    *mid = slow->next; 
    slow->next = NULL; 
} 

void search(node * heaad)
{
	dt test;
	bool ch=false;
	int a,b,c;
	
	cout<<"Date  : ";
	cin>>a;
	cout<<"Month : ";
	cin>>b;
	cout<<"Year  : ";
	cin>>c;
	cout<<"\n\n";
	test.setd(a,b,c);
	
	node *t= heaad;
	
	while(t!=NULL)
	{
		if (t->data->pesan->getYearfr() == test.getYear() && t->data->pesan->getMonthfr() == test.getMonth() && t->data->pesan->getDayfr() == test.getDay())
  		{ 
			t->data->print();
			
			ch=true;
 	    }
        
        t=t->next;
	}
	
	if(!ch)
	{
		cout<<"No booking found\n\n";
	}
}

void searchTillHour(node * &hed, node* &til)
{
	dt test;
	int a,b,c,d;
	int t, position=0;
	bool check=false;
	string na, inst;
	string conf, conf2;
	
	cin.ignore();
	cout<<"Booked by: ";
	getline(cin,na);
	cout<<"Institution: ";
	getline(cin,inst);
	
	cout<<"Date  : ";
	cin>>a;
	cout<<"Month : ";
	cin>>b;
	cout<<"Year  : ";
	cin>>c;
	cout<<"Hour  : ";
	cin>>d;
	
	test.setdt(a,b,c,d);
	
	node *temp= hed;
	node *prev=NULL; 
	
	while(temp != NULL)
	{
		if (na==temp->data->getName() &&temp->data->getInstitution()==inst && temp->data->pesan->getYearfr() 
		== test.getYear() && temp->data->pesan->getMonthfr() == test.getMonth() && temp->data->pesan->getDayfr() ==
		 test.getDay() && temp->data->pesan->getHourfr()==test.getHour())
  		{ 
			temp->data->print();
			
			
			cout<<"Is this your booking? [if yes type Y]  ";
			cin>>conf2;
			if(conf2=="Y" || conf2=="y")
			{
				check=true;
				break;
			}
		}
		
		prev = temp; 	
        temp = temp->next;
	}
	
	if(check)
	{
		cout<<"Delete this booking [if yes type Y]?  ";
		cin>>conf;
		if((conf=="Y" || conf=="y") && temp==hed)
		{
			hed= temp->next;
			delete temp;
		}
		else if((conf=="Y" || conf=="y")&& temp != hed && temp != til)
		{
			prev->next= temp->next;
			delete temp;
		}
		else if((conf=="Y" || conf=="y")&& temp == til)
		{
			til=prev;
			til->next=NULL;
			delete temp;
		}
	}
	else
		cout<<"sorry, we cant find what you're looking for\n\n\n";
}

void save(node *pri)
{
	out.open("data.txt", ios::out);
	
   	while(pri)
    {
    	out<<endl;
		out<<pri->data->name<<endl;
		out<<pri->data->institution<<endl;
		out<<pri->data->pesan->getType()<<endl;
		out<<pri->data->pesan->getYearfr()<<endl;
		out<<pri->data->pesan->getMonthfr()<<endl;
		out<<pri->data->pesan->getDayfr()<<endl;
		out<<pri->data->pesan->getHourfr()<<endl;
		out<<pri->data->pesan->getHourT();
		
		pri=pri->next;
	}
}

void StaffMenu(node * &headd, node* &taill)
{
	in.open("data.txt", ios::in);
	int choice,ti;
	customer *semm;
	booking *pes;
	string name,institut,buff;
	dt tem1, tem2;
	int a,b,c,d,e;
	int te;
	bool tr;
	while(choice!=4)
	{
		cout<<"1. See the list of all booked meeting room\n";
		cout<<"2. Load data\n";
		cout<<"3. Delete a reservation\n";
		cout<<"4. Back\n\n";
		cout<<"Choice: ";
		cin>>choice;
		
		if(choice==1)
		{
			node *temp2=headd;
			while(temp2 != NULL)
			{
				cout<<"\n";
				temp2->data->print();
				temp2=temp2->next;
				tr= true;
			}
			
			if(!tr)
			{
				cout<<"There is no data";
			}
			cout<<"\n\n";
			system("pause");
			cout<<"\n\n";
		}
		else if(choice==2)
		{
			if(!in)
			{
				cout<<"There is no data, the program will be close\nThank you...."<<endl;
			}
			else
			{
				while(!in.eof())
				{
					getline(in,buff);
					getline(in,name);
					getline(in,institut);
					in>>te;
					in>>a;
					in>>b;
					in>>c;
					in>>d;
					in>>e;
					
					
					tem1.setdt(c,b,a,d);
					tem2.setdt(c,b,a,e);
					
					pes=new booking(te,tem1,tem2);
					semm=new customer(name,institut,pes);
					
					node*temp1= new node;
					temp1->data=semm;
					
					if(headd==NULL && taill==NULL)
					{
						headd= temp1;
						taill=temp1;
					}
					else
					{
						taill->next= temp1;
						taill=taill->next;
					}
				}
				MergeSort(&headd);
				save(headd);
			}
			
			
		}
		else if(choice==3)
		{
			searchTillHour(headd, taill);
			save(headd);
		}
		
	}
}

void CustomerMenu(node * &head, node * &tail)
{
	int c;
	customer *sem;
	
	while(c!=4)
	{
		cout<<"1. See the list of booked meeting room on a day\n";
		cout<<"2. Reserve a meeting room\n";
		cout<<"3. Delete a reservation\n";
		cout<<"4. Back\n\n";
		cout<<"Choice: ";
		cin>>c;
		
		if(c==1)
		{
			search(head);
		}
		else if(c==2)
		{
			sem= new customer;
			sem->input();
			
			node*temp1= new node;
			temp1->data=sem;
			
			if(head==NULL && tail==NULL)
			{
				head= temp1;
				tail=temp1;
			}
			else
			{
				tail->next= temp1;
				tail=tail->next;
			}	
			
			MergeSort(&head);
			save(head);
		}
		else if(c==3)
		{
			searchTillHour(head, tail);
			save(head);
		}
		
	}
	
	
	
}

int main()
{
	node *hea=NULL, *tal=NULL;
	int cou=0;
	int c1=0;
	
	while(c1!=3)
	{
		cout<<"==========================="<<endl;
		cout<<"Meeting room booking system"<<endl;
		cout<<"==========================="<<endl<<endl;
	
		cout<<"1.Staff\n";
		cout<<"2.Customer\n\n";
		cout<<"Choice: ";
		cin>>c1;
		
		if(c1==1)
		{
			StaffMenu(hea,tal);
		}
		else if(c1==2)
		{
			CustomerMenu(hea, tal);
		}
	}
	
	
	
	
	
	
	return 0;
}
