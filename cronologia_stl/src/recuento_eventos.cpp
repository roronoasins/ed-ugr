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

void recuentoEventos( const Cronologia & c ){
  Cronologia::const_iterator it_cr = c.cbegin();
  int n_acontecimientos = 0, maximo = 0;
  for ( ; it_cr != c.cend(); ++it_cr){
    int n = it_cr->second.getAcontecimientos().size();
   n_acontecimientos += n;
   maximo =  n > maximo ? n : maximo;
 }

 int n_anios = c.getCrono().size();
 double promedio_anual = (double) n_acontecimientos / c.getCrono().size();

  cout << "Numero total de anios: " <<  n_anios << endl
       << "Numero total de acontecimientos: " << n_acontecimientos << endl
       << "Maximo numero de acontecimientos en un solo año: " << maximo << endl
       << "Promedio de los acontecimientos por año: " << promedio_anual << endl;
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
   f >> mi_cronologia;

   recuentoEventos(mi_cronologia);

   }
