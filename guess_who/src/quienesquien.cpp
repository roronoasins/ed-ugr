#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <vector>

template <typename T>
bool esHoja(const bintree<T> & A, const typename bintree<T>::node &v)
{
	return ( v.left().null() && v.right().null() );
}

template <typename T>
int profundidad(const bintree<T> & A, const typename bintree<T>::node &v)
{
	int prof = 0;
	typename bintree<T>::node aux=v;

	while (aux != A.root()) {
		prof++;
		aux = aux.parent();
	}

	return prof;
}

QuienEsQuien::QuienEsQuien(){
	bintree<Pregunta> nuevo_arbol;
	bintree<Pregunta>::node nuevo_nodo;

	this->arbol = nuevo_arbol;
	this->jugada_actual = nuevo_nodo;
}
QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	this->limpiar();
	personajes = quienEsQuien.getPersonajes();
	atributos = quienEsQuien.getAtributos();
	tablero = quienEsQuien.getTablero();
	arbol = quienEsQuien.getArbol();
	jugada_actual = quienEsQuien.getJugada_actual();
}

QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	this->limpiar();
	personajes = quienEsQuien.getPersonajes();
	atributos = quienEsQuien.getAtributos();
	tablero = quienEsQuien.getTablero();
	arbol = quienEsQuien.getArbol();
	jugada_actual = quienEsQuien.getJugada_actual();

	return *this;
}


QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

vector<string> QuienEsQuien::getPersonajes() const
{
	return personajes;
}

vector<string> QuienEsQuien::getAtributos() const
{
	return atributos;
}

vector<vector<bool>> QuienEsQuien::getTablero() const
{
	return tablero;
}

bintree<Pregunta> QuienEsQuien::getArbol() const
{
	return arbol;
}

bintree<Pregunta>::node QuienEsQuien::getJugada_actual() const
{
	return jugada_actual;
	}

void QuienEsQuien::limpiar(){
	personajes.clear();
	atributos.clear();
	tablero.clear();
	arbol.clear();
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();

  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");

    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}

    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;

	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));

	    		assert(valor == "0" || valor == "1");

	    		bool valor_atributo = valor == "1";

	    		atributos_personaje.push_back(valor_atributo);

	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}

				string nombre_personaje = linea;

	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}

	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada línea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un número a un vector de bool que corresponde
  *        con su representación en binario con un numero de digitos
  *        fijo.
  *
  * @param n Número a convertir en binario.
  * @param digitos Número de dígitos de la representación binaria.
  *
  * @return Vector de booleanos con la representación en binario de @e n
  *      con el número de elementos especificado por @e digitos.

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}

void QuienEsQuien::crear_nodo (vector<int> v, typename bintree<Pregunta>::node &nodo, int profundidad)
{
	vector<int> vector_l, vector_r;

	for (unsigned j = 0; j < v.size(); ++j) {

		if (tablero [v[j]][profundidad] == 1)
      vector_l.push_back (v[j]);

  	else
      vector_r.push_back (v[j]);
    }

	if (vector_l.size() > 1) {
		Pregunta pregunta_l (atributos[profundidad+1], vector_l.size());
		arbol.insert_left (nodo, pregunta_l);
		bintree<Pregunta>::node l = nodo.left();
		crear_nodo (vector_l, l, profundidad+1);
	}

	else if (vector_l.size() > 0){
		int indice = vector_l.front();
		Pregunta pregunta_l (personajes[indice], vector_l.size());
		arbol.insert_left (nodo, pregunta_l);
	}

	if (vector_r.size() > 1) {
		Pregunta pregunta_r (atributos[profundidad+1], vector_r.size());
		arbol.insert_right (nodo, pregunta_r);
		bintree<Pregunta>::node r = nodo.right();
		crear_nodo (vector_r, r, profundidad+1);
	}

	else  if (vector_r.size() > 0){
		int indice = vector_r.front();
		Pregunta pregunta_r (personajes[indice], vector_r.size());
		arbol.insert_right (nodo, pregunta_r);
	}
}

