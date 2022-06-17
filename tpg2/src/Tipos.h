#ifndef TIPOS_H
#define TIPOS_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <utility>

using namespace std;

using Nat = unsigned int;

using Casilla = std::pair<int, int>;

using Jugador = std::string;

using Nombre = std::string;

enum Direccion {
    Horizontal,
    Vertical
};

enum Construccion {
    casa,
    comercio
};

#endif // TIPOS_H

