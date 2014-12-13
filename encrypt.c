#include <stdio.h>
#include <stdlib.h>

#define SUCESS 0
#define FAIL 1
#define BITS 8

int main(int argc, char **argv) {
    /* simple arg check */
    if (argc != 2) {
        fprintf(stderr, "error: cat FILE_PLAIN | %s PASSWORD > FILE_ENC\n",
                argv[0]);
        return FAIL;
    }

    /* get seed from first argument */
    char *pw = argv[1];
    unsigned int pw_seed = 0;
    int pw_seed_byte_num = 0;
    int c;
    for (c = 0; pw[c] != '\0'; c++) {
        if (pw_seed_byte_num < sizeof(unsigned int)) {
            pw_seed = pw_seed ^ (unsigned char)pw[c];
            pw_seed = pw_seed << (pw_seed_byte_num * BITS);
            pw_seed_byte_num++;
        } else {
            pw_seed_byte_num = 0;
        }
    }

    /* encrypt */
    long int buff = 0;
    size_t n;
    while ((n = fread(&buff, sizeof(long int), 1, stdin))) {
        srandom(pw_seed);
        buff = buff ^ random();
        fwrite(&buff, sizeof(long int), 1, stdout);
    }

    return SUCESS;
}
