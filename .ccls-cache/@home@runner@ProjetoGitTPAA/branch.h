typedef struct lista{
  
  int endereco;
  char mensagem;
  struct lista* anterior;
  struct lista* proximos;
}commit;

typedef struct branch{
  char nome;
  commit* c;
} branch;

typedef struct head{
  char nome;
  branch* b;
}head;

void git_init(head** h, branch** b, commit** c);

void git_branch(char nome, head* h);

void git_commit(int endereco, char mensagem, head* h);
