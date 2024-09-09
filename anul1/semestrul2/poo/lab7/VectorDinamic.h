#pragma once
#include <iostream>
#include <string>
#ifndef VECTORDINAMIC_H
#define VECTORDINAMIC_H
#define INITIAL_CAPACITY 5

template <typename ElementT>
class IteratorVector;

template<typename ElementT>
class VectorDinamic
{	
private:
	ElementT* elemente;
	int lg;
	int cap;
	void redimensionare();
public:
	// constructor 
	VectorDinamic();

	//destructor
	~VectorDinamic();

	//copiator
	VectorDinamic(const VectorDinamic& ot);

	/*
	Operator de asignare
	-dealocare obiect curent si asigurarea capacitatii pentru noul element
	-copiaza toate elementele
	*/
	VectorDinamic& operator=(const VectorDinamic& ot);

	//Muta constructorul
	VectorDinamic(VectorDinamic &&ot) noexcept;

	//Muta assignarea
	VectorDinamic& operator=(VectorDinamic&& ot) noexcept;

	//Adauga in vector
	void push_back(const ElementT &el);

	//Get un ElementT
	ElementT& get(int poz) const;

	//Set un ElementT
	void set(int poz, const ElementT& el);

	int getCap() const noexcept;

	int getLg() const noexcept;

	void erase(int position);

	friend class IteratorVector<ElementT>;

	//iteratoul vectorului
	IteratorVector<ElementT> begin() const;

	//get ultimul element
	IteratorVector<ElementT> end() const;

	bool empty() const noexcept;

	IteratorVector<ElementT> iterator() {
		return IteratorVector(*this);
	}

	ElementT& operator[](int poz) const;
};

template<typename ElementT>
ElementT &VectorDinamic<ElementT>::operator[](int poz) const {
	return elemente[poz];
}

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic() :lg(0), cap(INITIAL_CAPACITY) {
	this->elemente = new ElementT[INITIAL_CAPACITY];
}

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(const VectorDinamic<ElementT> &ot) {
	this->elemente = new ElementT[ot.cap];
	for (int i = 0; i < ot.lg; i++) {
		elemente[i] = ot.elemente[i];
	}
	lg = ot.lg;
	cap = ot.cap;
}

template<typename ElementT>
bool VectorDinamic<ElementT>::empty() const noexcept {
	return lg == 0;
}

template<typename ElementT>
VectorDinamic<ElementT> &VectorDinamic<ElementT>::operator=(const VectorDinamic<ElementT>& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elemente;
	elemente = new ElementT[ot.cap];
	for (int i = 0; i < ot.cap; i++) {
		elemente[i] = ot.elemente[i];
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}

template<typename ElementT>
VectorDinamic<ElementT>::~VectorDinamic() {
	delete[] elemente;
	lg = 0;
	cap = 0;
}

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(VectorDinamic &&ot) noexcept {
	elemente = ot.elemente;
	lg = ot.lg;
	cap = ot.cap;

	ot.elemente = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

template<typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(VectorDinamic<ElementT>&& ot) noexcept {
	if (this == &ot) {
		return *this;
	}
	delete[] elemente;

	elemente = ot.elemente;
	lg = ot.lg;
	cap = ot.cap;

	ot.elemente = nullptr;
	ot.lg = 0;;
	ot.cap = 0;
	return *this;
}

template<typename ElementT>
void VectorDinamic<ElementT>::push_back(const ElementT &el) {
	redimensionare();
	elemente[lg++] = el;
}

template<typename ElementT>
void VectorDinamic<ElementT>::erase(int position) {
	this->lg--;
	for (int i = position; i < this->lg; i++) {
		this->elemente[i] = this->elemente[i + 1];
	}
}

template<typename ElementT>
void VectorDinamic<ElementT>::set(int poz, const ElementT& el) {
	elemente[poz] = el;
}

template<typename ElementT>
ElementT& VectorDinamic<ElementT>::get(int poz) const {
	return elemente[poz];
}

template<typename ElementT>
int VectorDinamic<ElementT>::getLg() const noexcept {
	return lg;
}


template<typename ElementT>
int VectorDinamic<ElementT>::getCap() const noexcept {
	return cap;
}

template<typename ElementT>
void VectorDinamic<ElementT>::redimensionare() {
	if (lg < cap) {
		return;
	}
	cap *= 2;
	auto* aux = new ElementT[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elemente[i];
	}
	delete[] elemente;
	elemente = aux;
}

template<typename ElementT>
IteratorVector<ElementT> VectorDinamic<ElementT>::begin() const {
	return IteratorVector<ElementT>(*this);
}

template<typename ElementT>
IteratorVector<ElementT> VectorDinamic<ElementT>::end() const {
	return IteratorVector<ElementT>(*this, lg);
}

template<typename ElementT>
class IteratorVector {
private:
	const VectorDinamic<ElementT>& vec; // ref la vectorul dinamic
	int poz = 0; // prima poz o sa fie 0
public:
	//constructor iterator
	IteratorVector(const VectorDinamic<ElementT>& v);

	IteratorVector(const VectorDinamic<ElementT>& v, int poz) noexcept;

	//veridica daca iteratorul e valid
	bool valid() const;

	//get element
	ElementT& element() const;

	//trece la urmatorul element din vector
	void next();

	//suprascriu pointerul
	ElementT& operator* ();

	//suprascriu operatorul de incrementare
	IteratorVector& operator++();

	//verific egalitatea
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;

};

template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectorDinamic<ElementT>& v) : vec{ v } {}


template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectorDinamic<ElementT>& v, int poz) noexcept :vec{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVector<ElementT>::valid()const {
	return poz < vec.lg;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::element() const {
	return vec.elemente[poz];
}

template<typename ElementT>
void IteratorVector<ElementT>::next() {
	poz++;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::operator*() {
	return element();
}

template<typename ElementT>
IteratorVector<ElementT>& IteratorVector<ElementT>::operator++() {
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator==(const IteratorVector<ElementT>& ot) noexcept {
	return ot.poz == poz;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator!=(const IteratorVector<ElementT>& ot) noexcept {
	return !(*this == ot);
}

#endif // !VECTORDINAMIC_H