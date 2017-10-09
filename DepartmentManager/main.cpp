#include <bits/stdc++.h>
#include "include/ioproc.h"
#include "include/MCMF.h"
using namespace std;

const int inf = 1e9;
MCMF<int, int> g;
map<string, vector<string> > Admit;
map<string, int> StudentNo, DepartmentsNo;
map<int, string> NoStudent, NoDepartments;
int n, m;
extern map<string, Department> Departments;
extern map<string, Student> Students;

int main() {
	freopen("input_data.txt", "r", stdin);
	freopen("output_data.txt", "w", stdout);
	Test();
	// match model
	g.ini();
	for(auto it : Students) {
		StudentNo[it.fi]=n;
		NoStudent[n]=it.fi;
		n++;
	}
	m=n;
	for(auto it : Departments) {
		DepartmentsNo[it.fi]=m;
		NoDepartments[m]=it.fi;
		m++;
	}
	int Sink=m+1, Sourse=m+2;
	for(auto it : StudentNo) {
		g.link(Sourse, it.se, inf, 0);
	}
	for(auto it : Departments) {
		int DeparNo=DepartmentsNo[it.fi];
		g.link(DeparNo, Sink, it.se.MemberLimit, 0);
	}
	for(auto it : Students) {
		int StuNo=StudentNo[it.fi], DeparNo, Tot=sz(it.se.ApplicationsDepartment);
		for(auto Dep : it.se.ApplicationsDepartment) {
			if(!DepartmentsNo.count(Dep))continue;
			DeparNo=DepartmentsNo[Dep];
			g.link(StuNo, DeparNo, 1, -Tot);
			Tot--;
		}
	}
	pii t=g.run(Sourse, Sink);
	for(int Cur=0; Cur<n; Cur++) {
		for(int it=g.h[Cur]; ~it; it=g.ne[it]) {
			int v=g.to[it];
			if(g.to[it]<m) {
				if(!g.cap[it]) {
					Admit[NoDepartments[v]].pb(NoStudent[Cur]);
				}
			}
		}
	}
	for(auto it : Admit) {
		sort(it.se.begin(), it.se.end());
		if(DepartmentsNo.count(it.fi))DepartmentsNo.erase(it.fi);
		for(auto s : it.se) {
			if(StudentNo.count(s))StudentNo.erase(s);
		}
	}
	Out();

	// test match result
	/*	de(sz(DepartmentsNo));
		de(m);
		de(sz(StudentNo));
		de(n);
		for(auto it : StudentNo)
		de(t.fi);
		de(t.se);
	*/
	return 0;
}
