/*Proyecto de Arboles Binarios y archivos.
* Estudiantes:
*	Katherine Amador.
*	Jose Serrano.
*	Samantha Acuña.
*Fecha de inicio: 19 de octubre del 2021.
*Fecha de entrega: 15 de noviembre del 2021.
*/

//Imports
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>

using namespace std;



struct Nodo {
	Nodo* sig;
	Nodo* nHijo;
	Nodo* nPadre;
	int cant; //cantidad
	string valor; //caracteristicas
	string nivel; //tipo de caracteristica
	//constructor
	struct Lista* sublista;
	Nodo(int c, string n, string v) {
		cant = c;
		valor = v;
		nivel = n;
		sig = NULL;
		nHijo = NULL;
		nPadre = NULL;
		sublista = NULL;
	}

} *raiz;

struct Lista {
	int posicion;
	Lista* sig;
	struct Nodo* nexoNodo;
	//constructor
	Lista(int pos) {
		posicion = pos;
		sig = NULL;
		nexoNodo = NULL;
	}
};

struct Persona {
	char nombre[30];
	int edad;
	char genero[7];
	char estadoCivil[15];
	char oficio[30];
	int sueldo;
	int anosTrabajo;
	int cantHijos;
	char hobby[30];
	char tipoAlimentacion[20];
	char tipoComida[20];
	char tipoMusica[15];
	char provincia[15];
	char canton[15];
	char distrito[15];
	int numMascotas;
};


/*
	Metodos de archivos.
*/


void escribir(Persona x) // El metodo escribir, requiere de un parametro persona y guarda en un archivo txt, los datos ingresados de la persona.
{
	fstream archivo("lista.txt", ios::in | ios::out | ios::binary);
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo";
		exit(1);
	}
	archivo.seekp(0, ios::end);
	archivo.write(reinterpret_cast<char*>(&x), sizeof(x));
	archivo.close(); //se cierra el archivo
}

bool verificaPosicionArch(int posicion) {	// Funciona para comprobar que exista un elemento en el archivo en la posicion que se marque
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo" << endl;
		exit(1);
	}
	//archivo.seekg(0);
	int index = 0;
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (posicion == index)
		{
			archivo.close();
			return true;
		}

		index++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archivo.close();
	return false;
}

void leer() // El metodo leer, imprime toda la informacion del txt.
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	//archivo.seekg(0);
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		cout << "\nNombre: " << p.nombre << " Edad: " << p.edad << " Genero: " << p.genero << " Estado Civil: " << p.estadoCivil
			<< " Oficio: " << p.oficio << " Sueldo: " << p.sueldo << " Años de trabajo: " << p.anosTrabajo << " Cantidad de hijos: " << p.cantHijos
			<< " Hobby: " << p.hobby << " Tipo de alimentacion: " << p.tipoAlimentacion << " Tipo de comida: " << p.tipoComida
			<< " Tipo de musica: " << p.tipoMusica << " Provincia: " << p.provincia << " Canton: " << p.canton << " Distrito: " << p.distrito << " Numeros de mascotas: " << p.numMascotas << endl;

		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archivo.close();
}

int buscaPersona(string nombre) // Se busca la persona del archivo y retorna su posicion que posee en el archivo
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo" << endl;
		exit(1);
	}
	//archivo.seekg(0);
	int index = 0;
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (p.nombre == nombre)
		{
			archivo.close();
			cout << "\nSe encuentra en la posicion: " << index << endl;
			return index;
		}

		index++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	cout << "No se encontró el nombre" << endl;
	archivo.close();
}
bool boolBuscaPersona(string nombre) // Se busca la persona del archivo si esta repetida
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo" << endl;
		exit(1);
	}
	//archivo.seekg(0);
	int index = 0;
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (p.nombre == nombre)
		{
			archivo.close();
			cout << "\nNombre repetido encuentra en la posicion: " << index << endl;
			return true;
		}

		index++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	cout << "Nombre no esta repetido en el archivo, proceda con los demas valores" << endl;
	archivo.close();
	return false;
}


void leerPersona(int posicion) // Se imprime la persona en base a su posicion en el archivo
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	if (verificaPosicionArch(posicion)) {	//si la posicion existe en el archivo se imprimen los datos
		archivo.seekg(posicion * sizeof(p), ios::beg);
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
		cout << "\nNombre: " << p.nombre << " Edad: " << p.edad << " Genero: " << p.genero << " Estado Civil: " << p.estadoCivil
			<< " Oficio: " << p.oficio << " Sueldo: " << p.sueldo << " Años de trabajo: " << p.anosTrabajo << " Cantidad de hijos: " << p.cantHijos
			<< " Hobby: " << p.hobby << " Tipo de alimentacion: " << p.tipoAlimentacion << " Tipo de comida: " << p.tipoComida
			<< " Tipo de musica: " << p.tipoMusica << " Provincia: " << p.provincia << " Canton: " << p.canton << " Distrito: " << p.distrito << " Numero de mascotas: " << p.numMascotas << endl;
		archivo.close();
	}
	else
		cout << "Posicion inexistente en el archivo" << endl;
}

int totalpersonas() { // Cuenta el total de personas que hay en el archivo
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	int i = 0;
	//archivo.seekg(0);
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		i++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archivo.close();
	return i;
}


void modificarPersona(Persona modificar, int posicion) { // Se modifica la persona, segun el id ingresa de la persona a modificar


	fstream archivo("lista.txt", ios::in | ios::out | ios::binary);

	if (archivo.fail()) {
		cout << "\nEl archivo no se puede abrir";
		exit(1);
	}
	if (verificaPosicionArch(posicion)) {	//verifica que exista esa posicion en el archivo
		archivo.seekp(posicion * sizeof(modificar), ios::beg);
		archivo.write(reinterpret_cast<char*>(&modificar), sizeof(modificar));
		archivo.close(); //se cierra el archivo
		cout << "La persona ha sido modificada en la posicion: " << posicion << " Con exito" << endl;
	}
	else
		cout << "Posicion inexistente en el archivo" << endl;
}

/*
	Arbol binario, sus estructuras y funciones
*/
Nodo* generaRaiz() { // Se utiliza para contar el total de personas que estan almacenadas en el archivo y generar la raiz del arbol de decision
	//cuenta las personas del archivo para crear la raiz
	int c = totalpersonas();

	//Se crea la raiz
	Nodo* nn = new Nodo(c, "Todos", "");
	nn->sig = NULL;
	return nn;
}

Nodo* recorreNivel(string tipo) { // Sirve para recorrer los nodos y encontrar donde asignar el nuevo tipo
	Nodo* temp = raiz->nHijo;
	Nodo* tempAnt = raiz;
	//recorre el arbol
	while (temp != NULL) {
		tempAnt = temp;
		temp = temp->nHijo;
		if (temp->nivel == tipo) {
			return temp;	//si encuentra el nivel
		}
	}
	//si no se encuentra el nivel
	return temp;
}

