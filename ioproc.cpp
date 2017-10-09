#include <bits/stdc++.h>
#include "include/ioproc.h"
using namespace std;
const string STUDENT[4]= {"free_time", "student_no", "applications_department", "tags"};
const string DEPARTMENTS[4]= {"event_schedules", "member_limit", "department_no", "tags"};
const string WEEK[7]= {"Mon", "Tues", "Wed", "Thur", "Fri", "Sta", "Sun"};
const int WEEKDX[7]= {0, 1440, 2880, 4320, 5760, 7200, 8640};
map<string, Department> Departments;
map<string, Student> Students;
extern map<string, vector<string> > Admit;
extern map<string, int> StudentNo, DepartmentsNo;
extern map<int, string> NoStudent, NoDepartments;
//translate from HH:MM to num
int Time(string Str) {
	int HH=0, MM=0;
	rep(i, 0, 2)HH=HH*10+Str[i]-'0';
	rep(i, 4, 6)MM=MM*10+Str[i]-'0';
	return HH*60+MM;
}
//get all time of a department or a student
vector<pii> GetTime() {
	vector<pii> FreeTime;
	string Str;
	while(true) {
		getline(cin, Str);
		if(Str.find(']')!=string::npos) {
			break;
		}
		int Id=-1;
		rep(day, 0, 7) {
			if(Str.find(WEEK[day])!=string::npos) {
				Id=day;
				break;
			}
		}
		string Begin, End;
		Begin=Str.substr(Str.find('.')+1, Str.find('~')-Str.find('.')-1);
		End=Str.substr(Str.find('~')+1, Str.rfind('"')-Str.find('~')-1);
		FreeTime.pb(mp(Time(Begin)+WEEKDX[Id], Time(End)+WEEKDX[Id]));
	}
	return FreeTime;
}

string GetStuNo(string Str) {
	return Str.substr(Str.find(STUDENT[1])+sz(STUDENT[1])+4, Str.rfind('"')-(Str.find(STUDENT[1])+sz(STUDENT[1])+4));
}

vector<string> GetAppDep() {
	vector<string> AppDep;
	string Str;
	while(true) {
		getline(cin, Str);
		if(Str.find(']')!=string::npos) {
			break;
		}
		AppDep.pb(Str.substr(Str.find("\"")+1, Str.rfind("\"")-Str.find("\"")-1));
	}
	return AppDep;
}
//get all tags of a department or student
vector<string> GetTags() {
	vector<string> Tags;
	string Str;
	while(true) {
		getline(cin, Str);
		if(Str.find(']')!=string::npos) {
			break;
		}
		Tags.pb(Str.substr(Str.find("\"")+1, Str.rfind("\"")-Str.find("\"")-1));
	}
	return Tags;
}

void GetStudentInfo() {
	string Str;
	getline(cin, Str);
	string *StuNo;
	Student *NewStudent;
	int Cnt;
	Cnt=1;
	while(Cnt) {
		getline(cin, Str);
		int id=-1;
		rep(i, 0, 4) {
			if(Str.find(STUDENT[i])!=string::npos) {
				id=i;
				break;
			}
		}
		if(id==-1) {
			if(Str.find('{')!=string::npos) {
				Cnt++;
				NewStudent=new Student;
				StuNo=new string;
			}
			if(Str.find('}')!=string::npos) {
				Cnt--;
				Students[*StuNo]=*NewStudent;
			}
			if(Str.find('[')!=string::npos) {
				Cnt++;
			}
			if(Str.find(']')!=string::npos) {
				Cnt--;
			}
		}
		switch(id) {
			case 0:
				NewStudent->FreeTime=GetTime();
				break;
			case 1:
				*StuNo=GetStuNo(Str);
				break;
			case 2:
				NewStudent->ApplicationsDepartment=GetAppDep();
				break;
			case 3:
				NewStudent->Tags=GetTags();
				break;
		}
	}
	//test infomation is correct
	/*	for(auto it=Students.begin(); it!=Students.end(); it++){
			de(it->fi);
			for(auto FT : it->se.FreeTime){
				dd(FT.fi), de(FT.se);
			}
			for(auto AD : it->se.ApplicationsDepartment){
				de(AD);
			}
			for(auto tag : it->se.Tags){
				de(tag);
			}
		}*/
}

