#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_Servidor.h"

class ServidorTest_ext : public testing::Test {
protected:
    Casilla pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    set<Casilla> posicion1, posicion2, posiciones234, posiciones01234, posiciones56789;
    set<int> h1, v1, h2, v2, h3, v3, h4, v4, h12, v12, h1234, v1234;
    Jugador jugador1, jugador2, jugador3, jugador4;

    void SetUp() {
        pos0 = {-2, -2};
        pos1 = {4, -2};
        pos2 = {3, 0};
        pos3 = {5, -3};
        pos4 = {4, -3};
        pos5 = {2, 0};
        pos6 = {2, -4};
        pos7 = {6, 0};
        pos8 = {6, -4};
        pos9 = {4, 7};
        posicion1 = {pos1};
        posicion2 = {pos2};
        posiciones234 = {pos2, pos3, pos4};
        posiciones01234 = {pos0, pos1, pos2, pos3, pos4};
        posiciones56789 = {pos5, pos6, pos7, pos8, pos9};
        jugador1 = "jugador1";
        jugador2 = "jugador2";
        jugador3 = "jugador3";
        jugador4 = "jugador4";
        h1 = {1, 5, -6, -1};
        v1 = {0, 7, -3};
        h2 = {1, 3, -5};
        v2 = {-8, 1, -3};
        h3 = {-6, -9, 9};
        v3 = {9, -5, -8};
        h4 = {6, -7, 8};
        v4 = {-3, 8, -5};
        h12 = {-1, 1, 3, 5, -5, -6};
        v12 = {0, 1, -3, 7, -8};
        h1234 = {-9, -7, -6, -5, -1, 9, 8, 6, 5, 3, 1};
        v1234 = {-8, 9, -5, 8, -3, 7, 0, 1};
    }
};

TEST_F(ServidorTest_ext, congeladas) {
    Servidor test;
    test.nuevaPartida(jugador1, Mapa(h1, v1));
    test.nuevaPartida(jugador2, Mapa(h2, v2));
    test.nuevaPartida(jugador3, Mapa(h3, v3));
    test.nuevaPartida(jugador4, Mapa(h4, v4));

    auto congeladas = test.congeladas();
    EXPECT_TRUE(congeladas.empty());
    test.unirPartidas(jugador2, jugador3);
    congeladas = test.congeladas();
    EXPECT_TRUE(congeladas.count(jugador3));
    EXPECT_FALSE(congeladas.count(jugador2));
    test.unirPartidas(jugador2, jugador4);
    congeladas = test.congeladas();
    EXPECT_TRUE(congeladas.count(jugador3));
    EXPECT_TRUE(congeladas.count(jugador4));
    EXPECT_FALSE(congeladas.count(jugador1));
    test.unirPartidas(jugador1, jugador2);
    congeladas = test.congeladas();
    EXPECT_TRUE(congeladas.count(jugador2));
}

TEST_F(ServidorTest_ext, copia) {
    Servidor test;
    test.nuevaPartida(jugador1, Mapa(h1, v1));
    test.nuevaPartida(jugador2, Mapa(h2, v2));
    test.agregarComercio(jugador1, pos1);
    test.agregarComercio(jugador1, pos2);
    test.agregarCasa(jugador1, pos3);
    test.avanzarTurnoPartida(jugador1);
    test.agregarCasa(jugador2, pos4);
    test.agregarComercio(jugador2, pos3);
    test.unirPartidas(jugador1, jugador2);

    DiccTrie<SimCity> copias = test.partidas();
    SimCity copia = (copias.at(jugador1));

    EXPECT_EQ(copia.comercios(), test.verComercios(jugador1));
    EXPECT_EQ(copia.casas(), test.verCasas(jugador1));
    copia.agregarComercio(pos5);
    copia.avanzarTurno();
    EXPECT_EQ(copia.turnos() - 1, test.verTurnos(jugador1));
    EXPECT_EQ(copia.popularidad(), test.verPopularidad(jugador1));
    EXPECT_EQ(copia.mapa(), test.verMapa(jugador1));
}
