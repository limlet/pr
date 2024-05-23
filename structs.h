#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.h"

using namespace std;
using namespace sf;


struct LabyrinthElem { // клетки лабиринта
	bool down, right, tree, coin; //tree это клетки, которые уже входят в дерево
};

class Labirint {
private:
	//Image image;
	//Texture texture;
	//Sprite spr;
public:
	__int64 labWidth, labHigh; //ширина лабиринта, высота лабиринта
	//String file;

	Labirint(int h, int w) {
		labWidth = w;
		labHigh = h;
		//file = f;
		/*image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		spr.setTexture(texture);*/
	}
	vector<vector<LabyrinthElem>> walls; //массив строк, где каждая клетка это наличие стенки снизу и сверху

	void generateBinaryTree();


	void generateStartEl(vector<pair<int, int>>& graph);
	void generateMiddleEl(vector<pair<int, int>>& graph);
	void addToWalls(const vector<pair<int, int>>& graph);

	int findG(pair<int, int> a, const vector<pair<int, int>>& v, int end);

	void print();

	void generateWilson();
};

class Player {
private:
	int w, h;
public:
	Image image;
	Texture texture;
	Sprite spr;
	float x, y;
	float dx = 0, dy = 0, speed = 0;
	int dir = 0;
	bool game = 1;
	int cntC = 0;
	Player(int X, int Y) {
		x = X; y = Y;
		spr.setTextureRect(IntRect(25, 30, -24, 22));
		w = 24;
		h = 22;
	}

	void cat(string f);

	void update(float time);

	void move(float& frameNow, float time, vector<vector<LabyrinthElem>>& lab);

	void interactWithMap(vector<vector<LabyrinthElem>>& lab);

	bool flag(int height, int width);

	bool coin(int y, int x);
};