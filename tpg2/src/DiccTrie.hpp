#include "DiccTrie.h"


// CONSTRUCTOR
template <class T, std::size_t C>
DiccTrie<T, C>::DiccTrie(): _raiz(new Nodo()), _size(0), _claves() {}


template <class T, std::size_t C>
DiccTrie<T, C>::DiccTrie(const DiccTrie<T, C>& aCopiar): DiccTrie() {
    *this = aCopiar;
}


template <class T, std::size_t C>
DiccTrie<T, C>::~DiccTrie() {
    _eliminar(_raiz);
}


// OPERATORS
template <class T, std::size_t C>
DiccTrie<T, C>& DiccTrie<T, C>::operator=(const DiccTrie<T, C>& d) {
    if (&d != this) {   // evitar auto-asignación
        if (_raiz != nullptr) {
            _eliminar(_raiz);
        }
        _raiz = _copiar(d._raiz);
        _size = d._size;
        _copiar_claves(d);
    }
    return *this;
}


template <class T, std::size_t C>
T& DiccTrie<T, C>::operator[](const std::string& clave){
    if (!count(clave)) {
        insert(std::make_pair(clave, T{}));
    }
    return at(clave);
}
template <class T, std::size_t C>
const T& DiccTrie<T, C>::operator[](const std::string& clave) const{
    if (!count(clave)) {
        insert(std::make_pair(clave, T{}));
    }
    return at(clave);
}


// FUNCIONES
template <class T, std::size_t C>
void DiccTrie<T, C>::insert(const std::pair<std::string, T>& cs) {
    // aliases
    const std::string& clave = std::get<0>(cs);
    const T& significado = std::get<1>(cs);
    // encontrar
    std::tuple<Nodo*, Nodo*, std::size_t> padre_hijo_i = _alcanzar(clave);
    // aliases
    Nodo* padre = std::get<0>(padre_hijo_i);
    Nodo* hijo = std::get<1>(padre_hijo_i);
    std::size_t i = std::get<2>(padre_hijo_i) - 1;
    // agregar clave
    // definir
    if (hijo != nullptr) { // i == len(clave), redefinir
        delete hijo->definicion;
        hijo->definicion = new T(significado); // copia
    } else { // crear rama
        Nodo* curr = padre;
        while (i < clave.size()) {
            Nodo* nuevo = new Nodo();
            nuevo->anterior = curr;
            auto pos = std::size_t(clave[i]);
            (curr->siguientes)[pos] = nuevo;
            curr = nuevo;
            ++i;
        }
        delete curr->definicion;
        curr->definicion = new T(significado);
        auto it = _claves.insert(_claves.end(), {clave, curr}); // crear it
        curr->_clave = it;
    }
    ++_size;
}


template <class T, std::size_t C>
int DiccTrie<T, C>::count(const std::string& clave) const {
    std::tuple<Nodo*, Nodo*, std::size_t> padre_hijo_i = _alcanzar(clave);
    return std::get<1>(padre_hijo_i) != nullptr && std::get<1>(padre_hijo_i)->definicion != nullptr;
}


template <class T, std::size_t C>
const T& DiccTrie<T, C>::at(const std::string& clave) const {
    std::tuple<Nodo*, Nodo*, std::size_t> padre_hijo_i = _alcanzar(clave);
    return *(std::get<1>(padre_hijo_i)->definicion);
}
template <class T, std::size_t C>
T& DiccTrie<T, C>::at(const std::string& clave) {
    std::tuple<Nodo*, Nodo*, std::size_t> padre_hijo_i = _alcanzar(clave);
    return *(std::get<1>(padre_hijo_i)->definicion);
}


template <class T, std::size_t C>
void DiccTrie<T, C>::erase(const std::string& clave) {
    // encontrar
    std::tuple<Nodo*, Nodo*, std::size_t> padre_hijo_i = _alcanzar(clave);
    // alias
    Nodo* padre = std::get<0>(padre_hijo_i);
    Nodo* hijo = std::get<1>(padre_hijo_i);
    std::size_t i = std::get<2>(padre_hijo_i) - 1;
    // eliminar
    if (hijo != nullptr) {
        if (_es_null_array(hijo->siguientes)) {
            _eliminar(hijo);
            (padre->siguientes)[i] = nullptr;
        } else {
            delete hijo->definicion;
            hijo->definicion = nullptr;
        }
        _claves.erase(hijo->_clave); // del it
        --_size;
    }
}


template <class T, std::size_t C>
int DiccTrie<T, C>::size() const{
    return _size;
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::empty() const{
    return _size == 0;
}


// AUX
template <class T, std::size_t C>
typename DiccTrie<T, C>::Nodo* DiccTrie<T, C>::_copiar(Nodo* raiz) {
    Nodo* copia = new Nodo();
    for (int i = 0; i < C; ++i) {
        if (raiz->siguientes[i] != nullptr) {
            (copia->siguientes)[i] = _copiar(raiz->siguientes[i]);
            (copia->siguientes)[i]->anterior = copia;
        }
    }
    if (raiz->definicion != nullptr) {
        copia->definicion = new T(*(raiz->definicion));
    } else {
        copia->definicion = nullptr;
    }
    return copia;
}


template <class T, std::size_t C>
void DiccTrie<T, C>::_copiar_claves(const DiccTrie<T, C>& otro) {
    _claves.erase(_claves.begin(), _claves.end());
    for (auto x : otro._claves) {
        std::tuple<Nodo*, Nodo*, std::size_t> padre_hijo_i = _alcanzar(std::get<0>(x));
        _claves.insert(_claves.end(), {std::get<0>(x), std::get<1>(padre_hijo_i)});
    }
}


template <class T, std::size_t C>
void DiccTrie<T, C>::_eliminar(Nodo* raiz){
    for (int i = 0; i < C; ++i) {
        if ((raiz->siguientes)[i] != nullptr) {
            _eliminar((raiz->siguientes)[i]);
        }
    }
    delete raiz->definicion;
    delete raiz;
}


template <class T, std::size_t C>
std::tuple<typename DiccTrie<T, C>::Nodo*, typename DiccTrie<T, C>::Nodo*, std::size_t>
DiccTrie<T, C>::_alcanzar(const std::string& clave) const {
    Nodo* curr = nullptr;
    Nodo* prox = _raiz;
    std::size_t i = 0;
    while (i < clave.size() && prox) {
        curr = prox;
        auto pos = std::size_t(clave[i]);
        prox = (curr->siguientes)[pos];
        ++i;
    }
    return std::tuple<Nodo*, Nodo*, std::size_t>(curr, prox, i);
}


template <class T, std::size_t C>
bool DiccTrie<T, C>::_es_null_array(Nodo* (&a)[C]) {
    bool res = true;
    size_t i = 0;
    while (i < C and res) {
        res = a[i] != nullptr;
        ++i;
    }
    return res;
}

