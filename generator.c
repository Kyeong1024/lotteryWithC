#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CHAR 50
#define WIN_CHAR 1052

int *makeRandom(int (*winNum)[6]);

int main(void) {
  FILE *fp;
  char row[MAX_CHAR];
  char *token;
  int winNum[WIN_CHAR][6];
  int index = 0;
  int length = 0;
  int idx = 0;

  fp = fopen("result.csv", "r");

  // read csv
  while (feof(fp) != true) {
    fgets(row, MAX_CHAR, fp);
    token = strtok(row, ",");

    for (int i = 0; token != NULL; i++) {
      // pick and save only win numbers
      if (i == 2) {
        char *numToken = strtok(token, " ");
        int winNumers[6];

        for (int j = 0; j < 6; j++) {
          winNumers[j] = atoi(numToken);
          numToken = strtok(NULL, " ");
        }

        for (int k = 0; k < 5; k++) {
          winNum[idx][k] = winNumers[k];
        }
      }
      
      token = strtok(NULL, ",");
    }
    idx++;
  }

  int *randomNumber = makeRandom(winNum);

  printf(
    "%i %i %i %i %i %i\n", 
    randomNumber[0], 
    randomNumber[1], 
    randomNumber[2], 
    randomNumber[3], 
    randomNumber[4], 
    randomNumber[5]
  );
  return 0;
}

int *makeRandom(int (*winNum)[6]) {
  static int randomNumbers[6];
  int min;
  int minIndex = 0;

  // 난수 생성
  srand(time(NULL));

  for (int i = 0; i < 6; i++) {
    int random = (rand() % 45) + 1;
    randomNumbers[i] = random;
    
    if (i > 0) {
      for (int j = 0; j < i; j++) {
        if (randomNumbers[j] == random) {
          i--;
          break;
        }
      }
    }
  }

  for (int i = 0; i < 6; i++) {
    min = randomNumbers[i];
    for (int j = i; j < 6; j++) {
      if (randomNumbers[j] < min) {
        min = randomNumbers[j];
        minIndex = j;
      }
    }

    if (min != randomNumbers[i]) {
      int tmp = randomNumbers[i];
      randomNumbers[i] = min;
      randomNumbers[minIndex] = tmp;
    }
  }

    
  for (int i = 0; i < WIN_CHAR; i++) {
    bool isSame = false;
    int count = 1;
    for (int j = 0; j < 6; j++) {
      if (winNum[i][j] == randomNumbers[j]) {
        count++;
      }
    }

    if (count == 6) {
      return makeRandom(winNum);
    }

    count = 1;
  }


  return randomNumbers;
}