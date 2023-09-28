#include "pila.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct _pila_t {
	nodo_t *tope;
	size_t cantidad;
};

pila_t *pila_crear()
{
	pila_t *pila = (pila_t *)malloc(sizeof(pila_t));

	if (pila == NULL) {
		return NULL;
	}

	pila->tope = NULL;
	pila->cantidad = 0;

	return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL) {
		return NULL;
	}

	nodo_t *nodo_a_apilar = (nodo_t *)malloc(sizeof(nodo_t));

	if (nodo_a_apilar == NULL) {
		return NULL;
	}

	nodo_a_apilar->elemento = elemento;
	nodo_a_apilar->siguiente = pila->tope;
	pila->tope = nodo_a_apilar;
	(pila->cantidad)++;

	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	if (pila_vacia(pila)) {
		return NULL;
	}

	void *elemento_a_retornar;
	nodo_t *nodo_auxiliar;

	elemento_a_retornar = pila->tope->elemento;
	nodo_auxiliar = pila->tope;
	pila->tope = pila->tope->siguiente;
	free(nodo_auxiliar);
	(pila->cantidad)--;

	return elemento_a_retornar;
}

void *pila_tope(pila_t *pila)
{
	if (pila_vacia(pila)) {
		return NULL;
	}

	return pila->tope->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if (pila_vacia(pila)) {
		return 0;
	}

	return pila->cantidad;
}

bool pila_vacia(pila_t *pila)
{
	if (pila == NULL || pila->cantidad == 0) {
		return true;
	}

	return false;
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL) {
		return;
	}

	while (!pila_vacia(pila)) {
		pila_desapilar(pila);
	}
	free(pila);
}