Nodo* recorreNodoH(Nodo* temp, string valor) { // Recorre el nodo de manera horizontal para saber que valores tiene el nivel
	while (temp != NULL) {
		if (temp->valor == valor) { //si existe el valor
			return temp;
		}
		temp = temp->sig;
	}
	return NULL; //si no existe va a ser NULL
}

Lista* agregaPosicion(Nodo* temp, int posicion) { // Agrega la poscion en las sublistas
	//recorrer la sublista para colocar la posicion al final de la lista
	Lista* lista = temp->sublista;
	Lista* nnL = new Lista(posicion);
	nnL->nexoNodo = temp;
	if (lista == NULL) {
		lista = nnL;
	}
	else {
		Lista* tempL = lista;
		while (tempL->sig != NULL)
			tempL = tempL->sig;
		tempL->sig = nnL;
	}

	return lista;
}

Nodo* creaNodoString(string valor, int posicion, Nodo* r, string tipoN) { // Se creo con el fin de crear un nodo tipo String
	//se recorre el nivel
	Nodo* temp = r->nHijo;	//Nodo del nivel Genero
	Nodo* tempAnt = r; //Nodo padre
	while (temp != NULL) {
		if (temp->nivel == tipoN) //si se encuentra el nivel, para el bucle
			break;
		tempAnt = temp;
		temp = temp->nHijo;
	}
	if (temp != NULL) {	//ya existe el nivel
		//busca si hay del mismo valor
		Nodo* t = recorreNodoH(temp, valor); //desde el nodo de inicio busca el valor de la lista
		if (t != NULL) { //si existe el valor
			t->cant += 1;
			t->sublista = agregaPosicion(t, posicion);
		}
		else { //Si no existe el valor
			//se recorre al ultimo valor de la lista
			while (temp->sig != NULL) {
				temp = temp->sig;
			}


			Nodo* nn = new Nodo(1, tipoN, valor);
			nn->nPadre = tempAnt;

			nn->sig = NULL;
			temp->sig = nn; //se asigna al arbol
			//generando la sublista
			Lista* nnL = new Lista(posicion);
			nnL->sig = NULL;
			nnL->nexoNodo = temp; //enlace al nodo seleccionado segun el valor
			nn->sublista = nnL; //se agrega la lista al nuevo nodo
		}
	}
	else { //no existe el nivel, entonces lo crea con sus respectivos valores
		Nodo* nn = new Nodo(1, tipoN, valor); // en el valor iria el valor conseguido por el archivo falta generar el codigo para conseguir ese valor
		nn->cant = 1; //la persona que crea el nodo
		nn->sig = NULL;
		nn->nPadre = tempAnt;
		tempAnt->nHijo = nn;

		//crea sublista primer dato
		nn->sublista = agregaPosicion(nn, posicion);
	}
	return r;
}

//Las funciones determina... funcionan para retornar un valor que va a servir para insertarlo en un nodo como corresponda
string determinaValorEdad(int valor) { // Se utiliza para determinar en que nodo del nivel edad ira el valor que se presente en el archivo
	if (valor < 18)
		return "<18";
	else if (valor <= 50)
		return "18<=50";
	else	//valor > 50
		return ">50";
}

string determinaValorSueldo(int valor) {
	if (valor < 100000)
		return "<100'000";
	else if (valor < 500000)
		return "100'000 < 500'000 ";
	else if (valor < 1000000)
		return "500'000 <= 1'000'000";
	else
		return ">1'000'000";
}

string determinaValorCantH(int valor) {
	if (valor <= 2)
		return "<=2";
	else if (valor <= 5)
		return "2 <= 5";
	else
		return ">5";
}

string determinaValorAnosT(int valor) { // Años trabajados
	if (valor < 3)
		return "<3";
	else if (valor < 5)
		return "3 <= 5";
	else if (valor <= 10)
		return "5 <= 10";
	else
		return "> 10";
}

string determinaValorCantM(int valor) { // Cantidad de mascotas
	if (valor <= 2)
		return "<2";
	else if (valor <= 10)
		return "2 <= 10";
	else
		return ">10";
}

Nodo* creaNodoInt(int valor, int posicion, Nodo* r, string tipoN) { // Funcion que se utiliza para generar un nivel si el valor dado es un entero
	/*
	Se deben de realizar agrupaciones pre establecidas mediante las condiciones
	para convertir int a string se usa:
	int a = 10;
	stringstream ss;
	ss << a;
	string str = ss.str();
	Esto se utilizara para poder insertar el dato del valor a nodo que debe de ser un string
	Previamente debe de pasar el int por algunas condiciones pare determinar en qué nodo debe de ir
	*/
	//Se recorre el nivel
	Nodo* temp = r->nHijo;	//Nodo del nivel Edad
	Nodo* tempAnt = r; //Nodo padre
	while (temp != NULL) {
		if (temp->nivel == tipoN) //si se encuentra el nivel, para el bucle
			break;
		tempAnt = temp;
		temp = temp->nHijo;
	}
	//Determina el cuál es el tipo, para agrupar el valor correctamente
	string v;
	if (tipoN == "Edad")
		v = determinaValorEdad(valor);
	else if (tipoN == "Sueldo")
		v = determinaValorSueldo(valor);
	else if (tipoN == "Anos Trabajo")
		v = determinaValorAnosT(valor);
	else if (tipoN == "Cantidad Hijos")
		v = determinaValorCantH(valor);
	else if (tipoN == "Cantidad de Mascotas")
		v = determinaValorCantM(valor);
	//este condicional determina si existe  o no el nivel
	if (temp != NULL) {	//ya existe el nivel
		//busca si hay del mismo valor
		Nodo* t = recorreNodoH(temp, v); //desde el nodo de inicio busca el valor de la lista
		if (t != NULL) { //si existe el valor
			t->cant += 1;
			t->sublista = agregaPosicion(t, posicion);
		}
		else { //Si no existe el valor
			//se recorre al ultimo valor de la lista
			while (temp->sig != NULL)
				temp = temp->sig;
			string v = determinaValorEdad(valor);
			Nodo* nn = new Nodo(1, tipoN, v);
			nn->nPadre = tempAnt;
			nn->sig = NULL;
			temp->sig = nn; //se asigna al arbol
			//generando la sublista
			temp->sublista = agregaPosicion(temp, posicion);
		}
	}
	else { //no existe el nivel, entonces lo crea con sus respectivos valores
		Nodo* nn = new Nodo(1, tipoN, v); // en el valor iria el valor conseguido por el archivo falta generar el codigo para conseguir ese valor
		nn->cant = 1; //la persona que crea el nodo
		nn->sig = NULL;
		nn->nPadre = tempAnt;
		tempAnt->nHijo = nn;

		//
		//crea sublista primer dato
		nn->sublista = agregaPosicion(nn, posicion);

	}
	return r;
}

