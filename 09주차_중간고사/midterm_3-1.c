#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char name;
  int dist_sq;
  int temp;
} Station;

int main()
{
  int n;
  scanf("%d", &n);
  Station stations[10];

  for (int i = 0; i < n; i++)
  {
    int x, y;
    scanf(" %c %d %d %d", &stations[i].name, &x, &y, &stations[i].temp);
    stations[i].dist_sq = x * x + y * y;
  }

  for (int i=0; i<n; i++) {
    printf("%c %d %d\n", stations[i].name, stations[i].dist_sq, stations[i].temp);
  }

  return 0;
}