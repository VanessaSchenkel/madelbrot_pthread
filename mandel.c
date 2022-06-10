#include "bitmap.h"

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

struct thread_args
{
    struct bitmap *bitmap;
    double x_inicial, x_final, y_inicial, y_final;
    int max, thread_num, total_threads;
};

pthread_mutex_t mutex;

int iteration_to_color(int i, int max);
int iterations_at_point(double x, double y, int max);
void *compute_image(struct thread_args *args);

void show_help()
{
    printf("Use: ./mandel [opção]\n");
    printf("-n <num>      Número de threads. (default=1)\n");
    printf("-m <max>      O número máximo de iterações por ponto. (default=1000)\n");
    printf("-x <coord>    Coordenada X do centro da imagem. (default=0)\n");
    printf("-y <coord>    Cordenada Y do centro da imagem. (default=0)\n");
    printf("-e <escala>   Escala da imagem em coordenadas de Mandlebrot. (default=4)\n");
    printf("-L <pixels>   Largura da imagem em pixels. (default=500)\n");
    printf("-A <pixels>   Altura da imagem em pixels. (default=500)\n");
    printf("-h            Mostrar ajuda.\n");
    printf("\nAlguns exemplos de uso:\n");
    printf("./mandel -e 2 -n 20\n");
    printf("./mandel -x -0.5 -y -0.5 -e 0.25 -n 10\n\n");
    printf("./mandel -x 0.286932 -y 0.014287 -e .0005 -m 1000 -n 10\n\n");
    printf("./mandel -x -0.5 -y -0.5 -e 0.025 -n 10\n\n");
}

int main(int argc, char *argv[])
{
    char c;

    struct thread_args *args;
    pthread_t *tid; // identificador único das threads
    int threads_completas = 0;

    // Pega o horário para acrescentar no nome da imagem
    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    printf("Hora: %d:%d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);

    const char *outfile = "mandelbrot_pthread.bmp";

    // Valores default caso não sejam passados
    double x_centro = 0;
    double y_centro = 0;
    double escala = 4;
    int largura_img = 500;
    int altura_img = 500;
    int max = 1000;
    int threads = 1;

    while ((c = getopt(argc, argv, "x:y:e:L:A:m:n:h")) != -1)
    {
        switch (c)
        {
        case 'x':
            x_centro = atof(optarg);
            break;
        case 'y':
            y_centro = atof(optarg);
            break;
        case 'e':
            escala = atof(optarg);
            break;
        case 'W':
            largura_img = atoi(optarg);
            break;
        case 'H':
            altura_img = atoi(optarg);
            break;
        case 'm':
            max = atoi(optarg);
            break;
        case 'n':
            threads = atoi(optarg);
            break;
        case 'h':
            show_help();
            exit(1);
            break;
        }
    }

    // Mostra a configuração da imagem
    printf("mandelbrot a ser gerado: x=%lf y=%lf escala=%lf max=%d threads=%d outfile=%s\n", x_centro, y_centro, escala, max, threads, outfile);

    // Cria o bitmap conforme tamanho passado
    struct bitmap *bitmap = bitmap_create(largura_img, altura_img);

    // Preenche o bitmap de azul escuro
    bitmap_reset(bitmap, MAKE_RGBA(0, 0, 255, 0));

    // Computa a imagem com threads
    int i = 0;
    int valor_retorno;

    pthread_mutex_init(&mutex, NULL);

    // Aloca espaço na memória
    args = malloc(sizeof(struct thread_args) * threads);
    tid = malloc(sizeof(pthread_t) * threads);

    for (i = 0; i < threads; i++)
    {
        if (i >= threads)
        {
            break;
        }

        args[i].bitmap = bitmap;
        args[i].x_inicial = x_centro - escala;
        args[i].x_final = x_centro + escala;
        args[i].y_inicial = y_centro - escala;
        args[i].y_final = y_centro + escala;
        args[i].max = max;

        args[i].thread_num = i + threads_completas;
        args[i].total_threads = threads;

        /* Cria um novo fluxo de execução (uma nova thread). O novo fluxo executa de forma concorrente com a thread criadora.
            tid -> identificador único da nova thread
            compute_image -> nome da função que contém o código a ser executado pela thread
            args: ponteiro para uma região de memória com dados de entrada para a função
        */
        valor_retorno = pthread_create(&tid[i], NULL, (void *)&compute_image, (void *)&args[i]);
        if (valor_retorno < 0)
        {
            printf("Erro pthread_create: %s\n", strerror(errno));
            i--; // tenta de novo
        }

        printf("A thread %d foi gerada.\n", i);
    }

    for (i = 0; i < threads; i++)
    {
        if (i >= threads) // não precisa de mais threads
        {
            break;
        }
        /* Faz a sincronização, aguarda o término de uma thread (se ela não terminou) e recupera o resultado produzido
                tid: identificador da thread a ter seu término sincronizado
            Se tid não terminou, a chamadora espera bloqueada até o término
         */
        valor_retorno = pthread_join(tid[i], NULL);

        // Se completa o join com sucesso, retorna 0
        if (valor_retorno < 0)
        {
            printf("Erro pthread_join: : %s\n", strerror(errno));
        }
        else
        {
            printf("Thread número %d fez pthread_join com sucesso.\n", i);
            threads_completas++;
            printf("%d threads finalizaram.\n", threads_completas);
        }
    }
    // Libera espaço
    free(tid);
    free(args);

    if (!bitmap_save(bitmap, outfile))
    {
        return 1;
    }

    return 0;
}

/*
Computa a imagem inteira, escrevendo cada ponto no bitmap
*/
void *compute_image(struct thread_args *args)
{
    int i, j;

    int largura = bitmap_width(args->bitmap);
    int altura = bitmap_height(args->bitmap);

    // Para cada pixel da imagem
    int altura_inicial = (int)(((double)args->thread_num / (double)args->total_threads) * altura);
    int altura_final;

    // Verifica se é a última thread
    if (args->thread_num == args->total_threads - 1)
    {
        altura_final = altura;
    }
    else
    {
        altura_final = altura_inicial + (altura / args->total_threads);
    }

    printf("Thread número: %d -> desenhando do pixels %d ao pixel %d.\n", args->thread_num, altura_inicial, altura_final);

    for (j = altura_inicial; j < altura_final; j++)
    {

        for (i = 0; i < largura; i++)
        {
            pthread_mutex_lock(&mutex);

            // Determina o ponto no espaço x,y para o pixel
            double x = (args->x_inicial) + i * ((args->x_final) - (args->x_inicial)) / largura;
            double y = (args->y_inicial) + j * ((args->y_final) - (args->y_inicial)) / altura;

            // Computa a interação neste ponto
            int iteracao = iterations_at_point(x, y, (args->max));

            // Seta o pixel no bitmap.
            bitmap_set((args->bitmap), i, j, iteracao);

            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

/*
Retorna o número de iterações no ponto x,y
*/
int iterations_at_point(double x, double y, int max)
{
    double x0 = x;
    double y0 = y;

    int iter = 0;

    while ((x * x + y * y <= 4) && iter < max)
    {

        double xt = x * x - y * y + x0;
        double yt = 2 * x * y + y0;

        x = xt;
        y = yt;

        iter++;
    }

    return iteration_to_color(iter, max);
}

/*
Converte para uma cor RGBA
*/
int iteration_to_color(int i, int max)
{
    int r = 215 * i / max;
    int g = 60 * i / max;
    int b = 112 * i / max;
    return MAKE_RGBA(r, g, b, 0);
}
