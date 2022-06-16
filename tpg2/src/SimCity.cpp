#include "SimCity.h"

SimCity::SimCity(Mapa m): _mapa(m), _turno(0), _antiguedad(0), _popularidad(0), _construcciones() {
    _construcciones.push_back(new map<Casilla, Construccion>());
}

SimCity::~SimCity() {
    // no recursivo, los hijos se tienen que manejar por su cuenta.
    for (auto it : _construcciones) {
        delete it;
    }
}

SimCity& SimCity::operator=(const SimCity& aCopiar) {
    _turno = aCopiar._turno;
    _antiguedad = aCopiar._antiguedad;
    _popularidad = aCopiar._popularidad;
    _construcciones = aCopiar._construcciones;  // indef
    _mapa = aCopiar._mapa;  // indef
    _uniones = aCopiar._uniones;  // los struct tienen funcion de copiado? no para los punteros
    return *this;
}

Mapa SimCity::mapa() const {
    Mapa res = _mapa;
    for (auto it = _uniones.begin(); it != _uniones.end(); ++it) {
        res = res + (it->sc)->mapa();
    }
    return res;
}

map<Casilla, Nat> SimCity::casas() const {
    map<Casilla, Nat> res = listDeTipo(casa);
    map<Casilla, Nat> comerciosTotales = listDeTipo(comercio);
    for (auto it = _uniones.begin(); it != _uniones.end(); ++it) {
        map<Casilla, Nat> casasActuales = it->sc->casas();
        for (auto itCs = casasActuales.begin(); itCs != casasActuales.end(); ++itCs) {
            const Casilla p = itCs->first;
            const Nat n = itCs->second;
            if ((!res.count(p) /*edit*/|| res.at(p) < n) && (!comerciosTotales.count(p) || comerciosTotales.at(p) < n)) {
                res[p] = _turno - it->turnoUnido + n;
            }
        }
        map<Casilla, Nat> comerciosActuales = it->sc->listDeTipo(comercio);
        comerciosTotales.insert(comerciosActuales.begin(), comerciosActuales.end());
    }
    return res;
}

map<Casilla, Nat> SimCity::comercios() const {
    map<Casilla, Nat> casasTotales = casas();
    map<Casilla, Nat> comerciosTotales = comerciosAux(casasTotales);
    manhatizar(comerciosTotales, casasTotales);
    return comerciosTotales;
}

Nat SimCity::popularidad() const {
    return _popularidad;
}

Nat SimCity::turnos() const {
    return _antiguedad;
}

void SimCity::avanzarTurno() {
    _turno++;
    _antiguedad++;
    _construcciones.push_back(new map<Casilla, Construccion>());  // tengo quilombo con el const por aliasing
}

void SimCity::agregarCasa(Casilla pos) {
    _construcciones.back()->insert(std::make_pair(pos, casa));
}

void SimCity::agregarComercio(Casilla pos) {
    _construcciones.back()->insert(std::make_pair(pos, comercio));
}

void SimCity::unir(const SimCity& otro) {
    _popularidad = _popularidad + otro._popularidad + 1;
    _antiguedad = max(_antiguedad, otro._antiguedad);
    Hijo nuevoHijo = Hijo(&otro, _turno);  // tengo quilombo con el const por aliasing
    _uniones.push_back(nuevoHijo);
}

map<Casilla, Nat> SimCity::listDeTipo(Construccion tipo) const {
    map<Casilla, Nat> res;
    int i = 0;  // tiene que empezar en 1
    for (auto it = _construcciones.begin(); it != _construcciones.end(); ++it, ++i)
        for (auto itCs = (*it)->begin(); itCs != (*it)->end(); ++itCs)
            if (itCs->second == tipo) res[itCs->first] = _turno - i;
    return res;
}

map<Casilla, Nat> SimCity::comerciosAux(const map<Casilla, Nat>& casasTotales) const{
    map<Casilla, Nat> res = listDeTipo(comercio);
    for (auto it = _uniones.begin(); it != _uniones.end(); ++it) {
        map<Casilla, Nat> comerciosActuales = it->sc->comercios();
        for (auto itCs = comerciosActuales.begin(); itCs != comerciosActuales.end(); ++itCs) {
            const Casilla p = itCs->first;
            const Nat n = itCs->second;
            if ((!res.count(p) /*edit*/|| res.at(p) < n) && (!casasTotales.count(p) || casasTotales.at(p) < n)) {
                res[p] = _turno - it->turnoUnido + n;
            }
        }
    }
    return res;
}
void SimCity::manhatizar(map<Casilla, Nat>& comercios, const map<Casilla, Nat>& casasTotales) const {
    for (auto it = comercios.begin(); it != comercios.end(); ++it)
        it->second = max(it->second, nivelCom(it->first, casasTotales));
}

Nat SimCity::nivelCom(Casilla p, const map<Casilla, Nat>& cs) {
    Nat maxLvl = 0;
    for (int i = -3; i <= 3; ++i) {
        for (int j = abs(i) - 3; j <= 3 - abs(i); ++j) {
            Casilla p2(p.first + i, p.second + j);
            if (cs.count(p2)) {
                maxLvl = max(maxLvl, cs.find(p2)->second);
            }
        }
    }
    return maxLvl;
}

bool SimCity::huboConstruccion() const {
    bool res = !(_construcciones.back()->empty());
    if (!res) {
        SimCity::Hijo ult = _uniones.back();
        res = ult.turnoUnido == _turno && !((ult.sc->_construcciones.back())->empty());
    }
    return res;
}