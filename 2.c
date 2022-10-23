#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Definicion de Tipos
typedef char tString [50];
typedef struct {
    int LU;
    tString nombreApellido;
    int codMateria;
    float nota;
}rExamenesFinales;

//Variables Globales
rExamenesFinales alumno;
FILE * archivo;

int cantNotas;
float notas;
int totalAlumnos;
tString nombreMP;
float mejorPromedio;
int alumnoAnterior;

//Prototipo de Funciones
void inicializacion();
void procesoCorte();
void finalizacion();
void principioCorte();
void finCorte();
void unAlumno();
float calcularPromedio(int, float);
void buscarMP(float);

//Funcion Principal 
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();
    return 0;
}
//Implementacion
void inicializacion() {
    archivo = fopen("Notas.dat","rb");
    printf("Archivo abierto!\n");
    fread(&alumno,sizeof(rExamenesFinales),1,archivo);
    totalAlumnos = 0;
    mejorPromedio = 0;
    printf("\t*** Listado de Promedios ***\n");
    printf("Numero de Libreta \t Nota Promedio\n");
}

void procesoCorte() {
    while (!feof(archivo)) {
        principioCorte();
        while(!feof(archivo) && alumno.LU == alumnoAnterior){
            unAlumno();
            fread(&alumno,sizeof(rExamenesFinales),1,archivo);
        }
        finCorte();
    }
}

void principioCorte() {
    cantNotas = 0;
    notas = 0;
    alumnoAnterior = alumno.LU;
    printf("\t%d",alumno.LU);
}

void unAlumno() {
    cantNotas = cantNotas + 1;
    notas = notas + alumno.nota;
}

void finCorte() {
    float promedio = calcularPromedio(cantNotas, notas);
    printf("\t \t \t %.2f\n",promedio);
    buscarMP(promedio);
    totalAlumnos = totalAlumnos + 1;
}

float calcularPromedio(int pContador, float pAcumulador){
    return (pAcumulador / (float)pContador);
}

void buscarMP(float pPromedio) {
    if(pPromedio > mejorPromedio) {
        mejorPromedio = pPromedio;
        strcpy(nombreMP,alumno.nombreApellido);
    }
}

void finalizacion() {
    printf("Total de alumnos: %d\n\n",totalAlumnos);
    printf("El alumno con mayor promedio es: %s - Obtuvo: %.2f\n",nombreMP,mejorPromedio);
    fclose(archivo);
    printf("Archivo cerrado!");
}