int GetLimit(string Str) {
	int Limit=0;
	for(int Pos=Str.rfind(' ')+1; '0'<=Str[Pos]&&Str[Pos]<='9'; Pos++) {
		Limit=Limit*10+Str[Pos]-'0';
	}
	return Limit;
}

string GetDeparNo(string Str) {
	return Str.substr(Str.find(DEPARTMENTS[2])+sz(DEPARTMENTS[2])+4, Str.rfind('"')-(Str.find(DEPARTMENTS[2])+sz(DEPARTMENTS[2])+4));
}

void GetDepartmentInfo() {
	string Str;
	getline(cin, Str);
	string *DeParNo;
	Department *NewDepartment;
	int Cnt;
	Cnt=1;
	while(Cnt) {
		getline(cin, Str);
		int id=-1;
		rep(i, 0, 4) {
			if(Str.find(DEPARTMENTS[i])!=string::npos) {
				id=i;
				break;
			}
		}
		if(id==-1) {
			if(Str.find('{')!=string::npos) {
				Cnt++;
				NewDepartment=new Department;
				DeParNo=new string;
			}
			if(Str.find('}')!=string::npos) {
				Cnt--;
				Departments[*DeParNo]=*NewDepartment;
			}
			if(Str.find('[')!=string::npos) {
				Cnt++;
			}
			if(Str.find(']')!=string::npos) {
				Cnt--;
			}
		}
		switch(id) {
			case 0:
				NewDepartment->EventSchedules=GetTime();
				break;
			case 1:
				NewDepartment->MemberLimit=GetLimit(Str);
				break;
			case 2:
				*DeParNo=GetDeparNo(Str);
				break;
			case 3:
				NewDepartment->Tags=GetTags();
				break;
		}
	}
	//test information is correct
	/*	for(auto it=Departments.begin(); it!=Departments.end(); it++){
			de(it->fi);
			for(auto ES : it->se.EventSchedules){
				dd(ES.fi), de(ES.se);
			}
			de(it->se.MemberLimit);
			for(auto tag : it->se.Tags){
				de(tag);
			}
		}*/
}
void Test() {
	string Str;
	getline(cin, Str);
	GetStudentInfo();
	GetDepartmentInfo();
}

void Out() {
	cout<<"{"<<endl;
	cout<<"\t\"unlucky_student\": ["<<endl;
	bool Firs=1;
	for(auto it=StudentNo.begin(); it!=StudentNo.end(); it++) {
		if(!Firs)cout<<","<<endl;
		cout<<"\t\t\""<<it->fi<<"\"";
		Firs=0;
	}
	cout<<endl<<"\t],"<<endl;
	cout<<"\t\"admitted\": ["<<endl;
	Firs=1;
	for(auto it : Admit) {
		if(!Firs)cout<<","<<endl;
		cout<<"\t\t{"<<endl;
		cout<<"\t\t\t\"member\": ["<<endl;
		bool Sec=1;
		for(auto Sno : it.se) {
			if(!Sec)cout<<","<<endl;
			cout<<"\t\t\t\t\""<<Sno<<"\"";
			Sec=0;
		}
		cout<<endl<<"\t\t\t],"<<endl;
		cout<<"\t\t\t\"department_no\": \""<<it.fi<<"\""<<endl;
		cout<<"\t\t}";
		Firs=0;
	}
	cout << "\t]," << endl;
	cout<<endl<<"\t\"unlucky_department\": ["<<endl;
	Firs=1;
	for(auto it=DepartmentsNo.begin(); it!=DepartmentsNo.end(); it++) {
		if(!Firs)cout<<","<<endl;
		cout<<"\t\t\""<<it->fi<<"\"";
		Firs=0;
	}
	cout<<endl<<"\t]"<<endl;
	cout<<"}"<<endl;
}
