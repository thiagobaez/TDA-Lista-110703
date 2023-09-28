#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include <stdio.h>
#include <stdbool.h>

void cargar_lista_con_elementos(lista_t *lista, int *n1, int *n2, int *n3,
				int *n4, int *n5)
{
	lista_insertar(lista, n1);
	lista_insertar(lista, n2);
	lista_insertar(lista, n3);
	lista_insertar(lista, n4);
	lista_insertar(lista, n5);
}

void cargar_cola_con_elementos(cola_t *cola, int *n1, int *n2, int *n3, int *n4,
			       int *n5)
{
	cola_encolar(cola, n1);
	cola_encolar(cola, n2);
	cola_encolar(cola, n3);
	cola_encolar(cola, n4);
	cola_encolar(cola, n5);
}

void cargar_pila_con_elementos(pila_t *pila, int *n1, int *n2, int *n3, int *n4,
			       int *n5)
{
	pila_apilar(pila, n1);
	pila_apilar(pila, n2);
	pila_apilar(pila, n3);
	pila_apilar(pila, n4);
	pila_apilar(pila, n5);
}

void sumar_uno(void *elemento)
{
	int *numero = (int *)elemento;

	(*numero)++;
}

int funcion_de_prueba_comparador(void *numero_lista, void *numero_contexto)
{
	if (numero_contexto == numero_lista) {
		return 0;
	}

	return 1;
}

bool encontrar_un_numero(void *elemento, void *contexto)
{
	if (elemento == contexto) {
		return false;
	}

	return true;
}

void crear_lista_y_verificar_que_este_vacia()
{
	pa2m_nuevo_grupo("Creación de la lista");

	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_vacia(lista) == true,
		     "Se crea una lista valida y está vacia");
	lista_destruir(lista);
}

void pruebas_de_insercion_al_final()
{
	pa2m_nuevo_grupo("Inserción al final de la lista");

	lista_t *lista = lista_crear();

	int n1 = 7, n2 = 43, n3 = 99, n4 = 854;

	pa2m_afirmar(
		lista_insertar(NULL, &n1) == NULL,
		"Se prueba insertar al final en una lista nula, devuelve NULL");
	lista_insertar(lista, &n1);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == &n1,
		"Se prueba insertar al final en una lista vacía y se verifica que está en la posición correcta");
	lista_insertar(lista, &n2);
	lista_insertar(lista, &n3);
	lista_insertar(lista, &n4);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 3) == &n4,
		"Se prueba insertar al final en una lista con elementos y se verifica que está en la posición correcta");
	lista_insertar(lista, NULL);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == NULL,
		     "Se prueba insertar al final un elemento NULL");

	lista_destruir(lista);
}

void pruebas_de_insercion_en_cualquier_posicion()
{
	pa2m_nuevo_grupo("Inserción en cualquier posición de la lista");

	int n1 = 7, n2 = 43, n3 = 99, n4 = 854, n5 = 324;

	lista_t *lista = lista_crear();

	pa2m_afirmar(
		lista_insertar_en_posicion(NULL, &n1, 2) == NULL,
		"Se prueba insertar en cualquier posición en una lista nula, devuelve NULL");

	pa2m_afirmar(
		lista_insertar_en_posicion(lista, &n1, 32) == lista,
		"Se prueba que al insertar un elemento en cualquier posición en una lista vacia se devuelva la lista");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == &n1,
		"Se prueba insertar en cualquier posición en una lista vacía y se verifica que está en la primer posición");
	lista_insertar(lista, &n2);
	lista_insertar(lista, &n3);
	lista_insertar_en_posicion(lista, &n4, 1);

	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == &n4,
		"Se prueba insertar en cualquier posición en una lista con elementos y se verifica que está en la posición correcta");
	lista_insertar_en_posicion(lista, &n5, 10);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 4) == &n5,
		"Se prueba insertar en una posición inexistente en la lista, y se verifica que la posición de ese elemento es la última");

	bool todos_los_elementos_estan_bien_posicionados = false;
	if (lista_elemento_en_posicion(lista, 0) == &n1 &&
	    lista_elemento_en_posicion(lista, 1) == &n4 &&
	    lista_elemento_en_posicion(lista, 2) == &n2 &&
	    lista_elemento_en_posicion(lista, 3) == &n3 &&
	    lista_elemento_en_posicion(lista, 4) == &n5) {
		todos_los_elementos_estan_bien_posicionados = true;
	}
	pa2m_afirmar(
		todos_los_elementos_estan_bien_posicionados == true,
		"Se prueba insertar varios elementos y que todos estén en la posición que le corresponde");
	lista_destruir(lista);

	lista = lista_crear();

	pa2m_afirmar(
		lista_insertar_en_posicion(lista, NULL, 2) == lista &&
			lista_primero(lista) == NULL,
		"Se prueba insertar un elemento nulo en cualquier posicion en una lista válida");

	lista_insertar(lista, &n1);
	lista_insertar(lista, &n1);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) ==
			     lista_elemento_en_posicion(lista, 2),
		     "Se prueba insertar un elemento repetido en la lista");

	lista_destruir(lista);
}

