#include "Cronologia.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

const int TAM = 500;

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

/***************************************************************************/
/**************************************************************************/

int main(int argc, char * argv[])
{

  if (argc < 4){
      cerr << "\nNumero de argumentos incorrecto." << endl
           << "-> USO: '" << argv[0] << " 'nombre_fichero_cronologia' "
           << "' 'inicio_intervalo' 'fin_intervalo' "
           << "'nombre_fichero_subcronologia (OPCIONAL)'" << endl;
      exit (1);
   }

   // Apertura del archivo con los datos de entrada
   ifstream fi (argv[1]);

   // Si no se puede abrir, se lanza un error y acaba el programa
   if (!fi) {
     cerr << "No puedo abrir el fichero " << argv[1] << endl;

     exit (2);
   }

   Cronologia mi_cronologia;
   Cronologia intervalo;

   int inicio_intervalo = atoi(argv[2]);
   int fin_intervalo = atoi(argv[3]);


   fi >> mi_cronologia; //Cargamos en memoria, en el traductor.

   fi.close();

   intervalo = mi_cronologia.intervalo(inicio_intervalo, fin_intervalo);

   if (argc != 5)
	 		cout << endl << intervalo;

	 else {
		 ofstream fo (argv[4]);

		 fo << endl << intervalo;

		 fo.close();
	 }

   return 0;
}
