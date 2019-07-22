/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   baralho.h
 * Author: elias
 *
 * Created on 19 de Abril de 2019, 09:03
 */

#ifndef BARALHO_H
#define BARALHO_H


/*  A natureza da carta informa, através de números inteiros, seu tipo (Rei, 7, Dama  etc.). Sendo:
 * 1 - Às.
 * 2 - 2.
 * 3 - 3.
 * .
 * .
 * .
 * 7 - 7.
 * 8 - Dama.
 * 9 - Valete.
 * 10 - Rei.
 * 
 * A representação do naipe da carta é segundo o valor da variável "naipe". De acordo com a listagem abaixo
 * 1 - Copas.
 * 2 - Ouros.
 * 3 - Paus.
 * 4 - Espadas. 
 *  */

typedef struct{
    int natureza;
    int naipe;
    int valor;
}tCarta;


typedef struct cartaBaralho {
    int indice; // o indice da carta irá identificar posição da carta no baralho
    tCarta carta;
    struct  cartaBaralho *proximaCarta;
}tCartaDoBaralho;

typedef struct baralho{
    tCartaDoBaralho *primeira, *ultima;
    int quantidadeCartas;
}tBaralho;


/*Retorna a quantidade de cartas existentes no baralho
 * inputs: o baralho
 * output: valor inteiro da quantidade de cartas no baralho
 * pré-condicao: baralho válido
 * pés-condicao: baralho inalterado
 */
int quantidadeCartas(tBaralho *baralho);

/*Torna o baralho vazio
 * inputs: o baralho
 * output: nenhum
 * pré-condicao: baralho válido
 * pós-condicao: baralho sem cartas
 */
void fazBaralhoVazio(tBaralho *baralho);

/*Verifica se o baralho esta vazio
 * inputs: o baralho
 * output: retorna 1 se o baralho for vazio e 0 se o baralho não estiver vazio
 * pré-condicao: baralho válido
 * pós-condicao: baralho inalterado
 */
int vazio(tBaralho *baralho);

/* cria baralho com todas as cartas de um jogo de bisca
 * inputs: ponteiro do baralho
 * output: nenhum
 * pre-condicao: ponteiro para baralho válido
 * pos-condicao: baralho criado com todas as cartas
 */
void criaBaralho(tBaralho **baralho);

/* Embaralha todas as cartas do baralho
 * inputs: o baralho
 * output: nenhum
 * pre-condicao: baralho válido
 * pos-condicao: baralho embaralhado
 */
void embaralhar(tBaralho *baralho);

/* Imprime todas as cartas do baralho
 * inputs: o baralho
 * output: nenhum
 * pre-condicao: baralho valido
 * pos-condicao: baralho inalterado
 */
void imprimeBaralho(tBaralho *baralho);

/* Imprime o naipe da carta
 * inputs: uma carta
 * output: nenhum
 * pre-condicao: carta válida
 * pos-condicao: carta inalterada
 */
void imprimeNaipe(tCarta *carta);

/* Imprime a natureza da carta (K,7,A etc.)
 * inputs: a carta
 * output: nenhum
 * pre-condicao: carta valdia
 * pos-condicao: carta inalterada
 */
void imprimeNatureza(tCarta * carta);

/* Libera memória do baralho
 * inputs: o baralho
 * output: nenhum
 * pre-condicao: baralho valido
 * pos-condicao: baralho destruido
 */
void destroiBaralho(tBaralho **baralho);

/* Insere uma carta no baralho
 * inputs: Um baralho e uma carta
 * output: nenhum
 * pre-condicao: baralho e carta validos
 * pos-condicao: carta inserida no baralho
 */
void insereNoBaralho(tBaralho **baralho, tCarta* carta);

/* Cria uma carta
 * inputs: o naipe, a natureza e a carta a ser criada
 * output: nenhum
 * pre-condicao: Naipe adimite valores entre 1 e 4, a natureza adimite valores entre 1 e 10 e uma carta válida
 * pos-condicao: Carta criada
 */
void criaCarta(int naipe, int natureza, tCarta* carta);

/* Imprime uma carta
 * inputs: a carta
 * output: nenhum
 * pre-condicao: carta válida
 * pos-condicao: carta inalterada
 */
