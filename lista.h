#ifndef _LISTA_H
#define _LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct especie{
    char nomeCientifico[60];
    int quantDaEspecie;
    int origem;
} Especie;

typedef struct noEspecie{
    struct noEspecie *prox, *ant;
    Especie info;
}NoEspecie;

struct listaEspecies{
    NoEspecie *inicio, *fim;
    int quantEspecies;
};

typedef struct listaEspecies* ListaEspecies;

typedef struct projeto{
    char nomeProjeto[60], descricao[150], dataDeInicio[12];
    ListaEspecies especies;
} Projeto;

typedef struct noProjeto{
    struct noProjeto *prox, *ant;
    Projeto info;
} NoProjeto;

struct listaProjetos{
    NoProjeto *inicio, *fim;
    int quantDeProjetos;
};

typedef struct listaProjetos *ListaProjetos;

typedef ListaProjetos Lista;

void limpaTerminal();
Lista criarLista();
int listaVazia(Lista lista);
Especie lerEspecieTeclado();
int cadastrarEspecie(ListaEspecies lista);
int removerEspecie(ListaEspecies lista, Especie remover);
Projeto criarProjeto();
int cadastrarProjetos(Lista lista);
void imprimirProjetos(NoProjeto *atual, NoProjeto *fim);
void imprimirEspecies(NoEspecie *atual, NoEspecie *fim);
int removerProjeto(Lista lista, Projeto remover);
void liberarLista(Lista lista);
int totalDeArvoresPlantadas(Lista lista);
void listarArvoresPorEspecie(Projeto projetoEspecies);

#endif // _LISTA_H
