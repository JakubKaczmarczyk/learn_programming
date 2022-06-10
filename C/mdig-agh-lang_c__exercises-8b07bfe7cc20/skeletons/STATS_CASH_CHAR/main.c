#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // STATS
    double a = 1.0;
    double b = 2.0;
    double c= 3.0;
    printf("Suma: %.3f, srednia: %f\n",(a+b+c), ((a+b+c)/3.0));

    // CASH
    const double USD_TO_EUR = 0.77;
    const double USD_TO_PLN = 3.40;
    unsigned int one_dollar_papers = 3;
    printf("%d USD = %7.2f EUR\n",one_dollar_papers, (double) one_dollar_papers*USD_TO_EUR);
    printf("%d USD = %7.2f PLN\n",one_dollar_papers, (double) one_dollar_papers*USD_TO_PLN);

    // CHAR
    const unsigned int kod = 65;
    printf("znak: %c", kod);
    return EXIT_SUCCESS;
}