bool validaInt(string var) {	//Funciona decodifica el string para saber si son numeros digitados
	int largo = var.size();
	int i = 0;
	while (i < largo) {
		if (!isdigit(var[i])) //si el char no es un entero
			return false;
		i++;
	}
	return true;	//si todos los chars son numeros positivos, no se permiten signos
}

string tipoOpcion(int opcion) {
	string nivel;
	if (opcion == 1)
		return "Edad";
	else if (opcion == 2)
		return "Genero";
	else if (opcion == 3)
		return"Estado Civil";
	else if (opcion == 4)
		return"Oficio";
	else if (opcion == 5)
		return"Sueldo";
	else if (opcion == 6)
		return"Años de Trabajo";
	else if (opcion == 7)
		return "Cantidad de Hijos";
	else if (opcion == 8)
		return "Hobby";
	else if (opcion == 9)
		return"Tipo de Alimentacion";
	else if (opcion == 10)
		return"Tipo Comida";
	else if (opcion == 11)
		return"Tipo Musica";
	else if (opcion == 12)
		return"Provincia";
	else if (opcion == 13)
		return"Canton";
	else if (opcion == 14)
		return "Distrito";
	else if (opcion == 15)
		return"Cantidad Mascotas";
	else
		return "";
}

bool verificaNiveles(Nodo* raiz, int opcion) {
	Nodo* temp = raiz;
	int cont = 0;
	string tipo = tipoOpcion(opcion);
	while (temp != NULL) {
		if (temp->nivel == tipo)	// Si la opcion que se eligió ya fue usada en el arbol de decision no se inserta de nuevo o se excede los 15 niveles
			return false;
		temp = temp->nHijo;
		cont++;
	}
	return true;	// Si la opcion no existe en el arbol de decision se puede insertar
}

bool verificaMinimo(Nodo* raiz) {

	int cont = -1;
	Nodo* temp = raiz;
	while (temp != NULL) {
		temp = temp->nHijo;
		cont++;
	}
	if (cont < 3) {
		//system("CLS");
		cout << "*********************Ingrese otro nivel minimo 3" << ", hay: " << cont << "**********************\n" << endl;
		return false;
	}
	return true;
}

// Estructura del Arbol Binario
Nodo* arbolDecision(Nodo* r) {	//Se realiza el arbol de decision
	cout << "\t\t\t-------------CREACION DEL ARBOL BINARIO---------------" << endl;
	cout << "Se selecciona la opcion que desea" << endl;
	cout << "\n1-Edad  2-Genero  3-Estado civil  4-Oficio " << endl;
	cout << "5-Sueldo  6-Anios de trabajo  7-Cantidad de hijos  8-Hobby  9-Tipo de alimentacion" << endl;
	cout << "10-Tipo de comida  11-Tipo de musica  12-Provincia  13-Canton  14-Distrito  15-Cantidad de mascotas" << endl;
	cout << "\nIntroduzca una opcion : " << endl;
	string num;
	cin >> num;
	//valida si el string contiene numero enteros positivos sin caracteres
	if (validaInt(num)) {
		//convierte el string en un int
		int opcion = stoi(num, NULL, 10);	//int stoi (const string&  str, size_t* idx = 0, int base = 10);

		//verifica si está repetida la opcion en el arbol, si tambien ha llegado a su maximo
		if (verificaNiveles(r, opcion)) {
			//abre el archivo
			ifstream archivo("lista.txt", ios::in | ios::binary);
			struct Persona p;
			if (archivo.fail()) {
				cout << "No se pudo abrir el archivo";
				exit(1);
			}
			int posicion = 0;	//tiene la funcion de saber la posicion de los elementos en el archivo
			archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
			while (!archivo.eof()) {//end of file
				//falta funcion que determine que no se repitan
				//contador para un maximo y minimo de niveles

				if (opcion == 1) {
					r = creaNodoInt(p.edad, posicion, r, "Edad");
					cout << "Dato Edad insertado con exito" << endl;
				}
				else if (opcion == 2) {
					r = creaNodoString(p.genero, posicion, r, "Genero");
					cout << "Dato Genero insertado con exito" << endl;
				}
				else if (opcion == 3) {
					r = creaNodoString(p.estadoCivil, posicion, r, "Estado Civil");
					cout << "Dato Estado Civil insertado con exito" << endl;
				}
				else if (opcion == 4) {
					r = creaNodoString(p.oficio, posicion, r, "Oficio");
					cout << "Dato Oficio insertado con exito" << endl;
				}
				else if (opcion == 5) {
					r = creaNodoInt(p.sueldo, posicion, r, "Sueldo");
					cout << "Dato Sueldo insertado con exito" << endl;
				}
				else if (opcion == 6) {
					r = creaNodoInt(p.anosTrabajo, posicion, r, "Anos de Trabajo");
					cout << "Nivel Anos de Trabajo insertado con exito" << endl;
				}
				else if (opcion == 7) {
					r = creaNodoInt(p.cantHijos, posicion, r, "Cantidad de Hijos");
					cout << "Nivel Cantidad de Hijos insertado con exito" << endl;
				}
				else if (opcion == 8) {
					r = creaNodoString(p.hobby, posicion, r, "Hobby");
					cout << "Nivel Hobby insertado con exito" << endl;
				}
				else if (opcion == 9) {
					r = creaNodoString(p.tipoAlimentacion, posicion, r, "Tipo de Alimentacion");
					cout << "Nivel Tipo de Alimentacion insertado con exito" << endl;
				}
				else if (opcion == 10) {
					r = creaNodoString(p.tipoComida, posicion, r, "Tipo Comida");
					cout << "Nivel Tipo Comida insertado con exito" << endl;
				}
				else if (opcion == 11) {
					r = creaNodoString(p.tipoMusica, posicion, r, "Tipo Musica");
					cout << "Nivel Tipo Musica insertado con exito" << endl;
				}
				else if (opcion == 12) {
					r = creaNodoString(p.provincia, posicion, r, "Provincia");
					cout << "Nivel Provincia insertado con exito" << endl;
				}
				else if (opcion == 13) {
					r = creaNodoString(p.canton, posicion, r, "Canton");
					cout << "Nivel Canton insertado con exito" << endl;
				}
				else if (opcion == 14) {
					r = creaNodoString(p.distrito, posicion, r, "Distrito");
					cout << "Nivel Distrito insertado con exito" << endl;
				}
				else if (opcion == 15) {
					r = creaNodoInt(p.numMascotas, posicion, r, "Cantidad de Mascotas");
					cout << "Nivel Cantidad Mascotas insertado con exito" << endl;
				}
				archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
				posicion += 1;

			}
			archivo.close();
		}
		else
			cout << "Excede la cantidad maxima de niveles del arbol o la opcion ya se encontraba en el arbol";
	}
	else
		cout << "Dato incorrecto" << endl;
	//Sale del condicional anterior
	cout << endl << "Desea continuar?" << endl << "digite cualquier numero del 1-9 para continuar o digite 0 para terminar" << endl;
	int op;
	cin >> op;

	if (op != 0 || !verificaMinimo(r)) {
		r = arbolDecision(r);
	}
	system("CLS");
	cout << "Arbol generado con exito" << endl;
	return r;
}

