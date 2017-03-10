/* Programa realizado por Jose Antonio Bernal Pérez y Javier Muñoz Sanchez de 1º C*/
/* Fundamentos de Programación. Universidad Complutense de Madrid.                */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

typedef enum { Nadie, Automata, Persona } tJugador;

tJugador quienEmpieza() // Determina quien empieza la partida en pasaCalculadora.
{
	srand(time(NULL));
	int turno = (rand() % 2) + 1;
	return tJugador(turno);
}

int digitoAleatorio() // Primer turno de Automata.
{
	int numero = (rand() % 9) + 1;
	return numero;
}

bool mismaFila(int ultimo, int numero) 
{
	int fila = (ultimo - 1) / 3;
	int numeroFila = (numero - 1) / 3;
	bool aux;
	if ((fila == numeroFila) || (numero == 0)) // Si el ultimo esta en la misma fila que el numero.
	{ 
		aux = true;
	}
	else
		aux = false;
	return aux;
}

bool mismaColumna(int ultimo, int numero)
{
	int columna = (ultimo - 1) % 3;
	int numeroColumna = (numero - 1) % 3;
	bool aux;
	if ((columna == numeroColumna) || (numero == 0)) // Si el ultimo esta en la misma columna que el numero.
	{ 
		aux = true;
	}
	else
		aux = false;
	return aux;
}

bool digitoValido(int ultimo, int numero)
{
	bool aux;
	if (((mismaFila(ultimo, numero) == true) || (mismaColumna(ultimo, numero) == true)) &&
		((numero >= 0) && (numero <= 9) && (numero != ultimo))) // Cualquier numero no valido para el juego no activaria este condicional.
	{
		aux = true;
	}
	else
		aux = false;
	return aux;
}

int digitoPersona() // Primer turno de Persona.
{
	cout << "7   8   9" << endl;
	cout << "4   5   6" << endl;
	cout << "1   2   3" << endl;
	cout << "Introduce un numero (0 para abandonar): ";
	int numero;
	cin >> numero;
	while (numero < 0 && numero > 9) // Bucle de error.
	{
		cout << "Ese numero no es correcto." << endl;
		cout << "7   8   9" << endl;
		cout << "4   5   6" << endl;
		cout << "1   2   3" << endl;
		cout << "Introduce un numero (0 para abandonar): ";
		cin >> numero;
	}
	return numero;
}

int digitoAutomata(int ultimo) // Automata elige un numero al azar que cumpla las reglas.
{
	int numero = digitoAleatorio();
	while (digitoValido(ultimo, numero) == false)
	{
		numero = digitoAleatorio();
	}
	return numero;
}

int digitoInteligente(int ultimo, int acumulado) // Automata elige un numero que cumpla una serie de criterios.
{
	int diferencia = 30 - acumulado;
	int numero = 0;
	if (((diferencia <= 9) && (diferencia > 0)) && (digitoValido(ultimo, diferencia) == true)) // Si puede sumar un numero valido tal que la diferencia sea igual a 30.
	{
		numero = diferencia;
	}
	else
	{
		numero = -1; // Dato negativo para que digitoValido(ultimo, numero) sea false y active el bucle.
		int columna = (ultimo - 1) % 3;
		while ((digitoValido(ultimo, numero) == false)) // De este bucle solo saldra un digito valido para el juego.
		{
			switch (columna) // Este switch sirve para que, si puede escoger el numero mas alto posible, que lo escoja.
			{
			case 0: // Columna 0.
			{
				if ((ultimo != 7) && ((acumulado + 7) <= 30))
				{
					numero = 7;
				}
				else
				{
					numero = digitoAleatorio();
					while (((numero + acumulado) > 30) && (acumulado != 30) && (ultimo != 1))
					{
						numero = digitoAleatorio();
					}
				}
				break;
			}
			case 1: // Columna 1.
			{
				if ((ultimo != 8) && ((acumulado + 8) <= 30))
				{
					numero = 8;
				}
				else
				{
					numero = digitoAleatorio();
					while (((numero + acumulado) > 30) && (acumulado < 29) && (ultimo != 2))
					{
						numero = digitoAleatorio();
					}
				}
				break;
			}
			case 2: // Columna 2.
			{
				if ((ultimo != 9) && ((acumulado + 9) <= 30))
				{
					numero = 9;
				}
				else
				{
					numero = digitoAleatorio();
					while (((numero + acumulado) > 30) && (acumulado < 28) && (ultimo != 3))
					{
						numero = digitoAleatorio();
					}
				}
				break;
			}
			} // Si no puede escoger el numero mas alto, escogera uno al azar que no sume 31 o mas, si es posible.
		} // Fin del bucle.
	}
	return numero;
}

