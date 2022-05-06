#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *cmd = "pactl list short | grep RUNNING | awk '/input/ {print $2}' | wc -c";
    char *sigCommand = "kill -47 $(pidof dwmblocks) >/dev/null";
    char buf[50];
    FILE *fp;

    while (1) {
    	if ((fp = popen(cmd, "r")) == NULL) {
            printf("Error opening pipe!\n");
            return -1;
    	}

	if (fgets(buf, 50, fp)) {
	    system(sigCommand);
	    sleep(1);
	}
	else {
	   sleep(1); 
	}
	if (pclose(fp)) {
        printf("Command not found or exited with error status\n");
        return -1;
    }
    }
    return 0;
}
