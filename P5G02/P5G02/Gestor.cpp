#include "Gestor.h"

#include <iostream> // Entrada/salida de datos por consola.
#include <fstream> // Entrada/salida de datos por fichero.
#include <iomanip> // Permite manipular la salida de datos por consola.

using namespace std;

const string BIENVENIDO = "Bienvenido al correo de "; // Mensaje de bienvenida del dominio.
const string INTNOM = "Introduzca su nombre de usuario: "; // Pide introducir un nombre de usuario.
const string INTCON = "Introduzca su contrasenia: "; // Pide introducir una contraseña.
const string ERRORUSU = "Ese usuario ya existe."; // Mensaje de error al crear una cuenta con un usuario que ya existe.
const string ERRORUSU2 = "Ese usuario no existe."; // Mensaje de error al iniciar sesion con un usuario que no existe.
const string ERRORUSU3 = "La lista de usuarios esta llena."; // Mensaje de error al crear una cuenta con la lista de usuarios llena.
const string ERRORCON = "La contrasenia no es valida."; // Mensaje de error cuando la contraseña no es valida.
const string BIENVBANDEJA = "Correo de "; // Indica en que correo has iniciado sesion.
const string BANDENTRADA = "-----------------------------Bandeja de entrada-----------------------------"; // Encabezado de bandeja de entrada.
const string BANDSALIDA = "-----------------------------Bandeja de salida------------------------------"; // Encabezado de bandeja de salida.
const string LINEA = "----------------------------------------------------------------------------"; // Linea separadora.
const string NUM = " N"; // Encabezado del numero del correo.
const string EMISOR = "EMISOR"; // Encabezado del emisor.
const string ASUNTO = "ASUNTO"; // Encabezado del asunto.
const string FECHA = "FECHA"; // Encabezado de la fecha.
const string ELEG = "Elija una opcion: "; // Da a elegir diferentes opciones.
const string MEN = "Introduzca una opcion: "; // Pide una opcion en el menu de la bandeja.
const string MEN1OP1 = "1 - Leer correo."; // Opcion 1 del menu de bandeja.
const string MEN1OP2 = "2 - Enviar correo."; // Opcion 2 del menu de bandeja.
const string MEN1OP3 = "3 - Borrar correo."; // Opcion 3 del menu de bandeja.
const string MEN1OP4ENT = "4 - Ver bandeja de salida."; // Opcion 4 del menu de bandeja de entrada.
const string MEN1OP4SAL = "4 - Ver bandeja de entrada."; // Opcion 4 del menu de bandeja de salida.
const string MEN1OP5 = "5 - Lectura rapida de correos sin leer."; // Opcion 5 del menu de bandeja.
const string MEN1OP0 = "0 - Cerrar sesion."; // Opcion 0 del menu de bandeja.
const string ERRORMEN = "Opcion incorrecta. Introduce una opcion: "; // Error de opcion incorrecta del menu.
const string POSLEER = "Elige la posicion del correo a leer: "; // Pide la posicion de un correo a leer.
const string ERRLEER = "No se puede leer el correo."; // Se muestra cuando no se puede leer un correo.
const string MEN2OP1 = " 1. Contestar correo."; // Opcion 1 del menu de correo.
const string MEN2OP0 = " 0. Volver a la bandeja."; // Opcion 0 del menu de correo.
const string ENVIADO = "Correo enviado."; // Mensaje de aviso de envio correcto.
const string VOLVIENDO = "Volviendo a bandeja..."; // Mensaje de vuelta a bandeja.
const string BORRCORREO = "Cual correo deseas borrar?: "; // Pide la posicion del correo a borrar.
const string LECTENTER = "Pulsa ENTER para leer el siguiente correo..."; // Pide ENTER para pasar a leer el siguiente correo en lectura rapida.
const string ERRLECT = "No hay correos sin leer."; // Se muestra cuando no hay correos sin leer para lectura rapida.
const string ERRBANDDEST = "La bandeja de entrada del destinatario esta llena."; // Error cuando la bandeja de entrada del destinatario esta llena.
const string ERRBANDEMI = "Tu bandeja de salida esta llena."; // Error cuando la bandeja de salida del emisor esta llena.
const string ERRLISTCORR = "La lista de correos esta llena, no se pueden mandar mas correos."; // Error cuando la lista de correos esta llena.
const string ENVENTER = "Pulsa ENTER para volver a bandeja..."; // Pide ENTER para volver a bandeja.

