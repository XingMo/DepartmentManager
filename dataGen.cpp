#include <bits/stdc++.h>
using namespace std;

const int NoDepart = 20;
const int NoStudent = 300;

// tags string
vector<string> TAGS= {"sports","music","darwing","math","science","others"};
// free time string
vector<string> FTIS= {
	"Mon.8:20~10:00", "Mon.10:20~12:00", "Mon.14:00~15:40", "Mon.15:50~17:30", "Mon.19:00~21:35",
	"Tues.8:20~10:00", "Tues.10:20~12:00", "Tues.14:00~15:40", "Tues.15:50~17:30", "Tues.19:00~21:35",
	"Wed.8:20~10:00", "Wed.10:20~12:00", "Wed.14:00~15:40", "Wed.15:50~17:30", "Wed.19:00~21:35",
	"Thur.8:20~10:00", "Thur.10:20~12:00", "Thur.14:00~15:40", "Thur.15:50~17:30", "Thur.19:00~21:35",
	"Fri.8:20~10:00", "Fri.10:20~12:00", "Fri.14:00~15:40", "Fri.15:50~17:30", "Fri.19:00~21:35",
	"Sat.8:20~10:00", "Sat.10:20~12:00", "Sat.14:00~15:40", "Sat.15:50~17:30", "Sat.19:00~21:35",
	"Sun.8:20~10:00", "Sun.10:20~12:00", "Sun.14:00~15:40", "Sun.15:50~17:30", "Sun.19:00~21:35"
};

struct Student {
	string id;
	set<string> freeTime;
	set<string> tag;
	vector<string> departApply;
};

struct Department {
	string id;
	int memLimit;
	string eventSche;
	vector<string> tag;
};

vector<Department> Vec_depart;
vector<Student> Vec_student;

//shift TAGS to get random result
void TagShift(int n) {
	for(int i=0; i<n; i++) {
		int nxt=rand()%(TAGS.size()-i);
		if(i!=i+nxt) swap(TAGS[i], TAGS[i+nxt]);
	}
}

//shift FTIS to get randome result
void FtiShift(int n) {
	for(int i=0; i<n; i++) {
		int nxt=rand()%(FTIS.size()-i);
		if(i!=i+nxt) swap(FTIS[i], FTIS[i+nxt]);
	}
}

int main() {
	freopen("input_data.txt", "w", stdout);
	srand(time(0));

	// department information generating part
	for(int i=1; i<=NoDepart; i++) {
		Department now;
		// formatted id
		int id = i;
		now.id = "D";
		now.id += to_string(id/100), id%=100;
		now.id += to_string(id/10), id%=10;
		now.id += to_string(id);

		// member limit
		now.memLimit = rand()%6+10;

		// tags of department
		int ptr=0;
		int Notag = 2 + rand()%(TAGS.size()-2)+1;
		TagShift(Notag);
		while(Notag--)
			now.tag.push_back(TAGS[ptr++]);

		// event schedule
		now.eventSche = FTIS[rand()%FTIS.size()];
		Vec_depart.push_back(now);
	}

	for(int i=1; i<=NoStudent; i++) {
		Student now;
		// formatted id
		int id = i;
		now.id = (string)"0315020" + ( id<10? ((string)"0"+to_string(id)) : (to_string(id)) );

		// intrest tag
		int ptr=0;
		int Notag = 2 + rand()%(TAGS.size()-2)+1;
		TagShift(Notag);
		while(Notag--)
			now.tag.insert(TAGS[ptr++]);

		// free time
		ptr=0;
		int Nofti = 2 + rand()%(FTIS.size()-2)+1;
		FtiShift(Nofti);
		while(Nofti--)
			now.freeTime.insert(FTIS[ptr++]);

		// look for department greedy
		// NegScore is a paremeter opposite to interesting attitude
		vector<pair<int,Department*>> List;
		for(int i=0; i<Vec_depart.size(); i++) {
			Department &dep = Vec_depart[i];
			// caculate NegScore
			int NegScore = 20;
			for(auto depTag : dep.tag) if(now.tag.find(depTag) != now.tag.end())
					NegScore --;

			// prevent free time collision
			bool done = 0;
			for(auto depApl : List)
				if(depApl.second->eventSche == dep.eventSche && depApl.first > NegScore) {
					depApl.second = &dep;
					done = 1;
				}
			if(done) continue;

			if(now.freeTime.find(dep.eventSche) == now.freeTime.end()) NegScore *= 2;
			List.push_back({NegScore, &dep});
		}
		// get 5 top interest departments
		sort(List.begin(), List.end());
		if(List.size()>5)
			List.erase(List.begin()+5, List.end());

		for(auto depApl : List) now.departApply.push_back(depApl.second->id);
		Vec_student.push_back(now);
	}

	// Output Part
	cout << "{" << endl;
	cout << "\t\"students\": [" << endl;
	bool firs = 1;
	for(auto now : Vec_student) {
		if(!firs) cout << "," << endl;
		cout << "\t\t{" << endl;

		bool ffirs = 1;

		cout << "\t\t\t\"free_time\": [" << endl;
		for(auto ft : now.freeTime) {
			if(!ffirs) cout << "," << endl;
			cout << "\t\t\t\t\"" << ft << "\"";
			ffirs = 0;
		}
		cout << endl << "\t\t\t]," << endl;

		cout << "\t\t\t\"student_no\": \"" << now.id << "\"," << endl;

		ffirs = 1;
		cout << "\t\t\t\"applications_department\": [" << endl;
		for(auto ad : now.departApply) {
			if(!ffirs) cout << "," << endl;
			cout << "\t\t\t\t\"" << ad << "\"";
			ffirs = 0;
		}
		cout << endl << "\t\t\t]," << endl;

		ffirs = 1;
		cout << "\t\t\t\"tags\": [" << endl;
		for(auto tg : now.tag) {
			if(!ffirs) cout << "," << endl;
			cout << "\t\t\t\t\"" << tg << "\"";
			ffirs = 0;
		}
		cout << endl << "\t\t\t]" << endl;

		cout << "\t\t}";
		firs = 0;
	}
	cout << endl << "\t]," << endl;

	firs = 1;
	cout << "\t\"departments\": [" << endl;
	for(auto now : Vec_depart) {
		if(!firs) cout << "," << endl;
		cout << "\t\t{" << endl;

		cout << "\t\t\t\"event_schedules\": [" << endl;
		cout << "\t\t\t\t\"" << now.eventSche << "\"" << endl;
		cout << "\t\t\t]," << endl;

		cout << "\t\t\t\"member_limit\": " << now.memLimit << endl;

		cout << "\t\t\t\"department_no\": \"" << now.id << "\"," << endl;

		bool ffirs = 1;
		cout << "\t\t\t\"tags\": [" << endl;
		for(auto tg : now.tag) {
			if(!ffirs) cout << "," << endl;
			cout << "\t\t\t\t\"" << tg << "\"";
			ffirs = 0;
		}
		cout << endl << "\t\t\t]" << endl;

		cout << "\t\t}";
		firs = 0;
	}
	cout << endl << "\t]" << endl;
	cout << "}";
	return 0;
}

