#include "aed2_Servidor.h"


aed2_Servidor::aed2_Servidor(): _s() {}


aed2_Servidor::~aed2_Servidor() {
    //for (auto it = _construcciones.begin(); it != _construcciones.end(); ++it) {
    //    delete *it;
    //}
}

void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {
    Mapa m(horizontales, verticales);
    _s.nuevaPartida(j, m);
//    map<Casilla, Construccion>* cs = new map<Casilla, Construccion>{};
//    _construcciones.emplace_back(cs);
//    _pendientes.insert(std::make_pair(j, cs));
}


void aed2_Servidor::agregarCasa(Jugador j, Casilla c) {
    //std::map<Casilla, Construccion>* pend = _pendientes.at(j);
    //std::map<Casilla, Nat> casas = _s.verCasas(j);
    //stt::map<Casilla, Nat> casas = _s.verCasas(j);
    //(*_pendientes.at(j)).insert(make_pair(c, casa));
    _s.agregarCasa(j, c);
}


void aed2_Servidor::agregarComercio(Jugador j, Casilla c) {
    _s.agregarComercio(j, c);
    //(*_pendientes.at(j)).insert(make_pair(c, comercio));
}


void aed2_Servidor::avanzarTurno(Jugador j) {
    //*_pendientes.at(j) = _validarPendientes(j);
    _s.avanzarTurnoPartida(j);
    //map<Casilla, Construccion>* cs = new map<Casilla, Construccion>{};
    //_construcciones.emplace_back(cs);
    //_pendientes.insert(std::make_pair(j, cs));
}


void aed2_Servidor::unir(Jugador j1, Jugador j2) {
    _s.unirPartidas(j1, j2);
    //map<Casilla, Construccion>* cs_j2 = _pendientes.at(j2);
    //for (auto & it : *cs_j2) {
    //    _pendientes.at(j1)->insert(it);
    //}
}


set<int> aed2_Servidor::riosHorizontales(Jugador j) const {
    return _s.verMapa(j).horizontales();
}


set<int> aed2_Servidor::riosVerticales(Jugador j) const {
    return _s.verMapa(j).verticales();
}


set<Casilla> aed2_Servidor::casas(Jugador j) const {
    std::map<Casilla, Nat> cas = _s.verCasas(j);
    //std::map<Casilla, Construccion> pend = _validarPendientes(j);
    std::set<Casilla> res;

    //auto itP = pend.begin();
    //while (itP != pend.end()){
    //    if ((*itP).second == casa) {
    //res.insert((*itP).first);
    //    }
    //    itP++;
    //}

    auto it = cas.begin();
    while (it != cas.end()) {
        //if (!pend.count(it->first)) {
            res.insert(it->first);
        //}
        it++;
    }

    return res;
}


set<Casilla> aed2_Servidor::comercios(Jugador j) const {
    //std::map<Casilla, Construccion> pend = _validarPendientes(j);
    std::map<Casilla, Nat> com = _s.verComercios(j);
    std::set<Casilla> res;

    //auto itP = pend.begin();
    //while (itP != pend.end()) {
    //    if ((*itP).second == comercio) {
    //        res.insert((*itP).first);
    //    }
    //    itP++;
    //}

    auto it = com.begin();
    while (it != com.end()) {
        //if (!pend.count(it->first)) {
            res.insert(it->first);
        //}
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
    } //else if (_pendientes.at(j)->count(c) && _pendientes.at(j)->at(c) == comercio) {
    //    return SimCity::nivelCom(c, casas);
    //}
    return 0; // Posición no definida
}


bool aed2_Servidor::huboConstruccion(Jugador j) const {
    return _s.huboConstruccion(j);//!(*_pendientes.at(j)).empty(); //|| _s.huboUnionConConstrucciones(j);
    //return _s.verTurnos(j) != 1; //????? Si esta vacio el SimCity?
}


Nat aed2_Servidor::popularidad(Jugador j) const {
    return _s.verPopularidad(j);
}


Nat aed2_Servidor::antiguedad(Jugador j) const {
    return _s.verTurnos(j);
}

//std::map<Casilla, Construccion> aed2_Servidor::_validarPendientes(Jugador j) const {
//    std::map<Casilla, Nat> com;
//    std::map<Casilla, Nat> cas;
//    if (_s.huboUnionConConstrucciones(j)) {
//        com = _s.verConstruccionesDeTipo(j, comercio);
//        cas = _s.verConstruccionesDeTipo(j, casa);
//    } else {
//        com = _s.verComercios(j);
//        cas = _s.verCasas(j);
//    }
//    std::map<Casilla, Construccion>* pend = _pendientes.at(j);
//    std::map<Casilla, Construccion> res;
//    for (auto it : *pend) {
//        if (!(com.count(it.first) || cas.count(it.first))) {
//            res.insert(it);
//        }
//    }
//    return res;
//}
//
//
