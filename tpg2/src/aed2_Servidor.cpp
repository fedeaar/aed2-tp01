#include "aed2_Servidor.h"


aed2_Servidor::aed2_Servidor() {}


void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {}


void aed2_Servidor::agregarCasa(Jugador j, Casilla c) {}


void aed2_Servidor::agregarComercio(Jugador j, Casilla c) {}


void aed2_Servidor::avanzarTurno(Jugador j) {}


void aed2_Servidor::unir(Jugador j1, Jugador j2) {}


set<int> aed2_Servidor::riosHorizontales(Jugador j) const {}


set<int> aed2_Servidor::riosVerticales(Jugador j) const {}


set<Casilla> aed2_Servidor::casas(Jugador j) const {}


set<Casilla> aed2_Servidor::comercios(Jugador j) const {}


Nat aed2_Servidor::nivel(Jugador j, Casilla c) const {}


bool aed2_Servidor::huboConstruccion(Jugador j) const {}


Nat aed2_Servidor::popularidad(Jugador j) const {}


Nat aed2_Servidor::antiguedad(Jugador j) const {}

