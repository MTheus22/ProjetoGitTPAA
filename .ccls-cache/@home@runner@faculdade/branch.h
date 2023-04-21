#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct lista lista;
typedef struct gancho gancho;
typedef struct head head;
typedef struct branch branch;

lista *inicia_lista(void);
head *inicia_head(void);
branch *inicia_branch(void);
gancho *inicia_cabeca(void);
void git_branch(lista *atual, char *nome_branch);
void git_commit (gancho *cabeca, branch *repos_atual, head *repositorio, char *text);
void git_log(head *repositorio);
char *gera_hash(gancho *cabeca);
int verifica_combinacao(char *string, gancho *cabeca);

#endif