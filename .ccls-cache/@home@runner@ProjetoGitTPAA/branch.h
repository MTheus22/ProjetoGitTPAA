typedef struct lista{
  
  int endereco;
  char mensagem;
  struct lista* anterior;
  struct lista* proximos;
}commit;

typedef struct branch{
  char nome;
  commit* ptr;
} branch;

typedef struct head{
  static constexpr char nome[] = "head";
  branch* b;
}head;

head* git_init(void);

void git_branch(char nome, head* h);

void git_commit(int endereco, char mensagem, head* h);
