#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SYS_USB "/sys/bus/usb/devices"
#define IDPRODUCT "07dc"
#define IDVENDOR "8087"


int read_value(char* in);

int main()
{

	printf("Buscando dispositivo %s%s\n", IDPRODUCT, IDVENDOR);

	DIR* dev;
	struct dirent* entry;


	

	if((dev = opendir(SYS_USB)) == NULL)
	{
		fprintf(stderr, "Error abriendo la carpeta.\n"); 


		return 1;
	}


	while((entry = readdir(dev)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;

		if (strchr(entry->d_name, ':') != NULL)
			continue;



		printf("%s:\n", entry->d_name);


		read_value(entry->d_name);




		continue;

		fprintf(stderr, "Error encontrando el dispositivo.\n");
		return -1;
	}

	return 0;
}

int read_value(char* in)
{

	
	char Path_idProduct[64];
	char Path_idVendor[64]; 

	char CmpValue[9];
	char CmpBuf[9];
	char Temp[5];
	
	snprintf(CmpValue, sizeof(CmpValue), "%s%s%c", IDPRODUCT, IDVENDOR, '\0');


	snprintf(Path_idProduct, sizeof(Path_idProduct),
			"%s/%s/idProduct",SYS_USB, in);

	snprintf(Path_idVendor, sizeof(Path_idProduct),
			"%s/%s/idVendor",SYS_USB, in);


	FILE* Pfp = fopen(Path_idProduct, "r");
	FILE* Vfp = fopen(Path_idVendor, "r");





	if(Pfp == NULL)
	{
		fprintf(stderr, "Error abriendo el archivo en: %s\n", Path_idProduct);

		return 1;
	}

	if(Vfp == NULL)
	{
		fprintf(stderr, "Error abriendo el archivo en: %s\n", Path_idVendor);

		return 1;
	}




	for(int i = 0; i < 4; i++)
		Temp[i] = fgetc(Pfp);

	Temp[4] = '\0';


	printf("	idProduct: %s\n", Temp);
	
	strcpy(CmpBuf, Temp);
	CmpBuf[4] = '\0';

	



	for(int i = 0; i < 4; i++)
		Temp[i] = fgetc(Vfp);

	Temp[4] = '\0';

	printf("	idVector: %s\n", Temp);




	strcpy(&CmpBuf[4], Temp);
	CmpBuf[9] = '\0';




	printf("	CmpBuf: %s\n", CmpBuf);
	

	if((strcmp(CmpBuf, CmpValue)) == 0)
		printf("El dispositivo esta conectado en el puerto %s", in);

	printf("la diferencia es %i\n", strcmp(CmpBuf, CmpValue));


	fclose(Pfp);
	fclose(Vfp);



}