void inicializar(tGestor &gestor, string dominio) 
{
	// Inicializa el gestor.
	gestor.dominio = dominio;
	inicializar(gestor.correos);
	inicializar(gestor.usuarios);
	gestor.usuarioActivo = -1;
}

bool arrancar(tGestor &gestor, string dominio) 
{
	// Arranca (carga las listas) el gestor.
	bool ok = false;
	inicializar(gestor, dominio);
	bool ok1 = cargar(gestor.usuarios, dominio);
	bool ok2 = cargar(gestor.correos, dominio);
	if(ok1 && ok2) // Si se han cargado correctamente.
		ok = true;
	return ok;
}

void apagar(tGestor &gestor) 
{
	// Apaga el gestor (guarda todas las listas).
	guardar(gestor.usuarios, gestor.dominio);
	guardar(gestor.correos, gestor.dominio);
	destruir(gestor);
}

void destruir(tGestor &gestor)
{
	// Destruye de la memoria dinámica un dato tipo tGestor.
	destruir(gestor.usuarios);
	destruir(gestor.correos);
}

bool crearCuenta(tGestor &gestor) 
{
	// Crea una cuenta nueva en el dominio.
	bool ok = false;
	cout << endl << BIENVENIDO << gestor.dominio << endl;
	if((gestor.usuarios.contador) < MAX_USUARIOS)
	{
		cout << endl << INTNOM;
		cin.sync();
		string id;
		cin >> id;
		cout << INTCON;
		string contrasenia;
		cin.sync();
		cin >> contrasenia;
		string usuario = id + "@" + gestor.dominio;
		int posicion = -1;
		buscarUsuario(gestor.usuarios, usuario, posicion);
		if(posicion != -1)
		{
			cout << ERRORUSU << endl;
		}
		else
		{
			tUsuario usuarioNuevo;
			inicializar(usuarioNuevo, usuario, contrasenia);
			bool ok1 = insertar(gestor.usuarios, usuarioNuevo);
			if(ok1 == true)
			{
				int activo;
				buscarUsuario(gestor.usuarios, usuario, activo);
				if(activo != -1)
				{
					gestor.usuarioActivo = activo;
				}
				ok = true;
			}
		}
	}
	else
	{
		cout << ERRORUSU3 << endl;
	}
	return ok;
}

bool iniciarSesion(tGestor &gestor) 
{
	// Inicia sesion con una cuenta del dominio.
	cout << endl << BIENVENIDO << gestor.dominio;
	cout << endl << INTNOM;
	string id, contrasenia;
	cin.sync();
	cin >> id;
	string usuario = id + "@" + gestor.dominio;
	int posicion = -1;
	buscarUsuario(gestor.usuarios, usuario, posicion);
	bool ok = false;
	if(posicion == -1)
	{
		cout << ERRORUSU2 << endl;
	}
	else
	{
		cout << INTCON;
		cin.sync();
		cin >> contrasenia;
		bool valido = validarContrasenia(*gestor.usuarios.usuarios[posicion], contrasenia);
		if(valido == true)
		{
			gestor.usuarioActivo = posicion;
			ok = true;
		}
		else
		{
			gestor.usuarioActivo = -1;
			cout << ERRORCON << endl;
		}
	}
	return ok;
}

