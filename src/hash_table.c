#include "../headers/hash_table.h"
#include "../headers/git.h"
#include "../headers/utils.h"
#include <openssl/sha.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

CommitsTable *create_hash_table() {
  CommitsTable *hash_table = malloc(sizeof(CommitsTable));
  hash_table->table_size = 521;
  hash_table->number_commits = 0;
  hash_table->commits_list_array =
      malloc(sizeof(CommitsList *) * hash_table->table_size);
  fill_commits_list_with_null(hash_table);
  return hash_table;
}

Commit *get_commit_from_table(CommitsTable *hash_table, unsigned char *hash) {
  uint64_t table_index = get_index_in_table(hash, hash_table->table_size);
  CommitsList *commits_list = *(hash_table->commits_list_array + table_index);
  if (hash_compare(hash, commits_list->first_node->commit->hash))
    return commits_list->first_node->commit;
  else
    return search_commits_list(commits_list, hash)->commit;
}

CommitsListNode *get_node_from_commits_list_table(CommitsTable *hash_table,
                                                  unsigned char *hash) {
  uint64_t table_index = get_index_in_table(hash, hash_table->table_size);
  CommitsList *commits_list = *(hash_table->commits_list_array + table_index);
  if (hash_compare(hash, commits_list->first_node->commit->hash))
    return commits_list->first_node;
  else
    return search_commits_list(commits_list, hash);
}

CommitsListNode *search_commits_list(CommitsList *commits_list, unsigned char *hash) {
  CommitsListNode *current_node = commits_list->first_node->next;
  do {
    if (hash_compare(current_node->commit->hash, hash))
      return current_node;
    current_node = current_node->next;
  } while (current_node != NULL);
  return current_node;
}

void insert_commit_in_table(CommitsTable *hash_table, Commit *commit) {
  uint64_t table_index =
      get_index_in_table(commit->hash, hash_table->table_size);
  insert_in_commit_list(hash_table->commits_list_array + table_index, commit);
}

void insert_in_commit_list(CommitsList **commit_list_pointer, Commit *commit) {
  if (*commit_list_pointer == NULL)
    initialize_commit_list(commit_list_pointer, commit);
  else
    insert_commit_on_tail(*commit_list_pointer, commit);
}

void initialize_commit_list(CommitsList **commit_list_pointer, Commit *commit) {
  *commit_list_pointer = malloc(sizeof(CommitsList));
  (*commit_list_pointer)->tail = (**commit_list_pointer).first_node;
  (*commit_list_pointer)->first_node->commit = commit;
  (*commit_list_pointer)->first_node->next = NULL;
  (*commit_list_pointer)->first_node->visited = false;
}

void insert_commit_on_tail(CommitsList *commit_list, Commit *commit) {
  CommitsListNode *new_tail = malloc(sizeof(CommitsListNode));
  CommitsListNode *previous_tail = commit_list->tail;
  commit_list->tail = new_tail;
  previous_tail->next = new_tail;
  new_tail->next = NULL;
  new_tail->commit = commit;
  new_tail->visited = false;
}

uint64_t get_index_in_table(unsigned char *hash, int table_size) {
  uint32_t hash_chunks[8];
  uint64_t hash_sum = 0;
  for (int i = 0; i < 8; i++)
    hash_sum += hash_chunks[i];
  return (uint64_t)hash_sum % table_size;
}

void divide_sha256_in_32_bits_chunks(const unsigned char *sha256,
                                     uint32_t *chunks) {
  for (int i = 0; i < 8; i++) {
    chunks[i] =
        ((uint32_t)sha256[i * 4] << 24) | ((uint32_t)sha256[i * 4 + 1] << 16) |
        ((uint32_t)sha256[i * 4 + 2] << 8) | (uint32_t)sha256[i * 4 + 3];
  }
}

void fill_commits_list_with_null(CommitsTable *hash_table) {
  for (int i = 0; i < hash_table->table_size; i++)
    hash_table->commits_list_array[i] = NULL;
}
