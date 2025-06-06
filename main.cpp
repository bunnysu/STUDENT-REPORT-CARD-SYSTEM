#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


//---------------full description of class-----------------

class student
{
	int rollno;
	char name[50];
	int m_marks, e_marks, cal_marks, p_marks, web_marks, c_marks;
	double avg;
	char grade;
	void calculate();	    //function to calculate grade
public:
	void getdata();	        //function to accept data from user
	void showdata() const;	//function to show data on screen
	void show_tabular() const;
	int retrollno() const;
};


void student::calculate()
{
	avg=(m_marks+e_marks+cal_marks+p_marks+web_marks+c_marks)/6.0;
	if(avg>=75)
		grade='A';
	else if(avg>=60)
		grade='B';
	else if(avg>=50)
		grade='C';
	else
		grade='D';
}

void student::getdata()
{
    student st;
    bool flag=false;
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	ifstream inFile;
    inFile.open("sturecord.dat",ios::binary);
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==rollno)
		{
	  		cout<<"This roll number already exists";
	  		flag=true;
		}
	}
    inFile.close();
		if (flag==false)
        {
            cout<<"\n\nEnter The Name of student ";
            cin.ignore();
            cin.getline(name,50);
            cout<<"\nEnter The marks in myanmar out of 100 : ";
            cin>>m_marks;
            while(m_marks>100)
            {
                cout<<"The marks you entered is invalid, re-enter the mark: ";
                cin>>m_marks;
            }
            cout<<"\nEnter The marks in english out of 100 : ";
            cin>>e_marks;
            while(e_marks>100)
            {
                cout<<"The marks you entered is invalid, re-enter the mark: ";
                cin>>e_marks;
            }
            cout<<"\nEnter The marks in calculus out of 100 : ";
            cin>>cal_marks;
            while(cal_marks>100)
            {
                cout<<"The marks you entered is invalid, re-enter the mark: ";
                cin>>cal_marks;
            }
            cout<<"\nEnter The marks in physics out of 100 : ";
            cin>>p_marks;
            while(p_marks>100)
            {
                cout<<"The marks you entered is invalid, re-enter the mark: ";
                cin>>p_marks;
            }
            cout<<"\nEnter The marks in web technology out of 100 : ";
            cin>>web_marks;
            while(web_marks>100)
            {
                cout<<"The marks you entered is invalid, re-enter the mark: ";
                cin>>web_marks;
            }
            cout<<"\nEnter The marks in C++ out of 100 : ";
            cin>>c_marks;
            while(c_marks>100)
            {
                cout<<"The marks you entered is invalid, re-enter the mark: ";
                cin>>c_marks;
            }
            cout<<"\n\nStudent record Has Been Created ";
            calculate();
            }

}

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Myanmar : "<<m_marks;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Calculus : "<<cal_marks;
	cout<<"\nMarks in Physics : "<<p_marks;
	cout<<"\nMarks in Web Technology : "<<web_marks;
	cout<<"\nMarks in C++ : "<<c_marks;
	cout<<"\nPercentage of student is  : "<<avg;
	cout<<"\nGrade of student is : "<<grade;
}

void student::show_tabular() const
{
	cout<<setw(4)<<rollno<<setw(20)<<name<<setw(5)<<m_marks<<setw(5)<<e_marks<<setw(5)<<cal_marks<<setw(5)<<p_marks<<setw(5)<<web_marks
	<<setw(5)<<c_marks<<setw(7)<<setprecision(2)<<avg<<setw(5)<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;

}


//--------------declaration of functions--------

void write_student();	//write the record in binary file
void display_all();		//read all records from binary file
void display_stu(int);	//accept rollno and read record from binary file
void display_stu1(int); //for student menu
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();	//display result menu
void intro();	//display welcome screen
void entry_menu();	//display entry menu on screen
void entry_login(); //accept the password to get access to the entry menu


//--------------main function-------------------

int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\nAre you Admin? (y/n): ";
		cin>>ch;
		switch(ch)
		{
			case 'n': result();
				break;
			case 'y': entry_login();
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}

void entry_login()
{
    string password;
    system("cls");
    cout<<"\n\n\tEnter Login Code: ";
    cin>>password;
    if(password=="12qwaszx")
    {
        entry_menu();
    }else{
        cout<<"\n\n\tInvalid Login Code!!Press any key to exit...";
        cin.ignore();
        cin.get();
    }
}

//-----------function to display entry menu------------

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.DELETE STUDENT RECORD";
	cout<<"\n\n\t5.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-5) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':   display_all();break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_stu(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_student(num);break;
	case '5':	break;
	default:	cout<<"\a"; entry_menu();
	}
}

//------------write the student data----------

void write_student()
{
	student st;
	st.getdata();
	ofstream outFile;
	outFile.open("sturecord.dat",ios::binary|ios::app);

	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
	cin.ignore();
	cin.get();
	entry_menu();
}

//------------read the file and display-----------

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("sturecord.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
	entry_menu();
}

//-------------read the individual file for each student-----------

void display_stu(int n)
{
	student st;
	ifstream inFile;
	inFile.open("sturecord.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		st.showdata();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
    cin.ignore();
    cin.get();
	entry_menu();
}

void display_stu1(int n)
{
	student st;
	ifstream inFile;
	inFile.open("sturecord.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		st.showdata();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
    cin.ignore();
    cin.get();
	result();
}

//------------------function to delete file--------------

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("sturecord.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("sturecord.dat");
	rename("Temp.dat","sturecord.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
	entry_menu();
}

//----------------function to display result menu-----------------

void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\t1. Student Report Card";
	cout<<"\n\n\t2. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_stu1(rno); break;
	case '2' :	break;
	default:	cout<<"\a";
	}
}

//-----------------intro function-----------------------

void intro()
{
    int i=0;
    for (i=0; i<=45; i++)
    {
        cout<<"-";
    }
    cout<<"\n\n\n\t\t  STUDENT";
	cout<<"\n\n\t\tREPORT CARD";
	cout<<"\n\n\t\t  PROJECT";
    cout<<"\n\n\n\tMADE BY : Group 3 of Section B"<<"\n"<<endl;
    for (i=0; i<=45; i++)
    {
        cout<<"-";
    }
    cin.get();
}
