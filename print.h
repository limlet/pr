#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "structs.h"

using namespace std;
using namespace sf;

void printFlag(RenderWindow& window, int h, int w, float& frameNowF, float time);
void printCoin(RenderWindow& window, float& frameNow, float time, int y, int x);

void printSfmlLab(const vector<vector<LabyrinthElem>>& lab, string file, RenderWindow& window, float& frame, float time/*, vector<vector<pair<Sprite, Sprite>>>& labSprites*/);
int printGameSfml(RenderWindow& window, Player& pl, vector<vector<LabyrinthElem>>& lab, string file);
pair<int, string> menu(int& cnt);