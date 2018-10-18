#define _GNU_SOURCE  // Must be defined for RTLD_NEXT
#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <assert.h>
#include <string.h>

// The following function pointers points to the original function. Example: compare with "man 2 fopen".
static FILE* (*real_fopen)(const char* path, const char* mode) = 0;
static char* (*real_fgets)(char *s, int size, FILE *stream) = 0;
static int (*real_open)(const char* pathname, int flags) = 0;

static void load_functions(void){
	// We use lazy initialization. Just initialize once 
	static volatile bool loaded = false;

	if(loaded) // Has the functions already been loaded?
		return; // if so just return.

	// OK, lets query for the original shared symbols
	real_fopen = dlsym(RTLD_NEXT, "fopen");
	real_fgets = dlsym(RTLD_NEXT, "fgets");
	real_open = dlsym(RTLD_NEXT, "open");

	loaded = true; // prevent this from happening again
}
















/*
// Below we provide our haxing code. Part 1
FILE* fopen(const char* path, const char* mode)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fopen was called with path=%s\n", path);
	return real_fopen(path, mode);
}

char *fgets(char *s, int size, FILE *stream)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fgets was called with size=%d\n", size);
	return real_fgets(s, size, stream);
}
*/















/*
// Part 2a: Redirect all files to my fake.key
FILE* fopen(const char* path, const char* mode)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fopen was called with path=%s\n", path);
	printf("**HAXER**: replacing path\n");
	return real_fopen("/home/alex/preload/fake.key", mode);
}

char *fgets(char *s, int size, FILE *stream)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fgets was called with size=%d\n", size);
	return real_fgets(s, size, stream);
}
*/




















/*
// Part 2b: Redirect only selected file to fake.key
FILE* fopen(const char* path, const char* mode)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fopen was called with path=%s\n", path);
	
	if (strcmp(path, "/noaccess/secret.key")) // Only change the file we want
		return real_fopen(path, mode);
	else
	{
		printf("**HAXER**: replacing path to /home/alex/preload/fake.key\n");
		return real_fopen("/home/alex/preload/fake.key", mode);
	}
}

char *fgets(char *s, int size, FILE *stream)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fgets was called with size=%d\n", size);
	return real_fgets(s, size, stream);
}
*/



















/*
// Part 3: Redirect file to dummy file but generate content from code
// Very unsafe way of doing it! Don't try this at home
static FILE* overrideFILE = 0;

FILE* fopen(const char* path, const char* mode)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fopen was called with path=%s\n", path);
	
	if (strcmp(path, "/noaccess/secret.key")) // Only change the file we want
		return real_fopen(path, mode);
	else
	{
		printf("**HAXER**: replacing path to /home/alex/preload/dummy.key\n");
		overrideFILE = real_fopen("/home/alex/preload/dummy.key", mode);
		return overrideFILE;
	}
}

char *fgets(char *s, int size, FILE *stream)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: fgets was called with size=%d\n", size);

	if (stream == overrideFILE)
	{
		printf("**HAXER**: fgets replacing content to \"SECRET\"\n");
		strcpy(s, "SECRET");
		return s;
	}

	return real_fgets(s, size, stream);
}

*/











//Part4: Lets inject some code to fix the random number generator
/*int rand()
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: rand called\n");
	return 6;
}
*/

/*
//Part5: Lets try open so we can see if this runs with for example "cat"
int open(char* pathname, int flags)
{
	load_functions(); // Lazy initialization
	printf("**HAXER**: open was called with pathname=%s flags=%d\n", pathname, flags);

	if (strcmp(pathname, "/noaccess/secret.key")) // Only change the file we want
		return real_open(pathname, flags);

	printf("**HAXER**: replacing path to /etc/passwd\n");
	return real_open("/etc/passwd", flags);
}
*/