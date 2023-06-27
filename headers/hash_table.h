#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "./git.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct commitsListNode {
  Commit *commit;
  struct commitsListNode *next;
  bool visited; // Para ser usado para printar o grafo de commits, e permitir
                // checkar facilmente se um commit ja foi visitado ou não
} CommitsListNode;

typedef struct commitsList {
  CommitsListNode *first_node;
  CommitsListNode *tail;
} CommitsList;

typedef struct commitsTable {
  CommitsList **commits_list_array;
  int number_commits;
  int table_size;
} CommitsTable;

CommitsTable *create_hash_table();

void divide_sha256_in_32_bits_chunks(const unsigned char *sha256,
                                     uint32_t *chunks);

void insert_commit_in_table(CommitsTable *hash_table, Commit *commit);

Commit *get_commit_from_table(CommitsTable *hash_table, unsigned char *hash);

CommitsListNode *get_node_from_commits_list_table(CommitsTable *hash_table,
                                                  unsigned char *hash);

void fill_commits_list_with_null(CommitsTable *hash_table);

uint64_t get_index_in_table(unsigned char *hash, int table_size);

CommitsListNode *search_commits_list(CommitsList *commits_list,
                                     unsigned char *hash);

void insert_commit_on_tail(CommitsList *commit_list, Commit *commit);

void initialize_commit_list(CommitsList **commit_list_pointer, Commit *commit);

void insert_in_commit_list(CommitsList **commit_list_pointer, Commit *commit);

#endif
