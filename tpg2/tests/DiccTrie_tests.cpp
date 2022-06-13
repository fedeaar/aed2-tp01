#include "gtest-1.8.1/gtest.h"
#include "../src/DiccTrie.h"

using namespace std;
// tomados del L09 + agregados propios

TEST(DiccTrie_test, vacio) {
    DiccTrie<int> vacio;

    EXPECT_TRUE(vacio.empty());
    EXPECT_EQ(vacio.count("hola"), 0);
}

TEST(DiccTrie_test, asignar) {
    DiccTrie<int> singleton;
    singleton.insert(make_pair("hola", 1));

    EXPECT_EQ(singleton.at("hola"), 1);
    EXPECT_EQ(singleton.size(), 1);
}

TEST(DiccTrie_test, obtener) {
    DiccTrie<int> sin_prefijos;
    DiccTrie<int> con_prefijos;

    sin_prefijos.insert(make_pair("hola", 1));
    sin_prefijos.insert(make_pair("chau", 2));
    sin_prefijos.insert(make_pair("adios", 3));

    con_prefijos.insert(make_pair("c",  1));
    con_prefijos.insert(make_pair("casa",  2));
    con_prefijos.insert(make_pair("casona",  3));

    EXPECT_EQ(sin_prefijos.at("hola"), 1);
    EXPECT_EQ(sin_prefijos.at("chau"), 2);
    EXPECT_EQ(sin_prefijos.at("adios"), 3);

    EXPECT_EQ(con_prefijos.at("c"), 1);
    EXPECT_EQ(con_prefijos.at("casa"), 2);
    EXPECT_EQ(con_prefijos.at("casona"), 3);
}

TEST(DiccTrie_test, redefinir) {
    DiccTrie<int> con_prefijos;

    con_prefijos.insert(make_pair("c",  1));
    con_prefijos.insert(make_pair("casa",  2));
    con_prefijos.insert(make_pair("casona",  3));

    con_prefijos.insert(make_pair("c", 2));
    EXPECT_EQ(con_prefijos.at("c"), 2);
    con_prefijos.insert(make_pair("c", 3));
    EXPECT_EQ(con_prefijos.at("c"), 3);
}

TEST(DiccTrie_test, count) {
    DiccTrie<int> vacio;
    DiccTrie<int> sin_prefijos;
    DiccTrie<int> con_prefijos;

    sin_prefijos.insert(make_pair("hola", 1));
    sin_prefijos.insert(make_pair("chau", 2));
    sin_prefijos.insert(make_pair("adios", 3));

    con_prefijos.insert(make_pair("c", 1));
    con_prefijos.insert(make_pair("casa", 2));
    con_prefijos.insert(make_pair("casona", 3));

	EXPECT_FALSE(vacio.count("a") == 1);
	EXPECT_FALSE(vacio.count("aaaa") == 1);
	EXPECT_FALSE(vacio.count("adios") == 1);

	EXPECT_TRUE(sin_prefijos.count("hola") == 1);
	EXPECT_TRUE(sin_prefijos.count("chau") == 1);
	EXPECT_TRUE(sin_prefijos.count("adios") == 1);

	EXPECT_FALSE(sin_prefijos.count("h") == 1);
	EXPECT_FALSE(sin_prefijos.count("ho") == 1);
	EXPECT_FALSE(sin_prefijos.count("hol") == 1);

	EXPECT_TRUE(con_prefijos.count("c") == 1);
	EXPECT_TRUE(con_prefijos.count("casa") == 1);
	EXPECT_TRUE(con_prefijos.count("casona") == 1);
	EXPECT_FALSE(con_prefijos.count("ca") == 1);
	EXPECT_FALSE(con_prefijos.count("cas") == 1);
	EXPECT_FALSE(con_prefijos.count("caso") == 1);
}

