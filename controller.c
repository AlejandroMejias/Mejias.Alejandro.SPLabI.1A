#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "auxiliares.h"
#include "controller.h"
#include "bicicletas.h"
#include "parser.h"



/** \brief Carga los datos de los bicicletas desde el archivo bicicletas.csv (modo texto).
 *
 * \param path char*
 * \param pListaBicicletas LinkedList*
 * \return int 1 si se ejecutó correctamente, 0 si error
 *
 */
int controlador_cargarDesdeTexto(char* path, LinkedList* pListaBicicletas)
{
    int retorno = 0;
    FILE* pArchivo;

    system("cls");

    if(path != NULL && pListaBicicletas != NULL)
    {
        pArchivo = fopen(path, "r");

        if(pArchivo != NULL)
        {
            if(parsear_BicicletaDesdeTexto(pArchivo,pListaBicicletas))
            {
                retorno = 1;
            }
            fclose(pArchivo);
        }
    }

    if(retorno == 1)
    {
        system("cls");
        printf("\n\nDatos guardados en data.csv exitosamente...\n\n\n");
    }
    else
    {
        system("cls");
        printf("\n\nNo se pudo guardar los datos en data.csv...\n\n\n");
    }

    system("pause");

    return retorno;
}
/** \brief Listar bicicletas
 *
 * \param pListaBicicletas LinkedList*
 * \return int  1 si se ejecutó correctamente, 0 si error
 *
 */
int controlador_listarBicicletas(LinkedList* pListaBicicletas)
{
    int retorno = 0;
    int i;
    int tam = ll_len(pListaBicicletas);
    eBicicleta* auxBicicleta = NULL;


    if(pListaBicicletas != NULL && tam > 0)
    {
        system("cls");
        printf("  ID              NOMBRE                   TIPO     TIEMPO\n");
        printf("---------------------------------------------------------------\n\n");
        for(i = 0; i < tam; i++)
        {
            auxBicicleta = (eBicicleta*)ll_get(pListaBicicletas,i);
            if(auxBicicleta != NULL)
            {
                imprimirBicicleta(auxBicicleta);

            }
        }
        retorno = 1;
    }
    else
    {
        system("cls");
        printf("\nNo se encontraron bicicletas en la lista,debes cargarlos primero...\n");
    }
    printf("\n\n");
    system("pause");
    return retorno;
}

/** \brief Asigna los tiempos de manera aleatoria
 *
 * \param pListaBicicletas
 * \return 0 si todo esta ok, -1 si no pudo asignar los tiempos
 *
 */

int controller_asignarTiempos(LinkedList* pListaBicicletas)
{
    int retorno = -1;
    LinkedList* nuevaLista = NULL;

    if(pListaBicicletas != NULL && !ll_isEmpty(pListaBicicletas))
    {
        nuevaLista = ll_newLinkedList();

        if(nuevaLista != NULL)
        {
            nuevaLista = ll_map(pListaBicicletas,asignarEstadisticas);

            if(nuevaLista != NULL)
            {
                system("cls");
                printf("\nSe asignaron los tiempos correctamente...\n\n");
                system("pause");
                ll_deleteLinkedList(nuevaLista);
                retorno = 0;
            }
        }
    }

    if(retorno == -1)
    {
        system("cls");
        printf("\nNo fue posible asignar los tiempos, cargue un archivo si aun no lo hizo...\n\n");
        system("pause");
    }

    return retorno;
}

/** \brief Se encarga de filtrar la lista por tipo
 *
 * \param Path donde se guarda la lista filtrada
 * \param pListaBicicletas
 * \return 0 si pudo crear la lista, -1 si no pudo, 1 para indicar que la opcion elegida no es correcta
 *
 */

