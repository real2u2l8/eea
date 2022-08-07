/*
*
*	BN_add, BN_div, BN_mod
*	(int a, int b, int *x, int *y
*/

#include <stdio.h>
#include <openssl/bn.h>

BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b){
	const char *str_0 = "0";
	const char *str_1 = "1";
    if (b == 0){
        BN_dec2bn(&x,str_0);
        BN_dec2bn(&y,str_1);

        return a;
    }
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *tmp = BN_new();
	BIGNUM *gcd = BN_new();
	BIGNUM *dv = BN_new();
	BIGNUM *rem = BN_new();

	BN_div(dv, rem, a, b, ctx);
    gcd = XEuclid(b, rem, x, y);
    tmp = y;
	BIGNUM *result_mul = BN_new();
	BIGNUM *result_sub = BN_new();
	BN_div(dv, rem, a, b, ctx);
	BN_mul(result_mul, dv, y, ctx);
	BN_sub(result_sub, x, result_mul);
	
    y = result_mul; 
    x = tmp;
    return gcd;
}

BIGNUM *extended_gcd(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b) {
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *tmp = BN_new();
	BIGNUM *gcd = BN_new();
	BIGNUM *dv = BN_new();
	BIGNUM *rem = BN_new();
    x = 1;
    y = 0;

    if (0 == b) return a;

    int new_x = 0;
    int new_y = 1;
    int new_r = b;
    int r = a;
    int quotient, tmp;
    while (new_r) {
        quotient = r / new_r;

        tmp = r;
        r = new_r;
        new_r = tmp - quotient * new_r;

        tmp = x;
        x = new_x;
        new_x = tmp - quotient * new_x;

        tmp = y;
        y = new_y;
        new_y = tmp - quotient * new_y;
    }
    return r;
}

void printBN(char *msg, BIGNUM * a)
{
    /* Use BN_bn2hex(a) for hex string * Use BN_bn2dec(a) for decimal string */
    char * number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main (int argc, char *argv[]){
	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *x = BN_new();
	BIGNUM *y = BN_new();
	BIGNUM *gcd;    

	if(argc != 3){
		printf("usage: xeuclid num1 num2");
		return -1;
	}
    BN_dec2bn(&a, argv[1]);
    BN_dec2bn(&b, argv[2]);
    gcd = XEuclid(x,y,a,b);

    printBN("(a,b) = ", gcd);
    printBN("a = ", a);
    printBN("b = ", b);
    printBN("x = ", x);
    printBN("y = ", y);
  
	printf("%s*(%s) + %s*(%s) = %s\\n",
										BN_bn2dec(a),
										BN_bn2dec(x),
										BN_bn2dec(b),
										BN_bn2dec(y),
										BN_bn2dec(gcd));

    if(a != NULL) BN_free(a);
    if(b != NULL) BN_free(b);
    if(x != NULL) BN_free(x);
    if(y != NULL) BN_free(y);
    if(gcd != NULL) BN_free(gcd);
  
	return 0;
}
