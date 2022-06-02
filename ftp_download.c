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
#define BEGGINING 6

typedef struct
{
	char user[256];
	char password[256];
	char host[256];
	char ip[256];
	char path[256];
	char filename[256];
	int port;
	char host_name[256];
} URL;

URL url;
int authentication = FALSE;

void print_url()
{
	switch (authentication)
	{
	case TRUE:
		printf("URL read:\n");
		printf("User->%s\nPassword.>%s\nHost->%s\nPath->%s\n", url.user, url.password, url.host, url.path);
		break;

	case FALSE:
		printf("URL read:\n");
		printf("Host->%s\nPath->%s\n", url.host, url.path);
		break;
	}
	printf("Host name  : %s\n", url.host_name);
	printf("IP Address : %s\n", url.ip);
	printf("Port  : %d\n", url.port);
}

// Reads desirable to new and updates string
void read_substring(char *string, char parameter, char *new)
{

	int i = 0;

	while ((string[i] != parameter) || string[i] == '\0')
	{
		new[i] = string[i];
		i++;
	}

	if (parameter != '\0')
	{
		strcpy(&string[0], &string[i + 1]);
		return;
	}

	strcpy(&string[0], &string[i]);
	return;
}

int define_url(char *url_string)
{

	char string[256];
	int beggining = 0, aux = 0;
	int i = 0;

	// verify url
	strncpy(string, url_string, BEGGINING);
	if (strcmp(string, "ftp://") != 0)
	{
		printf("No ftp:// included\n");
		return -1;
	}

	// works just fine
	strcpy(url_string, &url_string[BEGGINING]);

	// if not is 0 by default
	if (url_string[0] == '[')
	{
		authentication = TRUE;
		strcpy(url_string, &url_string[1]);
	}

	switch (authentication)
	{
	case TRUE:
		read_substring(url_string, ':', url.user);
		read_substring(url_string, '@', url.password);
		strcpy(url_string, &url_string[1]);
		read_substring(url_string, '/', url.host);
		read_substring(url_string, '/', url.path);
		break;

	case FALSE:
		read_substring(url_string, '/', url.host);
		read_substring(url_string, '/', url.path);
		break;
	}

	struct hostent *h = gethostbyname(url.host);

	if (h == NULL)
	{
		printf("Failed to gethostbyname\n");
		return -1;
	}
	strcpy(url.ip, inet_ntoa(*((struct in_addr *)h->h_addr_list[0])));
	strcpy(url.host_name, h->h_name);
	url.port = PORT;
	print_url();

	return 0;
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Error receiving from compilation");
		return -1;
	}

	if (define_url(argv[1]) < 1)
	{
		return -1;
	}

	int com_socket, data_socket;
}