void pruebas_de_quitar_elementos()
{
	pa2m_nuevo_grupo("Quitar elementos de la lista");
	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 599;

	pa2m_afirmar(
		lista_quitar_de_posicion(NULL, 0) == NULL,
		"Se prueba quitar de cualquier posición de una lista nula, devuelve NULL");
	pa2m_afirmar(lista_quitar(NULL) == NULL,
		     "Se prueba quitar de una lista nula, devuelve NULL");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 2) == NULL,
		"Se prueba quitar de cualquier posición de una lista vacía, devuelve NULL");
	pa2m_afirmar(
		lista_quitar(lista) == NULL,
		"Se prueba quitar al final de una lista vacía, devuelve NULL");

	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);
	pa2m_afirmar(
		lista_quitar(lista) == &n5,
		"Se prueba quitar el último elemento de una lista con elementos, devuelve el elemento");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 2) == &n3,
		"Se prueba quitar un elemento de cualquier posición de una lista con elementos, devuelve el elemento correspondiente");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 28) == &n4,
		"Se prueba quitar de una posición inexistente en la lista y se verifica que se eliminó el último elemento de la lista");

	bool los_elementos_se_quitan_correctamente = false;
	if (lista_quitar_de_posicion(lista, 0) == &n1 &&
	    lista_quitar_de_posicion(lista, 1) == &n2) {
		los_elementos_se_quitan_correctamente = true;
	}
	pa2m_afirmar(
		los_elementos_se_quitan_correctamente == true,
		"Se prueba quitar múltiples elementos de una lista y se verifica que los elementos devueltos sean los correctos");
	lista_insertar(lista, NULL);
	pa2m_afirmar(
		lista_quitar(lista) == NULL,
		"Se prueba quitar un elemento NULL de la lista (que había sido previamente insertado), devuelve el elemento (NULL)");

	lista_destruir(lista);
}

void pruebas_de_obtener_elementos()
{
	pa2m_nuevo_grupo("Obtener elementos de la lista en posiciónes");

	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 599;

	pa2m_afirmar(
		lista_elemento_en_posicion(NULL, 1) == NULL,
		"Se prueba obtener un elemento de una lista nula, devuelve NULL");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == NULL,
		"Se prueba obtener un elemento de una lista vacía, devuelve NULL");

	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);

	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 22) == NULL,
		"Se prueba obtener un elemento de posición inexistente, resulta NULL");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 3) == &n4,
		"Se prueba obtener un elemento de posición existente en la lista, devuelve el elemento");

	lista_destruir(lista);
}

void pruebas_de_buscar_elementos()
{
	pa2m_nuevo_grupo("Buscar elementos en la lista");
	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33, n6 = 65;
	int *n7 = &n2;
	pa2m_afirmar(lista_buscar_elemento(lista, funcion_de_prueba_comparador,
					   &n5) == NULL,
		     "Se prueba buscar en una lista vacía, resulta NULL");
	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);

	pa2m_afirmar(lista_buscar_elemento(NULL, funcion_de_prueba_comparador,
					   &n3) == NULL,
		     "Se prueba buscar de una lista nula, resulta NULL");
	pa2m_afirmar(lista_buscar_elemento(lista, NULL, &n3) == NULL,
		     "Se prueba buscar con un comparador nulo, devuelve NULL");
	pa2m_afirmar(lista_buscar_elemento(lista, funcion_de_prueba_comparador,
					   NULL) == NULL,
		     "Se prueba buscar con un contexto nulo");
	pa2m_afirmar(
		lista_buscar_elemento(lista, funcion_de_prueba_comparador,
				      &n3) == &n3,
		"Se prueba buscar un elemento que sí existe en la lista, devuelve el elemento");
	pa2m_afirmar(
		lista_buscar_elemento(lista, funcion_de_prueba_comparador,
				      &n6) == NULL,
		"Se prueba buscar un elemento que no existe en la lista, devuelve NULL");
	pa2m_afirmar(
		lista_buscar_elemento(lista, funcion_de_prueba_comparador,
				      n7) == &n2,
		"Se prueba buscar un elemento duplicado en la lista, devuelve el primero encontrado");

	lista_destruir(lista);
}