bintree<Pregunta> QuienEsQuien::crear_arbol()
{

	//TODO :D:D

	Pregunta pregunta (atributos[0], personajes.size());
	bintree<Pregunta> arb (pregunta);
	arbol = arb;

	vector<int> vector_l;
	vector<int> vector_r;

	for (int j = 0; j < tablero.size(); ++j) {

		if (tablero [j][0] == 1)
			vector_l.push_back (j);

		else
			vector_r.push_back(j);
	}

	Pregunta pregunta_l (atributos[1], vector_l.size());
	arbol.insert_left (arbol.root(), pregunta_l);
	bintree<Pregunta>::node a_l = arbol.root().left();
	crear_nodo (vector_l, a_l, 1);

	Pregunta pregunta_r (atributos[1], vector_r.size());
	arbol.insert_right (arbol.root(), pregunta_r);
	bintree<Pregunta>::node a_r = arbol.root().right();
	crear_nodo (vector_r, a_r, 1);

	return arbol;
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
	arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
	bool seguir = true;

	while (seguir) {

		jugada_actual = arbol.root();
		char opcion;

		bool existe = true;
		while (!esHoja (arbol, jugada_actual)) {

			int respuesta;
			/////////////
			set<string> personajes_levantados = informacion_jugada (jugada_actual);
			set<string>::iterator it = personajes_levantados.begin();

			cout << "Personajes levantados: " << endl << endl;
			for (it; it != personajes_levantados.end(); ++it)
				cout << *it << endl;

			cout << endl;
			/////////////
			do {
				cout << (*jugada_actual).obtener_pregunta() << "? Si = 1, No = 0" << endl;
				cin >> respuesta;
			}while (respuesta != 0 && respuesta != 1);

		if (respuesta == 1 && !jugada_actual.left().null()) {
				jugada_actual = jugada_actual.left();
			}

			else if (respuesta == 0 && !jugada_actual.right().null())
				jugada_actual = jugada_actual.right();

			else {
				cout << endl << "No existe el personaje con tales atributos " << endl;
				existe = false;
			}

		}

		if (existe)
			cout << "¡Ya lo se! Tu personaje es " << (*jugada_actual).obtener_personaje() << endl;

		do {
			cout << "¿Quieres jugar otra vez? Responde s o n: ";
			cin >> opcion;
		}while (opcion != 's' && opcion != 'n');



		if (opcion == 'n') {
			seguir = false;
		}
	}
}


set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
	set<string> personajes_levantados;

	bintree<Pregunta> sub_arbol;

	sub_arbol.assign_subtree (arbol, jugada_actual);

	bintree<Pregunta>::preorder_iterator pre_it;

	for (pre_it = sub_arbol.begin_preorder(); pre_it != sub_arbol.end_preorder(); ++pre_it) {

		if ((*pre_it).obtener_num_personajes() == 1) {
			string personaje = (*pre_it).obtener_personaje();
			personajes_levantados.insert (personaje);
		}
	}

return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss,
					  const bintree<Pregunta>& a,
		    		  bintree<Pregunta>::node n,
					  string& pre){
	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);
	    }
  	}
}

void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){
	// TODO ^^
	queue<bintree<Pregunta>::node> nodetes;
	bintree<Pregunta> sub_arbol;
	typename bintree<Pregunta>::node n = arbol.root();

	if ( !n.null() ){
		nodetes.push(n);
		while( !nodetes.empty() ){
			n = nodetes.front();
			nodetes.pop();

		//Si tras la raiz hay un hijo erroneo, se coloca al hermano como nueva raiz
		//Si if compuesto con or, no funciona(el programa), separado si
		/*
		if ( n == arbol.root() ){
			if ( ( (*(n.left())).obtener_num_personajes() == 0 ) || ( n.left().null() ) ){
				sub_arbol.assign_subtree (arbol, n.right());
				arbol = sub_arbol;
			}else	if ( ( (*(n.right())).obtener_num_personajes() == 0 ) || ( n.right().null() ) ){
					sub_arbol.assign_subtree (arbol, n.left());
					arbol = sub_arbol;
			}
		}*/

		if ( n == arbol.root() ){
			if ( ( (*(n.left())).obtener_num_personajes() == 0 )  ){
				sub_arbol.assign_subtree (arbol, n.right());
				arbol = sub_arbol;
			}else	if ( ( (*(n.right())).obtener_num_personajes() == 0 ) ){
					sub_arbol.assign_subtree (arbol, n.left());
					arbol = sub_arbol;
			}
			if (n.left().null()){
				sub_arbol.assign_subtree (arbol, n.right());
				arbol = sub_arbol;
			}else if ( n.right().null() ){
					sub_arbol.assign_subtree (arbol, n.right());
					arbol = sub_arbol;
			}
		}
			//Elimina cada nodo redundante al moverse por el arbol
			//Mira cada caso posible tenga un hijo(izq o der) o que no tenga para los que son preguntas
			if ( n != arbol.root()  && !esHoja(arbol, n) ){
				if ( !n.left().null() || !n.right().null() ){
					if ( n.left().null() && !n.right().null() ){
						sub_arbol.assign_subtree (arbol, n.right());
						arbol.replace_subtree(n, sub_arbol, sub_arbol.root());
					}else
						if ( n.right().null() && !n.left().null() ){
							sub_arbol.assign_subtree (arbol, n.left());
							arbol.replace_subtree(n, sub_arbol, sub_arbol.root());
						}

				}


			}



			if ( !n.left().null() )
				nodetes.push(n.left());
			if ( !n.right().null() )
				nodetes.push(n.right());
		}
	}

}

