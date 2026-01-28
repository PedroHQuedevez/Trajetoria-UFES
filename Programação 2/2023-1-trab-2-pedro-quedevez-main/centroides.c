#include "centroides.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>

struct grupo_centroides
{
    centroide **centroides;
    int total_grupos;
};

struct centroide
{
    float *array;
    int quant_grupo;
    int grupo;
    int flag_convergiu;
};

struct banco_imagens
{
    imagem **imagens;
    int size;
    int image_size;
};

struct imagem
{
    int *array;
    int count_imagem;
    int grupo;
};

int quant_pixels(char *path)
{
    int quant = 0;
    int lixo;
    char img[500];
    FILE *arq;

    sprintf(img, "%s/%s%d.csv", path, "imagem_", 0);

    arq = fopen(img, "r");

    while (fscanf(arq, "%i,", &lixo) != -1)
    {
        quant++;
    }
    fclose(arq);
    return quant;
}

int quant_imagens(char *path)
{
    DIR *dir;
    struct dirent *entry;
    int quant = 0;

    dir = opendir(path);

    if (dir != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG)
            {
                quant++;
            }
        }
        closedir(dir);
    }
    else
    {
        printf("Erro ao abrir o diretório.\n");
        exit(1);
    }

    // printf("%i\n", quant);
    return quant;
}

banco_imagens *criar_banco_imagens(char *path)
{
    int total_imagens;
    total_imagens = quant_imagens(path); //-1 pro primeiro caso de teste que ta lendo 1 a mais;

    banco_imagens *banco;
    banco = (banco_imagens *)malloc(sizeof(banco_imagens));
    banco->imagens = (imagem **)calloc(total_imagens, sizeof(imagem *));
    banco->size = total_imagens;
    banco->image_size = quant_pixels(path);

    return banco;
}

banco_imagens *ler_banco(banco_imagens *banco, char *path)
{
    FILE *arq;
    char caminho_img[250];

    for (int i = 0; i < (banco->size); i++)
    {
        // printf("%i\n",i);

        sprintf(caminho_img, "%s/%s%d.csv", path, "imagem_", i);

        // printf("%s\n",caminho_img);

        arq = fopen(caminho_img, "r");

        if (arq == NULL)
        {
            printf("erro ao abrir imagem:");
            exit(1);
        }

        banco->imagens[i] = (imagem *)malloc(sizeof(imagem));
        banco->imagens[i]->array = (int *)malloc(banco->image_size * sizeof(int));
        banco->imagens[i]->count_imagem = i;

        for (int j = 0; j < banco->image_size; j++)
        {
            fscanf(arq, "%i,", &banco->imagens[i]->array[j]);
            // fscanf(file,",");
        }

        fclose(arq);
    }
    // printf("CHEGOU0\n");
    return banco;
}

void print_imagem(imagem *i)
{
    for (int j = 0; j < 1024; j++)
    {
        printf("%i\n", i->array[j]);
    }
}

void destroy_imagem(imagem *img)
{
    free(img->array);
    free(img);
}
void destroy_banco(banco_imagens *banco)
{
    for (int i = 0; i < banco->size; i++)
    {
        destroy_imagem(banco->imagens[i]);
        // printf("%i\n",i);
    }
    free(banco->imagens);
    free(banco);
}

centroide *centroide_construct()
{
    centroide *c;
    c = (centroide *)malloc(sizeof(centroide));
    c->quant_grupo = 0;
    c->grupo = 0;
    c->flag_convergiu = 0;
    return c;
}

void destroy_centroide(centroide *c)
{
    free(c->array);
    free(c);
}

grupo_centroides *grupo_construct()
{
    grupo_centroides *grupo = (grupo_centroides *)malloc(sizeof(grupo_centroides));
    grupo->centroides = NULL;
    grupo->total_grupos = 0;
    return grupo;
}

