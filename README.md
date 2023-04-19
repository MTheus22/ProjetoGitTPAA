# Projeto Git - Tecnicas de Programação e Analise de Algoritmos

## Objetivo:
Desenvolver uma estrutura de dados que simule o fluxo de um projeto Git, respondendo aos comandos que normalmente seriam utilizados em um projeto Git de maneira coerente.

### Comandos:
- __git init__ --> Inicializa o projeto git.
- __git commit__ --> Realiza um commit.
	- -m "mensagem" --> Permite passar uma mensagem junto com o commit. 
- __git branch__ --> Mostra todas as branchs disponiveis e em qual branch o usuario esta.
	- nomedabranch --> Cria uma branch com o nome escolhido.
- __git checkout__ --> Recebe um commit ou o nome de uma branch e muda para o mesmo, não faz nada caso não seja passado nenhum parametro.
	- nomedabranch --> Muda para a branch especificada.
	- hashdocommit --> Muda para o commit especifica em modo "deatached head".
	- -b "nomebranch"--> Permite criar uma branch e mudar pra ela em um só comando.
- __git merge__ --> Recebe o nome de outra branch e cria um novo commit na branch atual com a junção dos arquivos das duas branches, não faz nada caso não seja passado nenhum parametro.
	- nomedabranch --> Realiza merge da branch atual com a branch especificada.
