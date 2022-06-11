# Madelbrot Fractal Paralelo

Esse repositório é um projeto para a cadeira de Computação Avançada. Foi desenvolvido em C, para criar imagens do formato bmp criadas a partir do paralelismo do [Mandelbrot Fractal](https://en.wikipedia.org/wiki/Mandelbrot_set). Foi utilizado pthreads e mutex para realizar o lock e unlock das mesmas.

## Uso

```shell
# Se quiser executar o Makefile
make
```

```shell
# Senão
gcc mandel.o bitmap.o -o mandel -lpthread
gcc -Wall -g -c mandel.c -o mandel.o
gcc -Wall -g -c bitmap.c -o bitmap.o

# Executa
./mandel [opções]
```

### Possíveis parâmetros

| Comando | O que é                                       | Valor default |
| ------- | --------------------------------------------- | ------------- |
| -n      | Número the threads                            | 1             |
| -m      | Número máximo de iterações por ponto          | 1000          |
| -x      | Coordenada X do centro da imagem              | 0             |
| -y      | Coordenada Y do centro da imagem              | 0             |
| -e      | Escala da imagem em coordenadas de Mandlebrot | 4             |
| -L      | Largura da imagem em pixels                   | 500           |
| -A      | Altura da imagem em pixels                    | 500           |
| -h      | Mostra as opções                              | NA            |

### Exemplo de comando e imagem gerada

```shell
./mandel -e 2 -n 20
```

<img width="498" alt="image" src="https://user-images.githubusercontent.com/38566830/173098656-53e4f117-0b27-4ce6-94a1-c56cbc3cd6c6.png">

```shell
./mandel -x 0.286932 -y 0.014287 -e .0005 -m 1000 -n 10
```

<img width="494" alt="image" src="https://user-images.githubusercontent.com/38566830/173096738-37a05bf9-d9bd-4c65-892d-23092e152df7.png">

```shell
./mandel -x -0.5 -y -0.5 -e 0.25 -n 10
```

<img width="495" alt="image" src="https://user-images.githubusercontent.com/38566830/173097189-01d4c070-1b76-48d5-bafc-6ece128e3620.png">

```shell
./mandel -x -0.5 -y -0.5 -e 0.025 -n 10
```

![image](https://user-images.githubusercontent.com/38566830/173097411-250efca0-ea0a-42c8-bcd5-a7fcfe5b0b8e.png)

### Exemplo de output

Execução

```shell
./mandel -x 0.286932 -y 0.014287 -e .0005 -m 1000 -n 10 -L 2000 -A 2000
```

```
Mandelbrot a ser gerado: x=-0.500000 y=-0.500000 escala=0.025000 max=1000 threads=10 outfile=mandelbrot_pthread.bmp
Criado bitmap de altura 2000 e largura 2000
-Inicialização do mutex com sucesso

-----
A thread 0 foi criada.

-----
A thread 1 foi criada.
Mutex da thread 0 lock
Thread número: 0 -> desenha da altura inicial 0 a altura final 200.

-----
A thread 2 foi criada.

-----
A thread 3 foi criada.

-----
A thread 4 foi criada.

-----
A thread 5 foi criada.

-----
A thread 6 foi criada.

-----
A thread 7 foi criada.

-----
A thread 8 foi criada.

-----
A thread 9 foi criada.
Mutex da thread 0 unlock

Mutex da thread 2 lock
Thread número: 2 -> desenha da altura inicial 400 a altura final 600.
Thread número 0 fez pthread_join com sucesso.

-----
1 threads finalizaram.

Mutex da thread 2 unlock

Mutex da thread 1 lock
Thread número: 1 -> desenha da altura inicial 200 a altura final 400.
Mutex da thread 1 unlock

Mutex da thread 3 lock
Thread número: 3 -> desenha da altura inicial 600 a altura final 800.
Thread número 1 fez pthread_join com sucesso.

-----
2 threads finalizaram.

Thread número 2 fez pthread_join com sucesso.

-----
3 threads finalizaram.

Mutex da thread 3 unlock

Mutex da thread 4 lock
Thread número: 4 -> desenha da altura inicial 800 a altura final 1000.
Thread número 3 fez pthread_join com sucesso.

-----
4 threads finalizaram.

Mutex da thread 4 unlock

Mutex da thread 5 lock
Thread número: 5 -> desenha da altura inicial 1000 a altura final 1200.
Thread número 4 fez pthread_join com sucesso.

-----
5 threads finalizaram.

Mutex da thread 5 unlock

Mutex da thread 6 lock
Thread número: 6 -> desenha da altura inicial 1200 a altura final 1400.
Thread número 5 fez pthread_join com sucesso.

-----
6 threads finalizaram.

Mutex da thread 6 unlock

Mutex da thread 7 lock
Thread número: 7 -> desenha da altura inicial 1400 a altura final 1600.
Thread número 6 fez pthread_join com sucesso.

-----
7 threads finalizaram.

Mutex da thread 7 unlock

Mutex da thread 8 lock
Thread número: 8 -> desenha da altura inicial 1600 a altura final 1800.
Thread número 7 fez pthread_join com sucesso.

-----
8 threads finalizaram.

Mutex da thread 8 unlock

Mutex da thread 9 lock
Thread número: 9 -> desenha da altura inicial 1800 a altura final 2000.
Thread número 8 fez pthread_join com sucesso.

-----
9 threads finalizaram.

Mutex da thread 9 unlock

Thread número 9 fez pthread_join com sucesso.

-----
10 threads finalizaram.
```

## Projeto sequencial

O projeto sequencial foi retirado de [Project 3: Parallel Mandelbrot](https://www3.nd.edu/~dthain/courses/cse30341/spring2018/project3/)