void pruebas_de_cantidad_de_elementos()
{
	pa2m_nuevo_grupo("Cantidad de elementos de la lista");
	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;

	pa2m_afirmar(
		lista_tamanio(NULL) == 0,
		"Se prueba obtener la cantidad de elementos de una lista nula, devuelve 0");
	pa2m_afirmar(
		lista_tamanio(lista) == 0,
		"Se prueba obtener la cantidad de elementos de una lista nula, devuelve 0");
	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);
	pa2m_afirmar(
		lista_tamanio(lista) == 5,
		"Se prueba obtener la cantidad de elementos de una lista con elementos, devuelve 5");

	lista_destruir(lista);
}

void pruebas_de_lista_vacia()
{
	pa2m_nuevo_grupo("Vaciar lista");
	lista_t *lista = lista_crear();
	int n1 = 66, n2 = 13;
	pa2m_afirmar(
		lista_vacia(NULL) == true,
		"Se prueba verificar si una lista nula está vacía, devuelve TRUE");
	pa2m_afirmar(
		lista_vacia(lista) == true,
		"Se prueba verificar si una lista vacía está vacía, devuelve TRUE");
	lista_insertar(lista, &n1);
	lista_insertar(lista, &n2);
	pa2m_afirmar(
		lista_vacia(lista) == false,
		"Se prueba verificar si una lista con elementos no está vacía, devuelve FALSE");

	lista_destruir(lista);
}

void pruebas_de_obtener_primer_y_ultimo_elemento()
{
	pa2m_nuevo_grupo("Primer y ultimo elemento de la lista");
	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;
	pa2m_afirmar(
		lista_primero(NULL) == NULL,
		"Se prueba obtener el primer elemento de una lista nula, devuelve NULL");
	pa2m_afirmar(
		lista_primero(lista) == NULL,
		"Se prueba obtener el primer elemento de una lista vacía, devuelve NULL");
	pa2m_afirmar(
		lista_ultimo(NULL) == NULL,
		"Se prueba obtener el último elemento de una lista nula, devuelve NULL");
	pa2m_afirmar(
		lista_ultimo(lista) == NULL,
		"Se prueba obtener el último elemento de una lista vacía, devuelve NULL");

	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);
	pa2m_afirmar(
		lista_primero(lista) == &n1,
		"Se prueba obtener el primer elemento de una lista con elementos, devuelve el primero");
	pa2m_afirmar(
		lista_ultimo(lista) == &n5,
		"Se prueba obtener el último elemento de una lista con elementos, devuelve el último");

	lista_destruir(lista);
}

void pruebas_iterador_externo()
{
	pa2m_nuevo_grupo("Iterador externo");
	lista_t *lista = lista_crear();
	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(
		lista_iterador_crear(NULL) == NULL,
		"Se prueba crear un iterador externo con una lista nula, devuelve NULL");
	pa2m_afirmar(
		iterador != NULL,
		"Se prueba crear un iterador externo con una lista vacía, devuelve el iterador creado");
	lista_iterador_destruir(iterador);
	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);
	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(
		iterador != NULL,
		"Se prueba crear un iterador externo con una lista con elementos, devuelve el iterador");
	pa2m_afirmar(lista_iterador_avanzar(NULL) == false,
		     "Se prueba avanzar un iterador nulo, devuelve FALSE");
	pa2m_afirmar(
		lista_iterador_avanzar(iterador) == true,
		"Se prueba avanzar un iterador que todavía tiene elementos para iterar, devuelve TRUE");
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(NULL) == false,
		"Se prueba verificar si un iterador nulo tiene más elementos para iterar, devuelve FALSE");
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador) == true,
		"Se prueba verificar si un iterador que tiene más elementos para iterar, los tenga, devuelve TRUE");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) != NULL,
		"Se prueba obtener el elemento actual de un iterador que si tiene elementos para obtener, devuelve el elemento");
	pa2m_afirmar(
		lista_iterador_elemento_actual(NULL) == NULL,
		"Se prueba obtener el elemento actual de un iterador nulo, devuelve NULL");
	while (lista_iterador_tiene_siguiente(iterador)) {
		lista_iterador_avanzar(iterador);
	}
	pa2m_afirmar(
		lista_iterador_avanzar(iterador) == false,
		"Se prueba avanzar un iterador que ya no tiene elementos para iterar, devuelve FALSE");
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador) == false,
		"Se prueba verificar si un iterador que no tiene más elementos para iterar, no los tenga. Devuelve FALSE");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == NULL,
		"Se prueba obtener el elemento actual de un iterador que no tiene elementos para obtener, devuelve NULL");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void pruebas_iterador_interno()
{
	pa2m_nuevo_grupo("Iterador interno");
	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;

	pa2m_afirmar(lista_con_cada_elemento(NULL, encontrar_un_numero, &n3) ==
			     0,
		     "Se prueba iterar una lista nula, devuelve 0");
	pa2m_afirmar(lista_con_cada_elemento(lista, encontrar_un_numero, &n3) ==
			     0,
		     "Se prueba iterar una lista vacía, devuelve 0");
	pa2m_afirmar(
		lista_con_cada_elemento(lista, NULL, &n3) == 0,
		"Se prueba iterar una lista con una función nula, devuelve 0");
	pa2m_afirmar(
		lista_con_cada_elemento(lista, encontrar_un_numero, NULL) ==
			lista_tamanio(lista),
		"Se prueba iterar una lista con un auxiliar nulo, devuelve la cantidad de elementos iterados");

	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);
	pa2m_afirmar(
		lista_con_cada_elemento(lista, encontrar_un_numero, &n5) ==
			lista_tamanio(lista),
		"Se prueba iterar una lista en su totalidad, devuelve la cantidad de elementos iterados");
	pa2m_afirmar(
		lista_con_cada_elemento(lista, encontrar_un_numero, NULL) ==
			lista_tamanio(lista),
		"Se prueba iterar una lista deteniéndose antes de terminar de visitar todos los elementos, devuelve la cantidad de elementos iterados");

	lista_destruir(lista);
}

