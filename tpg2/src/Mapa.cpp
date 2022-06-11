#include "Mapa.h"
#include "Tipos.h"


Mapa::Mapa(std::set<int> hs, std::set<int> vs) : _hs(hs), _vs(vs) {}


Mapa::~Mapa() {}


const std::set<int>& Mapa::horizontales() const{
    return _hs;
}


const std::set<int>& Mapa::verticales() const{
    return _vs;
}


bool Mapa::esRio(const Pos& p) {
    return _hs.count(p.y) == 1 || _vs.count(p.x) == 1;
}


Mapa Mapa::operator+(const Mapa& b) {
    Mapa res(_hs, _vs);
    const std::set<int>& bHor = b.horizontales();
    const std::set<int>& bVer = b.verticales();

    auto it = bHor.begin();
    while (it != bHor.end()) {
        res._hs.insert(*it);
        it++;
    }

    it = bVer.begin();
    while (it != bVer.end()) {
        res._vs.insert(*it);
        it++;
    }

    return res;
}