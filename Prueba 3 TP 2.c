#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char info;
    struct nodo* sgte;
} Nodo;

// se definen para no poner ** dos veces
typedef Nodo* Pila;
typedef Nodo* PNodo;

//PROTOTIPOS DE FUNCION.
void push(Pila* pila, char valor);
char pop(Pila* pila);
char matrizTransicion (char caracter);
int estaEnElAlfabeto(char caracter); // Manda un caracter y devuelve un '1' (true) si pertenece al alfabeto y ´0´ si este no pertenece.
int tipos (char caracter);
void procesarTipos(int,Pila*);
int columnas(char caracter);
int recorrer (char* s); // Duda !!!
/*
enum ElementosMatriz {
    NRC, // no reconoce cadena
    POP,
    T1E2,
    F1T2,
    E1P,  // E1 mas el )
    DN,
    N
};
*/

int main()
{
    Pila pila = NULL;
    char expresion[] = "";
    int i = 0;
    int nroColumna = 0;
    int nroFila = 0;

        int matrizTransicion [7][6] = {
        {12,0,0,12,0,0},
        {0,12,0,0,0,-1},
        {34,0,0,34,0,0},
        {0,0,34,0,0,-1},
        {5,0,0,1,0,0},
        {56,0,0,0,0,-1},
        {-1,0,0,0,0,0}
    };

    printf("Ingrese una expresion: ");
    scanf("%s",expresion);

    for (i=0; i<=strlen(expresion); i++) {
        //printf("%s","s");
        nroColumna = columnas(expresion[i]);
        if(nroColumna == 5) {
               if(nroFila == 1 || nroFila == 3 || nroFila == 5) {
                  pop(pila);
               } else {
                printf ("%s","No se reconoce la cadena.");
               }
        } else{
               nroFila = 0;  // por si vuelve a la funcion pushearFilas, que la fila este inicializada y revise la columna fila por fila, todas.
               pushearFilas(nroFila,nroColumna);
        }
            /*else {
            procesarTipos(matrizTransicion[nroFila][nroColumna], pila);
        }*/
        nroFila ++;
    }

    return 0;

}

// DEFINICIONES DE FUNCIONES.
void push(Pila*pila, char valor)
{
    PNodo nodoNuevo = (PNodo)malloc(sizeof(Nodo)); //malloc remplaza el "new" y recibe como parametro el sizeof
    nodoNuevo -> info = valor;
    nodoNuevo -> sgte = *pila;
    *pila = nodoNuevo;
}

char pop(Pila *pila)
{
    char info;
    PNodo aux = *pila;
    *pila = aux -> sgte;
    info = aux -> info;
    free(aux);             // equivalente al delete de c++

    return info;
}

int estaEnElAlfabeto(char caracter)
{
    char alfabeto[15] = {'0','1','2','3','4','5','6','7','8','9','*','+','(',')'};
    int i;

    for(i = 0; i <= 15; i++) {
        if( caracter == alfabeto[i]) {
            return 1;
        }
    }
    return 0;
}

int columnas(char caracter)
{
    int columna = 0;

    switch (caracter) {
    case '0'...'9':
        columna = 0;
        break;
    case '+':
        columna = 1;
        break;
    case '*':
        columna = 2;
        break;
    case '(':
        columna = 3;
        break;
    case ')':
        columna = 4;
        break;
    default:
        columna = 6;
    }
    return columna;
}

void pushearFilas(int fila, int columna)
{
        int matrizTransicion [7][6] = {
        {12,0,0,12,0,0},
        {0,12,0,0,0,-1},
        {34,0,0,34,0,0},
        {0,0,34,0,0,-1},
        {5,0,0,1,0,0},
        {56,0,0,0,0,-1},
        {-1,0,0,0,0,0}
    };
    int valor = 0;
    int n = 0;
    int m = 0;
    //fila = 0;
    while(fila < 7){
         valor = matrizTransicion[fila][columna];
        if(valor != 0){
            if(valor == -1){      // el -1 es un pop
                pop(valor);
            } else{
                n = valor / 10;
                m = ((valor / 10) - n)* 10;
                push(pila,m);/*-------------- Che anto, no habia que*/
                push(pila,n);
                nuevaFila = filaSiguiente(n,m,columna);
                pushearFilas(nuevaFila,columna);
            }
        } else{
            fila ++;
        }
    }
}

int filaSiguiente(int valor1, int valor2, int columna)
{
    int fila = 0;
    if(matrizTransicion[valor1][columna] != 0){
        fila = valor1;
    } else if(matrizTransicion[valor2][columna] != 0){
        fila = valor2;
    }
  return fila;
}

void procesarTipos(int valorMatriz, Pila*pila)
{
    if(valorMatriz > 9) {
        int a = valorMatriz / 10;
        float b = (valorMatriz % 10) * 10;
        push(&pila,a);
        push(&pila,b);
    }

}
/*
int procesarCadena(char * s)
{
int acum = 0;

char c[] = "";
while (c = get(c) != '\0') // La funcion get lee todo lo que haya en el buffer hasta que encuentre un '\n', y lo copia en la variable correspondiente.
{
	if (isdigit(c) == 1)        // La funcion isdigit() toma un char como argumento y devuelve 1 si es un dígito y 0 si no lo es.
	{
		c = convertir(c);
	    acum = acum * 10 + c;
	} else if (isdigit(c) == 0)
	{
		push (pila,acum);
		acum = 0;
	} else if (c = '+')
	{
		acum = acum + recorrer(s);
	} else if (c = '*')
	{
		acum = acum * recorrer(s);
	}
}

return acum;
}
*/