int menuBandeja(tGestor &gestor, bool entrada) 
{
	// Pinta en pantalla el menu de la bandeja (entrada/salida).
	system("cls");
	cout << BIENVBANDEJA << gestor.usuarios.usuarios[gestor.usuarioActivo]->id << endl;
	if(entrada == true)
		cout << BANDENTRADA << endl;
	else
		cout << BANDSALIDA << endl;
	cout << LINEA << endl;
	cout << setw(3) << NUM;
	cout << setw(3) << " ";
	cout << setw(21) << EMISOR;
	cout << setw(40) << ASUNTO;
	cout << setw(10) << FECHA;
	cout << endl << endl;
	cout << LINEA << endl;
	mostrarCorreosBandeja(gestor, entrada);
	cout << LINEA << endl;
	cout << ELEG << endl;
	cout << MEN1OP1 << endl;
	cout << MEN1OP2 << endl;
	cout << MEN1OP3 << endl;
	if(entrada == true)
		cout << MEN1OP4ENT << endl;
	else
		cout << MEN1OP4SAL << endl;
	cout << MEN1OP5 << endl;
	cout << MEN1OP0 << endl;
	cout << LINEA << endl;
	cout << MEN;
	int opcion = 0;
	cin.sync();
	cin >> opcion;
	while((opcion < 0) || (opcion > 5))
	{
		cout << ERRORMEN;
		cin.sync();
		cin >> opcion;
	}
	return opcion;
}

void mostrarCorreosBandeja(tGestor &gestor, bool entrada)
{
	// Muestra los correos de la bandeja.
	int i = 0;
	bool ok = true;
	if(entrada == true)
	{
		i = gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos.contador - 1;
		while((i >= 0) && (ok == true))
		{
			cout << setw(3) << (gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos.contador - i);
			if(!(gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos.registros[i].leido))
				cout << setw(3) << "*";
			else
				cout << setw(3) << "-";
			int posicion;
			ok = buscar(gestor.correos, gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos.registros[i].ident, posicion);
			cout << obtenerCabecera(gestor.correos.listaCorreo[posicion]);
			i--;
		}
	}
	else
	{
		i = gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados.contador - 1;
		while((i >= 0) && (ok == true))
		{
			cout << setw(3) << (gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados.contador - i);
			if(!(gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados.registros[i].leido))
				cout << setw(3) << "*";
			else
				cout << setw(3) << "-";
			int posicion;
			ok = buscar(gestor.correos, gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados.registros[i].ident, posicion);
			cout << obtenerCabecera(gestor.correos.listaCorreo[posicion]);
			i--;
		}
	}
}

void ejecutarMenuBandeja(tGestor &gestor, int opcion, bool &entrada) 
{
	// Ejecuta la opcion seleccionada del menu de la bandeja.
	if(entrada == true) // Bandeja de entrada.
	{
		switch (opcion)
		{
		case 1: // Leer correo.
			{
				leerCorreo(gestor, gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos);
			}
			break;
		case 2: // Enviar correo.
			{
				tCorreo correo;
				correoNuevo(correo, gestor.usuarios.usuarios[gestor.usuarioActivo]->id);
				enviarCorreo(gestor, correo);
			}
			break;
		case 3: // Borrar correo.
			{
				borrarCorreo(gestor, gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos);
			}
			break;
		case 4: // Cambio de bandeja.
			{
				entrada = false;
			}
			break;
		case 5: // Lectura rapida.
			{
				lecturaRapida(gestor, gestor.usuarios.usuarios[gestor.usuarioActivo]->recibidos);
			}
			break;
		}
	}
	else // Bandeja de salida.
	{
		switch (opcion)
		{
		case 1: // Leer correo.
			{
				leerCorreo(gestor, gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados);
			}
			break;
		case 2: // Enviar correo.
			{
				tCorreo correo;
				correoNuevo(correo, gestor.usuarios.usuarios[gestor.usuarioActivo]->id);
				enviarCorreo(gestor, correo);
			}
			break;
		case 3: // Borrar correo.
			{
				borrarCorreo(gestor, gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados);
			}
			break;
		case 4: // Cambio de bandeja.
			{
				entrada = true;
			}
			break;
		case 5: // Lectura rapida.
			{
				lecturaRapida(gestor, gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados);
			}
			break;
		}
	}
}

