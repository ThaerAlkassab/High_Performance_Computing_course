#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
// Returns hostname for the local computer
void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}
 
// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}
 
int main()
{
    char hostbuffer[256];
    struct hostent *host_entry;
    int hostname;
 
    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
 
    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
 
    printf("Hostname: %s\n", hostbuffer);

    // To get CPUid

    if (!cpuid_present()) {
        printf("Sorry, your CPU doesn't support CPUID!\n");
        return -1;
    }

    }

    printf("Processor has %d physical cores\n", data.num_cores);
 
    return 0;
}
