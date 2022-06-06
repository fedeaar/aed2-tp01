#ifndef TP_SIMCITY_DICCTRIE_H
#define TP_SIMCITY_DICCTRIE_H

template<class T>
class DiccTrie {
public:
    DiccTrie();
    DiccTrie(const DiccTrie<T>& aCopiar);
    ~DiccTrie();

    DiccTrie& operator=(const DiccTrie<T>& d);

    void insert(const pair<std::string, T>& cs);
    int count(const std::string &key) const;

    const T& at(const std::string& key) const;
    T& at(const std::string& key);

    void erase(const std::string& key);

    int size() const;

    bool empty() const;

    T &operator[](const std::string &key);

private:
    struct Nodo {
        std::map<char, Nodo*> siguientes {};
        T* definicion = nullptr;
    };
    Nodo* _raiz{};
    int _size{};

    Nodo* _copy(Nodo* _raiz);
    void _delete(Nodo* _raiz);
    std::tuple<Nodo*, Nodo*, size_t> _alcanzar(const std::string& clave) const;
};

#endif //TP_SIMCITY_DICCTRIE_H
