#include "SimCity.h"

SimCity::SimCity(Mapa m) : _mapa(m) {
    _turno = 0;
    _antiguedad = 0;
    _popularidad = 0;
}

SimCity::SimCity(const SimCity& aCopiar) {
        _turno = aCopiar._turno;
        _antiguedad = aCopiar._antiguedad;
        _popularidad = aCopiar._popularidad;
        _construcciones = aCopiar._construcciones;
        _mapa = aCopiar._mapa;
        _uniones = aCopiar._uniones; //los struct tienen funcion de copiado?
}

SimCity::~SimCity() {}

Mapa SimCity::mapa() const {
    Mapa res = _mapa;
    for (auto it = _uniones.begin(); it != _uniones.end(); ++it) {
        res = res + (it->sc)->mapa();
    }
    return res;
}

std::map<Casilla, Nat> SimCity::casas() const {
    map<Casilla, Nat> res = listDeTipo(casa);
    map<Casilla, Nat> comerciosTotales = listDeTipo(comercio);
    for (auto it = _uniones.begin(); it != _uniones.end(); ++it) {
        map<Casilla, Nat> casasActuales = it->sc->casas();
        for (auto itCs = casasActuales.begin(); itCs != casasActuales.end(); ++itCs) {
            const Casilla p = itCs->first;
            const Nat n = itCs->second;
            if (!res.count(p) && !comerciosTotales.count(p)) {
                res[p] = _turno - it->turnoUnido + n;
            }
        }
        comerciosTotales = comerciosTotales + it->sc->listDeTipo("comercio");
    }
    return res;
}

std::map<Casilla, Nat> SimCity::comercios() const {}

Nat SimCity::popularidad() const {
    return _popularidad;
}

Nat SimCity::turnos() const {
    return _turno;
}

void SimCity::avanzarTurno(const std::map<Casilla, Construccion>& cs) {
    _turno++;
    _antiguedad++;
    _construcciones.push_back(&cs);  // tengo quilombo con el const por aliasing
}

void SimCity::unir(const SimCity& otro) {
    _popularidad = _popularidad + otro._popularidad + 1;
    _antiguedad = max(_antiguedad, otro._antiguedad);
    Hijo nuevoHijo = Hijo(&otro, _turno);  // tengo quilombo con el const por aliasing
    _uniones.push_back(nuevoHijo);
}

map<Casilla, Nat> SimCity::listDeTipo(Construccion tipo) const {
    map<Casilla, Nat> res;
    int i = 1; //tiene que empezar en 1
    for (auto it = _construcciones.begin(); it != _construcciones.end(); ++it) {
        for (auto itCs = (*it)->begin(); itCs != (*it)->end(); ++itCs) {
            if (itCs->second == tipo) res[itCs->first] = _turno - i;
        }
        ++i;
    }
}
