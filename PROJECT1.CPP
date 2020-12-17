#include<stdio.h>
#include<graphics.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<conio.h>
#include<fstream.h>
#include<iostream.h>
void admin_func();
int compare(char name[50],long id);
void voter_func(long);
class candidate
{
   int nov;
   char name[50],symbol[20];
   public:
   candidate()
   {
     nov=0;
   }
   void set()
   {
     printf("\n--------------------------\n");
     cout<<"enter name of candidate ";
     gets(name);
     cout<<"enter symbol";
     gets(symbol);
     printf("\n--------------------------\n");
   }
   void delet()
   {
     strcpy(name,"             ");
     strcpy(symbol,"            ");
   }
   void count()
   {
    nov++;
   }
   char* getname()
   {
     return(name);
   }
   void display()
   {
      printf("\n--------------------------\n");
	cout<<"NAME:  "<<name;
	cout<<"\nSYMBOL:   "<<symbol;
	cout<<"\nNO. OF VOTES"<<nov;
      printf("\n--------------------------\n");
   }
};
candidate c1,c2,c3;
class voter
{
  long id;
  char name[50];
  public:
  void set()
  {
  printf("\n--------------------------\n");
  cout<<"enter name of voter";
  gets(name);
  cout<<"enter id ";
  cin>>id;
  printf("\n--------------------------\n");
 }
 long getid()
 {
    return id;
 }
 void delet()
 {
   strcpy(name,"               ");
   id=0;
 }
 void display()
 {
 printf("\n--------------------------\n");
  cout<<"NAME:  "<<name;
  cout<<"\tID:    "<<id;
 printf("\n--------------------------\n");
 }
 friend int compare(char name[50],long id);
};

void main()
{
  long id;
  char name[50];
  clrscr();
  start:
  printf("\n--------------------------\n");
  cout<<"enter name";
  gets(name);
  cout<<"enter id";
  cin>>id;
  if(strcmp(name,"admin")==0 && id==12345)
    admin_func();
  else
  {
   if(compare(name,id)==1)
   voter_func(id);
   else
   goto start;
  }
}

int compare(char name1[50],long id1)
{
   voter v;
   ifstream fin;
   fin.open("voters.bin",ios::in);
   while(fin.read((char*)&v,sizeof(v)))
   {
      if(strcmp(name1,v.name)==0 && id1==v.id)
      {
	return 1;
      }
   }
   return 0;
}

