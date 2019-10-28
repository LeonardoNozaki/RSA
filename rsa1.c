/*
Nome: José Vitor Novaes Santos RA: 743556
*/

#include <stdio.h>
#include <string.h>
#include <gmp.h>

void sam(mpz_t msg, mpz_t exp, mpz_t n);

int main(){
    char entrada[2049];
    mpz_t modulo;
    mpz_t exp;
    mpz_t mensagem;
    int base;

    //leitura da base
    scanf("%d%*c", &base);

    //leitura do n
    scanf("%[^\n]%*c", entrada);
    mpz_init(modulo);
    mpz_set_str(modulo, entrada, 10);

    //leitura da chave privada ou publica
    scanf("%[^\n]%*c", entrada);
    mpz_init(exp);
    mpz_set_str(exp, entrada, 10);

    //leitura da msg
    scanf("%[^\n]%*c", entrada);
    mpz_init(mensagem);
    mpz_set_str(mensagem, entrada, 10);

    sam(mensagem, exp, modulo);
    
    return 0;
}

void sam(mpz_t msg, mpz_t exp, mpz_t n){
    size_t index;
    mpz_t resultado;

    mpz_init(resultado);
    mpz_set(resultado, msg);

    index = (mpz_sizeinbase(exp, 2) - 1); //pega o numero de bits a partir do primeiro bit 1, -1 é para remover a contagem do \0
    index--;
    
    //anda de bit em bit realizando o quadrado e multiplicacao
    for(; index >= 0; index--){
        mpz_mul(resultado, resultado, resultado);
        mpz_mod(resultado, resultado, n);

        if(mpz_tstbit(exp, index)){ //teste o bit da posicao index e retorna se é 0 ou 1
            mpz_mul(resultado, resultado, msg);
            mpz_mod(resultado, resultado, n);
        }

        if(index == 0){
            break;
        }
    } 

    gmp_printf("%Zd\n", resultado);
}