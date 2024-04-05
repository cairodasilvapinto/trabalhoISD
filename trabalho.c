#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Função para converter binário para decimal
int binarioParaDecimal(char *binario)
{
    int decimal = 0;
    int tamanho = strlen(binario);
    for (int i = 0; i < tamanho; i++)
    {
        if (binario[i] == '1')
        {
            decimal += pow(2, tamanho - 1 - i);
        }
    }
    // Se o bit mais significativo é 1, então o número é negativo
    if (binario[0] == '1')
    {
        decimal -= pow(2, tamanho); // Subtrai 2^n
    }
    return decimal;
}

// Função para converter decimal para hexadecimal
void decimalParaHexadecimal(int decimal, char *hexadecimal)
{
    if (decimal < 0)
    {
        decimal = 256 + decimal; // Adiciona 2^8 para obter o valor correto em complemento de dois
    }
    if (decimal < 16)
    {
        sprintf(hexadecimal, "0%X", decimal);
    }
    else
    {
        sprintf(hexadecimal, "%X", decimal);
    }
}

// Função para converter binário para hexadecimal
void binarioParaHexadecimal(char *binario, char *hexadecimal)
{
    int decimal = binarioParaDecimal(binario);
    decimalParaHexadecimal(decimal, hexadecimal);
}

// Função para realizar a operação de soma ou subtração em binário
void operacaoBinaria(char *num1, char *num2, char operacao, char *resultado)
{
    int tamanho = strlen(num1);
    int carry = 0;
    for (int i = tamanho - 1; i >= 0; i--)
    {
        int bit1 = num1[i] - '0';
        int bit2 = num2[i] - '0';
        if (operacao == '+')
        {
            // Soma em binário
            resultado[i] = (bit1 ^ bit2 ^ carry) + '0';
            carry = (bit1 & bit2) | (bit2 & carry) | (bit1 & carry);
        }
        else if (operacao == '-')
        {
            // Subtração em binário
            resultado[i] = (bit1 ^ bit2 ^ carry) + '0';
            carry = (~bit1 & bit2) | (~(bit1 ^ bit2) & carry);
        }
    }
    resultado[tamanho] = '\0';
    if (carry && operacao == '+')
    {
        // Overflow na soma, mantém apenas os 8 bits menos significativos
        memmove(resultado, resultado + 1, tamanho);
        resultado[tamanho - 1] = '0';
    }
}

void realizarOperacoesEImprimirResultado(char *primeiro, char operacao1, char *segundo, char operacao2, char *terceiro)
{
    char resultado1[9], resultadoFinal[9];
    char primeiroHex[3], segundoHex[3], terceiroHex[3], resultado1Hex[3], resultadoFinalHex[3];
    int primeiroDec, segundoDec, terceiroDec, resultado1Dec, resultadoFinalDec;

    // Converta os números binários para decimal e hexadecimal
    primeiroDec = binarioParaDecimal(primeiro);
    binarioParaHexadecimal(primeiro, primeiroHex);
    segundoDec = binarioParaDecimal(segundo);
    binarioParaHexadecimal(segundo, segundoHex);
    terceiroDec = binarioParaDecimal(terceiro);
    binarioParaHexadecimal(terceiro, terceiroHex);

    // Realize a primeira operação
    operacaoBinaria(primeiro, segundo, operacao1, resultado1);
    resultado1Dec = binarioParaDecimal(resultado1);
    binarioParaHexadecimal(resultado1, resultado1Hex);

    // Realize a segunda operação
    operacaoBinaria(resultado1, terceiro, operacao2, resultadoFinal);
    resultadoFinalDec = binarioParaDecimal(resultadoFinal);
    binarioParaHexadecimal(resultadoFinal, resultadoFinalHex);

    // Imprima o resultado
    printf("%sb (%di %sh)\n%c\n%sb (%di %sh)\n%c\n%sb (%di %sh)\n=\n%sb (%di %sh)\n",
           primeiro, primeiroDec, primeiroHex,
           operacao1,
           segundo, segundoDec, segundoHex,
           operacao2,
           terceiro, terceiroDec, terceiroHex,
           resultadoFinal, resultadoFinalDec, resultadoFinalHex);
}

int main()
{
    char primeiro[9], segundo[9], terceiro[9];
    char operacao1, operacao2;
    int continuar = 1;

    while (continuar)
    {
        printf("Informe o primeiro número binário ou -1 para sair: ");
        scanf("%s", primeiro);
        if (strcmp(primeiro, "-1") == 0)
        {
            continuar = 0;
            continue;
        }

        printf("Informe a operação (+ ou -): ");
        scanf(" %c", &operacao1);

        printf("Informe o segundo número binário: ");
        scanf("%s", segundo);

        printf("Informe a operação (+ ou -): ");
        scanf(" %c", &operacao2);

        printf("Informe o terceiro número binário: ");
        scanf("%s", terceiro);

        // Realize as operações e imprima o resultado
        realizarOperacoesEImprimirResultado(primeiro, operacao1, segundo, operacao2, terceiro);
    }

    return 0;
}
