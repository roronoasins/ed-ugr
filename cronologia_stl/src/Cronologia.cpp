#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

#include "Cronologia.h"
#include "FechaHistorica.h"

using namespace std;

/**************************************************/
Cronologia::Cronologia () {}

Cronologia::Cronologia (MapaFH fechas) {
		crono = fechas;
}

Cronologia::Cronologia (const Cronologia & otro) {
	crono = otro.getCrono();
}

Cronologia::~Cronologia () {
	crono.clear();
}

MapaFH Cronologia::getCrono() const {
	return crono;
}

void Cronologia::setCrono (const Cronologia crono) {
	*this += crono;
}

set<string> Cronologia::acontecimientos (int anio) {
	FechaHistorica f = this->getEventos(anio);
	set<string> acontecimientos;
	if ( f.getAnio() == anio )
		 acontecimientos = crono[anio].getAcontecimientos();
	else cout << "No hay años registrados en " << anio << "." << endl;

	return acontecimientos;
}

FechaHistorica Cronologia::getEventos ( int anio ) {
	FechaHistorica eventos = crono[anio];
	return eventos;
}

void Cronologia :: AniadeFecha (const FechaHistorica & f) {
	crono.insert(MapaFH::value_type(f.getAnio(), f));
}

string Cronologia::acontecimientoconcreto (int anio, int contador) {
	FechaHistorica f = this->getEventos(anio);
	string acontecimientos;
	if ( f.getAnio() == anio )
		 acontecimientos = crono[anio].getAcontecimientoConcreto(contador);
	else
		cout << "No hay años registrados en " << anio << "." << endl;

	return acontecimientos;
}

Cronologia & Cronologia::operator= (const Cronologia & otro) {
	crono.clear();
	crono = otro.getCrono();

	return (*this);
}

Cronologia Cronologia ::  operator + (const MapaFH & otro) {
	Cronologia cronologia = *this;

	cronologia += otro;

	return cronologia;
}

Cronologia Cronologia :: operator + (const FechaHistorica & otro) {
	Cronologia resultado = *this;

	resultado.AniadeFecha (otro);

	return resultado;
}

Cronologia & Cronologia :: operator += (const FechaHistorica & otro) {
	AniadeFecha (otro);

	return (*this);
}

Cronologia & Cronologia :: operator += (const Cronologia & otro) {
	Cronologia::const_iterator it = otro.cbegin();
	Cronologia::iterator it_this;

	for (; it != otro.cend(); ++it) {
		FechaHistorica f = it->second;
		it_this = crono.find (f.getAnio());

		if (it_this != this->end())
			it_this->second.setAcontecimientos (f.getAcontecimientos());

		else
			crono.insert(MapaFH::value_type (it->first, it->second));
	}

return (*this);
}

 Cronologia::iterator Cronologia::begin () {

	return crono.begin();


}

Cronologia::iterator Cronologia::end () {

	return	crono.end();


}

Cronologia::const_iterator Cronologia::cbegin () const{

	return crono.begin();


}

Cronologia::const_iterator Cronologia::cend () const{

	return crono.end();



}

Cronologia Cronologia::intervalo (int inicio, int fin ) {
    MapaFH sub_c;

    MapaFH::iterator it = crono.begin();

    while ( (it->first < inicio) && (it != crono.end() ) )
        ++it;

    if (it != crono.end())
        for ( ; (it->first <= fin) && (it !=crono.end()); ++it )
                sub_c[it->first] = it->second;


        if ( sub_c.empty() ) {
            cout << "No hay ninguna fecha dentro del intervalo: [" << inicio
                 << ", " << fin << "] en la cronologia" << endl;
        }

			Cronologia sub_crono(sub_c);

        return sub_crono;
}


void Cronologia::Union(const Cronologia & c1, const Cronologia & c2){
	Cronologia union_ = c1;
	union_ += c2;
	*this = union_;
}

MapaFH Cronologia::PalabraClave (string buscar) {

    MapaFH recopilatorio;

    if (buscar != "") {
        Cronologia :: iterator it_crono;
        FechaHistorica :: iterator it_fecha;
        bool encontrado = false;
		bool iguales = false;

		int contador = 1;

        for (it_crono = crono.begin(); it_crono != crono.end(); ++it_crono) {
            FechaHistorica fecha = it_crono->second;

            contador = 1;

            for (it_fecha = fecha.begin(); it_fecha != fecha.end(); ++it_fecha) {
                string evento = *it_fecha;


                encontrado = false;

				for (int i = 0; evento[i] != '\0' && !encontrado; ++i) {
                    if (tolower(buscar[0]) == tolower(evento[i])) {
                         iguales = true;



                        for (int j = 1; buscar[j] != '\0' && iguales; ++j){
                            if (tolower(buscar[j]) != tolower(evento[++i]))
                                iguales = false;


                        }
                    }

						if (iguales) {
							FechaHistorica fecha_valida(fecha.getAnio(), acontecimientoconcreto(fecha.getAnio(), contador));
		                    encontrado = true;
		                    recopilatorio[it_crono->first] = fecha_valida;
		                    iguales = false;
                    }
                }

                contador ++;
            }
        }
    } else
        cerr << "\nNo hay evento que buscar" << endl;

    if (recopilatorio.empty())
        cerr << "\nNo se han encontrado acontecimientos" << endl;

    return recopilatorio;
}
