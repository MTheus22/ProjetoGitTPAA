#include "../headers/git.h"
#include "../headers/client.h"
#include "../headers/utils.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void git_branch(char *name, Head *const head, BranchList *const branch_list) {
  if (!name)
    list_branches(head, branch_list);
  else {
    Branch *new_branch = malloc(sizeof(Branch));
    strcpy(new_branch->name, name);
    new_branch->commit = head->commit;
    if (branch_list->branch == NULL)
      initialize_branch_list(branch_list, new_branch);
    else
      insert_branch_list(branch_list, new_branch);
  }
}

void list_branches(Head *const head, BranchList *const branch_list) {
  if (!branch_list->branch)
    return;
  BranchList *current_branch = branch_list;
  while (current_branch) {
    if (head->branch == current_branch->branch)
      printf("* %s\n", current_branch->branch->name);
    else
      printf("%s\n", current_branch->branch->name);
    current_branch = current_branch->next_branch;
  }
}

void initialize_branch_list(BranchList *const branch_list, Branch *new_branch) {
  branch_list->next_branch = NULL;
  branch_list->branch = new_branch;
  branch_list->number_branches = 1;
}

void insert_branch_list(BranchList *const branch_list, Branch *new_branch) {
  BranchList *last_node = branch_list;
  while (last_node->next_branch)
    last_node = last_node->next_branch;
  last_node->next_branch = malloc(sizeof(BranchList));
  last_node->next_branch->branch = new_branch;
  last_node->next_branch->next_branch = NULL;
  branch_list->number_branches++;
}

void git_init(Head **head, BranchList **branch_list,
              CommitsTable **commits_table) {
  *head = malloc(sizeof(Head));
  *branch_list = malloc(sizeof(BranchList));
  *commits_table = create_hash_table();

  (*head)->commit = NULL;
  (*head)->branch = NULL;

  (*branch_list)->branch = NULL;
  (*branch_list)->next_branch = NULL;
}

Status git_checkout(Head *const head, BranchList *const branch_list,
                    unsigned char *hash, char *branch_name,
                    CommitsTable *commits_table) {
  Status status;
  status.is_error = false;
  if (branch_name == NULL && hash == NULL) {
    status.is_error = true;
    strcpy(status.error_log,
           "Attempting to checkout to neither a branch nor a commit");
    return status;
  }
  if (hash != NULL) {
    Commit *commit = get_commit_from_table(commits_table, hash);
    if (commit) {
      head->commit = commit;
      head->branch = NULL;
      return status;
    }
  }
  Branch *branch_searched = search_on_branch_list(branch_list, branch_name);
  if (branch_searched) {
    head->branch = branch_searched;
    head->commit = branch_searched->commit;
    return status;
  } else {
    status.is_error = true;
    strcpy(status.error_log,
           "Não foi encontrado nenhum commit ou branch correspondente \n");
    return status;
  }
}

Status git_merge(Head *head, BranchList *branch_list, unsigned char *hash,
                 char *branch_name, CommitsTable *commits_table,
                 CommitList **commit_list) {
  Status status;
  status.is_error = false;
  if (head->branch == NULL && head->commit == NULL) {
    status.is_error = true;
    strcpy(status.error_log, "Não foi passado nenhum commit ou branch");
    return status;
  }
  if (branch_name == NULL && hash == NULL) {
    status.is_error = true;
    strcpy(status.error_log, "Não foi passado nenhum commit ou branch");
    return status;
  }
  if (hash != NULL) {
    Commit *commit = get_commit_from_table(commits_table, hash);
    if (commit) {
      Commit *new_commit =
          create_commit_and_point_to_two_others(commit, head->commit);
      insert_commit_in_table(commits_table, new_commit);
      head->commit = new_commit;
      return status;
    }
  }
  Branch *branch_searched = search_on_branch_list(branch_list, branch_name);
  if (branch_searched) {
    Commit *new_commit = create_commit_and_point_to_two_others(
        head->commit, branch_searched->commit);
    insert_commit_in_table(commits_table, new_commit);
    head->commit = new_commit;
    head->branch->commit = new_commit;
    return status;
  } else {
    status.is_error = true;
    strcpy(status.error_log, "Não foi passado nenhum commit ou branch");
    return status;
  }
}

Commit *create_commit_and_point_to_two_others(Commit *commit1,
                                              Commit *commit2) {
  Commit *new_commit = malloc(sizeof(Commit));
  char *hash1 = get_hash_string(commit1->hash);
  char *hash2 = get_hash_string(commit2->hash);
  *(hash1 + 32) = '\0';
  *(hash2 + 32) = '\0';
  strcpy(new_commit->message, strcat(hash1, hash2));
  new_commit->hash = generate_hash(new_commit->message);
  if (new_commit == NULL)
    return NULL;
  new_commit->commits_pointed = 2;
  new_commit->previous_commits =
      malloc(sizeof(Commit *) * new_commit->commits_pointed);
  *new_commit->previous_commits = commit1;
  *(new_commit->previous_commits + 1) = commit2;
  return new_commit;
}

void git_log(Head *const head, CommitsTable *commits_table) {
  if (head->branch == NULL && head->commit == NULL) {
    printf("Não existe nenhum commit, faça um commit antes de usar o git log");
    return;
  }
  if (head->branch == NULL)
    printf("--- Detached state ---\n");
  else
    printf("--- Branch: %s ---\n", head->branch->name);
  print_commit(head->commit, commits_table);
  reset_nodes_to_false(head->commit, commits_table);
}

