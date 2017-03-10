#include "Usuario.h"
#include "ListaRegistros.h"

using namespace std;

const string CENTINELAUSU = "XXX"; // Centinela de usuario.

void inicializar(tUsuario& usuario, string id, string contrasenia) // Inicializa un usuario.
{
	usuario.id = id;
	usuario.contrasenia = contrasenia;
	inicializar(usuario.enviados);
	inicializar(usuario.recibidos);
}

bool validarContrasenia(const tUsuario &usuario, string id, string contrasenia) // Devuelve true si la contraseña es correcta.
{
	bool ok = false;
	if((usuario.id == id) && (usuario.contrasenia == contrasenia))
	{
		ok = true;
	}
	return ok;
}

bool cargar(tUsuario& usuario, ifstream& archivo) // Carga un usuario desde un archivo.
{
	bool ok = false;
	archivo >> usuario.id;
	if(usuario.id != CENTINELAUSU)
	{
		archivo >> usuario.contrasenia;
		cargar(usuario.recibidos, archivo);
		cargar(usuario.enviados, archivo);
		ok = true;
	}
	return ok;
}

void guardar(const tUsuario& usuario, ofstream& archivo) // Guarda un usuario en un archivo.
{
	archivo << usuario.id;
	archivo << endl;
	archivo << usuario.contrasenia;
	archivo << endl;
	guardar(usuario.recibidos, archivo);
	guardar(usuario.enviados, archivo);
}