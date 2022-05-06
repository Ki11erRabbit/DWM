#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *discord = "ps Huh p $(pidof Discord) | wc -l";
    int discordTheadCount = 0;
    int sum = 0;
    unsigned int count = 0;
    int averageThreadCount = 132;
    char *sigCommand = "kill -43 $(pidof dwmblocks) >/dev/null;";
    char *Share = "echo '🖥️' > /tmp/recordingicon";
    char *Record = "echo '🔴🖥️' > /tmp/recordingicon";
    char *clearIcon = "echo '' > /tmp/recordingicon";
    char buf[50];
    FILE *fp;
//usually goes no lower than 140 threads for screensharing

    while (1) {
    	if ((fp = popen(discord, "r")) == NULL) {
            printf("Error opening pipe!\n");
            return -1;
    	}
	
	if (fgets(buf, 50, fp)) {
	    discordTheadCount = atoi(buf);
	    //printf("%d\n", averageThreadCount);
	    if (discordTheadCount < 138) {
		sum += discordTheadCount;
		count++;
		averageThreadCount = sum / count;
		system(clearIcon);
		system(sigCommand);
	    }
	    else if (discordTheadCount - averageThreadCount > 5) {
		system(Share);
		system(sigCommand);
	    }
	    else {
		sum += discordTheadCount;
		count++;
		averageThreadCount = sum / count;
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
