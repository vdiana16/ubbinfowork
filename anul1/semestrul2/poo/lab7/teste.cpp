#include "teste.h"
#include <iostream>
#include <assert.h>
#include <cstdbool>

void Teste::runTeste() {
    testCreareProdus();
    testCopieProdus();
    testCmp();
    testEgalitate();

    testAdaugaProdus();
    testStergeProdus();
    testModificaProdus();
    testCautaProdus();

    testAdaugaProd();
    testStergeProd();
    testCautaProd();
    testModificaProd();
    testSortNume();
    testSortPret();
    testSortNumeTip();
    testFiltPretMaiMare();
    testFiltNume();
    testFiltProducator();

    testVectorDinamic();
}

void Teste::testCreareProdus() {
    Produs p = { 1,"Lapte","A",10,"Zuzu" };

    assert(p.getId() == 1);
    assert(p.getNume() == "Lapte");
    assert(p.getTip() == "A");
    assert(p.getPret() == 10);
    assert(p.getProducator() == "Zuzu");

    p.setNume("Iaurt");
    assert(p.getNume() == "Iaurt");
    p.setTip("B");
    assert(p.getTip() == "B");
    p.setPret(20);
    assert(p.getPret() == 20);
    p.setProducator("Danone");
    assert(p.getProducator() == "Danone");
}

void Teste::testCopieProdus() {
    Produs p1 = { 1,"Lapte","A",10,"Zuzu" };
    Produs p2 = { p1 };

    assert(p1.getId() == p2.getId());
    assert(p1.getNume() == p2.getNume());
    assert(p1.getTip() == p2.getTip());
    assert(p1.getPret() == p2.getPret());
    assert(p1.getProducator() == p2.getProducator());
}

void Teste::testCmp() {
    Produs p1 = { 1,"Lapte","A",10,"Zuzu" };
    Produs p2 = { 2,"Iaurt","C",15,"Danone" };

    assert(cmpNume(p1, p2) == false);
    assert(cmpPret(p1, p2) == true);
    assert(cmpNume(p2, p1) == true);
    assert(cmpPret(p2, p1) == false);
    assert(cmpTip(p1, p2) == true);
    assert(cmpTip(p2, p1) == false);
}

void Teste::testEgalitate() {
    Produs p1 = { 1,"Lapte","A",10,"Zuzu" };
    Produs p2 = { 2,"Lapte","A",10,"Zuzu" };
    Produs p3 = { 3,"Iaurt","C",15,"Danone" };

    assert(p1 == p2);
}


void Teste::testAdaugaProdus() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    const VectorDinamic<Produs> prod = rep.getLista();
    assert(prod.getLg() == 0);
    rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
    rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
    rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

    const VectorDinamic<Produs> prod1 = rep.getLista();
    assert(prod1.getLg() == 3);
    try {
        rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Exista deja acest produs!\n");
    }
}

void Teste::testStergeProdus() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);

    rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
    rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
    rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

    const VectorDinamic<Produs> prod = rep.getLista();
    assert(prod.getLg() == 3);

    rep.stergeProdus(1);

    const VectorDinamic<Produs> prod1 = rep.getLista();
    assert(prod1.getLg() == 2);

    try {
        rep.stergeProdus(0);
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Nu exista acest produs!\n");
    }
}

void Teste::testModificaProdus() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    int pozitie;

    rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
    rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
    rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

    const VectorDinamic<Produs> prod = rep.getLista();
    assert(prod.getLg() == 3);

    rep.modificaProdus(1, Produs{ 1,"Oua","A",20,"LaBunica" });
    pozitie = rep.cautaId(1);
    const VectorDinamic<Produs> prod1 = rep.getLista();
    assert(prod1[pozitie].getNume() == "Oua");

    try {
        rep.modificaProdus(6, Produs{ 1,"Oua","A",20,"LaBunica" });
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Nu exista acest produs!\n");
    }
}

void Teste::testCautaProdus() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    Produs pgasit, pcautat;

    rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
    rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
    rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

    const VectorDinamic<Produs> prod = rep.getLista();
    assert(prod.getLg() == 3);

    pcautat = Produs{ 2,"Iaurt","B",15,"Danone" };
    pgasit = rep.cautaProdus(2);
    assert(pgasit == pcautat);

    try {
        rep.cautaProdus(6);
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Nu exista acest produs!\n");
    }
}

void Teste::testAdaugaProd() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 0);

    srv.adaugaProd("Oua", "B", 15, "LaBunica");

    const VectorDinamic<Produs> prod1 = srv.getListaProd();
    assert(prod1.getLg() == 1);

    assert(prod1[0].getId() == 1);
    assert(prod1[0].getNume() == "Oua");
    assert(prod1[0].getTip() == "B");
    assert(prod1[0].getPret() == 15);
    assert(prod1[0].getProducator() == "LaBunica");

    try {
        srv.adaugaProd("Oua", "B", 15, "LaBunica");
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Exista deja acest produs!\n");
    }

    try {
        srv.adaugaProd("", "", 0, "");
        assert(false);
    }
    catch (const ValidException& e) {
        assert(e.getMesaje().size() == 4);
    }
}

