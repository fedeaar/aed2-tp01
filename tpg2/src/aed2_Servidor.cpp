#include "aed2_Servidor.h"


aed2_Servidor::aed2_Servidor() {}


void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {
    Mapa m(horizontales, verticales);
    map<Pos, Construccion> cs;
    _s.nuevaPartida(j, m);
    _pendientes.insert(make_pair(j, cs));
}


void aed2_Servidor::agregarCasa(Jugador j, Casilla c) {
    Pos p;
    p.x = c.first;
    p.y = c.second;
    _pendientes.at(j).insert(p, casa);
}


void aed2_Servidor::agregarComercio(Jugador j, Casilla c) {
    Pos p;
    p.x = c.first;
    p.y = c.second;
    _pendientes.at(j).insert(p, comercio);
}


void aed2_Servidor::avanzarTurno(Jugador j) {
    _s.avanzarTurnoPartida(j, _pendientes.at(j));
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
    std::map<Casilla, Nat> cn = _s.verCasas(j);
    std::set<Casilla> res;
    auto it = cn.begin();

    while (it != cn.end()) {
        res.insert((*it).first);
        it++;
    }

    return res;
}


set<Casilla> aed2_Servidor::comercios(Jugador j) const {
    std::map<Casilla, Nat> cn = _s.verComercios(j);
    std::set<Casilla> res;
    auto it = cn.begin();

    while (it != cn.end()) {
        res.insert((*it).first);
        it++;
    }

    return res;
}


Nat aed2_Servidor::nivel(Jugador j, Casilla c) const {
    std::map<Casilla, Nat> casas = _s.verCasas(j);
    if (casas.count(c) == 1) {
        return casas[c];
    }
    std::map<Casilla, Nat> comercios = _s.verComercios(j);
    if (comercios.count(c) == 1) {
        return casas[c];
    }

    return 0; // Posición no definida
}


bool aed2_Servidor::huboConstruccion(Jugador j) const {
    return _s.verTurnos(j) == 1; //????? Si esta vacio el SimCity?
}


Nat aed2_Servidor::popularidad(Jugador j) const {
    return _s.verPopularidad(j);
}


Nat aed2_Servidor::antiguedad(Jugador j) const {
    return _s.verTurnos(j);
}