void print_commit(Commit *commit, CommitsTable *commits_table) {
  CommitsListNode *node =
      get_node_from_commits_list_table(commits_table, commit->hash);
  if (node->visited)
    return;
  printf("Message: %s\n", commit->message);
  printf("Hash: %s\n", get_hash_string(commit->hash));
  node->visited = true;
  for (int i = 0; i < commit->commits_pointed; i++)
    print_commit(*(commit->previous_commits + i), commits_table);
}

void reset_nodes_to_false(Commit *commit, CommitsTable *commits_table) {
  CommitsListNode *node =
      get_node_from_commits_list_table(commits_table, commit->hash);
  for (int i = 0; i < commit->commits_pointed; i++)
    reset_nodes_to_false(*(commit->previous_commits + i), commits_table);
  node->visited = false;
}

void git_commit(char *message, Head *const head, CommitsTable *commits_table,
                CommitList **commit_list) {
  Commit *new_commit = malloc(sizeof(Commit));
  new_commit->commits_pointed = 1;
  new_commit->previous_commits =
      malloc(sizeof(Commit *) * new_commit->commits_pointed);
  strcpy(new_commit->message, message);
  new_commit->hash = generate_hash(message);
  *new_commit->previous_commits = head->commit;
  insert_commit_in_table(commits_table, new_commit);
  insert_on_commit_list(commit_list, new_commit);

  if (head->branch != NULL)
    head->branch->commit = new_commit; // Branch se move para o comimt novo
  head->commit = new_commit;           // Head muda para o commit novo
}

void first_commit(char *message, Head *const head,
                  BranchList *const branch_list, CommitsTable *commits_table,
                  CommitList **commit_list) {
  head->commit = malloc(sizeof(Commit));
  head->commit->hash = generate_hash(message);
  strcpy(head->commit->message, message);
  head->commit->previous_commits = NULL;
  head->commit->commits_pointed = 0;
  git_branch("main", head, branch_list);
  head->branch = branch_list->branch;
  insert_commit_in_table(commits_table, head->commit);
  insert_on_commit_list(commit_list, head->commit);
}

void git_push(BranchList *branch_list, CommitList *commit_list) {
  int hash_string_size = 64;
  int number_sections = 4;
  int section_separator = 2 * number_sections;
  int main_command_template_length = 5;
  int commit_template_length = strlen("hash: message: commits_pointed:\n") +
                               hash_string_size + BUFFER_TEXT_LENGTH + 1;
  int commit_graph_template_length =
      hash_string_size + 1 + hash_string_size + 1 + hash_string_size;
  int branch_template_length =
      strlen("name: commit_hash:\n") + BUFFER_TEXT_LENGTH + hash_string_size;
  int server_buffer_length =
      commit_template_length * commit_list->number_nodes +
      branch_template_length * branch_list->number_branches +
      commit_graph_template_length * commit_list->number_nodes +
      main_command_template_length;
  char *server_buffer = malloc(server_buffer_length * 10);
  memset(server_buffer, 0, server_buffer_length);
  sprintf(server_buffer, "push\n-\n");
  insert_commit_data_on_buffer(server_buffer, commit_list);
  insert_graph_data_on_buffer(server_buffer, commit_list);
  insert_branch_data_on_buffer(server_buffer, branch_list);
  send_data_to_server(server_buffer);
}

void insert_branch_data_on_buffer(char *buffer, BranchList *branch_list) {
  BranchList *current_node = branch_list;
  while (current_node) {
    sprintf(buffer + strlen(buffer), "name:%s commit_hash:%s\n",
            current_node->branch->name,
            get_hash_string(current_node->branch->commit->hash));
    current_node = current_node->next_branch;
  }
  sprintf(buffer + strlen(buffer), "-\n");
}

void insert_graph_data_on_buffer(char *buffer, CommitList *commit_list) {
  CommitListNode *current_node = commit_list->commit_list_node;
  while (current_node != NULL) {
    if (current_node->commit->commits_pointed == 0)
      sprintf(buffer + strlen(buffer), "%s NULL\n",
              get_hash_string(current_node->commit->hash));
    else if (current_node->commit->commits_pointed == 1)
      sprintf(
          buffer + strlen(buffer), "%s %s\n",
          get_hash_string(current_node->commit->hash),
          get_hash_string((**(current_node->commit->previous_commits)).hash));
    else
      sprintf(
          buffer + strlen(buffer), "%s %s %s\n",
          get_hash_string(current_node->commit->hash),
          get_hash_string((**(current_node->commit->previous_commits)).hash),
          get_hash_string(
              (**(current_node->commit->previous_commits + 1)).hash));
    current_node = current_node->next;
  }
  sprintf(buffer + strlen(buffer), "-\n");
}

void insert_commit_data_on_buffer(char *buffer, CommitList *commit_list) {
  CommitListNode *current_node = commit_list->commit_list_node;
  while (current_node != NULL) {
    sprintf(buffer + strlen(buffer), "hash:%s message:%s commits_pointed:%i\n",
            get_hash_string(current_node->commit->hash),
            current_node->commit->message,
            current_node->commit->commits_pointed);
    current_node = current_node->next;
  }
  sprintf(buffer + strlen(buffer), "-\n");
}

unsigned char *generate_hash(char *message) {
  unsigned char *hash = malloc(SHA256_DIGEST_LENGTH);
  unsigned char *string_to_hash = generate_string_to_hash(message);
  SHA256(string_to_hash, strlen((char *)string_to_hash), hash);
  return hash;
}

unsigned char *generate_string_to_hash(char *message) {
  time_t current_date;
  time(&current_date);
  unsigned char *string_to_hash =
      malloc(strlen(message) + strlen(ctime(&current_date)) + 1);
  strcpy((char *)string_to_hash, message);
  strcat((char *)string_to_hash, ctime(&current_date));
  return string_to_hash;
}
