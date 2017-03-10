// Escrito por Jose Antonio Bernal Pérez y Javier Muñoz Sanchez. 1ºC, Fundamentos de Programacion, Universidad Complutense de Madrid.
// Practica 3. 2048.

/*---------- Bibliotecas utilizadas ----------*/

#include <iostream> // Entrada y salida de datos por consola.
#include <fstream> // Entrada y salida de datos de fichero.
#include <iomanip> // Organizacion de la salida de datos por consola.
#include <ctime> // Permite acceder al reloj de Windows.
#include <string> // Permite manipular cadenas tipo string.
#include <cstdlib> // Permite utilizar la funcion rand().
#include <Windows.h> // Permite cambiar los colores de fondo de la consola.
#include <conio.h> // Permite utilizar la funcion _getch().

/*---------- Espacios de nombres usados ----------*/

using namespace std; // Facilita el uso de funciones de iostream.

/*---------- Constantes utilizadas ----------*/

const int TAMANO = 4; // Tamaño de la tabla de juego. Dimension TAMANOxTAMANO.
const int MAXRECORD = 10; // Maximo de puntuaciones guardadas en la lista de records.
const int CASILLATOPE = 2048; // Maximo valor que puede tener una casilla.

// Caracteres usados para construir el tablero.
const char SUPIZQ = char(218); // Caracter de la esquina superior izquierda.
const char HORIZO = char(196); // Caracter de linea horizontal.
const char SUPCRU = char(194); // Caracter de cruceta de la parte superior.
const char SUPDER = char(191); // Caracter de la esquina superior derecha.
const char VERTIC = char(179); // Caracter de linea vertical.
const char IZQCRU = char(195); // Caracter de cruceta de la parte izquierda.
const char CRUCET = char(197); // Caracter de cruceta central.
const char DERCRU = char(180); // Caracter de cruceta de la parte derecha.
const char INFIZQ = char(192); // Caracter de la esquina inferior izquierda.
const char INFCRU = char(193); // Caracter de cruceta de la parte inferior.
const char INFDER = char(217); // Caracter de la esquina inferior derecha.

// Frases utilizadas en el programa.
const string CARGAR = "Quiere cargar una partida guardada? (s/n)"; // Pregunta si cargar una partida.
const string GUARDAR = "Quieres guardar la partida? (S/N): "; // Pregunta si guardar una partida.
const string NOMBREGUARD = "Que nombre quieres ponerle a tu partida? (incluye el .txt): "; // Pregunta que nombre ponerle a tu partida.
const string PERDIDA = "Lo siento, has perdido."; // Frase al perder la partida.
const string GANADA = "Enhorabuena, has ganado!"; // Frase al ganar la partida.
const string PUNTUAC = "Puntuacion total: "; // Muestra la puntuacion total al perder/ganar la partida.
const string ADIOS = "Hasta pronto!"; // Frase al acabar el juego.
const string PUNTOS = "Puntos: "; // Muestra la puntuacion en este turno.
const string PUNTOSTOT = "  Puntos totales: "; // Muestra la puntuacion en la partida.
const string CONTINUAR = "Usa las flechas para jugar. ESC para salir."; // Frase para guiar al usuario para continuar la partida.
const string ARCHIVOPRED = "tablero.txt"; // Archivo predeterminado para cargar/guardar la partida.
const string ARCHIVOCARG = "Introduce el nombre del archivo a cargar (.txt incluido): "; // Pide al usuario un nombre para cargar/guardar un archivo.
const string ERRORCARG = "No se pudo cargar la tabla. Pulsa ENTER para empezar una nueva partida."; // Error al no poder cargar un archivo.
const string RECORDSPRED = "records.txt"; // Archivo predeterminado para cargar/guardar los records.
const string CENTINELA = "???"; // Centinela de la lista de records.
const string NUEVORECORD = "Has batido un record! Cual es tu nombre?: "; // Frase que anuncia un nuevo record.
const string MUESTRARECORD = "Esta es la tabla de records: "; // Muestra la tabla de records.

