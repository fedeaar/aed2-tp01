#include "Mapa.h"


Mapa::Mapa(std::set<Nat> hs, std::set<Nat> vs) {}


Mapa::~Mapa() {}


const std::set<Nat>& Mapa::horizontales() {}


const std::set<Nat>& Mapa::verticales() {}


bool Mapa::esRio(const Pos& p) {}


Mapa Mapa::operator+(const Mapa& b) {}