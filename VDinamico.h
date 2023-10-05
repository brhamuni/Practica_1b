#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <climits>
#include <cmath>
#include "Aeropuerto.h"
#include "UTM.h"


#ifndef PRACTICA_1_VDINAMICO_H
#define PRACTICA_1_VDINAMICO_H

template<typename T>
class VDinamico {
private:
    T *vector;
    unsigned long int tamlog;
    unsigned long int tamfis ;
public:
    unsigned long getTamfis() const {
        return tamfis;
    }

public:
    VDinamico();
    VDinamico(unsigned long int n);
    VDinamico(const VDinamico<T> &orig);
    VDinamico (const VDinamico &orig, unsigned int posicionInicial, unsigned int numElementos);
    T &operator[](unsigned long int pos);
    virtual ~VDinamico();
    VDinamico<T> &operator=(VDinamico &orig);
    void ordenaRev();
    void ordena();
    void insertar(const T& dato, unsigned long int pos = UINT_MAX);
    T borrar(unsigned int pos = UINT_MAX);
    int busquedaBin(const T& dato);
    unsigned int Tamlog() const;

};

template<class T>
VDinamico<T>::VDinamico():tamfis(1),tamlog(0) {
    vector = new T [tamfis];
}

template<class T>
int VDinamico<T>::busquedaBin(const T &dato) {
    //Antes de realizar esto el vector deberia estar ordenado
    //Inicializamos una posicion inferior
    int inf= 0;
    //Incializamos la posicion superior
    int sup = tamlog -1 ;
    //Variable para la busqueda de la posicion
    int curIn;
    //Mientras la posicion
    while(inf <= sup){
        //Reducimos el vector para la busqueda
        curIn = (inf + sup)/2;
        //Si el vector tiene el dato pues devolvemos el partido
        if(vector[curIn] == dato)
            return  curIn;
            //Si el datos es menor que la posicion del vector
        else if (vector[curIn] < dato) inf = curIn + 1 ;
        else sup = curIn - 1 ;

    }
    //En caso de que no se realice la busqueda del dato dentro del vector devolvemos el fallo
    return -1;
}

template<class T>
unsigned int VDinamico<T>::Tamlog() const {
    return tamlog;
}

template<class T>
T VDinamico<T>::borrar(unsigned int pos) {

    if(tamlog*3<tamfis) {
        tamfis= tamfis / 2;
        T *vaux = new T[tamfis];
        for (int long i = 0; i < tamlog; i++) {
            vaux[i] = vector[i];
        };
        delete[] vector;
        vector = vaux;
    }

    if(pos==UINT_MAX){
        return vector[--tamlog];
    }else{
        if(pos>tamlog)
            throw std::out_of_range ("borrar :: La posicion no puede ser mayor que el numero de elementos del vector");

        for(int long i=pos;i<tamlog-1;i++){
            vector[i]=vector[i+1];
        }
        tamlog--;
    };
    return vector[tamlog];
}

template<class T>
void VDinamico<T>::insertar(const T& dato, unsigned long int pos){

    if(tamlog==tamfis) {
        T *vaux= new T[tamfis=tamfis*2];
        for(int i=0;i<tamlog;i++)
            vaux[i]=vector[i];
        delete[] vector;
        vector=vaux;
    }

    if(pos==UINT_MAX){
        vector[tamlog++]=dato;
    }else{
        if(pos<0)
            throw std::out_of_range ("insertar :: La posicion no puede ser mayor que el numero de elementos del vector");

        if(tamlog!=0) {
            tamlog++;
            for (int i = tamlog - 1; i > pos +1; i--) {
                vector[i] = vector[i - 1];
            }
            vector[pos] = dato;
        }
    }

}

/**
 * @brief Ordena el vector de menor a mayor con la funcion sort
 * @tparam T
 */

template <class T>
void VDinamico<T>::ordena(){
    std::sort(vector, vector+tamlog);
}

