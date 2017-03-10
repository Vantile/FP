// Practica 2: Jose Antonio Bernal Pérez y Javier Muñoz Sanchez. 1º C.
// Universidad Complutense de Madrid. Fundamentos de Programación.


// Bibliotecas utilizadas en este programa.
#include <iostream> // Entrada y salida de datos por teclado y pantalla.
#include <fstream> // Entrada y salida de datos de fichero.
#include <string> // Manipulacion de variables tipo string.
#include <ctime> // Utilizada para la seed de la funcion rand().


// Espacios de nombres usados.
using namespace std; // Para una utilizacion mas comoda de comandos de iostream y fstream.


// Constantes utilizadas.
const int CARTASPORPALO = 13; // Cartas que hay por cada palo.
const int MAXCARTAS = 52; // Maximo de cartas en un mazo.
const int CENTINELA = 52; // Centinela en un array.


// Lectura de archivo.
const string ARCHIVOMAZO = "MazoCartas.txt"; // Archivo predeterminado para la lectura/escritura de mazos.
const string PEDIRARCHIVO = "Como se llama el archivo del mazo? (Incluye la extension .txt) : "; // Enunciado para pedir el nombre de un archivo.
const char CPICAS = 'p'; // Caracter de picas.
const char CTREBOLES = 't'; // Caracter de treboles.
const char CDIAMANTES = 'd'; // Caracter de diamantes.
const char CCORAZONES = 'c'; // Caracter de corazones.
const char CCENTINELA = 'x'; // Caracter centinela.


// Constantes para los nombres de las cartas.
const string PALOPICAS = "Picas"; // Palo de picas.
const string PALOTREBOLES = "Treboles"; // Palo de treboles.
const string PALODIAMANTES = "Diamantes"; // Palo de diamantes.
const string PALOCORAZONES = "Corazones"; // Palo de corazones.
const string NUMAS = "As"; // Numero AS, 1.
const string NUMDOS = "Dos"; // Numero 2.
const string NUMTRES = "Tres"; // Numero 3.
const string NUMCUATRO = "Cuatro"; // Numero 4.
const string NUMCINCO = "Cinco"; // Numero 5.
const string NUMSEIS = "Seis"; // Numero 6.
const string NUMSIETE = "Siete"; // Numero 7.
const string NUMOCHO = "Ocho"; // Numero 8.
const string NUMNUEVE = "Nueve"; // Numero 9.
const string NUMDIEZ = "Diez"; // Numero 10.
const string NUMJ = "J"; // Numero J, 11.
const string NUMQ = "Q"; // Numero Q, 12.
const string NUMK = "K"; // Numero K, 13.


// Opciones y constantes del menu.
const string OPCION1 = "1. Cargar un mazo de cartas desde un fichero."; // Opcion 1.
const string OPCION2 = "2. Barajar mazo de cartas."; // Opcion 2.
const string OPCION3 = "3. Añadir mazo."; // Opcion 3.
const string OPCION4 = "4. Cortar mazo."; // Opcion 4.
const string OPCION5 = "5. Guardar mazo de cartas en un fichero."; // Opcion 5.
const string OPCION6 = "6. Separar en negras y rojas."; // Opcion 6.
const string OPCION7 = "7. Separar en bajas y altas."; // Opcion 7.
const string OPCION8 = "8. Repartir el mazo en montones."; // Opcion 8.
const string OPCION9 = "9. Truco de los tres montones."; // Opcion 9.
const string OPCION10 = "10. Truco de la posada."; // Opcion 10.
const string OPCION11 = "11. Truco del jugador desconfiado."; // Opcion 11.
const string OPCION0 = "0. Salir."; // Opcion 0, salida.
const string INTRODUCEOPCION = "Introduce una opción: "; // Enunciado para pedir la opcion seleccionada.

// Constantes utilizadas en main().
const string CARGADO = "Mazo cargado.";
const string MOSTRARMAZO = "Este mazo tiene estas cartas: ";
const string MAZOUNIDO = "Mazo añadido correctamente.";
const string MAZONEGRO = "Mazo negro: ";
const string MAZOROJO = "Mazo rojo: ";
const string MAZOALTO = "Mazo de altas: ";
const string MAZOBAJO = "Mazo de bajas: ";
const string ENCUANTOSMONTONES = "En cuantos montones quieres dividir?: ";
const string CUALMONTONTEQUEDAS = "Con cual monton te quedas?: ";
const string MONTONELEGIDO = "Monton elegido: ";
const string ADIOS = "Hasta pronto!";
const string SALIR = "Pulsa ENTER para salir...";


// Errores varios.
const string ERROROPCION = "Opcion incorrecta. Introduce una opción: "; // Error al introducir una opcion invalida en el menu.
const string ERRORARCHIVO = "Archivo incorrecto."; // Error al introducir un archivo que cargar incorrecto o no existente.
const string ERRORMAZO = "Mazo no valido."; // Error al cargar un mazo en un truco sin que cumpla los requisitos.
const string ERRORGRANDE = "Error: Mazo demasiado grande.";


// Truco de los tres montones. Constantes utilizadas.
// Todas estas constantes guian al usuario para completar correctamente el truco a realizar.
const string TRUCOTRESMONTONES = "Bienvenido al truco de los Tres Montones!";
const string MEMORIZACARTA = "Memoriza una carta del mazo.";
const string ESTEMAZOTIENE = "Este mazo tiene estas cartas: ";
const string AHORAREPARTO = "Ahora reparto el mazo en 3 montones.";
const string PRIMERMONTON = "Primer monton.";
const string SEGUNDOMONTON = "Segundo monton.";
const string TERCERMONTON = "Tercer monton.";
const string ENCUALMONTON = "En cual monton esta tu carta?: ";
const string OTRAVEZMONTON = "Junto los 3 montones y los vuelvo a repartir en 3.";
const string ESESTA = "Es esta tu carta?: ";


// Final de los trucos. Guia al usuario para poder salir de un truco que ha finalizado.
const string FINTRUCO = "Pulsa ENTER para salir al menu.";
const string AVANZARTRUCO = "Pulsa ENTER para ir avanzando por el truco.";


