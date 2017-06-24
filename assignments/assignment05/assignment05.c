/******************************************************************************/
/*                                                                            */
/*  Topic: Pointers                                                           */
/*                                                                            */
/*  Objective: Print values and addresses of values and so on                 */
/*                                                                            */
/*  Comments: Display all cases                                               */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

int main()
{
    // values
    int    i      = 25;
    float  f      = 3.142;
    double d      = 1.73217;
    char   s[20]  = "Hello, C Programmer";
    char   c      = 'x';

    // pointers
    int    *ip = &i;
    float  *fp = &f;
    double *dp = &d;
    char   *sp = s;
    char   *cp = &c;

    // pointers to pointers
    int    **ipp = &ip;
    float  **fpp = &fp;
    double **dpp = &dp;
    char   **spp = &sp;
    char   **cpp = &cp;

    // integer
    printf("Value of variable i: %d\n", i);
    printf("Address of variable i: %p\n", &i);
    printf("Value of pointer ip: %p\n", ip);
    printf("Address of pointer ip: %p\n", &ip);
    printf("Dereferenced value of pointer ip: %d\n", *ip);
    printf("Value of pointer to pointer ipp: %p\n", ipp);
    printf("Address of pointer to pointer ipp: %p\n", &ipp);
    printf("Dereferenced value of pointer ipp to pointer ip: %p\n\n", *ipp);

    // float
    printf("Value of variable f: %f\n", f);
    printf("Address of variable f: %p\n", &f);
    printf("Value of pointer fp: %p\n", fp);
    printf("Address of pointer fp: %p\n", &fp);
    printf("Dereferenced value of pointer fp: %f\n", *fp);
    printf("Value of pointer to pointer fpp: %p\n", fpp);
    printf("Address of pointer to pointer fpp: %p\n", &fpp);
    printf("Dereferenced value of pointer fpp to pointer fp: %p\n\n", *fpp);

    // double
    printf("Value of variable d: %f\n", d);
    printf("Address of variable d: %p\n", &d);
    printf("Value of pointer dp: %p\n", dp);
    printf("Address of pointer dp: %p\n", &dp);
    printf("Dereferenced value of pointer dp: %f\n", *dp);
    printf("Value of pointer to pointer dpp: %p\n", dpp);
    printf("Address of pointer to pointer dpp: %p\n", &dpp);
    printf("Dereferenced value of pointer dpp to pointer dp: %p\n\n", *dpp);

    // string
    printf("Value of variable s: %s\n", s);
    printf("Address of variable s: %p\n", &s);
    printf("Value of pointer sp: %p\n", sp);
    printf("Address of pointer sp: %p\n", &sp);
    printf("Dereferenced value of pointer sp: %s\n", (char *) sp);
    printf("Value of pointer to pointer spp: %p\n", spp);
    printf("Address of pointer to pointer spp: %p\n", &spp);
    printf("Dereferenced value of pointer spp to pointer sp: %p\n\n", *spp);

    // char
    printf("Value of variable c: %c\n", c);
    printf("Address of variable c: %p\n", &c);
    printf("Value of pointer cp: %p\n", cp);
    printf("Address of pointer cp: %p\n", &cp);
    printf("Dereferenced value of pointer cp: %c\n", *cp);
    printf("Value of pointer to pointer cpp: %p\n", cpp);
    printf("Address of pointer to pointer cpp: %p\n", &cpp);
    printf("Dereferenced value of pointer cpp to pointer cp: %p\n\n", *cpp);
}
