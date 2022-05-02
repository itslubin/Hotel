
#include <iostream>
#include <string>
#include <fstream>
using namespace std;



const int DIAS = 30;

typedef double tDias[DIAS];

void cargar(tDias dias);
void mostrar(tDias dias);
void reservar(tDias dias);
bool comprobar(tDias dias, int inicio, int final);
void guardar(tDias dias);
void datos(int dia_comienzo, int dia_fin, int precio_total);

int main() {

	tDias dias;
	char respuesta = 'A';
while (respuesta == 'A') {
	cargar(dias);
	mostrar(dias);
	reservar(dias);
	guardar (dias);

cout << "Introduzca 'A' si desea realizar mas reservas o 'B' en caso contrario : " << endl;
cin >> respuesta;
}
	return 0;
}

/*Se cargan los datos de los precios de la habitacion desde archivo "datos.txt" al array*/

void cargar(tDias dias) {

	ifstream archivo;
	archivo.open("datos.txt");
	double numero;
	if (archivo.is_open()) {
		for (int i = 0; i < 30; i++) {
			archivo >> numero;
			dias[i] = numero;   
	   }
	}
	else {
		cout << " No se pudo abrir el archivo" << endl;
	}
}

/*Muestra por pantalla la informacion de los precios de la habitacion 
mostrando "RESERVADO" en caso de que el precio de la habitacion sea 0*/

void mostrar(tDias dias) {
    cout << "La informacion de la habitacion es : " << endl;
	for (int i = 0; i < 30; i++) {
	    cout << "Dia " << i + 1 << " : ";
	    if (dias[i] == 0) {
		    cout << "RESERVADO" << endl;
	    }
	    else {
	        cout << dias[i] << endl;
	    }
	}
	cout << endl;
}

/*Pide al usuario los dias de reserva de la habitacion y hace la reserva,
contiene las funciones "comprobar" para verificar que la habitacion esta disponible y "datos" que crea el archivo .txt*/

void reservar(tDias dias) {
    bool disponible = false;
    int dia_comienzo, dia_fin, precio_total = 0;
    while (!disponible) {
        cout << "Introduzca el dia de comienzo de la reserva de la habitacion : " << endl;
        cin >> dia_comienzo;
        cout << "Introduzca el dia de finalizacion de la reserva de la habitacion : " << endl;
        cin >> dia_fin;
        // aprovechamos el booleano disponible (para el for) que equivale a que no hemos encontrado el día reservado y entonces hay que seguir buscando, pero a la que lo encontramos se para el for gracias a la condicion
        disponible = comprobar(dias, dia_comienzo, dia_fin);
    }
    for (int i = dia_comienzo - 1; i <= dia_fin - 1; i++) {
        precio_total = precio_total + dias[i];
    }
    for (int i = dia_comienzo - 1; i <= dia_fin - 1; i++) {
        dias[i] = 0;
    }
    datos(dia_comienzo, dia_fin, precio_total);
}

/*Recibe el dia de inicio y fin de la reserva y comprueba si se puede reservar la habitacion*/

bool comprobar(tDias dias, int inicio, int final) {
    bool disponible = true;   
    int i = inicio - 1;
    while (i <= final - 1 && disponible) {
        if (dias[i] == 0) {
            cout << "El dia " << i + 1 << " esta reservado." << endl;
            disponible = false;
        }
        else {
            i++;
        }
    }
    return disponible;
}

/*Me actualiza los datos del archivo datos.txt con los datos actualizados del array*/

void guardar(tDias dias) {
    ofstream archivo;
    archivo.open("datos.txt");
    if (archivo.is_open()) {
		for (int i = 0; i < 30; i++) {
		    archivo << dias[i] << endl;
		}
    }
}

/*Me crea un archivo .txt nuevo que contiene los datos de la reserva realizada por el usuario*/

void datos(int dia_comienzo, int dia_fin, int precio_total) {
    string nombre;
    cout << "Introduzca un nombre para la reserva : ";
    cin >> nombre;
    ofstream archivo;
    archivo.open(nombre+".txt");
    if (archivo.is_open()) {
    archivo << "El dia de comienzo de la reserva es : " << dia_comienzo << endl;
    archivo << "El dia de finalizacion de la reserva es : " << dia_fin << endl;
    archivo << "El precio total de la reserva es : " << precio_total;
    }
}

