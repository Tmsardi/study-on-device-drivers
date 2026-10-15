#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SYS_USB "/sys/bus/usb/devices"
#define IDPRODUCT 07dc
#define IDVENDOR 8087


int read_value(char* in);

int main()
{


	DIR* dev;
	struct dirent* entry;


	

	if((dev = opendir(SYS_USB)) == NULL)
	{
		fprintf(stderr, "Error abriendo la carpeta.\n"); 


		return 1;
	}

	while((entry = readdir(dev)) != NULL)
	{
		if(entry->d_name[0] == '.')
			continue;

		read_value(entry->d_name);


		printf("%s\n", entry->d_name);


		continue;

		fprintf(stderr, "Error encontrando el dispositivo.\n");
		return -1;
	}


	return 0;
}

int read_value(char* in)
{

	printf("hola");
	
	char Path_idProduct[64];
	char Path_idVendor[64]; 

	char CmpBuf[8];
	char* Temp[5];
	
	snprintf(Path_idProduct, sizeof(Path_idProduct),
			"%s/%s/idProduct",SYS_USB, in);

	snprintf(Path_idVendor, sizeof(Path_idProduct),
			"%s/%s/idVendor",SYS_USB, in);
	
	int Pfd = open(Path_idProduct, O_RDONLY);
	int Vfd = open(Path_idVendor, O_RDONLY);

	printf("hola como estas bien y tu super");

	read(Pfd, Temp, 4);
	
	printf("%s",Pfd);

	

















}

