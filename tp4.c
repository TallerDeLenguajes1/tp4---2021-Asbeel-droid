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

int pedirCantidad();
Tarea ** espacioLista(int cantidad);
void cargarTareas(Tarea ** lista, int n);
void mostrarTarea(Tarea * tarea);
void estadoTarea(Tarea ** toDo, Tarea ** done, int n);
Tarea * buscarPorPalabra(Tarea ** lista, int n, char palabra[]);
Tarea * buscarPorID(Tarea ** lista, int n, int id);
void liberarMemoria(Tarea ** lista, int n);


int main()
{
    srand(time(NULL));//Para que los valores random valuen entre ejecuciones

    int cantidad;
    char palabra[N];
    Tarea tarea;
    Tarea ** toDo;
    Tarea ** done;

    cantidad = pedirCantidad();
    toDo = espacioLista(cantidad);
    done = espacioLista(cantidad);
    cargarTareas(toDo, cantidad);

    printf("\n REVISION DE TAREAS \n");
    estadoTarea(toDo, done, cantidad);
    
    

    liberarMemoria(toDo, cantidad);
	liberarMemoria(done, cantidad);
    return 0;
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

Tarea ** espacioLista(cantidad)
{
    Tarea ** lista =(Tarea **) malloc(sizeof(Tarea *) * cantidad);
    return lista;
}

void cargarTareas(Tarea ** lista, int n)
{
    for (int i = 0 ; i < n ; i++)
	{
		printf("------Tarea Nro %d\n", (i + 1));
		lista[i] = (Tarea *) malloc(sizeof(Tarea *));
		(lista[i])->TareaID = i + 1;
		(lista[i])->Duracion = 1 + rand() % 10;
		(lista[i])->Descripcion = (char *) malloc(sizeof(char)*N);
		printf("Ingrese una breve descripcion:\n");
		gets((lista[i])->Descripcion);
	}
}

void mostrarTarea(Tarea * tarea)
{
    printf("ID: %d\n", tarea->TareaID);
    printf("Duracion: %dhs\n", tarea->Duracion);
    printf("Descripcion: %s\n", tarea->Descripcion);
    printf("\n");		
}

void estadoTarea(Tarea ** toDo, Tarea ** done, int n)
{
	char ask;
	
	for(int i = 0 ; i < n ; i++)
	{
		printf("\tTarea Nro %d\n", (i + 1));
		mostrarTarea(toDo[i]);

		printf("Ya realizo la tarea? (S/N)\n");
		scanf(" %c", &ask);
		
		if(ask == 's' || ask == 'S')
		{
			done[i] = toDo[i];
			toDo[i] = NULL;
			printf("\t%d\n", (done[i])->TareaID);
		}
	}
}

Tarea * buscarPorID(Tarea ** lista, int n, int id)
{
	if (id > n)
		return NULL;
	else
		return lista[id - 1];
}

void liberarMemoria(Tarea ** lista, int n)
{
	for (int i = 0 ; i < n ; i++)
	{
		if(lista[i])
			free((lista[i])->Descripcion);
		free(lista[i]);
	}
	free(lista);
}