void imprimeCarta(tCarta *carta);

/* Busca uma carta no baralho
 * inputs: um baralho e um indice
 * output: uma carta caso seja ela esteja presente no baralho, caso não esteja o programa é terminado
 * pre-condicao: baralho válido e indice válido
 * pos-condicao: baralho inalterado
 */
tCarta buscaCarta(tBaralho * baralho, int indice);

/* Insere carta no indice desejado 
 * inputs: baralho, carta e indice
 * output: nenhum
 * pre-condicao: indice ser igual a um dos indices pertencentes ao baralho
 * pos-condicao: baralho com a carta inserida no indice passado
 */
void insereCartaNoIndice(tBaralho *baralho,tCarta *copiaDaCarta,int indice);

/* Retira carta de um indice desejado
 * inputs: baralho, indice e carta
 * output: nenhum
 * pre-condicao: baralho válido e indice pertencente ao baralho
 * pos-condicao: baralho sem a carta cujo indice foi passado como parâmetro
 */
void retiraCartaBaralho(tBaralho ** baralho, int indice, tCarta *carta);

/* Busca a menor carta do baralho (menor valor)
 * inputs: baralho e trunfo
 * output: valor inteiro do indice da carta com o menor valor
 * pre-condicao: baralho preenchido
 * pos-condicao: baralho inalterado
 */
int buscaCartaComMenorValor(tBaralho *baralho,tCarta *trunfo); 

/* Busca uma carta com uma prioridade maior do que uma carta específica passada 
 * inputs: baralho, carta vencedora do monte no momento da execução e a carta trunfo
 * output: indice inteiro de uma carta de maior prioridade ou -1 caso não seja encontrada uma carta com maior prioridade que a carta vencedora anterior
 * pre-condicao: baralho valido, carta vencedora válida, trunfo válido
 * pos-condicao: baralho, carta vencedora e trunfo inalterados
 */
int buscaCartaDeMaiorPrioridade(tBaralho *baralho,tCarta *cartaVencedoraDoMonte,tCarta *trunfo);

/* Verifica se existe corte no baralho
 * inputs: baralho e carta trunfo
 * output:  1 se existe corte no baralho ou 0 caso não exista
 * pre-condicao: baralho e trunfo válidos
 * pos-condicao: baralho e trunfo inalterados
 */
int temCorteNoBaralho(tBaralho* baralho, tCarta *trunfo);

/* Verifica se existe uma carta de mesmo naipe porém de maior prioridade que a carta passada como vencedora anterior
 * inputs: baralho e carta vencedora anterior
 * output: 1 se houver encarte e 0 caso contrário
 * pre-condicao: baralho e carta vencedora válidos
 * pos-condicao: baralho e carta inalterados
 */
int temEncarteNoBaralho(tBaralho *baralho, tCarta * cartaVencedoraDoMonte);

/*  Tenta buscar uma carta de mesmo naipe com maior prioridade que a carta passada como parâmetro
 * inputs: baralho e carta vencedora anterior
 * output: valor inteiro do indice da carta com encarte vencedor ou -1 caso não consiga achar tal carta no baralho
 * pre-condicao: baralho e carta válidos
 * pos-condicao: baralho e carta inalterados
 */
int encarteVencedor(tBaralho *baralho, tCarta * cartaVencedoraDoMonte);

/* Busca indice do menor corte existente no baralho
 * inputs: baralho e carta trunfo
 * output: valor inteiro do indice do menor corte 
 * pre-condicao: baralho e carta trunfo válidos
 * pos-condicao: baralho e carta trunfo inalterados
 */
int menorCorte(tBaralho* baralho, tCarta *trunfo);

/* Busca indice do menor corte maior que o corte anterior
 * inputs: baralho e corte anterior
 * output: valor inteiro do indice da menor carta corte maior que o corte passado como parâmetro ou -1 caso não haja tal carta 
 * pre-condicao: baralho e carta válidos
 * pos-condicao: baralho e carta inalterados
 */
int menorCorteVencedor(tBaralho *baralho, tCarta * corteAnterior);




#endif /* BARALHO_H */

