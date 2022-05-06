#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *obs = "pidof obs-ffmpeg-mux | wc -l";
    int pidOBS = 0;
    char *sigCommand = "kill -43 $(pidof dwmblocks) >/dev/null;";
    char *obsrecCommand = "echo '🔴🖥️' > /tmp/recordingicon";
    char *clearIcon = "echo '' > /tmp/recordingicon";
    char buf[50];
    FILE *fp;
    unsigned int count=0;


    while (1) {
    	if ((fp = popen(obs, "r")) == NULL) {
            printf("Error opening pipe!\n");
            return -1;
    	}
	
	if (fgets(buf, 50, fp)) {
	    pidOBS = atoi(buf);
	    printf("%d", pidOBS);
	    if (pidOBS) {
		system(obsrecCommand);
		system(sigCommand);
	    }
	    else {
		system(clearIcon);
		system(sigCommand);
	    }
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
