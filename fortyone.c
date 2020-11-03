#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#define MAXBUFLEN 1000000
void printAscii(char *line[]);
int main(int argc, char **argv) {
	// Check if file exists..
	if(argc <= 1) {
		printf("Not enough args...\n");
		exit(1);
	}
	FILE* fp;
	if((fp = fopen(argv[1], "rb")) == NULL) {
		printf("[!]Unable to open file. \n");
		exit(1);
	}
	struct stat stat;
	int fd;
    	//get file descriptor
	fstat(fd, &stat);
	//the size of the file is now in stat.st_size
	if(!S_ISREG(stat.st_mode)) {
		printf("File is not a compatiable file.\n");
	}
	unsigned char hex[1024] = "";
	size_t bytes = 0;
	int each = 0;
	// Read 1024 bytes into hex buffer from file pointer.
	while ( ( bytes = fread ( &hex, 1, 1024, fp)) > 0) {
		for ( each = 0; each < bytes; each++) {
			printf("%0.2x ", hex[each]);
			if ((each % 8) == 0) {
				printf("  ");
			}
			if((each % 16) == 0) {
				printf("	");
				for( int j = each-16; j < each; j++){
					if (hex[j] < 0x1F|| hex[j] > 0x7E) {
						printf(".");
						continue;
					}
					printf("%c", hex[j]);
				}
				printf("\n");
			}

		}
    	}
    fclose ( fp);
    printf("\nFile Read Successfully!\n");
    return 0;
}