// Truco de la posada. Constantes utilizadas.
// Todas estas constantes guian al usuario para completar correctamente el truco a realizar.
const string TRUCOPOSADA = "Bienvenido al truco de la posada!";
const string POSADA1 = "Tenemos cuatro J, cuatro Q, cuatro K y cuatro A.";
const string POSADA2 = "Los repartimos en 4 habitaciones, de manera que en cada habitacion";
const string POSADA3 = "haya una J, una Q, una K y un A.";
const string HABITACION1 = "Primera habitacion; ";
const string HABITACION2 = "Segunda habitacion: ";
const string HABITACION3 = "Tercera habitacion: ";
const string HABITACION4 = "Cuarta habitacion: ";
const string POSADA4 = "Uno los mazos de las cuatro habitaciones en uno solo.";
const string PORDONDECORTAR = "Indicame la posicion por la que cortar el mazo: ";
const string POSADA5 = "Cortamos el mazo y los repartimos en habitaciones otra vez.";
const string POSADA6 = "En una habitacion estan las J, en otra las Q, en otra las K y en otra las A.";
const string POSADA7 = "Pulsa ENTER para comprobarlo.";


// Truco del jugador desconfiado. Constantes utilizadas.
// Todas estas constantes guian al usuario para completar correctamente el truco a realizar.
const string TRUCODESCONF = "Bienvenido al truco del Jugador Desconfiado.";
const string DESCONF1 = "En una partida de poker, un jugador no se fia de los demas jugadores.";
const string DESCONF2 = "Por ello, propone que las cartas sean visibles antes de repartirse.";
const string DESCONF3 = "Al saber las cartas, el mazo se baraja.";
const string DESCONF4 = "Cada jugador queda con estas cartas: ";
const string JUGA1 = "Jugador 1: ";
const string JUGA2 = "Jugador 2: ";
const string JUGA3 = "Jugador 3: ";
const string JUGA4 = "Jugador 4: ";
const string CONTINUAR = "Pulsa ENTER para seguir con el truco.";
const string DESCONF5 = "Tampoco se fia del jugador que reparte, asi que propone unas reglas.";
const string DESCONF6 = "Cada jugador divide su mazo en izquierdo y derecho segun las reglas.";
const string DESCONF7 = "Despues, cada jugador da su mazo derecho al que tiene a la derecha.";
const string DESCONF8 = "Y el mazo izquierdo se lo da al que tiene a su izquierda.";
const string DESCONF9 = "Despues unen sus mazos y quedan asi: ";
const string DESCONF10 = "Se repite de nuevo el proceso anterior con las mismas reglas.";
const string DESCONF11 = "Los mazos de cada jugador quedan asi: ";
const string DESCONF12 = "Se repite de nuevo el proceso, pero esta vez con diferentes reglas.";
const string DESCONF13 = "Cada jugador se queda con su mazo derecho.";
const string DESCONF14 = "Pasan el mazo izquierdo al jugador de su izquierda.";
const string DESCONF15 = "Cuando por fin, el jugador 1 se fia, resulta que...";
const string JUGAF1 = "Jugador 1: Tiene ESCALERA DE COLOR.";
const string JUGAF2 = "Jugador 2: Tiene FULL.";
const string JUGAF3 = "Jugador 3: Tiene POKER.";
const string JUGAF4 = "Jugador 4: Tiene COLOR.";


// Tipos definidos.
typedef enum {PICAS, TREBOLES, DIAMANTES, CORAZONES} tPalo; // Tipo que define el palo de una carta.
typedef enum {A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K} tNumero; // Tipo que define el numero de una carta.
typedef int tCarta; // Tipo que define el codigo de la carta.
typedef tCarta tMazo[MAXCARTAS]; // Array del mazo de cartas.



/*-------------------------------------------------- Funciones utilizadas. -------------------------------------------------------*/


void crearMazoVacio(tMazo mazo); 
// Crea un mazo vacío.

tCarta codigoCarta(char palo, int numero); // Funcion que devuelve el numero tCarta que corresponde a la carta.
// Usado a la hora de leer el fichero y asignar su codigo en el array.

bool cargarMazo(tMazo mazo); 
// Funcion para cargar el mazo a utilizar en el programa.

int cuantasEnMazo(const tMazo mazo); 
// Funcion que devuelve cuantas cartas hay en el mazo.

tPalo darPalo(tCarta carta); 
// Devuelve el palo correspondiente a la carta elegida.

tNumero darNumero(tCarta carta); 
// Devuelve el numero correspondiente a la carta elegida.

void escribirCarta(tCarta carta); 
// Escribe la carta indicada para que sea legible para el usuario.
	
void escribirMazo(const tMazo mazo); 
// Escribe un mazo entero usando la funcion escribirCarta.

void barajarMazo(tMazo mazo); 
// Baraja el mazo de manera aleatoria.

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo); 
// Funcion que une mazoOriginal con nuevoMazo.

bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino); 
// Funcion para partir el mazo.

void cortarMazo(tMazo mazo, int cuantas); 
// Usa partirMazo para concatenar los mazos resultantes.

void guardarMazo(const tMazo mazo); 
// Funcion para guardar el archivo.

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo); 
// Divide el mazo en colores, negro y rojo.

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
// Divide el mazo en bajas y altas. Si es 7 o menor, sera baja. En caso contrario, alta.

void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);
// Divide el mazo en enCuantasMazos montones y se queda con el queMazoPido monton.

void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der);
// Divide el mazo en par e impar.

void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der);
// Divide el mazo en figura (A, J, Q, K) y en no figura (el resto).

int menu();
// Menu de inicio.

bool desconfBool(const tMazo mazo);
// Funcion para comprobar que el mazo es correcto en el tercer truco.

void trucoTresMontones();
// Funcion que realiza el truco de los Tres Montones.

bool posadaBool(const tMazo mazo);
// Funcion utilizada para determinar si mazo cumple los requisitos necesarios para que funcione en el truco de la posada.
	
void trucoPosada();
// Funcion que realiza el truco de la posada.

void trucoJugadorDesconfiado();
// Funcion que realiza el truco del jugador desconfiado.

/*------------------------------------------------------------------------------------------------------------------------------*/

