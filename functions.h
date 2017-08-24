#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <conio.h>
#include <time.h>
#include <algorithm>

using namespace std;

string polish( const char * text );

vector <string> Load(string path, vector <string> content) {
	ifstream file;
	file.open(path, ios::in);

	if(file.is_open()) {
		string line;
		while(getline(file, line)) {
			content.push_back(line);
		}
		file.close();
	}
	else {
		cout << polish("Blad otwarcia pliku. Waøπ siÍ losy galaktyki, sam napraw ten problem. \n");
		cin.get();
		exit(0);
	}

	return content;
}

string polish( const char * text )
{
    string result;
    for(; * text; text++)
    switch(* text )
    {
    case 'π': result += static_cast < char >( 0xa5 ); break;
    case 'Ê': result += static_cast < char >( 0x86 ); break;
    case 'Í': result += static_cast < char >( 0xa9 ); break;
    case '≥': result += static_cast < char >( 0x88 ); break;
    case 'Ò': result += static_cast < char >( 0xe4 ); break;
    case 'Û': result += static_cast < char >( 0xa2 ); break;
    case 'ú': result += static_cast < char >( 0x98 ); break;
    case 'ø': result += static_cast < char >( 0xbe ); break;
    case 'ü': result += static_cast < char >( 0xab ); break;
    case '•': result += static_cast < char >( 0xa4 ); break;
    case '∆': result += static_cast < char >( 0x8f ); break;
    case ' ': result += static_cast < char >( 0xa8 ); break;
    case '£': result += static_cast < char >( 0x9d ); break;
    case '—': result += static_cast < char >( 0xe3 ); break;
    case '”': result += static_cast < char >( 0xe0 ); break;
    case 'å': result += static_cast < char >( 0x97 ); break;
    case 'Ø': result += static_cast < char >( 0xbd ); break;
    case 'è': result += static_cast < char >( 0x8d ); break;
        default: result += * text; break;
    }
    return result;
}

vector <string> AddTranslation(string universe, vector <string> translations) {
	// Checks if given translation already exists
	for(int su = 0; su < translations.size(); su++) 
		if(translations[su] == universe) {
			break; // breaks the loop
			cout << polish("Takie t≥umaczenie juø istnieje.\n"); 
		}
		translations.push_back(universe);
		return translations;
}

vector <string> AddWord(string word, vector <string> words) {
	// Checks if given word already exists
	for(int i = 0; i < words.size(); i++)
		if(words[i] == word) {
			break;
			cout << polish("To s≥Ûwko juø jest w s≥owniku, przerywam.. :)\n");
			return words; // breaks the function
		}
		words.push_back(word);
		return words;
}

string GetSingleString(string text) {
	string st = "";
	int i = 0, j = 0, counter = 0;

	char* oldArray = (char*) malloc(text.length() * sizeof(*oldArray));

	/*while(oldArray[j] != ' ') {
		counter++;
		j++;
	} */

	//char* newArray = (char*) malloc(counter * sizeof(*newArray));

	strcpy(oldArray, text.c_str());
	
	while(oldArray[i] != ' ') {
		st.push_back(oldArray[i]);
		i++;
	}
	// cout << st; // for developing purpose
	 
	return st;
}

void Learn(vector <string> words, vector <string> translations) {
	char ch = 'x';
	int randint = 0;

	system("cls");
	srand( time( NULL));

	// 'e' exits
	while(ch != 'e') {
		ch = 'x';
		randint = rand() % words.size();
		
		cout << "\n" << polish(words[randint].c_str()) << " - " << polish(translations[randint].c_str())
			<< polish("\n\nPos≥uchaj wymowy: y/n ");

		while(ch != 'n' && ch != 'e') {
			ch = _getch();
			
			if(ch == 'y') {
				string single_word = GetSingleString(words[randint]);
				string link = "https://www.diki.pl/images-common/en/mp3/" + single_word +".mp3";

				//clearing spaces
				string::iterator ending_position = remove(link.begin(), link.end(), ' ');
				link.erase(ending_position, link.end()); 

				const char* cLink = link.c_str(); 

				ShellExecute(0, 0, cLink, 0, 0, SW_SHOWMINIMIZED);
			}				
		}
		system("cls");
	}
}

void SetConsole(HANDLE hConsole) {
	
	//sets color
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	//sets font family and size
	CONSOLE_FONT_INFOEX ConsoleFontInfo;

	ConsoleFontInfo.cbSize = sizeof(ConsoleFontInfo);
	ConsoleFontInfo.nFont = 0;
	ConsoleFontInfo.dwFontSize.X = 0;
	ConsoleFontInfo.dwFontSize.Y = 24;
	ConsoleFontInfo.FontFamily == FF_DONTCARE;
	ConsoleFontInfo.FontWeight = FW_NORMAL;

	wcscpy(ConsoleFontInfo.FaceName, L"Consolas");

	SetCurrentConsoleFontEx(hConsole, FALSE, &ConsoleFontInfo);
}