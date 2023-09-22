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
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

nodo_t* recorrer_lista_hasta(lista_t* lista, size_t posicion){

	nodo_t* actual;
	int posicion_actual=0;

	actual=lista->nodo_inicio;
	while(posicion_actual<(int)posicion){
		if(actual->siguiente==NULL && posicion_actual<(int)posicion){	
			return NULL;
		}
		actual=actual->siguiente;
		posicion_actual++;
	}


	return actual;

}

lista_t *lista_crear()
{ 
	lista_t* lista=malloc(sizeof(lista_t));

	if(lista==NULL){
		return NULL;
	}

	lista->nodo_inicio=NULL;	

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	nodo_t* actual;
	nodo_t* nuevo;
	
	nuevo=(nodo_t*)malloc(sizeof(nodo_t));

	if(nuevo==NULL){
		return NULL;
	}

	nuevo->elemento=elemento;
	nuevo->siguiente=NULL;

	if(lista->nodo_inicio==NULL){
		lista->nodo_inicio=nuevo;
	}
	else{
		actual=lista->nodo_inicio;
		while(actual->siguiente!=NULL){
			actual=actual->siguiente;
		}
		actual->siguiente=nuevo;
	
	}

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	
	int posicion_actual=0;
	nodo_t* actual;
	nodo_t* nodo_a_insertar;

	if(lista==NULL || elemento==NULL){
		return NULL;
	}

	nodo_a_insertar=(nodo_t*)malloc(sizeof(nodo_t));

	if(nodo_a_insertar==NULL){
		return NULL;
	}
	nodo_a_insertar->elemento=elemento;

	if(lista->nodo_inicio==NULL){
		lista->nodo_inicio=nodo_a_insertar;
	}

	if(posicion==0){
		nodo_a_insertar->siguiente=lista->nodo_inicio;
		lista->nodo_inicio=nodo_a_insertar;
	}

	else{
		actual=lista->nodo_inicio;
		while(actual->siguiente!=NULL && posicion_actual<(int)posicion-1){
			actual=actual->siguiente;
			posicion_actual++;
		}
		nodo_a_insertar->siguiente=actual->siguiente;
		actual->siguiente=nodo_a_insertar;
	
	}
	
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	nodo_t* actual;
	void* dato_a_retornar;


	if(lista==NULL || lista->nodo_inicio==NULL){
		return NULL;
	}

	if(lista->nodo_inicio->siguiente==NULL){
		dato_a_retornar=lista->nodo_inicio->elemento;
		free(lista->nodo_inicio);
		lista->nodo_inicio=NULL;
		return dato_a_retornar;
	}


	actual=lista->nodo_inicio;
	while(actual->siguiente->siguiente!=NULL){
		actual=actual->siguiente;

	}

	dato_a_retornar=actual->siguiente->elemento;
	free(actual->siguiente);
	actual->siguiente=NULL;

	return dato_a_retornar;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{	
	nodo_t* actual, *aux;
	void* dato_a_retornar;
	int posicion_actual=0;

	if(lista==NULL || lista->nodo_inicio==NULL){
		return NULL;
	}

	if(posicion==0 || lista->nodo_inicio->siguiente==NULL){
		dato_a_retornar=lista->nodo_inicio->elemento;
		aux=lista->nodo_inicio;
		lista->nodo_inicio=lista->nodo_inicio->siguiente;
		free(aux);
		return dato_a_retornar;
		
	}

	actual=lista->nodo_inicio;
	while(actual->siguiente->siguiente!=NULL && posicion_actual<(int)posicion-1){
		actual=actual->siguiente;
		posicion_actual++;
	}

	dato_a_retornar=actual->siguiente->elemento;
	aux=actual->siguiente;
	actual->siguiente=actual->siguiente->siguiente;
	free(aux);

	return dato_a_retornar;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	nodo_t* direccion_posicion_buscada;

	if(lista==NULL || lista->nodo_inicio==NULL){
		return NULL;
	}

	direccion_posicion_buscada=recorrer_lista_hasta(lista,posicion);

	if(direccion_posicion_buscada==NULL){
		return NULL;
	}
	else{
		return direccion_posicion_buscada->elemento;
	}

}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{	/**
 * Devuelve el primer elemento de la lista que cumple la condición
 * comparador(elemento, contexto) == 0.
 *
 * Si no existe el elemento devuelve NULL.
 */
	nodo_t* actual;
	void* elemento_condicionado=NULL;
	bool terminado=false;

	if(lista==NULL || lista->nodo_inicio==NULL || comparador==NULL || contexto==NULL){
	return NULL;
	}

	if(lista->nodo_inicio->siguiente==NULL){
		if((*comparador)(lista->nodo_inicio->elemento,contexto)==0){
			return lista->nodo_inicio->elemento;
		}

	}
	actual=lista->nodo_inicio;
	while(!terminado && actual!=NULL){
		if((*comparador)(actual->elemento,contexto)==0){
			elemento_condicionado=actual->elemento;
			terminado=true;
		}
		actual=actual->siguiente;
	}
	return elemento_condicionado;

}

void *lista_primero(lista_t *lista)
{
	if(lista==NULL || lista->nodo_inicio==NULL){
	return NULL;
	}

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	nodo_t* actual;
	
	if(lista==NULL || lista->nodo_inicio==NULL){
		return NULL;
	}

	actual=lista->nodo_inicio;
	while(actual->siguiente!=NULL){
		actual=actual->siguiente;
	}
	
	return actual->elemento;
}

bool lista_vacia(lista_t *lista)
{	
	bool estaVacia;

	if(lista==NULL || lista->nodo_inicio==NULL){
		estaVacia=true;
	}
	else{
		estaVacia=false;
	}
	return estaVacia;
}

size_t lista_tamanio(lista_t *lista)
{	
	nodo_t* actual;
	size_t contador=1;
	if(lista_vacia(lista)){
		return 0;
	}
	actual=lista->nodo_inicio;
	while(actual->siguiente!=NULL){
		actual=actual->siguiente;
		contador++;
	}
	return contador;
	
}	

void lista_destruir(lista_t *lista)
{	
	nodo_t* actual;
	nodo_t* siguiente;

	actual = lista->nodo_inicio;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual->elemento); // Liberar el elemento
        free(actual); // Liberar el nodo
        actual = siguiente;
    }
    free(lista); 
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
