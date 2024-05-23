#include <vector>
#include <iomanip>
#include "print.h"
#include "structs.h"
#include "constants.h"
#include "players.h"

using namespace std;
using namespace sf;

int startGame(int difficult, Player& pl) {
	if (difficult == 0) {
		RenderWindow window(VideoMode(labirintElSize * labWEasy, labirintElSize * labHEasy), "Labirints");
		Labirint lab(labHEasy, labWEasy);
		lab.generateBinaryTree();
		return printGameSfml(window, pl, lab.walls, "123.png");
	}
	else if (difficult == 1) {
		RenderWindow window(VideoMode(labirintElSize * labWNormal, labirintElSize * labHNormal), "Labirints");
		Labirint lab(labHNormal, labWNormal);
		lab.generateWilson();
		return printGameSfml(window, pl, lab.walls, "123.png");
	}
	else {
		RenderWindow window(VideoMode(labirintElSize * labWHard, labirintElSize * labHHard), "Labirints");
		Labirint lab(labHHard, labWHard);
		lab.generateWilson();
		return printGameSfml(window, pl, lab.walls, "123.png");
	}
}

int main() {
	srand(time(0));
	int cnt = 0;

	pair<int, string> settings = menu(cnt);

	if (settings.first == -1) return 0;

	Player pl(20, 20);
	pl.cat(settings.second);

	string name;
	map<string, int> players = file();
	//map<string, int> m1 = players;
	signIn(players, pl, name);

	while (1) {
		if (settings.first == -1) break;
		pl.cat(settings.second);
		pl.game = 1;
		pl.x = 20, pl.y = 20;
		cnt += startGame(settings.first, pl);
		settings = menu(pl.cntC);
	}
	file2(players, name, pl);
}