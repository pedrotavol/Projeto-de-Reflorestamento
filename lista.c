#include "lista.h"

void limpaTerminal(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

ListaEspecies criarListaEspecies(){
    ListaEspecies lista = (ListaEspecies)malloc(sizeof(ListaEspecies));

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantEspecies = 0;

    return lista;
}

Lista criarLista(){ //Inicia lista duplamente encadeada de projetos
    Lista lista = (Lista)malloc(sizeof(Lista));

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantDeProjetos = 0;

    return lista;
}

int listaVazia(Lista lista){
    if(lista->quantDeProjetos == 0)
        return 1;
    else
        return 0;
}

void LerString(char *linha, int tamanho){ //Ler string sem \n
    fgets(linha, tamanho, stdin);
    linha[strcspn(linha, "\n")] = '\0';

    setbuf(stdin, NULL);
}

Especie criarEspecie(){
    Especie novaEspecie;

    printf("Insira o nome cientifico da especie: ");
    LerString(novaEspecie.nomeCientifico, sizeof(novaEspecie.nomeCientifico));

    do{
        printf("Insira a origem da especie ([1] Nativa ou [2] Exotica): ");
        scanf("%d", &novaEspecie.origem);
        setbuf(stdin, NULL);

        if(novaEspecie.origem != 1 && novaEspecie.origem != 2){
            printf("Erro: operacao invalida.\n");
        }
    }while(novaEspecie.origem != 1 && novaEspecie.origem != 2);

    do{
        printf("Insira a quantidade de representante da especie no projeto: ");
        scanf("%d", &novaEspecie.quantDaEspecie);
        setbuf(stdin, NULL);

        if(novaEspecie.quantDaEspecie < 0)
            printf("Erro: quantidade invalida.\n");
    }while(novaEspecie.quantDaEspecie < 0);

    return novaEspecie;
}

int adicionarEspecie(ListaEspecies lista, Especie especieInfo){
    NoEspecie *novaEspecie = (NoEspecie*)malloc(sizeof(NoEspecie));
    if(novaEspecie == NULL){ //Se deu erro na alocação
        return 0;
    }

    novaEspecie->info = especieInfo;
    novaEspecie->prox = NULL;

    if(lista->quantEspecies == 0){
        novaEspecie->ant = NULL;
        lista->inicio = novaEspecie;
        lista->fim = novaEspecie;
    }
    else{
        novaEspecie->ant = lista->fim;
        lista->fim->prox = novaEspecie;
        lista->fim = novaEspecie;
    }
    lista->quantEspecies++;

    return 1;
}

int cadastrarEspecie(ListaEspecies lista){
    Especie novaEspecie = criarEspecie();

    if(adicionarEspecie(lista, novaEspecie) == 0){
        printf("Erro: especie(s) nao cadastrado(s)\n"); //Tem que colocar um free aqui depois liberando os que eu coloquei
        return 0;
    }

    printf("Especie(s) cadastrada(s)!\n");
    return 1;
}

int removerEspecie(ListaEspecies lista, Especie remover){
    if(lista->quantEspecies == 0){
        return 0;
    }
    NoEspecie *atual = lista->inicio;

    while(strcmp(atual->info.nomeCientifico, remover.nomeCientifico) != 0 && atual != lista->fim){
        atual = atual->prox;
    }

    if(atual == lista->inicio){
        lista->inicio = atual->prox;
    }
    else if(atual == lista->fim){
        lista->fim = atual->ant;
    }
    else{
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }

    lista->quantEspecies--;
    free(atual);
    return 1;
}

Projeto criarProjeto(){
    Projeto novoProjeto;

    printf("Insira o nome do projeto: ");
    LerString(novoProjeto.nomeProjeto, sizeof(novoProjeto.nomeProjeto));

    printf("Insira a data de inicio do projeto (00/00/0000): ");
    LerString(novoProjeto.dataDeInicio, sizeof(novoProjeto.dataDeInicio));

    printf("Deseja inserir um descricao? (S ou N): ");
    char op;
    do{
        scanf("%c", &op);
        setbuf(stdin, NULL);

        if(op == 'S' || op == 's'){
            printf("Insira a descricao (ate 150 caracteres): ");
            LerString(novoProjeto.descricao, sizeof(novoProjeto.descricao));
        }
        else if(op == 'N'|| op == 'n'){
            strcpy(novoProjeto.descricao, "Sem descricao");
        }
        else{
            printf("Erro: operacao invalida.\n");
        }

    }while(op != 'S' && op != 's' && op != 'N' && op != 'n');

    int quantidade;
    printf("Insira a quantidade de especies: ");
    do{
        scanf("%d", &quantidade);
        setbuf(stdin, NULL);

        if(quantidade < 0)
            printf("Erro: quantidade invalida.\n");
    }while(quantidade < 0);

    novoProjeto.especies = criarListaEspecies();
    for(int i=0; i<quantidade; i++){
        cadastrarEspecie(novoProjeto.especies);
    }

    return novoProjeto;
}

int adicionarProjeto(Lista lista, Projeto projetoInfo){
    NoProjeto *novoProjeto = (NoProjeto*)malloc(sizeof(NoProjeto));
    if(novoProjeto == NULL){
        return 0;
    }

    novoProjeto->info = projetoInfo;
    novoProjeto->prox = NULL;

    if(lista->quantDeProjetos == 0){
        novoProjeto->ant = NULL;
        lista->inicio = novoProjeto;
        lista->fim = novoProjeto;
    }
    else{
        novoProjeto->ant = lista->fim;
        lista->fim->prox = novoProjeto;
        lista->fim = novoProjeto;
    }
    lista->quantDeProjetos++;

    return 1;
}

int cadastrarProjetos(Lista lista){
    Projeto novoProjeto = criarProjeto();

    if(adicionarProjeto(lista, novoProjeto) == 0){
        printf("Erro: projeto(s) nao cadastrado(s)\n"); //Tem que colocar um free aqui depois liberando os que eu coloquei
        return 0;
    }

    printf("Projeto(s) cadastrado(s)!\n");
    return 1;
}

int removerProjeto(Lista lista, Projeto remover){
    if(lista->quantDeProjetos == 0){
        return 0;
    }
    NoProjeto *atual = lista->inicio;

    while(strcmp(atual->info.nomeProjeto, remover.nomeProjeto) != 0 && atual != lista->fim){
        atual = atual->prox;
    }

    if(atual == lista->inicio){
        lista->inicio = atual->prox;
    }
    else if(atual == lista->fim){
        lista->fim = atual->ant;
    }
    else{
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }

    lista->quantDeProjetos--;

    NoEspecie *atualEspecie = atual->info.especies->inicio, *copia;

    while(atualEspecie != NULL){ //Liberando a memoria alocada pelas especies
        copia = atualEspecie;
        atualEspecie = atualEspecie->prox;
        free(copia);
    }
    free(atual);

    return 1;
}

void imprimirProjetos(NoProjeto *atual, NoProjeto *fim){
    printf("%s\n", atual->info.nomeProjeto);
    if(atual == fim)
        return;

    imprimirProjetos(atual->prox, fim);
}

void imprimirEspecies(NoEspecie *atual, NoEspecie *fim){
    printf("%s\n", atual->info.nomeCientifico);
    if(atual == fim)
        return;

    imprimirEspecies(atual->prox, fim);
}

void liberarLista(Lista lista){
    NoProjeto *atualProjeto = lista->inicio, *copiaProjeto;
    NoEspecie *atualEspecie, *copiaEspecie;

    while(atualProjeto != NULL){
        copiaProjeto = atualProjeto;
        atualEspecie = atualProjeto->info.especies->inicio;
        atualProjeto = atualProjeto->prox;

        while(atualEspecie != NULL){
            copiaEspecie = atualEspecie;
            atualEspecie = atualEspecie->prox;
            free(copiaEspecie);
        }

        free(copiaProjeto);
    }
    free(lista);
}

void listarArvoresPorEspecie(Projeto projetoEspecies){
    NoEspecie *atual = projetoEspecies.especies->inicio;

    while(atual != NULL){
        printf("%s\t%d\n", atual->info.nomeCientifico, atual->info.quantDaEspecie);
        atual = atual->prox;
    }
}

int contarArvoresPorProjeto(Projeto contar){
    NoEspecie *atual = contar.especies->inicio;
    int totalDeArvores = 0;

    while(atual != NULL){
        totalDeArvores += atual->info.quantDaEspecie;
        atual = atual->prox;
    }

    return totalDeArvores;
}

int totalDeArvoresPlantadas(Lista lista){
    NoProjeto *atual = lista->inicio;
    int totalPlantadas = 0;

    while(atual != NULL){
        totalPlantadas += contarArvoresPorProjeto(atual->info);
        atual = atual->prox;
    }

    return totalPlantadas;
}
