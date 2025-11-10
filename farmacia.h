#ifndef FARMACIA_H
#define FARMACIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Sistema de Administração de Farmácia */
struct cliente{
    int id;
    char nome[50];
    char cpf[14];
    char telefone[12];
    char alergias[80];
};

struct funcionario{
    int id;
    char nome[50];
    char cpf[14];
    float salario;
    char endereco[50];
    char telefone[12];
    char email[50];
};

struct medicamento{
    int id;
    char nome[30];
    char fabricante[30];
    float dosagem;
    float preco;
    int quantidade;
};

struct venda{
    int idCliente;
    int idMed;
    int quantidade;
    float valorTotal;
};

/* Protótipos de funções do sistema farmácia*/
void cadastrarFuncionario(FILE* fp);
void cadastrarCliente(FILE* fp);
void cadastrarMedicamento(FILE* fp);

void registrarVendas(FILE* fp);
void relatorioVendas(FILE* fp);
void relatorioEstoque(FILE* fp);

FILE* excluirFuncionario(FILE* fp);
FILE* excluirCliente(FILE* fp);
FILE* excluirMedicamento(FILE* fp);

void listarFuncionario(FILE* fp);
void listarCliente(FILE* fp);
void listarMedicamento(FILE* fp);

FILE* atualizarFuncionario(FILE* fp);
FILE* atualizarCliente(FILE* fp);
FILE* atualizarMedicamento(FILE* fp);

int menu();
#endif 
