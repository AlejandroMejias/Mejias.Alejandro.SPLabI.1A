#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.h"
#include "bicicletas.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los bicicletas desde el archivo bicicletas.csv (modo texto).
 *
 * \param Puntero File
 * \param pListaBicicletas LinkedList*
 * \return int  1 si se ejecutó correctamente, 0 si error
 *
 */
int parsear_BicicletaDesdeTexto(FILE* pArchivo, LinkedList* pListaBicicletas)
{
    int retorno = 0;
    char buffer[4][30];
    int respuesta;
    eBicicleta* auxBicicleta = NULL;

    if( pArchivo != NULL && pListaBicicletas != NULL)
    {
        //fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

        while( !feof(pArchivo))
        {
            respuesta = fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            if( respuesta == 4)
            {
                auxBicicleta = bicicleta_nuevaParam(buffer[0], buffer[1], buffer[2], buffer[3]);

                if(auxBicicleta != NULL)
                {
                    ll_add(pListaBicicletas, auxBicicleta);
                    retorno = 1;
                }
            }
            else
            {
                break;
            }
        }
    }

    return retorno;
}
