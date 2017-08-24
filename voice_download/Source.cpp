#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include <time.h>

using namespace std;

string GetSingleString(string text) {
	string st = "";
	int i = 0, j = 0, counter = 0;

	char* oldArray = (char*) malloc(text.length() * sizeof(*oldArray));

	strcpy(oldArray, text.c_str());
	
	while(oldArray[i] != ' ') {
		st.push_back(oldArray[i]);
		i++;
	}


	return st;
}

int main(void) {
	clock_t tStart = clock();
	vector <string> words;

	string time;

	fstream file;
	file.open("words.txt", ios::in);

	if(file.is_open()) {
		string line;
			while(getline(file, line)) {
				words.push_back(line);
			}
			file.close();	
	} else {
		cout << "File open error."; 
	}

	string link;

	system("pause");
	system("cls");
	//http://audio.oxforddictionaries.com/en/mp3/house_gb_1.mp3

	for(int y = 0; y < words.size(); y++) {
		time = to_string((int)(clock() - tStart)/CLOCKS_PER_SEC);
		SetConsoleTitle(("Execution timer: " + time).c_str());

		cout << "Downloading [" << y << "/" << words.size() << "]" << " :" << words[y] << "\n";
		link = "http://audio.oxforddictionaries.com/en/mp3/" + GetSingleString(words[y]) +"_gb_1.mp3";
		ShellExecute(0, 0, link.c_str(), 0, 0, SW_SHOW);
		Sleep(150);
	}
	cin.get();
	return 0;
}

