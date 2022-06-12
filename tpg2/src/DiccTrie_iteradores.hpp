#include "DiccTrie.h"


// CONSTRUCTOR
template<class T, std::size_t C>
DiccTrie<T, C>::iterator::iterator(Nodo* raiz): _actual(raiz), _clave() {}


template <class T, std::size_t C>
typename DiccTrie<T, C>::iterator DiccTrie<T, C>::begin() {
    iterator primero {_raiz};
    primero.next(); // 'primero' no está posicionado sobre una clave aún
    return primero;
}


template <class T, std::size_t C>
typename DiccTrie<T, C>::iterator DiccTrie<T, C>::end() {
    return iterator(); // null
}

// OPERADORES
template <class T, std::size_t C>
bool DiccTrie<T, C>::iterator::operator==(const iterator& otro) {
    return _actual == otro._actual; // igualdad de direcciones, no hace falta chequear claves.
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::iterator::operator!=(const iterator& otro) {
    return _actual != otro._actual;
}


template <class T, std::size_t C>
void DiccTrie<T, C>::iterator::operator++() {
    next();
}


// FUNCIONES
template <class T, std::size_t C>
void DiccTrie<T, C>::iterator::next() {
    std::tuple<Nodo*, std::string> siguiente = _avanzar(_actual, _clave);
    _actual = std::get<0>(siguiente);
}


template <class T, std::size_t C>
const std::string& DiccTrie<T, C>::iterator::clave() {
    return _clave;
}


template <class T, std::size_t C>
T& DiccTrie<T, C>::iterator::significado() {
    return *(_actual->definicion);
}
template <class T, std::size_t C>
const T& DiccTrie<T, C>::iterator::significado() const {
    return *(_actual->definicion);
}


// AUX
template <class T, std::size_t C> typename std::tuple<typename DiccTrie<T, C>::Nodo*, std::string>
DiccTrie<T, C>::iterator::_avanzar(Nodo* raiz, std::string& clave, std::size_t correr) {
    if (raiz == nullptr) {
        return {raiz, clave};
    }
    std::tuple<Nodo*, std::string> proximo = _proxima(raiz, clave, true, correr); // check misma rama
    if (std::get<0>(proximo) == nullptr && raiz->anterior != nullptr) {  // subir y check desplazado
        std::size_t pos = clave.empty() ? 0 : std::size_t(clave[clave.size() - 1]) + 1;
        clave.pop_back();
        proximo = _avanzar(raiz->anterior, clave, pos);
    }
    return proximo;
}

template <class T, std::size_t C> typename std::tuple<typename DiccTrie<T, C>::Nodo*, std::string>
DiccTrie<T, C>::iterator::_proxima(Nodo* raiz, std::string& clave, bool skip, std::size_t correr) {
    if (!skip && raiz->definicion != nullptr) {
        return {raiz, clave};
    } else {
        std::tuple<Nodo*, std::string> primero = {nullptr, ""};
        for (std::size_t i = correr; i < C; ++i) {
            if ((raiz->siguientes)[i] != nullptr) {
                clave += char(i);
                primero = _proxima((raiz->siguientes)[i], clave);
                break;
            }
        }
        return primero;
    }
}
