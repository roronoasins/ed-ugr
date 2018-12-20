#include "Cronologia.h"
#include <fstream>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <climits>
#include <cstring>

using namespace std;

const int TAM = 2000;

ostream& operator<<(ostream &os, const FechaHistorica &f){
  os << f.getAnio();
  set<string> a = f.getAcontecimientos();
  set<string>::iterator i = a.begin();

  for (; i != a.end(); i++){
    os << "#";
    os << *i;
  }
  return os;
}

istream& operator>>(istream &is, FechaHistorica &f) {
	char cad [TAM];

	is.get(cad, TAM, '#');
	int anio = atoi(cad);

	set<string> fecha;
  char * p;

	is.get(cad,TAM,'\n');

	string cadena (cad);
    p = strtok (cad,"#\n");
    while (p != NULL) {
      fecha.insert(p);
      p = strtok (NULL, "#\n");
    }


	f.setAnio(anio);
	f.setAcontecimientos (fecha);

  return is;
}

ostream& operator<< (ostream &os, const Cronologia & crono) {
	MapaFH fechas = crono.getCrono();

	MapaFH::iterator it_cr;

	for ( it_cr = fechas.begin(); it_cr != fechas.end(); ++it_cr)
		os << it_cr->second << endl << endl;

  return (os);
}

istream& operator>> (istream &is, Cronologia & crono) {
	MapaFH fechas;

	while (!is.eof()) {
    FechaHistorica fecha;

		is >> fecha;

    fechas[fecha.getAnio()] = fecha;

	}
	crono = fechas;

  return (is);
}

int main(int argc, char * argv[]){

  if (argc!=2){
      cout<<"Dime el nombre del fichero con la cronologia"<<endl;
      return 0;
   }

   ifstream f (argv[1]);
   if (!f){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }

   Cronologia mi_cronologia;
   f >> mi_cronologia; //Cargamos en memoria, en el traductor.
   cout << mi_cronologia;

   int anio;
   cout<<"Dime un año a consultar:";
   cin >> anio;

   FechaHistorica eventos;
   eventos = mi_cronologia.getEventos(anio);  //Asumimos que Cronologia::GetEventos() devuelve objeto de clase FechaHistorica
   cout << "Eventos consultados: \n" << eventos << endl << endl;

   // Recorremos con iterador los acontecimientos para mostrarlos por pantalla
   // Este proceso requiere la definición de un tipo iterator // const_iterator en FechaHistorica
   // Y la definición de los métodos begin() y end() en FechaHistorica
   FechaHistorica::const_iterator it;
   cout << "Prueba de iterator: \n" << anio << ":";              //Imprimimos el anio
   for (it=eventos.begin(); it!=eventos.end();++it)
     cout<<(*it)<<'#';
   cout<<endl;





}