/*---------- Tipos declarados por el usuario ----------*/

typedef enum {Arriba, Abajo, Derecha, Izquierda, Salir, Nada} tAccion; // Accion a realizar por el tablero.
typedef int tTablero[TAMANO][TAMANO]; // Tablero usado en el juego.
typedef string tNombres[MAXRECORD]; // Nombres en la lista de records.
typedef int tPuntuacion[MAXRECORD]; // Puntuaciones en la lista de records.
typedef struct
{
	tNombres nombre;
	tPuntuacion puntuacion;
} tRecords; // Estructura de la lista de records.

/*---------- Funciones usadas en el programa ----------*/

void colorFondo(int color); // Funcion usada para cambiar el color de fondo de la consola.

void inicializa(tTablero tablero); // Inicializa el tablero; rellena dos casillas al azar.

int log2(int num); // Devuelve el logaritmo en base 2 de un numero.

void visualiza(const tTablero tablero, int puntos, int totalPuntos); // Dibuja el tablero en consola.

void carga(tTablero tablero, int &puntos); // Carga un tablero desde un archivo a elegir.

tAccion leeAccion(); // Coge una accion por teclado y la devuelve.

void mueveFichas(tTablero tablero, tAccion accion); // Mueve las fichas del tablero dependiendo de la accion.

int mayor(const tTablero tablero); // Devuelve el numero mas grande que haya en el tablero.

bool lleno(const tTablero tablero); // Devuelve true si el tablero esta lleno y no permite combinaciones.

void combinaFichas(tTablero tablero, tAccion accion, int &puntos); // Combina las fichas del tablero dependiendo de la accion.

void nuevaFicha(tTablero tablero); // Añade una nueva ficha al tablero en una casilla vacia.

void nuevoRecord(int puntos); // Actualiza el listado de records cuando hay un nuevo record.

void muestraRecords(); // Muestra la lista de records por pantalla.

void guarda(const tTablero tablero, int puntos); // Guarda una partida en un fichero.

/*---------- Codigo del programa ----------*/

int main()
{
	srand(time(NULL)); // Semilla de la funcion rand().
	colorFondo(0); // Fondo negro.
	tTablero tablero;
	int puntos = 0;
	int totalPuntos = 0;
	tAccion accion = Nada;
	cout << CARGAR << endl;
	char siNo;
	cin.sync();
	cin >> siNo;
	inicializa(tablero);
	if (siNo == 's') // Cargar partida? Si/No
	{
		carga(tablero, puntos);
		totalPuntos = puntos;
	}
	bool llenoB = lleno(tablero);
	int mayorI = mayor(tablero);
	while ((accion != Salir) && (llenoB == false) && (mayorI < CASILLATOPE)) // Mientras no pulse ESC, ni este lleno el tablero, ni se llene a CASILLATOPE.
	{
		// Aqui transcurre la partida hasta que se cumple alguna de las condiciones para salir.
		visualiza(tablero, puntos, totalPuntos);
		accion = leeAccion();
		mueveFichas(tablero, accion);
		puntos = 0;
		combinaFichas(tablero, accion, puntos);
		llenoB = lleno(tablero);
		mayorI = mayor(tablero);
		if (llenoB == false) // Si el tablero no esta lleno.
		{
			nuevaFicha(tablero);
		}
		totalPuntos = totalPuntos + puntos;
	}
	system("cls"); // Limpia la consola.
	if (accion == Salir) // Si se pulsa ESC.
	{
		cout << GUARDAR;
		cin.sync();
		cin >> siNo;
		if (siNo == 's') // Guardar partida? Si/No.
		{
			guarda(tablero, totalPuntos);
		}
	}
	if (llenoB == true) // Si el tablero esta lleno y no hay combinaciones.
	{
		cout << endl << PERDIDA;
		cout << endl << PUNTUAC << totalPuntos << ".";
	}
	if (mayorI == CASILLATOPE) // Si has llegado a CASILLATOPE.
	{
		cout << endl << GANADA;
		cout << endl << PUNTUAC << totalPuntos << ".";
		nuevoRecord(totalPuntos);
		muestraRecords();
	}
	// Fin del juego.
	cout << endl << ADIOS << endl;
	cin.sync();
	cin.get();
}

