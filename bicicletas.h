#ifndef BICICLETAS_H_INCLUDED
#define BICICLETAS_H_INCLUDED

typedef struct
{
    int id;
    char nombre[50];
    char tipo[50];
    int tiempo;

}eBicicleta;

eBicicleta* nueva_bicicleta();
eBicicleta* bicicleta_nuevaParam(char* idStr, char* nombreStr, char* tipoStr,char* tiempoStr);
int imprimirBicicleta(eBicicleta* this);

//ID
int bicicleta_setId(eBicicleta* this, int id);
int bicicleta_getId(eBicicleta* this, int* id);

//NOMBRE
int bicicleta_setNombre(eBicicleta* this, char* nombre);
int bicicleta_getNombre(eBicicleta* this, char* nombre);

//TIPO
int bicicleta_setTipo(eBicicleta* this, char* tipo);
int bicicleta_getTipo(eBicicleta* this, char* tipo);

// TIEMPO

int bicicleta_setTiempo(eBicicleta* this, int tiempo);
int bicicleta_getTiempo(eBicicleta* this, int* tiempo);
void* asignarEstadisticas(void* pais);
int getAleatorioTiempo();
int filtrarTipo(void* tipo,char* Str);
int sort_Tiempo_Tipo(void* tipo1, void* tipo2);
#endif // BICICLETAS_H_INCLUDED
