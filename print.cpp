#include "print.h"
#include "constants.h"

void printSfmlLab(const vector<vector<LabyrinthElem>>& lab, string file, RenderWindow& window, float& frame, float time/*, vector<vector<pair<Sprite, Sprite>>>& labSprites*/) {

    Image im;
	im.loadFromFile("images/" + file);
	Texture tex;
	tex.loadFromImage(im);
	Sprite sp;
	sp.setTexture(tex);

	for (int i = 0; i < lab[0].size(); i++) {
		sp.setTextureRect(IntRect(2, 0, labirintElSize, 1));
		sp.setPosition(i * labirintElSize, 0);
		//labSprites[0][i].first = sp;
		window.draw(sp);
	}
	for (int i = 0; i < lab.size(); i++) {
		sp.setTextureRect(IntRect(0, 0, 1, labirintElSize));
		sp.setPosition(0, i * labirintElSize);
		//labSprites[i + 1][0].second = sp;
		window.draw(sp);

		for (int j = 0; j < lab[i].size(); j++) {
			if (lab[i][j].right != 0) {
				sp.setTextureRect(IntRect(0, 0, 1, labirintElSize));
				sp.setPosition((j + 1) * labirintElSize, i * labirintElSize);
				window.draw(sp);
	
			}
			if (lab[i][j].down != 0) {
				sp.setTextureRect(IntRect(2, 0, labirintElSize, 1));
				sp.setPosition(j * labirintElSize, (i + 1) * labirintElSize);
				window.draw(sp);
	
			}
			if (lab[i][j].coin && (i != lab.size() - 1 || j != lab[0].size() - 1)) {
				printCoin(window, frame, time, i, j);
			}
		}
		sp.setTextureRect(IntRect(0, 0, 1, labirintElSize));
		sp.setPosition(labirintElSize * lab[0].size() - 1, i * labirintElSize - 1);
		window.draw(sp);
	}
    for (int i = 0; i < lab[0].size(); i++) {
		sp.setTextureRect(IntRect(2, 0, labirintElSize, 1));
		sp.setPosition(i * labirintElSize - 1, labirintElSize * lab.size() - 1);
		window.draw(sp);
	}
}

void printFlag(RenderWindow& window, int h, int w, float& frameNowF, float time) {
	Image flagIm;
	flagIm.loadFromFile("images/items.png");
	Texture flagTex;
	flagTex.loadFromImage(flagIm);
	Sprite flag;
	flag.setTexture(flagTex);
	frameNowF += time * 0.005;
	if (frameNowF > 3) frameNowF = 0;
	flag.setTextureRect(IntRect(17 * (int)frameNowF, 0, 15, 18));
	flag.setScale(2, 2);
	flag.setPosition(labirintElSize * (w - 1) + 10, labirintElSize * (h - 1) + 10);
	//flag.setPosition(0, 0);
	window.draw(flag);
}

void printCoin(RenderWindow& window, float& frameNow, float time, int y, int x) {
	Image im;
	im.loadFromFile("images/items.png");
	Texture tex;
	tex.loadFromImage(im);
	Sprite spr;
	spr.setTexture(tex);
	frameNow += time * 0.000005;
	if (frameNow > 2) frameNow = 0;
	spr.setTextureRect(IntRect(15 * (int)frameNow, 20, 14, 14));
	spr.setScale(2, 2);
	spr.setPosition(labirintElSize * x + 10, labirintElSize * y + 10);
	//flag.setPosition(0, 0);
	window.draw(spr);
}

int printGameSfml(RenderWindow& window, Player& pl, vector<vector<LabyrinthElem>>& lab, string file) {
	Clock clock;
	float frameNow = 0;
	float frameNowF = 0;
	float frameC = 0;
	//vector<vector<pair<Sprite, Sprite>>> labirintSprites(rows + 1, vector<pair<Sprite, Sprite>>(columns + 1));

	int cnt = 0;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event e;

		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}
		printFlag(window, lab.size(), lab[0].size(), frameNowF, time);
		printSfmlLab(lab, file, window, frameC, time);
		pl.move(frameNow, time, lab);

		window.draw(pl.spr);
		window.display();
		window.clear();
		if (pl.game == 0) window.close();
	}
	return cnt;
}

