#include "domain.h"



int Produs::getId() const noexcept{
	return this->id;
}

double Produs::getPret() const noexcept{
	return this->pret;
}

string Produs::getNume() const noexcept{
	return this->nume;
}

string Produs::getTip() const noexcept{
	return this->tip;
}

string Produs::getProducator() const noexcept{
	return this->producator;
}

void Produs::setPret(double pretnou) {
	this->pret = pretnou;
}

void Produs::setNume(string numenou) {
	this->nume = numenou;
}
void Produs::setTip(string tipnou) {
	this->tip = tipnou;
}

void Produs::setProducator(string producatornou) {
	this->producator = producatornou;
}

bool Produs::operator==(const Produs &cop) {
	return this->nume == cop.getNume() && this->tip == cop.getTip() && this->pret == cop.getPret() && 
		this->producator == cop.getProducator();
}

bool cmpNume(const Produs &p1, const Produs &p2) {
	return p1.getNume() < p2.getNume();
}

bool cmpPret(const Produs &p1, const Produs &p2) {
	return p1.getPret() < p2.getPret();
}

bool cmpTip(const Produs &p1, const Produs &p2) {
	return p1.getTip() < p2.getTip();
}

