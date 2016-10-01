#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<ctime>
#include<cstdio>
#include<conio.h>
using namespace std;

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	string str;
	string success("<p class=\"FM-cbox5\"><a href=\"http://home.gamer.com.tw/"),
		   fail("<div class=\"FM-cboxfold");
	//success �S�R��, fail �R��
	map<int, string> list, winner;
	int i, count = 1;

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
		else if (!str.compare(0, 23, fail))
			count++;
	}

	list.erase(list.find(1));
	//�ư��ۤv
	i = 1;
	for (auto iter = list.begin(); iter != list.end(); iter++, i++) {
		printf("%3dF %25s\t", iter->first, iter->second.c_str());
		if (!(i % 3))
			cout << endl;
	}

	int totalNum;

	cout << "\n-------------\n��J����H��: ";
	cin >> totalNum;
	
	srand(time(NULL));
	count--;
	for (i = 0; i < totalNum; i++) {
		int luckyNum = (rand() % count);
		auto iter = next(list.begin(), luckyNum);

		winner[iter->first] = iter->second;
		list.erase(list.find(iter->first));
		count--;
	}
	cout << "�����W��:" << endl;

	i = 1;
	for (auto iter = winner.begin(); iter != winner.end(); iter++, i++) {
		printf("%3dF %25s\t", iter->first, iter->second.c_str());
		fout << iter->first << "F "<< iter->second << endl;
		if (!(i % 3))
			cout << endl;
	}

	fin.close();
	fout.close();
	_getch();
	return 0;
}