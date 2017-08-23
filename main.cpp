#include "main.h"

#define LSTART_MAX 100.0  //Valores Máximos y Mínimos de los argumentos de entrada.
#define LSTART_MIN 0.0
#define LEND_MAX 100.0
#define LEND_MIN 0.0
#define ANGLE_MAX 90.0
#define ANGLE_MIN -90.0
#define LCONST_MAX 1.0
#define LCONST_MIN 0.0
#define N_MAX 8
#define N_MIN 3
#define RGB_MAX 255
#define RGB_MIN 0

int
main(int argc, char *argv[])
{
	int error = OFF;
	RGBcolor RGBdef ={0,0,0};
	Map cMap={-1,-1,1,1};
	userDataType Flags = {0,0,0,0,0,0,0,0,{0,0,0,0},{0,0,0}};		  //Inicializo flags para validación de arg de entrada
	userDataType uData = {1,100,1,0.7,-20,20,&Flags,3,cMap,RGBdef};   //Defaults
	if(parsecmdline(argc,argv,&Callback,&uData)!=-1){
		if(!CheckParameters(&uData)){
			system("PAUSE");
			/*if(al_init()){
				if(al_init_primitives_addon()){
					if(al_init_acodec_addon()){
						if(al_install_audio()){
							if(uData.type == TRIANGLE) {if(!NAME_OF_TRIANGLEFUNCTION(uData)) error = OFF;}
							else if(uData.type == POLYGON) {if(NAME_OF_POLYGONFUNCTION(uData)) error = OFF;}
							else if(uData.type == MANDELBROT) {if(NAME_OF_MANDELBROT(uData)) error = OFF;}
					
					
							al_uninstall_audio();
				
						}else printf("Error: No se pudo inicializar audio codec addon de allegro!\n");
							
					}else printf("Error: No se pudo inicializar audio addon de allegro!\n");
					al_shutdown_primitives_addon();
		
				}else printf("Error: No se pudo inicializar las primitivas de allegro!!\n");
				al_uninstall_system();
	
			}else printf("Error: No se pudo inicializar allegro!!!\n");*/				
			
		}else{
			error=ON;
		}
	}else{
		error=ON;
	}

	
	
	if(error) system("PAUSE");
	
	if(error == ON)	return -1;
	else return 0;
}

/* Todas las funciones de acá en adelante tienen exit(número) para cada error */
/* Consideren la posibilidad de elegir números para hacer un log de errores, o*/
/* Simplemente piensen que hacer de lo contrario al hallar error de argumentos*/

