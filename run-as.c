#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	struct passwd *pwd;
	struct group  *grp;
	int uid;
	int gid;

	if (argc != 4) {
		fprintf(stderr, "Usage: run-as <user> <group> <command line>\n");
		exit(EXIT_FAILURE);
	}

	if (sscanf(argv[1], "%d", &uid) != 1) {
		pwd = getpwnam(argv[1]);
		if (pwd == NULL) {
			fprintf(stderr, "%s: invalid U-ID or user name: %s\n", argv[0], argv[1]);
			exit(EXIT_FAILURE);
		}
		uid = pwd->pw_uid;
	}

	if (sscanf(argv[2], "%d", &gid) != 1) {
		grp = getgrnam(argv[2]);
		if (grp == NULL) {
			fprintf(stderr, "%s: invalid G-ID or group name: %s\n", argv[0], argv[2]);
			exit(EXIT_FAILURE);
		}
		gid = grp->gr_gid;
	}

	if (setregid(gid, gid) != 0) {
		fprintf(stderr, "%s: unable to set G-ID.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (setreuid(uid, uid) != 0) {
		fprintf(stderr, "%s: unable to set U-ID.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	return system(argv[3]);
}

