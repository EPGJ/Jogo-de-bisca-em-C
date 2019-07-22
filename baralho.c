/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"baralho.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


void fazBaralhoVazio(tBaralho *baralho){
    baralho->primeira = NULL;
    baralho->ultima = NULL;
}

int vazio(tBaralho *baralho){
    
    if(baralho->primeira == NULL){
        return 1; // baralho está vazio
    }
    return 0; // baralho não está vazio.
    
}

void criaBaralho(tBaralho **baralho){
    int naipe,natureza;
    tCarta carta;
    
    *baralho = malloc(sizeof(tBaralho));
    
    fazBaralhoVazio(*baralho);
    
    for(naipe=1;naipe<=4;naipe++){
        for(natureza = 1;natureza <= 10;natureza++){
            
            criaCarta(naipe,natureza,&carta);
            insereNoBaralho(baralho, &carta);
            
        }
    }
    
    
}
tCarta buscaCarta(tBaralho * baralho, int indice){
    
    tCartaDoBaralho * p;
    
    for(p= baralho->primeira; p !=NULL; p = p->proximaCarta){
        if(indice  == p->indice)return p->carta;
    }
    printf("ERRO!!! carta não existe no baralho");
    exit(1);
    
}
void insereCartaNoIndice(tBaralho *baralho ,tCarta *copiaDaCarta,int indice){
    
    tCartaDoBaralho * p;
    
    for(p= baralho->primeira; p !=NULL; p = p->proximaCarta){
        if(indice  == p->indice){
            p->carta = *copiaDaCarta;
        }
    }
    
}
void embaralhar(tBaralho *baralho){   
    srand(time(NULL));
    tCartaDoBaralho * p;
    tCarta copiaDaCarta;
    int i;
         
    for(p = baralho->primeira ; p != NULL; p = p->proximaCarta){      
        
        i = rand()%baralho->quantidadeCartas; // recebe um indice alearótio entre 0 e (quantidade de cartas atualmente no jogo -1);
        copiaDaCarta = p->carta;
        p->carta = buscaCarta(baralho,i);
        insereCartaNoIndice(baralho,&copiaDaCarta,i);
                
    }
    
    
    
}
void imprimeCarta(tCarta *carta){
   
    imprimeNatureza(carta);
    imprimeNaipe(carta);
    
}
void imprimeNatureza(tCarta * carta){
     switch(carta->natureza){
        //Às
        case 1:
            printf(" A");
            break;
        //Valete
        case 8:
            printf(" J");
            break;
        //Dama    
        case 9:
            printf(" Q");
            break;
        //Rei    
        case 10:
            printf(" K");
            break; 
        default:
            printf(" %d", carta->natureza);
    }
}


void imprimeNaipe(tCarta *carta){
    
    switch(carta->naipe){
        // Copas
        case 1:
            printf("\u2665 ");
            break;
        //Ouros
        case 2:
            printf("\u2666 ");
            break;
        //Paus
        case 3:
            printf("\u2663 ");
            break;
        //Espadas
        case 4:
            printf("\u2660 ");
            break;
        
    }
}
void imprimeBaralho(tBaralho *baralho){
    tCartaDoBaralho * p;
    int i;
    if(baralho->primeira ==  NULL) {
        printf("Baralho Vazio!\n");
        return;
    }
    for(p = baralho->primeira, i=0; p != NULL ; p = p->proximaCarta,i++){
        if(i%10 ==0 ) printf("\n");
        imprimeCarta(&(p->carta));
    }
    printf("\n\n");
    
}
void destroiBaralho(tBaralho **baralho){
    tCartaDoBaralho *p, *t = (*baralho)->primeira;
    
    
    while(t!=NULL){
        (*baralho)->quantidadeCartas--;
        p = t->proximaCarta;
        free(t);
        t = p;
    }
    free(*baralho);
    fazBaralhoVazio((*baralho));    
        
    
    
    
}