void colorFondo(int color) // Funcion usada para cambiar el color de fondo de la consola.
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void inicializa(tTablero tablero) // Inicializa el tablero; rellena dos casillas al azar.
{
	for (int i = 0; i < TAMANO; i++) // Vacia todas las casillas del tablero.
	{
		for (int j = 0; j < TAMANO; j++)
		{
			tablero[i][j] = 1;
		}
	}
	int cas = 0; // Numero de casillas rellenadas.
	int num = 0;
	int i = 0;
	int j = 0;
	while (cas < 2) // Hasta que se rellenen 2 casillas.
	{
		i = rand() % TAMANO;
		j = rand() % TAMANO;
		if (tablero[i][j] == 1)
		{
			int cuatro = 0;
			num = rand() % 100;
			if (num < 95) // 95% de probabilidades de que rellenen con un 2.
			{
				tablero[i][j] = 2;
			}
			else // 5% de probabilidades de que se rellenen con un 4. (Solo un 4 a la vez)
			{
				if (cuatro == 0)
				{
					tablero[i][j] = 4;
					cuatro++;
				}
				else
				{
					tablero[i][j] = 2;
				}
			}
		}
		cas++;
	}
}

int log2(int num) // Devuelve el logaritmo en base 2 de un numero.
{
	int i = 0;
	int aux = 1;
	while (aux != num)
	{
		aux = aux * 2;
		i++;
	}
	return i;
}

void visualiza(const tTablero tablero, int puntos, int totalPuntos) // Dibuja el tablero en consola.
{
	system("cls"); // Limpia la consola.
	cout << endl;
	cout << PUNTOS << setw(6) << right << puntos; // Muestra los puntos de este movimiento.
	cout << PUNTOSTOT << setw(6) << right << totalPuntos << endl; // Muestra los puntos totales.
	int filas = (TAMANO * 4); // Filas del tablero.
	int columnas = (TAMANO * 6); // Columnas del tablero.
	int primeraFila = 0;
	for (int i = 0; i <= filas; i++) // Recorre todas las filas para mostrarlas en pantalla.
	{
		// Este bucle esta hecho para poder hacer una tabla de dimension TAMANOxTAMANO, sin importar cuanto valga TAMANO.
		if (i == 0) // Si es la primera fila del tablero.
		{
			cout << SUPIZQ;
			int j = 0;
			while (j < columnas)
			{
				cout << HORIZO << HORIZO << HORIZO << HORIZO << HORIZO << HORIZO;
				j = j + 6;
				if (j == columnas)
				{
					cout << SUPDER;
				}
				else
				{
					cout << SUPCRU;
				}
			}
			cout << endl;
		}

		if (((i % 4) == 0) && (i != 0) && (i != filas)) // Si es una fila entre casillas del tablero.
		{
			cout << IZQCRU;
			int j = 0;
			while (j < columnas)
			{
				cout << HORIZO << HORIZO << HORIZO << HORIZO << HORIZO << HORIZO;
				j = j + 6;
				if (j == columnas)
				{
					cout << DERCRU;
				}
				else
				{
					cout << CRUCET;
				}
			}
			cout << endl;
		}

		if (i == filas) // Si es la ultima fila del tablero.
		{
			cout << INFIZQ;
			int j = 0;
			while (j < columnas)
			{
				cout << HORIZO << HORIZO << HORIZO << HORIZO << HORIZO << HORIZO;
				j = j + 6;
				if (j == columnas)
				{
					cout << INFDER;
				}
				else
				{
					cout << INFCRU;
				}
			}
			cout << endl;
		}

		if (((i + 2) % 4) == 0) // Si es una fila en mitad de una casilla.
		{
			cout << VERTIC;
			int j = 1;
			for (int k = 0; k < TAMANO; k++)
			{
				colorFondo(log2(tablero[(i / 4)][k]));
				if (tablero[(i / 4)][k] != 1)
				{
					cout << " " << right << setw(4) << tablero[(i / 4)][k] << " ";
				}
				else
				{
					cout << right << setw(6) << " ";
				}
				colorFondo(0);
				cout << VERTIC;
			}
			cout << endl;
		}
		if ((i % 2) != 0) // Si es una fila que no es ninguna de las anteriores.
		{
			cout << VERTIC;
			int j = 1;
			for (int k = 0; k < TAMANO; k++)
			{
				colorFondo(log2(tablero[(i / 4)][k]));
				cout << setw(6) << " ";
				colorFondo(0);
				cout << VERTIC;
			}
			cout << endl;
		}
	}
	cout << CONTINUAR;
}