void pruebas_de_destruir_todo()
{
	pa2m_nuevo_grupo("Destruir la lista con funcion destructora");
	lista_t *lista = lista_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;

	cargar_lista_con_elementos(lista, &n1, &n2, &n3, &n4, &n5);
	lista_destruir_todo(lista, sumar_uno);

	bool funcion_destructora_aplicada_correctamente = false;

	if (n1 == 24 && n2 == 34 && n3 == 406 && n4 == 124 && n5 == 34) {
		funcion_destructora_aplicada_correctamente = true;
	}
	pa2m_afirmar(
		funcion_destructora_aplicada_correctamente == true,
		"Se prueba aplicar la funcion destruir todo y se verifica que funciona correcamente");
}

void pruebas_de_cola()
{
	pa2m_nuevo_grupo("Pruebas generales de cola");
	cola_t *cola = cola_crear();
	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;

	pa2m_afirmar(
		cola_vacia(cola) == true,
		"Se prueba crear una cola y verificar que esta empieza vacía");
	pa2m_afirmar(
		cola_vacia(NULL) == true,
		"Se prueba verificar si una cola nula esta vacia, devuelve TRUE");
	pa2m_afirmar(
		cola_frente(NULL) == NULL,
		"Se prueba obtener el elemento del frente de la cola NULL, devuelve NULL");
	pa2m_afirmar(
		cola_frente(cola) == NULL,
		"Se prueba obtener el elemento del frente de la cola vacia, devuelve NULL");
	pa2m_afirmar(
		cola_tamanio(cola) == 0,
		"Se prueba obtener el tamaño de una cola vacía, devuelve 0");
	pa2m_afirmar(
		cola_tamanio(NULL) == 0,
		"Se prueba obtener el tamaño de una cola nula, devuelve 0");
	pa2m_afirmar(
		cola_encolar(cola, &n1) == cola && cola_frente(cola) == &n1,
		"Se prueba encolar en una cola vacía y se verifica que está en el frente, devuelve la cola");
	pa2m_afirmar(cola_encolar(NULL, &n1) == NULL,
		     "Se prueba encolar en una cola nula, devuelve NULL");
	pa2m_afirmar(cola_encolar(cola, NULL) == cola &&
			     cola_tamanio(cola) == 2,
		     "Se prueba encolar un elemento NULL, devuelve la cola");
	pa2m_afirmar(
		cola_desencolar(cola) == &n1,
		"Se prueba desencolar un elemento y verificar que es el correcto");

	cola_destruir(cola);
	cola = cola_crear();

	cargar_cola_con_elementos(cola, &n1, &n2, &n3, &n4, &n5);
	pa2m_afirmar(
		cola_vacia(cola) == false,
		"Se prueba encolar elementos y se verifica que la cola no esta vacia, devuelve FALSE");
	pa2m_afirmar(
		cola_tamanio(cola) == 5,
		"Se prueba encolar elementos y se verifica la cantidad de elementos encolados");
	pa2m_afirmar(
		cola_frente(cola) == &n1,
		"Se prueba obtener el elemento del frente en cola con elementos, devuelve el elemento del frente");

	bool elementos_correctamente_desencolados = false;
	if (cola_desencolar(cola) == &n1 && cola_desencolar(cola) == &n2 &&
	    cola_desencolar(cola) == &n3) {
		elementos_correctamente_desencolados = true;
	}

	pa2m_afirmar(
		elementos_correctamente_desencolados == true,
		"Se prueba desencolar varios elementos y se verifica que los elementos desencolados sean correctos");
	pa2m_afirmar(
		cola_frente(cola) == &n4,
		"Se prueba nuevamente que en el frente de la cola se encuentre el elemento correcto");

	cola_destruir(cola);
}

