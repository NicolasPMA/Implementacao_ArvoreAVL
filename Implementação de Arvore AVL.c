#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defini��o da estrutura do n� da �rvore AVL
typedef struct arvore {
    int info;
    int FB; // Fator de Balanceamento
    struct arvore *esq;
    struct arvore *dir;
} arvore;

// Fun��o para criar um novo n�
arvore* NovoNo(int valor) {
    arvore* novo = (arvore*) malloc(sizeof(arvore));
    if (!novo) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    novo->info = valor;
    novo->FB = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// Fun��o para encontrar o maior elemento da sub�rvore esquerda
arvore* MaiorEsquerda(arvore* r) {
    arvore* atual = r;
    while (atual->dir != NULL)
        atual = atual->dir;

    return atual;
}

// Rota��o � esquerda simples
arvore* RotacaoEsqSimples(arvore* r) {
    arvore* a = r;
    arvore* b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    if (b->FB == 1) {
        a->FB = 0;
        b->FB = 0;
    }
    else {
        a->FB = 1;
        b->FB = -1;
    }

    return b;
}

// Rota��o � esquerda dupla
arvore* RotacaoEsqDupla(arvore* r) {
    arvore* a = r;
    arvore* c = a->dir;
    arvore* b = c->esq;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;

    switch(b->FB) {
        case -1:
            a->FB = 0;
            c->FB = 1;
            break;

        case 0:
            a->FB = 0;
            c->FB = 0;
            break;

        case +1:
            a->FB = -1;
            c->FB = 0;
            break;
    }

    b->FB = 0;
    return b;
}

// Rota��o � esquerda geral
arvore* RotacaoEsq(arvore* r) {
    if (r->dir->FB == -1)
        r = RotacaoEsqDupla(r);
    else
        r = RotacaoEsqSimples(r);

    return r;
}

// Rota��o � direita simples
arvore* RotacaoDirSimples(arvore* r) {
    arvore* a = r->esq;
    arvore* b = r;
    b->esq = a->dir;
    a->dir = b;

    if (a->FB == -1) {
        a->FB = 0;
        b->FB = 0;
    } else {
        a->FB = -1;
        b->FB = 1;
    }

    return a;
}

// Rota��o � direita dupla
arvore* RotacaoDirDupla(arvore* r) {
    arvore* c = r;
    arvore* a = c->esq;
    arvore* b = a->dir;
    a->dir = b->esq;
    c->esq = b->dir;
    b->esq = a;
    b->dir = c;

    switch(b->FB) {
        case -1:
            a->FB = 0;
            c->FB = 1;
            break;

        case 0:
            a->FB = 0;
            c->FB = 0;
            break;

        case +1:
            a->FB = -1;
            c->FB = 0;
            break;
    }

    b->FB = 0;
    return b;
}

// Rota��o � direita geral
arvore* RotacaoDir(arvore* r) {
    if (r->esq->FB == 1)
        r = RotacaoDirDupla(r);
    else
        r = RotacaoDirSimples(r);

    return r;
}

// Fun��o para inserir um elemento na �rvore AVL
arvore* Inserir(arvore* r, int x, int* hMudou) {
    if (r == NULL) {
        r = NovoNo(x);
        *hMudou = 1;
    }
    else {
        if (x < r->info) {
            r->esq = Inserir(r->esq, x, hMudou);
            if (*hMudou == 1) {
                switch(r->FB) {
                    case -1:
                        r = RotacaoDir(r);
                        *hMudou = 0;
                        break;

                    case 0:
                        r->FB = -1;
                        *hMudou = 1;
                        break;

                    case +1:
                        r->FB = 0;
                        *hMudou = 0;
                        break;
                }
            }
        }
        else if (x > r->info) {
            r->dir = Inserir(r->dir, x, hMudou);
            if (*hMudou == 1) {
                switch(r->FB) {
                    case -1:
                        r->FB = 0;
                        *hMudou = 0;
                        break;

                    case 0:
                        r->FB = +1;
                        *hMudou = 1;
                        break;

                    case +1:
                        r = RotacaoEsq(r);
                        *hMudou = 0;
                        break;
                }
            }
        }
        else {
            *hMudou = 0; // Valor j� existe na �rvore
        }
    }

    return r;
}

// Fun��o para remover um elemento da �rvore AVL
arvore* Remover(arvore* r, int x, int* hMudou) {
    if (r == NULL) {
        *hMudou = 0;
        return NULL;
    }
    if (x < r->info) {
        r->esq = Remover(r->esq, x, hMudou);
        if (*hMudou == 1) {
            switch(r->FB) {
                case -1:
                    r->FB = 0;
                    *hMudou = 1;
                    break;

                case 0:
                    r->FB = +1;
                    *hMudou = 0;
                    break;

                case +1:
                    {
                        int fbDir = r->dir ? r->dir->FB : 0;
                        r = RotacaoEsq(r);
                        if (fbDir == 0)
                            *hMudou = 0;
                        else
                            *hMudou = 1;
                        break;
                    }
            }
        }
    }
    else if (x > r->info) {
        r->dir = Remover(r->dir, x, hMudou);
        if (*hMudou == 1) {
            switch(r->FB) {
                case +1:
                    r->FB = 0;
                    *hMudou = 1;
                    break;

                case 0:
                    r->FB = -1;
                    *hMudou = 0;
                    break;

                case -1:
                    {
                        int fbEsq = r->esq ? r->esq->FB : 0;
                        r = RotacaoDir(r);
                        if (fbEsq == 0)
                            *hMudou = 0;
                        else
                            *hMudou = 1;
                        break;
                    }
            }
        }
    }
    else {
        // N� encontrado
        if (r->esq == NULL || r->dir == NULL) {
            arvore* temp = r->esq ? r->esq : r->dir;
            free(r);
            *hMudou = 1;
            return temp;
        }
        else {
            arvore* temp = MaiorEsquerda(r->esq);
            r->info = temp->info;
            r->esq = Remover(r->esq, temp->info, hMudou);
            if (*hMudou == 1) {
                switch(r->FB) {
                    case -1:
                        r->FB = 0;
                        *hMudou = 1;
                        break;

                    case 0:
                        r->FB = +1;
                        *hMudou = 0;
                        break;

                    case +1:
                        {
                            int fbDir = r->dir ? r->dir->FB : 0;
                            r = RotacaoEsq(r);
                            if (fbDir == 0)
                                *hMudou = 0;
                            else
                                *hMudou = 1;
                            break;
                        }
                }
            }
        }
    }

    return r;
}

// Fun��o para ler uma �rvore do arquivo
void LerArvore(FILE *arquivo, arvore **a) {
    char c;
    int num;
    fscanf(arquivo, " %c", &c); // L� o caractere '('
    fscanf(arquivo, "%d", &num);
    if (num == -1) {
        *a = NULL; // N� vazio
    }
    else {
        *a = NovoNo(num); // Cria um novo n� com o valor lido
        LerArvore(arquivo, &((*a)->esq)); // L� a sub�rvore esquerda
        LerArvore(arquivo, &((*a)->dir)); // L� a sub�rvore direita
    }

    fscanf(arquivo, " %c", &c); // L� o caractere ')'
}

// Fun��es para imprimir a �rvore
void ImprimirPreOrdem(arvore *a) {
    if (a != NULL) {
        printf("%d ", a->info);
        ImprimirPreOrdem(a->esq);
        ImprimirPreOrdem(a->dir);
    }
}

void ImprimirEmOrdem(arvore *a) {
    if (a != NULL) {
        ImprimirEmOrdem(a->esq);
        printf("%d ", a->info);
        ImprimirEmOrdem(a->dir);
    }
}

void ImprimirPosOrdem(arvore *a) {
    if (a != NULL) {
        ImprimirPosOrdem(a->esq);
        ImprimirPosOrdem(a->dir);
        printf("%d ", a->info);
    }
}

// Fun��o para encontrar a altura da �rvore
int Altura(arvore* a) {
    if (a == NULL)
        return 0;
    else {
        int alturaEsquerda = Altura(a->esq);
        int alturaDireita = Altura(a->dir);
        return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
    }
}

// Fun��o para imprimir n�s no n�vel dado
void ImprimirNivel(arvore* a, int nivel) {
    if (a == NULL)
        return;
    if (nivel == 1)
        printf("%d ", a->info);
    else if (nivel > 1) {
        ImprimirNivel(a->esq, nivel - 1);
        ImprimirNivel(a->dir, nivel - 1);
    }
}

// Fun��o para realizar o percurso em largura
void ImprimirEmLargura(arvore* a) {
    int h = Altura(a);
    for (int i = 1; i <= h; i++) {
        ImprimirNivel(a, i);
    }
}

// Fun��o para verificar se um elemento existe na �rvore
int Existe(arvore *a, int x) {
    if (a == NULL) {
        return 0;
    }
    if (x == a->info) {
        return 1;
    }
    else if (x < a->info) {
        return Existe(a->esq, x);
    }
    else {
        return Existe(a->dir, x);
    }
}

// Fun��o para encontrar o n�vel de um n� x
int EncontrarNivel(arvore* a, int x, int nivel) {
    if (a == NULL)
        return 0;
    if (a->info == x)
        return nivel;
    else if (x < a->info)
        return EncontrarNivel(a->esq, x, nivel + 1);
    else
        return EncontrarNivel(a->dir, x, nivel + 1);
}

// Fun��o para imprimir as folhas menores que um valor x
void ImprimirFolhasMenoresQue(arvore *a, int x) {
    if (a != NULL) {
        if (a->esq == NULL && a->dir == NULL && a->info < x) {
            printf("%d ", a->info);
        }
        ImprimirFolhasMenoresQue(a->esq, x);
        ImprimirFolhasMenoresQue(a->dir, x);
    }
}

// Fun��o para liberar a mem�ria alocada para a �rvore
void LiberarArvore(arvore* a) {
    if (a == NULL)
        return;

    LiberarArvore(a->esq);
    LiberarArvore(a->dir);
    free(a);
}

int main() {
    arvore *a = NULL;
    FILE *arquivo;
    int opcao, x;
    char nomeArquivo[100];

    do {
        printf("\n--- Menu ---\n");
        printf("1 - Ler uma arvore de um arquivo fornecido pelo usuario\n");
        printf("2 - Imprimir a arvore (opcoes: pre-ordem; em-ordem; pos-ordem; e em largura)\n");
        printf("3 - Verificar se um elemento x existe na arvore\n");
        printf("4 - Imprimir o nivel de um no x\n");
        printf("5 - Imprimir as folhas menores que um valor x\n");
        printf("6 - Inserir um no x na arvore\n");
        printf("7 - Remover um no x da arvore\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo: ");
                scanf("%s", nomeArquivo);
                arquivo = fopen(nomeArquivo, "rt");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo!\n");
                }
                else {
                    // Se uma �rvore j� estiver carregada, liberar a mem�ria antes de carregar a nova
                    if (a != NULL) {
                        LiberarArvore(a);
                        a = NULL;
                    }

                    LerArvore(arquivo, &a);
                    fclose(arquivo);
                    printf("Arvore carregada com sucesso!\n");
                }
                break;

            case 2:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                }
                else {
                    printf("Escolha a ordem de impressao:\n");
                    printf("1 - Pre-Ordem\n");
                    printf("2 - Em-Ordem\n");
                    printf("3 - Pos-Ordem\n");
                    printf("4 - Em Largura\n");
                    printf("Opcao: ");
                    int ordem;
                    scanf("%d", &ordem);

                    switch (ordem) {
                        case 1:
                            printf("Percurso em Pre-Ordem: ");
                            ImprimirPreOrdem(a);
                            break;

                        case 2:
                            printf("Percurso em Em-Ordem: ");
                            ImprimirEmOrdem(a);
                            break;

                        case 3:
                            printf("Percurso em Pos-Ordem: ");
                            ImprimirPosOrdem(a);
                            break;

                        case 4:
                            printf("Percurso em Largura: ");
                            ImprimirEmLargura(a);
                            break;

                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                    printf("\n");
                }
                break;

            case 3:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                }
                else {
                    printf("Digite o valor de x: ");
                    scanf("%d", &x);
                    if (Existe(a, x)) {
                        printf("Elemento %d existe na arvore.\n", x);
                    }
                    else {
                        printf("Elemento %d nao existe na arvore.\n", x);
                    }
                }
                break;

            case 4:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                }
                else {
                    printf("Digite o valor de x: ");
                    scanf("%d", &x);
                    int nivel = EncontrarNivel(a, x, 1);
                    if (nivel != 0) {
                        printf("O no %d esta no nivel %d da arvore.\n", x, nivel);
                    }
                    else {
                        printf("O no %d nao existe na arvore.\n", x);
                    }
                }
                break;

            case 5:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                }
                else {
                    printf("Digite o valor de x: ");
                    scanf("%d", &x);
                    printf("Folhas menores que %d: ", x);
                    ImprimirFolhasMenoresQue(a, x);
                    printf("\n");
                }
                break;

            case 6: {
                printf("Digite o valor de x: ");
                scanf("%d", &x);
                int hMudou = 0;
                a = Inserir(a, x, &hMudou);
                printf("Elemento %d inserido na arvore.\n", x);
                break;
            }

            case 7: {
                printf("Digite o valor de x: ");
                scanf("%d", &x);
                int hMudou = 0;
                a = Remover(a, x, &hMudou);
                printf("Elemento %d removido da arvore, se existia.\n", x);
                break;
            }

            case 8:
                printf("Liberando memoria alocada para a arvore...\n");
                if (a != NULL) {
                    LiberarArvore(a);
                    a = NULL;
                    printf("Memoria liberada com sucesso.\n");
                }

                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
    while (opcao != 8);

    return 0;
}