int main()
{
	tMazo mazo;
	crearMazoVacio(mazo); // Se "inicializa" el mazo.
	srand(time(NULL)); // Semilla para la funcion rand().
	int opcion = menu(); // Se llama al menu().
	while (opcion != 0)
	{
		switch (opcion) // Dependiendo de la opcion del menu...
		{
			case 1: // Cargar mazo.
			{
				bool aux = cargarMazo(mazo);
				if (aux == true)
				{
					cout << CARGADO << endl;
					cout << MOSTRARMAZO << endl;
					escribirMazo(mazo);
				}
				else
					cout << ERRORARCHIVO << endl;
			}
				break;
			case 2: // Barajar mazo.
			{
				barajarMazo(mazo);
				int cuantas = cuantasEnMazo(mazo);
				escribirMazo(mazo);
			}
				break;
			case 3: // Añadir mazo.
			{
				tMazo mazo2;
				bool aux = cargarMazo(mazo2);
				if (aux == true)
					cout << CARGADO << endl;
				else
					cout << ERRORARCHIVO << endl;
				bool aux2 = unirMazos(mazo, mazo2);
				if (aux2 == true)
				{
					cout << MAZOUNIDO << endl;
					escribirMazo(mazo);
				}
				else
				{
					cout << ERRORGRANDE << endl;
				}
			}
				break;
			case 4: // Cortar mazo.
			{
				int num;
				cout << PORDONDECORTAR;
				cin >> num;
				cortarMazo(mazo, num);
				escribirMazo(mazo);
			}
				break;
			case 5: // Guardar mazo.
			{
				guardarMazo(mazo);
			}
				break;
			case 6: // Separar en negras y rojas.
			{
				tMazo mazoNegro, mazoRojo;
				repartirNegroRojo(mazo, mazoNegro, mazoRojo);
				cout << MAZONEGRO << endl << endl;
				escribirMazo(mazoNegro);
				cout << MAZOROJO << endl << endl;
				escribirMazo(mazoRojo);
			}
				break;
			case 7: // Separar en bajas y altas.
			{
				tMazo mazoBajas, mazoAltas;
				repartirBajaAlta(mazo, mazoBajas, mazoAltas);
				cout << MAZOBAJO << endl << endl;
				escribirMazo(mazoBajas);
				cout << MAZOALTO << endl << endl;
				escribirMazo(mazoAltas);
			}
				break;
			case 8: // Repartir mazo en montones.
			{
				tMazo monton;
				int montones = 0;
				int montonEleg = 0;
				cout << ENCUANTOSMONTONES;
				cin >> montones;
				cout << CUALMONTONTEQUEDAS;
				cin >> montonEleg;
				repartirIntercalando(mazo, montones, montonEleg, monton);
				cout << MONTONELEGIDO << endl << endl;
				escribirMazo(monton);
			}
			case 9: // Truco de los tres montones.
			{
				trucoTresMontones();
			}
				break;
			case 10: // Truco de la posada.
			{
				trucoPosada();
			}
				break;
			case 11: // Truco del jugador desconfiado.
			{
				trucoJugadorDesconfiado();
			}
				break;
		}
		opcion = menu(); // Vuelve a llamar al menu.
	}
	// Fin del programa.
	cout << ADIOS << endl;
	cout << SALIR;
	cin.sync();
	cin.get();
}

void crearMazoVacio(tMazo mazo) // Crea un mazo vacío.
{
	mazo[0] = CENTINELA;
}

tCarta codigoCarta(char palo, int numero) // Funcion que devuelve el numero tCarta que corresponde a la carta.
{ // Usado a la hora de leer el fichero y asignar su codigo en el array.
	tPalo paloCarta = PICAS;
	switch (palo)
	{
	case 'p':
	{
		paloCarta = PICAS;
	}
		break;
	case 't':
	{
		paloCarta = TREBOLES;
	}
		break;
	case 'd':
	{
		paloCarta = DIAMANTES;
	}
		break;
	case 'c':
	{
		paloCarta = CORAZONES;
	}
		break;
	}

	numero = (int(paloCarta) * CARTASPORPALO) + (numero - 1);
	tCarta codigo = tCarta(numero);
	return codigo;
}

bool cargarMazo(tMazo mazo) // Funcion para cargar el mazo a utilizar en el programa.
{
	bool abierto = false;
	string nombre = ARCHIVOMAZO; // Inicializacion, no tiene porque llamarse asi.
	int veces = 1;
	cout << PEDIRARCHIVO;
	cin >> nombre;
	ifstream archivo;
	archivo.open(nombre);
	while ((archivo.is_open() == false) && (veces < 3))
	{
		cout << ERRORARCHIVO << endl;
		veces++;
		cout << PEDIRARCHIVO;
		cin >> nombre;
		archivo.open(nombre);
	}

	if (archivo.is_open() == true)
	{
		abierto = true;
		char palo = 'a', aux;
		int numero, i = 0;
		// Este codigo extrae los datos del archivo y los pasa en forma de codigo de carta al array mazo.
		archivo >> palo;
		archivo.get(aux);
		archivo >> numero;
		archivo.get(aux);
		while ((i < MAXCARTAS) && (palo != CCENTINELA))
		{
			mazo[i] = codigoCarta(palo, numero);
			i++;
			archivo.get(palo);
			archivo.get(aux);
			archivo >> numero;
			archivo.get(aux);
		}
		if (i <= MAXCARTAS) // Asigna el centinela al acabar de leer el archivo.
		{
			mazo[i] = CENTINELA;
		}
	}
	archivo.close();
	return abierto;
}

int cuantasEnMazo(const tMazo mazo) // Funcion que devuelve cuantas cartas hay en el mazo.
{
	int i = 0;
	while ((mazo[i] != CENTINELA) && (i < MAXCARTAS))
	{
		i++;
	}
	return i;
}

tPalo darPalo(tCarta carta) // Devuelve el palo correspondiente a la carta elegida.
{
	int aux = (carta / CARTASPORPALO);
	tPalo palo = tPalo(aux);
	return palo;
}

tNumero darNumero(tCarta carta) // Devuelve el numero correspondiente a la carta elegida.
{
	int aux = (carta % CARTASPORPALO);
	tNumero numero = tNumero(aux);
	return numero;
}

