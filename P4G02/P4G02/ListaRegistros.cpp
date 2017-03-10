#include "ListaRegistros.h"

using namespace std;

const string CENTINELA_REG = "XXX";
const int CENTINELA_CARG = 0;

void inicializar(tListaRegistros &listaReg) // Inicializa una lista de registros.
{
	listaReg.registros[0].ident = CENTINELA_REG;
	listaReg.registros[0].leido = 0;
	listaReg.contador = 0;
}

bool insertar(tListaRegistros &listaReg, tRegistro registro) // Inserta un registro en una lista de registros.
{
	bool ok = false;
	if(listaReg.contador < MAX_REGISTROS)
	{
		listaReg.registros[listaReg.contador].ident = registro.ident;
		listaReg.registros[listaReg.contador].leido = registro.leido;
		listaReg.contador++;
		ok = true;
	}
	return ok;
}

void cargar(tListaRegistros &listaReg, ifstream& archivo) // Carga una lista de registros desde un fichero.
{
	inicializar(listaReg);
	int contador;
	archivo >> contador;
	if((contador >= 1) && (contador <= MAX_REGISTROS))
	{
		int j = 0;
		while(j < contador)
		{
			tRegistro registro;
			archivo >> registro.ident;
			archivo >> registro.leido;
			insertar(listaReg, registro);
			j++;
		}
	}
}

void guardar(const tListaRegistros &listaReg, ofstream& archivo) // Guarda una lista de registros en un fichero.
{
	archivo << listaReg.contador;
	archivo << endl;
	for(int i = 0; i < listaReg.contador; i++)
	{
		archivo << listaReg.registros[i].ident;
		archivo << " ";
		archivo << listaReg.registros[i].leido;
		archivo << endl;
	}
}

int buscar(const tListaRegistros &listaReg, string id) // Busca un registro.
{
	int i = 0;
	while((i < listaReg.contador) && (listaReg.registros[i].ident != id))
	{
		i++;
	}
	if(listaReg.registros[i].ident != id)
	{
		i = -1;
	}
	return i;
}

bool borrar(tListaRegistros &listaReg, string id) // Borra un registro de una lista de registros.
{
	int posicion = buscar(listaReg, id);
	bool ok = false;
	if(posicion != -1)
	{
		int i = listaReg.contador;
		if((posicion + 1 != i))
		{
			while((posicion + 1) < i)
			{
				listaReg.registros[posicion].ident = listaReg.registros[(posicion + 1)].ident;
				listaReg.registros[posicion].leido = listaReg.registros[(posicion + 1)].leido;
				posicion++;
			}
			listaReg.contador--;
			ok = true;
		}
		else
		{
			listaReg.registros[posicion].ident = "";
			listaReg.registros[posicion].leido = 1;
			listaReg.contador--;
		}
	}
	return ok;
}

bool correoLeido(tListaRegistros &listaReg, string id) // Marca un correo como leido.
{
	int posicion = buscar(listaReg, id);
	bool ok = false;
	if(posicion != -1)
	{
		listaReg.registros[posicion].leido = 1;
		ok = true;
	}
	return ok;
}