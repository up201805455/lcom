#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
    return binstr;
}

void print_usage(char *name) {
    printf("Usage: %s <action> <byte> <bit no>\n", name);
    printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
        "\t\t <byte> 8-bit integer in hexadecimal\n"
        "\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[]) {
    

 // alinea a)   Validar os argumentos de entrada e imprimir uma mensagem de erro apropriada, caso os valores não estejam correctos;     
    
    char action = argv[1][0]; // action: h , l , r , s, t
    unsigned long byte = strtol(argv[2], NULL , 16); // value to convert must be smaller than 256
    int bit = atoi(argv[3]); // bit to operate on : must be between 0 and 7

    if (argc != 4) {
        printf("Incorrect number of arguments\n");
        print_usage(argv[0]);
        return 1;
    }

    if (action != 'h' && action != 'l' && action != 'r' && action != 's' && action != 't' ){
        print_usage(argv[0]);
        printf("\t <action> must be one of h,l,r,s,t \n");
        return 1;
    }

    if(byte <0 || byte > (1<<8) -1){
        print_usage(argv[0]);
        printf("\t <byte> mmust be non-negative and smaller than 256 \n");
        return 1;
    }

    if(bit <0 || bit >7){
        print_usage(argv[0]);
        printf("\t <bit> mmust be between 0 and 7 \n");
        return 1;
    }

// alinea b) Imprimir os argumentos depois de estes serem validados (o segundo argumento deve ser imprimido em binário usando a função byte2bin);
    char binary[9];
    if(byte2bin(byte, binary) == NULL){
        printf("Error in decimal to binary translation\n");
        return 1;
    }
    printf("Number %s in hexadecimal is %ld in decimal and %s in binary\n", argv[2], byte, binary);

// alinea c) e d)

uint8_t result;
uint8_t mask = BIT(bit);

switch (action){

case 'h': case 'l':
    if(mask & byte){
        printf("Bit %d of number %ld is high (1)\n" , bit , byte);
    }
    else{
        printf("Bit %d of number %ld is lower (0)\n" , bit , byte);
    }
    break;

case 'r':
    result = byte & ~mask;
    printf("Reset bit %d of number %ld results in %d\n", bit, byte, result);
    break;

case 's':
    result = byte | mask;
    printf("Set bit %d of number %ld results in %d\n", bit, byte, result);
    break;

case 't':
    result = byte ^ mask;
    printf("Toggle bit %d of number %ld results in %d \n", bit, byte, result);
    break;

default:
   return 1;
}
return 0;

}
