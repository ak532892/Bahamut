#include<map>
#include<set>
#include<ctime>
#include<cstdio>
#include<string>
#include<conio.h>
#include<fstream>
#include<iostream>
using namespace std;

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt"), fout2("out2.txt");
	string str, findPeople("<p class=\"FM-cbox5\"><a href=\"http://home.gamer.com.tw/"),
		noPeople("<div class=\"FM-cboxfold");
	//success 沒刪文, fail 刪文
	map<int, string> peopleList, winner;
	int i, count = 1, del = 0, endFloor;

	//截止樓層
	cout << "截止樓層: ";
	cin >> endFloor;

	cout << "----------載入抽獎名單中----------" << endl;
	while (getline(fin, str)) {
		if (!str.compare(0, 54, findPeople)) {
			string account = "", id = "";

			for (i = 54; str[i] != '"'; i++)
				account += str[i];
			for (i += (23 + account.length()); str[i] != ')'; i++)
				id += str[i];

			peopleList[count] = account + " (" + id + ")";
			fout << count << "F " << peopleList[count] << "\t";
			if (!(count++ % 3))	fout << endl;
		}
		else if (!str.compare(0, 23, noPeople)) {
			count++;
			del++;
		}
		if (count > endFloor)
			break;
	}
	cout << "-------------載入結束-------------" << endl;
	fout.close();

	count--;
	peopleList.erase(peopleList.find(1));
	del++;
	count -= del;
	//排除自己
	//顯示抽獎人數
	/*
	i = 1;
	for (auto& iter:list) {
	printf("%3dF %25s\t", iter->first, iter->second.c_str());
	if (!(i++ % 3))
	cout << endl;
	}*/

	int totalNum;

	cout << "輸入抽獎人數: ";
	cin >> totalNum;

	srand(time(NULL));

	set<string> dup;
	//排除重複
	for (i = 0; i < totalNum && count; i++) {
		int luckyNum = (rand() % count);
		int setSize = dup.size();
		auto iter = next(peopleList.begin(), luckyNum);

		dup.insert(iter->second);
		if (setSize == dup.size()) {
			peopleList.erase(peopleList.find(iter->first));
			count--;
			i--;
			continue;
		}
		winner[iter->first] = iter->second;
		peopleList.erase(peopleList.find(iter->first));
		count--;
	}
	cout << "中獎名單:" << endl;

	i = 1;
	for (auto& iter:winner) {
		printf("%3dF %25s\t", iter.first, iter.second.c_str());
		fout2 << iter.first << "F " << iter.second << "\t";
		if (!(i++ % 3)) {
			cout << endl;
			fout2 << endl;
		}
	}

	cout << "\n------結束請按任意鍵------" << endl;
	fin.close();
	fout2.close();
	_getch();
	return 0;
}