void Teste::testStergeProd() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 15, "LaBunica");
    srv.adaugaProd("Lapte", "A", 20, "Zuzu");
    srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
    srv.adaugaProd("Unt", "C", 7.15, "Napolact");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 4);

    srv.stergeProd(3);

    const VectorDinamic<Produs> prod1 = srv.getListaProd();
    assert(prod1.getLg() == 3);

    assert(prod1[0].getNume() == "Oua");
    assert(prod1[1].getNume() == "Lapte");
    assert(prod1[2].getNume() == "Unt");

    srv.stergeProd(2);

    const VectorDinamic<Produs> prod2 = srv.getListaProd();
    assert(prod2.getLg() == 2);

    assert(prod2[0].getNume() == "Oua");
    assert(prod2[1].getNume() == "Unt");

    try {
        srv.stergeProd(10);
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Nu exista acest produs!\n");
    }
}

void Teste::testModificaProd() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 15, "LaBunica");
    srv.adaugaProd("Lapte", "A", 20, "Zuzu");
    srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

    srv.modificaProd(1, "Ulei", "C", 20, "Spornic");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 3);

    assert(prod[0].getId() == 1);
    assert(prod[0].getNume() == "Ulei");
    assert(prod[0].getTip() == "C");
    assert(prod[0].getPret() == 20);
    assert(prod[0].getProducator() == "Spornic");

    try {
        srv.modificaProd(2, "", "", 0, "");
        assert(false);
    }
    catch (const ValidException& e) {
        assert(e.getMesaje().size() == 4);
    }

    try {
        srv.modificaProd(5, "Oua", "A", 20, "LaBunica");
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Nu exista acest produs!\n");
    }
}

void Teste::testCautaProd() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 15, "LaBunica");
    srv.adaugaProd("Lapte", "A", 20, "Zuzu");
    srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 3);

    auto prodcautat = srv.cautaProd(2);

    assert(prodcautat.getNume() == "Lapte");
    assert(prodcautat.getTip() == "A");
    assert(prodcautat.getPret() == 20);
    assert(prodcautat.getProducator() == "Zuzu");

    try {
        srv.cautaProd(20);
        assert(false);
    }
    catch (const RepoException& e) {
        assert(e.getMesaj() == "Nu exista acest produs!\n");
    }
}

void Teste::testSortNume() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 15, "LaBunica");
    srv.adaugaProd("Lapte", "A", 20, "Zuzu");
    srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
    srv.adaugaProd("Ulei", "D", 15, "Spornic");
    srv.adaugaProd("Faina", "C", 6, "Dobrogea");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 5);

    VectorDinamic<Produs> lsort = srv.sortNume();
    assert(lsort[0].getNume() == "Faina");
    assert(lsort[1].getNume() == "Kinder Bueno");
    assert(lsort[2].getNume() == "Lapte");
    assert(lsort[3].getNume() == "Oua");
    assert(lsort[4].getNume() == "Ulei");
}

void Teste::testSortPret() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 12, "LaBunica");
    srv.adaugaProd("Lapte", "A", 20, "Zuzu");
    srv.adaugaProd("Kinder Bueno", "C", 30, "Kinder");
    srv.adaugaProd("Ulei", "D", 15, "Spornic");
    srv.adaugaProd("Faina", "C", 6, "Dobrogea");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 5);

    VectorDinamic<Produs> lsort = srv.sortPret();
    assert(lsort[0].getNume() == "Faina");
    assert(lsort[1].getNume() == "Oua");
    assert(lsort[2].getNume() == "Ulei");
    assert(lsort[3].getNume() == "Lapte");
    assert(lsort[4].getNume() == "Kinder Bueno");
}

void Teste::testSortNumeTip() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 12, "LaBunica");
    srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
    srv.adaugaProd("Oua", "C", 30, "LaBunica");
    srv.adaugaProd("Faina", "D", 15, "Pambac");
    srv.adaugaProd("Faina", "C", 6, "Dobrogea");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 5);

    VectorDinamic<Produs> lsort = srv.sortNumeTip();
    assert(lsort[0].getId() == 2);
    assert(lsort[1].getId() == 5);
    assert(lsort[2].getId() == 4);
    assert(lsort[3].getId() == 1);
    assert(lsort[4].getId() == 3);

}

void Teste::testFiltPretMaiMare() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Oua", "B", 12, "LaBunica");
    srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
    srv.adaugaProd("Oua", "C", 30, "LaBunica");
    srv.adaugaProd("Faina", "D", 6, "Pambac");
    srv.adaugaProd("Faina", "C", 15, "Dobrogea");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 5);

    VectorDinamic<Produs> lfilt = srv.filtPretMaiMare(14);
    assert(lfilt[0].getId() == 2);
    assert(lfilt[1].getId() == 3);
    assert(lfilt[2].getId() == 5);
}

