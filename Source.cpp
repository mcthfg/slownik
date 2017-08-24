#include "functions.h"

int main(void) {

	SetConsole(GetStdHandle(STD_OUTPUT_HANDLE));

	string path_words = "res\\words.txt", 
		path_translations = "re\\translations.txt",
		path_translations_words = "res\\translations_only_words.txt";

	vector <string> words;
	vector <string> translations;
	vector <string> translations_words;

    words = Load(path_words, words);
	translations = Load(path_translations, translations);
	translations_words = Load(path_translations_words, translations_words);

	from_exit: for(;;) {
		SetConsoleTitle("v0.15");

		cout << polish("Menu g³ówne:\n");
		cout << "-----------\n";
		cout << polish("1. Pokazuj t³umaczenia\n");
		cout << polish("2. Pokazuj s³ówka\n");
		cout << polish("3. Dodaj s³ówko\n");
		cout << polish("4. S³ownik diki.pl\n");
		cout << polish("5. Graj!\n");
		cout << polish("6. Nauka\n");
		cout << polish("e. Wyjœcie\n\n");
		cout << polish("Twój wybór: ");

		char c = '0', v = '0';
		
		c = _getch();

			switch(c) {

			case 'e': exit(0);
			case 'E': exit(0); // caps lock case

			case '6': {
				Learn(words, translations_words);
				break;
			}

			case '5': {
				system("cls");

				int random, randint, points = 0;
				char which = '0';

				string input;

				while(true) {
					srand( time( NULL)); // for selecting option 1 or 2

					string str = (polish(("Jesteœ w trybie gry. Punkty: " + to_string(points)).c_str()));
					const char* title = str.c_str();

					SetConsoleTitle(title);
					
					switch(which) {

						// displays words to translate

						case '0': { 
							randint = rand() % words.size();
							cout << polish(words[randint].c_str()) << " - ";

							getline(cin, input);

							if(input == "e" || input == "E") {
								system("cls");
								if(points < 0)
									cout << polish("Twoja liczba punktów: ") << points << " :( ";
								else if(points == 0)
									cout << polish("Twoja liczba punktów: ") << points << " :| ";
								else if(points > 0)
									cout << polish("Twoja liczba punktów: ") << points << " :)";
								_getch();
								system("cls");

								goto from_exit;
							}

							if(input == polish(translations_words[randint].c_str())) {
								cout << polish("\nDobrze!\n\nPos³uchaj wymowy: y/n");
								
								char f = _getch();

								if(f == 'y') {
									string res = GetSingleString(words[randint]);
									string linkname = "https://www.diki.pl/slownik-angielskiego?q=" + res;
									const char* link = linkname.c_str();

									ShellExecute(0, 0, link, 0, 0, SW_SHOW); 
								}

								points++;
								Sleep(500);
							} else {
								cout << polish("\nle!\n\nPrawid³owe t³umaczenie: ") << polish(translations_words[randint].c_str())
									<< polish("\n\nPos³uchaj wymowy: y/n");
								
								char f = _getch();

								if(f == 'y') {
									string res = GetSingleString(words[randint]);
									string linkname = "https://www.diki.pl/slownik-angielskiego?q=" + res;
									const char* link = linkname.c_str();

									ShellExecute(0, 0, link, 0, 0, SW_SHOW); 
								}

								points--;
								_getch();
								system("cls");
							}
							which = '1';
						break;
						}
						
						// displays translations to enter word

						case '1': {
							randint = rand() % words.size();
							cout << polish(translations[randint].c_str()) << " - ";

							getline(cin, input);

							if(input == "e" || input == "E") {
								system("cls");
								cout << polish("Twoja liczba punktów: ") << points << " :)";
								_getch();
								system("cls");

								goto from_exit;
							}

							if(input == polish(words[randint].c_str())) {
								cout << "\nDobrze!\n\n" << polish("Pos³uchaj wymowy: y/n ");

								char f = _getch();

								if(f == 'y') {
									string res = GetSingleString(words[randint]);
									string linkname = "https://www.diki.pl/slownik-angielskiego?q=" + res;
									const char* link = linkname.c_str();

									ShellExecute(0, 0, link, 0, 0, SW_SHOW); 
								}

								points++;
								Sleep(500);
							} else {
								cout << polish("\nle!\n\nPrawid³owe s³ówko: ") << polish(words[randint].c_str()) 
									<< polish("\n\nPos³uchaj wymowy: y/n ");

								char f = _getch();

								if(f == 'y') {
									string res = GetSingleString(words[randint]);
									string linkname = "https://www.diki.pl/slownik-angielskiego?q=" + res;
									const char* link = linkname.c_str();

									ShellExecute(0, 0, link, 0, 0, SW_SHOW); 
								}
								
								points--;
								_getch();
								system("cls");
							}
							which = '0';
						break;
						}
						default: continue;
					}
				}
				break;
			}
			
			//translates word with diki.pl and displays in web browser

			case '4': { 
				system("cls");
				SetConsoleTitle((polish("S³ownik diki.pl")).c_str());
				string word;

				cout << polish("Co przet³umaczyæ? ");
				cin >> word;

				if(word == "e") {
					system("cls");
					break;
				}
				string link = "https://www.diki.pl/slownik-angielskiego?q=" + word;
				const char* war = link.c_str();

				system("cls");
				ShellExecute(0, 0, war, 0, 0, SW_SHOW);
				break; 
			}
				

			case '3': { // word appending
				string word, translation;
				bool is_correct = false;

				SetConsoleTitle((polish("Dodawanie s³ówka")).c_str());

				system("cls");

				char f;

				while(is_correct == false) {
					cout << polish("Podaj s³ówko: ");
					cin >> word;
					cout << polish("\nPodaj t³umaczenie: ");
					cin >> translation;

					system("cls");

					cout << polish("S³ówko: ") << word << polish("\nT³umaczenie: ") << translation 
						<< polish("\n\nCzy jest poprawnie? y/n ");

					f = _getch();

					if(f == 'y' || f == 'Y')
						is_correct = true;
				}
				words = AddWord(word, words);
				translations = AddTranslation(translation, translations);

				// appending new lines to a file

				ofstream words, translations;
				words.open(path_words, ios::app);
				translations.open(path_translations, ios::app);

				if(!words.is_open() || !translations.is_open()) {
					system("cls");
					cout << polish("B³¹d otwarcia pliku. [IO Exception] Zapisano do pamiêci.\n");
				}
				else {
					words << "\n" << word;
					translations << "\n" << translation;
					cout << "\n\nZapisano poprawnie. ";

					words.close();
					translations.close();
				}
			system("cls");
			break;
			}

			case '2': {
				v = '0';
				system("cls");

				SetConsoleTitle((polish("Pokazuj s³ówka")).c_str());

				while(true) {
					//v = _getch();
					if(v == 'e')
						continue;
					else {
						srand( time (NULL));
						int num = rand() % words.size();

						cout << polish(words[num].c_str()) << " - ";
						v = _getch();
					
						if(v == 'e') {
							system("cls");
							break;
						}
					
						cout << polish(translations[num].c_str());
						v = _getch();
					
						if(v == 'e') {
							system("cls");
							break;
						}
						system("cls");
					}
				}
			break;
			}

			case '1': {
				v = '0';
				system("cls");

				SetConsoleTitle((polish("Pokazuj t³umaczenia")).c_str());

				while(true) {
					srand(time(NULL));
					int num = rand() % translations.size();

					cout << polish(translations[num].c_str()) << " - ";
					v = _getch();
					
					if(v == 'e') {
							system("cls");
							break;
						}

					cout << polish(words[num].c_str());
					v = _getch();

					if(v == 'e') {
							system("cls");
							break;
						}
					system("cls"); 
				}
			break;
			}
			default: system("cls"); cout << polish("\nNie ma takiej opcji.\n\n");
		}
	}
	cin.get();
}
