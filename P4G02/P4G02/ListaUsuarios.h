#ifndef ListaUsuarios_h
#define ListaUsuarios_h

#include "Usuario.h"
#include <string> // Permite usar variables tipo string.

const int MAX_USUARIOS = 4; // Maximo de usuarios permitidos en la lista de usuarios.

typedef tUsuario tUsuarios[MAX_USUARIOS]; // Array de usuarios.
typedef struct{
	tUsuarios usuarios;
	int contador; // Numero de usuarios.
}tListaUsuarios; // Lista de usuarios.

void inicializar(tListaUsuarios &usuarios); // Inicializa una lista de usuarios.
bool cargar(tListaUsuarios& usuarios, std::string dominio); // Carga una lista de usuarios desde un archivo.
void guardar(const tListaUsuarios& usuarios, std::string dominio); // Guarda una lista de usuarios en un archivo.
bool insertar(tListaUsuarios& usuarios, const tUsuario& usuario); // Inserta un usuario en una lista de usuarios.
bool buscarUsuario(const tListaUsuarios& usuarios, std::string id, int& posicion); // Busca un usuario en una lista de usuarios.

#endif