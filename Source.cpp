#include<map>
#include<set>
#include<ctime>
#include<cstdio>
#include<string>
#include<conio.h>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

int main() {
	ifstream fin("網頁原始碼.txt");
	ofstream fout("抽獎名單.txt"), fout2("中獎名單.txt");
	string str, findPeople("<p class=\"FM-cbox5\"><a href=\"http://home.gamer.com.tw/"),
			noPeople("class=\"FM-cboxfold\"");
	//findPeople 沒刪文, noPeople刪文
	map<int, string> peopleList, winner;
	int i, count = 1, del = 0, endFloor, cgline = 1, noPeopleLen = noPeople.length();

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
			if (!(cgline++ % 3))	fout << endl;
			count++;
		}
		else{
			if (str.length() >= 61) {
				if (str.compare(42, noPeopleLen, noPeople) && 
					str.compare(31, noPeopleLen, noPeople) &&
					str.compare(5, noPeopleLen, noPeople))
					continue;
			}
			else if (str.length() >= 50) {
				if (str.compare(31, noPeopleLen, noPeople) &&
					str.compare(5, noPeopleLen, noPeople))
					continue;
			}
			else if (str.length() >= 24) {
				if (str.compare(5, noPeopleLen, noPeople))
					continue;
			}
			else continue;
			istringstream sin(str);
			string dupDel;

			while (sin >> dupDel) {
				if (!dupDel.compare(0, noPeopleLen, noPeople)) {
					count++;
					del++;
				}
			}
		}
		if (count > endFloor)
			break;
	}
	cout << "-------------載入結束-------------" << endl;
	fout.close();
	count--;

	//排除自己
	if(peopleList.find(1) != peopleList.end())
		peopleList.erase(peopleList.find(1));
	del++;
	count -= del;

	//驗證一下自己沒有少貼上樓層
	cout << "總文章: " << count << endl;
	cout << "自刪 or 被刪文章數: " << del << endl;
	
	//顯示抽獎人數
	/*
	i = 1;
	for (auto& iter:list) {
	printf("%3dF %25s\t", iter->first, iter->second.c_str());
	if (!(i++ % 3))
	cout << endl;
	}
	*/

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
