#include "Mapa.h"


Mapa::Mapa(std::set<int> hs, std::set<int> vs) : _hs(std::move(hs)), _vs(std::move(vs)) {}


Mapa::~Mapa() = default;


bool Mapa::operator==(const Mapa &otro) const {
    return _hs == otro._hs && _vs == otro._vs;
}


const std::set<int>& Mapa::horizontales() const {
    return _hs;
}


const std::set<int>& Mapa::verticales() const {
    return _vs;
}


bool Mapa::esRio(const Casilla& c) {
    return _hs.count(c.second) || _vs.count(c.first);
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

