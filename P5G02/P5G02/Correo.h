#ifndef Correo_h
#define Correo_h

#include <string> // Biblioteca para operar/manipular variables tipo string.
typedef time_t tFecha; // Tipo definido, se utiliza para la fecha de un correo.
typedef struct {
	std::string emisor; // Emisor del correo.
	std::string destinatario; // Destinatario del correo.
	std::string asunto; // Asunto del correo.
	std::string cuerpo; // Cuerpo del correo.
	tFecha fecha; // Fecha en la que se creo el correo.
	std::string ident; // Indentificador del correo (emisor + "_" + fecha).
} tCorreo; // Estructura que almacena todas las partes de un correo.

std::string mostrarFecha(tFecha fecha); // Muestra la fecha (fecha y hora) de un correo.
std::string mostrarFechaSoloDia(tFecha fecha); // Muestra la fecha (solo fecha) de un correo.
void correoNuevo(tCorreo &correo, std::string emisor); // Crea un correo nuevo.
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, std::string emisor); // Crea un correo respuesta de otro.
std::string aCadena(const tCorreo &correo); // Traduce a string (para sacar por consola) un correo.
std::string obtenerCabecera(const tCorreo &correo); // Obtiene la cabecera (para mostrar en bandeja de entrada) de un correo.
bool cargar(tCorreo &correo, std::ifstream& archivo); // Carga un correo de un archivo.
void guardar(const tCorreo &correo, std::ofstream& archivo); // Guarda un correo en un archivo.

#endif