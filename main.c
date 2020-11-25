#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"
#include "bicicletas.h"
#include "auxiliares.h"
#include "controller.h"

int main()
{
    srand (time(NULL));
    char opcion;
    int flag = 0;
    int flagOrdenamiento = 0;
    LinkedList* ListaBicicletas = ll_newLinkedList();
    LinkedList* ListaOrdenada = NULL;


    do
    {
        opcion = menu();

        switch(opcion)
        {
            case 'a':
                controlador_cargarDesdeTexto("bicicletas.csv",ListaBicicletas);
                break;
            case 'b':
                controlador_listarBicicletas(ListaBicicletas);
                break;
            case 'c':
                controller_asignarTiempos(ListaBicicletas);
                flag = 1;
                break;
            case 'd':
                if(flag == 1)
                {
                    controller_filtrarTipo("listaFiltrada.csv",ListaBicicletas);
                }
                else
                {
                    system("cls");
                    printf("\nDebes cargar los tiempos primero...\n\n");
                    system("pause");
                }
                break;
            case 'e':
                if(flag == 1)
                {
                    //Copio la lista original  para pasarla al sort
                    ListaOrdenada = ll_clone(ListaBicicletas);

                    if(ListaOrdenada != NULL)
                    {
                        controller_ordenarPorCriterios(ListaOrdenada);
                        controlador_listarBicicletas(ListaOrdenada);
                        flagOrdenamiento = 1;
                    }
                }
                else
                {
                    system("cls");
                    printf("\nDebes cargar los tiempos primero...\n\n");
                    system("pause");
                }
                break;
            case 'f':
                if(flag == 1 && flagOrdenamiento == 1)
                {
                    controller_GuardarPosiciones("ordenadas.csv",ListaOrdenada);
                }
                else
                {
                    system("cls");
                    printf("\nDebes cargar los tiempos primero...\n\n");
                    system("pause");
                }
                break;
        }
        system("cls");
        fflush(stdin);
    }
    while(opcion != 'x');

    ll_deleteLinkedList(ListaBicicletas);
    ll_deleteLinkedList(ListaOrdenada);
    return 0;
}
