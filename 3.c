#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Definicion de Tipos
typedef char tString [25];
typedef struct{
    tString IP;
    tString nombre;
    int tipo;
    int tamanio;
}rDocumentos;

//Variables Globales
rDocumentos documento;
FILE * archivo;

tString vTipos [5] = {".docx",".pdf",".jpg",".png",".xlsx"};

int cantDocumentos;
int totalKB;
int tamanioTotal;
int totalDocumentosImpresos;
int totalImagenesImpresas;
tString IPAnterior;
int tipoAnterior;
int totalKBImagenes;
int totalKBImpresiones;
int tamanioImagen;

//Prototipo de Funciones
void inicializacion();
void principioCorte();
void procesoCorte();
void unDocumento();
void finCorte();
void finalizacion();

//Funcion Principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();
    return 0;
}

//Implementacion
void inicializacion() {
    archivo = fopen("colaImpresion.dat","rb");
    printf("Archivo abierto!\n");
    fread(&documento,sizeof(rDocumentos),1,archivo);
    totalDocumentosImpresos = 0;
    totalImagenesImpresas = 0;
    totalKBImagenes = 0;
    totalKBImpresiones = 0;
    printf("\t*** Documentos Impresos ***\n");
    printf("IP \t\t Documento \t\t Tamanio (bytes)\n");
}

void procesoCorte() {
    while(!feof(archivo)) {
        principioCorte();
        while(!feof(archivo) && strcmp(IPAnterior, documento.IP) == 0){
            unDocumento();
            fread(&documento,sizeof(rDocumentos),1,archivo);
        }
        finCorte();
    }
}

void principioCorte(){
    cantDocumentos = 0;
    totalKB = 0;
    tamanioTotal = 0;
    //IPAnterior = documento.IP;
    strcpy(IPAnterior, documento.IP);
    tipoAnterior = documento.tipo;
    printf("%s\n",documento.IP);
}

void unDocumento() {
    cantDocumentos = cantDocumentos + 1;
    tamanioTotal = tamanioTotal + documento.tamanio;
    if(documento.tipo == 3 || documento.tipo == 4){
        tamanioImagen = tamanioImagen + documento.tamanio;
    }
    printf("\t\t%s \t\t %d\n",strcat(documento.nombre,vTipos[documento.tipo - 1]),documento.tamanio);
}

void finCorte() {
    totalKB = tamanioTotal / 1024;
    printf("Cantidad de documentos impresos PC %s %d \t %d KB\n",IPAnterior,cantDocumentos,totalKB);
    printf("************************************************************\n");
    totalDocumentosImpresos = totalDocumentosImpresos + 1;
    totalKBImpresiones = totalDocumentosImpresos + totalKB;
    if(tipoAnterior == 3 || tipoAnterior == 4){
        totalImagenesImpresas++;
        totalKBImagenes = totalKBImagenes + tamanioImagen;
    }
}

void finalizacion() {
    printf("Total de archivos de imagenes impresos %d \t %d KB\n",totalImagenesImpresas,totalKBImagenes);
    printf("Total de documentos impresos \t\t %d\t\t%d KB\n",totalDocumentosImpresos,totalKBImpresiones);
    fclose(archivo);
    printf("Archivo cerrado!");
}