void admin_func()
{
  clrscr();
  printf("\n**********ADMIN MENU*****************\n");
  voter v;
  candidate c;
  int choice;
  int loc,obj;
  ofstream outfile;
  ifstream infile;
  while(1)
  {
    cout<<"enter choice:";
    cout<<"\n1.Add voters information";
    cout<<"\n2.Update voter information";
    cout<<"\n3.Display voter information";
    cout<<"\n4.Delete voter information";
    cout<<"\n5.Add candidates information";
    cout<<"\n6.Update candidates information";
    cout<<"\n7.Display candidates information";
    cout<<"\n8.Delete candidates information";
    cout<<"\n9.Exit";
    cin>>choice;
    switch(choice)
    {
       case 1:
	 outfile.open("voters.bin",ios::app);
	 v.set();
	 outfile.write((char*)&v,sizeof(v));
	 outfile.close();
	 break;
       case 2:
	 outfile.open("voters.bin",ios::ate);
	 cout<<"\nenter the position of object to be updated";
	 cin>>obj;
	 loc=(obj-1)*sizeof(v);
	 outfile.seekp(loc,ios::beg);
	 v.set();
	 outfile.write((char*)&v,sizeof(v));
	 outfile.close();
	 break;
      case 3:
	 infile.open("voters.bin",ios::in);
	 infile.seekg(0,ios::beg);
	 infile.read((char*)&v,sizeof(v));
	 while(!infile.eof())
	 {
	    v.display();
	    infile.read((char*)&v,sizeof(v));
	 }
	 infile.close();
	 break;
      case 4:
	 outfile.open("voters.bin",ios::ate);
	 cout<<"\nenter the position of object to be updated";
	 cin>>obj;
	 loc=(obj-1)*sizeof(v);
	 outfile.seekp(loc,ios::beg);
	 v.delet();
	 outfile.write((char*)&v,sizeof(v));
	 outfile.close();
	 break;
      case 5:
	 outfile.open("candidat.bin",ios::app);
	 c.set();
	 outfile.write((char*)&c,sizeof(c));
	 outfile.close();
	 break;
      case 6:
	 outfile.open("candidat.bin",ios::ate);
	 cout<<"\nenter the position of object to be updated";
	 cin>>obj;
	 loc=(obj-1)*sizeof(c);
	 outfile.seekp(loc,ios::beg);
	 c.set();
	 outfile.write((char*)&c,sizeof(c));
	 outfile.close();
	 break;
      case 7:
	  infile.open("candidat.bin",ios::in);
	 infile.seekg(0,ios::beg);
	 infile.read((char*)&c,sizeof(c));
	 while(!infile.eof())
	 {
	    c.display();
	    infile.read((char*)&c,sizeof(c));
	 }
	 c.display();
	 infile.close();
	 break;
      case 8:
	 outfile.open("candidat.bin",ios::ate);
	 cout<<"\nenter the position of object to be updated";
	 cin>>obj;
	 loc=(obj-1)*sizeof(c);
	 outfile.seekp(loc,ios::beg);
	 c.delet();
	 outfile.write((char*)&c,sizeof(c));
	 outfile.close();
	 break;
      case 9:
	exit(1);
      default:
	cout<<"\nwrong choice";
    }
  }
}

void voter_func(long id)
{
   clrscr();
   int choice;
   int gm,gd=DETECT;
   char name[50];
   initgraph(&gd,&gm,"..\\bgi");
   outtextxy(100,10,"BALLOT PAPER");
   rectangle(40,30,90,90);
   ifstream infile;
   infile.open("candidat.bin",ios::in);
   infile.read((char*)&c1,sizeof(c1));
   strcpy(name,c1.getname());
    outtextxy(120,50,name);
    outtextxy(120,70,"enter 1 to vote");
    circle(60,150,30);
   infile.read((char*)&c2,sizeof(c2));
   strcpy(name,c2.getname());
  outtextxy(120,150,name);
  outtextxy(120,150,"enter 2 to vote");
   line(60,210,30,250);
   line(30,250,90,250);
   line(90,250,60,210);
   infile.read((char*)&c3,sizeof(c3));
   strcpy(name,c3.getname());
    outtextxy(120,250,name);
    outtextxy(120,250,"enter 3 to vote");
   a:
   cin>>choice;
   infile.close();
   ofstream outfile;
   int loc;
   outfile.open("candidat.bin",ios::ate);
   if(choice==1)
   {
     c1.count();
     outfile.seekp(0,ios::beg);
     outfile.write((char*)&c1,sizeof(c1));
   }
   else if(choice==2)
   {
     c2.count();
     loc=sizeof(c2);
     outfile.seekp(loc,ios::beg);
     outfile.write((char*)&c2,sizeof(c2));
   }
   else if(choice==3)
   {
      c3.count();
      loc=2*sizeof(c3);
     outfile.seekp(loc,ios::beg);
     outfile.write((char*)&c3,sizeof(c3));
   }
   else
   {
      outtextxy(40,150,"invalid choice");
      goto a;
   }
   outfile.close();
   ifstream fin;
   voter v;
   fin.open("voters.bin",ios::in);
   while(fin.read((char*)&v,sizeof(v)))
   {
    if(v.getid()==id)
     loc=fin.tellg();
   }
   fin.close();
   ofstream fout;
   fout.open("voters.bin",ios::out);
   v.delet();
   fout.seekp(loc,ios::beg);
   fout.write((char*)&v,sizeof(v));
   fout.close();
}