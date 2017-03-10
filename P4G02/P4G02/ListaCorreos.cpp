#include "ListaCorreos.h"

#include <fstream> // Entrada/salida de datos por fichero.
using namespace std;

const string CENTINELA = "XXX"; // Centinela para finalizar una lista de correos.
const string EXTCORREOS = "_correos.txt"; // Extension para el archivo de la lista de correos.

void inicializar(tListaCorreos &correos) // Inicializa una lista de correos.
{
	correos.listaCorreo[0].ident = CENTINELA;
	correos.numCorreos = 0;
}

bool buscar(const tListaCorreos &correos, string id, int &pos) // Busca un correo por su id en una lista de correos.
{
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

bool insertar(tListaCorreos &correos, const tCorreo &correo) // Inserta un correo ordenadamente en una lista de correos.
{
	int posicion = 0;
	bool ok = buscar(correos, correo.ident, posicion);
	int i = correos.numCorreos;
	int j = 0;
	while (i > posicion)
	{
		correos.listaCorreo[i].ident = correos.listaCorreo[(i - 1)].ident;
		correos.listaCorreo[i].emisor = correos.listaCorreo[(i - 1)].emisor;
		correos.listaCorreo[i].destinatario = correos.listaCorreo[(i - 1)].destinatario;
		correos.listaCorreo[i].asunto = correos.listaCorreo[(i - 1)].asunto;
		correos.listaCorreo[i].cuerpo = correos.listaCorreo[(i - 1)].cuerpo;
		correos.listaCorreo[i].fecha = correos.listaCorreo[(i - 1)].fecha;
		i--;
	}
	correos.listaCorreo[posicion].ident = correo.ident;
	correos.listaCorreo[posicion].emisor = correo.emisor;
	correos.listaCorreo[posicion].destinatario = correo.destinatario;
	correos.listaCorreo[posicion].asunto = correo.asunto;
	correos.listaCorreo[posicion].cuerpo = correo.cuerpo;
	correos.listaCorreo[posicion].fecha = correo.fecha;
	correos.numCorreos++;
	return ok;
}

bool cargar(tListaCorreos &correos, string dominio) // Carga una lista de correos de un archivo.
{
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
		while ((correo.ident != CENTINELA) && (i < MAX_CORREOS) && (max == true))
		{
			max = cargar(correo, archivo);
			if (max == true)
			{
				correos.listaCorreo[i].ident = correo.ident;
				correos.listaCorreo[i].emisor = correo.emisor;
				correos.listaCorreo[i].destinatario = correo.destinatario;
				correos.listaCorreo[i].asunto = correo.asunto;
				correos.listaCorreo[i].cuerpo = correo.cuerpo;
				correos.listaCorreo[i].fecha = correo.fecha;
				i++;
			}
			else
			{
				correos.listaCorreo[i].ident = CENTINELA;
			}
		}
		correos.listaCorreo[i].ident = CENTINELA;
		correos.numCorreos = i;
	}
	archivo.close();
	return ok;
}

void guardar(const tListaCorreos &correos, string dominio) // Guarda una lista de correos en un archivo.
{
	string nombreArchivo = dominio + EXTCORREOS;
	ofstream archivo;
	archivo.open(nombreArchivo);
	tCorreo correo;
	int i = 0;
	while ((correos.listaCorreo[i].ident != CENTINELA) && (i < MAX_CORREOS) && (i < correos.numCorreos))
	{
		correo.ident = correos.listaCorreo[i].ident;
		correo.emisor = correos.listaCorreo[i].emisor;
		correo.destinatario = correos.listaCorreo[i].destinatario;
		correo.asunto = correos.listaCorreo[i].asunto;
		correo.cuerpo = correos.listaCorreo[i].cuerpo;
		correo.fecha = correos.listaCorreo[i].fecha;
		guardar(correo, archivo);
		i++;
	}
	archivo << CENTINELA;
	archivo.close();
}

void ordenar_AF(tListaCorreos &correos) // Ordena por asunto y fecha una lista de correos.
{
	tListaCorreos listaOrdenada;
	inicializar(listaOrdenada);
	for (int i = 0; i < correos.numCorreos; i++)
	{
		insertar(listaOrdenada, correos.listaCorreo[i]);
	}
	for (int i = 0; i < correos.numCorreos; i++)
	{
		correos.listaCorreo[i].ident = listaOrdenada.listaCorreo[i].ident;
		correos.listaCorreo[i].asunto = listaOrdenada.listaCorreo[i].asunto;
		correos.listaCorreo[i].emisor = listaOrdenada.listaCorreo[i].emisor;
		correos.listaCorreo[i].destinatario = listaOrdenada.listaCorreo[i].destinatario;
		correos.listaCorreo[i].cuerpo = listaOrdenada.listaCorreo[i].cuerpo;
		correos.listaCorreo[i].fecha = listaOrdenada.listaCorreo[i].fecha;
	}
	correos.numCorreos = listaOrdenada.numCorreos;
	correos.listaCorreo[correos.numCorreos].ident = CENTINELA;
}