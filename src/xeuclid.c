/*
*
*	BN_add, BN_div, BN_mod
*	(int a, int b, int *x, int *y
*/

#include <stdio.h>
#include <openssl/bn.h>

BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b) {
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *tmp = BN_new(); //a -> r_1
    BIGNUM *r1 = BN_new(); //a -> r_1
    BIGNUM *q = BN_new(); 
    BIGNUM *r = BN_new();   //r
    BIGNUM *r2 = BN_new();  //b -> r_2
    BIGNUM *result_mul = BN_new();
    BIGNUM *s_1 = BN_new();
    BIGNUM *t_1 = BN_new();
    BIGNUM *s_2 = BN_new();
    BIGNUM *t_2 = BN_new();
    BIGNUM *s = BN_new();
    BIGNUM *t = BN_new();
    BN_dec2bn(&s_1,"1");
    BN_dec2bn(&t_1,"0");
    BN_dec2bn(&s_2, "0");
    BN_dec2bn(&t_2, "1");
    
    if ("0" == BN_bn2dec(b)){
        BIGNUM *gcd = BN_new();
        BN_copy(gcd, a);
        return gcd;
    } 
    

    BN_copy(r2, b); // new_r = b; 
    BN_copy(r1, a); //  tmp = a
    
    while (BN_is_zero(r2) != 1) {
        BN_div(q, r, r1, r2, ctx); //quotient = r / new_r;
        BN_mul(result_mul, q, s_2, ctx);
        BN_sub(s, s_1, result_mul); //t 값
        BN_mul(result_mul, q, t_2, ctx);
        BN_sub(t, t_1, result_mul); // s값

        BN_copy(r1, r2);
        BN_copy(r2, r);

        BN_copy(s_1, s_2);
        BN_copy(s_2, s);

        BN_copy(t_1, t_2);
        BN_copy(t_2, t);
    }
    BN_copy(x, s_1);
    BN_copy(y, t_1);
    return r1;
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
  
	printf("%s*(%s) + %s*(%s) = %s\n",
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