/*
	Consultas
*/

//Consulta 1
void contarHojas() { // Metodo para contar nodos hojas del arbol de decision.
	Nodo* tempV = raiz;
	int hoja = 0;
	//Para recorrer hacia abajo.
	while (tempV->nHijo != NULL) {	//el ultimo de el arbol posee los nodos hojas
		tempV = tempV->nHijo;
	}
	//Para recorrer hacia el lado
	Nodo* tempH = tempV;
	while (tempH != NULL) {
		hoja++;
		tempH = tempH->sig;
	}
	cout << "Cantidad de hojas en el arbol: " << hoja<<endl;
}

//Consulta 2
void imprimeNodoNivelx() {
	string nivel;
	cout << "Escriba el nivel en el que desea ver la cantidad de nodos: " << endl;
	cin >> nivel;
	Nodo* temp = raiz;
	int cont = 0;
	while (temp != NULL) {	//se ubica en el nivel que corresponda
		if (temp->nivel == nivel)
			break;
		temp = temp->nHijo;
	}
	if (temp == NULL)
		cout << "No existe el nivel" << endl;
	else {
		while (temp != NULL) {	//cuenta los nodos del nivel
			temp = temp->sig;
			cont++;
		}
		cout << "La cantidad de nodos del nivel " << nivel << " es " << cont << endl;
	}
}

//Consulta3
void imprimeNivelGrande() {
	string nivel;
	Nodo* temp = raiz;
	int cont = 0;
	int contM = 0;	//contador de máximo
	while (temp != NULL) {	//se ubica en el nivel que corresponda

		Nodo* tempV = temp;
		while (tempV != NULL) {	//cuenta los nodos del nivel
			tempV = tempV->sig;
			cont++;
		}
		if (cont > contM) {	//si el nivel tiene más valores que el nivel con mayor numero de valores en el momento
			contM = cont;
			nivel = temp->nivel;	//nombre del nivel con mayor valores
		}
		temp = temp->nHijo;	//recorre el nivel
	}
	cout << "La categoria con mas valores es: " << nivel << " con " << contM << endl;
}

//Consulta4
void imprimeValorMayMen() {
	string num;
	cout << "Se selecciona la opcion que desea ver el mayor y menor" << endl;
	cout << "\n1-Edad  2-Genero  3-Estado civil  4-Oficio " << endl;
	cout << "5-Sueldo  6-Anios de trabajo  7-Cantidad de hijos  8-Hobby  9-Tipo de alimentacion" << endl;
	cout << "10-Tipo de comida  11-Tipo de musica  12-Provincia  13-Canton  14-Distrito  15-Cantidad de mascotas" << endl;
	cout << "\nIntroduzca una opcion : " << endl;
	cin >> num;
	if (validaInt(num)) {
		int opcion = stoi(num, NULL, 10);
		string nivel = tipoOpcion(opcion);
		Nodo* temp = raiz;
		while (temp != NULL) {	//se ubica en el nivel que corresponda
			if (temp->nivel == nivel)
				break;
			temp = temp->nHijo;
		}
		if (temp == NULL)
			cout << "No existe el nivel ingresado" << endl;
		else {
			Nodo* tempV = temp;	//se utiliza para desplazarse horizontalmente
			int cMayor = 0;
			string nMayor;
			int cMenor = 0;
			string nMenor;
			cMenor = temp->cant;	//asignamos el valor a el menor
			while (tempV != NULL) {
				if (cMayor <= tempV->cant) {	//busca el mayor
					cMayor = tempV->cant;
					nMayor = tempV->valor;
					cout << cMayor << " " << nMayor << endl;
				}
				if (cMenor >= tempV->cant) {	//busca el menor
					cMenor = tempV->cant;
					nMenor = tempV->valor;
					cout << cMenor << " " << nMenor << endl;
				}
				tempV = tempV->sig;
			}
			cout << "El nivel: " << nivel << " el valor con mayor cantidad de personas: " << nMayor << "\tel valor con menor cantidad de personas: " << nMenor << endl;
		}
	}
	else
		cout << "valor digitado erroneo" << endl;
	return;
}

//Consulta 5
void numeroPersonaNivel() {
	//Contadores
	int conNivel = 0;
	//Punteros
	Nodo* tempV = raiz;
	//Para recorrer hacia abajo.
	while (tempV != NULL) {
		int conPersona = 0;
		Nodo* tempH = tempV;
		while (tempH != NULL) {
			conPersona += tempH->cant;
			tempH = tempH->sig;
		}
		cout << "Nivel" << conNivel << ": " << conPersona << endl;
		tempV = tempV->nHijo;
		conNivel++;
	}
}

//Consulta 6
void buscaValorArch() {
	int cont = 0;
	string tipo;
	string valor;
	cin.ignore();
	cout << "Digite la caracteristica que desea buscar en el archivo: "<<endl;
	getline(cin, tipo);
	cout << "Digite el valor que desea buscar en el archivo: " << endl;
	getline(cin, valor);
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo" << endl;
		exit(1);
	}
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (tipo == "Edad" && determinaValorEdad(p.edad) == valor)
			cont += 1;
		else if (tipo == "Genero" && p.genero == valor)
			cont += 1;
		else if(tipo == "Estado Civil" && p.estadoCivil==valor)
			cont += 1;
		else if(tipo == "Oficio" && p.oficio == valor)
			cont += 1;
		else if(tipo == "Sueldo" && determinaValorSueldo(p.sueldo) == valor)
			cont += 1;
		else if(tipo == "Anos de Trabajo" &&  determinaValorAnosT(p.anosTrabajo)== valor)
			cont += 1;
		else if(tipo == "Cantidad de Hijos" && determinaValorCantH(p.cantHijos) == valor)
			cont += 1;
		else if(tipo == "Hobby" && p.hobby == valor)
			cont += 1;
		else if (tipo == "Tipo de Alimentacion" && p.tipoAlimentacion == valor)
			cont += 1;
		else if(tipo == "Tipo de Comida" && p.tipoComida == valor)
			cont += 1;
		else if(tipo == "Tipo de Musica" && p.tipoMusica == valor)
			cont += 1;
		else if(tipo == "Provincia" && p.provincia == valor)
			cont += 1;
		else if(tipo == "Canton" && p.canton == valor)
			cont += 1;
		else if(tipo == "Distrito" && p.distrito == valor)
			cont += 1;
		else if(tipo == "Numero Mascotas" && determinaValorCantM(p.numMascotas) == valor)
			cont += 1;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archivo.close();
	cout << "En el archivo:\n" << tipo << "= " << valor << "= " << cont << endl;
	//return cont;
}

