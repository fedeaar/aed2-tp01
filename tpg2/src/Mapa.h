#ifndef TP_SIMCITY_MAPA_H
#define TP_SIMCITY_MAPA_H

#include "Tipos.h"


class Mapa {

public:

    /**
     CONSTRUCTOR
     * Crea un mapa.
     * Complejidad: O(copy(hs) + copy(vs))
     **/
    Mapa(std::set<int> hs, std::set<int> vs);

    /**
     DESTRUCTOR
     **/
    ~Mapa();

    /**
     OPERATOR ==
     * Evalua igualdad entre mapas.
     * Complejidad: O(#horizontales + #verticales)
     **/
    bool operator==(const Mapa& otro) const;

    /**
     HORIZONTALES
     * Devuelve el conjunto de ríos horizontales.
     * Complejidad: O(#horizontales)
     **/
    const std::set<int>& horizontales() const;

    /**
     VERTICALES
     * Devuelve el conjunto de ríos verticales.
     * Complejidad: O(#verticales)
     **/
    const std::set<int>& verticales() const;

    /**
     ES RIO
     * Verifica si en determinada posición hay un río.
     * Complejidad: O(#horizontales + #verticales)
     **/
    bool esRio(const Casilla& c);

    /**
     SUMA
     * Une dos Mapas.
     * Complejidad: O(#horizontales(this) * #horizontales(b) + #verticales(this) * #verticales(b))
     **/
    Mapa operator+(const Mapa& b);

private:

    std::set<int> _hs;
    std::set<int> _vs;

};

#endif //TP_SIMCITY_MAPA_H
