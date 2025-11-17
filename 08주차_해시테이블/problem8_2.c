#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int *hash;

void insertItem(int m, int e);
int searchItem(int m, int e);

int main() {

  int m, n;
  scanf("%d %d", &m, &n);

  hash = (int *)malloc(sizeof(int) * m);
  for (int i = 0; i < m; i++) {
    hash[i] = 0;
  }
  char op;
  int e;
  while (1) {
    scanf(" %c", &op);
    if (op == 'i') {
      scanf("%d", &e);
      insertItem(m, e);
    }
    else if (op == 's') {
      scanf("%d", &e);
      if (searchItem(m, e) == -1) {
        printf("-1\n");
      }
    }
    else if (op == 'e') {
      break;
    }
  }

  return 0;
}

void insertItem(int m, int e) {
  int x = e % m;
  int i = x, col = 0;

  while (1) {
    if (hash[i] == 0) {
      hash[i] = e;
      break;
    }
    i++; col++;
    if (i >= m) i = 0;
    if (i == x) {
      printf("-1\n");
      return;
    }
  }
  for (int j = 0; j < col; j++) {
    printf("C");
  }
  printf("%d\n", i);
}

int searchItem(int m, int e) {
  int x = e % m;
  int i = x;

  while (1) {
    if (hash[i] == e) {
      printf("%d %d\n", i, hash[i]);
      return 0;
    }
    i++;
    if (i >= m) i = 0;
    if (i == x) {
      return -1;
    }
  }

  return 0;
}