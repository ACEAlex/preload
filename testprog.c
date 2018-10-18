#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	printf("Hello world\n");

	FILE* fd = fopen("/noaccess/secret.key", "r");

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

	printf("If you roll 6 on a die ten times you win a price!\n");

	// Init rand generator.
	srand(time(NULL));

	for(int i = 1; i <= 10; ++i)
	{
		int die = rand()%6;

		if (die == 0){ // 0 is equivalent to  6
			printf("Roll %d: Great! It was a 6\n", i);
		}
		else
		{
			printf("Sorry you did not win!\n");
			return -1;
		}
	}

	printf("We have a winner! Infinite fame and glory to you!\n\n");

	return 0;
}