TEST(DiccTrie_test, copiar) {
    DiccTrie<int> sin_prefijos;
    DiccTrie<int> con_prefijos;

    sin_prefijos.insert(make_pair("hola", 1));
    sin_prefijos.insert(make_pair("chau", 2));
    sin_prefijos.insert(make_pair("adios", 3));

    con_prefijos.insert(make_pair("c", 1));
    con_prefijos.insert(make_pair("casa", 2));
    con_prefijos.insert(make_pair("casona", 3));

    DiccTrie<int> copia(sin_prefijos);

	EXPECT_TRUE(copia.count("hola") == 1);
	EXPECT_TRUE(copia.count("chau") == 1);
	EXPECT_TRUE(copia.count("adios") == 1);

	EXPECT_FALSE(copia.count("h") == 1);
	EXPECT_FALSE(copia.count("ho") == 1);
	EXPECT_FALSE(copia.count("hol") == 1);

	EXPECT_EQ(sin_prefijos.at("hola"), copia.at("hola"));
	EXPECT_EQ(sin_prefijos.at("chau"), copia.at("chau"));
	EXPECT_EQ(sin_prefijos.at("adios"), copia.at("adios"));

	DiccTrie<int> copia2(con_prefijos);

	EXPECT_TRUE(copia2.count("c") == 1);
	EXPECT_TRUE(copia2.count("casa") == 1);
	EXPECT_TRUE(copia2.count("casona") == 1);
	EXPECT_FALSE(copia2.count("ca") == 1);
	EXPECT_FALSE(copia2.count("cas") == 1);
	EXPECT_FALSE(copia2.count("caso") == 1);

	EXPECT_EQ(copia2.at("c"), 1);
	EXPECT_EQ(copia2.at("casa"), 2);
	EXPECT_EQ(copia2.at("casona"), 3);
}

TEST(DiccTrie_test, no_aliasing) {
    DiccTrie<int> singleton;
    singleton.insert(make_pair("hola", 1));

	DiccTrie<int> copia(singleton);
	copia.insert(make_pair("hare", 2));
	ASSERT_FALSE(singleton.count("hare") == 1);
}


TEST(DiccTrie_test, TrieDeTries) {
    DiccTrie<int> vacio;
    DiccTrie<int> singleton;
    DiccTrie<int> sin_prefijos;
    DiccTrie<int> con_prefijos;
    DiccTrie<DiccTrie<int>> dicc_dicc;

    singleton.insert(make_pair("hola", 1));

    sin_prefijos.insert(make_pair("hola", 1));
    sin_prefijos.insert(make_pair("chau", 2));
    sin_prefijos.insert(make_pair("adios",  3));

    con_prefijos.insert(make_pair("c",  1));
    con_prefijos.insert(make_pair("casa",  2));
    con_prefijos.insert(make_pair("casona",  3));

    dicc_dicc.insert(make_pair("vacio",  vacio));
    dicc_dicc.insert(make_pair("singleton",  singleton));
    dicc_dicc.insert(make_pair("sin_prefijos",  sin_prefijos));
    dicc_dicc.insert(make_pair("con_prefijos",  con_prefijos));

	EXPECT_FALSE(dicc_dicc.at("vacio").count("hola") == 1);

	EXPECT_EQ(dicc_dicc.at("singleton").at("hola"), 1);

	EXPECT_EQ(dicc_dicc.at("sin_prefijos").at("hola"), 1);
	EXPECT_EQ(dicc_dicc.at("sin_prefijos").at("chau"), 2);
	EXPECT_EQ(dicc_dicc.at("sin_prefijos").at("adios"), 3);

	EXPECT_EQ(dicc_dicc.at("con_prefijos").at("c"), 1);
	EXPECT_EQ(dicc_dicc.at("con_prefijos").at("casa"), 2);
	EXPECT_EQ(dicc_dicc.at("con_prefijos").at("casona"), 3);

}

TEST(DiccTrie_test, eraseUnicaClave) {
    DiccTrie<int> singleton;
    singleton.insert(make_pair("hola", 1));

    EXPECT_TRUE(singleton.count("hola") == 1);

    singleton.erase("hola");

    EXPECT_FALSE(singleton.count("hola") == 1);
}


TEST(DiccTrie_test, erase) {
    DiccTrie<int> sin_prefijos;
    DiccTrie<int> con_prefijos;

    sin_prefijos.insert(make_pair("hola", 1));
    sin_prefijos.insert(make_pair("chau", 2));
    sin_prefijos.insert(make_pair("adios",  3));

    con_prefijos.insert(make_pair("c",  1));
    con_prefijos.insert(make_pair("casa",  2));
    con_prefijos.insert(make_pair("casona",  3));

    con_prefijos.erase("c");
    EXPECT_FALSE(con_prefijos.count("c") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);
    EXPECT_TRUE(con_prefijos.count("casona") == 1);

    con_prefijos.erase("casona");
    EXPECT_FALSE(con_prefijos.count("casona") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);

    con_prefijos.erase("casa");
    EXPECT_FALSE(con_prefijos.count("casa") == 1);

    sin_prefijos.erase("hola");
    EXPECT_FALSE(sin_prefijos.count("hola") == 1);

    sin_prefijos.erase("chau");
    EXPECT_FALSE(sin_prefijos.count("chau") == 1);

    sin_prefijos.erase("adios");
    EXPECT_FALSE(sin_prefijos.count("adios") == 1);
}

