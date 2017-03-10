#include "Usuario.h"
#include "ListaRegistros.h"

using namespace std;

const string CENTINELAUSU = "XXX"; // Centinela de usuario.

void inicializar(tUsuario& usuario, string id, string contrasenia) 
{
	// Inicializa un usuario.
	usuario.id = id;
	usuario.contrasenia = contrasenia;
	inicializar(usuario.enviados);
	inicializar(usuario.recibidos);
}

void destruir(tUsuario &usuario)
{
	// Destruye de la memoria dinámica un dato tipo tUsuario.
	destruir(usuario.recibidos);
	destruir(usuario.enviados);
}

bool validarContrasenia(const tUsuario &usuario, string contrasenia) 
{
	// Devuelve true si la contraseña es correcta.
	return (usuario.contrasenia == contrasenia);
}

bool cargar(tUsuario& usuario, ifstream& archivo) 
{
	// Carga un usuario desde un archivo.
	bool ok = false;
	string centinela;
	archivo >> centinela;
	if(centinela != CENTINELAUSU)
	{
		usuario.id = centinela;
		archivo >> usuario.contrasenia;
		cargar(usuario.recibidos, archivo);
		cargar(usuario.enviados, archivo);
		ok = true;
	}
	return ok;
}

void guardar(const tUsuario& usuario, ofstream& archivo) 
{
	// Guarda un usuario en un archivo.
	archivo << usuario.id;
	archivo << endl;
	archivo << usuario.contrasenia;
	archivo << endl;
	guardar(usuario.recibidos, archivo);
	guardar(usuario.enviados, archivo);
}