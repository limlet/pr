#include "structs.h"

void Labirint::generateBinaryTree() {
	walls.resize(labHigh, vector<LabyrinthElem>(labWidth, { 1, 1, 1, 0 }));// down = 1 right = 1 tree = 1, coin = 0, 1 - есть стена, 0 - нету стены, здесть tree не надо
	for (int i = 0; i < labHigh; i++) {
		int cnt = 0;
		for (int j = 0; j < labWidth; j++) {

			if (i == 0 && j == labWidth - 1) {
				walls[i][j].down = 0;
			}
			else if (i == labHigh - 1) {
				if (j != labWidth - 1) walls[i][j].right = 0;
			}
			else if (j == labWidth - 1) {
				//if (rand() % 25 < 5 && walls[i - 1][j].down == 0) walls[i][j].down = 1;
				walls[i][j].down = 0;
			}
			else {
				walls[i][j].down = rand() % 2;
				if (walls[i][j].down) walls[i][j].right = 0;
			}
		}
	}
}

void Labirint::generateStartEl(vector<pair<int, int>>& graph) {
	graph.push_back({ rand() % (int)labHigh, rand() % (int)labWidth });
	while (walls[graph.back().first][graph.back().second].tree) {
		graph[0] = { rand() % (int)labHigh, rand() % (int)labWidth };
	}
}
void Labirint::generateMiddleEl(vector<pair<int, int>>& graph) {
	vector<int> shiftY{ -1, 0, 0, 1 }, shiftX{ 0, -1, 1, 0 };
	if (graph.back().first != 0 && graph.back().second == 0 && graph.back().first != labHigh - 1) {
		shiftY = { -1, 0, 1 };
		shiftX = { 0, 1, 0 };
	}
	else if (graph.back().first == 0 && graph.back().second != 0 && graph.back().second != labWidth - 1) {
		shiftY = { 0, 0, 1 };
		shiftX = { -1, 1, 0 };
	}
	else if (graph.back().first == labHigh - 1 && graph.back().second != 0 && graph.back().second != labWidth - 1) {
		shiftY = { 0, -1, 0 };
		shiftX = { -1, 0, 1 };
	}
	else if (graph.back().second == labWidth - 1 && graph.back().first != 0 && graph.back().first != labHigh - 1) {
		shiftY = { -1, 0, 1 };
		shiftX = { 0, -1, 0 };
	}
	else if (graph.back().first == 0 && graph.back().second == 0) {
		shiftY = { 0, 1 };
		shiftX = { 1, 0 };
	}
	else if (graph.back().first == labHigh - 1 && graph.back().second == 0) {
		shiftY = { -1, 0 };
		shiftX = { 0, 1 };
	}
	else if (graph.back().first == 0 && graph.back().second == labWidth - 1) {
		shiftY = { 0, 1 };
		shiftX = { -1, 0 };
	}
	else if (graph.back().first == labHigh - 1 && graph.back().second == labWidth - 1) {
		shiftY = { 0, -1 };
		shiftX = { -1, 0 };
	}
	int sh = rand() % shiftY.size();
	graph.push_back({ graph.back().first + shiftY[sh], graph.back().second + shiftX[sh] });
}
void Labirint::addToWalls(const vector<pair<int, int>>& graph) {
	for (int i = 0; i < graph.size(); i++) {
		if (i != graph.size() - 1 && graph[i].first - graph[i + 1].first == -1) walls[graph[i].first][graph[i].second].down = 0;
		if (i != graph.size() - 1 && graph[i].second - graph[i + 1].second == -1) walls[graph[i].first][graph[i].second].right = 0;
		if (i != 0 && graph[i].first - graph[i - 1].first == -1) walls[graph[i].first][graph[i].second].down = 0;
		if (i != 0 && graph[i].second - graph[i - 1].second == -1) walls[graph[i].first][graph[i].second].right = 0;
		walls[graph[i].first][graph[i].second].tree = 1;
	}
	walls[graph[0].first][graph[0].second].coin = 1;
}

int Labirint::findG(pair<int, int> a, const vector<pair<int, int>>& v, int end) {
	for (int i = 0; i < end; i++) {
		if (v[i] == a) return i;
	}
	return -1;
}

void Labirint::print() {
	for (int i = 0; i < labWidth; i++) cout << " _";
	cout << endl;
	for (const auto& row : walls) {
		cout << '|';
		for (const auto& el : row) {
			if (el.down == 0) cout << ' ';
			else cout << '_';
			if (el.right == 0) cout << ' ';
			else cout << '|';
		}
		cout << endl;
	}
}

void Labirint::generateWilson() {
	walls.resize(labHigh, vector<LabyrinthElem>(labWidth, { 1, 1, 0, 0 })); // down = 1, right = 1, tree = 0, coin = 0, 1 - есть стена, 0 - нету стены
	vector<pair<int, int>> graph;
	long long cnt = 1;
	walls[rand() % (int)labHigh][rand() % (int)labWidth].tree = 1;
	while (cnt < labHigh * labWidth) {
		generateStartEl(graph);
		while (!walls[graph.back().first][graph.back().second].tree) {
			generateMiddleEl(graph);
			if (find(graph.begin(), graph.end(), graph.back()) == graph.begin()) {
				graph.pop_back();
			}
			else if (find(graph.begin(), graph.end(), graph.back()) != graph.end() - 1) {
				graph.erase(find(graph.begin(), graph.end(), graph.back()), graph.end());
			}
		}
		addToWalls(graph);
		cnt += graph.size() - 1;
		graph.clear();
	}
}