void buscaValorArbol() {
	string tipo;
	string valor;
	int cont =0;
	cout << "Digite la caracteristica que desea buscar en el Arbol: " << endl;
	getline(cin, tipo);
	cout << "Digite el valor que desea buscar en el Arbol: " << endl;
	getline(cin, valor);
	Nodo* temp = raiz;
	while (temp != NULL) {	//Para localizar el nivel
		if (temp->nivel == tipo)
			break;
		temp = temp->nHijo;
	}
	if (temp != NULL) {	//localiza el valor
		while (temp != NULL) {
			if (temp->valor == valor)
				cont= temp->cant;
			temp = temp ->sig;
		}
	}
	cout << "En el Arbol:\n" << tipo << "= " << valor << "= " << cont << endl;
	//return 0;
}
void imprimeTipoArchArbol() {
	/*string tipoArch;
	string valorArch;
	string tipoArb;
	string valorArb;
	cout << "Digite la caracteristica que desea buscar en el archivo: ";
	getline(cin, tipoArch);
	cout << "Digite el valor que desea buscar en el archivo: " << endl;
	getline(cin,valorArch);*/
	buscaValorArch();
	//cout << "En el archivo:\n" << tipoArch << "= " << valorArch << "= " << contArch<<endl;

	/*cout << "Digite la caracteristica que desea buscar en el Arbol: " << endl;
	getline(cin, tipoArb);
	cout << "Digite el valor que desea buscar en el Arbol: " << endl;
	getline(cin, valorArb);*/
	buscaValorArbol();
	//cout << "En el Arbol:\n" << tipoArb << "= " << valorArb << "= " << contArbol << endl;

}

	//Reportes
//Reporte 1
Nodo * imprimirInformacionPreorden(Nodo*n) { //Imprimir la información completa del árbol en preorden.
	if (n == NULL)
	{
		return n;
	}

	cout << n->nivel << endl;  // Aqui falta algo mas?
	imprimirInformacionPreorden(n->nPadre);
	imprimirInformacionPreorden(n->nHijo);
	//n -> sig;
}

//Reporte 2
void imprimeTodo() {
	Nodo* temp = raiz->nHijo;
	while (temp != NULL) {
		cout << temp->nivel << " : ";
		Nodo* tempL = temp;
		while (tempL != NULL) {
			cout <<tempL->valor<<" = "<<tempL->cant<<"\t";
			tempL = tempL->sig;
		}
		temp = temp->nHijo;
		cout << endl;
	}

}
//Reporte 3
void imprimeAnchura() {
	Nodo* temp = raiz->nHijo;
	while (temp != NULL) {
		int ancho = 0;
		Nodo* tempL = temp;
		while (tempL != NULL) {
			ancho += 1;
			tempL = tempL->sig;
		}
		cout << temp->nivel << " : " << ancho<<endl;
		temp = temp->nHijo;
	}
}
//Reporte 4
void imprimenHijo() {
	string padre;
	cin.ignore();
	cout << "Digite el Nodo Padre: " << endl;
	getline(cin, padre);
	Nodo* temp = raiz;
	while (temp != NULL) {
		if (temp->nivel == padre)
			break;
		temp = temp->nHijo;
	}
	if (temp != NULL) {
		Nodo* tempL = temp;
		while (tempL != NULL) {
			cout << tempL->nivel << " : " << tempL->valor << endl;
			tempL = tempL->sig;
		}
	}
	else {
		cout << "No existe el nodo digitado"<<endl;
	}
}

/*
	Funciones que van a en el main.
*/


void agregarPersona() { // Metodo para agregar una persosna al archivo

	string datoString;
	cout << "Nombre: " << endl;
	getline(cin, datoString);
	if (!boolBuscaPersona(datoString)) {
		Persona personaNueva;

		strncpy_s(personaNueva.nombre, datoString.c_str(), sizeof(personaNueva.nombre));

		cout << "Edad: " << endl;
		cin >> personaNueva.edad;
		cin.ignore();

		cout << "Genero: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.genero, datoString.c_str(), sizeof(personaNueva.genero));

		cout << "Estado civil: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.estadoCivil, datoString.c_str(), sizeof(personaNueva.estadoCivil));

		cout << "Oficio: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.oficio, datoString.c_str(), sizeof(personaNueva.oficio));

		cout << "Sueldo: " << endl;
		cin >> personaNueva.sueldo;
		cin.ignore();

		cout << "Años de trabajo: " << endl;
		cin >> personaNueva.anosTrabajo;
		cin.ignore();

		cout << "Cantidad de hijos: " << endl;
		cin >> personaNueva.cantHijos;
		cin.ignore();

		cout << "Hobby: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.hobby, datoString.c_str(), sizeof(personaNueva.hobby));

		cout << "Tipo de alimentacion: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.tipoAlimentacion, datoString.c_str(), sizeof(personaNueva.tipoAlimentacion));

		cout << "Tipo de comida: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.tipoComida, datoString.c_str(), sizeof(personaNueva.tipoComida));

		cout << "Tipo de musica: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.tipoMusica, datoString.c_str(), sizeof(personaNueva.tipoMusica));

		cout << "Provincia: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.provincia, datoString.c_str(), sizeof(personaNueva.provincia));

		cout << "Canton: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.canton, datoString.c_str(), sizeof(personaNueva.canton));

		cout << "Distrito: " << endl;
		getline(cin, datoString);
		strncpy_s(personaNueva.distrito, datoString.c_str(), sizeof(personaNueva.distrito));

		cout << "Cantidad de mascotas: " << endl;
		cin >> personaNueva.numMascotas;
		cin.ignore();
		escribir(personaNueva);
		cout << "Se ha agregado la persona" << endl;
	}
}

