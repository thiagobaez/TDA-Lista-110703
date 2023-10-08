#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t cantidad;
};

struct lista_iterador {
	nodo_t *actual;
};

nodo_t *crear_nodo(void *elemento)
{
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if (nuevo_nodo == NULL) {
		return NULL;
	}

	nuevo_nodo->elemento = elemento;

	return nuevo_nodo;
}

nodo_t *recorrer_lista_hasta(lista_t *lista, size_t posicion)
{
	if (posicion > lista->cantidad - 1) {
		return NULL;
	}

	nodo_t *nodo_actual = lista->nodo_inicio;

	for (size_t i = 0; i < posicion; i++) {
		nodo_actual = nodo_actual->siguiente;
	}

	return nodo_actual;
}

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL) {
		return NULL;
	}
	nodo_t *nuevo_nodo = crear_nodo(elemento);

	if (nuevo_nodo == NULL) {
		return NULL;
	}

	if (lista->nodo_inicio == NULL) {
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_final = nuevo_nodo;
	} else {
		lista->nodo_final->siguiente = nuevo_nodo;
		lista->nodo_final = nuevo_nodo;
	}

	(lista->cantidad)++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL) {
		return NULL;
	}

	if (lista_vacia(lista) || posicion > (lista->cantidad - 1)) {
		return lista_insertar(lista, elemento);
	}

	nodo_t *nodo_a_insertar = crear_nodo(elemento);

	if (nodo_a_insertar == NULL) {
		return NULL;
	}

	if (posicion == 0) {
		nodo_a_insertar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_a_insertar;
	} else {
		nodo_t *nodo_actual = recorrer_lista_hasta(lista, posicion - 1);
		nodo_a_insertar->siguiente = nodo_actual->siguiente;
		nodo_actual->siguiente = nodo_a_insertar;
	}

	lista->cantidad++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return NULL;
	}
	nodo_t *anterior = NULL;

	if (lista->nodo_inicio != lista->nodo_final) {
		anterior = recorrer_lista_hasta(lista, (lista->cantidad) - 2);
	}

	void *dato_a_retornar = lista->nodo_final->elemento;
	free(lista->nodo_final);
	lista->nodo_final = anterior;

	if (anterior != NULL) {
		lista->nodo_final->siguiente = NULL;
	}

	if (anterior == NULL) {
		lista->nodo_inicio = NULL;
	}

	(lista->cantidad)--;
	return dato_a_retornar;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista)) {
		return NULL;
	}

	if (posicion > lista->cantidad - 1) {
		return lista_quitar(lista);
	}

	void *dato_a_retornar;
	nodo_t *aux;

	if (posicion == 0 || lista->nodo_inicio->siguiente == NULL) {
		dato_a_retornar = lista->nodo_inicio->elemento;
		aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(aux);
	} else {
		nodo_t *nodo_actual = recorrer_lista_hasta(lista, posicion - 1);
		dato_a_retornar = nodo_actual->siguiente->elemento;
		aux = nodo_actual->siguiente;
		nodo_actual->siguiente = nodo_actual->siguiente->siguiente;
		free(aux);
	}

	lista->cantidad--;
	return dato_a_retornar;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista)) {
		return NULL;
	}
	nodo_t *direccion_posicion_buscada =
		recorrer_lista_hasta(lista, posicion);

	if (direccion_posicion_buscada == NULL) {
		return NULL;
	}

	return direccion_posicion_buscada->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista_vacia(lista) || comparador == NULL) {
		return NULL;
	}

	nodo_t *actual;
	void *elemento_condicionado = NULL;
	bool terminado = false;

	actual = lista->nodo_inicio;
	while (!terminado && actual != NULL) {
		if ((*comparador)(actual->elemento, contexto) == 0) {
			elemento_condicionado = actual->elemento;
			terminado = true;
		}
		actual = actual->siguiente;
	}
	return elemento_condicionado;
}

void *lista_primero(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return NULL;
	}

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return NULL;
	}

	return lista->nodo_final->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL || lista->nodo_inicio == NULL) {
		return true;
	}

	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista_vacia(lista)) {
		return 0;
	}
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if (lista == NULL) {
		return;
	}
	nodo_t *actual;
	nodo_t *siguiente;

	actual = lista->nodo_inicio;
	while (actual != NULL) {
		siguiente = actual->siguiente;
		free(actual);
		actual = siguiente;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (lista == NULL) {
		return;
	}

	nodo_t *actual;
	nodo_t *siguiente;

	actual = lista->nodo_inicio;
	while (actual != NULL) {
		if (funcion != NULL) {
			funcion(actual->elemento);
		}
		siguiente = actual->siguiente;
		free(actual);
		actual = siguiente;
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL) {
		return NULL;
	}

	lista_iterador_t *iterador =
		(lista_iterador_t *)malloc(sizeof(lista_iterador_t));

	if (iterador == NULL) {
		return NULL;
	}
	iterador->actual = lista->nodo_inicio;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->actual == NULL) {
		return false;
	}

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->actual == NULL) {
		return false;
	}
	if (iterador->actual->siguiente == NULL) {
		iterador->actual = iterador->actual->siguiente;
		return false;
	}

	iterador->actual = iterador->actual->siguiente;
	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->actual == NULL) {
		return NULL;
	}
	return iterador->actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return;
	}
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (lista == NULL || funcion == NULL) {
		return 0;
	}

	size_t elementos_iterados = 0;
	nodo_t *nodo_actual = lista->nodo_inicio;
	bool iterar = true;

	while (nodo_actual != NULL && iterar) {
		iterar = funcion(nodo_actual->elemento, contexto);
		elementos_iterados++;
		nodo_actual = nodo_actual->siguiente;
	}

	return elementos_iterados;
}
