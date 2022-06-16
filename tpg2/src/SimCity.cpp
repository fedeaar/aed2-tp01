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
    return maximizar(casa);
}

map<Casilla, Nat> SimCity::comercios() const {
    map<Casilla, Nat> casasTotales = casas();
    map<Casilla, Nat> comerciosTotales = maximizar(comercio);
    for (auto it = comerciosTotales.begin(); it != comerciosTotales.end();) {
        if(casasTotales.count(it->first)) {
            comerciosTotales.erase(it->first);
        } else {
            it->second = max(it->second, nivelCom(it->first, casasTotales));
            ++it;
        }
    }
    return comerciosTotales;
}

map<Casilla, Nat> SimCity::maximizar(Construccion tipo) const {
    vector<pair<Casilla, Nat>> planchadas = plancharConstruccion(tipo);
    map<Casilla, Nat> res;
    for(int i = 0; i < planchadas.size(); ++i) {
        Casilla p = planchadas[i].first;
        Nat n = planchadas[i].second;
        if(!res.count(p) || res[p] < n) res[p] = n;
    }
    return res;
}

vector<pair<Casilla, Nat>> SimCity::plancharConstruccion(Construccion tipo) const {
    vector<pair<Casilla, Nat>> res = listDeTipo(tipo);
    for (auto it = _uniones.begin(); it != _uniones.end(); ++it) {
        map<Casilla, Nat> actuales = it->sc->casas();
        for (auto itCs = actuales.begin(); itCs != actuales.end(); ++itCs) {
            res.emplace_back(itCs->first, _turno - it->turnoUnido + itCs->second);
        }
    }
    return res;
}

vector<pair<Casilla, Nat>> SimCity::listDeTipo(Construccion tipo) const {
    vector<pair<Casilla, Nat>> res;
    int i = 0;
    for (auto it = _construcciones.begin(); it != _construcciones.end(); ++it, ++i)
        for (auto itCs = (*it)->begin(); itCs != (*it)->end(); ++itCs) 
            if (itCs->second == tipo) res.emplace_back(itCs->first, _turno - i);
        
    return res;
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
    _construcciones.push_back(new map<Casilla, Construccion>());
}

void SimCity::agregarCasa(Casilla pos) {
    (*_construcciones.back())[pos] = casa;
}

void SimCity::agregarComercio(Casilla pos) {
    (*_construcciones.back())[pos] = comercio;
}

void SimCity::unir(const SimCity& otro) {
    _popularidad = _popularidad + otro._popularidad + 1;
    _antiguedad = max(_antiguedad, otro._antiguedad);
    Hijo nuevoHijo = Hijo(&otro, _turno);
    _uniones.push_back(nuevoHijo);
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
    if (!res && _uniones.size()) {
        SimCity::Hijo ult = _uniones.back();
        res = ult.turnoUnido == _turno && !((ult.sc->_construcciones.back())->empty());
    }
    return res;
}