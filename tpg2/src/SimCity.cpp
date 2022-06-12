#include "SimCity.h"


SimCity::SimCity(Mapa m) {}


SimCity::SimCity(const SimCity& aCopiar) {}


SimCity::~SimCity() {}


Mapa SimCity::mapa() const {}


std::map<Casilla, Nat> SimCity::casas() const {}


std::map<Casilla, Nat> SimCity::comercios() const {}


Nat SimCity::popularidad() const {}


Nat SimCity::turnos() const {}


void SimCity::avanzarTurno(const std::map<Casilla, Construccion>& cs) {}


void SimCity::unir(const SimCity& otro) {}
