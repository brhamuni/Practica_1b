#include "UTM.h"

UTM::UTM(const float &latitud,const  float &longitud): latitud(latitud),longitud(longitud) {

}
float UTM::getLatitud() const {
    return latitud;
}

void UTM::setLatitud(float latitud) {
    UTM::latitud = latitud;
}

float UTM::getLongitud() const {
    return longitud;
}

void UTM::setLongitud(float longitud) {
    UTM::longitud = longitud;
}

UTM::~UTM() {

}