void carga(tTablero tablero, int &puntos) // Carga un tablero desde un archivo a elegir.
{
	ifstream archivo;
	string nombArch = ARCHIVOPRED;
	cout << ARCHIVOCARG;
	cin >> nombArch; // Archivo a cargar.
	archivo.open(nombArch);
	if (archivo.is_open()) // Si el archivo se ha abierto.
	{
		int DIM;
		archivo >> DIM;
		archivo.get();
		if (DIM == TAMANO) // Si el tamaño del tablero a cargar es compatible con la partida.
		{ // Se carga la partida.
			for (int i = 0; i < TAMANO; i++)
			{
				for (int j = 0; j < TAMANO; j++)
				{
					archivo >> tablero[i][j];
					archivo.get();
				}
			}
			archivo >> puntos;
		}
		else // Si no es compatible.
		{
			cout << ERRORCARG << endl;
			cin.sync();
			cin.get();
		}
	}

	else // Si no se ha podido abrir.
	{
		cout << ERRORCARG << endl;
		cin.sync();
		cin.get();
	}
}

tAccion leeAccion() // Coge una accion por teclado y la devuelve.
{
	cin.sync();
	tAccion accion = Nada;
	int dir = 0;
	while (accion == Nada)
	{
		dir = _getch();
		if (dir == 0xe0) // Si es una tecla especial.
		{
			dir = _getch();
		}
		switch (dir) // Cual tecla es?
		{
		case 27: // ESC.
		{
			accion = Salir;
		}
			break;
		case 72: // Flecha arriba.
		{
			accion = Arriba;
		}
			break;
		case 80: // Flecha abajo.
		{
			accion = Abajo;
		}
			break;
		case 77: // Flecha derecha.
		{
			accion = Derecha;
		}
			break;
		case 75: // Flecha izquierda.
		{
			accion = Izquierda;
		}
			break;
		default: // Ninguna de ellas.
		{
			accion = Nada;
		}
			break;
		}
	}
	return accion;
}

void mueveFichas(tTablero tablero, tAccion accion) // Mueve las fichas del tablero dependiendo de la accion.
{
	// Este procedimiento desplaza las fichas reordenando el array dependiendo de la direccion dada por accion.
	// Todos los casos tienen un proceso similar, variando donde empieza/acaba la reordenacion dependiendo de accion.
	int aux = 0;
	switch (accion)
	{
	case Arriba: // Desplazar el tablero hacia arriba.
	{
		for (int j = 0; j < TAMANO; j++)
		{
			int k = 0;
			for (int i = 0; i < TAMANO; i++)
			{
				if (tablero[i][j] != 1)
				{
					aux = tablero[i][j];
					tablero[i][j] = tablero[k][j];
					tablero[k][j] = aux;
					k++;
				}
			}
		}
	}
		break;
	case Abajo: // Desplazar el tablero hacia abajo.
	{
		for (int j = 0; j < TAMANO; j++)
		{
			int k = (TAMANO - 1);
			for (int i = (TAMANO - 1); i >= 0; i--)
			{
				if (tablero[i][j] != 1)
				{
					aux = tablero[i][j];
					tablero[i][j] = tablero[k][j];
					tablero[k][j] = aux;
					k--;
				}
			}
		}
	}
		break;
	case Izquierda: // Desplazar el tablero hacia la izquierda.
	{
		for (int i = 0; i < TAMANO; i++)
		{
			int k = 0;
			for (int j = 0; j < TAMANO; j++)
			{
				if (tablero[i][j] != 1)
				{
					aux = tablero[i][j];
					tablero[i][j] = tablero[i][k];
					tablero[i][k] = aux;
					k++;
				}
			}
		}
	}
		break;
	case Derecha: // Desplazar el tablero hacia la derecha.
	{
		for (int i = 0; i < TAMANO; i++)
		{
			int k = (TAMANO - 1);
			for (int j = (TAMANO - 1); j >= 0; j--)
			{
				if (tablero[i][j] != 1)
				{
					aux = tablero[i][j];
					tablero[i][j] = tablero[i][k];
					tablero[i][k] = aux;
					k--;
				}
			}
		}
	}
		break;
	}
}

