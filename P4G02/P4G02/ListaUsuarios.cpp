#include "ListaUsuarios.h"
#include <string> // Permite usar variables tipo string.
using namespace std;

const string CENTINELA = "XXX"; // Centinela de la lista de usuarios.
const string EXTUSUARIOS = "_usuarios.txt"; // Extension del archivo de la lista de usuarios.

void inicializar(tListaUsuarios &usuarios) // Inicializa una lista de usuarios.
{
	inicializar(usuarios.usuarios[0], CENTINELA, CENTINELA);
	usuarios.contador = 0;
}

bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion) // Busca un usuario en una lista de usuarios.
{
	int ini = 0;
	int fin = usuarios.contador - 1;
	int mitad = 0;
	bool ok = false;
	while ((ini <= fin) && (!ok)) // Busqueda binaria de un usuario.
	{
		mitad = (ini + fin) / 2;
		if(usuarios.usuarios[mitad].id == id)
		{
			ok = true;
		}
		else if (usuarios.usuarios[mitad].id < id)
		{
			ini = mitad + 1;
		}
		else
		{
			fin = mitad - 1;
		}
	}
	if((ok == false))
		posicion = -1;
	else
		posicion = mitad;
	return ok;
}

bool insertar(tListaUsuarios& usuarios, const tUsuario& usuario) // Inserta un usuario en una lista de usuarios.
{
	int posicion = 0;
	bool ok = false;
	int i = usuarios.contador;
	int j = 0;
	while((usuarios.usuarios[posicion].id < usuario.id) && (posicion < MAX_USUARIOS) && (ok != true) && (usuarios.usuarios[posicion].id != CENTINELA))
	{
		posicion++;
	}
	if(usuarios.contador != 0) // Si la lista de usuarios no esta vacia.
	{ // Ordena la lista "abriendo hueco" para el nuevo dato y lo inserta.
		while (i > posicion)
		{
			usuarios.usuarios[i].id = usuarios.usuarios[(i - 1)].id;
			usuarios.usuarios[i].contrasenia = usuarios.usuarios[(i - 1)].contrasenia;
			int j = 0;
			while(j < usuarios.usuarios[(i - 1)].recibidos.contador)
			{
				usuarios.usuarios[i].recibidos.registros[j].ident = usuarios.usuarios[(i - 1)].recibidos.registros[j].ident;
				usuarios.usuarios[i].recibidos.registros[j].leido = usuarios.usuarios[(i - 1)].recibidos.registros[j].leido;
				j++;
			}
			usuarios.usuarios[i].recibidos.contador = usuarios.usuarios[(i - 1)].recibidos.contador;
			j = 0;
			while(j < usuarios.usuarios[(i - 1)].enviados.contador)
			{
				usuarios.usuarios[i].enviados.registros[j].ident = usuarios.usuarios[(i - 1)].enviados.registros[j].ident;
				usuarios.usuarios[i].enviados.registros[j].leido = usuarios.usuarios[(i - 1)].enviados.registros[j].leido;
				j++;
			}
			usuarios.usuarios[i].enviados.contador = usuarios.usuarios[(i - 1)].enviados.contador;
			i--;
		}
		usuarios.usuarios[posicion].id = usuario.id;
		usuarios.usuarios[posicion].contrasenia = usuario.contrasenia;
		j = 0;
		while(j < usuario.recibidos.contador)
		{
			usuarios.usuarios[posicion].recibidos.registros[j].ident = usuario.recibidos.registros[j].ident;
			usuarios.usuarios[posicion].recibidos.registros[j].leido = usuario.recibidos.registros[j].leido;
			j++;
		}
		usuarios.usuarios[posicion].recibidos.contador = usuario.recibidos.contador;
		j = 0;
		while(j < usuario.enviados.contador)
		{
			usuarios.usuarios[posicion].enviados.registros[j].ident = usuario.enviados.registros[j].ident;
			usuarios.usuarios[posicion].enviados.registros[j].leido = usuario.enviados.registros[j].leido;
			j++;
		}
		usuarios.usuarios[posicion].enviados.contador = usuario.enviados.contador;
		usuarios.contador++;
		ok = true;
	}
	else // Si esta vacio. Directamente copia el usuario en el primer hueco de la lista.
	{
		usuarios.usuarios[posicion].id = usuario.id;
		usuarios.usuarios[posicion].contrasenia = usuario.contrasenia;
		j = 0;
		while(j < usuario.recibidos.contador)
		{
			usuarios.usuarios[posicion].recibidos.registros[j].ident = usuario.recibidos.registros[j].ident;
			usuarios.usuarios[posicion].recibidos.registros[j].leido = usuario.recibidos.registros[j].leido;
			j++;
		}
		usuarios.usuarios[posicion].recibidos.contador = usuario.recibidos.contador;
		j = 0;
		while(j < usuario.enviados.contador)
		{
			usuarios.usuarios[posicion].enviados.registros[j].ident = usuario.enviados.registros[j].ident;
			usuarios.usuarios[posicion].enviados.registros[j].leido = usuario.enviados.registros[j].leido;
			j++;
		}
		usuarios.usuarios[posicion].enviados.contador = usuario.enviados.contador;
		usuarios.contador++;
		ok = true;
	}
	inicializar(usuarios.usuarios[usuarios.contador], CENTINELA, CENTINELA);
	return ok;
}

bool cargar(tListaUsuarios& usuarios, string dominio) // Carga una lista de usuarios desde un archivo.
{
	bool ok = true;
	ifstream archivo;
	string dominioUs = dominio + EXTUSUARIOS;
	archivo.open(dominioUs);
	int i = 0;
	if(archivo.is_open())
	{
		inicializar(usuarios);
		string aux;
		while((ok == true) && (i < MAX_USUARIOS))
		{
			ok = cargar(usuarios.usuarios[i], archivo);
			i++;
		}
		ok = true;
		usuarios.contador = i - 1;
	}
	else
	{
		ok = false;
	}
	return ok;
}

void guardar(const tListaUsuarios& usuarios, string dominio) // Guarda una lista de usuarios en un archivo.
{
	string dominioUs = dominio + EXTUSUARIOS;
	int i = 0;
	ofstream archivo;
	archivo.open(dominioUs);
	while(i < usuarios.contador)
	{
		guardar(usuarios.usuarios[i], archivo);
		i++;
	}
	archivo << CENTINELA;
}

