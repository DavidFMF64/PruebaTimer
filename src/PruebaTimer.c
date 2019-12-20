/*
 ============================================================================
 Name        : PruebaTimer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#include "PruebaTimer.h"



void (*ptr_fun[5])(void) = { NULL, NULL, NULL, NULL, NULL };
int n_ptr_fun = 0;

int Var_prueba[2][2][5] =
{
	{
		{1,2,3,4,5},
		{10,20,30,40,50},
	},
	{
		{11,22,33,44,55},
		{12,22,32,42,52},
	},
};

int Var_prueba2[2][5] =
{
		{51,42,33,24,15},
		{14,24,34,44,54},
};

int Var_prueba1[5] =  {80,90,30,40,60};


int Var_float_prueba1[5] =  {80.1, 90.2, 30.3, 40.4, 60.5};


void f1 ( void ) {

	printf("Imprime F1\r\n");
}

void f2 ( void ) {

	printf("Imprime F2\r\n");
}

void f3 ( void ) {

	printf("Imprime F3\r\n");
}


void AddFx ( void (f() ) ) {

	if (n_ptr_fun<5) {

		ptr_fun[n_ptr_fun] = f;
		n_ptr_fun++;
	}

}

void Fx ( void ) {
	int i=0;

	AddFx ( f1 );
	AddFx ( f2 );
	AddFx ( f3 );

	while ( ptr_fun[i] !=  0 ) {

		ptr_fun[i]();

		i++;
	}
}

typedef enum
		{
			FORMATO_C=0,
			FORMATO_EXCEl,
			FORMATO_MAX,L
		}ENUM_FORMATO;


void PrintFormatVar ( char* name, int* data_in, int z_in, int y_in, int x_in, ENUM_FORMATO formato )	//variable del tipo  Var[z][y][x]
{
	int x,y,z;
	int* pdata;
	int  data;

	char txt_1[10]="";
	char txt_2[10]="";
	char txt_3[10]="";
	char txt_4[10]="";
	char txt_5[10]="";
	char txt_6[10]="";

	if (z_in <1) z_in=1;
	if (y_in <1) y_in=1;
	if (x_in <1) x_in=1;

	switch (formato) {
	case FORMATO_C:
			strcpy(txt_1, "{\n\r" );
			if (y_in>1) { strcpy(txt_2, " {\r\n" ); }
			if (x_in>1) { strcpy(txt_3, "  { " );   }
			if (x_in>1) { strcpy(txt_4, "},\n\r" ); }
			if (y_in>1) { strcpy(txt_5, " },\n\r"); }
			strcpy(txt_6, "};\n\r");
		break;

	case FORMATO_EXCEl:
		//strcpy(txt_1, "\n\r" );
		strcpy(txt_2, " \r\n" );
		strcpy(txt_3, "   " );
		strcpy(txt_4, "\n\r" );
		strcpy(txt_5, "\n\r");
		//strcpy(txt_6, "\n\r");
		break;

	default:
		//strcpy(txt_1, "" );
		strcpy(txt_2, " \r\n" );
		strcpy(txt_3, "   " );
		strcpy(txt_4, "\n\r" );
		strcpy(txt_5, "\n\r");
		//strcpy(txt_6, "");
		break;

	}

	pdata = data_in;

	printf(name);
	printf( txt_1 ); //printf("{\n\r");
	for (z=0;z<z_in;z++) {
		printf( txt_2 ); //printf(" {\r\n");
		for (y=0;y<y_in;y++) {
			printf( txt_3 ); //printf("  { ");
			for (x=0;x<x_in;x++) {
				data = *pdata;
				if ( formato == FORMATO_C) printf("%02d, ", data);
				else if ( formato == FORMATO_EXCEl )  printf("%02d \t", data);
				else printf("%02d ", data);
				pdata++;
			}
			printf( txt_4 ); //printf("},\n\r");
		}
		printf( txt_5 ); //printf(" },\n\r");
	}
	printf( txt_6 ); //printf("};\n\r");

}



void fvoid ( void* data ) {
	int i=0;
	int* d;

	d = (int*)data;

	for (i=0;i<5;i++) {
		printf("%d ", *d );
		d++;
	}
	printf("\r\n");
}

int main(void) {



	puts("!!!Hello World!!!"); // prints !!!Hello World!!!

	Fx();

	PrintFormatVar ( "int Variable[2][2][5] = \r\n", (int*)&Var_prueba[0][0][0], 2, 2, 5, FORMATO_C);

	PrintFormatVar ( "valores Excel \r\n", (int*)&Var_prueba[0][0][0], 2, 2, 5, FORMATO_EXCEl );

	PrintFormatVar ( "int Variable2[2][5] = \r\n", (int*)&Var_prueba2[0][0], 0, 2, 5, FORMATO_C);
	PrintFormatVar ( "int Variable1[5] = \r\n", (int*)&Var_prueba1[0], 0, 0, 5, FORMATO_C);

	printf("\r\nvoid: "); fvoid ( Var_prueba1 );

	return EXIT_SUCCESS;
}