void escribirCarta(tCarta carta) // Escribe la carta indicada para que sea legible para el usuario.
{
	tPalo palo = darPalo(carta);
	tNumero numero = darNumero(carta);
	string cadPalo = " ";
	string cadNumero = " ";
	// Este codigo "transforma" el palo y el numero en la carta correspondiente para mostrarlo en pantalla
	// y sea posible para el usuario entender la carta que es.
	switch (palo)
	{
	case PICAS:
	{
		cadPalo = PALOPICAS;
	}
		break;
	case TREBOLES:
	{
		cadPalo = PALOTREBOLES;
	}
		break;
	case DIAMANTES:
	{
		cadPalo = PALODIAMANTES;
	}
		break;
	case CORAZONES:
	{
		cadPalo = PALOCORAZONES;
	}
	}

	switch (numero)
	{
	case A:
	{
		cadNumero = NUMAS;
	}
		break;
	case DOS:
	{
		cadNumero = NUMDOS;
	}
		break;
	case TRES:
	{
		cadNumero = NUMTRES;
	}
		break;
	case CUATRO:
	{
		cadNumero = NUMCUATRO;
	}
		break;
	case CINCO:
	{
		cadNumero = NUMCINCO;
	}
		break;
	case SEIS:
	{
		cadNumero = NUMSEIS;
	}
		break;
	case SIETE:
	{
		cadNumero = NUMSIETE;
	}
		break;
	case OCHO:
	{
		cadNumero = NUMOCHO;
	}
		break;
	case NUEVE:
	{
		cadNumero = NUMNUEVE;
	}
		break;
	case DIEZ:
	{
		cadNumero = NUMDIEZ;
	}
		break;
	case J:
	{
		cadNumero = NUMJ;
	}
		break;
	case Q:
	{
		cadNumero = NUMQ;
	}
		break;
	case K:
	{
		cadNumero = NUMK;
	}
		break;
	}
	// Fin de la "transformacion".

	cout << cadNumero << " de " << cadPalo << "." << endl;
}

void escribirMazo(const tMazo mazo) // Escribe un mazo entero usando la funcion escribirCarta.
{
	int i = 0;
	tCarta carta = mazo[i];
	while ((i < MAXCARTAS) && (carta != CENTINELA))
	{
		escribirCarta(carta);
		i++;
		carta = mazo[i];
	}
}

void barajarMazo(tMazo mazo) // Baraja el mazo de manera aleatoria.
{
	int numCartas = cuantasEnMazo(mazo);
	int barajas = 0;
	int i = 0; // Variables usadas para el numero aleatorio.
	int j = 0;
	tCarta aux = 0; // Variable auxiliar para el "swap".
	while (barajas < (3 * numCartas)) // Bucle para barajar el mazo.
	{
		i = rand() % numCartas;
		j = rand() % numCartas;
		aux = mazo[i];
		mazo[i] = mazo[j];
		mazo[j] = aux;
		barajas++;
	}
}

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo) // Funcion que une mazoOriginal con nuevoMazo.
{ // Solo se modifica mazoOriginal.
	bool booleano = true;
	int cartas = cuantasEnMazo(mazoOriginal);
	int tope = cartas + cuantasEnMazo(nuevoMazo);
	if (tope < MAXCARTAS) // Si la union no excede el tope de cartas.
	{
		int i = 0;
		while ((cartas < MAXCARTAS) && (nuevoMazo[i] != CENTINELA)) // Bucle de copia.
		{
			mazoOriginal[cartas] = nuevoMazo[i];
			cartas++;
			i++;
		}
		mazoOriginal[cartas] = CENTINELA; // Coloca el centinela al terminar de copiar.
	}
	else // En otro caso.
	{
		booleano = false;
	}
	return booleano;
}

bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino) // Funcion para partir el mazo.
{ // mazoDestino se quedaria con las primeras cuantasCoger cartas de mazoOrigen.
	// mazoOrigen quedaria con las restantes.
	int cartas = cuantasEnMazo(mazoOrigen);
	bool booleano = true;
	if (cuantasCoger <= cartas) // Si las cartas a coger no superan a las cartas que tiene mazoOrigen.
	{
		int aux = 0;
		for (int i = 0; i < cuantasCoger; i++)
		{ // Copia de las primeras cuantasCoger a mazoDestino.
			mazoDestino[i] = mazoOrigen[i];
			aux = i;
		}
		aux++;
		mazoDestino[aux] = CENTINELA;
		int cartasRestantes = cartas - aux;
		for (int i = 0; i < cartasRestantes; i++)
		{ // Colocacion de las restantes en mazoOrigen.
			mazoOrigen[i] = mazoOrigen[aux];
			aux++;
		}
		mazoOrigen[cartasRestantes] = CENTINELA;
	}
	else // En caso contrario, mazoDestino sera un mazo vacio.
	{
		mazoDestino[0] = CENTINELA;
		booleano = false;
	}
	return booleano;
}

void cortarMazo(tMazo mazo, int cuantas) // Usa partirMazo para concatenar los mazos resultantes.
{
	int cuantasMazoEntero = cuantasEnMazo(mazo);
	if (cuantasMazoEntero < MAXCARTAS)
	{
		tMazo mazoAux;
		partirMazo(mazo, cuantas, mazoAux);
		int i = 0;
		int restantes = cuantasMazoEntero - cuantas;
		while (restantes < cuantasMazoEntero) // Bucle de concatenacion.
		{
			mazo[restantes] = mazoAux[i];
			restantes++;
			i++;
		}
		mazo[restantes] = CENTINELA; // Escribe el centinela al terminar la copia.
	}
}

