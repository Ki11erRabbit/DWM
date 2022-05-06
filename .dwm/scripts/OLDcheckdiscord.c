#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    char *discord1 = "ps aux | grep Discord | awk '/video/ {print $13}' | wc -c";
    char *discord = "pgrep Discord | wc -l";
    char *discord2 = "kill -9 $(pgrep Discord | tail -n 1); notify-send 'killed'";
    char discordCount = 0;
    char *sigCommand = "kill -43 $(pidof dwmblocks) >/dev/null;";
    char *discordShare = "echo '🖥️' > /tmp/recordingicon";
    char *clearIcon = "echo '' > /tmp/recordingicon";
    char buf[50];
    FILE *fp;
    unsigned int count=0;


    while (1) {
    	if ((fp = popen(discord, "r")) == NULL) {
            printf("Error opening pipe!\n");
            return -1;
    	}

	if (fgets(buf, 50, fp)) {
		printf("%s", buf);
	    if (buf[0] == '9') {
		sleep(3);
		system(discord2);	
		discordCount++;
		//printf("%d\n", discordCount);
	    }
	    if (discordCount == 2) {
		system(discordShare);
	    }
	    else if (discordCount == 3) {
		system(clearIcon);
		count++;
	    }
	    else if (discordCount == 4) {
		discordCount = 0;
		count = 0;
	    }
	    else {
		count++;
	    }
	    if (count == 1800) {
	        discordCount = 0;
  		count = 0;
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
