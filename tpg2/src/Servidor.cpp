#include "Servidor.h"


Servidor::Servidor() {}


Servidor::~Servidor() {}


DiccTrie<SimCity> Servidor::partidas() {}


std::set<Nombre> Servidor::congeladas() {}


void Servidor::nuevaPartida(Nombre n, const Mapa& m) {}


void Servidor::unirPartidas(Nombre n, Nombre m) {}



void Servidor::avanzarTurnoPartida(Nombre n, const std::map<Pos, Construccion>& cs) {}


void Servidor::agregarCasa(Nombre n, const Pos& p) {}


void Servidor::agregarComercio(Nombre n, const Pos& p) {}


Mapa Servidor::verMapa(Nombre n) {}


std::map<Casilla, Nat> Servidor::verCasas(Nombre n) {}


std::map<Casilla, Nat> Servidor::verComercios(Nombre n) {}


Nat Servidor::verPopularidad(Nombre n) {}


Nat Servidor::verTurnos(Nombre n) {}


