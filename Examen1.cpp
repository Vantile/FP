/*
Apellidos: Bernal Pérez
Nombre: Jose Antonio
DNI: 48283545-J
Puesto: Pto0404 (Lab 04)
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

const int diasSemana = 7;
const int diaBueno = 100; // Lo uso para determinar los dias "positivos" o "negativos" de la empresa.
typedef double tFacturacion[diasSemana];

double mediaArit(const tFacturacion arrayEuros)
{
	double total = 0;
	double media = 0;
	for (int i = 0; i < diasSemana; i++)
	{
		total = total + arrayEuros[i];
	}
	media = total / diasSemana;
	return media;
}

double desvEstandar(const tFacturacion arrayEuros, double media)
{
	double sumatorio = 0;
	double j = 0;
	double cuad = 0;
	for (int i = 0; i < diasSemana; i++)
	{
		j = arrayEuros[i] - media;
		cuad = j * j;
		sumatorio = sumatorio + cuad;
	}
	double k = sumatorio / diasSemana;
	double desviacion = sqrt(k);
	return desviacion;
}

void maxDesv(const tFacturacion arrayEuros, double media)
{
	double P = 0;
	cout << "Introduzca la maxima desviación esperada (numero real): ";
	cin >> P;
	for (int i = 0; i < diasSemana; i++)
	{
		string dato = "positiva";
		if(abs(arrayEuros[i] - media) > P) // Dias especialmente buenos o malos.
		{
			if(arrayEuros[i] < P) // Dias especialmente malos.
			{
				dato = "negativa";
			}
			cout << "Desviacion " << dato << " inesperada (" << arrayEuros[i] << ") en el dia " << (i + 1) << "." << endl;
		}
	}
}

int main()
{
	tFacturacion arrayEuros;
	for(int i = 0; i < diasSemana; i++)
	{
		cout << "Cual fue la facturacion del dia " << i + 1 << "? ";
		cin >> arrayEuros[i];
		while ((arrayEuros[i] < 0) || (arrayEuros[i] > 1000))
		{
			cin.sync();
			cout << "Cantidad erronea. Vuelve a introducirla.";
			cin >> arrayEuros[i];
		}
	}
	cout << "Calculando media de facturacion..." << endl;
	double media = mediaArit(arrayEuros);
	cout << "La media de facturacion es: " << media << endl;
	// Escritura de archivo.
	ofstream desvF;
	desvF.open("desviacion.txt");
	double desviacion = 0;
	for(int i = 0; i < diasSemana; i++)
	{
		desviacion = arrayEuros[i] - media;
		desvF << desviacion << endl;
	}
	double desvStd = desvEstandar(arrayEuros, media);
	desvF << "La desviacion estandar es: " << desvStd << endl;
	desvF.close(); // Cierre.
	// Lectura de archivo.
	ifstream muestra;
	cout << "Estas son las desviaciones diarias: " << endl;
	muestra.open("desviacion.txt");
	if(muestra.is_open())
	{
		char aux = 'a';
		while(!muestra.eof())
		{
			muestra.get(aux);
			cout << aux;
		}
	}
	muestra.close(); // Cierre.

	maxDesv(arrayEuros, media);
	cout << "Pulsa ENTER para salir." << endl;
	cin.sync();
	cin.get();
	return 0;
}