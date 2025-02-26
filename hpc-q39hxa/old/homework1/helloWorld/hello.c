#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* run_command(char com[]){
    FILE *fp;
    char res[30];

    /* Open the command for reading. */
    fp = popen(com, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
        }
    /* Read the output a line at a time - output it. */
    while (fgets(res, sizeof(res), fp) != NULL) {
//        printf("%s", hs);
        res[strcspn(res, "\n")] = 0;
    }

    /* close */
    pclose(fp);
    return res;
}


int main()
{
    char hs[30];
    strcpy(hs,run_command("hostname"));
    char* cpuid = run_command("cat /proc/cpuinfo | grep processor | wc -l");
    printf("Hello World from %s CPU %s \n", hs,cpuid);
    return 0;
}
