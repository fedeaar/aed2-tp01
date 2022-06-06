#include "SimCity.h"


SimCity::SimCity(Mapa m) {}


SimCity::~SimCity() {}


Mapa SimCity::mapa() {}


std::map<Casilla, Nat> SimCity::casas() {}


std::map<Casilla, Nat> SimCity::comercios() {}


Nat SimCity::popularidad() {}


Nat SimCity::turnos() {}


void SimCity::avanzarTurno(const std::map<Casilla, Construccion>& cs) {}


void SimCity::unir(const SimCity& otro) {}
