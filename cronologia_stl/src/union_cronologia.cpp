#include "Cronologia.h"
#include <fstream>
#include <iostream>
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

  if (argc!=3 && argc!=4){
      cout<<"Error: debe dar al menos los nombres de dos ficheros con cronologías. "<<endl;
      cout<<"[Opcional]: un tercer nombre de fichero para guardar la cronología resultante."<<endl;
      return 0;
   }

   ifstream f1 (argv[1]);
   if (!f1){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }
   ifstream f2 (argv[2]);
   if (!f2){
    cout<<"No puedo abrir el fichero "<<argv[2]<<endl;
    return 0;
   }

   Cronologia c1, c2, cUnion;
   f1 >> c1;    // Cargamos los datos de los ficheros en las cronologías.
   f2 >> c2;

   cUnion.Union(c1, c2);

   if (argc==3)   //No se dio fichero de salida, imprimimos en cout
      cout << "Union de las cronologias: \n" << cUnion << endl;
   else{
     ofstream fout(argv[3]);
     if (!fout){
      cout<<"No puedo crear el fichero "<<argv[3]<<endl;
      return 0;
     }
    fout << cUnion;

  }
}