#ifdef EXT

TEST(DiccTrie_test, operator_corchetes) {
    DiccTrie<int> sin_prefijos;
    DiccTrie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    EXPECT_EQ(sin_prefijos["hola"], 1);
    EXPECT_EQ(sin_prefijos["chau"], 2);
    EXPECT_EQ(sin_prefijos["adios"], 3);

    EXPECT_EQ(con_prefijos["c"], 1);
    EXPECT_EQ(con_prefijos["casa"], 2);
    EXPECT_EQ(con_prefijos["casona"], 3);
}

TEST(DiccTrie_test, iterar_ordenado) {
    DiccTrie<int> a;
    std::vector<std::tuple<std::string, int>> test {
        {"hola", 1}, {"que", 2}, {"tal", 3}, {"ahora", 2}, {"esta", 100}, {"ordenado", 9}, {"0si", 0}, {"aero", 400}
    };
    for (auto x : test) {
        a[std::get<0>(x)] = std::get<1>(x);
    }
    std::vector<std::tuple<std::string, int>> res{};
    for (DiccTrie<int>::iterator_ordenado it = a.begin_ordenado(); it != a.end_ordenado(); ++it) {
        res.emplace_back(std::tuple<std::string, int>{it.clave(), it.significado()});
    }
    std::vector<std::tuple<std::string, int>> correcto {
        {"0si", 0}, {"aero", 400}, {"ahora", 2}, {"esta", 100}, {"hola", 1}, {"ordenado", 9}, {"que", 2}, {"tal", 3},
    };
    EXPECT_EQ(res, correcto);
}

TEST(DiccTrie_test, modificar_it_ordenado) {
    DiccTrie<int> a;
    a["hola"] = 1;
    a["chau"] = 2;
    a["adios"] =  3;

    for (auto it = a.begin_ordenado(); it != a.end_ordenado(); ++it) {
        it.significado() = 4;
    }
    EXPECT_EQ(a["hola"], 4);
    EXPECT_EQ(a["chau"], 4);
    EXPECT_EQ(a["adios"], 4);
}

TEST(DiccTrie_test, iterar) {
    DiccTrie<int> a;
    std::vector<std::tuple<std::string, int>> test {
            {"hola", 1}, {"que", 2}, {"tal", 3}, {"ahora", 2}, {"esta", 100}, {"ordenado", 9}, {"0si", 0}, {"aero", 400}
    };
    for (auto x : test) {
        a[std::get<0>(x)] = std::get<1>(x);
    }
    std::vector<std::tuple<std::string, int>> res{};
    for (DiccTrie<int>::iterator it = a.begin(); it != a.end(); ++it) {
        res.emplace_back(std::tuple<std::string, int>{it.clave(), it.significado()});
    }
    EXPECT_EQ(res, test);
}

TEST(DiccTrie_test, modificar_it) {
    DiccTrie<int> a;
    a["hola"] = 1;
    a["chau"] = 2;
    a["adios"] =  3;

    for (auto it = a.begin(); it != a.end(); ++it) {
        it.significado() = 4;
    }
    EXPECT_EQ(a["hola"], 4);
    EXPECT_EQ(a["chau"], 4);
    EXPECT_EQ(a["adios"], 4);
}

TEST(DiccTrie_test, borrar_iterado) {
    DiccTrie<int> a;
    std::vector<std::tuple<std::string, int>> test {
            {"hola", 1}, {"que", 2}, {"tal", 3}, {"ahora", 2}, {"esta", 100}, {"ordenado", 9}, {"0si", 0}, {"aero", 400}
    };
    for (auto x : test) {
        a[std::get<0>(x)] = std::get<1>(x);
    }
    a.erase("hola");
    std::vector<std::tuple<std::string, int>> res{};
    for (DiccTrie<int>::iterator it = a.begin(); it != a.end(); ++it) {
        res.emplace_back(std::tuple<std::string, int>{it.clave(), it.significado()});
    }
    test.erase(test.begin());
    EXPECT_EQ(res, test);
}
#endif

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