int printSkins(RenderWindow& window) {
	int button = 0;

	/*Image blackI, brownI, whiteI;
	blackI.loadFromFile("images/blackCat.png");
	brownI.loadFromFile("images/brownCat.png");
	whiteI.loadFromFile("images/whiteCat.png");
	Texture blackT, brownT, whiteT;
	blackT.loadFromImage(blackI);
	brownT.loadFromImage(brownI);
	whiteT.loadFromImage(whiteI);
	Sprite blackS(blackT), brownS(brownT), whiteS(whiteT), i(blackT);
	blackS.setTextureRect(IntRect(15, 0, 14, 29));
	brownS.setTextureRect(IntRect(15, 0, 14, 29));
	whiteS.setTextureRect(IntRect(15, 0, 14, 29));
	i.setTextureRect(IntRect(51, 2, 3, 3));
	blackS.setPosition(200, 450);
	brownS.setPosition(440, 450);
	whiteS.setPosition(680, 450);
	blackS.setScale(10, 10);
	brownS.setScale(10, 10);
	whiteS.setScale(10, 10);
	i.setScale(20, 20);

	bool a = 0;

	if (IntRect(200, 450, 140, 290).contains(Mouse::getPosition(window))) {
		i.setPosition(200, 450);
		a = 1;
		button = 1;
	}
	else if (IntRect(440, 450, 140, 290).contains(Mouse::getPosition(window))) {
		i.setPosition(440, 450);
		a = 1;
		button = 2;
	}
	else if (IntRect(680, 450, 140, 290).contains(Mouse::getPosition(window))) {
		i.setPosition(680, 450);
		a = 1;
		button = 3;
	}
	window.draw(blackS);
	window.draw(brownS);
	window.draw(whiteS);
	if (a) window.draw(i);*/

	return button;
}

