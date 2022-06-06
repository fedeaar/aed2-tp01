#include "Mapa.h"
#include "Tipos.h"


Mapa::Mapa(std::set<Nat> hs, std::set<Nat> vs) : _hs(hs), _vs(vs) {}


Mapa::~Mapa() {}


const std::set<Nat>& Mapa::horizontales() const{
    return _hs;
}


const std::set<Nat>& Mapa::verticales() const{
    return _vs;
}


bool Mapa::esRio(const Pos& p) {
    return _hs.count(p.y) == 1 || _vs.count(p.x) == 1;
}


Mapa Mapa::operator+(const Mapa& b) {
    Mapa res(_hs, _vs);

    auto it = b.horizontales().begin();
    while (it != b.horizontales().end()) {
        res._hs.insert(*it);
        it++;
    }

    it = b.verticales().begin();
    while (it != b.verticales().end()) {
        res._vs.insert(*it);
        it++;
    }

    return res;
}