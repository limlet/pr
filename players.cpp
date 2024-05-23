#include "players.h"

map<string, int> file() {
	ifstream fin("players.txt");
	map<string, int> m;
	string name;
	while (fin >> name) {
		int a; fin >> a;
		m[name] = a;
	}
	return m;
}

void file2(map<string, int> m, string name, Player pl) {
	fstream clearFile("players.txt", ios::out);
	clearFile.close();
	ofstream fout("players.txt");
	for (auto p : m) {
		if (p.first == name) {
			fout << name << ' ' << pl.cntC << endl;
		}
		else fout << p.first << ' ' << p.second << endl;
	}
}

void signIn(map<string, int>& m, Player& pl, string& nm) {
	RenderWindow window(VideoMode(labirintElSize * 20, labirintElSize * 20), "Labirints");
	Image backIm, buttonsIm;
	backIm.loadFromFile("images/menuBackground.png");
	buttonsIm.loadFromFile("images/buttons.png");
	Texture backTex, buttonsTex;
	backTex.loadFromImage(backIm);
	buttonsTex.loadFromImage(buttonsIm);
	Sprite background(backTex), enterName(buttonsTex), ready(buttonsTex), ready2(buttonsTex);

	enterName.setTextureRect(IntRect(62, 98, 50, 9));
	ready.setTextureRect(IntRect(62, 109, 30, 10));
	ready2.setTextureRect(IntRect(62, 120, 32, 12));

	background.setPosition(0, 0);
	enterName.setPosition(270, 300);
	ready.setPosition(270, 520);
	ready2.setPosition(260, 510);

	enterName.setScale(10, 10);
	ready.setScale(10, 10);
	ready2.setScale(10, 10);

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}
		window.draw(background);
		int button = 0;
		if (IntRect(270, 520, 300, 100).contains(Mouse::getPosition(window))) {
			window.draw(ready2);
			button = 1;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (button == 1) {
				window.draw(enterName);
				window.draw(ready);

				window.display();
				string name; cin >> name;
				if (m.count(name) != 0) {
					pl.cntC = m[name];
				}
				else {
					m[name] = 0;
				}
				nm = name;
			    window.close();
			}
		}

		window.draw(enterName);
		window.draw(ready);

		window.display();
		window.clear();
	}
}