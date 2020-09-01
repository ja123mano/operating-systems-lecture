#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>

int main (int argc, char *argv[]) {
	long rc = -420;
	struct passwd *pass;

	if (argc == 3 && argv[2][0] != '\0') {

		pass = getpwnam(argv[2]);

		if (pass == NULL) {
			fprintf(stderr, "Error: El usuario no se encontró (argumento [2])\n");
			exit(0);
		} else {
			rc = chown(argv[1], pass -> pw_uid, -1); 
		}
	}

	if (rc < 0) {
		fprintf (stderr, "Error.  #error = %d\n",errno);
		exit(0);
	}

	return 0; 
}

