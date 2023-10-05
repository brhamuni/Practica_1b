#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VDinamico.h"
#include "Aeropuerto.h"
#include "UTM.h"

int main(int argc, const char * argv[]) {
    clock_t t_ini = clock();

    VDinamico<Aeropuerto> vector;

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;

    std::string id;
    std::string ident;
    std::string tipo;
    std::string nombre;
    std::string latitud_str;
    std::string longitud_str;
    std::string continente;
    std::string iso_pais;

    float latitud, longitud;

    is.open("aeropuertos.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t lectura = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,ident,';');
                getline(columnas,tipo,';');
                getline(columnas,nombre,';');
                getline(columnas,latitud_str,';');
                getline(columnas,longitud_str,';');
                getline(columnas,continente,';');
                getline(columnas,iso_pais,';');

                //  Transformamos la latitud y longitud a float
                latitud=std::stof(latitud_str);
                longitud=std::stof(longitud_str);

                fila="";
                columnas.clear();

                /*std::cout << ++contador
                          << " Aeropuerto: ( ID=" << id
                          << " ident=" << ident << " Tipo=" << tipo << " Nombre=" << nombre
                          << " Posicion=(" << latitud << ", " << longitud << ")"
                          << " Continente=" << continente << " Pais=" << iso_pais
                          << ")" << std::endl;*/


                UTM *utm= new UTM(latitud,longitud);
                Aeropuerto *aeropuerto=new Aeropuerto(id,ident,tipo,nombre,continente,iso_pais,*utm);

                vector.insertar(*aeropuerto);

                delete aeropuerto;
                delete utm;
            }
        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - lectura) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    //Ordena mayor a menor y viceversa
    try {
        clock_t ordena1 = clock();
        std::cout<<"-------------------------------------Ordena 1--------------------------------------"<<std::endl<<std::endl;

        //Ordenar de menor a mayor
        vector.ordena();
        //Mostramos por pantalla los primeros o ultimos 30 aeropuertos
        std::cout << "Vector ordenado de menor a mayor: " << std::endl;
        for (int i = 1; i < 30; ++i) {
            std::cout << "Nombre: " + vector[i].getNombre() + " Id: " + vector[i].getId() + "\n" << std::endl;
        }
        std::cout << "Tiempo ordena1: " << ((clock() - ordena1) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

        clock_t ordena2 = clock();
        std::cout<<"-------------------------------------Ordena 2--------------------------------------"<<std::endl<<std::endl;


        //Ordenar de mayor a menor
        vector.ordenaRev();
        //Mostramos por pantalla los primeros o ultimos 30 aeropuertos
        std::cout << "Vector ordenado de mayor a menor: " << std::endl;

        for (int i = 1; i < 30; ++i) {
            std::cout << "Nombre: " <<vector[i].getNombre() << " Id: " << vector[i].getId() <<std::endl << std::endl;
        }

        std::cout << "Tiempo ordena2: " << ((clock() - ordena2) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


        //Buscar si estan los siguientes id's

        clock_t bus = clock();

        VDinamico<Aeropuerto> busquedaPorID(5);
        Aeropuerto* aux = new Aeropuerto[1];
        for (int i = 0; i < 5; ++i) {
            busquedaPorID.insertar(*aux);
        }

        busquedaPorID[0].setId("345166");
        busquedaPorID[1].setId("6640");
        busquedaPorID[2].setId("6676");
        busquedaPorID[3].setId("345364");
        busquedaPorID[4].setId("6778");

        vector.ordena();

        std::cout<<std::endl<<"-------------------------------------Busqueda Binaria/Dicotomica--------------------------------------"<<std::endl<<std::endl;
        for (int j = 0; j < 5; ++j) {
            int pos = vector.busquedaBin(busquedaPorID[j]);
            if (pos != -1) {
                std::cout << "El aeropuerto con id: " << busquedaPorID[j].getId()<< " ha sido encontrado en la poscicion: " << pos << std::endl;
            } else
                std::cout << "El aeropuerto con id: " << busquedaPorID[j].getId() << " no ha sido encontrado"<< std::endl;
        }


        std::cout << "Tiempo busquedaBin: " << ((clock() - bus) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

        //quitar los aeropuertos que tengan "NA" como continente
        clock_t elimina = clock();
        VDinamico<Aeropuerto> vectorNA;

        int i = 0;
        while (i < vector.Tamlog()) {
            //Bucle para poder borrar todos los "NA" que esten seguidos
            while (vector[i].getContinente() == "NA") {
                //Inserta en el nuevo vector los aeropuertos que no tienen continente
                vectorNA.insertar(vector[i]);
                vector.borrar(i);
            }
            i++;
        }

        std::cout<<std::endl<<"-------------------------------------Elimina NA's--------------------------------------"<<std::endl<<std::endl;
        std::cout<<"El vector con continentes tiene "<<vector.Tamlog()<<" elementos"<<std::endl;
        std::cout<<"El vector sin continentes tiene "<<vectorNA.Tamlog()<<" elementos"<<std::endl;
        std::cout<<"Los 20 primeros aeropuertos del vector sin continente son: "<<std::endl;

        for (int j = 0; j < 20; ++j) {
            std::cout<<"Aeropuerto: "<<vectorNA[j].getNombre()<<std::endl;
        }

        std::cout << "Tiempo elimina e inserta: " << ((clock() - elimina) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    }catch (std::out_of_range &e) {
        std::cerr<<e.what();
    }catch (std::bad_alloc &e){
        std::cerr<<e.what();
    } catch (std::invalid_argument &e) {
        std::cerr<<e.what();
    }

    std::cout << "Tiempo total del programa: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    return 0;
}
