#ifndef ListaCorreos_h
#define ListaCorreos_h
#include "Correo.h"

const int MAX_CORREOS = 6; // Maximo de correos permitidos en la lista de correos.
typedef tCorreo tTotalCorreos[MAX_CORREOS]; // Array de correos.
typedef struct {
	tTotalCorreos listaCorreo;
	int numCorreos;
} tListaCorreos; // Estructura de lista de correos.

void inicializar(tListaCorreos &correos); // Inicializa una lista de correos.
bool cargar(tListaCorreos &correos, std::string dominio); // Carga una lista de correos de un archivo.
void guardar(const tListaCorreos &correos, std::string dominio); // Guarda una lista de correos en un archivo.
bool insertar(tListaCorreos &correos, const tCorreo &correo); // Inserta un correo ordenadamente en una lista de correos.
bool buscar(const tListaCorreos &correos, std::string id, int &pos); // Busca un correo por su id en una lista de correos.
void ordenar_AF(tListaCorreos &correos); // Ordena por asunto y fecha una lista de correos.

#endif