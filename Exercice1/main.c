#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
static const char tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64_encode(char *dst, int size, char *src);

int main(void)
{
    int size = 0;
    int i;
    char *encode = NULL;
    char *mdp[50]={0};
    fgets(mdp, 50, stdin);
    for(i=0; mdp[i]!= '\0'; i++);
    mdp[i] = '\0';

    size = 4 * ((strlen(mdp) + 2) / 3);

    base64_encode(encode, size, mdp);

    printf("\nmdp = %s\n", mdp);
    printf("encode = %s", encode);
    free(encode);
    return (0);
}

int base64_encode(char *dst, int size, char *src)
{

    static int mod_table[] = {0, 2, 1};
    int str_size = strlen(src);
    int i = 0;
    int j = 0;
    int oct_a = 0;
    int oct_b = 0;
    int oct_c = 0;
    int triple = 0;


    dst = malloc(sizeof(char) * (size+1));
    for (; i < str_size;) {
        oct_a = i < str_size ? src[i++] : 0;            //si i < str_size alors oct_a = src[i++] else oct_a = 0
        oct_b = i < str_size ? src[i++] : 0;
        oct_c = i < str_size ? src[i++] : 0;
        triple = (oct_a << 16) + (oct_b << 8) + oct_c;
        dst[j++] = tab[(triple >> 18) & 63];
        dst[j++] = tab[(triple >> 12) & 63];
        dst[j++] = tab[(triple >> 6) & 63];
        dst[j++] = tab[(triple) & 63];
    }

     for (i = 0; i < mod_table[size % 3]; i++)
        dst[size-1 - i] = '=';
    dst[size]='\0';
    printf("dst = %s", dst);
    return (0);
}
