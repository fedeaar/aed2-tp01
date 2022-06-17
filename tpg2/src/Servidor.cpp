#include "Servidor.h"


Servidor::Servidor(): _partidas() {}


Servidor::~Servidor() {
    for (auto it = _partidas.begin(); it != _partidas.end(); ++it) {
        delete it.significado().sc;
    }
}


DiccTrie<SimCity> Servidor::partidas() {
    DiccTrie<SimCity> res{};
    for (auto it = _partidas.begin(); it != _partidas.end(); ++it) {
        res.insert(std::make_pair(it.clave(), *(it.significado().sc)));
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
    _partidas.insert(std::make_pair(n, Partida(m)));
}


void Servidor::unirPartidas(const Nombre& n, const Nombre& m) {
    _partidas.at(n).sc->unir(*_partidas.at(m).sc);
    _partidas.at(m).modificable = false;
}


void Servidor::avanzarTurnoPartida(const Nombre& n) {
    _partidas.at(n).sc->avanzarTurno();
}


void Servidor::agregarCasa(const Nombre& n, const Casilla& p) {
    _partidas.at(n).sc->agregarCasa(p);
}


void Servidor::agregarComercio(const Nombre& n, const Casilla& p) {
    _partidas.at(n).sc->agregarComercio(p);
}


Mapa Servidor::verMapa(const Nombre& n) const {
    return _partidas.at(n).sc->mapa();
}


std::map<Casilla, Nat> Servidor::verCasas(const Nombre& n) const {
    return _partidas.at(n).sc->casas();
}


std::map<Casilla, Nat> Servidor::verComercios(const Nombre& n) const {
    return _partidas.at(n).sc->comercios();
}


Nat Servidor::verPopularidad(const Nombre& n) const {
    return _partidas.at(n).sc->popularidad();
}


Nat Servidor::verTurnos(const Nombre& n) const {
    return _partidas.at(n).sc->turnos();
}


bool Servidor::huboConstruccion(const Nombre &n) const {
    return _partidas.at(n).sc->huboConstruccion();
}


