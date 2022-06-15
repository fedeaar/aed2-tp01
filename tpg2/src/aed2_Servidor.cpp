#include "aed2_Servidor.h"


aed2_Servidor::aed2_Servidor() {}


aed2_Servidor::~aed2_Servidor() {
    for (auto it = _construcciones.begin(); it != _construcciones.end(); ++it) {
        delete *it;
    }
}

void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {
    Mapa m(horizontales, verticales);
    _s.nuevaPartida(j, m);
    map<Casilla, Construccion>* cs = new map<Casilla, Construccion>{};
    _construcciones.emplace_back(cs);
    _pendientes.insert(std::make_pair(j, cs));
}


void aed2_Servidor::agregarCasa(Jugador j, Casilla c) {
    (*_pendientes.at(j)).insert(make_pair(c, casa));
}


void aed2_Servidor::agregarComercio(Jugador j, Casilla c) {
    (*_pendientes.at(j)).insert(make_pair(c, comercio));
}


void aed2_Servidor::avanzarTurno(Jugador j) {
    _s.avanzarTurnoPartida(j, *_pendientes.at(j));
    map<Casilla, Construccion>* cs = new map<Casilla, Construccion>{};
    _construcciones.emplace_back(cs);
    _pendientes.insert(std::make_pair(j, cs));
}


void aed2_Servidor::unir(Jugador j1, Jugador j2) {
    _s.unirPartidas(j1, j2);
    map<Casilla, Construccion>* cs_j2 = _pendientes.at(j2); // todo check que no haya problemas de complejidad
    // sino pasar a lista
    _pendientes.at(j1)->insert(cs_j2->begin(), cs_j2->end());
}


set<int> aed2_Servidor::riosHorizontales(Jugador j) const {
    return _s.verMapa(j).horizontales();
}


set<int> aed2_Servidor::riosVerticales(Jugador j) const {
    return _s.verMapa(j).verticales();
}


set<Casilla> aed2_Servidor::casas(Jugador j) const {
    std::map<Casilla, Nat> cn = _s.verCasas(j);
    std::map<Casilla, Construccion> pend = *_pendientes.at(j);
    std::set<Casilla> res;

    auto it = cn.begin();
    while (it != cn.end()) {
        res.insert((*it).first);
        it++;
    }

    auto itP = pend.begin();
    while (itP != pend.end()){
        if ((*itP).second == casa) {
            res.insert((*itP).first);
        }
        itP++;
    }

    return res;
}


set<Casilla> aed2_Servidor::comercios(Jugador j) const {
    std::map<Casilla, Nat> cn = _s.verComercios(j);
    std::map<Casilla, Construccion>* pend = _pendientes.at(j);
    std::set<Casilla> res;
    auto it = cn.begin();

    while (it != cn.end()) {
        res.insert((*it).first);
        it++;
    }

    auto itP = (*pend).begin();
    while (itP != (*pend).end()){
        if ((*itP).second == comercio) {
            res.insert((*itP).first);
        }
        itP++;
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
    } else if (_pendientes.at(j)->count(c) && _pendientes.at(j)->at(c) == comercio) {
        return SimCity::nivelCom(c, casas);
    }
    return 0; // Posición no definida
}


bool aed2_Servidor::huboConstruccion(Jugador j) const {
    return !(*_pendientes.at(j)).empty();
    //return _s.verTurnos(j) != 1; //????? Si esta vacio el SimCity?
}


Nat aed2_Servidor::popularidad(Jugador j) const {
    return _s.verPopularidad(j);
}


Nat aed2_Servidor::antiguedad(Jugador j) const {
    return _s.verTurnos(j);
}

