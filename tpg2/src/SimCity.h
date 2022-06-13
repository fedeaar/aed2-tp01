#ifndef TP_SIMCITY_SIMCITY_H
#define TP_SIMCITY_SIMCITY_H

#include "Tipos.h"
#include "Mapa.h"

class SimCity {
public:
    SimCity(Mapa m);
    ~SimCity();

    operator=(const SimCity& aCopiar);
    Mapa mapa() const;
    std::map<Casilla, Nat> casas() const;
    std::map<Casilla, Nat> comercios() const;
    Nat popularidad() const;
    Nat turnos() const;

    void avanzarTurno(const std::map<Casilla, Construccion>& cs);
    void unir(const SimCity& otro);

private:
    struct Hijo {
        Hijo(SimCity* s, Nat t): sc(s), turnoUnido(t) {};
        SimCity* sc;
        Nat turnoUnido;
    };
    Nat _antiguedad;
    Nat _turno;
    Nat _popularidad;
    Mapa _mapa;
    std::list<std::map<Casilla, Construccion>*> _construcciones;
    std::list<Hijo> _uniones;
};

#endif //TP_SIMCITY_SIMCITY_H

