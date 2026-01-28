#ifndef _CENTROIDES_H
#define _CENTROIDES_H

typedef struct centroide centroide;
typedef struct grupo_centroides grupo_centroides;

typedef struct imagem imagem;
typedef struct banco_imagens banco_imagens;

int quant_imagens(char *path);
banco_imagens *criar_banco_imagens(char *path);
banco_imagens *ler_banco(banco_imagens *banco, char *path);
void destroy_banco(banco_imagens *banco);
int quant_pixels(char *path);
// int retorna_banco_image_size (banco_imagens *b);
// int retorna_banco_size (banco_imagens *b);

grupo_centroides *grupo_construct();
grupo_centroides *le_centroides(char *path, banco_imagens *banco, grupo_centroides *grupo);
void kmeans(grupo_centroides *grupo, banco_imagens *banco, int lim_conv, char tipo, int repeticoes);
void kmeans_2(grupo_centroides *grupo, banco_imagens *banco, int lim_conver, char tipo_analise, int repeticoes);
void print_centroide(centroide *c, int pixels);
void centroid_group_destroy(grupo_centroides *grupo);
void centroid_group_clear(grupo_centroides *grupo);
void cria_arquivo_centroides(grupo_centroides *grupo, banco_imagens *banco, char *path_saida);
int grupo_vazio(grupo_centroides *grupo);
float cos_fun(float *array1, float *array2, int pixels);

int dist_euclidiana(int *array1, float *array2, int pixels);
int retorna_grupo(imagem *img);
int retorna_tam_img(banco_imagens *banco);
int retorna_quant_grupos(grupo_centroides *grupo);
float *retorna_array_centroide(grupo_centroides *c, int indice);

#endif
