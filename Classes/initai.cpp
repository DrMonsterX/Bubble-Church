#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
#include<cmath>
#include<ctime>
#include<queue>

//initial construction
//the graph num 20 can be changed with the tilemap
//graph[i] is a vertex
//you only need to change the num 20
//and figure out how to use mouse listener to judge the start and the destination input
//start is the present vec2  destination is the mouse vec2
//the function will be updated
//the path is stored in the Qclose
//you get the num from the Qclose and set the player's movement
using namespace std;
struct list {
	int num;
	struct list*prear;
	int access;
	int dist;
};
typedef struct head {
	int num;
	struct list*plist;
	int gfun;
	int hfun;

}Head;
Head graph[20];
queue<int> Qopen;
queue<int> Qclose;
vector<int> path;

void initgraph(int arr[][20]) {

	int i, j;
	//init the graph
	for (i = 0; i < 20; i++) {
		graph[i].gfun = 0;
		graph[i].hfun = 0;
		graph[i].num = i;
		graph[i].plist = nullptr;
	}
	cout << "show matrix" << endl;
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++)
			cout << arr[i][j] << ' ';
	//init the distance
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++) {
			if (arr[i][j] <= 1000) {
				list *plist = new list[1];
				plist->access = 1;
				plist->num = j;
				plist->dist = arr[i][j];
				plist->prear = nullptr;
				if (graph[i].plist == nullptr)
					graph[i].plist = plist;
				else {
					list *temp;
					for (temp = graph[i].plist; temp->prear != nullptr; temp = temp->prear);
					temp->prear = plist;
				}
			}
		}
	//show the graph
	cout << "show the graph" << endl;
	list *temp;
	for (i = 0; i < 20; i++) {
		cout << i << endl;
		for (j = 0, temp = graph[i].plist; j < 20 && temp->prear != nullptr; j++, temp = temp->prear)
			cout << temp->num << ' ' << temp->dist << endl;
	}

}
bool exist(int i, queue<int> q) {
	while (q.size()) {
		if (i == q.front()) {
			return true;
		}
		else q.pop();
	}
	return false;
}
void findpath() {
	int arr[20][20];
	srand((unsigned)time);
	int i, j;
	//initial the weight
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++)
			arr[i][j] = rand() % 1000;
	for (i = 0; i < 20; i++)
		arr[i][i] = 0;
	srand((unsigned)time);
	int t1, t2;
	for (i = 0; i < 150; i++) {
		t1 = rand() % 20;
		t2 = rand() % 20;
		arr[t1][t2] = 1000000;
	}
	//output initial matrix
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++)
			cout << arr[i][j] << ' ';

		cout << endl;
	}
	//floyd
	int k;
	int distance[20][20];
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++)
			distance[i][j] = arr[i][j];
	for (k = 0; k<20; k++)
		for (i = 0; i < 20; i++)
			for (j = 0; j < 20; j++) {
				if (arr[i][j] > arr[i][k] + arr[k][j])
					arr[i][j] = arr[i][k] + arr[k][j];
			}
	cout << "show distance matrix" << endl;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++)
			cout << arr[i][j] << ' ';
		cout << endl;
	}
	initgraph(arr);
	//output distance matrix
	cout << "show distance" << endl;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++)
			cout << arr[i][j] << ' ';

		cout << endl;
	}
	//aim function
	int Fun = 0;
	int gfun = 0;
	int hfun = 0;
	//update hfun
	int destination;
	cout << "input destination" << endl;
	cin >> destination;
	for (i = 0; i<20; i++)
		graph[i].hfun = arr[i][destination];
	int start;
	cout << "input start" << endl;
	cin >> start;

	//astarpath
	list *temp;
	int length = 0;
	int note = start;

	while (note != destination) {
		//update the openqueue and gfun
		if (exist(note, Qclose)) {

		}
		temp = graph[note].plist;
		for (temp = graph[note].plist; temp->prear != nullptr; temp = temp->prear) {
			if (!exist(temp->num, Qclose)) {
				Qopen.push(temp->num);
				graph[temp->num].gfun = arr[note][temp->num];
			}
		}
		//graph fun
		vector<pair<int, int>> f_vec;
		while (Qopen.size()) {
			k = Qopen.front();
			Qopen.pop();
			f_vec.push_back(make_pair(k, graph[k].gfun + graph[k].hfun));
		}
		//find minfun
		auto it = f_vec.begin();
		auto record = it->first;
		int minitem = 10000;
		for (; it != f_vec.end(); it++)
			if (it->second < minitem&&arr[note][record] <= 1000) {
				minitem = it->second;
				record = it->first;
			}

		length += arr[note][record];
		note = record;
		Qclose.push(note);
		cout << note << endl;
	}
	cout << "show the result" << endl;
	while (Qclose.size()) {
		cout << Qclose.front() << ' ';
		Qclose.pop();
	}
	cout << endl;
	cout << length << endl;

}
bool Run() {};
bool RunAndAttack(){}
bool RunToSafety() {};
bool HaveBall(){}
bool FindPath(){}
bool PathOnTime(){}
bool EnemyInRange(){}
bool TileInRange(){}
bool GetToSafety(){}
int main() {


	system("pause");
	return 0;
}