#include "DiccTrie.h"


/* iterador rapido*/
template<class T, std::size_t C>
DiccTrie<T, C>::iterator::iterator(typename std::list<std::tuple<std::string, Nodo*>>::iterator it): _it(it) {}


template <class T, std::size_t C>
typename DiccTrie<T, C>::iterator DiccTrie<T, C>::begin() {
    iterator primero {_claves.begin()};
    return primero;
}


template <class T, std::size_t C>
typename DiccTrie<T, C>::iterator DiccTrie<T, C>::end() {
    return iterator {_claves.end()};
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::iterator::operator==(const iterator& otro) {
    return _it == otro._it;
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::iterator::operator!=(const iterator& otro) {
    return _it != otro._it;
}


template <class T, std::size_t C>
void DiccTrie<T, C>::iterator::operator++() {
    _it++;
}


template <class T, std::size_t C>
void DiccTrie<T, C>::iterator::next() {
    _it++;
}


template <class T, std::size_t C>
const std::string& DiccTrie<T, C>::iterator::clave() {
    return std::get<0>(*_it);
}


template <class T, std::size_t C>
T& DiccTrie<T, C>::iterator::significado() {
    return *(std::get<1>(*_it)->definicion);
}
template <class T, std::size_t C>
const T& DiccTrie<T, C>::iterator::significado() const {
    return *(std::get<1>(*_it)->definicion);
}


/* iterador ordenado */
template<class T, std::size_t C>
DiccTrie<T, C>::iterator_ordenado::iterator_ordenado(Nodo* raiz): _actual(raiz), _clave() {}


template <class T, std::size_t C>
typename DiccTrie<T, C>::iterator_ordenado DiccTrie<T, C>::begin_ordenado() {
    iterator_ordenado primero {_raiz};
    primero.next();
    return primero;
}


template <class T, std::size_t C>
typename DiccTrie<T, C>::iterator_ordenado DiccTrie<T, C>::end_ordenado() {
    return iterator_ordenado();
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::iterator_ordenado::operator==(const iterator_ordenado& otro) {
    return _actual == otro._actual;
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::iterator_ordenado::operator!=(const iterator_ordenado& otro) {
    return _actual != otro._actual;
}


template <class T, std::size_t C>
void DiccTrie<T, C>::iterator_ordenado::operator++() {
    next();
}


template <class T, std::size_t C>
void DiccTrie<T, C>::iterator_ordenado::next() {
    std::tuple<Nodo*, std::string> siguiente = _avanzar(_actual, _clave);
    _actual = std::get<0>(siguiente);
}


template <class T, std::size_t C>
const std::string& DiccTrie<T, C>::iterator_ordenado::clave() {
    return _clave;
}


template <class T, std::size_t C>
T& DiccTrie<T, C>::iterator_ordenado::significado() {
    return *(_actual->definicion);
}
template <class T, std::size_t C>
const T& DiccTrie<T, C>::iterator_ordenado::significado() const {
    return *(_actual->definicion);
}


template <class T, std::size_t C> typename std::tuple<typename DiccTrie<T, C>::Nodo*, std::string>
DiccTrie<T, C>::iterator_ordenado::_avanzar(Nodo* raiz, std::string& clave, std::size_t correr) {
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
DiccTrie<T, C>::iterator_ordenado::_proxima(Nodo* raiz, std::string& clave, bool skip, std::size_t correr) {
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

