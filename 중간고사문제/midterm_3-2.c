#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char name;
  int dist_sq;
  int temp;
} Station;

void insertionSort(Station *stations, int n)
{
  for (int i = 1; i <= n - 1; i++)
  {
    Station save = stations[i];
    int j = i - 1;
    while (j >= 0 && stations[j].dist_sq > save.dist_sq)
    {
      stations[j + 1] = stations[j];
      j--;
    }
    stations[j + 1] = save;
  }
}

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

  insertionSort(stations, n);

  for (int i = 0;i < n;i++) {
    printf("%c %d %d\n", stations[i].name, stations[i].dist_sq, stations[i].temp);
  }

  return 0;
}