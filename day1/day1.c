#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_msg(char *msg) { fprintf(stderr, "[Message] :: `%s`\n", msg); }

typedef struct id_pair {
  int num1;
  int num2;
} id_pair;

int parse_number(char *str, char **end) {

  long num = strtol(str, end, 10);

  if (num == 0) {
    print_msg("Conversion to long failed. Exiting.");
    exit(1);
  }

  return num;
}

int int_smaller_than(const void *item, const void *compare_to) {

  int item1 = *(const int *)item;
  int item2 = *(const int *)compare_to;

  /* If item1 smaller than item2 */
  if (item1 < item2)
    return -1;
  /* If item1 bigger than item2 */
  if (item1 > item2)
    return 1;

  /* Else return 0 */
  return 0;
}

int repetitions_in_array(int needle, int haystack[], int haystack_size) {
  int count = 0;
  int curr = 0;

  for (int i = 0; i < haystack_size; i++) {
    curr = haystack[i];
    if (curr == needle) {
      ++count;
    }
  }
  return count;
}

int main(void) {
  FILE *f = fopen("input", "r");

  id_pair id_list[1024];

  char *buffer = calloc(sizeof(char), 1024);
  char *end = buffer;

  int col1[1024];
  int col2[1024];

  size_t count = 0;

  while (fgets(buffer, 1023, f)) {

    col1[count] = parse_number(buffer, &end);
    fprintf(stderr, "First number: %d\n", col1[count]);
    col2[count] = parse_number(end, NULL);
    fprintf(stderr, "Second number: %d\n", col2[count]);
    ++count;
    /* buffer = memset(buffer, 0, 1024); */
  }
  const size_t size = count;

  qsort(col1, size, sizeof(int), int_smaller_than);
  qsort(col2, size, sizeof(int), int_smaller_than);

  count = 0;

  /* For debugging */
  printf("\nColumn one:\n");
  for (int i = 0; i < 30; i++) {
    printf("%d, ", col1[i]);
  }

  printf("\nColumn two:\n");
  for (int i = 0; i < 30; i++) {
    printf("%d, ", col2[i]);
  }

  int differences[size];
  size_t total_difference = 0;

  for (int i = 0; i < size; i++) {
    int j = col1[i];
    int k = col2[i];
    int diff = 0;

    if (j > k) {
      differences[i] = j - k;
    } else if (k > j) {
      differences[i] = k - j;
    } else {
      differences[i] = 0;
    }
    total_difference = total_difference + differences[i];
  }

  printf("\nDifferences:\n");
  for (int i = 0; i < 30; i++) {
    printf("%d, ", differences[i]);
  }

  printf("\nTotal Difference: %zu\n ", total_difference);

  /* Part two */

  int similarity = 0;

  printf("\nColumn one repeats in col 2:\n");
  for (int i = 0; i < size; i++) {
    int repeated = repetitions_in_array(col1[i], col2, size);
    if (repeated) {
      printf("%d repeats in col 2 by: %d\n", col1[i], repeated);
      int simsum = col1[i] * repeated;
      similarity += simsum;
    }
  }

  printf("\nTotal simsum: %d\n", similarity);


  return 0;
}