void guardarMazo(const tMazo mazo) // Funcion para guardar el archivo.
{
	string nombre = ARCHIVOMAZO; // Declaracion, no tiene porque llamarse asi.
	cout << PEDIRARCHIVO;
	cin >> nombre;
	ofstream archivo;
	archivo.open(nombre); // Abre o crea el archivo.
	int cartas = cuantasEnMazo(mazo);
	tPalo j;
	tNumero k;
	int l = 0;
	for (int i = 0; i < cartas; i++)
	{
		j = darPalo(mazo[i]);
		switch (j) // Dependiendo del palo escribira una letra u otra.
		{
		case PICAS:
			archivo << CPICAS;
			break;
		case TREBOLES:
			archivo << CTREBOLES;
			break;
		case DIAMANTES:
			archivo << CDIAMANTES;
			break;
		case CORAZONES:
			archivo << CCORAZONES;
			break;
		default: // Si no es ninguno de esos palos, escribira el centinela.
			archivo << CCENTINELA;
			break;
		} // Fin del switch.
		archivo << " ";
		k = darNumero(mazo[i]);
		l = (int(k) + 1);
		archivo << l;
		archivo << endl;
	}
	archivo << CCENTINELA;
	archivo.close(); // Cierra el archivo.
}

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo)
{ // Divide el mazo en colores, negro y rojo.
	int numCartas = cuantasEnMazo(mazo);
	// Variables auxiliares.
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < numCartas)
	{
		tPalo palo = darPalo(mazo[i]);
		if ((palo == PICAS) || (palo == TREBOLES)) // Si el color es negro.
		{
			mazoNegro[j] = mazo[i];
			j++;
		}

		if ((palo == DIAMANTES) || (palo == CORAZONES)) // Si el color es rojo.
		{
			mazoRojo[k] = mazo[i];
			k++;
		}
		i++;
	}
	// Escribe el centinela cuando se acaba la division.
	mazoNegro[j] = CENTINELA;
	mazoRojo[k] = CENTINELA;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas)
{ // Divide el mazo en bajas y altas. Si es 7 o menor, sera baja. En caso contrario, alta.
	int numCartas = cuantasEnMazo(mazo);
	// Variables auxiliares.
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < numCartas)
	{
		tNumero numero = darNumero(mazo[i]);
		if ((int(numero) < 7)) // Si la carta es baja.
		{
			mazoBajas[j] = mazo[i];
			j++;
		}
		else // Si la carta es alta.
		{
			mazoAltas[k] = mazo[i];
			k++;
		}
		i++;
	}
	// Escribe el centinela al acabar la division.
	mazoBajas[j] = CENTINELA;
	mazoAltas[k] = CENTINELA;
}

void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo)
{ // Divide el mazo en enCuantasMazos montones y se queda con el queMazoPido monton.
	int inicio = queMazoPido - 1;
	int numCartas = cuantasEnMazo(mazo);
	int i = 0;
	while (inicio < numCartas)
	{
		mazoNuevo[i] = mazo[inicio];
		inicio = inicio + enCuantosMazos; // Dependiendo del monton elegido, copiara solo una u otra parte del mazo principal.
		i++;
	}
	mazoNuevo[i] = CENTINELA;
}

void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der)
{
	int numero = cuantasEnMazo(mazo);
	int i = 0; // Contador mazo.
	int j = 0; // Contador izq.
	int k = 0; // Contador der.
	tNumero numeroCarta;
	int parImpar;
	while (i < numero)
	{
		numeroCarta = darNumero(mazo[i]);
		parImpar = (tCarta(numeroCarta) + 1);
		if ((parImpar % 2 == 0)) // Si la carta es par.
		{
			izq[j] = mazo[i];
			j++;
		}
		else // Si la carta es impar.
		{
			der[k] = mazo[i];
			k++;
		}
		i++;
	}
	// Escritura del centinela.
	izq[j] = CENTINELA;
	der[k] = CENTINELA;
}

void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der)
{
	int numero = cuantasEnMazo(mazo);
	int i = 0; // Contador mazo.
	int j = 0; // Contador izq.
	int k = 0; // Contador der.
	tNumero numeroCarta;
	int figura;
	while (i < numero)
	{
		numeroCarta = darNumero(mazo[i]);
		figura = tCarta(numeroCarta);
		if ((figura == 0) || (figura > 9)) // Si la carta es un As, J, Q o K.
		{
			izq[j] = mazo[i];
			j++;
		}

		else // Si es cualquiera de las otras.
		{
			der[k] = mazo[i];
			k++;
		}
		i++;
	}
	izq[j] = CENTINELA;
	der[k] = CENTINELA;
}

int menu() // Menu de inicio.
{
	int opcion = 0;
	cout << OPCION1 << endl;
	cout << OPCION2 << endl;
	cout << OPCION3 << endl;
	cout << OPCION4 << endl;
	cout << OPCION5 << endl;
	cout << OPCION6 << endl;
	cout << OPCION7 << endl;
	cout << OPCION8 << endl;
	cout << OPCION9 << endl;
	cout << OPCION10 << endl;
	cout << OPCION11 << endl;
	cout << OPCION0 << endl;
	cout << INTRODUCEOPCION;
	cin >> opcion;
	while ((opcion < 0) || (opcion > 11))
	{
		cout << ERROROPCION;
		cin >> opcion;
	}
	return opcion;
}

bool desconfBool(const tMazo mazo) // Funcion para comprobar que el mazo es correcto en el tercer truco.
{
	bool aux = true;
	int cuantas = cuantasEnMazo(mazo);
	if (cuantas == 20) // Si tiene 20 cartas.
	{
		/* Este codigo comprueba si el mazo cumple con los requisitos
		carta por carta. */
		if (mazo[0] != 0)
			aux = false;
		if (mazo[1] != 11)
			aux = false;
		if (mazo[2] != 12)
			aux = false;
		if (mazo[3] != 14)
			aux = false;
		if (mazo[4] != 16)
			aux = false;
		if (mazo[5] != 17)
			aux = false;
		if (mazo[6] != 18)
			aux = false;
		if (mazo[7] != 21)
			aux = false;
		if (mazo[8] != 24)
			aux = false;
		if (mazo[9] != 25)
			aux = false;
		if (mazo[10] != 27)
			aux = false;
		if (mazo[11] != 28)
			aux = false;
		if (mazo[12] != 29)
			aux = false;
		if (mazo[13] != 30)
			aux = false;
		if (mazo[14] != 31)
			aux = false;
		if (mazo[15] != 35)
			aux = false;
		if (mazo[16] != 38)
			aux = false;
		if (mazo[17] != 48)
			aux = false;
		if (mazo[18] != 50)
			aux = false;
		if (mazo[19] != 51)
			aux = false;
	}

	else
	{
		aux = false;
	}
	return aux;
}