/**
 * @brief Ordena el vector de mayor a menor
 * @tparam T
 * @param aux Variable auxiliar que nos ayuda a hacer la permutacion en el vector
 */

template <class T>
void VDinamico<T>::ordenaRev(){
    std::sort(vector,vector+tamlog);
    T aux;
    for (int i = 0; i < tamlog/2 ; ++i) {
        aux = vector[i];
        vector[i]=vector[tamlog-i-1];
        vector[tamlog-i-1]=aux;
    }
}

/**
 * @brief Constructor de copia parcial
 * @tparam T
 * @param origen Direccion de memoria del vector que vamos a copiar
 * @param posicioninicial   Posicion inicial del vector dinamico
 * @param numElementos      Le pasamos el numero de elementos que va a tener nuestro nuevo vector
 */

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig, unsigned int posicionInicial, unsigned int numElementos) {
    if(posicionInicial>numElementos)
        throw std::out_of_range("La posicion inicial no puede ser mayor que el numero de elementos");

    delete [] vector;
    vector = new T [tamlog=numElementos] ;

    /*Para asegurarnos que es una potencia de dos calculamos el logaritmo en base 2 de orig.tamfis
    y hacemos %1 para sacar el resto y saber si es un entero, si asi fuera significa que es potencia de dos*/
    tamfis=orig.tamfis;

    if (log2(tamfis) == round(log2(tamfis)))
        tamfis++;
    while (log2(tamfis) != round(log2(tamfis))){
        tamfis++;
    }

    for(int i=0;i<tamlog;i++){
        vector[i]=orig.vector[posicionInicial+i];
    }
}

/**
 * @brief Operator igual para copiar la informacion de un vector en otro
 * @tparam T
 * @param orig vector del cual vamos a copiar las cosas
 * @return puntero con el nuevo vector
 */

template<class T>
VDinamico<T> &VDinamico<T>::operator=(VDinamico<T> &orig) {
    if (this!=&orig){
        delete [] vector;
        tamlog=orig.tam;
        if (log2(tamfis) == round(log2(tamfis)))
            tamfis++;
        while (log2(tamfis) != round(log2(tamfis))){
            tamfis++;
        }
    }else{
        if(tamfis==tamlog){
            tamfis=tamfis*2;
        }else
            tamfis=orig.tamfis;
    }


    delete [] vector;
    vector =new T [tamlog];
    for (int i=0;i<orig.tam;i++){
        vector[i]=orig.vector[i];
    }

    return *this;

}

/**
 * @brief Constructor parametrizado
 * @tparam T tipo de elemento
 * @param n tam del vector
 */

template<class T>
VDinamico<T>::VDinamico(unsigned long int n) {
    tamfis=n;
    vector = new T [tamfis];
}

/**
 * @brief Operator[] devuelve el contenido de la posicion del vector que se indica
 * @tparam T
 * @param pos Parametro en el que le pasamos la posicion que queremos de dicho vector
 * @return
 */

template<class T>
T &VDinamico<T>::operator[](unsigned long pos){
    if(pos>tamlog) {
        throw std::out_of_range("Operator[]::La posicion del vector no puede ser mayor que el tamaño");
    }
    return vector[pos];
}

/**
 * @brief Destructor del vector dinamico
 * @tparam T
 */

template<class T>
VDinamico<T>::~VDinamico(){
    delete [] vector;
}

/**
 * @brief Constructor copia
 * @tparam T
 * @param origen Direccion de memoria del vector que vamos a copiar
 */
template<class T>

VDinamico<T>::VDinamico(const VDinamico<T> &orig) {
    tamlog=orig.tamlog;
    tamfis=orig.tamfis;
    vector = new T[tamfis = orig.tamfis];
    for (long int i=0; i<tamlog; i++)
        vector[i] = orig.v[i];
}




#endif //PRACTICA_1_VDINAMICO_H
