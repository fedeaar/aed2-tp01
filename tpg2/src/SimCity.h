using namespace std;

#ifndef TP_SIMCITY_SIMCITY_H
#define TP_SIMCITY_SIMCITY_H

#include "Mapa.h"

class SimCity {

// FUNCIONALIDAD SIMCITY
public:
    SimCity(Mapa m);
    ~SimCity();

    SimCity& operator=(const SimCity& aCopiar);
    Mapa mapa() const;
    map<Casilla, Nat> casas() const;
    map<Casilla, Nat> comercios() const;
    Nat popularidad() const;
    Nat turnos() const;

    void avanzarTurno(const map<Casilla, Construccion>& cs);
    void unir(const SimCity& otro);

// ESTRUCTURA Y AUX
private:
    friend class aed2_Servidor;

    map<Casilla, Nat> listDeTipo(Construccion tipo) const;

    map<Casilla, Nat> comerciosAux(const map<Casilla, Nat>& casasTotales) const;

    void manhatizar(map<Casilla, Nat>& comercios, const map<Casilla, Nat>& casasTotales) const;

    static Nat nivelCom(Casilla p, const map<Casilla, Nat>& cs);

    struct Hijo {
        Hijo(const SimCity* s, Nat t): sc(s), turnoUnido(t) {};
        const SimCity* sc;
        Nat turnoUnido;
    };

    Nat _antiguedad;
    Nat _turno;
    Nat _popularidad;
    Mapa _mapa;
    list<const map<Casilla, Construccion>*> _construcciones;
    list<Hijo> _uniones;
};

#endif //TP_SIMCITY_SIMCITY_H

