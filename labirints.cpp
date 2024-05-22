#include <vector>
#include <iomanip>
#include "print.h"
#include "structs.h"
#include "constants.h"

using namespace std;
using namespace sf;

int startGame(int difficult = 0, string skin = "whiteCat.png") {
	Player pl(skin, 1, 20, 20);
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
	/*int dif = 0;
	if (difficulty == "easy" || difficulty == "Easy") dif = 0;
	else if (difficulty == "normal" || difficulty == "Normal") dif = 1;
	else if (difficulty == "hard" || difficulty == "Hard") dif = 2;*/

	int cnt = 0;
	pair<int, string> settings = menu(cnt);

	while (1) {
		cnt += startGame(settings.first, settings.second);
		settings = menu(cnt);
	}
}