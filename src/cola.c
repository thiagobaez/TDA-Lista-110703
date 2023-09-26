#include "cola.h"
#include "lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct _cola_t{
	nodo_t* frente;
	nodo_t* final;
	size_t tope;
};

cola_t *cola_crear()
{
	cola_t* cola=(cola_t*)malloc(sizeof(cola_t));

	if(cola==NULL){
		return NULL;
	}

	cola->frente=NULL;
	cola->final=NULL;
	cola->tope=0;

	return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if(cola==NULL || elemento==NULL){
		return NULL;
	}
	
	nodo_t* nuevo_nodo=(nodo_t*)malloc(sizeof(nodo_t));

	if(nuevo_nodo==NULL){
		return NULL;
	}

	nuevo_nodo->elemento=elemento;
	nuevo_nodo->siguiente=NULL;
	

	if(cola_vacia(cola)){
		cola->frente=nuevo_nodo;
		cola->final=nuevo_nodo;
		(cola->tope)++;
		return cola;
	}

	cola->final->siguiente=nuevo_nodo;
	cola->final=nuevo_nodo;
	(cola->tope)++;


	return cola;
}

void *cola_desencolar(cola_t *cola)
{	
	if(cola_vacia(cola)){
		return NULL;
	}

	nodo_t* nodo_auxiliar;
	void* dato_desencolado;

	dato_desencolado=cola->frente->elemento;
	nodo_auxiliar=cola->frente;
	cola->frente=cola->frente->siguiente;
	free(nodo_auxiliar);
	(cola->tope)--;
	
	return dato_desencolado;
}

void *cola_frente(cola_t *cola)
{	
	if(cola_vacia(cola)){
	return NULL;
	}

	return cola->frente->elemento;

}

size_t cola_tamanio(cola_t *cola)
{
	if(cola==NULL){
		return 0;
	}

	return cola->tope;
}

bool cola_vacia(cola_t *cola)
{
	if(cola==NULL || cola->tope==0){
		return true;
	}

	return false;
}

void cola_destruir(cola_t *cola)
{
	if(cola==NULL){
		return;
	}
	while(!cola_vacia(cola)){
		cola_desencolar(cola);
	}
	free(cola);

}
