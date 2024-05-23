#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "structs.h"

using namespace std;
using namespace sf;

void signIn(map<string, int>& m, Player& pl, string& nm);
map<string, int> file();
void file2(map<string, int> m, string name, Player pl);