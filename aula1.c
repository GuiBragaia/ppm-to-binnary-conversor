#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct {
    unsigned char r, g, b;
} Pixel;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char magic[MAX_SIZE];
    int width, height, maxval;
    fscanf(input, "%s\n%d %d\n%d\n", magic, &width, &height, &maxval);
    if (strcmp(magic, "P3") != 0) {
        printf("Erro: o arquivo não é um ppm em formato ASCII.\n");
        return 1;
    }

    Pixel *image = (Pixel*) malloc(width * height * sizeof(Pixel));
    if (!image) {
        printf("Erro ao alocar a imagem.\n");
        return 1;
    }

    for (int i = 0; i < width * height; i++) {
        int r, g, b;
        fscanf(input, "%d %d %d", &r, &g, &b);
        image[i].r = (unsigned char) r;
        image[i].g = (unsigned char) g;
        image[i].b = (unsigned char) b;
    }

    fclose(input);

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }


    fprintf(output, "P6\n%d %d\n%d\n", width, height, maxval);


    for (int i = 0; i < width * height; i++) {
        fputc(image[i].r, output);
        fputc(image[i].g, output);
        fputc(image[i].b, output);
    }

 
    fclose(output);

    
    free(image);

    return 0;
}
