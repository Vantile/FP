#ifndef Gestor_h
#define Gestor_h

#include "ListaUsuarios.h"
#include "ListaCorreos.h"

typedef struct{
	std::string dominio; // Dominio del sistema de correos.
	tListaUsuarios usuarios; // Lista de usuarios del dominio.
	tListaCorreos correos; // Lista de correos del dominio.
	int usuarioActivo; // Usuario activo (-1 si no hay nadie).
}tGestor; // Estructura que compone el gestor del sistema de correos.

void inicializar(tGestor &gestor, std::string dominio); // Inicializa el gestor.
bool arrancar(tGestor &gestor, std::string dominio); // Arranca (carga las listas) el gestor.
void apagar(const tGestor &gestor); // Apaga el gestor (guarda todas las listas).
bool crearCuenta(tGestor &gestor); // Crea una cuenta nueva en el dominio.
bool iniciarSesion(tGestor &gestor); // Inicia sesion con una cuenta del dominio.
int menuBandeja(tGestor &gestor, bool entrada); // Pinta en pantalla el menu de la bandeja (entrada/salida).
void ejecutarMenuBandeja(tGestor &gestor, int opcion, bool &entrada); // Ejecuta la opcion seleccionada del menu de la bandeja.
void leerCorreo(tGestor &gestor, tListaRegistros &listaReg); // Lee un correo.
void menuLeerCorreo(tGestor &gestor, const tCorreo &correoOriginal); // Pinta y ejecuta la opcion del menu de lectura del correo.
void borrarCorreo(tGestor &gestor, tListaRegistros &listaReg); // Borra un correo del sistema.
void enviarCorreo (tGestor &gestor, const tCorreo &correo); // Envia un correo a otro usuario del sistema.
void lecturaRapida(tGestor &gestor, tListaRegistros &listaReg); // Lee rapidamente todos los correos no leidos del usuario.

#endif