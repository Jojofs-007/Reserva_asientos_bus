/*
Programa hecho por Jonathán Josué Florián Sipaque
Realizado para Programación III 2022
*/

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <ctime>

using namespace std;

stack<string> cliente; // Esta es la pila, creada con la librería <stack> (reduce codigo y facilita el uso de la misma)

void menu_principal();	   // Muestra las opciones disponibles
void op_menu(int &);	   // Función encargada de dirigir al usuario al apartado escogido
void salir();			   // Se utiliza para salir de los ciclos y finalizar el programa
void configurar_autobus(); // Funcion que cambia los parametros
void ingresar_pasajeros(); // Se agregan elementos a la pila
void realizar_viaje();	   // Se eliminan los elementos de la pila
void si_no(int &);		   // Esta función es para realizar una pregunta "si/no"
void regresar();		   // Sirve para retornar al menu principal
void atraso();			   // Otorga un tiempo de atraso

int capacidad_bus = 5; // Puede aumentarse la capacidad del bus desde el programa
string destino1 = "Cuilapa";
string destino2 = "Barberena"; // Parametros del autobus

int main()
{
	system("Color 60");
	menu_principal();
	return 0;
}

void menu_principal()
{
	int menu;
	system("title Autobus: menu");
	system("cls");
	cout << "\tMenu principal" << endl;
	cout << "1. Configurar autobus.\n2. Ingresar pasajeros.\n3. Realizar viaje.\n0. Salir del programa." << endl;
	do
	{
		cerr << "Digite la opcion a seguir: ";
		cin >> menu;
		if ((menu < 0) || (menu > 3))
		{
			cerr << "\aEl numero digitado es invalido, intente de nuevo... ";
			getch();
		}
	} while ((menu < 0) || (menu > 3));
	op_menu(menu);
}

void op_menu(int &op)
{
	if ((op >= 1) && (op <= 3))
	{
		system("cls");
	}
	switch (op)
	{
	case 0:
		salir();
		break;
	case 1:
		configurar_autobus();
		break;

	case 2:
		ingresar_pasajeros();
		break;
	case 3:
		realizar_viaje();
		break;
	}
	regresar();
}

void salir()
{
	cout << "Gracias por usar este programa.\nIngrese cualquier tecla para salir... ";
	getch();
	exit(1);
}

void configurar_autobus()
{
	system("title Autobus: configuracion");
	int preg = 1;
	cout << "\tConfigurar autobus\n\n";
	cout << "Bienvenido al sistema del autobus, aqui puede cambiar los parametros." << endl;
	cout << "\nCapacidad maxima del autobus: " << capacidad_bus << endl;
	cout << "La ruta del viaje es de " << destino1 << " hasta " << destino2 << "." << endl;
	si_no(preg);
}

void ingresar_pasajeros()
{
	system("title Autobus: ingreso de pasajeros");
	int preg = 2;
	char pasajero[20];
	char p;
	cout << "\tIngreso de pasajeros\n\n";
	if (cliente.size() == capacidad_bus)
	{
		cerr << "\aTodos los asientos del autobus estan ocupados, intente en el siguiente viaje." << endl;
	}
	else
	{
		do
		{
			cin.ignore();
			cout << "Ingrese el nombre del pasajero: ";
			cin.getline(pasajero, 20, '\n');
			cliente.push(pasajero);
			cout << cliente.top() << " ha ingresado al autobus y se dirigio a su asiento." << endl;
			if (cliente.size() == capacidad_bus)
			{
				cerr << "\a\nLo sentimos, ya no hay asientos disponibles." << endl;
				regresar();
			}
			else
			{
				si_no(preg);
			}
		} while (cliente.size() <= 20);
	}
}

void realizar_viaje()
{
	system("title Autobus: Realizar viaje");
	int preg = 3;
	cout << "\tRealizar viaje\n\n";
	if (cliente.size() <= 0)
	{
		cout << "El autobus se encuentra vacio, ingrese pasajeros para realizar el viaje." << endl;
	}
	else
	{
		cout << "Pasajeros ingresados: " << cliente.size() << "/" << capacidad_bus << "." << endl;
		cout << "Ruta: " << destino1 << " hasta " << destino2 << "." << endl;
		si_no(preg);
		while (cliente.size() > 0)
		{
			cout << cliente.top() << " ya salio del autobus." << endl;
			cliente.pop();
			atraso();
		}
		cout << "\nAhora regresamos a nuestra estacion de autobuses." << endl;
	}
}

void si_no(int &n)
{
	char x;
	do
	{
		cout << "\nDesea ";
		switch (n)
		{
		case 1:
			cout << "cambiar los parametros?";
			break;
		case 2:
			cout << "ingresar un pasajero mas? Recuerda, quedan " << capacidad_bus - cliente.size() << " asientos en el autobus.";
			break;
		case 3:
			cout << "realizar el viaje?";
			break;
		}
		cout << " (s/n): ";
		cin >> x;
		if ((x == 's') || (x == 'S'))
		{
			switch (n)
			{
			case 1:
				cout << "A continuacion hara cambios a las variables." << endl;
				cout << "Ingrese la capacidad del autobus: ";
				cin >> capacidad_bus;
				cout << "Ingrese el lugar donde comienza el viaje: ";
				cin >> destino1;
				cout << "Ingrese el lugar donde termina el viaje: ";
				cin >> destino2;
				cout << "Los parametros han sido actualizados." << endl;
				break;
			case 2:
				break;
			case 3:
				cout << "\nEl viaje ha comenzado!\n\n";
				int r = 10;
				while (r > 0)
				{
					cout << "En " << r << " segundos llegamos a nuestro destino..." << endl;
					atraso();
					r--;
				}
				cout << "\nYa llegamos a " << destino2 << ".\n\n";
				break;
			}
		}
		else if ((x == 'n') || (x == 'N'))
		{
			regresar();
		}
		else
		{
			cerr << "\aEl caracter digitado es invalido, intente de nuevo." << endl;
		}
	} while ((((x != 's') && (x != 'S')) && (x != 'n')) && (x != 'N'));
}

void regresar()
{
	cout << "\nIngrese cualquier tecla para volver al menu principal... ";
	getch();
	menu_principal();
}

void atraso()
{
	for (int i = (time(NULL) + 1); time(NULL) != i; time(NULL))
		;
}