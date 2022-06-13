#include "Servidor.h"


// CONSTRUCTOR
Servidor::Servidor(): _partidas() {}


Servidor::~Servidor() {}


// FUNCIONES
DiccTrie<SimCity> Servidor::partidas() {
    DiccTrie<SimCity> res{};
    for (auto it = _partidas.begin(); it != _partidas.end(); ++it) {
        res[it.clave()] = it.significado().sc; //TODO: PENSAR
    }
    return res;
}


std::set<Nombre> Servidor::congeladas() {
    std::set<Nombre> res{};
    for (auto it = _partidas.begin(); it != _partidas.end(); ++it) {
        if (!it.significado().modificable) {
            res.insert(it.clave());
        }
    }
    return res;
}


void Servidor::nuevaPartida(const Nombre& n, const Mapa& m) {
    _partidas[n] = Partida(m);
}


void Servidor::unirPartidas(const Nombre& n, const Nombre& m) {
    _partidas[n].sc.unir(_partidas[m].sc);
}


void Servidor::avanzarTurnoPartida(const Nombre& n, const std::map<Casilla, Construccion>& cs) {
    _partidas[n].sc.avanzarTurno(cs);
}


void Servidor::agregarCasa(const Nombre& n, const Casilla& p) {
    std::map<Casilla, Construccion> cs {};
    cs.insert(std::make_pair(p, casa));
    _partidas[n].sc.avanzarTurno(cs);
}


void Servidor::agregarComercio(const Nombre& n, const Casilla& p) {
    std::map<Casilla, Construccion> cs {};
    cs.insert(std::make_pair(p, comercio));
    _partidas[n].sc.avanzarTurno(cs);
}


Mapa Servidor::verMapa(const Nombre& n) const {
    return _partidas[n].sc.mapa();
}


std::map<Casilla, Nat> Servidor::verCasas(const Nombre& n) const {
    return _partidas[n].sc.casas();
}


std::map<Casilla, Nat> Servidor::verComercios(const Nombre& n) const {
    return _partidas[n].sc.comercios();
}


Nat Servidor::verPopularidad(const Nombre& n) const {
    return _partidas[n].sc.popularidad();
}


Nat Servidor::verTurnos(const Nombre& n) const {
    return _partidas[n].sc.turnos();
}


