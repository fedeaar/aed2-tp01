#ifndef TP_SIMCITY_SIMCITY_H
#define TP_SIMCITY_SIMCITY_H

#include "Mapa.h"


class SimCity {

public:

    /**
     CONSTRUCTOR
     * crea un nuevo SimCity.
     * Complejidad: O(copy(mapa))
     **/
    explicit SimCity(Mapa m);

    /**
     CONSTRUCTOR
     * crea un nuevo SimCity por Copia.
     * Complejidad: O(copy(Mapa) + cons)
     * donde cons = la cantidad de construcciones definidas directamente en este SimCity particular.
     -- PRODUCE ALIASING CON LAS UNIONES --
     **/
    SimCity(const SimCity& aCopiar);

    /**
     DESTRUCTOR
     **/
    ~SimCity();

    /**
     MAPA
     * devuelve el mapa asociado al SimCity.
     * Complejidad: O(sum(i = 0; N; copy(mapa_i))),
     * con N la cantidad de SimCities que componen la partida actual.
     **/
    Mapa mapa() const;

    /**
     CASAS
     * Retorna las posiciones y respectivos niveles de todas las casas en el juego actual.
     * Complejidad: TODO
     **/
    map<Casilla, Nat> casas() const;

    /**
     COMERCIOS
     * Retorna las posiciones y respectivos niveles de todos los comercios en el juego actual.
     * Complejidad: TODO
     **/
    map<Casilla, Nat> comercios() const;

    /**
     POPULARIDAD
     * Retorna la cantidad total de uniones que se realizaron para conformar la partida actual.
     * Complejidad: O(1)
     **/
    Nat popularidad() const;

    /**
     TURNOS
     *  Retorna la cantidad de turnos que pasaron desde que se inició el SimCity.
     * Complejidad: O(1)
     **/
    Nat turnos() const;

    /**
     AVANZAR TURNO
     *  Avanza el turno de un SimCity.
     * Complejidad: O(#cs)
     **/
    void avanzarTurno(std::map<Casilla, Construccion> cs={});

    /**
     AGREGAR CASA
     *  Agrega una casa al turno actual del SimCity.
     * Complejidad: O(1)
     **/
    void agregarCasa(Casilla pos);

    /**
     AGREGAR CASA
     *  Agrega un comercio al turno actual del SimCity.
     * Complejidad: O(1)
     **/
    void agregarComercio(Casilla pos);


    /**
     UNIR
     *  Une dos partidas de SimCity.
     * Complejidad: O(1)
     -- PRODUCE ALIASING --
     **/
    void unir(const SimCity& otro);

    /**
     HUBO CONSTRUCCIONES
     * evalua si se agregaron construcciones éste turno.
     * Complejidad: O(1)
     */
    bool huboConstruccion() const;


private:

    struct Hijo {
        Hijo(const SimCity* s, Nat t): sc(s), turnoUnido(t) {};
        const SimCity* sc;
        Nat turnoUnido;
    };

    Nat _antiguedad;
    Nat _turno;
    Nat _popularidad;
    Mapa _mapa;
    list<map<Casilla, Construccion>*> _construcciones;
    list<Hijo> _uniones;


    /**
     * resuelve las colisiones dentro de un mismo tipo de construccion en el SimCity eligiendo los valores máximos.
     */
    map<Casilla, Nat> maximizar(Construccion tipo) const ;

    /**
     * aplana la lista de diccionarios de cada SimCity en la union, acorde al tipo de construcción querido.
     */
    vector<pair<Casilla, Nat>> plancharConstruccion(Construccion tipo) const;

    /**
     * aplana la lista de diccionarios de _construcciones, acorde al tipo de construcción querido.
     */
    vector<pair<Casilla, Nat>> listDeTipo(Construccion tipo) const;

    /**
     * retorna el nivel que tendría el comercio de la posición p.
     */
    static Nat nivelCom(Casilla p, const map<Casilla, Nat>& cs);

};

#endif //TP_SIMCITY_SIMCITY_H