void modPersona() { // Metodo para que el usuario pueda modificar a alguien del archivo.
	Persona personaNueva;

	string datoString;

	cout << "Nombre: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.nombre, datoString.c_str(), sizeof(personaNueva.nombre));

	cout << "Edad: " << endl;
	cin >> personaNueva.edad;
	cin.ignore();

	cout << "Genero: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.genero, datoString.c_str(), sizeof(personaNueva.genero));

	cout << "Estado civil: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.estadoCivil, datoString.c_str(), sizeof(personaNueva.estadoCivil));

	cout << "Oficio: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.oficio, datoString.c_str(), sizeof(personaNueva.oficio));

	cout << "Sueldo: " << endl;
	cin >> personaNueva.sueldo;
	cin.ignore();

	cout << "Años de trabajo: " << endl;
	cin >> personaNueva.anosTrabajo;
	cin.ignore();

	cout << "Cantidad de hijos: " << endl;
	cin >> personaNueva.cantHijos;
	cin.ignore();

	cout << "Hobby: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.hobby, datoString.c_str(), sizeof(personaNueva.hobby));

	cout << "Tipo de alimentacion: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.tipoAlimentacion, datoString.c_str(), sizeof(personaNueva.tipoAlimentacion));

	cout << "Tipo de comida: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.tipoComida, datoString.c_str(), sizeof(personaNueva.tipoComida));

	cout << "Tipo de musica: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.tipoMusica, datoString.c_str(), sizeof(personaNueva.tipoMusica));

	cout << "Provincia: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.provincia, datoString.c_str(), sizeof(personaNueva.provincia));

	cout << "Canton: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.canton, datoString.c_str(), sizeof(personaNueva.canton));

	cout << "Distrito: " << endl;
	getline(cin, datoString);
	strncpy_s(personaNueva.distrito, datoString.c_str(), sizeof(personaNueva.distrito));

	cout << "Cantidad de mascotas: " << endl;
	cin >> personaNueva.numMascotas;
	cin.ignore();

	int posicion;
	cout << "Ingrese la posicion que desea modificar en el archivo: " << endl;
	cin >> posicion;

	modificarPersona(personaNueva, posicion);
}

void escribeTemporal(Persona p) {
	fstream archivo("temporal.txt", ios::in | ios::out | ios::binary);
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo";
		exit(1);
	}
	archivo.seekp(0, ios::end);
	archivo.write(reinterpret_cast<char*>(&p), sizeof(p));
	archivo.close(); //se cierra el archivo
}

void eliminarPersona() {
	string nom;
	cout << "Digite el nombre y apellido que desea eliminar de la lista" << endl;
	getline(cin, nom);
	ifstream archivo("lista.txt", ios::in | ios::out | ios::binary);		//"lista.txt", ios::in | ios::out | ios::binary
	fstream temporal("temporal.txt", ios::in | ios::out | ios::binary | ios::trunc);
	struct Persona p;

	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo";
		exit(1);
	}
	else {
		if (buscaPersona(nom)) {
			archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
			while (!archivo.eof()) {
				if (p.nombre == nom) {
					cout << "\nDato eliminado" << endl;
				}
				else {
					escribeTemporal(p);
				}
				archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
			}
		}
	}
	temporal.close();
	archivo.close();
	remove("lista.txt");
	rename("temporal.txt", "lista.txt");
}
/*
	Partes del Main.
*/
void personasMenu() {
	int opcion;
	cout << "1. Agregar persona" << endl;
	cout << "2. Modificar a una persona" << endl;
	cout << "3. Borrar a una persona" << endl;
	cout << "4. Leer a una persona" << endl;

	cout << "Ingrese una opcion: " << endl;
	cin >> opcion;

	if (opcion == 1) {
		agregarPersona();
	}
	if (opcion == 2) {
		modPersona();
	}
	if (opcion == 3) {
		eliminarPersona();
	}
	if (opcion == 4) {
		int numeroPosicion;
		cout << "Ingrese el numero de posicion que desea leer: " << endl;
		cin >> numeroPosicion;
		leerPersona(numeroPosicion);
	}
}

void consultas() {
	int opcion;
	cout << "1. Imprimir la cantidad de hojas en el arbol. " << endl;
	cout << "2. Imprimir la cantidad de nodos en un nivel deseado." << endl;
	cout << "3. Imprimir cual categoria tiene mas valores diferentes, \nrecorriendo todo el arbol. Debe validar si la categoria esta o no el arbol." << endl;
	cout << "4. Imprimir en el nivel deseado cual es el valor de la caracteristica \ncon mayor cantidad de personas y cual es la que tiene menor cantidad de personas!= de cero." << endl;
	cout << "5. Imprimir la comprobacion de la suma de todas las cantidades por nivel." << endl;
	cout << "6. Imprimir la cantidad de una caracteristica con un valor en especifico recorriendo el archivo, \nademas, imprimir la cantidad de una caracteristica con un valor en especifico recorriendo \nel arbol creado. Si en el arbol actual no se realizo esa clasificacion indicarlo o si no hay con ese determinado \nvalor indicarlo tambien. " << endl;
	cout << "\nIngrese una opcion: " << endl;
	cin >> opcion;

	if (opcion == 1) {
		contarHojas();
	}
	if (opcion == 2) {
		imprimeNodoNivelx();
	}
	if (opcion == 3) {
		imprimeNivelGrande();
	}
	if (opcion == 4) {
		imprimeValorMayMen();
	}
	if (opcion == 5) {
		numeroPersonaNivel();
	}
	if (opcion == 6) {
		imprimeTipoArchArbol();
	}

}

void reportes() {
	int opcion;
	cout << "1. Imprimir la informacion completa del arbol en preorden." << endl;
	cout << "2. Imprimir la informacion completa del arbol por cada flujo de informacion." << endl;
	cout << "3. Imprimir el arbol en anchura (por niveles) indicando el nivel respectivo." << endl;
	cout << "4. Imprimir la subClasificacion de una rama en especifico. Se debe solicitar caracteristica y valor." << endl;
	cout << "\nIngrese una opcion: " << endl;
	cin >> opcion;

	if (opcion == 1) {
		imprimirInformacionPreorden(raiz);
	}
	if (opcion == 2) {
		imprimeTodo();
	}
	if (opcion == 3) {
		imprimeAnchura();
	}
	if (opcion == 4) {
		imprimenHijo();
	}
}

void menu() {

	int opcionPrincipal;
	bool repetir = true;

	do {
		cout << "\t\t\t---------------------Menu-------------------" << endl;
		cout << "\n1. Creacion del arbol binario" << endl;
		cout << "2. Opciones del arbol binario" << endl,

			cout << "\nIngrese una opcion: " << endl;
		cin >> opcionPrincipal;

		if (opcionPrincipal == 1) {
			//Metodo de la creacion del arbol binario creado a la manera del usuario.
			raiz = generaRaiz();
			raiz= arbolDecision(raiz);
		}
		if (opcionPrincipal == 2) {
			int opcionSecundaria;
			cout << "1. Personas" << endl;
			cout << "2. Consultas" << endl;
			cout << "3. Reportes" << endl;

			cout << "Ingrese una opcion: " << endl;
			cin >> opcionSecundaria;
			if (opcionSecundaria == 1) {
				personasMenu();
			}
			if (opcionSecundaria == 2) {
				consultas();
			}
			if (opcionSecundaria == 3) {
				reportes();
			}
		}

	} while (repetir);

}