void insereNoBaralho(tBaralho **baralho, tCarta *carta){
    
    tCartaDoBaralho * nova = (tCartaDoBaralho *) malloc(sizeof(tCartaDoBaralho));
    
    if((*baralho)->ultima == NULL){
        (*baralho)->ultima = nova;
        (*baralho)->primeira = nova;
        (*baralho)->quantidadeCartas= 0;
    }
    
    else{
        (*baralho)->ultima->proximaCarta = nova;
        (*baralho)->ultima = (*baralho)->ultima->proximaCarta;
    }
    
    (*baralho)->ultima->indice = (*baralho)->quantidadeCartas; //O índice será numericamente igual a quantidade de cartas existentes no baralho durante a execução dessa função.
    (*baralho)->quantidadeCartas++;
    (*baralho)->ultima->carta = *carta;
    (*baralho)->ultima->proximaCarta = NULL;
    
}

void criaCarta(int naipe, int natureza, tCarta* carta){
  
    carta->naipe = naipe;
    carta->natureza = natureza;
    switch(natureza){
        //Às
        case 1:      
            carta->valor = 11;
            break;
        // 7
        case 7:
            carta->valor = 10;
            break;
        // Valete
        case 8:
            carta->valor = 2;
            break;
        // Dama
        case 9:
            carta->valor = 3;
            break;
        // Rei
        case 10:
            carta->valor = 4;
            break;
        
        default:
            if(natureza> 10 || natureza<1){
                printf("ERRO!! essa carta não pertence ao jogo de Bisca.");
                exit(1);
            }
            else{
                carta->valor = 0;
            }
    }
    
}
int quantidadeCartas(tBaralho *baralho){
    return baralho->quantidadeCartas;
}

void retiraCartaBaralho(tBaralho ** baralho, int i, tCarta *carta){
    
    int indice  = i-1;
    int p = 0;
    *carta = buscaCarta((*baralho), indice);
    tCartaDoBaralho *atual = (*baralho)->primeira, *anterior = NULL;
    tCartaDoBaralho *cartaARetirar= (*baralho)->primeira, *anteriorDaCarta=NULL;
    
    while(atual != (*baralho)->ultima->proximaCarta){
        
        if(atual->indice == indice && p ==0){
            cartaARetirar = atual;
            anteriorDaCarta = anterior;  
            p++;
            
        }
        if(atual->indice > indice){
            atual->indice --;
        }
        anterior = atual;
        atual = atual->proximaCarta;
        
    }
    
    if(anteriorDaCarta == NULL){
        (*baralho)->primeira = cartaARetirar->proximaCarta;
    }
    else{
        anteriorDaCarta->proximaCarta = cartaARetirar->proximaCarta;
        if(i == (*baralho)->quantidadeCartas ){
            (*baralho)->ultima = anteriorDaCarta;
        }
    }
       
    
    free(cartaARetirar);
    (*baralho)->quantidadeCartas--;
    
    if((*baralho)->ultima !=NULL){
        (*baralho)->ultima->proximaCarta = NULL;
    }
    else{
        (*baralho)->primeira = NULL;
    }
    
}

int buscaCartaComMenorValor(tBaralho *baralho,tCarta *trunfo){
    
    int menorValorCarta = baralho->primeira->carta.valor;
    tCartaDoBaralho *menorCarta = baralho->primeira;
    tCartaDoBaralho *p;
    
    for(p = baralho->primeira; p !=NULL; p = p->proximaCarta){
        
        if(p->carta.valor == menorValorCarta && p->carta.naipe != trunfo->naipe){
            
            menorValorCarta = p->carta.valor;
            menorCarta = p;
            
        }
        if(p->carta.valor < menorValorCarta){
            
            menorValorCarta = p->carta.valor;
            menorCarta = p;
        }
        
    }
    return menorCarta->indice+1;
}

