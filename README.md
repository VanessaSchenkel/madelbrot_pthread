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

| Comando       | O que é                                       |  Valor default |
| ------------- | --------------------------------------------- |--------------- |
| -n            | Número the threads                            |  1             |
| -m            | Número máximo de iterações por ponto          |    1000        |
| -x            | Coordenada X do centro da imagem              |  0             |
| -y            | Coordenada Y do centro da imagem              |  0             |
| -e.           | Escala da imagem em coordenadas de Mandlebrot | 4              |
| -L            | Largura da imagem em pixels                   | 500            |
| -A            | Altura da imagem em pixels                    | 500            |
| -h.           | Mostra as opções                              | NA             |



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
```
Hora: 12:23:57
mandelbrot a ser gerado: x=0.000000 y=0.000000 escala=2.000000 max=1000 threads=20 outfile=mandelbrot_pthread.bmp
A thread 0 foi gerada.
Thread número: 0 -> desenhando do pixels 0 ao pixel 25.
Thread número: 1 -> desenhando do pixels 25 ao pixel 50.
A thread 1 foi gerada.
A thread 2 foi gerada.
A thread 3 foi gerada.
A thread 4 foi gerada.
Thread número: 2 -> desenhando do pixels 50 ao pixel 75.
A thread 5 foi gerada.
A thread 6 foi gerada.
Thread número: 3 -> desenhando do pixels 75 ao pixel 100.
A thread 7 foi gerada.
A thread 8 foi gerada.
Thread número: 4 -> desenhando do pixels 100 ao pixel 125.
A thread 9 foi gerada.
Thread número: 5 -> desenhando do pixels 125 ao pixel 150.
Thread número: 6 -> desenhando do pixels 150 ao pixel 175.
Thread número: 8 -> desenhando do pixels 200 ao pixel 225.
Thread número: 9 -> desenhando do pixels 225 ao pixel 250.
Thread número: 10 -> desenhando do pixels 250 ao pixel 275.
Thread número: 7 -> desenhando do pixels 175 ao pixel 200.
A thread 10 foi gerada.
A thread 11 foi gerada.
A thread 12 foi gerada.
A thread 13 foi gerada.
A thread 14 foi gerada.
A thread 15 foi gerada.
A thread 16 foi gerada.
A thread 17 foi gerada.
A thread 18 foi gerada.
A thread 19 foi gerada.
Thread número: 11 -> desenhando do pixels 275 ao pixel 300.
Thread número: 13 -> desenhando do pixels 325 ao pixel 350.
Thread número: 14 -> desenhando do pixels 350 ao pixel 375.
Thread número: 15 -> desenhando do pixels 375 ao pixel 400.
Thread número: 16 -> desenhando do pixels 400 ao pixel 425.
Thread número: 17 -> desenhando do pixels 425 ao pixel 450.
Thread número: 18 -> desenhando do pixels 450 ao pixel 475.
Thread número: 12 -> desenhando do pixels 300 ao pixel 325.
Thread número: 19 -> desenhando do pixels 475 ao pixel 500.
Thread número 0 fez pthread_join com sucesso.
1 threads finalizaram.
Thread número 1 fez pthread_join com sucesso.
2 threads finalizaram.
Thread número 2 fez pthread_join com sucesso.
3 threads finalizaram.
Thread número 3 fez pthread_join com sucesso.
4 threads finalizaram.
Thread número 4 fez pthread_join com sucesso.
5 threads finalizaram.
Thread número 5 fez pthread_join com sucesso.
6 threads finalizaram.
Thread número 6 fez pthread_join com sucesso.
7 threads finalizaram.
Thread número 7 fez pthread_join com sucesso.
8 threads finalizaram.
Thread número 8 fez pthread_join com sucesso.
9 threads finalizaram.
Thread número 9 fez pthread_join com sucesso.
10 threads finalizaram.
Thread número 10 fez pthread_join com sucesso.
11 threads finalizaram.
Thread número 11 fez pthread_join com sucesso.
12 threads finalizaram.
Thread número 12 fez pthread_join com sucesso.
13 threads finalizaram.
Thread número 13 fez pthread_join com sucesso.
14 threads finalizaram.
Thread número 14 fez pthread_join com sucesso.
15 threads finalizaram.
Thread número 15 fez pthread_join com sucesso.
16 threads finalizaram.
Thread número 16 fez pthread_join com sucesso.
17 threads finalizaram.
Thread número 17 fez pthread_join com sucesso.
18 threads finalizaram.
Thread número 18 fez pthread_join com sucesso.
19 threads finalizaram.
Thread número 19 fez pthread_join com sucesso.
20 threads finalizaram.
```

## Projeto sequencial 
O projeto sequencial foi retirado de (Project 3: Parallel Mandelbrot)[https://www3.nd.edu/~dthain/courses/cse30341/spring2018/project3/]
