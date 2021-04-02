#include <stdio.h>
// celsisu = 5 * (fahr-32)/9
double convert_to_celsius(float temp);


int main(int argc, char **argv) {
    // Print arguments
    int celsius;
    char str[20];
    strcpy(str, argv[1]);
    float tmpf;
    int tmpi;
    float tmp_val;
    for (int i = 0; i < argc; ++i)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    tmpf = atof(str);
    tmpi = atoi(str);
    // tmp_val = (float)tmp;
    printf("Value to be converted: %f", tmpf);
}


double convert_to_celsius(float temp) {
    return 5 * (temp-32)/9;
}