int
Callback(char *key, char *value,  void *userData){
	
	int errfl = ON;
	userDataType *uData=(userDataType*)userData;
	char*aux[]={"255","255","255"};

	if(key == NULL){	
		if(!strcmp(value,"help")){
			printf("Welcome to our Fractals function. Here is a run down of the available frantals:\n ");
			return -1;
		}else{
			printf("Error: Program only accepts \"-key value\" type arguments, help and default being the only exceptions.\n");
			return -1;
		}
	}
	
	if(!strcmp(key,"type")){				//Para todo argumento posible,
		if(uData->Flags->type == OFF){		//si lo encuentra enciende el flag,
			if(!strcmp(value,"TRIANGLE")){		//y guarda el valor para ser verificado más adelante
				uData->type = TRIANGLE;			//en otra funcion.
				uData->Flags->type = ON;
			}else
			if(!strcmp(value,"POLYGON")){
				uData->type = POLYGON;
				uData->Flags->type = ON;
			}else
			if(!strcmp(value,"MANDELBROT")){
				uData->type = MANDELBROT;
				uData->Flags->type = ON;
			}else{
				printf("Error: %s is not a valid fractal type.",value);
				return -1;
			}
			errfl = OFF;
		}else{
			printf("Error: Multiple -%s arguments!\n",key); //Y para todo argumento posible,
			return -1;								  //si esta repetido se reporta como error.
		}
	}

/* Considerar trasladar la validación de limites maximos y minimos de los parametros a estos if */
/* En mi opinion extenderia demasiado el codigo del Callback y achicaria demasiado la funcion Check*/
	
	if(!strcmp(key,"lStart")){				 
		if(uData->Flags->lStart == OFF){	
			uData->lStart = strtod(value,NULL);	
			uData->Flags->lStart = ON;
			errfl = OFF;
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;								
		}
	}

	if(!strcmp(key,"lEnd")){
		if(uData->Flags->lEnd == OFF){
			uData->lEnd = strtod(value,NULL);
			uData->Flags->lEnd = ON;
			errfl = OFF;
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"leftAngle")){
		if(uData->Flags->leftAngle == OFF){
			if(isanumber(value)){
				uData->leftAngle = strtod(value,NULL);
				uData->Flags->leftAngle = ON;
				errfl = OFF;
			}else{
				printf("Error: leftAngle given is not a number.\n");
				return -1;
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"rightAngle")){
		if(uData->Flags->rightAngle == OFF){
			if(isanumber(value)){
				uData->rightAngle = strtod(value,NULL);
				uData->Flags->rightAngle = ON;
				errfl = OFF;
			}else{
				printf("Error: rightAngle given is not a number.\n");
				return -1;
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"lConstant")){
		if(uData->Flags->lConstant == OFF){
			uData->lConstant = strtod(value,NULL);
			uData->Flags->lConstant = ON;
			errfl = OFF;
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"N")){
		if(uData->Flags->order == OFF){
			uData->order = strtol(value,NULL,10);
			uData->Flags->order = ON;
			errfl = OFF;
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"x0")){
		if(uData->Flags->CMap.x0 == OFF){
			if(isanumber(value)){
				uData->CMap.x0 = strtod(value,NULL);
				uData->Flags->CMap.x0 = ON;
				errfl = OFF;
			}else{
				printf("Error: x0 given is not a number.\n");
				return -1;
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"xf")){
		if(uData->Flags->CMap.xf == OFF){
			if(isanumber(value)){
				uData->CMap.xf = strtod(value,NULL);
				uData->Flags->CMap.xf = ON;
				errfl = OFF;
			}else{
				printf("Error: xf given is not a number.\n");
				return -1;
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"y0")){
		if(uData->Flags->CMap.y0 == OFF){
			if(isanumber(value)){
				uData->CMap.y0 = strtod(value,NULL);
				uData->Flags->CMap.y0 = ON;
				errfl = OFF;
			}else{
				printf("Error: y0 given is not a number.\n");
				return -1;
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"yf")){
		if(uData->Flags->CMap.yf == OFF){
			if(isanumber(value)){
				uData->CMap.yf = strtod(value,NULL);
				uData->Flags->CMap.yf = ON;
				errfl = OFF;
			}else{
				printf("Error: yf given is not a number.\n");
				return -1;
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(!strcmp(key,"color")){
		if(uData->Flags->pColor.R == OFF){
			if(isanumber(value)){
				uData->pColor.R = strtol(value,NULL,10);
				uData->pColor.G = uData->pColor.R;
				uData->pColor.B = uData->pColor.R;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"gy")){
				uData->pColor.R = 128;
				uData->pColor.G = uData->pColor.R;
				uData->pColor.B = uData->pColor.R;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"bk")){
				uData->pColor.R = 0;
				uData->pColor.G = 0;
				uData->pColor.B = 0;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"w")){
				uData->pColor.R = 255;
				uData->pColor.G = 255;
				uData->pColor.B = 255;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"g")){
				uData->pColor.R = 0;
				uData->pColor.G = 255;
				uData->pColor.B = 0;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"r")){
				uData->pColor.R = 255;
				uData->pColor.G = 0;
				uData->pColor.B = 0;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"b")){
				uData->pColor.R = 0;
				uData->pColor.G = 0;
				uData->pColor.B = 255;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"m")){
				uData->pColor.R = 255;
				uData->pColor.G = 0;
				uData->pColor.B = 255;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"y")){
				uData->pColor.R = 255;
				uData->pColor.G = 255;
				uData->pColor.B = 0;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"c")){
				uData->pColor.R = 0;
				uData->pColor.G = 255;
				uData->pColor.B = 255;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"p")){
				uData->pColor.R = 127;
				uData->pColor.G = 0;
				uData->pColor.B = 255;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(!strcmp(value,"o")){
				uData->pColor.R = 255;
				uData->pColor.G = 128;
				uData->pColor.B = 0;
				uData->Flags->pColor.R = ON;
				errfl = OFF;
			}else if(strchr(value,',')!=NULL){
				aux[0]=strtok(value,",");
				aux[1]=strtok(NULL,",");						
				aux[2]=strtok(NULL,",");
				if((aux[0]!=NULL)&&(isanumber(aux[0]))){
					if(aux[1]!=NULL&&(isanumber(aux[1]))){
						if((aux[2]!=NULL)&&(isanumber(aux[2]))){
							uData->pColor.R=strtol(aux[0],NULL,10);
							uData->pColor.G=strtol(aux[1],NULL,10);
							uData->pColor.B=strtol(aux[2],NULL,10);
							uData->Flags->pColor.R=ON;
							errfl = OFF;
						}else{
							printf("Error: color given is formatted wrong, use argument 'help' for details.\n");
							return -1;
						}
					}else{
						printf("Error: color given is formatted wrong, use argument 'help' for details.\n");
						return -1;
					}
				}else{
					printf("Error: color given is formatted wrong, use argument 'help' for details.\n");
					return -1;
				}
			}else{
				printf("Error: color chosen is invalid, or in the wrong format.\n");
			}
		}else{
			printf("Error: Multiple -%s arguments!\n",key);
			return -1;
		}
	}

	if(errfl == ON){
		printf("Error: Invalid key -%s!\n",key);
		return (-1);
	}
	return 0;
}

