#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

typedef pair<int,int> P;

struct PatternFinder {
	vector<P> notes;
	int total;
	int record;

	PatternFinder() {
		total = 0;
		record = 0;
	}

	void addNote(int pos, int note) {
		notes.push_back({pos,note});
	}

	void find(vector<P> pairs) {
		vector<array<int,2>> data;
		int n = pairs.size();
		for (int i = 0; i < n; i++) {
			data.push_back({notes[pairs[i].first].first-notes[pairs[i].second].first,i});
		}
		sort(data.begin(),data.end());

        int count = 0;
        for (int i = 0; i < n; i++) {
            count++;
            if (i == n-1 || data[i][0] != data[i+1][0]) {
                record = max(record, count);
                total += count;
                count = 0;
            }
        }
	}

	void findPatterns() {
		int n = notes.size();
		vector<array<int,3>> pairs;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
			    if (notes[i].second-notes[j].second < 0) continue;
				pairs.push_back({notes[i].second-notes[j].second,i,j});
			}
		}
		cout << "number of pairs: " << pairs.size() << "\n";
		sort(pairs.begin(),pairs.end());
		vector<P> cur;
		for (int i = 0; i < pairs.size(); i++) {
			cur.push_back({pairs[i][1],pairs[i][2]});
			if (i == pairs.size()-1 || pairs[i][0] != pairs[i+1][0]) {
			    cout << "processing interval " << pairs[i][0] << "\n";
			    record = 0;
				find(cur);
        		cout << "maximum number of notes in a pattern: " << record << "\n";
				cur.clear();
			}
		}
		cout << "total number of notes in patterns: " << total << "\n";
	}
};

int main(int argc, char **argv) {
	PatternFinder pf;
	int n;
	cin >> n;
	while (n--) {
	    int t, p;
	    cin >> t >> p;
	    pf.addNote(t,p);
	}
	pf.findPatterns();
}
