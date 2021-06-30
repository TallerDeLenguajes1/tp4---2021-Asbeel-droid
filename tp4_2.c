#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 50

typedef struct
{
    int TareaID; //Numerado en ciclo iterativo
    char * Descripcion; //
    int Duracion; // entre 10 y 100
} Tarea ;

typedef struct Nodo
{
    Tarea T;
    Nodo * siguiente;
} Nodo;

//Operaciones de la lista enlazada
Nodo * crearListaVacia();
Nodo * crearNodo(Tarea T);
void insertarNodo(Nodo ** Lista, Nodo * nodo);
//--------------------------------

int pedirCantidad();
Tarea CrearTarea(int id);
void mostrarTarea(Nodo * nodo);
void listarTareas(Nodo ** Lista);
void estadoTarea(Nodo ** toDo, Nodo ** done);
Nodo * buscarPorPalabra(Nodo ** lista, char palabra[]);
Nodo * buscarPorID(Nodo ** lista, int id);
void liberarMemoria(Nodo ** lista);
void listarTareas(Nodo ** Lista);


int main()
{
    srand(time(NULL));//Para que los valores random valuen entre ejecuciones

    int cantidad;
    char palabra[N];
	int id;
    Tarea tarea;
    Tarea ** toDo;
    Tarea ** done;

    cantidad = pedirCantidad();
    toDo = crearListaVacia();
    done = crearListaVacia();
    cargarTareas(toDo, cantidad);

    printf("\n REVISION DE TAREAS \n");
    estadoTarea(&toDo, &done);
    
	printf("\n BUSCAR TAREAS POR PALABRA CLAVE \n");
    printf("Ingrese una palabra clave para buscar una tarea: ");
	scanf(" %s", palabra);
	if(buscarPorPalabra(&toDo, palabra))
		mostrarTarea(buscarPorPalabra(&toDo, palabra));
	else
		printf("No se encontraron coincidencias.\n");
	printf("\n"); 
	printf("\n BUSCAR TAREAS POR ID \n");
    printf("Ingrese una ID de una tarea: (entre 1 y %d)\n", cantidad);
	scanf(" %d", &id);
	if(buscarPorID(&toDo, id))
		mostrarTarea(buscarPorID(toDo, id));
	else
		printf("No se encontraron coincidencias.\n");
	printf("\n");  
    

    liberarMemoria(&toDo);
	liberarMemoria(&done);
    return 0;
}

Nodo * crearListaVacia()
{
    return NULL;
}

Nodo * crearNodo(Tarea T)
{
    Nodo * nuevoNodo = (Nodo *) malloc(sizeof(Nodo));

    nuevoNodo->T = T;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

void insertarNodo(Nodo ** Lista, Nodo * nodo)
{
    if (Lista)
    {
        nodo->siguiente = * Lista;
        * Lista = nodo;
    } else
    {
        * Lista = nodo;
    }
}

int pedirCantidad()
{
    int num;
    do
    {
        printf("Ingrese el numero de tareas que desea realizar:");
        scanf("%u", &num);
        fflush(stdin);
        if(num < 1)
            printf("ERROR, intente nuevamente.\n"); 
    } while(num < 1);
    printf("\n");
    return num;
}


void cargarTareas(Tarea ** lista, int n)
{
	Tarea tareaNueva;
    Nodo * nuevoNodo;
    for (int i = 0 ; i < n ; i++)
	{
		printf("------Tarea Nro %d\n", (i + 1));
		tareaNueva.TareaID = i + 1;
		tareaNueva.Duracion = 10 + rand() % 91;
		tareaNueva.Descripcion = (char *)malloc(sizeof(char) * N);
        printf("Ingrese una breve descripcion:\n");
        fflush(stdin);
        gets(tareaNueva.Descripcion);

		nuevoNodo = crearNodo(tareaNueva);
        insertarNodo(lista, nuevoNodo);
	}
}

void mostrarTarea(Nodo * nodo)
{
    if(nodo)
	{
		printf("ID: %d\n", nodo->T.TareaID);
		printf("Descripcion: %s\n", nodo->T.Descripcion);
		printf("Duracion: %dHs\n", nodo->T.Duracion);
		printf("\n");		
	}		
}

void estadoTarea(Nodo ** toDo, Nodo ** done)
{
	char ask;
	
	Nodo * aux = *toDo;
	Nodo * anterior = NULL;
	
	while (aux)
	{
		printf("\tTarea Nro %d\n", aux->T.TareaID);
		mostrarTarea(aux);
		printf("?Ya realizo la tarea? (S/N)\n");
		scanf(" %c", &ask);
		
		if(ask == 's' || ask == 'S')
		{
			//Es el primer elemento
			if(!anterior)
			{
				InsertarEnLista(done, aux);
				*toDo = (*toDo)->siguiente;
				aux->siguiente = NULL;
				aux = *toDo;
			}
			//Es un elemento cualquiera
			else
			{
				InsertarEnLista(done, aux);
				anterior->siguiente = aux->siguiente;
				aux->siguiente = NULL;
				aux = anterior->siguiente;
			}
		}
		else
		{
			anterior = aux;
			aux = aux->siguiente;
		}
	}
}

Nodo * buscarPorID(Nodo ** lista, int id)
{
	Nodo * aux = *lista;
	while (aux)
	{
		if (aux->T.TareaID == id)
			return aux;
		aux = aux->siguiente;
	}
	return NULL;
}

void liberarMemoria(Nodo ** lista)
{
	Nodo * aux;
	
	while (*lista)
	{
		free((*lista)->T.Descripcion);
		aux = *lista;
		*lista = (*lista)->siguiente;
		free(aux);
	}
}

Nodo * buscarPorPalabra(Nodo ** lista, char * palabra)
{	
	Nodo * aux = *lista;
	while (aux)
	{
	    if (strstr(aux->T.Descripcion, palabra))
	        return aux;
	    aux = aux->siguiente;
	}
	
	return NULL;
}

void listarTareas(Nodo ** Lista)
{
	Nodo * aux = *Lista;
	while (aux)
	{
		mostrarTarea(aux);
		aux = aux->Siguiente;
	}
		
}
