//
//  main.c
//  Evaluacion3
//
//  Created by Santiago Robles on 26/04/22.
//

#include <stdio.h>
#include <stdlib.h>

struct punto2D{
    double x;
    double y;
    struct punto2D *siguiente;
};

int menu(void); //regresa la opcion seleccionada por el usuario
void doOption(int option, struct punto2D *medicion, struct punto2D *firstMedicion);//hace lo que el usuario selecciono
struct punto2D * newPoint(void);
void printList(struct punto2D *medicion);
void freeMemory(struct punto2D *medicion);
void minimosCuadrados(struct punto2D *medicion);

int main() {


    
    struct punto2D *medicion = NULL;//va a recorrer la lista
    struct punto2D *firstMedicion = NULL; //vamos a guardar el inicio de la lista
    
    doOption(menu(), medicion, firstMedicion);
    return 0;
}
//funcion que muestra el menu y regresa la opcion agarrada por el usuario
int menu(void){
    int menuOption;
    do{
        printf("\n1. Introducir nuevo dato");
        printf("\n2. Imprimir datos");
        printf("\n3. Minimos Cuadrados");
        printf("\n4. Salir");
        printf("\nIntroduce la opcion: ");
        scanf("%d", &menuOption);
    }while(menuOption != 1 && menuOption != 2 && menuOption != 3 && menuOption != 4);
    return menuOption;
}
//hace la accion correspondiente a la opcion agarrada por el usuario
void doOption(int option, struct punto2D *medicion, struct punto2D *firstMedicion){
    switch (option) {
        case 1:
            if(medicion == NULL){
                //si es el primer punto, se pone al principio
                medicion = newPoint();
                firstMedicion = medicion;
                doOption(menu(), medicion, firstMedicion);
            }else{
                //si no es el primer punto, se pone la direccion de memoria en el
                //siguiente
                if(medicion -> siguiente == NULL){
                    medicion -> siguiente =newPoint();
                }else if(medicion ->siguiente != NULL){
                    do{
                        medicion = medicion -> siguiente;
                    }while(medicion -> siguiente != NULL);
                    medicion -> siguiente = newPoint();
                }
                
            doOption(menu(), medicion, firstMedicion);
            break;
        case 2:
            printList(firstMedicion);
            doOption(menu(), medicion, firstMedicion);
            break;
        case 3:
                minimosCuadrados(firstMedicion);
                doOption(menu(), medicion, firstMedicion);
            break;
        case 4:
                printf("\nBorrando memoria...");
                freeMemory(firstMedicion);
                printf("\nGracias por usar el programa!\nAutor: Santiago Robles\n");
                break;
        default:
            printf("\nRevisar entrada");
            break;
            }
    }
    
}
//regresa el puntero donde se guarda la informacion del nuevo punto
struct punto2D * newPoint(){
    float x,y;

        struct punto2D *nextPoint =(struct punto2D*)malloc(sizeof(struct punto2D));
        printf("\nIntroduce x: ");
        scanf("%f", &x);
        printf("\nIntroduce y: ");
        scanf("%f", &y);
        nextPoint -> x = x;
        nextPoint -> y = y;
        nextPoint -> siguiente = NULL;
        return nextPoint;

}
//imprime la lista, recorriendo hasta que el siguiente sea NULO e imprime el ultimo dato
void printList(struct punto2D *medicion){
    int punto = 1;
    struct punto2D tempPoint = *medicion;
    printf("\nTabla X, Y. Utilizar en Calculadora grafica DESMOS");
    //imprimes hasta el penultimo dato
    while (tempPoint.siguiente != NULL) {
        printf("\n%f, %f", tempPoint.x,tempPoint.y);
        punto++;
        tempPoint = *tempPoint.siguiente;
    }
    //imprimir el ultimo punto
    printf("\n%f, %f\n", tempPoint.x,tempPoint.y);
    
}
void freeMemory(struct punto2D *medicion){
    struct punto2D *freeIndex = medicion;

    while (freeIndex -> siguiente != NULL) {
        struct punto2D *saveAddress = freeIndex -> siguiente; //guarda la siguiente direccion antes de borrar la info
        printf("\nBorrando %p", freeIndex);
        free(freeIndex);
        freeIndex = saveAddress; //seguimos con la siguiente direccion
    }
    printf("\nBorrando %p", freeIndex);
    free(freeIndex); //borramos la ultima direccion
}

void minimosCuadrados(struct punto2D *medicion){
    float sumX = 0; //sumatoria de x
    float sumY = 0;//sumatoria de y
    float sumXY = 0;//sumatoria de xy
    float sumXCuadrada = 0;//sumatoria de x al cuadrado
    float n = 0;//cuantos datos se usan
    
    struct punto2D *tempIndex = medicion;
    //calculamos las sumatorias de los datos que necesitamos
    while (tempIndex -> siguiente != NULL) {
        n++;
        sumX += tempIndex -> x;
        sumY += tempIndex -> y;
        sumXY += (tempIndex -> x) * (tempIndex -> y);
        sumXCuadrada += tempIndex -> x * tempIndex -> x;
        tempIndex = tempIndex -> siguiente;
    }
    n++;
    sumX += tempIndex -> x;
    sumY += tempIndex -> y;
    sumXY += (tempIndex -> x) * (tempIndex -> y);
    sumXCuadrada += tempIndex -> x * tempIndex -> x;
    //printf("SumX: %f, SumY: %f, SumXY: %f, SumX2: %f", sumX,sumY,sumXY,sumXCuadrada);
    
    //calculamos m
    float m;
    m =(sumXY - ((sumX * sumY)/n))/(sumXCuadrada - ((sumX * sumX)/n));
    //calculamos b
    float b;
    b = (sumY/n) - (m * (sumX/n));
    printf("\nIntroducir ecuacion en graficadora DESMOS: ");
    printf("\ny = %fx+%f\n", m,b);
}
