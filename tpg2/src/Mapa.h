#ifndef TP_SIMCITY_MAPA_H
#define TP_SIMCITY_MAPA_H

#include "Tipos.h"

class Mapa {
public:
    Mapa(std::set<Nat> hs, std::set<Nat> vs);
    ~Mapa();

    const std::set<Nat>& horizontales();
    const std::set<Nat>& verticales();

    bool esRio(const Pos& p);
    Mapa operator+(const Mapa& b);

private:
    std::set<Nat> hs;
    std::set<Nat> vs;
};

#endif //TP_SIMCITY_MAPA_H