//Datos quemados.
void datosQuemados() {
	fstream archivo("lista.txt", ios::in | ios::out | ios::binary | ios::trunc);
	//in order
	//nombre, edad, genero, estadocivil, oficio, sueldo, a�os de trabajo, cant hijos, hobby, alimentaci�n, comida, musica, provincia, canton , distrito

	Persona p1 = { "Ana Alves", 20, "Mujer", "Soltera", "Miscelanea", 500000, 3, 1, "Futbol", "Pollotariano", "Salado", "Hardcore zumba","Alajuela","San Ram�n","Palmares", 1 };
	escribir(p1);
	Persona p2 = { "Rambo Alvarez", 20, "Hombre", "Viudo", "Militar", 100000, 15, 8, "Basquetbol", "Carnivoro", "Picante", "Metal","San Jose","Curridabat","La Palma", 0 };
	escribir(p2);
	Persona p3 = { "Carlos Rojas", 37, "Hombre", "Soltero", "Chef", 500000, 3, 0, "Ver series", "Omnivoro", "Dulce", "Salsa","Alajuela","San Carlos","La Palmera", 5 };
	escribir(p3);
	Persona p4 = { "Alina Araya", 25, "Mujer", "Soltera", "Enfermera", 700000, 5, 2, "Tenis", "Lactovegetariano", "Agridulce", "Merengue","Alajuela","Grecia","Bolivar", 1 };
	escribir(p4);
	Persona p5 = { "Jose Quesada", 21, "Hombre", "Casado", "Programador", 1000000, 3, 0, "Jugar play", "Vegetariano", "Picante", "Merengue","Alajuela","San Ramon","Palmares", 2 };
	escribir(p5);
	Persona p6 = { "Maria Carranza", 40, "Mujer", "Soltera", "QA", 1200000, 16, 0, "Caminar", "Omnivoro", "Condimentada", "Jazz","San Jose","Escazu","Escazu", 2 };
	escribir(p6);
	Persona p7 = { "Fernanda Huertas", 27, "Mujer", "Soltera", "Ingeniera Industrial", 800000, 10, 0, "Leer libros", "Vegano", "Picante", "Jazz","Guanacaste","Liberia","Mayorga", 0 };
	escribir(p7);
	Persona p8 = { "Carlos Vaca", 37, "Hombre", "Divorciado", "Ebanista", 2000000, 20, 10, "Pintar", "Omnivoro", "Salado", "Rock","Heredia","San Rafael","La Plaza", 2 };
	escribir(p8);
	Persona p9 = {"Alba Cascarron", 50, "Mujer", "Viuda", "Costurera", 300000, 25, 2, "Ver television", "Crudismo", "Dulce", "Techno","Puntarenas","Buenos Aires","La Penca", 1};
	escribir(p9);
	Persona p10 = { "Marlen Montero", 48, "Mujer", "Casada", "Ama de casa", 150000, 0, 5, "Ver novelas", "Lactovegetariano", "Agridulce", "Rock","Alajuela","San Carlos","La Tigra", 3 };
	escribir(p10);
	Persona p11 = { "Pancracio Sancho", 80, "Hombre", "Viudo", "Pensionado", 150000, 55, 7, "Ver noticias", "Omnivoro", "Condimentada", "Clasica","Alajuela","Los Chiles","San Jorge", 0 };
	escribir(p11);
	Persona p12 = { "Fleyber Saborio", 22, "Hombre", "Divorciado", "Soldador", 1000000, 3, 1, "Poker", "Omnivoro", "Condimentada", "Metal","San Jose","Guachipelin","Villareal", 2 };
	escribir(p12);
	Persona p13 = { "Marina Rojas", 37, "Mujer", "Divorciada", "Doctora", 1500000, 10, 2, "Ver series", "Vegano", "Dulce", "Rock","Cartago","Cartago","Carmen", 4 };
	escribir(p13);
	Persona p14 = { "Maria Urbina", 17, "Mujer", "Soltera", "Estudiante", 0, 0, 0, "Tenis", "Vegana", "Picante", "Electronica","Guanacaste","Liberia","La Leyla", 4 };
	escribir(p14);
	Persona p15 = { "Alma Costa", 70, "Mujer", "Vuida", "Pensionada", 1000000, 3, 10, "Ver novelas", "Vegetariano", "Dulce", "Jazz","Alajuela","San Ramon","Palmares", 0 };
	escribir(p15);
	Persona p16 = { "Ana Carranza", 41, "Mujer", "Soltera", "Programadora", 1500000, 16, 0, "Correr", "Pollotariano", "Agridulce", "Hardcore","San Jose","Curridabat","Curridabat", 0 };
	escribir(p16);
	Persona p17 = { "Alvaro Jimenez", 27, "Hombre", "Soltero", "Policia", 500000, 3, 1, "Futbol", "Omnivoro", "Salado", "Gospel","Puntarenas","Esparza","San Rafael", 5 };
	escribir(p17);
	Persona p18 = { "Sofia Salas", 19, "Mujer", "Soltera", "Recepcionista", 500000, 1, 0, "Ver series", "Omnivoro", "Picante", "Caribe�o","Alajuela","San Carlos","Agua Azul", 1 };
	escribir(p18);
	Persona p19 = { "Linaza Harvey", 29, "Mujer", "Casada", "Boxeadora", 100000, 10, 1, "Tenis", "Ovovegetariana", "Condimentada", "Bachata","Alajuela","Los Chiles","Medio Queso", 2 };
	escribir(p19);
	Persona p20 = { "Gerardo Guzman", 35, "Hombre", "Viudo", "Carpintero", 450000, 10, 0, "Leer el periodico", "Carnivoro", "Salado", "Rock and Roll","Limon","Guacimo","Cantarrana", 3 };
	escribir(p20);
	Persona p21 = { "Sofia Sanchez", 37, "Mujer", "Casada", "Administracion", 400000, 5, 2, "Comprar Zapatos", "Vegetariana", "Dulce", "Country","Cartago","Carmen","Merced", 0 };
	escribir(p21);
	Persona p22 = { "Pancho Maradiaga", 90, "Hombre", "Viudo", "Pensionado", 100000, 55, 7, "Ver noticias", "Omnivoro", "Dulce", "Jazz","Alajuela","La Leyla","San Jorge", 4 };
	escribir(p22);
	Persona p23 = { "David Gonzalez", 24, "Hombre", "Soltero", "Jornalero", 200000, 9, 1, "Ver videos", "Omnivoro", "Salado", "Instrumental","Alajuela","San Carlos","Cutris", 2 };
	escribir(p23);
	Persona p24 = { "Tatiana Rojas", 27, "Mujer", "Casada", "Ingeniera", 1500000, 5, 0, "Ver series", "Omnivoro", "Dulce", "Rock","Cartago","Cartago","Ochomogo", 5 };
	escribir(p24);
	Persona p25 = { "Juan Vainas", 40, "Hombre", "Casado", "Doctor", 0, 0, 0, "Tenis", "Vegano", "Berenjena", "Electronica","Guanacaste","Liberia","La Cruz", 5 };
	escribir(p25);
	Persona p26 = { "Evelyn Gutierrez", 24, "Mujer", "Casada", "Ama de Casa", 0, 0, 6, "Ver novelas", "Omnivoro", "Dulce", "Hip Hop","Guanacaste","Bagaces","Mogote", 0 };
	escribir(p26);
	Persona p27 = { "Bellota Azul", 18, "Mujer", "Soltera", "Estudiante", 15000, 0, 0, "Correr", "Pollotariano", "Uvas", "Hardcore","San Jose","Desamparados","Desamparados", 4 };
	escribir(p27);
	Persona p28 = { "Blanca Nieves", 35, "Mujer", "Soltera", "Princesa", 200000, 15, 0, "Ver animales", "Vegana", "Manzana", "Hip Hop","Puntarenas","Esparza","Caldera", 3 };
	escribir(p28);
	Persona p29 = { "Stephanie Quesada", 22, "Mujer", "Casada", "Emprendedora", 350000, 2, 1, "Jugar Futbol", "Omnivoro", "Agridulce", "Reggaeton","Guanacaste","Hojancha","Matambu", 1 };
	escribir(p29);
	Persona p30 = { "Tulio Ramirez", 50, "Hombre", "Soltero", "Reportero", 450000, 7, 2, "Poker", "Omnivoro", "Agridulce", "Techno","Alajuela","Los Chiles","Pangola", 1 };
	escribir(p30);
	Persona p31 = { "Gerardo Mazorca", 61, "Hombre", "Viudo", "Maestro", 2000000, 10, 0, "Correr", "Omnivoro", "Salado", "Jazz","Limon","Guacimo","Cantarrana", 3 };
	escribir(p31);
	Persona p32 = { "Tinkerbell Dalpra", 25, "Mujer", "Casada", "Cajera", 1000000, 3, 10, "Poker", "Omnivoro", "Dulce", "Reggae","Guanacaste","Abangares","La Delta", 5 };
	escribir(p32);
	Persona p33 = { "Gerard Moreno", 20, "Hombre", "Casado", "Empresario", 3000000, 4, 0, "Poker", "Omnivoro", "Picante", "Techno","Heredia","San Rafael","Los Angeles", 3 };
	escribir(p33);
	Persona p34 = { "Xiomara Campos", 56, "Mujer", "Casada", "Estilista", 300000, 4, 1, "Maquillaje", "Omnivoro", "Salado", "Flamenco","Limon","Rio Blanco","Brisas", 1 };
	escribir(p34);
	Persona p35 = { "Juana La Cubana", 50, "Mujer", "Soltera", "Escritora", 600000, 25, 0, "Ver novelas", "Pollotariano", "Pollo", "Reggae","Alajuela","San Ram�n","Bajo Rodriguez", 3 };
	escribir(p35);
	Persona p36 = { "Watermelon Rodriguez", 27, "Mujer", "Casada", "Maestra", 4000000, 8, 3, "Basquetbol", "Omnivoro", "Picante", "Metal","San Jose","Desamparados","La Carpio", 3 };
	escribir(p36);
	Persona p37 = { "Kimberly Rojas", 23, "Mujer", "Soltera", "Estudiante", 100000, 2, 0, "Tomar Cafe", "Omnivoro", "Salado", "Drum and Bass","Guanacaste","Carrillo","Palmira", 0 };
	escribir(p37);
	Persona p38 = { "Rita Peluche", 80, "Mujer", "Soltera", "Enfermera", 700000, 50, 2, "Tenis", "Lactovegetariano", "Berenjena", "Salsa","Alajuela","Los Angeles","Bolivar", 3 };
	escribir(p38);
	Persona p39 = { "Jose Suarez", 21, "Hombre", "Casado", "Futbolista", 1000000, 0, 0, "Jugar play", "Vegetariano", "Picante", "Bachata","Alajuela","San Ramon","Palmares", 2 };
	escribir(p39);
	Persona p40 = { "Gledys Huertas", 55, "Mujer", "Viuda", "Disenadora", 500000, 10, 0, "Ver revistas de moda", "Omnivoro", "Dulce", "Jazz","San Jose","Desamparados","San Miguel", 1 };
	escribir(p40);
	Persona p41 = { "Dickembell Arroyo", 25, "Hombre", "Soltero", "Cajero", 450000, 7, 2, "Poker", "Omnivoro", "Picante", "Techno","Alajuela","Los Chiles","Pangola", 1 };
	escribir(p41);
	Persona p42 = { "Ronald Montero", 47, "Hombre", "Divorciado", "Maestro", 2000000, 10, 2, "Ver series", "Omnivoro", "Cafe", "Rock","Limon","Guacimo","Sarapiqui", 4 };
	escribir(p42);
	Persona p43 = { "Walt Disney", 19, "Hombre", "Casada", "Herrero", 500000, 1, 1, "Futbol", "Omnivoro", "Dulce", "Reggae","Guanacaste","Abangares","La Delta", 0 };
	escribir(p43);
	Persona p44 = { "Chayanne Rojas", 50, "Hombre", "Casado", "Empresario", 3000000, 4, 0, "Poker", "Omnivoro", "Manzana", "Salsa","Heredia","Desamparados","Los Angeles" , 0 };
	escribir(p44);
	Persona p45 = { "Miguel Contreras", 75, "Hombre", "Viudo", "Pensionado", 2500000, 40, 2, "Ganaderia", "Omnivoro", "Salado", "Clasica","Guanacaste","Nandayure","San Rafael", 4 };
	escribir(p45);
	Persona p46 = { "Pepe Jose", 20, "Hombre", "Soltero", "Mesero", 600000, 1, 0, "Ver novelas", "Vegetariano", "Pescado", "Reggae","Cartago","San Ram�n","Bajo Rodriguez", 3 };
	escribir(p46);
	Persona p47 = { "Natasha Vanessa", 60, "Mujer", "Soltera", "Comerciante", 9000000, 50, 9, "Coser", "Omnivoro", "Picante", "Metal","San Jose","Desamparados","La Carpio", 5 };
	escribir(p47);
	Persona p48 = { "Juan Castro", 40, "Hombre", "Casado", "Abogado", 2000000, 20, 2, "Tomar cafe", "Omnivoro", "Salado", "Blues","Guanacaste","Carrillo","Palmira", 0 };
	escribir(p48);
	Persona p49 = { "Katherine Amador", 20, "Mujer", "Soltera", "Estudiante", 1150000, 0, 0, "Reposteria", "Omnivoro", "Dulce", "Country","Alajuela","San Carlos","Pocosol", 2 };
	escribir(p49);
	Persona p50 = { "Samantha Montero", 19, "Mujer", "Soltera", "Estudiante", 175000, 0, 0, "Ver series", "Omnivoros", "Jalapeno", "Metal","Alajuela","San Carlos","Fortuna", 2 };
	escribir(p50);
	archivo.close();
}

int main()
{
	datosQuemados();
	menu();

	return 0;
}
