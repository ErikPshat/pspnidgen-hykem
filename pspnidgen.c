// Copyright (C) 2013       Hykem <hykem@hotmail.com>
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/gpl-2.0.txt

#include <stdio.h>
#include <string.h>
#include "sha1.h"

int main(int argc, char **argv)
{
    if (argc <= 1){
        printf("Usage: pspnidgen <input> <output>\n");
        return 0;
    }

    FILE* input = fopen(argv[1], "rb");
    FILE* output = fopen(argv[2], "wb");
    unsigned char line[256];
	unsigned char hash[20];
	unsigned char nid[4];
	memset(line, 0, 256);
	memset(hash, 0, 20);
	memset(nid, 0, 4);

    while (fgets(line, sizeof(line), input)) {
		sha1(line, strlen(line) - 1, hash);
		nid[0] = hash[3];
		nid[1] = hash[2];
		nid[2] = hash[1];
		nid[3] = hash[0];
		fprintf(output, "0x");
		int i;
		for(i = 0; i < 4; i++) fprintf(output, "%02X", nid[i]);
		fprintf(output, " %s", line);
    }

    fclose(input);
    fclose(output);
    return 0;
}
