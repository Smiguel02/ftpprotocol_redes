#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

#define PORT 21
#define USER "anonymous"
#define PASSWORD "anonymous"

typedef struct
{
	char user[256];
	char password[256];
	char host[256];
	char ip[256];
	char path[256];
	char filename[256];
	int port;
} URL;

URL *url;
int authentication = FALSE;

int define_url(char *url_string)
{

	char string[256];
	int beggining;
	int i = 0;

	beggining = strcmp(url_string, "ftp://");
	printf("beggining=%d\n", beggining);
	strcpy(string, url_string[beggining + 1]);

	if (!beggining)
	{
		printf("Error on ftp definition");
		return -1;
	}

	// if not is 0 by default
	if (url_string[beggining + 1] == '[')
	{
		authentication = TRUE;
	}

	switch (authentication)
	{
	case TRUE:
		strcmp();

		break;

	case FALSE:

		break;
	}
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Error receiving from compilation");
		return -1;
	}
}