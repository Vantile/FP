// Jose Antonio Bernal Pérez. 1º C. Fundamentos de Programacion.
// Practica 5.

#include "Gestor.h"
#include <string> // Permite usar variables tipo string.
#include <iostream> // Entrada/salida de datos por consola.
#include <vld.h> // Encabezado de Visual Leak Detector.

using namespace std;

const string DOMINIO = "fdimail.com"; // Dominio del sistema de correos.
const string MAINOP1 = "1. Iniciar sesion."; // Opcion 1 de main.
const string MAINOP2 = "2. Crear cuenta nueva."; // Opcion 2 de main.
const string MAINOP0 = "0. Salir."; // Opcion 0 de main.
const string OPMAIN = "Elija la opcion deseada: "; // Pide una opcion para el menu main.
const string ERRMAIN = "Opcion incorrecta. Introduzca una opcion: "; // Error de opcion incorrecta en main.
const string ERRSES = "No ha sido posible iniciar sesion."; // Error de inicio de sesion.
const string ERRCRE = "No ha sido posible crear la cuenta."; // Error al crear una cuenta.
const string DESP = "Hasta pronto!"; // Mensaje de despedida.
const string ENTER = "Pulsa ENTER para continuar..."; // Pide ENTER para continuar.

int main()
{
	tGestor gestor;
	int opcion = -1;
	arrancar(gestor, DOMINIO);
	while(opcion != 0)
	{
		system("cls");
		cout << MAINOP1 << endl;
		cout << MAINOP2 << endl;
		cout << MAINOP0 << endl;
		cout << OPMAIN;
		cin >> opcion;
		while((opcion < 0) || (opcion > 2))
		{
			cout << ERRMAIN;
			cin.sync();
			cin >> opcion;
		}
		switch(opcion)
		{
		case 1: // Iniciar sesion.
			{
				bool ok = iniciarSesion(gestor);
				bool entrada = true;
				int opcion2 = -1;
				while((opcion2 != 0) && (ok == true))
				{
					opcion2 = menuBandeja(gestor, entrada);
					ejecutarMenuBandeja(gestor, opcion2, entrada);
				}
				if(ok == false)
					cout << ERRSES;
			}
			break;
		case 2: // Crear cuenta.
			{
				bool ok = crearCuenta(gestor);
				bool entrada = true;
				int opcion2 = -1;
				while((opcion2 != 0) && (ok == true))
				{
					opcion2 = menuBandeja(gestor, entrada);
					ejecutarMenuBandeja(gestor, opcion2, entrada);
				}
				if(!ok)
					cout << ERRCRE;
			}
			break;
		}
		cout << endl << ENTER << endl;
		cin.sync();
		cin.get();
	}
	cout << endl << DESP << endl;
	apagar(gestor);
}