int buscaCartaDeMaiorPrioridade(tBaralho *baralho,tCarta *cartaVencedoraDoMonte,tCarta *trunfo){
    
    int i = -1; // valor do indice caso não seja encontrada uma carta de maior prioridadade na mão do jogador. .
    
    
    if(cartaVencedoraDoMonte->naipe == trunfo->naipe){
        
        if(temCorteNoBaralho(baralho,trunfo)){

            return menorCorteVencedor(baralho,cartaVencedoraDoMonte);
        }
        // se não houver corte no baralho  a função retorna -1;
        
    }
    
    else{
        
        if(temEncarteNoBaralho(baralho, cartaVencedoraDoMonte)){

            return encarteVencedor(baralho, cartaVencedoraDoMonte);
        }
        else{

            if(temCorteNoBaralho(baralho, trunfo)){
                return menorCorte(baralho, trunfo);
            }
            // se não houver corte no baralho a função retorna -1
        }
        
    }
          
    return i;
    
}

int temCorteNoBaralho(tBaralho* baralho, tCarta *trunfo){
    
    tCartaDoBaralho *p;
    
    for(p=baralho->primeira; p !=NULL;p = p->proximaCarta){
        
        if(p->carta.naipe == trunfo->naipe) return 1;
        
    }
    
    return 0;
}
 
int temEncarteNoBaralho(tBaralho *baralho, tCarta * cartaVencedoraDoMonte){
    
    tCartaDoBaralho *p;
    
    for(p=baralho->primeira; p !=NULL;p = p->proximaCarta){
        
        if(p->carta.naipe == cartaVencedoraDoMonte->naipe){
            
            
            if(p->carta.valor == cartaVencedoraDoMonte->valor && p->carta.natureza > cartaVencedoraDoMonte->natureza)
                return 1;
            if(p->carta.valor > cartaVencedoraDoMonte->valor)
                return 1;
            
        }
        
    }
    
    
    return 0;
    
}

int encarteVencedor(tBaralho *baralho, tCarta * vencedora){
    
    tCartaDoBaralho *p;
    
    for(p = baralho->primeira; p!=NULL; p = p->proximaCarta){
        
        if(p->carta.naipe == vencedora->naipe){
            
            if(p->carta.valor == vencedora->valor && p->carta.natureza > vencedora->natureza){
                
                return p->indice+1;
                
            }
            if(p->carta.valor > vencedora->valor){

                return p->indice+1;
                
            }
            
        }
    }
    return -1;
    
}

int menorCorte(tBaralho* baralho, tCarta *trunfo){
    
    tCartaDoBaralho * p,*menorCorte;
    int count=0;
    
    
    for(p= baralho->primeira; p!=NULL; p = p->proximaCarta){
        
        if(p->carta.naipe == trunfo->naipe){
            
            if(count == 0){
                menorCorte = p;
            }
            else{
                
                if(menorCorte->carta.natureza > p->carta.natureza && menorCorte->carta.valor == p->carta.valor){
                    menorCorte = p;
                }
                if(menorCorte->carta.valor > p->carta.valor){
                    menorCorte = p;
                }
                
            }
            count++;
        }
        
    }
    
    return menorCorte->indice+1;
    
    
}

int menorCorteVencedor(tBaralho *baralho, tCarta * vencedora){
    
    tCartaDoBaralho * p, *menorCorte;
    int count=0, i=-1;
    
    for(p= baralho->primeira; p!=NULL; p = p->proximaCarta){
        // Cumpre as condições se a carta for um corte maior que a carta vencedora.
        if(p->carta.naipe == vencedora->naipe &&( (p->carta.valor > vencedora->valor) || (p->carta.valor == vencedora->valor && p->carta.natureza > vencedora->natureza) ) ){
            
            if(count == 0){
                i=p->indice+1;
                menorCorte = p;
            }
            
            else{
                
                if(menorCorte->carta.valor > p->carta.valor){
                    i= p->indice+1;
                    menorCorte = p;
                }
                else{
                    if(menorCorte->carta.valor == p->carta.valor && menorCorte->carta.natureza> p->carta.natureza){
                        i=p->indice+1;
                        menorCorte = p;
                    }
                }
                
            }
            count++;
        }
        
    }
    return i;
    
}