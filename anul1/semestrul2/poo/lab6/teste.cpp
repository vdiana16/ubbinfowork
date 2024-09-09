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
	RepoProdus rep;
	
	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);
	try {
		rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}
}

void Teste::testStergeProdus() {
	RepoProdus rep;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);
	rep.stergeProdus(1);
	assert(rep.getLista().size() == 2);

	try {
		rep.stergeProdus(0);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}
}

void Teste::testModificaProdus() {
	RepoProdus rep;
	int pozitie;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);

	rep.modificaProdus(1, Produs{ 1,"Oua","A",20,"LaBunica" });
	pozitie = rep.cautaId(1);
	auto lista = rep.getLista();
	assert(lista[pozitie].getNume() == "Oua");

	try {
		rep.modificaProdus(6, Produs{ 1,"Oua","A",20,"LaBunica" });
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}
}

void Teste::testCautaProdus() {
	RepoProdus rep;
	Produs pgasit, pcautat;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);
	
	pcautat = Produs{ 2,"Iaurt","B",15,"Danone" };
	pgasit = rep.cautaProdus(2);
	assert(pgasit == pcautat);

	try {
		rep.cautaProdus(6);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}
}

void Teste::testAdaugaProd() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	assert(srv.getListaProd().size() == 0);
	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	assert(srv.getListaProd().size() == 1);

	auto lista = srv.getListaProd();

	assert(lista[0].getId() == 1);
	assert(lista[0].getNume() == "Oua");
	assert(lista[0].getTip() == "B");
	assert(lista[0].getPret() == 15);
	assert(lista[0].getProducator() == "LaBunica");

	try {
		srv.adaugaProd("Oua", "B", 15, "LaBunica");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}

	try {
		srv.adaugaProd("", "", 0, "");
		assert(false);
	}
	catch (const ValidException& e) {
		assert(true);
	}
}

void Teste::testStergeProd() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
	srv.adaugaProd("Unt", "C", 7.15, "Napolact");
	
	assert(srv.getListaProd().size() == 4);

	srv.stergeProd(3);
	assert(srv.getListaProd().size() == 3);
	
	auto lista = srv.getListaProd();
	assert(lista[0].getNume() == "Oua");
	assert(lista[1].getNume() == "Lapte");
	assert(lista[2].getNume() == "Unt");

	srv.stergeProd(2);
	auto lista2 = srv.getListaProd();
	assert(srv.getListaProd().size() == 2);
	assert(lista2[0].getNume() == "Oua");
	assert(lista2[1].getNume() == "Unt");

	try {
		srv.stergeProd(10);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}
}

void Teste::testModificaProd() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

	assert(srv.getListaProd().size() == 3);

	srv.modificaProd(1, "Ulei", "C", 20, "Spornic");

	auto lista = srv.getListaProd();
	assert(lista[0].getId() == 1);
	assert(lista[0].getNume() == "Ulei");
	assert(lista[0].getTip() == "C");
	assert(lista[0].getPret() == 20);
	assert(lista[0].getProducator() == "Spornic");

	try {
		srv.modificaProd(5, "", "", 0, "");
		assert(false);
	}
	catch (const ValidException& e) {
		assert(true);
	}

	try {
		srv.modificaProd(5, "Oua", "A", 20, "LaBunica");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(true);
	}
}

void Teste::testCautaProd() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

	assert(srv.getListaProd().size() == 3);

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
		assert(true);
	}
}

void Teste::testSortNume() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
	srv.adaugaProd("Ulei", "D", 15, "Spornic");
	srv.adaugaProd("Faina", "C", 6, "Dobrogea");
	
	assert(srv.getListaProd().size() == 5);

	auto lsort = srv.sortNume();
	assert(lsort[0].getNume() == "Faina");
	assert(lsort[1].getNume() == "Kinder Bueno");
	assert(lsort[2].getNume() == "Lapte");
	assert(lsort[3].getNume() == "Oua");
	assert(lsort[4].getNume() == "Ulei");
}

void Teste::testSortPret() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 30, "Kinder");
	srv.adaugaProd("Ulei", "D", 15, "Spornic");
	srv.adaugaProd("Faina", "C", 6, "Dobrogea");

	assert(srv.getListaProd().size() == 5);

	auto lsort = srv.sortPret();
	assert(lsort[0].getNume() == "Faina");
	assert(lsort[1].getNume() == "Oua");
	assert(lsort[2].getNume() == "Ulei");
	assert(lsort[3].getNume() == "Lapte");
	assert(lsort[4].getNume() == "Kinder Bueno");
}

void Teste::testSortNumeTip() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 15, "Pambac");
	srv.adaugaProd("Faina", "C", 6, "Dobrogea");

	assert(srv.getListaProd().size() == 5);
	auto lsort = srv.sortNumeTip();
	assert(lsort[0].getId() == 2);
	assert(lsort[1].getId() == 5);
	assert(lsort[2].getId() == 4);
	assert(lsort[3].getId() == 1);
	assert(lsort[4].getId() == 3);
	
}

void Teste::testFiltPretMaiMare() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 6, "Pambac");
	srv.adaugaProd("Faina", "C", 15, "Dobrogea");

	assert(srv.getListaProd().size() == 5);

	auto lfilt = srv.filtPretMaiMare(14);
	assert(lfilt[0].getId() == 2);
	assert(lfilt[1].getId() == 3);
	assert(lfilt[2].getId() == 5);
}

void Teste::testFiltNume() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Faina", "C", 15, "Dobrogea");
	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 6, "Pambac");

	assert(srv.getListaProd().size() == 5);

	auto lfilt = srv.filtNume("Faina");
	assert(lfilt[0].getId() == 1);
	assert(lfilt[1].getId() == 3);
	assert(lfilt[2].getId() == 5);
}

void Teste::testFiltProducator() {
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv(rep, val);

	srv.adaugaProd("Faina", "C", 15, "Dobrogea");
	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "LaBunica");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 6, "Pambac");

	assert(srv.getListaProd().size() == 5);

	auto lfilt = srv.filtProducator("LaBunica");
	assert(lfilt[0].getId() == 2);
	assert(lfilt[1].getId() == 3);
	assert(lfilt[2].getId() == 4);
}