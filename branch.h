typedef struct lista{
  
  int endereco;
  char mensaegem[100];
  struct lista* anterior;
  struct lista* proximos[];
}commit;

typedef struct branch{
  char nome;
  commit* ptr;
} branch;

typedef struct head{
  static constexpr char nome[] = "head";
  branch* b;
}head;

