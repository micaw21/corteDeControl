#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definicion de Tipos
typedef char tString [50];
typedef struct{
    int nroCuenta;
    tString nombre;
    int codOperacion;
    float importe;
}rDatosBanco;

//Variables Globales
rDatosBanco clientes;
FILE * archivo;

float totalDeposito;
float totalExtraccion;
int cantDepositos;
int cantExtracciones;
int cuentaAnterior;

//Prototipo de Funciones
void inicializacion();
void procesoCorte();
void finalizacion();
void principioCorte();
void unaCuenta();
void finCorte();

//Funcion Principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();
    return 0;
}

//Implementacion
void inicializacion() {
    archivo = fopen("DatosBanco.dat","rb");
    printf("Archivo abierto!\n");
    fread(&clientes,sizeof(rDatosBanco),1,archivo);
    printf("\t*** Detalle de Movimientos por Cuenta ***\n");
    printf("Nro. Cuenta \t Deposito \t Extraccion\n");
}

void procesoCorte() {
    while(!feof(archivo)) {
        principioCorte();

        while(!feof(archivo) && clientes.nroCuenta == cuentaAnterior) {
            unaCuenta();
            fread(&clientes,sizeof(rDatosBanco),1,archivo);
        }

        finCorte();
    }
}

void principioCorte() {
    totalDeposito = 0;
    totalExtraccion = 0;
    cantDepositos = 0;
    cantExtracciones = 0;
    cuentaAnterior = clientes.nroCuenta;
}

void unaCuenta() {
    if(clientes.codOperacion == 1) {
        totalDeposito = totalDeposito + clientes.importe;
        cantDepositos = cantDepositos + 1;
        printf("\t %d \t %.2f \t %d\n",clientes.nroCuenta,clientes.importe,0);
    } else {
        totalExtraccion = totalExtraccion + clientes.importe;
        cantExtracciones = cantExtracciones + 1;
        printf("\t %d \t %d\t\t%.2f\n",clientes.nroCuenta,0,clientes.importe);
    }
}

void finCorte() {
    printf("Total Cta %d \t $%.2f \t $%.2f\n",cuentaAnterior,totalDeposito,totalExtraccion);
    printf("Cant. de mov. Cta %d \t %d \t %d\n",cuentaAnterior,cantDepositos,cantExtracciones);
    printf("-------------------------------------------------------\n");
}

void finalizacion() {
    fclose(archivo);
    printf("Archivo cerrado!\n");
}