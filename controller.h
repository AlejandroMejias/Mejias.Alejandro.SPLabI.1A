#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

int controlador_cargarDesdeTexto(char* path , LinkedList* pListaPandemia);
int controlador_listarBicicletas(LinkedList* pListaBicicletas);
int controller_asignarTiempos(LinkedList* pListaBicicletas);
int controller_filtrarTipo(char* path, LinkedList* pListaPandemia);
int controller_ordenarPorCriterios(LinkedList* pListaBicicletas);
int controller_GuardarPosiciones(char* path, LinkedList* pListaPandemia);

#endif // CONTROLLER_H_INCLUDED