float QuienEsQuien::calcular_profundidad_promedio(const bintree<Pregunta> &a, typename bintree<Pregunta>::node n){
	queue<bintree<Pregunta>::node> nodetes;
	int contador = 0, suma = 0;
	if ( !n.null() ){
		nodetes.push(n);
		while( !nodetes.empty() ){
			n = nodetes.front();
			nodetes.pop();
			if ( (*n).obtener_num_personajes() == 1 ){
				suma += profundidad(a, n);
				++contador;
			}
			if ( !n.left().null() )
				nodetes.push(n.left());
			if ( !n.right().null() )
				nodetes.push(n.right());
		}
	}
	return (float) suma/contador;
}

float QuienEsQuien::profundidad_promedio_hojas(){
	return this->calcular_profundidad_promedio(arbol, arbol.root());
}

/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petición para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atr_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}

//////// Adicionales ////////

void QuienEsQuien::preguntas_formuladas (bintree<Pregunta>::node jugada)
{
	bintree<Pregunta>::node nodo_1 = jugada.parent();
	bintree<Pregunta>::node nodo_2 = jugada;
	set<string> preguntas;

	bool seguir = true;

	while (seguir) {

		if (nodo_2 == nodo_1.left())
			preguntas.insert ((*nodo_1).obtener_pregunta() + " - si");

		else
			preguntas.insert ((*nodo_1).obtener_pregunta() + " - no");

		if (!nodo_1.parent().null()) {
			nodo_2 = nodo_1;
			nodo_1 = nodo_1.parent();
		}

		else
			seguir = false;
	}

	set<string>::iterator it;

	for (it = preguntas.begin(); it != preguntas.end(); ++it)
		cout << *it << endl;

	cout << "pero aun no se cual es." << endl;
}

void QuienEsQuien::aniade_personaje(string nombre,vector<bool> caracteristicas){
	//Creo nodo asociado a raíz del árbol.
	bintree<Pregunta>::node nodo = arbol.root();

	//Mientras que no sea hoja.
	int contador = 0;
	bool nodo_vacio = false;

	while (!esHoja (arbol, nodo) && !nodo_vacio) {

		Pregunta pregunta ((*nodo).obtener_pregunta(), (*nodo).obtener_num_personajes() + 1);
		*nodo = pregunta;

		if (caracteristicas[contador] == 1) {
			if (!nodo.left().null())
				nodo = nodo.left();

			else
				nodo_vacio = true;
		}

		else {
			if (!nodo.right().null())
				nodo = nodo.right();

			else
				nodo_vacio = true;
		}

		++contador;
	}

	if (!nodo_vacio) {
		string personaje = (*nodo).obtener_personaje();
		Pregunta nueva_pregunta (atributos[contador], 2);
		*nodo = nueva_pregunta;

		Pregunta antiguo_personaje (personaje, 1);
		Pregunta nuevo_personaje (nombre, 1);

		if (caracteristicas[contador] == 0) {
			arbol.insert_left (nodo, antiguo_personaje);
			arbol.insert_right (nodo, nuevo_personaje);
		}

		else {
			arbol.insert_left (nodo, nuevo_personaje);
			arbol.insert_right (nodo, antiguo_personaje);
		}
	}

	else {

		Pregunta personaje (nombre, 1);

		if (nodo.left().null())
			arbol.insert_left (nodo, personaje);

		else
			arbol.insert_right (nodo, personaje);
	}

	personajes.push_back (nombre);
	tablero.push_back (caracteristicas);

	cout << endl << "Se ha introducido el nuevo personaje." << endl;

}

void QuienEsQuien::elimina_personaje (string nombre)
{
	unsigned indice = -1;
	for (unsigned i = 0; i < personajes.size(); ++i) {

		if (personajes [i] == nombre)
			indice = i;
	}

	if (indice != -1) {

		vector<bool> caracteristicas = tablero [indice];

		bintree<Pregunta>::node nodo = arbol.root();

		int contador = 0;

		while (!esHoja (arbol, nodo)) {

			Pregunta pregunta ((*nodo).obtener_pregunta(), (*nodo).obtener_num_personajes() - 1);
			*nodo = pregunta;

			if (caracteristicas[contador] == 1)
				nodo = nodo.left();

			else
				nodo = nodo.right();

			++contador;
		}

		bintree<Pregunta> arbol_basura;

		if (caracteristicas[contador-1] == 1)
			arbol.prune_left (nodo.parent(), arbol_basura);

		else
			arbol.prune_right (nodo.parent(), arbol_basura);

		vector<string>::iterator it = personajes.begin();

		while (*it != nombre)
			++it;

		personajes.erase (it);

		vector<vector<bool> >::iterator it_tab = tablero.begin();

		while (*it_tab != caracteristicas)
			++it_tab;

		tablero.erase (it_tab);

		cout << endl << "Se ha eliminado el personaje " << nombre << endl;

	}else
		cout << "El personaje no se encuentra en el arbol" << endl;
}
