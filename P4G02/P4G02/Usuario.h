#ifndef Usuario_h
#define Usuario_h

#include "ListaRegistros.h"
#include <string> // Permite usar variables tipo string.
#include <fstream> // Entrada/salida de datos por fichero.

typedef struct{
	std::string id; // Nombre de usuario.
	std::string contrasenia; // Contraseña.
	tListaRegistros recibidos; // Registro de correos recibidos.
	tListaRegistros enviados; // Registro de correos enviados.
}tUsuario; // Estructura de un usuario.

bool cargar(tUsuario& usuario, std::ifstream& archivo); // Carga un usuario desde un archivo.
void guardar(const tUsuario& usuario, std::ofstream& archivo); // Guarda un usuario en un archivo.
void inicializar(tUsuario& usuario, std::string id, std::string contrasenia); // Inicializa un usuario.
bool validarContrasenia(const tUsuario &usuario, std::string id, std::string contrasenia); // Devuelve true si la contraseña es correcta.

#endif