#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <list>

/**
 * DiccTrie implementa un diccionario de string sobre una estructura de trie.
 * @tparam T el tipo del significado.
 * @tparam C la cantidad de caracteres sobre los que operar. Por defecto se hace un cast del caracter a std::size_t.
 */
template<class T, std::size_t C=256>
class DiccTrie {

// FUNCIONALIDAD DICCIONARIO
public:

    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    DiccTrie();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    DiccTrie(const DiccTrie<T, C>& aCopiar);

    /**
    DESTRUCTOR
    **/
    ~DiccTrie();

    /**
    OPERADOR ASIGNACION
     **/
    DiccTrie& operator=(const DiccTrie& d);

    /**
     OPERADOR []
     * Acceso o definición de pares clave/valor
     * obs: un acceso a una clave inexistente agrega esa clave al trie con el valor predeterminado de T.
     **/
    T &operator[](const std::string &clave);
    const T &operator[](const std::string &clave) const;

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario.
    **/
    void insert(const std::pair<std::string, T>& cs);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/
    int count(const std::string &clave) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    * -- PRODUCE ALIASING --
    * -- Versión modificable y no modificable
    **/
    const T& at(const std::string& clave) const;
    T& at(const std::string& clave);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    * -- PRODUCE ALIASING --
    **/
    void erase(const std::string& clave);

    /**
     SIZE
     * Devuelve cantidad de claves definidas
     **/
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario
     **/
    bool empty() const;


// ESTRUCTURA Y AUX
private:

    struct Nodo {
        Nodo* siguientes[C]{};
        Nodo* anterior = nullptr;
        T* definicion = nullptr;
        typename std::list<std::tuple<std::string, Nodo*>>::iterator _clave;
    };

    Nodo* _raiz;
    std::size_t _size;
    std::list<std::tuple<std::string, Nodo*>> _claves;

    /**
     * copia recursivamente el árbol C-ario.
     */
    Nodo* _copiar(Nodo* raiz);

    /**
     * copia las claves del árbol C-ario.
     */
    void _copiar_claves(const DiccTrie<T, C>& otro);

    /**
     * elimina recursivamente el árbol C-ario.
     **/
    void _eliminar(Nodo* raiz);

    /**
     * retorna el par padre-hijo donde está definida la clave, o el último nodo, de no estarlo.
     **/
    std::tuple<Nodo*, Nodo*, size_t> _alcanzar(const std::string& clave) const;

    /**
     * evalúa si un array tiene punteros válidos.
     **/
    bool _es_null_array(Nodo* (&a)[C]);


// FUNCIONALIDAD ITERADOR
public:

    class iterator {

        // ITERADOR
    public:

        /**
         CONSTRUCTOR INICIAL
         * crea un iterador apuntando a la primer clave.
         **/
        explicit iterator(typename std::list<std::tuple<std::string, Nodo*>>::iterator actual);

        /**
         OPERADOR ==
         * evalúa si dos iteradores son iguales
         **/
        bool operator==(const iterator& otro);

        /**
         OPERADOR !=
         * evalúa si dos iteradores son distintos
         **/
        bool operator!=(const iterator& otro);

        /**
         OPERADOR ++
         * avanza el iterador a la próxima clave.
         **/
        void operator++();

        /**
         NEXT
         * avanza el iterador a la próxima clave.
         **/
        void next();

        /**
         CLAVE
         * retorna la clave asociada al iterador.
         **/
        const std::string& clave();

        /**
         SIGNIFICADO
         * retorna el significado asociado al iterador.
         -- PRODUCE ALIASING --
         * -- Versión modificable y no modificable
         **/
        T& significado();
        const T& significado() const;

        // ESTRUCTURA Y AUX
    private:
        typename std::list<std::tuple<std::string, Nodo*>>::iterator _it;
    };

    /**
     BEGIN
     * crea un nuevo iterador a las claves del diccionario.
     **/
    iterator begin();

    /**
     END
     * crea un iterador invalido que demarca el final de una iteración.
     **/
    iterator end();


    class iterator_ordenado {

    // ITERADOR
    public:

        /**
         CONSTRUCTOR INICIAL
         * crea un iterador apuntando a la primer clave.
         **/
        explicit iterator_ordenado(Nodo* raiz=nullptr);

        /**
         OPERADOR ==
         * evalúa si dos iteradores son iguales
         **/
        bool operator==(const iterator_ordenado& otro);

        /**
         OPERADOR !=
         * evalúa si dos iteradores son distintos
         **/
        bool operator!=(const iterator_ordenado& otro);

        /**
         OPERADOR ++
         * avanza el iterador a la próxima clave.
         **/
        void operator++();

        /**
         NEXT
         * avanza el iterador a la próxima clave.
         **/
        void next();

        /**
         CLAVE
         * retorna la clave asociada al iterador.
         **/
        const std::string& clave();

        /**
         SIGNIFICADO
         * retorna el significado asociado al iterador.
         -- PRODUCE ALIASING --
         * -- Versión modificable y no modificable
         **/
        T& significado();
        const T& significado() const;

    // ESTRUCTURA Y AUX
    private:
        std::string _clave;
        Nodo* _actual;

        std::tuple<Nodo*, std::string> _avanzar(Nodo* raiz, std::string& clave, std::size_t correr=0);
        std::tuple<Nodo*, std::string> _proxima(Nodo* raiz, std::string& clave, bool skip=false, std::size_t correr=0);
    };

    /**
     BEGIN ORDENADO
     * crea un nuevo iterador a las claves del diccionario, ejecuta en orden.
     **/
    iterator_ordenado begin_ordenado();

    /**
     END ORDENADO
     * crea un iterador ordenado invalido que demarca el final de una iteración.
     **/
    iterator_ordenado end_ordenado();
};


#include "DiccTrie.hpp"
#include "DiccTrie_iteradores.hpp"
#endif // STRING_MAP_H_
