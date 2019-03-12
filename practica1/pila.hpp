template<typename T> struct Pila;

template<typename T> void CrearPila (Pila<T>& p);
template<typename T> void Apilar(Pila<T> &p, const T &elemento);
template<typename T> bool Desapilar(Pila<T> &p, const T &elemento);
template<typename T> void Cima(const Pila<T> &p, T &elemento, bool& error);
template<typename T> bool EsVacia(const Pila<T> &p);
template<typename T> void DuplicarPila(Pila<T> &pEnt, Pila<T> &pSal);
template<typename T> void Vaciar(Pila<T> &p);

template<typename T> struct Pila {
	friend void CrearPila <T> (Pila<T>& p);
	friend void Apilar <T> (Pila<T> &p, const T &elemento);
	friend bool Desapilar <T> (Pila<T> &p, const T &elemento);
	friend void Cima <T> (const Pila<T> &p, T &elemento, bool& error);
	friend bool EsVacia <T> (const Pila<T> &p);
	friend void DuplicarPila <T> (Pila<T> &pEnt, Pila<T> &pSal);
	friend void Vaciar<T>(Pila<T> &p);
private: 
	struct Nodo {
		T elem;
		Nodo *elemSiguiente;
	};
	Nodo *cima;
	int numDatos;
};

template<typename T>
void CrearPila(Pila<T>& p) {
	p.cima = nullptr;
	p.numDatos = 0;
}
template<typename T> 
void Apilar(Pila<T> &p, const T &elemento) {
	typename Pila<T>::Nodo *nuevo;
	nuevo = p.cima;
	p.cima = new typename Pila<T>::Nodo;
	p.cima->elem = elemento;
	p.cima->elemSiguiente = nuevo;
	p.numDatos = p.numDatos + 1;

}
template<typename T>
bool Desapilar(Pila<T> &p, const T &elemento) {
	if (p.numDatos >0) {
		typename Pila<T>::Nodo *aux;
		aux = p.cima;
		p.cima = p.cima->elemSiguiente;
		elemento = aux->elem;
		delete aux;
		p.numDatos = p.numDatos - 1;
	}
	return (p.numDatos > 0);	//Quedan elementos en la pila
}
template<typename T> 
void Cima(const Pila<T> &p, T &elemento, bool& error) {
	if (EsVacia(p)) {
		error = true;
	} else {
		error = false;
		elemento = p.cima->elem;;
	}
}
template<typename T> 
bool EsVacia(const Pila<T> &p) {
	return p.numDatos == 0;
}

template<typename T>
void DuplicarPila(Pila<T> &pEnt, Pila<T> &pSal) {
	typename Pila<T>::Nodo *ptEnt;
	typename Pila<T>::Nodo *ptSal;
	if (EsVacia(pEnt)) {
		CrearPila(pSal);
	} else {
		ptEnt = pEnt.cima;
		pSal.cima = new typename Pila<T>::Nodo;
		pSal.cima->elem = ptEnt->elem;
		ptSal = pSal.cima;
		ptEnt = ptEnt->elemSiguiente;
		while (ptEnt != nullptr) {
			ptSal->elemSiguiente = new typename Pila<T>::Nodo;
			ptSal = ptSal->elemSiguiente;
			ptSal->elem = ptEnt->elem;
			ptEnt = ptEnt->elemSiguiente;
		}
		ptSal->elemSiguiente = nullptr;
		pSal.numDatos = pEnt.numDatos;
	}
}
template <typename T>
void Vaciar(Pila<T> &p) {
	while (p.numDatos > 0) {
		T aux;
		Desapilar(p, aux);
	}
}
