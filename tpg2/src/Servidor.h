#ifndef TP_SIMCITY_SERVIDOR_H
#define TP_SIMCITY_SERVIDOR_H

#include "Tipos.h"
#include "Mapa.h"
#include "SimCity.h"
#include "DiccTrie.h"

class Servidor {
public:
    Servidor();
    ~Servidor();

    DiccTrie<SimCity> partidas();
    std::set<Nombre> congeladas();

    void nuevaPartida(Nombre n, const Mapa& m);
    void unirPartidas(Nombre n, Nombre m);

    void avanzarTurnoPartida(Nombre n, const std::map<Pos, Construccion>& cs);
    void agregarCasa(Nombre n, const Pos& p);
    void agregarComercio(Nombre n, const Pos& p);

    Mapa verMapa(Nombre n) const;
    std::map<Casilla, Nat> verCasas(Nombre n) const;
    std::map<Casilla, Nat> verComercios(Nombre n) const;
    Nat verPopularidad(Nombre n) const;
    Nat verTurnos(Nombre n) const;

private:
    struct Partida {
        Partida(SimCity* s, bool m): sc(s), modif(m) {};
        SimCity* sc;
        bool modif;
    };
    DiccTrie<Partida> _partida;
};

#endif //TP_SIMCITY_SERVIDOR_H
