/*
 * Small tool to run command as non-priviledged user inboot script.
 *
 * (c) 2020 Christophe BLAESS <christophe.blaess@logilin.fr>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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

