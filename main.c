/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: elias
 *
 * Created on 6 de Abril de 2019, 17:36
 */

#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include"jogo.h"



int main(int argc, char** argv) {   
    setlocale(LC_ALL,"portuguese"); // permite o uso de acentos.
    tJogo *jogo;
    
    criaJogo(&jogo);
    comecaJogo(&jogo);
    destroiJogo(&jogo);
    
    return 0;
}

