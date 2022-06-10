# Madelbrot Fractal Paralelo 

Esse repositório é um projeto para a cadeira de Computação Avançada. Foi desenvolvido em C, para criar imagens do formato bmp criadas a partir do paralelismo do [Mandelbrot Fractal](https://en.wikipedia.org/wiki/Mandelbrot_set). 


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



### Exemplos

```shell
./mandel -e 2 -n 20
```
<img width="498" alt="image" src="https://user-images.githubusercontent.com/38566830/173098656-53e4f117-0b27-4ce6-94a1-c56cbc3cd6c6.png">

```shell
./mandel -x -0.5 -y -0.5 -e 0.25 -n 10
```
<img width="495" alt="image" src="https://user-images.githubusercontent.com/38566830/173097189-01d4c070-1b76-48d5-bafc-6ece128e3620.png">

```shell
./mandel -x 0.286932 -y 0.014287 -e .0005 -m 1000 -n 10
```
<img width="494" alt="image" src="https://user-images.githubusercontent.com/38566830/173096738-37a05bf9-d9bd-4c65-892d-23092e152df7.png">

```shell
./mandel -x -0.5 -y -0.5 -e 0.025 -n 10
```
![image](https://user-images.githubusercontent.com/38566830/173097411-250efca0-ea0a-42c8-bcd5-a7fcfe5b0b8e.png)


## Projeto sequencial 
O projeto sequencial foi retirado de (Project 3: Parallel Mandelbrot)[https://www3.nd.edu/~dthain/courses/cse30341/spring2018/project3/]
