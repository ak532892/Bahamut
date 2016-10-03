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
	ofstream fout("out.txt");
	string str;
	string success("<p class=\"FM-cbox5\"><a href=\"http://home.gamer.com.tw/"),
		fail("<div class=\"FM-cboxfold");
	//success 沒刪文, fail 刪文
	map<int, string> list, winner;
	int i, count = 1, del = 0;

	while (getline(fin, str)) {
		if (!str.compare(0, 54, success)) {
			string account = "", id = "";
			int accountLen;

			for (i = 54; str[i] != '"'; i++)
				account += str[i];
			accountLen = account.length();
			for (i += 23 + accountLen; str[i] != ')'; i++)
				id += str[i];

			list[count++] = account + " (" + id + ")";
		}
		else if (!str.compare(0, 23, fail)) {
			count++;
			del++;
		}
	}

	list.erase(list.find(1));
	del++;
	//排除自己
	i = 1;
	for (auto iter = list.begin(); iter != list.end(); iter++, i++) {
		printf("%3dF %25s\t", iter->first, iter->second.c_str());
		if (!(i % 3))
			cout << endl;
	}

	int totalNum;

	cout << "\n-------------\n輸入抽獎人數: ";
	cin >> totalNum;

	srand(time(NULL));
	count--;
	count -= del;
	set<string> dup;
	//排除重複
	for (i = 0; i < totalNum && count; i++) {
		int luckyNum = (rand() % count);
		auto iter = next(list.begin(), luckyNum);
		int setSize = dup.size();

		dup.insert(iter->second);
		if (setSize == dup.size()) {
			list.erase(list.find(iter->first));
			count--;
			continue;
		}
		winner[iter->first] = iter->second;
		list.erase(list.find(iter->first));
		count--;
	}
	cout << "中獎名單:" << endl;

	i = 1;
	for (auto iter = winner.begin(); iter != winner.end(); iter++, i++) {
		printf("%3dF %25s\t", iter->first, iter->second.c_str());
		fout << iter->first << "F " << iter->second << endl;
		if (!(i % 3))
			cout << endl;
	}

	fin.close();
	fout.close();
	_getch();
	return 0;
}