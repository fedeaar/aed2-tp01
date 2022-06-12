#ifndef TP_SIMCITY_SERVIDOR_H
#define TP_SIMCITY_SERVIDOR_H

#include "Tipos.h"
#include "Mapa.h"
#include "SimCity.h"
#include "DiccTrie.h"

class Servidor {

// FUNCIONALIDAD SERVIDOR
public:

    /**
     CONSTRUCTOR
     * crea un nuevo servidor.
     * Complejidad: O(1)
     **/
    Servidor();

    /**
     DESTRUCTOR
     **/
    ~Servidor();

    /**
     PARTIDAS
     * retorna una copia de las partidas en el SimCity.
     * Complejidad: O(SUM(i=0, N, copy(SimCity_i))
     **/ //TODO: CHECK complejidad / cambiar implementacion del iterador
    DiccTrie<SimCity> partidas();

    /**
     CONGELADAS
     * retorna el conjunto de Nombres de las partidas congeladas.
     * Complejidad: O(N)  donde N es la cantidad de partidas definidas
     */ //TODO: CHECK complejidad / cambiar implementacion del iterador
    std::set<Nombre> congeladas();

    /**
     NUEVA PARTIDA
     * crea una nueva partida de SimCity.
     * Complejidad: O(copy(Mapa))    TODO: CHECK
     **/
    void nuevaPartida(const Nombre& n, const Mapa& m);

    /**
     UNIR PARTIDAS
     * une dos partidas de SimCity.
     * Complejidad: O(claveMasLarga)
     */
    void unirPartidas(const Nombre& n, const Nombre& m);

    /**
     AVANZAR TURNO
     * avanza un turno de SimCity.
     * Complejidad: O(claveMasLarga)
     **/
    void avanzarTurnoPartida(const Nombre& n, const std::map<Casilla, Construccion>& cs);

    /**
     AGREGAR CASA
     * agrega una casa al SimCity y pasa de turno.
     * Complejidad: O(claveMasLarga)
     **/
    void agregarCasa(const Nombre& n, const Casilla& p);


    /**
     AGREGAR COMERCIO
     * agrega un comercio al SimCity y pasa de turno.
     * Complejidad: O(claveMasLarga)
     **/
    void agregarComercio(const Nombre& n, const Casilla& p);

    /**
     VER MAPA
     * crea una copia del mapa en el SimCity.
     * Complejidad: O(claveMasLarga + simCity::mapa())
     **/
    Mapa verMapa(const Nombre& n) const;

    /**
     VER CASAS
     * crea una copia de las casas en el SimCity.
     * Complejidad: O(claveMasLarga + simCity::casas())
     **/
    std::map<Casilla, Nat> verCasas(const Nombre& n) const;

    /**
     VER COMERCIOS
     * crea una copia de los comercios en el SimCity.
     * Complejidad: O(claveMasLarga + simCity::comercios())
     **/
    std::map<Casilla, Nat> verComercios(const Nombre& n) const;

    /**
     VER POPULARIDAD
     * muestra la popularidad de una Partida.
     * Complejidad: O(claveMasLarga)
     **/
    Nat verPopularidad(const Nombre& n) const;

    /**
     VER TURNOS
     * muestra el turno actual de una Partida.
     * Complejidad: O(claveMasLarga)
     **/
    Nat verTurnos(const Nombre& n) const;


// ESTRUCTURA Y AUX
private:

    struct Partida {
        explicit Partida(const Mapa& m): sc(SimCity(m)), modificable(false) {};
        SimCity sc;
        bool modificable;
    };

    DiccTrie<Partida> _partidas;
};

#endif //TP_SIMCITY_SERVIDOR_H
