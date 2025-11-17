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
  int n, k;
  scanf("%d %d", &n, &k);
  Station stations[10];

  for (int i = 0; i < n; i++)
  {
    int x, y;
    scanf(" %c %d %d %d", &stations[i].name, &x, &y, &stations[i].temp);
    stations[i].dist_sq = x * x + y * y;
  }

  insertionSort(stations, n);

  double numerator = 0.0, denominator = 0.0;
  for (int i = 0; i < k; i++)
  {
    if (stations[i].dist_sq == 0)
    {
      printf("%.3f\n", (double)stations[i].temp);
      return 0;
    }
    double weight = 1.0 / stations[i].dist_sq;
    numerator += weight * stations[i].temp;
    denominator += weight;
  }

  printf("%.3f\n", numerator / denominator);
  return 0;
}