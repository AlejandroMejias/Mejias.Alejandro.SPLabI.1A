#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "auxiliares.h"


/** \brief Se encarga de mostrar el menu de opciones
*
* \return Caracter introducido por el usuario
*
*/

char menu()
{
    char opcion;

    printf("        ****       Lista de pandemia        *****");
    printf("\n     ----------------------------------------------\n\n");
    printf("A)Cargar los datos al archivo\nB)Imprimir lista\nC)Asignar tiempo\nD)Filtrar por tipo\nE)Mostrar posiciones ordenadas\nF)Guardar posiciones\nX)Salir del sistema\n\n");
    printf("Ingrese su accion a ejecutar: ");

    opcion = tolower(getchar());
    fflush(stdin);
    opcion = validarCaracter(opcion);

    return opcion;
}
/** \brief Se encarga de validar un caracter
*
* \param Caracter a validar
* \return Caracter validado
*
*/
char validarCaracter(char caracter)
{

    while(caracter < 97 || caracter > 122 )
    {
        printf("\nERROR! Ingresa una opcion correcta: ");
        fflush(stdin);
        caracter = tolower(getchar());
    }
    return caracter;
}
