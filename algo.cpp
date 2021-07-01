#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <array>
#include <fstream>

using namespace std;

typedef pair<int,int> P;

struct SegmentTree {
	int N;
	vector<P> tree;

	void init(int n) {
		N = 1;
		while (N <= n) N *= 2;
		tree.resize(2*N);
	}

	void update(int k, P x) {
		k += N;
		tree[k] = x;
		for (k /= 2; k >= 1; k /= 2) {
			tree[k] = max(tree[2*k],tree[2*k+1]);
		}
	}

	P getMax(int a, int b) {
		a += N; b += N;
		P p = {0,0};
		while (a <= b) {
			if (a%2 == 1) p = max(p,tree[a++]);
			if (b%2 == 0) p = max(p,tree[b--]);
			a /= 2; b /= 2;
		}
		return p;
	}
};

struct PatternFinder {
	vector<P> notes;
	int window;
	int total;
	vector<set<P>> sets;
	SegmentTree tree;
	int record;

	PatternFinder() {
		window = 1e9;
		total = 0;
		tree.init(1e6);
		sets.resize(1e6);
		record = 0;
	}

	void addNote(int pos, int note) {
		notes.push_back({pos,note});
	}

	void setWindow(int w) {
		window = w;
	}

	void find(vector<P> pairs) {
		vector<array<int,3>> data;
		int n = pairs.size();
		for (int i = 0; i < n; i++) {
			data.push_back({notes[pairs[i].first].first,notes[pairs[i].second].first,i});
		}
		sort(data.begin(),data.end());

		vector<P> result(n);
		int j = n-1;
		vector<int> buffer;
		vector<int> changes;
		for (int i = n-1; i >= 0; i--) {
			if (i != n-1 && data[i][0] != data[i+1][0]) {
				for (auto pos : buffer) {
					tree.update(pos,*sets[pos].rbegin());
				}
				buffer.clear();
			}
			while (data[j][0]-data[i][0] > window) {
				changes.push_back(data[j][1]);
				sets[data[j][1]].erase({result[j].first,data[j][2]});
				if (sets[data[j][1]].size() == 0) {
					tree.update(data[j][1],{0,0});
				} else {
					tree.update(data[j][1],*sets[data[j][1]].rbegin());
				}
				j--;
			}
			int pos1 = data[i][0];
			int pos2 = data[i][1];
			auto best = tree.getMax(pos2+1,min(pos2+1+window-1,(int)1e6));
			if (best.first == 0) {
				result[i] = {1,-1};
			} else {
				result[i] = {best.first+1,best.second};
			}
			total += result[i].first;
			record = max(record, result[i].first);
			changes.push_back(pos2);
			sets[pos2].insert({result[i].first,i});
			buffer.push_back(pos2);
		}
		for (auto x : changes) {
			tree.update(x,{0,0});
			sets[x].clear();
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
	pf.setWindow(250);
	pf.findPatterns();
}
