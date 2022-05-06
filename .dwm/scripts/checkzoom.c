#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *zoom = "ps Huh p $(pidof zoom) | wc -l";
    int zoomTheadCount = 0;
    char *sigCommand = "kill -43 $(pidof dwmblocks) >/dev/null;";
    char *zoomShare = "echo '🖥️' > /tmp/recordingicon";
    char *zoomRecord = "echo '🔴🖥️' > /tmp/recordingicon";
    char *clearIcon = "echo '' > /tmp/recordingicon";
    char buf[50];
    FILE *fp;


    while (1) {
    	if ((fp = popen(zoom, "r")) == NULL) {
            printf("Error opening pipe!\n");
            return -1;
    	}
	
	if (fgets(buf, 50, fp)) {
	    zoomTheadCount = atoi(buf);
	    printf("%d", zoomTheadCount);
	    if (zoomTheadCount > 105) {
		system(zoomRecord);
		system(sigCommand);
	    }
	    else if (zoomTheadCount >100 ) {
		system(zoomShare);
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