void Teste::testFiltNume() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val);

    srv.adaugaProd("Faina", "C", 15, "Dobrogea");
    srv.adaugaProd("Oua", "B", 12, "LaBunica");
    srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
    srv.adaugaProd("Oua", "C", 30, "LaBunica");
    srv.adaugaProd("Faina", "D", 6, "Pambac");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 5);

    VectorDinamic<Produs> lfilt = srv.filtNume("Faina");
    assert(lfilt[0].getId() == 1);
    assert(lfilt[1].getId() == 3);
    assert(lfilt[2].getId() == 5);
}

void Teste::testFiltProducator() {
    VectorDinamic<Produs> teste;
    RepoProdus rep(teste);
    ProdusValidator val;
    ServiceProdus srv(rep, val); 

    srv.adaugaProd("Faina", "C", 15, "Dobrogea");
    srv.adaugaProd("Oua", "B", 12, "LaBunica");
    srv.adaugaProd("Faina", "A", 20, "LaBunica");
    srv.adaugaProd("Oua", "C", 30, "LaBunica");
    srv.adaugaProd("Faina", "D", 6, "Pambac");

    const VectorDinamic<Produs> prod = srv.getListaProd();
    assert(prod.getLg() == 5);

    VectorDinamic<Produs> lfilt = srv.filtProducator("LaBunica");
    assert(lfilt[0].getId() == 2);
    assert(lfilt[1].getId() == 3);
    assert(lfilt[2].getId() == 4);
}

void Teste::testVectorDinamic() {
    VectorDinamic<Produs> teste;
    assert(teste.getLg() == 0);
    assert(teste.empty() == true);

    teste.push_back({ 1, "Faina", "A", 20, "RaftulBunicii" });
    teste.push_back({ 2,"Oua", "C", 30, "LaBunica" });
    teste.push_back({ 3,"Lapte", "A", 20, "Zuzu" });
    assert(teste.getLg() == 3);
    assert(teste.get(0).getNume() == "Faina");
    assert(teste.get(1).getNume() == "Oua");
    assert(teste.get(2).getNume() == "Lapte");

    teste.set(0, { 1, "Drojdie", "A", 20, "RaftulBunicii" });
    assert(teste.get(0).getNume() == "Drojdie");

    int suma = 0;
    for (auto it = teste.begin(); it != teste.end(); ++it) {
        if(it.valid())
            suma += it.element().getPret();
    }
    assert(suma == 70);

    teste.erase(1);
    assert(teste.getLg() == 2);
    assert(teste.get(0).getNume() == "Drojdie");
    assert(teste.get(1).getNume() == "Lapte");

    VectorDinamic<Produs> teste2(teste);
    assert(teste2.getLg() == 2);
    assert(teste2.get(0).getNume() == "Drojdie");
    assert(teste2.get(1).getNume() == "Lapte");

    VectorDinamic<Produs> teste3;
    teste3 = teste2;
    assert(teste3.getLg() == 2);
    assert(teste3.get(0).getNume() == "Drojdie");
    assert(teste3.get(1).getNume() == "Lapte");

    VectorDinamic<Produs>& teste7 = teste3;
    teste3 = teste7;
    assert(teste3.getLg() == 2);
    assert(teste3.get(0).getNume() == "Drojdie");
    assert(teste3.get(1).getNume() == "Lapte");

    VectorDinamic<Produs> teste4(std::move(teste3));
    assert(teste4.getLg() == 2);
    assert(teste4.get(0).getNume() == "Drojdie");
    assert(teste4.get(1).getNume() == "Lapte");
    assert(teste3.empty() == true);

    VectorDinamic<Produs>& teste8 = teste4;
    teste4 = std::move(teste8);
    assert(teste4.getLg() == 2);
    assert(teste8.getLg() == 2);

    VectorDinamic<Produs> teste5;
    teste5 = std::move(teste4);
    assert(teste5.getLg() == 2);
    assert(teste5.get(0).getNume() == "Drojdie");
    assert(teste5.get(1).getNume() == "Lapte");
    assert(teste4.empty() == true);

    VectorDinamic<Produs> teste6;
    int initialCap = INITIAL_CAPACITY;
    assert(teste6.getCap() == initialCap);
    teste6.push_back({ 1, "Faina", "A", 20, "RaftulBunicii" });
    teste6.push_back({ 2,"Oua", "C", 30, "LaBunica" });
    teste6.push_back({ 3,"Lapte", "A", 20, "Zuzu" });
    teste6.push_back({ 4,"Ciocolata", "A", 20, "Milka" });
    teste6.push_back({ 5,"Zahar", "A", 10, "Coronita" });
    teste6.push_back({ 6,"Unt", "A", 10, "Napolact" });
    assert(teste6.getCap() == 2*initialCap);
    assert(teste6.get(0).getId() == 1);
    assert(teste6.get(1).getId() == 2);
    assert(teste6.get(2).getId() == 3);
    assert(teste6.get(3).getId() == 4);
    assert(teste6.get(4).getId() == 5);
    assert(teste6.get(5).getId() == 6);
}