int controller_filtrarTipo(char* path, LinkedList* pListaBicicletas)
{
    int retorno = -1;
    char opcion;
    char tipo[50];

    LinkedList* ListaFiltrada = ll_newLinkedList();

    if(pListaBicicletas != NULL && !ll_isEmpty(pListaBicicletas))
    {
        system("cls");

        printf("\nElija el tipo de bicicleta a filtrar:\n\nA)BMX\nB)PLAYERA\nc)MTB\nd)PASEO\n\n");
        printf("Ingrese su opcion: ");
        fflush(stdin);
        opcion = tolower(getchar());


        switch(opcion)
        {
        case 'a':
            strcpy(tipo,"BMX");
            retorno = 0;
            break;
        case 'b':
            strcpy(tipo,"PLAYERA");
            retorno = 0;
            break;
        case 'c':
            strcpy(tipo,"MTB");
            retorno = 0;
            break;
        case 'd':
            strcpy(tipo,"PASEO");
            retorno = 0;
            break;
        default:
            system("cls");
            printf("\nIngresaste una opcion incorrecta, seras redirigido al menu...\n\n");
            system("pause");
            retorno = 1;
        }

        if(retorno == 0)
        {
            ListaFiltrada = ll_filterTipo(pListaBicicletas,filtrarTipo,tipo);
            if(ListaFiltrada != NULL)
            {
                controller_GuardarPosiciones("listaFiltrada.csv",ListaFiltrada);
            }
        }

    }

    if(retorno == -1)
    {
        system("cls");
        printf("\nNo se pudo generar la lista, cargue un archivo si aun no lo hizo...\n\n");
        system("pause");
    }

    return retorno;
}
/** \brief Ordena la lista por tiempos y tipo
 *
 * \param pListaBicicletas
 * \return 0 si todo esta ok, -1 si no pudo ordenar
 *
 */

int controller_ordenarPorCriterios(LinkedList* pListaBicicletas)
{
    int retorno = -1;

    if(pListaBicicletas != NULL && !ll_isEmpty(pListaBicicletas))
    {
        if(!ll_sort(pListaBicicletas,sort_Tiempo_Tipo,1))
        {
            system("cls");
            printf("\nSe ordenaron las bicicletas correctamente...\n\n");
            system("pause");
            retorno = 0;
        }
    }

    if(retorno == -1)
    {
        printf("\nNo se pudo ordenar la lista, cargue un archivo si aun no lo hizo...\n\n");
        system("pause");
    }
    return retorno;
}
/** \brief Genera un archivo nuevo con la lista ya ordenada
 *
 * \param  Path donde se guardara la lista ordenada
 * \param  pListaBicicletas
 * \return 1 si todo ok, 0 si hubo error
 *
 */

int controller_GuardarPosiciones(char* path, LinkedList* pListaBicicletas)
{
    int retorno = 0;
    int i;
    int tam = ll_len(pListaBicicletas);
    int auxId;
    char auxNombre[100];
    char auxTipo[100];
    int auxTiempo;
    FILE* pArchivo;
    eBicicleta* auxBicicleta = NULL;

    system("cls");

    if(pListaBicicletas != NULL && path != NULL)
    {
        pArchivo = fopen(path, "w");
        if(pArchivo != NULL)
        {
            for(i = 0; i < tam; i++)
            {
                auxBicicleta = (eBicicleta*)ll_get(pListaBicicletas,i);
                if(auxBicicleta != NULL)
                {
                    bicicleta_getId(auxBicicleta,&auxId);
                    bicicleta_getNombre(auxBicicleta,auxNombre);
                    bicicleta_getTipo(auxBicicleta,auxTipo);
                    bicicleta_getTiempo(auxBicicleta,&auxTiempo);

                    fprintf(pArchivo,"%d,%s,%s,%d\n",auxId,auxNombre,auxTipo,auxTiempo);
                }
            }
            fclose(pArchivo);
            retorno = 1;
        }
    }

    if(retorno == 1)
    {
        system("cls");
        printf("\nDatos guardados en ordenadas.csv exitosamente...\n\n");
    }
    else
    {
        system("cls");
        printf("\nNo se pudo guardar los datos en ordenadas.csv, debe cargarlos previamente...\n\n");
    }

    system("pause");

    return retorno;
}