int mayor(const tTablero tablero) // Devuelve el numero mas grande que haya en el tablero.
{
	int mayor = 1;
	for (int i = 0; i < TAMANO; i++) // Busca el mayor numero en el tablero.
	{
		for (int j = 0; j < TAMANO; j++)
		{
			if (tablero[i][j] > mayor)
			{
				mayor = tablero[i][j];
			}
		}
	}
	return mayor;
}

bool lleno(const tTablero tablero) // Devuelve true si el tablero esta lleno y no permite combinaciones.
{
	bool lleno = true;
	int i = 0;
	int j = 0;
	while ((i < TAMANO) && (lleno == true)) // Busca en el tablero alguna casilla vacia.
	{
		j = 0;
		while ((j < TAMANO) && (lleno == true))
		{
			if (tablero[i][j] == 1) // Si la casilla esta vacia.
			{
				lleno = false;
			}
			j++;
		}
		i++;
	}

	if (lleno == true) // Si el tablero esta lleno.
	{
		i = 0;
		while (i < TAMANO) // Busca en el tablero alguna ficha contigua horizontalmente que sea igual a la anterior.
		{
			j = 0;
			while ((j + 1) < TAMANO)
			{
				if (tablero[i][j] == tablero[i][(j + 1)]) // Si dos fichas contiguas son iguales. Significa que hay combinacion posible.
				{
					lleno = false;
				}
				j++;
			}
			i++;
		}
		j = 0;
		while (j < TAMANO) // Busca en el tablero alguna ficha contigua verticalmente que sea igual a la anterior. Significa que hay combinacion posible.
		{
			i = 0;
			while ((i + 1) < TAMANO)
			{
				if (tablero[i][j] == tablero[(i + 1)][j]) // Si dos fichas contiguas son iguales.
				{
					lleno = false;
				}
				i++;
			}
			j++;
		}
	}
	return lleno;
}

