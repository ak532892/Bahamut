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
	ifstream fin("������l�X.txt");
	ofstream fout("����W��.txt"), fout2("�����W��.txt");
	string str, findPeople("<p class=\"FM-cbox5\"><a href=\"http://home.gamer.com.tw/"),
			noPeople("class=\"FM-cboxfold\"");
	//findPeople �S�R��, noPeople�R��
	map<int, string> peopleList, winner;
	int i, count = 1, del = 0, endFloor, cgline = 1, noPeopleLen = noPeople.length();

	//�I��Ӽh
	cout << "�I��Ӽh: ";
	cin >> endFloor;

	cout << "----------���J����W�椤----------" << endl;
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
	cout << "-------------���J����-------------" << endl;
	fout.close();
	count--;

	//�ư��ۤv
	if(peopleList.find(1) != peopleList.end())
		peopleList.erase(peopleList.find(1));
	del++;
	count -= del;

	//���Ҥ@�U�ۤv�S���ֶK�W�Ӽh
	cout << "�`�峹: " << count << endl;
	cout << "�ۧR or �Q�R�峹��: " << del << endl;
	
	//��ܩ���H��
	/*
	i = 1;
	for (auto& iter:list) {
	printf("%3dF %25s\t", iter->first, iter->second.c_str());
	if (!(i++ % 3))
	cout << endl;
	}
	*/

	int totalNum;
	
	cout << "��J����H��: ";
	cin >> totalNum;

	srand(time(NULL));

	set<string> dup;
	//�ư�����
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
	cout << "�����W��:" << endl;

	i = 1;
	for (auto& iter:winner) {
		printf("%3dF %25s\t", iter.first, iter.second.c_str());
		fout2 << iter.first << "F " << iter.second << "\t";
		if (!(i++ % 3)) {
			cout << endl;
			fout2 << endl;
		}
	}
	cout << "\n------�����Ы����N��------" << endl;
	
	fin.close();
	fout2.close();
	_getch();
	return 0;
}