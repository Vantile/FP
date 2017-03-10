#ifndef ListaRegistros_h
#define ListaRegistros_h

#include <string> // Permite usar variables tipo string.
#include <fstream> // Entrada/salida por fichero.

const int MAX_REGISTROS = 50; // Maximo de registros posibles en la lista de registros.
typedef struct {
	std::string ident; // Identificador del correo.
	bool leido; // True si el correo esta leido.
} tRegistro; // Estructura que compone un registro.

typedef tRegistro *tRegPtr; // Puntero a array de registros.

typedef struct{
	tRegPtr registros; // Lista de registros.
	int dimension; // Dimension de la lista de registros.
	int contador; // Numero de registros en lista.
}tListaRegistros; // Lista de registros.

void inicializar(tListaRegistros &listaReg); // Inicializa una lista de registros.
void cargar(tListaRegistros &listaReg, std::ifstream& archivo); // Carga una lista de registros desde un fichero.
void guardar(const tListaRegistros &listaReg, std::ofstream& archivo); // Guarda una lista de registros en un fichero.
bool insertar(tListaRegistros &listaReg, tRegistro registro); // Inserta un registro en una lista de registros.
bool borrar(tListaRegistros &listaReg, std::string id); // Borra un registro de una lista de registros.
bool correoLeido(tListaRegistros &listaReg, std::string id); // Marca un correo como leido.
int buscar(const tListaRegistros &listaReg, std::string id); // Busca un registro.
void redimensionar(tListaRegistros &listaReg); // Redimensiona una listaRegistros para aumentar/disminuir su tamaño.
void destruir(tListaRegistros &listaReg); // Destruye de la memoria dinámica un dato tipo tListaRegistros.
#endif