void combinaFichas(tTablero tablero, tAccion accion, int &puntos) // Combina las fichas del tablero dependiendo de la accion.
{
	switch (accion)
	{
	case Arriba: // El tablero combina las fichas hacia arriba.
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (j < TAMANO)
		{
			i = 0;
			while ((i + 1) < TAMANO) // Busca fichas contiguas verticalmente (sin contar las casillas vacias) que sean iguales.
			{
				if ((tablero[i][j] == tablero[(i + 1)][j]) && (tablero[i][j] != 1))
				{
					puntos = tablero[i][j] * 2; // Suma a los puntos el valor de la ficha por 2.
					tablero[i][j] = tablero[i][j] * 2; // Convierte el valor de la posicion del tablero correspondiente en el mismo por 2.
					k = i + 1;
					while (k < TAMANO) // Reordena el array para que no queden espacios vacios entre las fichas combinadas y las fichas contiguas.
					{
						if ((k + 1) < TAMANO)
						{
							tablero[k][j] = tablero[(k + 1)][j];
						}
						else // Si la casilla es la ultima, se vacia porque se ha eliminado ya una ficha con la combinacion (puede estar ya vacia anteriormente)
						{
							tablero[k][j] = 1;
						}
						k++;
					}
				}
				i++;
			}
			j++;
		}
	}
		break;
	case Abajo: // El tablero combina las fichas hacia abajo.
	{
		int i = TAMANO - 1;
		int j = TAMANO - 1;
		int k = TAMANO - 1;
		while (j >= 0)
		{
			i = TAMANO - 1;
			while ((i - 1) >= 0) // Busca fichas contiguas verticalmente (sin contar las casillas vacias) que sean iguales.
			{
				if ((tablero[i][j] == tablero[(i - 1)][j]) && (tablero[i][j] != 1))
				{
					puntos = tablero[i][j] * 2; // Suma a los puntos el valor de la ficha por 2.
					tablero[i][j] = tablero[i][j] * 2; // Convierte el valor de la posicion del tablero correspondiente en el mismo por 2.
					k = i - 1;
					while (k >= 0) // Reordena el array para que no queden espacios vacios entre las fichas combinadas y las fichas contiguas.
					{
						if ((k - 1) >= 0)
						{
							tablero[k][j] = tablero[(k - 1)][j];
						}
						else // Si la casilla es la ultima, se vacia porque se ha eliminado ya una ficha con la combinacion (puede estar ya vacia anteriormente)
						{
							tablero[k][j] = 1;
						}
						k--;
					}
				}
				i--;
			}
			j--;
		}
	}
		break;
	case Izquierda: // El tablero combina las fichas hacia la izquierda.
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < TAMANO)
		{
			j = 0;
			while ((j + 1) < TAMANO) // Busca fichas contiguas horizontalmente (sin contar las casillas vacias) que sean iguales.
			{
				if ((tablero[i][j] == tablero[i][(j + 1)]) && (tablero[i][j] != 1))
				{
					puntos = tablero[i][j] * 2; // Suma a los puntos el valor de la ficha por 2.
					tablero[i][j] = tablero[i][j] * 2; // Convierte el valor de la posicion del tablero correspondiente en el mismo por 2.
					k = j + 1;
					while (k < TAMANO) // Reordena el array para que no queden espacios vacios entre las fichas combinadas y las fichas contiguas.
					{
						if ((k + 1) < TAMANO)
						{
							tablero[i][k] = tablero[i][(k + 1)];
						}
						else // Si la casilla es la ultima, se vacia porque se ha eliminado ya una ficha con la combinacion (puede estar ya vacia anteriormente)
						{
							tablero[i][k] = 1;
						}
						k++;
					}
				}
				j++;
			}
			i++;
		}
	}
		break;
	case Derecha: // El tablero combina las fichas hacia la derecha.
	{
		int i = TAMANO - 1;
		int j = TAMANO - 1;
		int k = TAMANO - 1;
		while (i >= 0)
		{
			j = TAMANO - 1;
			while ((j - 1) >= 0) // Busca fichas contiguas horizontalmente (sin contar las casillas vacias) que sean iguales.
			{
				if ((tablero[i][j] == tablero[i][(j - 1)]) && (tablero[i][j] != 1))
				{
					puntos = tablero[i][j] * 2; // Suma a los puntos el valor de la ficha por 2.
					tablero[i][j] = tablero[i][j] * 2; // Convierte el valor de la posicion del tablero correspondiente en el mismo por 2.
					k = j - 1;
					while (k >= 0) // Reordena el array para que no queden espacios vacios entre las fichas combinadas y las fichas contiguas.
					{
						if ((k - 1) >= 0)
						{
							tablero[i][k] = tablero[i][(k - 1)];
						}
						else // Si la casilla es la ultima, se vacia porque se ha eliminado ya una ficha con la combinacion (puede estar ya vacia anteriormente)
						{
							tablero[i][k] = 1;
						}
						k--;
					}
				}
				j--;
			}
			i--;
		}
	}
	}
}

