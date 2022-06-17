#include "aed2_Servidor.h"


aed2_Servidor::aed2_Servidor(): _s() {}


aed2_Servidor::~aed2_Servidor() = default;


void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {
    Mapa m(std::move(horizontales), std::move(verticales));
    _s.nuevaPartida(j, m);
}


void aed2_Servidor::agregarCasa(Jugador j, Casilla c) {
    _s.agregarCasa(j, c);
}


void aed2_Servidor::agregarComercio(Jugador j, Casilla c) {
    _s.agregarComercio(j, c);
}


void aed2_Servidor::avanzarTurno(Jugador j) {
    _s.avanzarTurnoPartida(j);
}


void aed2_Servidor::unir(Jugador j1, Jugador j2) {
    _s.unirPartidas(j1, j2);
}


set<int> aed2_Servidor::riosHorizontales(Jugador j) const {
    return _s.verMapa(j).horizontales();
}


set<int> aed2_Servidor::riosVerticales(Jugador j) const {
    return _s.verMapa(j).verticales();
}


set<Casilla> aed2_Servidor::casas(Jugador j) const {
    std::map<Casilla, Nat> cas = _s.verCasas(j);
    std::set<Casilla> res;

    auto it = cas.begin();
    while (it != cas.end()) {
        res.insert(it->first);
        it++;
    }

    return res;
}


set<Casilla> aed2_Servidor::comercios(Jugador j) const {
    std::map<Casilla, Nat> com = _s.verComercios(j);
    std::set<Casilla> res;

    auto it = com.begin();
    while (it != com.end()) {
        res.insert(it->first);
        it++;
    }

    return res;
}


Nat aed2_Servidor::nivel(Jugador j, Casilla c) const {
    std::map<Casilla, Nat> casas = _s.verCasas(j);
    if (casas.count(c)) {
        return casas.at(c);
    }
    std::map<Casilla, Nat> comercios = _s.verComercios(j);
    if (comercios.count(c)) {
        return comercios.at(c);
    }
    return 0; // Posición no definida
}


bool aed2_Servidor::huboConstruccion(Jugador j) const {
    return _s.huboConstruccion(j);
}


Nat aed2_Servidor::popularidad(Jugador j) const {
    return _s.verPopularidad(j);
}


Nat aed2_Servidor::antiguedad(Jugador j) const {
    return _s.verTurnos(j);
}