void trucoTresMontones()
{
	/*
	El truco consiste en:
	Barajar un mazo con 21 cartas.
	Dividirlo en 3 montones y hacer que el usuario recuerde una carta.
	Cuando el usuario te dice en que monton esta, concatenar los tres
	montones de manera que el monton elegido quede en medio.
	Repetir el proceso otras 2 veces.
	La carta del usuario esta en la posicion 11 (10 del array) del mazo.
	*/
	cout << TRUCOTRESMONTONES << endl;
	tMazo mazo21;
	crearMazoVacio(mazo21); // "Inicializar" el mazo.
	bool aux = cargarMazo(mazo21);
	int cuantas = cuantasEnMazo(mazo21);
	if ((aux == true) && (cuantas == 21)) // Si el mazo tiene 21 cartas.
	{
		cout << AVANZARTRUCO << endl;
		// Pedir al usuario que recuerde una carta.
		cout << MEMORIZACARTA << endl;
		cout << ESTEMAZOTIENE << endl;
		escribirMazo(mazo21);
		cout << endl << endl;
		barajarMazo(mazo21);
		cin.sync();
		cin.get();
		int mazoAElegir = 1; // Inicializacion.
		cout << AHORAREPARTO << endl;
		tMazo monton1, monton2, monton3;
		// Repartir el mazo en 3 montones.
		repartirIntercalando(mazo21, 3, 1, monton1);
		repartirIntercalando(mazo21, 3, 2, monton2);
		repartirIntercalando(mazo21, 3, 3, monton3);
		// Enseñarselo al usuario.
		cout << PRIMERMONTON << endl;
		escribirMazo(monton1);
		cin.sync();
		cin.get();
		cout << endl << SEGUNDOMONTON << endl;
		escribirMazo(monton2);
		cin.sync();
		cin.get();
		cout << endl << TERCERMONTON << endl;
		escribirMazo(monton3);
		// Pedirle el monton en el que esta su carta.
		cout << endl << ENCUALMONTON;
		cin.sync();
		cin >> mazoAElegir;
		switch (mazoAElegir) // Dependiendo del monton, se unira el mazo de una manera u otra.
		{
		case 1:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton2);
			z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton3);
		}
			break;
		case 2:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton2);
			z = unirMazos(mazo21, monton3);
		}
			break;
		case 3:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton3);
			z = unirMazos(mazo21, monton2);
		}
			break;
		}
		cout << OTRAVEZMONTON << endl;
		// Repetir el proceso una segunda vez.
		repartirIntercalando(mazo21, 3, 1, monton1);
		repartirIntercalando(mazo21, 3, 2, monton2);
		repartirIntercalando(mazo21, 3, 3, monton3);
		cout << endl << PRIMERMONTON << endl;
		escribirMazo(monton1);
		cin.sync();
		cin.get();
		cout << endl << SEGUNDOMONTON << endl;
		escribirMazo(monton2);
		cin.sync();
		cin.get();
		cout << endl << TERCERMONTON << endl;
		escribirMazo(monton3);
		cout << endl << ENCUALMONTON;
		cin.sync();
		cin >> mazoAElegir;
		switch (mazoAElegir)
		{
		case 1:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton2);
			z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton3);
		}
			break;
		case 2:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton2);
			z = unirMazos(mazo21, monton3);
		}
			break;
		case 3:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton3);
			z = unirMazos(mazo21, monton2);
		}
			break;
		}
		cout << OTRAVEZMONTON << endl;
		// Repetir el proceso una ultima vez.
		repartirIntercalando(mazo21, 3, 1, monton1);
		repartirIntercalando(mazo21, 3, 2, monton2);
		repartirIntercalando(mazo21, 3, 3, monton3);
		cout << endl << PRIMERMONTON << endl;
		escribirMazo(monton1);
		cin.sync();
		cin.get();
		cout << endl << SEGUNDOMONTON << endl;
		escribirMazo(monton2);
		cin.sync();
		cin.get();
		cout << endl << TERCERMONTON << endl;
		escribirMazo(monton3);
		cout << endl << ENCUALMONTON;
		cin.sync();
		cin >> mazoAElegir;
		switch (mazoAElegir)
		{
		case 1:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton2);
			z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton3);
		}
			break;
		case 2:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton2);
			z = unirMazos(mazo21, monton3);
		}
			break;
		case 3:
		{
			crearMazoVacio(mazo21);
			bool z = unirMazos(mazo21, monton1);
			z = unirMazos(mazo21, monton3);
			z = unirMazos(mazo21, monton2);
		}
			break;
		}
		// Magia.
		cout << ESESTA;
		escribirCarta(mazo21[10]);
		cout << endl << endl;
	}
	else // Si el mazo no tiene 21 cartas.
	{
		cout << ERRORMAZO << endl;
	}
	cout << FINTRUCO << endl;
	cin.sync();
	cin.get();
}

bool posadaBool(const tMazo mazo)
{	// Funcion utilizada para determinar si mazo cumple los requisitos necesarios para que funcione en el truco de la posada.
	bool aux = true;
	int cuantas = cuantasEnMazo(mazo);
	int hab = 4;
	tNumero numero0, numero1, numero2, numero3;
	if (cuantas == 16)
	{
		int i = 0;
		while ((aux == true) && (i < hab)) // Comprueba si 4 cartas seguidas del mazo tienen el mismo numero.
		{
			int j = 0; // Al comienzo de cada bucle, debe ser 0.
			numero0 = darNumero(mazo[(i * hab) + j]);
			j++;
			numero1 = darNumero(mazo[(i * hab) + j]);
			j++;
			numero2 = darNumero(mazo[(i * hab) + j]);
			j++;
			numero3 = darNumero(mazo[(i * hab) + j]);
			if ((numero0 != numero1) || (numero1 != numero2) || (numero2 != numero3))
			{
				aux = false;
			}
			i++;
		}
		// Comprueba que los numeros de las cartas (J, Q, K, A) esten en el orden correcto.
		numero0 = darNumero(mazo[0]);
		numero1 = darNumero(mazo[hab]);
		numero2 = darNumero(mazo[hab * 2]);
		numero3 = darNumero(mazo[hab * 3]);
		if ((numero0 != J) || (numero1 != Q) || (numero2 != K) || (numero3 != A))
		{
			aux = false;
		}
	}
	else
	{
		aux = false;
	}
	return aux;
}