int digitoPersona(int ultimo)
{
	cout << "7   8   9" << endl;
	cout << "4   5   6" << endl;
	cout << "1   2   3" << endl;
	cout << "Introduce un numero (0 para abandonar): ";
	int numero;
	cin >> numero;
	while (digitoValido(ultimo, numero) == false) // Bucle de error.
	{
		cout << "Ese numero no es correcto." << endl;
		cout << "7   8   9" << endl;
		cout << "4   5   6" << endl;
		cout << "1   2   3" << endl;
		cout << "Introduce un numero (0 para abandonar): ";
		cin >> numero;
	}
	return numero;
}

bool actInforme(int jugadas, int ganadas, int abandonos) // Actualiza el informe de estadisticas del juego.
{
	 int programa = 0; 
	 int tPrograma = 0;
	 int tJugadas = 0;
	 int tGanadas = 0;
	 int tAbandonos = 0;
	 if ((jugadas == 0) && (ganadas == 0) && (abandonos == 0)) // Usara este if al acabar el programa para sumar las veces que se ha usado el programa.
	 {
		 programa = 1;
	 } // Si no se usa el condicional, la funcion no actualizara el valor tPrograma, ya que programa == 0.

	 ifstream datos;
	 datos.open("informePC.txt");
	 if (datos.is_open()) // Si el archivo existe, coge los datos.
	 {
		 string f1; // Variable para coger las frases.
		 char aux = 'a'; // Quitar espacios y saltos de linea, coger dato centinela.
		 // Este código sirve para leer el archivo de informePC y coger sus datos para actualizarlo.
		 while (aux != ':')
		 {
			 datos.get(aux);
		 }
		 datos.get(aux); // Quita el espacio entre los dos puntos y el dato.
		 datos >> tPrograma;

		 while (aux != ':')
		 {
			 datos.get(aux);
		 }
		 datos.get(aux);
		 datos >> tJugadas;

		 while (aux != ':')
		 {
			 datos.get(aux);
		 }
		 datos.get(aux);
		 datos >> tGanadas;

		 while (aux != ':')
		 {
			 datos.get(aux);
		 }
		 datos.get(aux);
		 datos >> tAbandonos;
		 // Acaba la lectura de datos.
		 programa = programa + tPrograma; // Actualiza los datos.
		 jugadas = jugadas + tJugadas; 
		 ganadas = ganadas + tGanadas;
		 abandonos = abandonos + tAbandonos;
	 }
	 // Si el archivo no existe, no se leen los datos y se crea el archivo desde cero.
	 ofstream informe;
	 informe.open("informePC.txt");
	 informe << "Numero de veces que se ha utilizado el programa: " << programa << endl;
	 informe << "Numero total de partidas jugadas: " << jugadas << endl;
	 informe << "Numero total de partidas ganadas por el programa: " << ganadas << endl;
	 informe << "Numero total de abandonos: " << abandonos << endl;
	 informe.close();
	 return true;
}

