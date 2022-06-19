#ifndef TP_SIMCITY_SERVIDOR_H
#define TP_SIMCITY_SERVIDOR_H

#include "Tipos.h"
#include "Mapa.h"
#include "SimCity.h"
#include "DiccTrie.h"


class Servidor {

public:

    /**
     CONSTRUCTOR
     * Crea un nuevo servidor.
     * Complejidad: O(1)
     **/
    Servidor();

    /**
     DESTRUCTOR
     **/
    ~Servidor();

    /**
     PARTIDAS
     * Retorna una copia de las partidas en el SimCity.
     * Complejidad: O(SUM(i=0; N; copy(SimCity_i))
     -- PRODUCE ALIASING con las uniones --
     **/
    DiccTrie<SimCity> partidas();

    /**
     CONGELADAS
     * Retorna el conjunto de Nombres de las partidas congeladas.
     * Complejidad: O(N)  donde N es la cantidad de partidas definidas
     **/
    std::set<Nombre> congeladas();

    /**
     NUEVA PARTIDA
     * Crea una nueva partida de SimCity.
     * Complejidad: O(copy(Mapa) + claveMasLarga)
     **/
    void nuevaPartida(const Nombre& n, const Mapa& m);

    /**
     UNIR PARTIDAS
     * Une dos partidas de SimCity.
     * Complejidad: O(claveMasLarga)
     */
    void unirPartidas(const Nombre& n, const Nombre& m);

    /**
     AVANZAR TURNO
     * Avanza un turno de SimCity.
     * Complejidad: O(claveMasLarga)
     **/
    void avanzarTurnoPartida(const Nombre& n);

    /**
     AGREGAR CASA
     * Agrega una casa al SimCity y pasa de turno.
     * Complejidad: O(claveMasLarga)
     **/
    void agregarCasa(const Nombre& n, const Casilla& p);


    /**
     AGREGAR COMERCIO
     * Agrega un comercio al SimCity y pasa de turno.
     * Complejidad: O(claveMasLarga)
     **/
    void agregarComercio(const Nombre& n, const Casilla& p);

    /**
     VER MAPA
     * Crea una copia del mapa en el SimCity.
     * Complejidad: O(claveMasLarga + simCity::mapa())
     **/
    Mapa verMapa(const Nombre& n) const;

    /**
     VER CASAS
     * Crea una copia de las casas en el SimCity.
     * Complejidad: O(claveMasLarga + simCity::casas())
     **/
    std::map<Casilla, Nat> verCasas(const Nombre& n) const;

    /**
     VER COMERCIOS
     * Crea una copia de los comercios en el SimCity.
     * Complejidad: O(claveMasLarga + simCity::comercios())
     **/
    std::map<Casilla, Nat> verComercios(const Nombre& n) const;

    /**
     VER POPULARIDAD
     * Muestra la popularidad de una Partida.
     * Complejidad: O(claveMasLarga)
     **/
    Nat verPopularidad(const Nombre& n) const;

    /**
     VER TURNOS
     * Muestra el turno actual de una Partida.
     * Complejidad: O(claveMasLarga)
     **/
    Nat verTurnos(const Nombre& n) const;

    /**
     HUBO CONSTRUCCION
     * Evalua si hubo una union en este turno para una Partida.
     * Complejidad: O(claveMasLarga)
     **/
    bool huboConstruccion(const Nombre& n) const;


private:

    struct Partida {
        explicit Partida(const Mapa& m): sc(new SimCity(m)), modificable(true) {};
        SimCity *sc;
        bool modificable;
    };

    DiccTrie<Partida> _partidas;
};

#endif //TP_SIMCITY_SERVIDOR_H