void trucoPosada()
{
	/*
	El truco consiste en:
	El mazo tiene 4 J, 4 Q, 4 K y 4 A juntas y en ese orden.
	Se reparte el mazo en 4 montones.
	En cada uno de los montones hay 1 J, 1 Q, 1 K y 1 A.
	Se unen los 4 mazos, concatenandolos.
	Se pide al usuario por cual posicion dividir el mazo.
	Se reparte el mazo resultante en 4 montones.
	En cada monton hay un unico tipo de carta (Q, J, K o A).
	*/
	cout << AVANZARTRUCO << endl;
	cout << TRUCOPOSADA << endl;
	tMazo mazoPosada;
	crearMazoVacio(mazoPosada); // "Inicializando" el mazo.
	bool aux = cargarMazo(mazoPosada);
	bool posada = posadaBool(mazoPosada);
	int cuantas = cuantasEnMazo(mazoPosada);
	if ((aux == true) && (posada == true)) // Si la baraja es valida.
	{
		cout << POSADA1 << endl;
		cout << POSADA2 << endl;
		cout << POSADA3 << endl << endl;
		cin.sync();
		cin.get();
		tMazo hab0, hab1, hab2, hab3;
		// Repartir en 4 montones.
		repartirIntercalando(mazoPosada, 4, 1, hab0);
		repartirIntercalando(mazoPosada, 4, 2, hab1);
		repartirIntercalando(mazoPosada, 4, 3, hab2);
		repartirIntercalando(mazoPosada, 4, 4, hab3);
		// Se muestra al usuario que se cumple lo dicho.
		cout << HABITACION1 << endl << endl;
		escribirMazo(hab0);
		cin.sync();
		cin.get();
		cout << endl << HABITACION2 << endl << endl;
		escribirMazo(hab1);
		cin.sync();
		cin.get();
		cout << endl << HABITACION3 << endl << endl;
		escribirMazo(hab2);
		cin.sync();
		cin.get();
		cout << endl << HABITACION4 << endl << endl;
		escribirMazo(hab3);
		cin.sync();
		cin.get();
		cout << endl << endl;
		cout << POSADA4 << endl;
		// Se une el mazo de nuevo.
		crearMazoVacio(mazoPosada);
		unirMazos(mazoPosada, hab0);
		unirMazos(mazoPosada, hab1);
		unirMazos(mazoPosada, hab2);
		unirMazos(mazoPosada, hab3);
		// Se pide al usuario por cual posicion cortar el mazo.
		cout << PORDONDECORTAR;
		int posicion = 0;
		cin.sync();
		cin >> posicion;
		// Se corta el mazo.
		cout << POSADA5 << endl;
		cortarMazo(mazoPosada, posicion);
		// Se reparte de nuevo.
		repartirIntercalando(mazoPosada, 4, 1, hab0);
		repartirIntercalando(mazoPosada, 4, 2, hab1);
		repartirIntercalando(mazoPosada, 4, 3, hab2);
		repartirIntercalando(mazoPosada, 4, 4, hab3);
		// Magia.
		cout << POSADA6 << endl;
		cout << POSADA7 << endl << endl;
		cin.sync();
		cin.get();
		cout << HABITACION1 << endl << endl;
		escribirMazo(hab0);
		cin.sync();
		cin.get();
		cout << endl << HABITACION2 << endl << endl;
		escribirMazo(hab1);
		cin.sync();
		cin.get();
		cout << endl << HABITACION3 << endl << endl;
		escribirMazo(hab2);
		cin.sync();
		cin.get();
		cout << endl << HABITACION4 << endl << endl;
		escribirMazo(hab3);
		cout << endl << endl;
	}
	else // Si el mazo no cumple los requisitos.
	{
		cout << ERRORMAZO << endl;
	}
	cout << FINTRUCO << endl;
	cin.sync();
	cin.get();
}

