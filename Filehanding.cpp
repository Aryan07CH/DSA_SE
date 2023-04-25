/*Department maintains a student information. The file contains roll number, name, division 
and address. Allow user to add, delete information of student. Display information of 
particular employee. If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details. Use sequential file to main the data.
*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class student
  {
	typedef struct stud
	{
		int roll;
		char name[10];
		char div;
		char add[10];
	}stud;
	stud rec;
	public:
	  void create();
	  void display();
	  int search();
	  void Delete();
  };
void student::create()
  {
	char ans;
	ofstream fout;
	fout.open("stud.dat",ios::out|ios::binary);
	do
	  {
		cout<<"\n\tEnter Roll No of Student    : ";
		cin>>rec.roll;
		cout<<"\n\tEnter a Name of Student     : ";
		cin>>rec.name;
		cout<<"\n\tEnter a Division of Student : ";
		cin>>rec.div;
		cout<<"\n\tEnter a Address of Student  : ";
		cin>>rec.add;
		fout.write((char *)&rec,sizeof(stud))<<flush;
		cout<<"\n\tDo You Want to Add More Records: ";
		cin>>ans;
	  }while(ans=='y'||ans=='Y');
	fout.close();
  }
void student::display()
  {
	ifstream fin;
	fin.open("stud.dat",ios::in|ios::binary);
	fin.seekg(0,ios::beg);
	cout<<"\n\tThe Content of File are:\n";
	cout<<"\n\tRoll\tName\tDiv\tAddress";
	while(fin.read((char *)&rec,sizeof(stud)))
	  {
		if(rec.roll!=-1)
       		  cout<<"\n\t"<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.div<<"\t"<<rec.add;
	  }
	fin.close();
  }
int student::search()
  {
	int r,i=0;
	ifstream fin;
	fin.open("stud.dat",ios::in|ios::binary);
	fin.seekg(0,ios::beg);
	cout<<"\n\tEnter a Roll No: ";
	cin>>r;
	while(fin.read((char *)&rec,sizeof(stud)))
	  {
		if(rec.roll==r)
		  {
			cout<<"\n\tRecord Found...\n";
			cout<<"\n\tRoll\tName\tDiv\tAddress";
			cout<<"\n\t"<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.div<<"\t"<<rec.add;
			return i;
		  }
		i++;
	  }
	fin.close();
	return 0;
  }
void student::Delete()
  {
	int pos;
	pos=search();
	fstream f;
	f.open("stud.dat",ios::in|ios::out|ios::binary);
	f.seekg(0,ios::beg);
	if(pos==0)
	  {
		cout<<"\n\tRecord Not Found";
		return;
	  }
	int offset=pos*sizeof(stud);
	f.seekp(offset);
	rec.roll=-1;
	strcpy(rec.name,"NULL");
	rec.div='N';
	strcpy(rec.add,"NULL");
	f.write((char *)&rec,sizeof(stud));
	f.seekg(0);
	f.close();
	cout<<"\n\tRecord Deleted";
  }
	
int main()
  {
	student obj;
	int ch,key;
	char ans;
	do
	  {
		cout<<"\n\t***** Student Information *****";
		cout<<"\n\t1. Create\n\t2. Display\n\t3. Delete\n\t4. Search\n\t5. Exit";
		cout<<"\n\t..... Enter Your Choice: ";
		cin>>ch;
		switch(ch)
		  {
			case 1: obj.create();
				break;
			case 2:	obj.display();
				break;
			case 3: obj.Delete();
				break;
			case 4: key=obj.search();
				if(key==0)
				  cout<<"\n\tRecord Not Found...\n";
				break;
			case 5:
				break;
		  }
		cout<<"\n\t..... Do You Want to Continue in Main Menu: ";
		cin>>ans;
	  }while(ans=='y'||ans=='Y');
return 1;
  }
