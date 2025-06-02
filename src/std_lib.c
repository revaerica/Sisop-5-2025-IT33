#include "std_lib.h"

int div(int a, int b) {
    int sign, quotient;
    if (b == 0) return 0;
    sign = ((a < 0) ^ (b < 0)) ? -1 : 1;
    quotient = 0;

    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    while (a >= b) {
        a -= b;
        quotient++;
    }

    return sign * quotient;
}

int safe_mod(int a, int b) {
    while (a >= b) a -= b;
    return a;
}


int mod(int a, int b) {
    int r;
    if (b == 0) return 0;
    r = a - div(a, b) * b;
    return r;
}

bool strcmp(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

void strcpy(char *dst, char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;
    for ( i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num)
{
    int res = 0;
    int sign = 1;
    int i = 0;

    // Lewati spasi
    while (str[i] == ' ') i++;

    // Tangani tanda
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }

    *num = sign * res;
}

void itoa(int num, char *str)
{
    int i = 0, j, k;
    int is_negative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = 0 - num; 
    }

    while (num != 0) {
        int digit = num - (num / 10) * 10;
        str[i++] = digit + '0';
        num = num / 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}