pair<int, string> menu(int& cnt) {
	RenderWindow window(VideoMode(labirintElSize * 20, labirintElSize * 20), "Labirints");
	Image menuIm, buttonsIm;
	menuIm.loadFromFile("images/menuBackground.png");
	buttonsIm.loadFromFile("images/buttons.png");
	Texture menuTex, buttonsTex;
	menuTex.loadFromImage(menuIm);
	buttonsTex.loadFromImage(buttonsIm);
	Sprite background(menuTex), playBut(buttonsTex), skinBut(buttonsTex), difBut(buttonsTex),
		ezBut(buttonsTex), normalBut(buttonsTex), hardBut(buttonsTex), backlight(buttonsTex), back(buttonsTex), backlight2(buttonsTex), coins(buttonsTex);

	//background.setTextureRect(IntRect(240, 240, 480, 480));
	playBut.setTextureRect(IntRect(8, 8, 42, 10));
	skinBut.setTextureRect(IntRect(8, 21, 42, 10));
	difBut.setTextureRect(IntRect(8, 34, 42, 10));
	ezBut.setTextureRect(IntRect(8, 46, 42, 10));
	normalBut.setTextureRect(IntRect(8, 59, 42, 10));
	hardBut.setTextureRect(IntRect(8, 71, 42, 10));
	backlight.setTextureRect(IntRect(7, 83, 44, 12));
	back.setTextureRect(IntRect(8, 97, 27, 10));
	backlight2.setTextureRect(IntRect(7, 109, 29, 12));
	coins.setTextureRect(IntRect(62, 86, 58, 9));

	background.setPosition(0, 0);
	playBut.setPosition(270, 450);
	skinBut.setPosition(270, 590);
	difBut.setPosition(270, 730);
	ezBut.setPosition(270, 260);
	normalBut.setPosition(270, 520);
	hardBut.setPosition(270, 780);
	back.setPosition(45, 45);
	backlight2.setPosition(38, 38);
	coins.setPosition(500, 45);

	//background.setScale(2, 2);
	playBut.setScale(10, 10);
	skinBut.setScale(10, 10);
	difBut.setScale(10, 10);
	ezBut.setScale(10, 10);
	normalBut.setScale(10, 10);
	hardBut.setScale(10, 10);
	backlight.setScale(10, 10);
	back.setScale(7, 7);
	backlight2.setScale(7, 7);
	coins.setScale(7, 7);

	Image blackI, brownI, whiteI;
	blackI.loadFromFile("images/blackCat.png");
	brownI.loadFromFile("images/brownCat.png");
	whiteI.loadFromFile("images/whiteCat.png");
	Texture blackT, brownT, whiteT;
	blackT.loadFromImage(blackI);
	brownT.loadFromImage(brownI);
	whiteT.loadFromImage(whiteI);
	Sprite blackS(blackT), brownS(brownT), whiteS(whiteT), i(blackT);
	blackS.setTextureRect(IntRect(15, 0, 14, 29));
	brownS.setTextureRect(IntRect(15, 0, 14, 29));
	whiteS.setTextureRect(IntRect(15, 0, 14, 29));
	i.setTextureRect(IntRect(51, 2, 3, 3));
	blackS.setPosition(200, 450);
	brownS.setPosition(440, 450);
	whiteS.setPosition(680, 450);
	blackS.setScale(10, 10);
	brownS.setScale(10, 10);
	whiteS.setScale(10, 10);
	i.setScale(20, 20);

	Font font;
	font.loadFromFile("images/font.ttf");
	Text coinsCnt("", font, 63);
	coinsCnt.setColor(Color::White);
	//coinsCnt.setScale(1, 1.5);
	coinsCnt.setPosition(720, 33);

	bool /*isMenu = 1, */isDif = 0, isSk = 0;

	pair<int, string> p{ 0, "whiteCat.png"};

	while (window.isOpen()) {  
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
				return{ -1, "" };
			}
		}
		window.draw(background);
		int button = 0;
		bool a = 0;

		if (isDif) {
			if (IntRect(270, 260, 420, 100).contains(Mouse::getPosition(window))) {
				backlight.setPosition(260, 250);
				window.draw(backlight);
				button = 1;
			}
			else if (IntRect(270, 520, 420, 100).contains(Mouse::getPosition(window))) {
				backlight.setPosition(260, 510);
				window.draw(backlight);
				button = 2;
			}
			else if (IntRect(270, 780, 420, 100).contains(Mouse::getPosition(window))) {
				backlight.setPosition(260, 770);
				window.draw(backlight);
				button = 3;
			}
			else if (IntRect(45, 45, 189, 70).contains(Mouse::getPosition(window))) {
				window.draw(backlight2);
				button = 4;
			}

			if (Mouse::isButtonPressed(Mouse::Left) && button) {
				if (button == 1) {
					p.first = 0;
				}
				else if (button == 2) {
					p.first = 1;
				}
				else if (button == 3) {
					p.first = 2;
				}
				else if (button == 4) isDif = 0;
			}

			window.draw(ezBut);
			window.draw(normalBut);
			window.draw(hardBut);
			window.draw(back);
		}
		else if (isSk) {
			bool a = 0;

			if (IntRect(200, 450, 140, 290).contains(Mouse::getPosition(window))) {
				i.setPosition(200, 450);
				a = 1;
				button = 1;
			}
			else if (IntRect(440, 450, 140, 290).contains(Mouse::getPosition(window))) {
				i.setPosition(440, 450);
				a = 1;
				button = 2;
			}
			else if (IntRect(680, 450, 140, 290).contains(Mouse::getPosition(window))) {
				i.setPosition(680, 450);
				a = 1;
				button = 3;
			}
		    else if (IntRect(45, 45, 189, 70).contains(Mouse::getPosition(window))) {
			    window.draw(backlight2);
			    button = 4;
		    }
			window.draw(blackS);
			window.draw(brownS);
			window.draw(whiteS);
			window.draw(back);
			if (a) window.draw(i);

			if (Mouse::isButtonPressed(Mouse::Left) && button) {
				if (button == 1) {
					p.second = "blackCat.png";
				}
				else if (button == 2) {
					p.second = "brownCat.png";
				}
				else if (button == 3) {
					p.second = "whiteCat.png";
				}
				else if (button == 4) {
					isSk = 0;
				}
			}
		}
		else {
			if (IntRect(270, 450, 420, 100).contains(Mouse::getPosition(window))) {
				backlight.setPosition(260, 440);
				window.draw(backlight);
				button = 1;
			}
			else if (IntRect(270, 590, 420, 100).contains(Mouse::getPosition(window))) {
				backlight.setPosition(260, 580);
				window.draw(backlight);
				button = 2;
			}
			else if (IntRect(270, 730, 420, 100).contains(Mouse::getPosition(window))) {
				backlight.setPosition(260, 720);
				window.draw(backlight);
				button = 3;
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (button == 1) {
					window.close();
					return p;
				}
				else if (button == 2) {
					isSk = 1;
				}
				else if (button == 3){
					isDif = 1;
				}
			}

			window.draw(playBut);
			window.draw(skinBut);
			window.draw(difBut);
		}

		window.draw(coins);
		coinsCnt.setString(to_string(cnt));
		window.draw(coinsCnt);

		window.display();
		window.clear();
	}
}