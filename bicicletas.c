#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "LinkedList.h"
#include "bicicletas.h"
#include "controller.h"


/** \brief Guarda una estructura Bicicleta inicializada y devuelve un puntero a dicha estructura
 *
 * \param
 * \param
 * \return Bicicleta* puntero a la estructura inicializada
 *
 */

eBicicleta* nueva_bicicleta()
{
    eBicicleta* nuevaBicicleta = (eBicicleta*) malloc(sizeof(eBicicleta));
    if(nuevaBicicleta != NULL)
    {
        nuevaBicicleta->id = 0;
        strcpy(nuevaBicicleta->nombre, " ");
        strcpy(nuevaBicicleta->tipo, " ");
        nuevaBicicleta->tiempo = 0;
    }
    return nuevaBicicleta;
}

/** \brief Recibe como string el id, el nombre, el tipo y el tiempo.
 *
 * \param char* idStr
 * \param char* nombreStr
 * \param char* tipoStr
 * \param char* tiempoStr
 * \return eBicicleta* nuevo bicicleta
 *
 */

eBicicleta* bicicleta_nuevaParam(char* idStr, char* nombreStr, char* tipoStr,char* tiempoStr)
{
    eBicicleta* nuevaBicicleta = nueva_bicicleta();
    if( nuevaBicicleta != NULL)
    {
        if(!(bicicleta_setId(nuevaBicicleta, atoi(idStr))
                && bicicleta_setNombre(nuevaBicicleta, nombreStr)
                && bicicleta_setTipo(nuevaBicicleta, tipoStr)
                && bicicleta_setTiempo(nuevaBicicleta,atoi(tiempoStr))))
        {
            nuevaBicicleta = NULL;
        }
    }

    return nuevaBicicleta;
}
/** \brief Muestra los datos de una bicicleta
 *
 * \param eBicicleta*
 * \param
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int imprimirBicicleta(eBicicleta* this)
{
    int retorno = 0;

    if(this != NULL)
    {
        printf("%4d  %20s   %20s  %7d    \n", this->id, this->nombre, this->tipo, this->tiempo);
        retorno = 1;
    }
    return retorno;

}
/** \brief Asigna el id a la bicicleta
 *
 * \param eBicicleta*
 * \param int
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */
int bicicleta_setId(eBicicleta* this, int id)
{
    int retorno = 0;

    if(this != NULL && id > 0)
    {
        this->id = id;
        retorno = 1;
    }
    return retorno;
}
/** \brief Obtiene el id de la bicicleta
 *
 * \param eBicicleta*
 * \param int
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_getId(eBicicleta* this, int* id)
{
    int retorno = 0;

    if( this != NULL && id != NULL)
    {
        *id = this->id;
        retorno = 1;
    }

    return retorno;
}
/** \brief Asigna el nombre a la bicicleta
 *
 * \param eBicicleta*
 * \param char*
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_setNombre(eBicicleta* this, char* nombre)
{
    int retorno = 0;
    if(this != NULL && nombre != NULL && strlen(nombre) < 50)
    {
        strcpy(this->nombre, nombre);
        retorno = 1;
    }
    return retorno;
}
/** \brief Obtiene el nombre de la bicicleta
 *
 * \param eBicicleta*
 * \param char*
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_getNombre(eBicicleta* this, char* nombre)
{
    int retorno = 0;

    if( this != NULL )
    {
        strcpy(nombre, this->nombre);
        retorno = 1;
    }
    return retorno;
}

/** \brief Asigna el tipo de bicicleta
 *
 * \param eBicicleta*
 * \param char*
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_setTipo(eBicicleta* this, char* tipo)
{
    int retorno = 0;
    if(this != NULL && tipo != NULL && strlen(tipo) < 50)
    {
        strcpy(this->tipo, tipo);
        retorno = 1;
    }
    return retorno;
}
/** \brief Obtiene el tipo de bicicleta
 *
 * \param eBicicleta*
 * \param char*
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_getTipo(eBicicleta* this, char* tipo)
{
    int retorno = 0;

    if( this != NULL)
    {
        strcpy(tipo, this->tipo);
        retorno = 1;
    }
    return retorno;
}

/** \brief Asigna el tiempo a la bicicleta
 *
 * \param eBicicleta*
 * \param int
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_setTiempo(eBicicleta* this, int tiempo)
{
    int retorno = 0;

    if( this != NULL && tiempo > -1)
    {
        this->tiempo = tiempo;
        retorno = 1;
    }
    return retorno;
}
/** \brief Obtiene el tiempo a la bicicleta
 *
 * \param eBicicleta*
 * \param int
 * \return int 1 si se ejecutó correctamente, 0 si error.
 *
 */

int bicicleta_getTiempo(eBicicleta* this, int* tiempo)
{
    int retorno = 0;

    if(this != NULL)
    {
        *tiempo = this->tiempo;
        retorno = 1;
    }

    return retorno;
}
/** \brief Asigna los tiempos a cada bicicleta
 *
 * \param Puntero generico void
 * \return Estructura bicicleta cargada con los tiempos
 *
 */

void* asignarEstadisticas(void* bicicleta)
{
    eBicicleta* auxBicicleta = NULL;

    if(bicicleta != NULL)
    {
        auxBicicleta = (eBicicleta*)bicicleta;

        bicicleta_setTiempo(auxBicicleta,getAleatorioTiempo());
    }

    return auxBicicleta;
}
/** \brief Se encarga de calcular de manera aleatoria el tiempo de las bicicletas
 *
 * \return tiempo
 *
 */

int getAleatorioTiempo()
{
    int random;

    random = 50 + rand()%(120 - 50);
    return random;
}

/** \brief Permite filtrar por tipo
 *
 * \param Puntero generico void que contiene la estructura
 * \param  tipo de bicicleta
 * \return 0 si todo esta ok, -1 si no pudo encontrar el tipo
 *
 */

int filtrarTipo(void* tipo,char* Str)
{
    int retorno = -1;

    eBicicleta* auxBicicleta;

    if(tipo != NULL)
    {
        auxBicicleta = (eBicicleta*)tipo;

        if(strcmp(auxBicicleta->tipo, Str) == 0)
        {
            retorno = 0;
        }
    }
    return retorno;
}
/** \brief Se encarga de ordenar por tiempo y tipo
 *
 * \param Puntero generico void que contiene la estructura uno
 * \param Puntero generico void que contiene la estructura dos
 * \return 0 si son iguales
 *         1 si la primera es mayor a la segunda
 *         -1 si la primera es menor a la segunda
 *
 */

int sort_Tiempo_Tipo(void* tipoUno, void* tipoDos)
{
    int retorno;
    int aux;

    eBicicleta* auxTipoUno ;
    eBicicleta* auxTipoDos;

    if(tipoUno != NULL && tipoDos != NULL)
    {
        auxTipoUno = (eBicicleta*)tipoUno;
        auxTipoDos = (eBicicleta*)tipoDos;

        // Tomo el resultado de la comparacion
        aux = strcmp(auxTipoUno->tipo,auxTipoDos ->tipo);

        if(aux == 0 && auxTipoUno->tiempo > auxTipoDos->tiempo)
        {
            retorno = 1;
        }
        else if(aux == 0 && auxTipoUno->tiempo < auxTipoDos->tiempo)
        {
            retorno = - 1;
        }
        else
        {
            retorno = aux;
        }
    }

    return retorno;
}