void nuevaFicha(tTablero tablero) // Añade una nueva ficha al tablero en una casilla vacia.
{
	int i = rand() % TAMANO;
	int j = rand() % TAMANO;
	while (tablero[i][j] != 1) // Busca una casilla vacia para rellenarla.
	{
		i = rand() % TAMANO;
		j = rand() % TAMANO;
	}
	int prob = rand() % 100;
	if (prob <= 94) // 95% de probabilidades de que sea un 2.
	{
		tablero[i][j] = 2;
	}
	else // 5% de probabilidades de que sea un 4.
	{
		tablero[i][j] = 4;
	}
}

void nuevoRecord(int puntos) // Actualiza el listado de records cuando hay un nuevo record.
{
	tRecords records;
	ifstream recordArch;
	recordArch.open(RECORDSPRED); // Abre el archivo de records.
	if (recordArch.is_open()) // Si esta abierto.
	{
		int i = 0;
		string nombre = " ";
		while ((nombre != CENTINELA) && (i < MAXRECORD)) // Mientras que el nombre no sea el centinela e i sea menor al maximo permitido.
		{ // Recoge todos los nombres y puntuaciones de la lista y los añade a la estructura records.
			recordArch >> nombre;
			records.nombre[i] = nombre;
			recordArch.get();
			if (nombre == CENTINELA)
			{
				records.puntuacion[i] = 0;
			}
			else
			{
				recordArch >> records.puntuacion[i];
			}
			recordArch.get();
			i++;
		}
		while (i < MAXRECORD)
		{
			records.nombre[i] = " ";
			records.puntuacion[i] = 0;
			i++;
		}
	}
	recordArch.close(); // Cierra el archivo.

	bool mayor = false;
	int i = 0;
	while ((i < MAXRECORD) && (mayor == false)) // Busca si hay algun record que sea menor al conseguido.
	{
		if (records.puntuacion[i] < puntos)
		{
			mayor = true;
		}
		i++;
	}
	if (mayor == true) // Si encuentra un record menor al conseguido.
	{	// Reordena la lista de manera que el record de menor puntuacion se elimine (si se ha alcanzado el numero maximo de records)
		int j = MAXRECORD - 1;
		while ((j > i))
		{
			records.nombre[j] = records.nombre[(j - 1)];
			records.puntuacion[j] = records.puntuacion[(j - 1)];
			j--;
		}
		cout << endl << NUEVORECORD;
		cin >> records.nombre[(i - 1)];
		records.puntuacion[(i - 1)] = puntos;
	}

	ofstream recordArch2;
	recordArch2.open(RECORDSPRED);
	if ((recordArch2.is_open()) && (mayor == true)) // Actualiza la lista de records.
	{
		i = 0;
		while ((i < MAXRECORD) && (records.nombre[i] != CENTINELA))
		{
			recordArch2 << records.nombre[i] << " " << records.puntuacion[i];
			recordArch2 << endl;
			i++;
		}
		recordArch2 << CENTINELA;
	}
	recordArch2.close();
}

void muestraRecords() // Muestra la lista de records por pantalla.
{
	cout << MUESTRARECORD << endl;
	ifstream archivo;
	archivo.open(RECORDSPRED);
	if (archivo.is_open())
	{
		char aux = '\n';
		while (aux != '?') // Lee hasta que la lista de records llegue al centinela.
		{
			cout << aux;
			archivo.get(aux);
		}
	}
	archivo.close();
}

void guarda(const tTablero tablero, int puntos) // Guarda una partida en un fichero.
{
	ofstream archivo;
	string nombArch = ARCHIVOPRED;
	cout << NOMBREGUARD;
	cin >> nombArch; // Nombre del fichero a guardar.
	archivo.open(nombArch);
	if (archivo.is_open())
	{
		archivo << TAMANO << endl; // Guarda el tamaño del tablero, para comprobar la compatibilidad en posteriores cargas.
		for (int i = 0; i < TAMANO; i++) // Guarda el contenido del tablero.
		{
			for (int j = 0; j < TAMANO; j++)
			{
				archivo << tablero[i][j] << endl;
			}
		}
		archivo << puntos; // Guarda los puntos obtenidos.
	}
	archivo.close();
}