#include "ListaUsuarios.h"
#include <string> // Permite usar variables tipo string.
using namespace std;

const string CENTINELA = "XXX"; // Centinela de la lista de usuarios.
const string EXTUSUARIOS = "_usuarios.txt"; // Extension del archivo de la lista de usuarios.

void inicializar(tListaUsuarios &usuarios) 
{
	// Inicializa una lista de usuarios.
	for(int i = 0; i < MAX_USUARIOS; i++)
	{
		usuarios.usuarios[i] = new tUsuario;
		inicializar(usuarios.usuarios[i]->recibidos);
		inicializar(usuarios.usuarios[i]->enviados);
	}

	usuarios.contador = 0;
}

void destruir(tListaUsuarios &usuarios)
{
	// Destruye de la memoria dinámica un dato tipo tListaUsuarios.
	for(int i = 0; i < MAX_USUARIOS; i++)
	{
		destruir(*usuarios.usuarios[i]);
		delete usuarios.usuarios[i];
	}
}

bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion) 
{
	// Busca un usuario en una lista de usuarios.
	int ini = 0;
	int fin = usuarios.contador;
	int mitad = 0;
	bool ok = false;
	while ((ini <= fin) && (!ok)) // Busqueda binaria de un usuario.
	{
		mitad = (ini + fin) / 2;
		if(usuarios.usuarios[mitad]->id == id)
		{
			ok = true;
		}
		else if (usuarios.usuarios[mitad]->id < id)
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

bool insertar(tListaUsuarios& usuarios, const tUsuario& usuario) 
{
	// Inserta un usuario en una lista de usuarios.
	bool ok = false;
	if(usuarios.contador < MAX_USUARIOS)
	{
		int posicion = 0;
		while((usuarios.usuarios[posicion]->id < usuario.id) && (posicion < usuarios.contador))
			posicion++;
		int i = usuarios.contador;
		destruir(*usuarios.usuarios[usuarios.contador]);
		while(i > posicion)
		{
			*usuarios.usuarios[i] = *usuarios.usuarios[i - 1];
			i--;
		}
		(*usuarios.usuarios[posicion]) = usuario;
		usuarios.contador++;
		if(usuarios.contador < MAX_USUARIOS)
			usuarios.usuarios[usuarios.contador]->id = CENTINELA;
		ok = true;
	}
	return ok;
}

bool cargar(tListaUsuarios& usuarios, string dominio) 
{
	// Carga una lista de usuarios desde un archivo.
	bool ok = true;
	ifstream archivo;
	string dominioUs = dominio + EXTUSUARIOS;
	archivo.open(dominioUs);
	int i = 0;
	if(archivo.is_open())
	{
		string aux;
		while((ok == true) && (i < MAX_USUARIOS))
		{
			ok = cargar(*usuarios.usuarios[i], archivo);
			if(ok)
				i++;
		}
		ok = true;
		usuarios.contador = i;
		usuarios.usuarios[i]->id = CENTINELA;
	}
	else
	{
		ok = false;
	}
	return ok;
}

void guardar(const tListaUsuarios& usuarios, string dominio) 
{
	// Guarda una lista de usuarios en un archivo.
	string dominioUs = dominio + EXTUSUARIOS;
	ofstream archivo;
	archivo.open(dominioUs);
	for(int i = 0; i < usuarios.contador; i++)
	{
		guardar(*usuarios.usuarios[i], archivo);
	}
	archivo << CENTINELA;
}

