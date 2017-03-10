#include "ListaCorreos.h"

#include <fstream> // Entrada/salida de datos por fichero.
using namespace std;

const string CENTINELA = "XXX"; // Centinela para finalizar una lista de correos.
const string EXTCORREOS = "_correos.txt"; // Extension para el archivo de la lista de correos.
const int DIMCORREOS = 10;

void inicializar(tListaCorreos &correos) 
{
	// Inicializa una lista de correos.
	if(correos.dimension > DIMCORREOS)
	{
		correos.numCorreos = 0;
	}
	else
	{
		correos.dimension = DIMCORREOS;
		correos.listaCorreo = new tCorreo[DIMCORREOS];
		correos.numCorreos = 0;
	}
}

void redimensionar(tListaCorreos &correos)
{
	// Redimensiona una listaCorreos para que aumente/disminuya su tamaño.
	int nuevaDim = correos.dimension;
	tCorreoPtr nuevaLista = new tCorreo[nuevaDim];
	for(int i = 0; i < correos.numCorreos; i++)
	{
		nuevaLista[i] = correos.listaCorreo[i];
	}
	delete [] correos.listaCorreo;
	correos.listaCorreo = nuevaLista;
}

void destruir(tListaCorreos &correos)
{
	// Destruye de la memoria dinámica un dato tipo tListaCorreos.
	delete [] correos.listaCorreo;
}

bool buscar(const tListaCorreos &correos, string id, int &pos) 
{
	// Busca un correo por su id en una lista de correos.
	int ini = 0;
	int fin = correos.numCorreos;
	int mitad = fin / 2;
	bool ok = false;
	while ((correos.listaCorreo[mitad].ident != id) && (ini < fin)) // Busqueda binaria en la lista de correos.
	{
		if (correos.listaCorreo[mitad].ident > id)
		{
			fin = mitad;
		}
		else
		{
			ini = mitad + 1;
		}
		mitad = (fin + ini) / 2;
	}
	if (correos.listaCorreo[mitad].ident == id)
	{
		ok = true;
	}
	pos = mitad; // Devuelve la posicion donde esta el correo o donde deberia estar.
	return ok;
}

bool insertar(tListaCorreos &correos, const tCorreo &correo) 
{
	// Inserta un correo ordenadamente en una lista de correos.
	if(correos.numCorreos >= correos.dimension)
	{
		int dimension = ((correos.dimension * 3) /2) + 1;
		correos.dimension = dimension;
		redimensionar(correos);
	}
	int posicion = 0;
	bool ok = buscar(correos, correo.ident, posicion);
	int i = correos.numCorreos;
	int j = 0;
	while (i > posicion)
	{
		correos.listaCorreo[i] = correos.listaCorreo[(i - 1)];
		i--;
	}
	correos.listaCorreo[posicion] = correo;
	correos.numCorreos++;
	return ok;
}

bool cargar(tListaCorreos &correos, string dominio) 
{
	// Carga una lista de correos de un archivo.
	string nombreArchivo = dominio + EXTCORREOS;
	ifstream archivo;
	bool ok = false;
	archivo.open(nombreArchivo);
	if (archivo.is_open())
	{
		tCorreo correo;
		correo.ident = "0";
		ok = true;
		bool max = true;
		int i = 0;
		int correosEnLista = 0;
		archivo >> correosEnLista;
		if(correosEnLista >= correos.dimension)
		{
			int dimension = correosEnLista;
			dimension++;
			while((dimension % 10) != 0)
				dimension++;
			correos.dimension = dimension;
			redimensionar(correos);
		}
		while ((i < correosEnLista) && (i < MAX_CORREOS) && (max == true))
		{
			max = cargar(correo, archivo);
			if (max == true)
			{
				correos.listaCorreo[i] = correo;
				i++;
			}
		}
		correos.numCorreos = i;
	}
	archivo.close();
	return ok;
}

void guardar(const tListaCorreos &correos, string dominio) 
{
	// Guarda una lista de correos en un archivo.
	string nombreArchivo = dominio + EXTCORREOS;
	ofstream archivo;
	archivo.open(nombreArchivo);
	tCorreo correo;
	int i = 0;
	archivo << correos.numCorreos << endl;
	while ((i < MAX_CORREOS) && (i < correos.numCorreos))
	{
		correo = correos.listaCorreo[i];
		guardar(correo, archivo);
		i++;
	}
	archivo.close();
}

void ordenar_AF(tListaCorreos &correos) 
{
	// Ordena por asunto y fecha una lista de correos.
	int pos;
	tCorreo correo;
	for(int i = 1; i < correos.numCorreos; i++)
	{
		correo = correos.listaCorreo[i];
		pos = 0;
		while((pos < i) && !(correos.listaCorreo[pos].asunto > correo.asunto))
		{		
			pos++;
		}
		if((correos.listaCorreo[pos].asunto == correo.asunto) && (correos.listaCorreo[pos].fecha > correo.fecha))
				pos++;
		for(int j = i; j > pos; j--)
			correos.listaCorreo[j] = correos.listaCorreo[j - 1];
		correos.listaCorreo[pos] = correo;
	}
}