void pruebas_de_pila()
{
	pa2m_nuevo_grupo("Pruebas generales de pila");
	pila_t *pila = pila_crear();

	int n1 = 23, n2 = 33, n3 = 405, n4 = 123, n5 = 33;

	pa2m_afirmar(
		pila_vacia(pila) == true,
		"Se prueba crear una pila y se verifica que esta inicie vacía");
	pa2m_afirmar(
		pila_tope(NULL) == NULL,
		"Se prueba obtener el elemento del tope de una pila NULL, devuelve NULL");
	pa2m_afirmar(
		pila_tope(pila) == NULL,
		"Se prueba obtener el elemento del tope de una pila vacia, devuelve NULL");
	pa2m_afirmar(
		pila_tamanio(pila) == 0,
		"Se prueba obtener el tamaño de una pila vacía, devuelve 0");
	pa2m_afirmar(
		pila_tamanio(NULL) == 0,
		"Se prueba obtener el tamaño de una pila nula, devuelve 0");
	pa2m_afirmar(
		pila_apilar(pila, &n1) == pila && pila_tope(pila) == &n1 &&
			pila_tamanio(pila) == 1,
		"Se prueba apilar en una pila vacía y se verifica que está en el tope, devuelve la pila");
	pa2m_afirmar(pila_apilar(NULL, &n1) == NULL,
		     "Se prueba apilar en una pila nula, devuelve NULL");
	pa2m_afirmar(
		pila_desapilar(pila) == &n1,
		"Se prueba desapilar un elemento y verificar que es el correcto");
	pa2m_afirmar(pila_apilar(pila, NULL) == pila,
		     "Se prueba apilar un elemento NULL, devuelve la pila");

	pila_destruir(pila);

	pila = pila_crear();

	cargar_pila_con_elementos(pila, &n1, &n2, &n3, &n4, &n5);
	pa2m_afirmar(
		pila_vacia(pila) == false,
		"Se prueba apilar elementos y se verifica que la pila no esta vacia, devuelve FALSE");
	pa2m_afirmar(
		pila_tamanio(pila) == 5,
		"Se prueba apilar elementos y se verifica la cantidad de elementos encolados");
	pa2m_afirmar(
		pila_tope(pila) == &n5,
		"Se prueba obtener el elemento del tope de una pila con elementos, devuelve el elemento correcto");

	bool elementos_correctamente_desapilados = false;
	if (pila_desapilar(pila) == &n5 && pila_desapilar(pila) == &n4 &&
	    pila_desapilar(pila) == &n3) {
		elementos_correctamente_desapilados = true;
	}

	pa2m_afirmar(
		elementos_correctamente_desapilados == true,
		"Se prueba desapilar varios elementos y se verifica que los elementos desapilados sean correctos");
	pa2m_afirmar(
		pila_tope(pila) == &n2,
		"Se prueba nuevamente que el tope de la pila sea el correcto");

	pila_destruir(pila);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS TDA LISTA - PADRON: 110703 ========================");
	pa2m_nuevo_grupo("------------- PRUEBAS CON LISTA -------------\n");
	crear_lista_y_verificar_que_este_vacia();
	pruebas_de_insercion_al_final();
	pruebas_de_insercion_en_cualquier_posicion();
	pruebas_de_quitar_elementos();
	pruebas_de_obtener_elementos();
	pruebas_de_buscar_elementos();
	pruebas_de_cantidad_de_elementos();
	pruebas_de_lista_vacia();
	pruebas_de_obtener_primer_y_ultimo_elemento();
	pruebas_iterador_externo();
	pruebas_iterador_interno();
	pruebas_de_destruir_todo();
	pa2m_nuevo_grupo("------------- PRUEBAS CON COLA -------------\n");
	pruebas_de_cola();
	pa2m_nuevo_grupo("------------- PRUEBAS CON PILA -------------\n");
	pruebas_de_pila();

	return pa2m_mostrar_reporte();
}