void Player::update(float time) {
	dx = 0; dy = 0;
	switch (dir) {
	case 0: dx = speed; break;
	case 1: dx = -speed; break;
	case 2: dy = speed; break;
	case 3: dy = -speed; break;
	}
	x += dx * time;
	y += dy * time;
	speed = 0;
	spr.setPosition(x, y);
}

void Player::move(float& frameNow, float time, vector<vector<LabyrinthElem>>& lab, int& cnt) {
	if ((Keyboard::isKeyPressed(Keyboard::A))) {
        dir = 1; speed = 0.1;
		frameNow += time * 0.005;
		if (frameNow > 3) frameNow = 0;
		spr.setTextureRect(IntRect((int)frameNow * 26, 30, 24 + ((int)frameNow == 2) * 3, 22));
		w = 14;
		h = 22;
	}
	if ((Keyboard::isKeyPressed(Keyboard::D))) {
		dir = 0; speed = 0.1;
		frameNow += time * 0.005;
		if (frameNow > 3) frameNow = 0;
		spr.setTextureRect(IntRect(((int)frameNow + 1) * 25 + ((int)frameNow == 2) * 4, 30, -24 - ((int)frameNow == 2) * 4, 22));
		w = 24 + ((int)frameNow == 2) * 3;
		h = 22;
	}
	if ((Keyboard::isKeyPressed(Keyboard::W))) {
		dir = 3; speed = 0.1;
		frameNow += time * 0.005;
		if (frameNow > 3) frameNow = 0;
		spr.setTextureRect(IntRect((int)frameNow * 15, 54, 13, 23));
		w = 13;
		h = 23;
	}
	if ((Keyboard::isKeyPressed(Keyboard::S))) {
		dir = 2; speed = 0.1;
		frameNow += time * 0.005;
		if (frameNow > 3) frameNow = 0;
		spr.setTextureRect(IntRect(14 * (int)frameNow + (int)frameNow, 0, 14, 27));
		w = 14;
		h = 27;
	}
	interactWithMap(lab, cnt);
	update(time);
}

bool Player::flag(int height, int width) {
	if (x >= labirintElSize * (width - 1) + 10 && x <= labirintElSize * (width - 1) + 25
		&& y >= labirintElSize * (height - 1) + 10 && y <= labirintElSize * (height - 1) + 28) return 1;
	else if (x + w >= labirintElSize * (width - 1) + 10 && x + w <= labirintElSize * (width - 1) + 25
		&& y >= labirintElSize * (height - 1) + 10 && y <= labirintElSize * (height - 1) + 28) return 1;
	else if (x >= labirintElSize * (width - 1) + 10 && x <= labirintElSize * (width - 1) + 25
		&& y + h >= labirintElSize * (height - 1) + 10 && y + h <= labirintElSize * (height - 1) + 28) return 1;
	else if (x + w >= labirintElSize * (width - 1) + 10 && x + w <= labirintElSize * (width - 1) + 25
		&& y + h >= labirintElSize * (height - 1) + 10 && y + h <= labirintElSize * (height - 1) + 28) return 1;
	return 0;
}

bool Player::coin(int i, int j) {
	if (x >= j * labirintElSize + 10 && x <= labirintElSize * j + 25
		&& y >= labirintElSize * i + 10 && y <= labirintElSize * i + 28) return 1;
	else if (x + w >= labirintElSize * j + 10 && x + w <= labirintElSize * j + 25
		&& y >= labirintElSize * i + 10 && y <= labirintElSize * i + 28) return 1;
	else if (x >= labirintElSize * j + 10 && x <= labirintElSize * j + 25
		&& y + h >= labirintElSize * i + 10 && y + h <= labirintElSize * i + 28) return 1;
	else if (x + w >= labirintElSize * j + 10 && x + w <= labirintElSize * j + 25
		&& y + h >= labirintElSize * i + 10 && y + h <= labirintElSize * i + 28) return 1;
	return 0;
}

void Player::interactWithMap(vector<vector<LabyrinthElem>>& lab, int& cnt) {
	for (int i = y / labirintElSize; i < (y + h) / labirintElSize && i < lab.size(); i++) {
		for (int j = x / labirintElSize; j < (x + h) / labirintElSize && j < lab[i].size(); j++) {
			if (dy < 0 && lab[i][j].down && y + h > (i + 1) * labirintElSize) y = i * labirintElSize + labirintElSize;
			else if (dx < 0 && lab[i][j].right && x + w > (j + 1) * labirintElSize) x = (j + 1) * labirintElSize;
			else if (dx > 0 && x + w >= (j + 1) * labirintElSize && lab[i][j].right) x = (j + 1) * labirintElSize - w;
			else if (dy > 0 && y + h >= (i + 1) * labirintElSize && lab[i][j].down) y = (i + 1) * labirintElSize - h;

			//coins

			if (lab[i][j].coin && coin(i, j)) {
				lab[i][j].coin = 0;
				cnt++;
			}
		}
	}
	if (y < 0) y = 0;
	if (x < 0) x = 0;
	if (x >= lab[0].size() * labirintElSize) x = (lab[0].size() - 1) * labirintElSize;
	if (y >= lab.size() * labirintElSize) y = (lab.size() - 1) * labirintElSize;

	//flag.setTextureRect(IntRect(17 * (int)frameNowF, 0, 15, 18));
	//flag.setPosition(labirintElSize * (w - 1) + 10, labirintElSize * (h - 1) + 10);

	if (flag(lab.size(), lab[0].size())) {
		game = 0;
	}
}