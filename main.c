#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
   int x;
   int y;
} Point;

int main(int argc, char *argv[]){
    if (argc != 3)
    {
        printf("Usage: %s <coords_file> <radius>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int radius = atoi(argv[2]);

    // srand((unsigned int)time(NULL));


    // FILE *file = fopen(filename, "w");
    // if (!file) {
    //     perror("Error opening file");
    //     return 1;
    // }

    // int numTargets = 100; 

    // // Заполнение файла случайными координатами
    // for (int i = 0; i < numTargets; i++) {
    //     int x = rand() % 100; 
    //     int y = rand() % 100; 
    //     fprintf(file, "%d,%d\n", x, y);
    // }

    // fclose(file);

    FILE *file1 = fopen(filename, "r");
    if (!file1)
    {
        perror("Error opening");
        return 1;
    }

    Point centroid = {0, 0};
    int targets = 0;
    int affectTarget = 0;

    while (!feof(file1))
    {
        Point target;
        if (fscanf(file1, "%d,%d", &target.x, &target.y) == 2)
        {
            centroid.x += target.x;
            centroid.y += target.y;
            targets++;
        }
        
    }

    if (targets > 0)
    {
        centroid.x /= targets;
        centroid.y /= targets;
    }
    
    rewind(file1);

        while (!feof(file1)) 
        {
        Point target;
        if (fscanf(file1, "%d,%d", &target.x, &target.y) == 2) 
        {
            int distance = abs(target.x - centroid.x) + abs(target.y - centroid.y);
            if (distance <= radius) 
            {
                affectTarget++;
            }
        }
    }

    printf("Optimal launch coordinates: (%d, %d)\n", centroid.x, centroid.y);
    printf("Number of affected targets: %d\n", affectTarget);

    fclose(file1);
    return 0;
    
    
}