void trucoJugadorDesconfiado()
{
	/*
	El truco consiste en:
	- Hay 4 jugadores en una partida de poker.
	- Uno de ellos no se fia, asique propone una manera alternativa de barajar.
	- Los jugadores dividen sus cartas en 2 mazos, izquierdo y derecho.
	- El jugador 1 pone en el izquierdo sus cartas negras, en el derecho, sus rojas.
	- El jugador 2 pone en el izquierdo sus cartas bajas, en el derecho, las altas.
	- El jugador 3 pone en el izquierdo sus cartas pares, en el derecho, sus impares.
	- El jugador 4 pone en el izquierdo sus cartas que son figura, en el derecho, las que no lo son.
	- A continuacion, cada jugador pasa su monton izquierdo al jugador a su izquierda, y el derecho al de la derecha.
	- Despues, los jugadores unen los mazos.
	- Se realiza la division y la union otra vez.
	- Se realiza la division de nuevo, pero esta vez cada jugador se queda su mazo derecho, y da el izquierdo al de su izquierda.
	- Al acabar, muestran las cartas.
	- El jugador 1 tiene escalera de color.
	- El jugador 2 tiene full.
	- El jugador 3 tiene poker.
	- El jugador 4 tiene color.
	*/
	cout << AVANZARTRUCO << endl;
	cout << TRUCODESCONF << endl;
	tMazo mazoDes;
	crearMazoVacio(mazoDes);
	bool abierto = cargarMazo(mazoDes);
	bool desconf = desconfBool(mazoDes);
	if ((abierto == true) && (desconf == true)) // Si la baraja es valida.
	{
		// Se explica el truco.
		cout << DESCONF1 << endl;
		cout << DESCONF2 << endl;
		// Se baraja el mazo y se muestra.
		barajarMazo(mazoDes);
		escribirMazo(mazoDes);
		cin.sync();
		cin.get();
		cout << DESCONF3 << endl;
		tMazo jug1, jug2, jug3, jug4;
		// Se reparte entre los jugadores.
		repartirIntercalando(mazoDes, 4, 1, jug1);
		repartirIntercalando(mazoDes, 4, 2, jug2);
		repartirIntercalando(mazoDes, 4, 3, jug3);
		repartirIntercalando(mazoDes, 4, 4, jug4);
		cout << DESCONF4 << endl;
		// Se muestran las cartas de cada jugador.
		cout << endl << JUGA1 << endl << endl;
		escribirMazo(jug1);
		cin.sync();
		cin.get();
		cout << endl << JUGA2 << endl << endl;
		escribirMazo(jug2);
		cin.sync();
		cin.get();
		cout << endl << JUGA3 << endl << endl;
		escribirMazo(jug3);
		cin.sync();
		cin.get();
		cout << endl << JUGA4 << endl << endl;
		escribirMazo(jug4);
		cout << endl;
		cout << CONTINUAR;
		cin.sync();
		cin.get();
		cout << DESCONF5 << endl;
		cout << DESCONF6 << endl;
		cout << DESCONF7 << endl;
		cout << DESCONF8 << endl;
		cout << DESCONF9 << endl;
		cin.sync();
		cin.get();
		// Se crean los izq y der para cada jugador y se reparten siguiendo las reglas.
		tMazo izq1, der1, izq2, der2, izq3, der3, izq4, der4;
		repartirNegroRojo(jug1, izq1, der1);
		repartirBajaAlta(jug2, izq2, der2);
		repartirParImpar(jug3, izq3, der3);
		repartirFiguraNoFigura(jug4, izq4, der4);
		tMazo jug11, jug12, jug13, jug14;
		// "Inicializando" mazos.
		crearMazoVacio(jug11);
		crearMazoVacio(jug12);
		crearMazoVacio(jug13);
		crearMazoVacio(jug14);
		// Jugador 1.
		unirMazos(jug11, izq2);
		unirMazos(jug11, der4);
		// Jugador 2.
		unirMazos(jug12, izq3);
		unirMazos(jug12, der1);
		// Jugador 3.
		unirMazos(jug13, izq4);
		unirMazos(jug13, der2);
		// Jugador 4.
		unirMazos(jug14, izq1);
		unirMazos(jug14, der3);
		// Se muestran los mazos resultantes de cada jugador.
		cout << endl << JUGA1 << endl << endl;
		escribirMazo(jug11);
		cin.sync();
		cin.get();
		cout << endl << JUGA2 << endl << endl;
		escribirMazo(jug12);
		cin.sync();
		cin.get();
		cout << endl << JUGA3 << endl << endl;
		escribirMazo(jug13);
		cin.sync();
		cin.get();
		cout << endl << JUGA4 << endl << endl;
		escribirMazo(jug14);
		cout << endl;
		cout << CONTINUAR;
		cin.sync();
		cin.get();
		cout << DESCONF10 << endl;
		// Se repite el proceso de nuevo.
		// Se reparten los mazos siguiendo las reglas.
		tMazo der11, izq11, der12, izq12, der13, izq13, der14, izq14;
		repartirNegroRojo(jug11, izq11, der11);
		repartirBajaAlta(jug12, izq12, der12);
		repartirParImpar(jug13, izq13, der13);
		repartirFiguraNoFigura(jug14, izq14, der14);
		tMazo jug21, jug22, jug23, jug24;
		// "Inicializando" mazos.
		crearMazoVacio(jug21);
		crearMazoVacio(jug22);
		crearMazoVacio(jug23);
		crearMazoVacio(jug24);
		// Jugador 1.
		unirMazos(jug21, izq12);
		unirMazos(jug21, der14);
		// Jugador 2.
		unirMazos(jug22, izq13);
		unirMazos(jug22, der11);
		// Jugador 3.
		unirMazos(jug23, izq14);
		unirMazos(jug23, der12);
		// Jugador 4.
		unirMazos(jug24, izq11);
		unirMazos(jug24, der13);
		// Se muestran los mazos resultantes de cada jugador.
		cout << DESCONF11 << endl << endl;
		cout << JUGA1 << endl << endl;
		escribirMazo(jug21);
		cin.sync();
		cin.get();
		cout << endl << JUGA2 << endl << endl;
		escribirMazo(jug22);
		cin.sync();
		cin.get();
		cout << endl << JUGA3 << endl << endl;
		escribirMazo(jug23);
		cin.sync();
		cin.get();
		cout << endl << JUGA4 << endl << endl;
		escribirMazo(jug24);
		cout << endl;
		cout << CONTINUAR;
		cin.sync();
		cin.get();
		cout << DESCONF12 << endl;
		cout << DESCONF13 << endl;
		cout << DESCONF14 << endl;
		cin.sync();
		cin.get();
		// Se reparten los mazos siguiendo las reglas.
		tMazo izq21, der21, izq22, der22, izq23, der23, izq24, der24;
		repartirNegroRojo(jug21, izq21, der21);
		repartirBajaAlta(jug22, izq22, der22);
		repartirParImpar(jug23, izq23, der23);
		repartirFiguraNoFigura(jug24, izq24, der24);
		// Se juntan los mazos de nuevo, pero con diferentes reglas.
		tMazo jug31, jug32, jug33, jug34;
		// "Inicializando" mazos.
		crearMazoVacio(jug31);
		crearMazoVacio(jug32);
		crearMazoVacio(jug33);
		crearMazoVacio(jug34);
		// Jugador 1.
		unirMazos(jug31, der21);
		unirMazos(jug31, izq22);
		// Jugador 2.
		unirMazos(jug32, der22);
		unirMazos(jug32, izq23);
		// Jugador 3.
		unirMazos(jug33, der23);
		unirMazos(jug33, izq24);
		// Jugador 4.
		unirMazos(jug34, der24);
		unirMazos(jug34, izq21);
		cout << DESCONF15 << endl << endl;
		// Se muestran los mazos de cada jugador.
		cout << JUGAF1 << endl << endl;
		escribirMazo(jug31);
		cin.sync();
		cin.get();
		cout << endl << JUGAF2 << endl << endl;
		escribirMazo(jug32);
		cin.sync();
		cin.get();
		cout << endl << JUGAF3 << endl << endl;
		escribirMazo(jug33);
		cin.sync();
		cin.get();
		cout << endl << JUGAF4 << endl << endl;
		escribirMazo(jug34);
		cout << endl;
	}

	else
	{
		cout << ERRORMAZO << endl;
	}
	cout << FINTRUCO << endl;
	cin.sync();
	cin.get();
}