#ifndef IOPROC_H
#define IOPROC_H

#include <bits/stdc++.h>
#include "define.h"
using namespace std;
//-----

struct Department {
	vector<pii> EventSchedules;
	int MemberLimit;
	vector<string> Tags;
};

struct Student {
	vector<pii> FreeTime;
	vector<string> ApplicationsDepartment;
	vector<string> Tags;
};

int Time(string);

vector<pii> GetTime();

string GetStuNo(string);

vector<string> GetAppDep();

vector<string> GetTags();

void GetStudentInfo();

int GetLimit(string);

string GetDeparNo(string);

void GetDepartmentInfo();

void Test();

void Out();

#endif
