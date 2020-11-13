#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/wireless.h>
#include <errno.h>

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Bad usage\n");
		fprintf(stderr, "Usage: %s ifname\n", argv[0]);
		return -1;
	}

	struct iwreq req;
	strcpy(req.ifr_ifrn.ifrn_name, argv[1]);
	int fd, status;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	char* buffer;
	buffer = calloc(32, sizeof(char));
	req.u.essid.pointer = buffer;
	req.u.essid.length = 32;
	if (ioctl(fd, SIOCGIWESSID, &req) == -1) {
		fprintf(stderr, "Failed ESSID get on interface %s: %s\n", argv[1], strerror(errno));
	} else {
		printf("%s", (char*)req.u.essid.pointer);
	}
	free(buffer);
}