tJugador pasaCalculadora(int dificultad) //Juego principal.
{
	int jugadas = 1;
	int ganadas = 0;
	int abandonos = 0;
	int acumulado = 0;
	int ultimo = 0;
	int turno = 0;
	int numero;
	turno = int(quienEmpieza()); // Hago turno tipo int para mayor comodidad.
	const int META = 31;
	while (acumulado < META) // Bucle del juego.
	{
		if ((turno == 1) || (turno == 2))
		{
			if (turno == 1) // Turno de Persona.
			{
				if (ultimo == 0)
				{
					cout << "Empiezas tu." << endl;
					numero = digitoPersona();
					if (numero == 0) // Cambia a un turno imposible.
					{
						turno = 100;
					}
					acumulado = acumulado + numero;
					cout << "Suma: " << acumulado << endl;
					ultimo = numero;
				}
				else
				{
					numero = digitoPersona(ultimo);
					if (numero == 0) // Cambia a un turno imposible.
					{
						turno = 100;
					}
					acumulado = acumulado + numero;
					cout << "Suma: " << acumulado << endl;
					ultimo = numero;
				}
				turno++; // Cambia el turno.
			}
			else if (turno == 2) // Turno de Automata. Dependiendo de la dificultad, la maquina usará un criterio u otro.
			{
				if (ultimo == 0) 
				{
					if (dificultad == 1) // Dificultad normal.
					{
						cout << "Empiezo yo." << endl;
						numero = digitoAleatorio();
						cout << "Yo pulso: " << numero << endl;
						acumulado = acumulado + numero;
						cout << "Suma: " << acumulado << endl;
						ultimo = numero;
					}
					if (dificultad == 2) // Dificultad difícil.
					{
						cout << "Empiezo yo." << endl;
						numero = digitoAleatorio();
						cout << "Yo pulso: " << numero << endl;
						acumulado = acumulado + numero;
						cout << "Suma: " << acumulado << endl;
						ultimo = numero;
					}
				}
				else
				{
					if (dificultad == 1) // Dificultad normal.
					{
						numero = digitoAutomata(ultimo);
						cout << "Yo pulso: " << numero << endl;
						acumulado = acumulado + numero;
						cout << "Suma: " << acumulado << endl;
						ultimo = numero;
					}
					if (dificultad == 2) // Dificultad difícil.
					{
						numero = digitoInteligente(ultimo, acumulado);
						cout << "Yo pulso: " << numero << endl;
						acumulado = acumulado + numero;
						cout << "Suma: " << acumulado << endl;
						ultimo = numero;
					}
				}
				turno--; // Cambia el turno.
			}
		}
		else // Cuando se ha introducido el numero 0.
		{
			acumulado = 32;
			cout << "Hasta Pronto " << "!" << endl;
		}
	} // Final del bucle.

	tJugador ganador = tJugador(turno);
	if (ganador == Automata) // Si gana el Jugador.
	{
		cout << "Enhorabuena! Has ganado." << endl;
	}

	else if (ganador == Persona) // Si gana la máquina.
	{
		cout << "Lo siento, has perdido." << endl;
		ganadas++;
	}
	else // Si abandonas.
	{
		cout << "Abandonaste." << endl;
		abandonos++;
	}
	actInforme(jugadas, ganadas, abandonos); // Actualiza los datos del informe al final del juego.
	return ganador;
} // Termina el juego.

int menu()
{
	int opcion = 0;
	cout << "Selecciona una opcion." << endl << endl;
	cout << "1 - Jugar" << endl;
	cout << "2 - Acerca de" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opcion: ";
	cin >> opcion;
	while ((opcion < 0) || (opcion > 2))
	{
		cout << "Opcion incorrecta." << endl;
		cout << "Selecciona una opcion." << endl << endl;
		cout << "1 - Jugar" << endl;
		cout << "2 - Acerca de" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
	}
	return opcion;
}

bool mostrar(string nombArch) // Lee el archivo.
{
	ifstream acercaDe;
	bool auxb;
	acercaDe.open(nombArch); // Esta linea da error en el compilador de MinGW, solo admite cadenas literales entre parentesis.
	// Compilado en Visual Studio funciona perfectamente.
	if(acercaDe.is_open()) // Si el archivo existe y se ha abierto.
	{
		string frase = "Hola.";
		while (!acercaDe.eof()) // Se repite hasta que acabe el archivo. acercaDe.eof() devuelve true si el archivo ha finalizado. Puede no funcionar en algunos S. O.
		{
			getline(acercaDe, frase);
			cout << frase << endl;
		}
		cout << endl << "Pulsa INTRO para acceder al menu." << endl;
		cin.sync();
		cin.get();
		auxb = true;
	}

	else // Si no se ha podido abrir el archivo.
	{
		cout << "No se pudo abrir el archivo o no existe." << endl;
		auxb = false;
	}

	return auxb;
}

int main()
{
	cout << "¡Bienvenido a Pasa la calculadora!" << endl << "¿Como te llamas? ";
	string nombre;
	cin >> nombre;
	cout << "Hola " << nombre << "." << endl;
	cin.sync();
	int opcion = menu();
	while (opcion != 0) // Bucle para repetir el menu en caso de error.
	{
		if (opcion == 1)
		{
			cout << "Introduce la dificultad que desees." << endl;
			cout << "1. Normal." << endl;
			cout << "2. Dificil." << endl;
			cout << "Dificultad: ";
			int dificultad;
			cin >> dificultad;
			while ((dificultad < 1) && (dificultad > 2)) // Bucle de dificultad.
			{
				cout << "Esa dificultad no existe." << endl;
				cout << "Introduce la dificultad que desees." << endl;
				cout << "1. Normal." << endl;
				cout << "2. Dificil." << endl;
				cout << "Dificultad: ";
				cin >> dificultad;
			} // Final del bucle de dificultad.
			pasaCalculadora(dificultad);
		}
		if (opcion == 2)
		{
			mostrar("VersionPC.txt");
		}
		opcion = menu();
	} // Final del bucle de opcion.

	actInforme(0, 0, 0); // Añade 1 a las veces que se ha usado el programa en el informe.
	cin.sync();
	cout << "Hasta Pronto!" << endl << "Pulsa INTRO para salir." << endl;
	cin.get();
	return 0;
}