// Jose Antonio Bernal Pérez. Laboratorio 1. Puesto 02. Dni: 48283545-J

/*------------------- Bibliotecas utilizadas. ------------------*/
#include <iostream> // Entrada y salida de datos por pantalla y teclado.
#include <fstream> // Entrada y salida de datos por fichero.
#include <string> // Manipulacion de cadenas tipo string.

/*------------------- Espacios de nombres. ------------------*/
using namespace std; // Utilizado para mayor comodidad con comandos de la biblioteca iostream.

/*------------------- Constantes utilizadas. ------------------*/

const int MAX_VIAJES = 10; // Numero MAXIMO de viajes del catalogo de viajes.

const int NUM_PREFERENCIAS = 3; // Numero MAXIMO de preferencias a elegir por el usuario.

const string CATALOGO = "catalogoViajes.txt"; // Nombre del fichero del que se cargara el catalogo de viajes.

const string CENTINELA = "XXX"; // Centinela que indica el final del catalogo de viajes.

const string PEDIRCATEGORIA = "Elija una categoria (0 para mochilero, 1 para turista, 2 para lujo): "; // Pide la categoria en la que reservar el viaje.

// mostrarViajesEnCategoria.
const string VIAJESCATEGORIA = "Viajes en la categoria: "; // Encabezado para mostrar los viajes disponibles en cierta categoria.

// leerPreferencias.
const string DESTINOSPREF = "Escribe tus destinos por orden de preferencia (de mayor a menor): "; // Pide al usuario sus destinos preferidos a los que viajar.

// hacerReserva.
const string RESERVA1 = "Su plaza para ir a "; // Frase 1 para indicar la reserva.
const string RESERVA2 = " ha sido reservada."; // Frase 2 para indicar la reserva.

// Errores en el programa.
const string ERRORCATALOGO = "No se pudo cargar el catalogo."; // Error mostrado cuando el fichero no se pudo cargar correctamente.
const string ERRORRESERVA = "No hay plazas que coincidan con sus preferencias."; // Error mostrado cuando no hay ningun destino coincidente con las preferencias.

// Fin del programa.
const string FINPROGRAMA = "Pulsa ENTER para salir..."; // Mostrado al finalizar el programa.

/*----------------- Tipos utilizados. -----------------*/
typedef enum {mochilero, turista, lujo} tCat; // Categorias de los viajes. mochilero(0), turista(1) y lujo(2).

/*----------------- Estructuras. -----------------*/
typedef struct {
	string destino; // Destino del viaje.
	int duracion; // Duracion del viaje.
	int plazas; // Plazas disponibles para viajar.
	tCat categoria; // Categoria disponible en el viaje.
} tViaje; // Utilizada para clasificar cada uno de los viajes disponibles en el catalogo.

/*----------------- Arrays. -------------------*/
typedef tViaje tArrayViaje[MAX_VIAJES]; // Contabiliza los viajes disponibles en el catalogo de viajes hasta un maximo de MAX_VIAJES.
typedef string tPreferencias[NUM_PREFERENCIAS]; // Guarda las preferencias a la hora de viajar del usuario hasta un maximo de NUM_PREFERENCIAS.

/* -----------------------------------Funciones utilizadas.----------------------------------------*/

bool cargarCatalogo(tArrayViaje arrayViaje); // Esta funcion carga el catalogo desde un fichero y lo guarda en arrayViaje.

void mostrarViajesEnCategoria(tCat categoria, tArrayViaje arrayViaje); // Muestra los viajes disponibles de categoria categoria en arrayViaje.

void guardarCatalogo(tArrayViaje arrayViaje); // Guarda en un fichero el catalogo contenido en arrayViaje.

void leerPreferencias(tPreferencias preferencias); // Lee las preferencias del usuario a la hora de viajar y las guarda en preferencias.

int buscarDestino(tArrayViaje arrayViaje, string destino, tCat categoria); // Busca un destino en arrayViaje que tenga como destino destino y como categoria categoria.

bool hacerReserva(tArrayViaje arrayViaje, tCat categoria, tPreferencias preferencias); // Realiza la reserva del viaje basandose en la categoria elegida y en las preferencias.

/* ------------------------------------------------------------------------------------------------*/


int main() // Funcion principal.
{
	tArrayViaje viaje;
	tPreferencias pref;
	bool cargado = cargarCatalogo(viaje);
	if (cargado == true)
	{
		cout << PEDIRCATEGORIA;
		int catDada = 0;
		cin.sync();
		cin >> catDada;
		tCat categoria = tCat(catDada);
		mostrarViajesEnCategoria(categoria, viaje);
		leerPreferencias(pref);
		bool reservado = hacerReserva(viaje, categoria, pref);
		if(reservado == true)
		{
			guardarCatalogo(viaje);
		}
	}
	else
	{
		cout << ERRORCATALOGO << endl;
	}
	cout << FINPROGRAMA << endl;
	cin.sync();
	cin.get();
	return 0;
}

