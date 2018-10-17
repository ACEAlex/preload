#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
	printf("Hello world\n");

	FILE* fd = fopen("/tmp/secret.key", "r");

	if (!fd)
	{
		printf("Licens key not found!\nYou are not authorized!\n");
		return -1;
	}

	char buffer[100];
	if (!fgets(buffer, sizeof(buffer), fd))
	{
		printf("Something went wrong reading from the file\n");
		return -1;
	}

	if (strcmp(buffer, "SECRET"))
	{
		printf("Access denied! Die pirate!\n");
		return -1;
	}

	printf("System init completed. Access granted! Welcome user!\n\n");

	return 0;
}