int
CheckParameters( userDataType *uData){	
	
	//En este if() se validan los arg de fractal conrespecto al resto de los arg. 
	
	if(uData->Flags->type == ON){	//Error en caso de que no este encendido el flag. Debe elegir que fractal es.
		if(uData->type == TRIANGLE){	//TRIANGLE no acepta más que lStart, lEnd y leftAngle, rightAngle. Otros argumentos son errores.
			if( (uData->Flags->lConstant == ON) || (uData->Flags->order == ON) || (uData->Flags->CMap.x0 == ON) || (uData->Flags->CMap.xf == ON) || (uData->Flags->CMap.y0 == ON) || (uData->Flags->CMap.yf == ON) || (uData->Flags->pColor.R == ON)){
				printf("Error: No constant, order, complex map, or color are accepted for TRIANGLE fractal.\n");
			}		
		}
		if(uData->type == POLYGON){	//POLYGON no acepta más que lStart, lEnd, lConstant, order y color. Otros argumentos son errores.
			if( (uData->Flags->leftAngle == ON) || (uData->Flags->rightAngle == ON) || (uData->Flags->CMap.x0 == ON) || (uData->Flags->CMap.xf == ON) || (uData->Flags->CMap.y0 == ON) || (uData->Flags->CMap.yf == ON) ){
				printf("Error: No angles or complex map are accepted for POLYGON fractal.\n");
				return -1;
			}
		}
		if(uData->type == MANDELBROT){	//Mandelbrot acepta solo x0,y0,xf,yf.
			if( (uData->Flags->lConstant == ON) || (uData->Flags->leftAngle == ON) || (uData->Flags->rightAngle == ON) || (uData->Flags->pColor.R == ON) || (uData->Flags->order == ON) || (uData->Flags->lStart == ON) || (uData->Flags->lEnd == ON)){
				printf("Error: No parameters except for complex map (x0,y0,xf,yf) are accepted for MANDELBROT fractal.\n");
				return -1;
			}
		}		
	}
	
//De aqui en adelante se verifican los limites numericos de los argumentos si estos fueron elegidos.
	
	if( (uData->Flags->lStart == ON) && ( (uData->lStart <= LSTART_MIN) || (uData->lStart > LSTART_MAX))){
		printf("Error: lStart value range exceeded. Value range: (0 ... 100] , Value chosen: %g\n",uData->lStart);
		return -1;
	}

	if( (uData->Flags->lEnd == ON) && ( (uData->lEnd <= LEND_MIN) || (uData->lEnd >= LEND_MAX) ) ){
		printf("Error: lEnd value range exceeded. Value range: (0 ... 100) Value chosen: %g\n",uData->lEnd);
		return -1;
	}else if( (uData->Flags->lEnd == ON) && (uData->lEnd >= uData->lStart)){
		printf("Error: lEnd value exceeds lStart value. lStart: %g lEnd: %g\n",uData->lStart,uData->lEnd);
		return -1;
	}

	if( (uData->Flags->lConstant == ON) && ( (uData->lConstant <= LCONST_MIN) || (uData->lConstant >= LCONST_MAX) ) ){
		printf("Error: lConstant value range exceeded. Value range: (0 ... 1) Value chosen: %g\n",uData->lConstant);
		return -1;
	}

	if( (uData->Flags->leftAngle == ON) && ( (uData->leftAngle < ANGLE_MIN) || (uData->leftAngle > ANGLE_MAX) ) ){
		printf("Error: leftAngle value range exceeded. Value range: (-90 ... 90) Value chosen: %g\n",uData->leftAngle);
		return -1;
	}
	
	if( (uData->Flags->rightAngle == ON) && ( (uData->rightAngle < ANGLE_MIN) || (uData->rightAngle > ANGLE_MAX) ) ){
		printf("Error: rightAngle value range exceeded. Value range: (-90 ... 90) Value chosen: %g\n",uData->rightAngle);
		return -1;
	}

	if( (uData->Flags->lStart == ON) && (uData->Flags->lEnd == ON) && (uData->lStart <= uData->lEnd) ){
		printf("Error: lEnd cannot be higher than lStart! lStart: %d lEnd: %g\n",uData->lStart,uData->lEnd);
		return -1;
	}

	if( (uData->Flags->CMap.x0 == ON) || (uData->Flags->CMap.xf == ON) || (uData->Flags->CMap.y0 == ON) || (uData->Flags->CMap.yf == ON) ){
		if( (uData->Flags->CMap.x0 == ON) && (uData->Flags->CMap.xf == ON) && (uData->Flags->CMap.y0 == ON) && (uData->Flags->CMap.yf == ON) ){
			if( (uData->CMap.x0 >= uData->CMap.xf) || (uData->CMap.y0 >= uData->CMap.yf) ){
				printf("Error: x0 must be lower than xf and y0 lower than yf for the complex map. x0: %g xf: %g y0: %g yf: %g\n",uData->CMap.x0,uData->CMap.xf,uData->CMap.y0,uData->CMap.yf);
				return -1;
			}
		}else{
			printf("Error: complex map requiers both limits (x0,y0) and (xf,yf). All of them must be set for Mandelbrot.\n");
			return -1;
		}
	}

	if( (uData->Flags->order == ON) && ((uData->order < N_MIN) || (uData->order > N_MAX))){
		printf("Error: N value range exceeded. Value range: [3 ... 8] Value chosen: %d\n",uData->leftAngle);
		return -1;
	}

	if( (uData->Flags->pColor.R == ON) && ((uData->pColor.R > 255) || (uData->pColor.G > 255) || (uData->pColor.B > 255) || (uData->pColor.R < 0) || (uData->pColor.G < 0) || (uData->pColor.B < 0)) ){
		printf("Error: RGB value invalid. Range for each option: [0 ... 255] Values chosen: %d %d %d.\n",uData->pColor.R,uData->pColor.G,uData->pColor.B);
		return -1;
	}

	//If there was no error, print the chosen values.
	char* names[]={"TRIANGLE","POLYGON","MANDELBROT"};
	
	if(uData->type == TRIANGLE){	//TRIANGLE no acepta más que lStart, lEnd y leftAngle, rightAngle. Otros argumentos son errores.
		printf("Fractal type: %d . %s\n lStart: %.4g\n lEnd: %.4g\n leftAngle: %.4g\n rightAngle: %.4g\n",uData->type,names[uData->type],uData->lStart,uData->lEnd,uData->leftAngle,uData->rightAngle);
	}
	if(uData->type == POLYGON){	//POLYGON no acepta más que lStart, lEnd, lConstant, order y color. Otros argumentos son errores.
		printf("Fractal type: %d . %s\n lStart: %.4g\n lEnd: %.4g\n lConstant: %.4g\n Order: %d\n R: %d G: %d B: %d \n",uData->type,names[uData->type],uData->lStart,uData->lEnd,uData->lConstant,uData->order,uData->pColor.R,uData->pColor.G,uData->pColor.B);
	}
	if(uData->type == MANDELBROT){	//Mandelbrot acepta solo x0,y0,xf,yf.
		printf("Fractal type: %d . %s\n Complex Map: (%g,%g)(%g,%g)\n",uData->type,names[uData->type],uData->CMap.x0,uData->CMap.y0,uData->CMap.xf,uData->CMap.yf);
	}		



	return 0;
}


int isanumber(char* value){
	int flag=0;
	for(int i=0;i<strlen(value);i++){
		if(isdigit(value[i]));else if(value[i]=='.') if(flag==ON) flag=ON; else return 0; else return 0;
	}
	return 1;
}