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

using namespace std;

using Nat = unsigned int;

using Casilla = pair<int, int>;

using Jugador = string;

using Nombre = string;

enum Direccion {
    Horizontal, Vertical // y, x
};

enum Construccion {
    casa,
    comercio
};

struct Pos {
    Nat x{};
    Nat y{};
};
#endif // TIPOS_H

