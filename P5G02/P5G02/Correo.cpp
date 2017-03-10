#include "Correo.h"
#include <iostream> // Entrada/salida de datos por consola.
#include <ctime> // Biblioteca para usar el tiempo del S. O.
#include <sstream> // Biblioteca para usar variables tipo stringstream.
#include <iomanip> // Permite manipular el formato de la salida por consola.
#include <fstream> // Entrada/salida de datos por archivo.

using namespace std;

const string CENTINELA_CORREOS = "XXX"; // Centinela de carga para los correos.
const char CENTINELA = 'X'; // Centinela que marca el final de un asunto/cuerpo, tipo char.
const string CENTINELASTR = "X"; // Centinela que marca el final de un asunto/cuerpo, tipo string.
const string DESTINATARIO = "Destinatario del correo (incluye el dominio): "; // Salida de consola para pedir el destinatario de un correo.
const string ASUNTO = "Escribe el asunto del correo: "; // Pide el asunto de un correo.
const string CUERPO = "Escribe el correo (escribe X para finalizar): "; // Pide el contenido del correo.
const string ASUNTORE = "Re: "; // String que añade el programa al asunto al contestar un correo.
const string DE = "De: "; // Salida de consola, despues se indica el emisor.
const string PARA = "Para: "; // Salida de consola, despues se indica el destinatario.
const string ASUNTOCADENA = "Asunto: "; // Salida de consola, despues se indica el asunto de un correo.

void correoNuevo(tCorreo &correo, std::string emisor) 
{
	// Crea un correo nuevo.
	correo.emisor = emisor;
	cout << DESTINATARIO;
	cin.sync();
	cin >> correo.destinatario;
	cout << ASUNTO;
	cin.sync();
	string asunto;
	getline(cin, asunto);
	correo.asunto = asunto;
	cout << CUERPO << endl;
	cin.sync();
	string cuerpo;
	stringstream cuerpoEnt;
	getline(cin, cuerpo);
	while (cuerpo != CENTINELASTR) // Convierte todas las palabras del cuerpo en un string.
	{
		cuerpoEnt << cuerpo;
		getline(cin, cuerpo);
	}
	correo.cuerpo = cuerpoEnt.str();
	correo.fecha = time(0);
	stringstream id;
	id << correo.emisor << "_" << correo.fecha;
	correo.ident = id.str();
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, std::string emisor) 
{
	// Crea un correo respuesta de otro.
	correo.emisor = emisor;
	correo.destinatario = correoOriginal.emisor;
	correo.asunto = ASUNTORE + correoOriginal.asunto;
	cout << CUERPO;
	cin.sync();
	stringstream cuerpo;
	string cuerpoPart;
	stringstream cuerpoEnt;
	getline(cin, cuerpoPart);
	while (cuerpoPart != CENTINELASTR) // Concatena el cuerpo del correoOriginal con el del correo contestacion.
	{
		cuerpoEnt << cuerpoPart << " ";
		getline(cin, cuerpoPart);
	}
	cuerpo << correoOriginal.cuerpo << endl << endl << endl << cuerpoEnt.str();
	correo.cuerpo = cuerpo.str();
	correo.fecha = time(0);
	stringstream id;
	id << correo.emisor << "_" << correo.fecha;
	correo.ident = id.str();
}

string mostrarFecha(tFecha fecha) 
{   
	// Muestra la fecha (fecha y hora) de un correo.
	stringstream resultado;
	tm ltm;

	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	resultado << " (" << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << ")";

	return resultado.str();
}

string mostrarFechaSoloDia(tFecha fecha) 
{
	// Muestra la fecha (solo fecha) de un correo.
	stringstream resultado;
	tm ltm;

	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;

	return resultado.str();
}

string aCadena(const tCorreo &correo) 
{
	// Traduce a string (para sacar por consola) un correo.
	stringstream inform;
	inform << DE << correo.emisor << "            " << mostrarFecha(correo.fecha) << endl;
	inform << PARA << correo.destinatario << endl;
	inform << ASUNTOCADENA << correo.asunto << endl << endl;
	inform << correo.cuerpo << endl << endl;
	string aux = inform.str();
	cout << aux;
	return inform.str();
}

string obtenerCabecera(const tCorreo &correo) 
{
	// Obtiene la cabecera (para mostrar en bandeja de entrada) de un correo.
	stringstream cabecera;
	cabecera << setw(20) << correo.emisor;
	cabecera << " " <<  setw(37) << correo.asunto;
	cabecera << " " << setw(13) << mostrarFechaSoloDia(correo.fecha) << endl;;
	return cabecera.str();
}

bool cargar(tCorreo &correo, std::ifstream& archivo) 
{
	// Carga un correo de un archivo.
	bool ok = false;
	string centinela;
	archivo >> centinela;
	if (centinela != CENTINELA_CORREOS) // Si no hemos llegado al final de la lista de correos del archivo.
	{
		correo.ident = centinela;
		archivo >> correo.fecha;
		archivo >> correo.emisor;
		archivo >> correo.destinatario;
		archivo.get();
		getline(archivo, correo.asunto);
		stringstream cuerpo;
		string fraseCuerpo;
		getline(archivo, fraseCuerpo);
		while (fraseCuerpo != CENTINELASTR)
		{
			cuerpo << fraseCuerpo;
			getline(archivo, fraseCuerpo);
		}
		correo.cuerpo = cuerpo.str();
		ok = true;
	}
	return ok;
}

void guardar(const tCorreo &correo, std::ofstream& archivo) 
{
	// Guarda un correo en un archivo.
	archivo << correo.ident << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo << endl;
	archivo << CENTINELA << endl;
}