void leerCorreo(tGestor &gestor, tListaRegistros &listaReg) 
{
	// Lee un correo.
	cout << POSLEER;
	int posicion = 0;
	cin >> posicion;
	posicion = listaReg.contador - posicion;
	int pos;
	bool ok = buscar(gestor.correos, listaReg.registros[posicion].ident, pos);
	if(ok == true)
	{
		system("cls");
		aCadena(gestor.correos.listaCorreo[pos]);
		ok = correoLeido(listaReg, listaReg.registros[posicion].ident);
	}
	else
		cout << ERRLEER << endl;
	menuLeerCorreo(gestor, gestor.correos.listaCorreo[pos]);
}

void menuLeerCorreo(tGestor &gestor, const tCorreo &correoOriginal) 
{
	// Pinta y ejecuta la opcion del menu de lectura del correo.
	cout << endl << LINEA << endl;
	cout << ELEG << endl;
	cout << MEN2OP1 << endl;
	cout << MEN2OP0 << endl;
	cout << LINEA << endl;
	cout << MEN;
	int opcion = 0;
	cin.sync();
	cin >> opcion;
	while((opcion != 0) && (opcion != 1))
	{
		cout << ERRORMEN;
		cin.sync();
		cin >> opcion;
	}
	switch(opcion)
	{
	case 1: // Contestar correo.
		{
			tCorreo correoNuevo;
			correoContestacion(correoOriginal, correoNuevo, gestor.usuarios.usuarios[gestor.usuarioActivo]->id);
			enviarCorreo(gestor, correoNuevo);
			cout << ENVIADO << endl;
		}
		break;
	case 0: // Volver a bandeja.
		{
			cout << VOLVIENDO << endl;
		}
		break;
	}
}

void enviarCorreo (tGestor &gestor, const tCorreo &correo) 
{
	// Envia un correo a otro usuario del sistema.
	if((gestor.correos.numCorreos) < MAX_CORREOS)
	{
		if((gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados.contador) < MAX_REGISTROS)
		{
			tRegistro registroActivo;
			registroActivo.ident = correo.ident;
			registroActivo.leido = 1;
			insertar(gestor.usuarios.usuarios[gestor.usuarioActivo]->enviados, registroActivo);
			tRegistro registroRec;
			registroRec.ident = correo.ident;
			registroRec.leido = 0;
			int posicion = -1;
			buscarUsuario(gestor.usuarios, correo.destinatario, posicion);
			if(posicion != -1)
			{
				if((gestor.usuarios.usuarios[posicion]->recibidos.contador) < MAX_REGISTROS)
				{
					insertar(gestor.correos, correo);
					insertar(gestor.usuarios.usuarios[posicion]->recibidos, registroRec);
					cout << ENVIADO << endl;
				}
				else
					cout << ERRBANDDEST << endl;
			}
			else
				cout << ERRORUSU2 << endl;
		}
		else
			cout << ERRBANDEMI << endl;
	}
	else
		cout << ERRLISTCORR << endl;
	cout << ENVENTER << endl;
	cin.sync();
	cin.get();
}

void borrarCorreo(tGestor &gestor, tListaRegistros &listaReg) 
{
	// Borra un correo del sistema.
	int posicion = -1;
	cout << BORRCORREO;
	cin.sync();
	cin >> posicion;
	posicion = listaReg.contador - posicion;
	string id = listaReg.registros[posicion].ident;
	borrar(listaReg, id);
}

void lecturaRapida(tGestor &gestor, tListaRegistros &listaReg) 
{
	// Lee rapidamente todos los correos no leidos del usuario.
	tListaCorreos lectura;
	inicializar(lectura);
	for(int i = 0; i < listaReg.contador; i++)
	{
		if(listaReg.registros[i].leido != 1)
		{
			correoLeido(listaReg, listaReg.registros[i].ident);
			int pos = -1;
			buscar(gestor.correos, listaReg.registros[i].ident, pos);
			if(pos != -1)
				insertar(lectura, gestor.correos.listaCorreo[pos]);
		}
	}
	ordenar_AF(lectura);
	if(lectura.numCorreos != 0)
	{
		for(int i = 0; i < lectura.numCorreos; i++)
		{
			system("cls");
			aCadena(lectura.listaCorreo[i]);
			cout << endl << LECTENTER;
			cin.sync();
			cin.get();
		}
	}
	else
		cout << ERRLECT << endl;
	delete [] lectura.listaCorreo;
}