bool cargarCatalogo(tArrayViaje arrayViaje) // Esta funcion carga el catalogo desde un fichero y lo guarda en arrayViaje.
{
	bool abierto = true;
	ifstream archivo;
	archivo.open(CATALOGO);
	if(archivo.is_open()) // Si el archivo se ha abierto correctamente.
	{
		int i = 0;
		int categoria = 0;
		char aux = ' ';
		arrayViaje[i].destino = " ";
		while((i < MAX_VIAJES) && (arrayViaje[i].destino != CENTINELA)) // Leera hasta que aparezca el centinela o hasta que alcance el maximo permitido.
		{
			archivo >> arrayViaje[i].destino;
			archivo.get(aux);
			if(arrayViaje[i].destino != CENTINELA) // Si el centinela ha aparecido, no se ejecutara esta parte del codigo.
			{
				archivo >> arrayViaje[i].duracion;
				archivo.get(aux);
				archivo >> arrayViaje[i].plazas;
				archivo.get(aux);
				archivo >> categoria;
				arrayViaje[i].categoria = tCat(categoria);
				i++;
			}
		}
	}
	else // Si el archivo no se ha abierto correctamente.
	{
		abierto = false;
	}
	return abierto;
}

void mostrarViajesEnCategoria(tCat categoria, tArrayViaje arrayViaje) // Muestra los viajes disponibles de categoria categoria en arrayViaje.
{
	int i = 0;
	cout << VIAJESCATEGORIA << endl << endl;
	while(arrayViaje[i].destino != CENTINELA)
	{
		if(categoria == arrayViaje[i].categoria) // Si la categoria seleccionada coincide con la categoria del viaje actual.
		{ // Se mostrara en pantalla.
			cout << arrayViaje[i].destino << ", ";
			cout << arrayViaje[i].duracion << " dias, ";
			cout << arrayViaje[i].plazas << " plaza(s) disponible(s)." << endl;
		}
		i++;
	}
}

void guardarCatalogo(tArrayViaje arrayViaje) // Guarda en un fichero el catalogo contenido en arrayViaje.
{
	ofstream archivo;
	archivo.open(CATALOGO);
	if(archivo.is_open()) // Si el archivo se ha abierto correctamente.
	{
		int i = 0;
		int categoria = 0;
		while((i < MAX_VIAJES) && (arrayViaje[i].destino != CENTINELA)) // Guardara en fichero hasta que llegue al maximo permitido o hasta que acabe el catalogo.
		{
			archivo << arrayViaje[i].destino;
			archivo << " ";
			archivo << arrayViaje[i].duracion;
			archivo << " ";
			archivo << arrayViaje[i].plazas;
			archivo << " ";
			categoria = int(arrayViaje[i].categoria);
			archivo << categoria;
			archivo << endl;
			i++;
		}
		archivo << CENTINELA; // Colocara el centinela al final para futuras lecturas.
	}
}

void leerPreferencias(tPreferencias preferencias) // Lee las preferencias del usuario a la hora de viajar y las guarda en preferencias.
{
	cout << DESTINOSPREF << endl << endl;
	int i = 0;
	while(i < NUM_PREFERENCIAS) // Pedira NUM_PREFERENCIAS al usuario.
	{
		cout << "Destino " << (i + 1) << ": ";
		cin >> preferencias[i];
		i++;
	}
}

int buscarDestino(tArrayViaje arrayViaje, string destino, tCat categoria) // Busca un destino en arrayViaje que tenga como destino destino y como categoria categoria.
{
	int i = 0;
	int posicion = -1;
	while(arrayViaje[i].destino != CENTINELA) // Mientras no se acabe el catalogo.
	{
		if((destino == arrayViaje[i].destino) && (categoria == arrayViaje[i].categoria)) // Si encuentra un destino que coincida con lo que busca el usuario.
		{
			posicion = i; // Guardara su posicion.
		}
		i++;
	}
	return posicion;
}

bool hacerReserva(tArrayViaje arrayViaje, tCat categoria, tPreferencias preferencias) // Realiza la reserva del viaje basandose en la categoria elegida y en las preferencias.
{
	bool reservado = false;
	int i = 0;
	int j = 0;
	while((i < NUM_PREFERENCIAS) && (reservado == false)) // Mientras no se supere el numero de preferencias permitido y no se haya reservado aun.
	{
		int destino = buscarDestino(arrayViaje, preferencias[i], categoria); // Se buscara un destino que coincida con los intereses del usuario.
		if(destino != -1) // Si se ha encontrado.
		{
			if(arrayViaje[destino].plazas > 0) // Si existen plazas para reservar.
			{ // Se reserva.
				cout << RESERVA1 << arrayViaje[destino].destino << RESERVA2 << endl;
				arrayViaje[destino].plazas--;
				reservado = true;
			}
		}
		i++;
	}

	if(reservado == false) // Si no se ha podido reservar.
	{
		cout << ERRORRESERVA << endl;
	}
	return reservado;
}