int grupo_vazio(grupo_centroides *grupo)
{
    if (grupo->centroides == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

grupo_centroides *le_centroides(char *path, banco_imagens *banco, grupo_centroides *grupo)
{
    int quant_centroids;

    scanf("\n%i", &quant_centroids);

    grupo->centroides = (centroide **)calloc(quant_centroids, sizeof(centroide *));
    grupo->total_grupos = quant_centroids;

    char caminho_iamgem[250];
    char Nome_img[20];
    FILE *imagem;

    int pixels = banco->image_size;

    for (int i = 0; i < quant_centroids; i++)
    {
        // printf("CHEGOU\n");
        grupo->centroides[i] = centroide_construct();
        grupo->centroides[i]->array = (float *)calloc(pixels, sizeof(float));
        grupo->centroides[i]->grupo = i;
        scanf("\n%s", Nome_img);
        sprintf(caminho_iamgem, "%s/%s.csv", path, Nome_img);

        imagem = fopen(caminho_iamgem, "r");
        if (imagem == NULL)
        {
            printf("erro ao abrir imagem:");
            exit(1);
        }

        for (int j = 0; j < pixels; j++)
        {

            fscanf(imagem, "%f,", &grupo->centroides[i]->array[j]);
        }
        fclose(imagem);
    }
    // printf("CHEGOU8\n");

    int repeticoes;
    float lim_conver;
    char tipo_analise;

    scanf("\n%i", &repeticoes);
    scanf("\n%f", &lim_conver);
    scanf("\n%c", &tipo_analise);
    if (tipo_analise == 'E' || tipo_analise == 'e')
    {
        kmeans(grupo, banco, lim_conver, tipo_analise, repeticoes);
    }
    if (tipo_analise == 'C' || tipo_analise == 'C')
    {
        kmeans_2(grupo, banco, lim_conver, tipo_analise, repeticoes);
    }

    return grupo;
}

void cria_arquivo_centroides(grupo_centroides *grupo, banco_imagens *banco, char *path_saida)
{
    FILE *arq;
    char path_arquivo[200];
    sprintf(path_arquivo, "%s/centroides.csv", path_saida);
    arq = fopen(path_arquivo, "w");

    for (int i = 0; i < grupo->total_grupos; i++)
    {
        fprintf(arq, "%.0f", grupo->centroides[i]->array[0]);
        for (int j = 1; j < banco->image_size; j++)
        {
            fprintf(arq, ",%.0f", grupo->centroides[i]->array[j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}

int dist_euclidiana(int *array1, float *array2, int pixels)
{
    int dist = 0;

    for (int i = 0; i < pixels; i++)
    {
        // printf("CHEGOU3\n");
        dist = dist + ((array1[i] - array2[i]) * (array1[i] - array2[i]));
    }
    return dist;
}

void soma_pixels(int *array1, float *array2, int pixels)
{
    for (int i = 0; i < pixels; i++)
    {
        array2[i] = array2[i] + array1[i];
    }
}

void soma_pixels2(float *array1, float *array2, int pixels)
{
    for (int i = 0; i < pixels; i++)
    {
        array2[i] = array2[i] + array1[i];
    }
}

void kmeans(grupo_centroides *grupo, banco_imagens *banco, int lim_conver, char tipo_analise, int repeticoes)
{
    for (int p = 0; p < repeticoes; p++)
    {
        int agrupamento, menor, dist, pixels, size; // agrupamento vai manter o seu valor na próxima chamada do kmeans?
        pixels = banco->image_size;
        size = banco->size;

        for (int j = 0; j < grupo->total_grupos; j++)
        {
            grupo->centroides[j]->quant_grupo = 1;
        }

        for (int j = 0; j < size; j++)
        {
            menor = dist_euclidiana(banco->imagens[j]->array, grupo->centroides[0]->array, pixels); // manter ordem da entrada
            // printf("CHEGOU4\n");
            agrupamento = 0;
            banco->imagens[j]->grupo = agrupamento;

            for (int i = 0; i < grupo->total_grupos; i++)
            {

                dist = dist_euclidiana(banco->imagens[j]->array, grupo->centroides[i]->array, pixels); // manter ordem da entrada
                // printf("CHEGOU5 %i\n",i);
                if (dist < menor)
                {
                    menor = dist;
                    agrupamento = i;
                    banco->imagens[j]->grupo = agrupamento;
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < grupo->total_grupos; j++)
            {
                if (banco->imagens[i]->grupo == grupo->centroides[j]->grupo)
                {
                    grupo->centroides[j]->quant_grupo++;
                }
            }
        }

        // printf("**************************CHEGOU6\n");
        for (int j = 0; j < size; j++)
        { // somando

            for (int i = 0; i < grupo->total_grupos; i++)
            {

                if (banco->imagens[j]->grupo == grupo->centroides[i]->grupo)
                {

                    soma_pixels(banco->imagens[j]->array, grupo->centroides[i]->array, pixels); // manter ordem da entrada
                }
            }
        }
        // printf("**************************CHEGOU7\n");
        float float_aux;
        int conta_qnts_convergidos = 0;
        centroide *centroide_aux = centroide_construct();
        centroide_aux->array = (float *)calloc(pixels, sizeof(float));
        //////////////////////////////////
        for (int i = 0; i < grupo->total_grupos; i++)
        {
            if (grupo->centroides[i]->quant_grupo == 0)
            {
                grupo->centroides[i]->quant_grupo = 1;
            }

            int count_mudancas = 0;

            for (int j = 0; j < pixels; j++) // atualizando centroide
            {
                float_aux = grupo->centroides[i]->array[j] / grupo->centroides[i]->quant_grupo;
                centroide_aux->array[j] = float_aux;

                if (((centroide_aux->array[j] - grupo->centroides[i]->array[j]) < lim_conver) && ((centroide_aux->array[j] - grupo->centroides[i]->array[j]) > (lim_conver * (-1))))
                {
                    count_mudancas++;
                }
                if (count_mudancas == pixels)
                {
                    grupo->centroides[i]->flag_convergiu = 1;
                }
                grupo->centroides[i]->array[j] = float_aux;
            }
        }

        for (int i = 0; i < grupo->total_grupos; i++)
        {
            if (grupo->centroides[i]->flag_convergiu == 1)
            {
                conta_qnts_convergidos++;
            }
        }
        if (conta_qnts_convergidos == grupo->total_grupos)
        {
            destroy_centroide(centroide_aux);
            break;
        }
        destroy_centroide(centroide_aux);
    }
}

float cos_fun(float *array1, float *array2, int pixels)
{
    float coss_calc = 0;
    float produto_linear = 0;
    float som_raizes_quadrados = 0;
    float som_quad1 = 0;
    float som_quad2 = 0;

    for (int i = 0; i < pixels; i++)
    {
        produto_linear = produto_linear + ((array1[i] / 255) * (array2[i] / 255));
        som_quad1 = som_quad1 + ((array1[i] / 255) * (array1[i] / 255));
        // printf("*%f\n", array1[i] / 255);
        // printf("**%f\n", array2[i] / 255);
        som_quad2 = som_quad2 + ((array2[i] / 255) * (array2[i] / 255));
    }
    // printf("%f\n", produto_linear);
    // printf("%f\n", som_quad1);
    // printf("%f\n", som_quad2);
    coss_calc = produto_linear / (((pow(som_quad1, (1 / 2))) * (pow(som_quad2, (1 / 2)))));
    return coss_calc;
}

void kmeans_2(grupo_centroides *grupo, banco_imagens *banco, int lim_conver, char tipo_analise, int repeticoes)
{
    for (int p = 0; p < repeticoes; p++)
    {
        int agrupamento, pixels, size;

        float maior;
        float dist;
        pixels = banco->image_size;
        size = banco->size;

        for (int j = 0; j < grupo->total_grupos; j++)
        {
            grupo->centroides[j]->quant_grupo = 1;
        }

        for (int j = 0; j < size; j++)
        {

            float *array_copy = (float *)calloc(pixels, sizeof(float));

            for (int l = 0; l < size; l++)
            {
                array_copy[l] = banco->imagens[j]->array[l];
            }

            maior = cos_fun(array_copy, grupo->centroides[0]->array, pixels); // manter ordem da entrada
            // printf("CHEGOU4\n");
            agrupamento = 0;
            banco->imagens[j]->grupo = agrupamento;

            for (int i = 0; i < grupo->total_grupos; i++)
            {

                dist = cos_fun(array_copy, grupo->centroides[i]->array, pixels); // manter ordem da entrada
                // printf("CHEGOU5 %i\n",i);
                if (dist > maior)
                {

                    maior = dist;
                    agrupamento = i;
                    banco->imagens[j]->grupo = agrupamento;
                }
            }
            free(array_copy);
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < grupo->total_grupos; j++)
            {
                if (banco->imagens[i]->grupo == grupo->centroides[j]->grupo)
                {
                    grupo->centroides[j]->quant_grupo++;
                }
            }
        }

        // printf("**************************CHEGOU6\n");
        for (int j = 0; j < size; j++)
        { // somando

            for (int i = 0; i < grupo->total_grupos; i++)
            {

                if (banco->imagens[j]->grupo == grupo->centroides[i]->grupo)
                {
                    float *array_copy2 = (float *)calloc(pixels, sizeof(float));

                    for (int l = 0; l < size; l++)
                    {
                        array_copy2[l] = banco->imagens[j]->array[l];
                    }
                    soma_pixels2(array_copy2, grupo->centroides[i]->array, pixels); // manter ordem da entrada
                    free(array_copy2);
                }
            }
        }
        // printf("**************************CHEGOU7\n");
        float float_aux;
        int conta_qnts_convergidos = 0;
        centroide *centroide_aux = centroide_construct();
        centroide_aux->array = (float *)calloc(pixels, sizeof(float));

        //////////////////////////////////
        for (int i = 0; i < grupo->total_grupos; i++)
        {
            if (grupo->centroides[i]->quant_grupo == 0)
            {
                grupo->centroides[i]->quant_grupo = 1;
            }

            int count_mudancas = 0;

            for (int j = 0; j < pixels; j++) // atualizando centroide
            {
                float_aux = grupo->centroides[i]->array[j] / grupo->centroides[i]->quant_grupo;
                centroide_aux->array[j] = float_aux;

                if (((centroide_aux->array[j] - grupo->centroides[i]->array[j]) < lim_conver) && ((centroide_aux->array[j] - grupo->centroides[i]->array[j]) > (lim_conver * (-1))))
                {
                    count_mudancas++;
                }
                if (count_mudancas == pixels)
                {
                    grupo->centroides[i]->flag_convergiu = 1;
                }
                grupo->centroides[i]->array[j] = float_aux;
            }
        }

        for (int i = 0; i < grupo->total_grupos; i++)
        {
            if (grupo->centroides[i]->flag_convergiu == 1)
            {
                conta_qnts_convergidos++;
            }
        }
        if (conta_qnts_convergidos == grupo->total_grupos)
        {
            destroy_centroide(centroide_aux);
            break;
        }
        destroy_centroide(centroide_aux);
    }
}

void print_centroide(centroide *c, int pixels)
{
    for (int i = 0; i < pixels; i++)
    {
        printf("%.3f\n", c->array[i]);
    }
}

void centroid_group_destroy(grupo_centroides *grupo)
{
    for (int i = 0; i < grupo->total_grupos; i++)
    {
        destroy_centroide(grupo->centroides[i]);
    }
    free(grupo->centroides);
    free(grupo);
}

void centroid_group_clear(grupo_centroides *grupo)
{
    for (int i = 0; i < grupo->total_grupos; i++)
    {
        destroy_centroide(grupo->centroides[i]);
    }
    free(grupo->centroides);
}

int retorna_grupo(imagem *img)
{
    return img->grupo;
}

int retorna_tam_img(banco_imagens *banco)
{
    return banco->image_size;
}

int retorna_quant_grupos(grupo_centroides *grupo)
{
    return grupo->total_grupos;
}

float *retorna_array_centroide(grupo_centroides *c, int indice)
{
    return c->centroides[indice]->array;
}