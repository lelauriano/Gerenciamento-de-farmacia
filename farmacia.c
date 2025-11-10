#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Sistema de Administração de Farmácia*/
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

void cadastrarFuncionario(FILE* fp) {
    struct funcionario func;
    fp = fopen("funcionarios.bin", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    printf("\t\tCADASTRO DE FUNCIONARIO\n\n");

    printf("Digite o ID:\n");
    scanf("%d", &func.id);
    getchar();                                  //Limpa o buffer do scanf

    printf("Digite o nome:\n");
    fgets(func.nome, 50, stdin);
    func.nome[strcspn(func.nome, "\n")] = 0;    //Limpa o buffer do fgets

    printf("Digite o CPF:\n");
    fgets(func.cpf, 50, stdin);
    func.cpf[strcspn(func.cpf, "\n")] = 0;

    printf("Digite o salario:\n");
    scanf("%f", &func.salario);
    getchar();

    printf("Digite o endereco:\n");
    fgets(func.endereco, 50, stdin);
    func.endereco[strcspn(func.endereco, "\n")] = 0;

    printf("Digite o telefone:\n");
    fgets(func.telefone, 50, stdin);
    func.telefone[strcspn(func.telefone, "\n")] = 0;

    printf("Digite o e-mail:\n");
    fgets(func.email, 50, stdin);
    func.email[strcspn(func.email, "\n")] = 0;

    fwrite(&func, sizeof(func), 1, fp);
    fclose(fp);

    printf("\nCadastro realizado com sucesso\n\n");
}

void cadastrarCliente(FILE* fp) {
    struct cliente cli;
    fp = fopen("clientes.bin", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    printf("\t\tCADASTRO DE CLIENTE\n\n");

    printf("Digite o ID:\n");
    scanf("%d", &cli.id);
    getchar();

    printf("Digite o nome:\n");
    fgets(cli.nome, 50, stdin);
    cli.nome[strcspn(cli.nome, "\n")] = 0;

    printf("Digite o CPF:\n");
    fgets(cli.cpf, 14, stdin);
    cli.cpf[strcspn(cli.cpf, "\n")] = 0;

    printf("Digite o telefone:\n");
    fgets(cli.telefone, 50, stdin);
    cli.telefone[strcspn(cli.telefone, "\n")] = 0;

    printf("Digite a(s) alergia(s):\n");
    fgets(cli.alergias, 80, stdin);
    cli.alergias[strcspn(cli.alergias, "\n")] = 0;

    fwrite(&cli, sizeof(cli), 1, fp);
    fclose(fp);

    printf("\nCadastro realizado com sucesso\n\n");
}

void cadastrarMedicamento(FILE* fp) {
    struct medicamento med;
    fp = fopen("medicamentos.bin", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\t\tCADASTRO DE MEDICAMENTO\n\n");

    printf("Digite o ID:\n");
    scanf("%d", &med.id);
    getchar();

    printf("Digite o nome:\n");
    fgets(med.nome, 30, stdin);
    med.nome[strcspn(med.nome, "\n")] = 0;

    printf("Digite o fabricante:\n");
    fgets(med.fabricante, 30, stdin);
    med.fabricante[strcspn(med.fabricante, "\n")] = 0;

    printf("Digite a dosagem:\n");
    scanf("%f", &med.dosagem);
    getchar();

    printf("Digite o preco:\n");
    scanf("%f", &med.preco);
    getchar();

    printf("Digite a quantidade\n");
    scanf("%d", &med.quantidade);
    getchar();

    fwrite(&med, sizeof(med), 1, fp);
    fclose(fp);

    printf("\nCadastro realizado com sucesso\n\n");
}

void registrarVendas(FILE* fp) {
    struct venda ven;
    struct medicamento med;
    fp = fopen("registro_vendas.bin", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\t\tREGISTRO DE VENDAS\n\n");

    printf("Digite o ID do cliente:\n");
    scanf("%d", &ven.idCliente);
    getchar();

    printf("Digite o ID do medicamento:\n");
    scanf("%d", &ven.idMed);
    getchar();

    printf("Digite a quantidade vendida:\n");
    scanf("%d", &ven.quantidade);
    getchar();
    
    printf("Digite o valor total:\n");
    scanf("%f", &ven.valorTotal);

    FILE* ptrMed;
    ptrMed = fopen("medicamentos.bin", "rb");
    if(ptrMed == NULL) {
        printf("Erro ao abrir arquivo de medicamentos\n");
        return;
    }

    FILE* ptrTemp;
    ptrTemp = fopen("temp.bin", "wb");
    if(ptrTemp == NULL) {
        printf("Erro ao abrir arquivo temporario\n\n");
        return;
    }

    int encontrado = 0;
    while (fread(&med, sizeof(med), 1, ptrMed) == 1) {
        if (med.id == ven.idMed) {
            if (med.quantidade >= ven.quantidade) {
                med.quantidade = med.quantidade - ven.quantidade; //Atualiza a quantidade de medicamentos em estoque
                encontrado = 1;
            }
            else {
                printf("Estoque insuficiente\n");
                return;
            }
        }
        fwrite(&med, sizeof(med), 1, ptrTemp); //Copia os dados do arquivo principal para o temporário com a quantidade de medicamentos atualizada
    }

    fclose(ptrMed);
    fclose(ptrTemp);
    remove("medicamentos.bin"); //Exclui o arquivo obsoleto
    rename("temp.bin", "medicamentos.bin"); //Transforma o arquivo temporário atualizado no arquivo principal

    if(encontrado == 0) {
        printf("Medicamento nao encontrado\n\n");
        return;
    }

    fwrite(&ven, sizeof(ven), 1, fp);
    fclose(fp);

    printf("\nVenda registrada com sucesso\n\n");
}

void relatorioVendas(FILE* fp) {
    struct venda ven;
    fp = fopen("registro_vendas.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    printf("\t\tRELATORIO DE VENDAS\n\n");
    
    while (fread(&ven, sizeof(ven), 1, fp) == 1) {
        printf("ID do comprador: %d\nID do medicamento: %d\nQuantidade: %d\nValor: %.2f\n\n", ven.idCliente, ven.idMed, ven.quantidade, ven.valorTotal);
    }

    fclose(fp);
}

void relatorioEstoque(FILE* fp) {
    struct medicamento med;
    fp = fopen("medicamentos.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    printf("\t\tRELATORIO DE ESTOQUE\n\n");

    while(fread(&med, sizeof(med), 1, fp) == 1) {
        printf("ID do medicamento: %d\nNome do medicamento: %s\nNome do fabricante: %s\nDosagem: %f\nPreco: %f\nQuantidade: %d\n\n", med.id, med.nome, med.fabricante, med.dosagem, med.preco, med.quantidade);
    }

    fclose(fp);
}

FILE* excluirFuncionario(FILE* fp) {
    struct funcionario func;
    fp = fopen("funcionarios.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo");
        return NULL;
    }

    int idBusca;
    int encontrado = 0;
    FILE* ptrTemp;
    ptrTemp = fopen("temp.bin", "wb");
    if (ptrTemp == NULL) {
        printf("Erro ao abrir arquivo temporario\n\n");
        return NULL;
    }

    printf("Digite o ID do funcionario a ser removido do sistema:\n");
    scanf("%d", &idBusca);

    while (fread(&func, sizeof(func), 1, fp) == 1) {
        if (func.id == idBusca) {
            encontrado = 1;
            printf("Funcionario excluido\n\n");
        }
        else {
            fwrite(&func, sizeof(func), 1, ptrTemp); //Copia os dados do arquivo principal para o temporário sem o funcionário excluído
        }
    }

    fclose(fp);
    fclose(ptrTemp);
    remove("funcionarios.bin"); //Exclui o arquivo obsoleto
    rename("temp.bin", "funcionarios.bin"); //Transforma o arquivo temporário atualizado no arquivo principal

    if (encontrado == 0) {
        printf("Funcionario nao encontrado\n\n");
    }
}

FILE* excluirCliente(FILE* fp) {
    struct cliente cli;
    fp = fopen("clientes.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return NULL;
    }

    int idBusca;
    int encontrado = 0;
    FILE* ptrTemp;
    ptrTemp = fopen("temp.bin", "wb");
    if (ptrTemp == NULL) {
        printf("Erro ao abrir arquivo temporario\n\n");
        return NULL;
    }

    printf("Digite o ID do cliente a ser removido do sistema:\n");
    scanf("%d", &idBusca);

    while (fread(&cli, sizeof(cli), 1, fp) == 1) {
        if (cli.id == idBusca) {
            encontrado = 1;
            printf("Cliente excluido\n\n");
        }
        else {
            fwrite(&cli, sizeof(cli), 1, ptrTemp); //Copia os dados do arquivo principal para o temporário sem o cliente excluído
        }
    }

    fclose(fp);
    fclose(ptrTemp);
    remove("clientes.bin"); //Exclui o arquivo obsoleto
    rename("temp.bin", "clientes.bin"); //Transforma o arquivo temporário atualizado no arquivo principal

    if (encontrado == 0) {
        printf("Cliente nao encontrado\n\n");
    }
}

FILE* excluirMedicamento(FILE* fp) {
    struct medicamento med;
    fp = fopen("medicamentos.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return NULL;
    }

    int idBusca;
    int encontrado = 0;
    FILE* ptrTemp;
    ptrTemp = fopen("temp.bin", "wb");
    if (ptrTemp == NULL) {
        printf("Erro ao abrir arquivo temporario\n\n");
        return NULL;
    }

    printf("Digite o ID do medicamento a ser removido do sistema:\n");
    scanf("%d", &idBusca);

    while (fread(&med, sizeof(med), 1, fp) == 1) {
        if (med.id == idBusca) {
            encontrado = 1;
            printf("Medicamento excluido\n\n");
        }
        else {
            fwrite(&med, sizeof(med), 1, ptrTemp); //Copia os dados do arquivo principal para o temporário sem o medicamento excluído
        }
    }

    fclose(fp);
    fclose(ptrTemp);
    remove("medicamentos.bin"); //Exclui o arquivo obsoleto
    rename("temp.bin", "medicamentos.bin"); //Transforma o arquivo temporário atualizado no arquivo principal

    if (encontrado == 0) {
        printf("Medicamento nao encontrado\n\n");
    }
}

//Lista todos os funcionários cadastrados no sistema
void listarFuncionario(FILE* fp) {
    struct funcionario func;
    fp = fopen("funcionarios.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    int contador = 0;

    printf("\t\tLISTA DE FUNCIONARIOS\n\n");

    while(fread(&func, sizeof(func), 1, fp) == 1) {
        printf("---------------------------------------------------------------------------\n");
        printf("ID: %d\n", func.id);
        printf("Nome: %s\n", func.nome);
        printf("CPF: %s\n", func.cpf);
        printf("Salario: %.2f\n", func.salario);
        printf("Endereco: %s\n", func.endereco);
        printf("Telefone: %s\n", func.telefone);
        printf("E-mail: %s\n", func.email);
        printf("---------------------------------------------------------------------------\n\n");
        contador++;
    }

    if (contador == 0) {
        printf("Nao ha funcionarios para exibir\n\n");
    }

    fclose(fp);
}

//Lista todos os clientes cadastrados no sistema
void listarCliente(FILE* fp) {
    struct cliente cli;
    fp = fopen("clientes.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    int contador = 0;

    printf("\t\tLISTA DE CLIENTES\n\n");

    while(fread(&cli, sizeof(cli), 1, fp) == 1) {
        printf("---------------------------------------------------------------------------\n");
        printf("ID: %d\n", cli.id);
        printf("Nome: %s\n", cli.nome);
        printf("CPF: %s\n", cli.cpf);
        printf("Telefone: %s\n", cli.telefone);
        printf("Alergias: %s\n", cli.alergias);
        printf("---------------------------------------------------------------------------\n\n");
        contador++;
    }

    if (contador == 0) {
        printf("Nao ha clientes para exibir\n\n");
    }

    fclose(fp);
}

//Lista todos os medicamentos cadastrados no sistema
void listarMedicamento(FILE* fp) {
    struct medicamento med;
    fp = fopen("medicamentos.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n\n");
        return;
    }

    int contador = 0;

    printf("\t\tLISTA DE MEDICAMENTOS\n\n");

    while(fread(&med, sizeof(med), 1, fp) == 1) {
        printf("---------------------------------------------------------------------------\n");
        printf("ID: %d\n", med.id);
        printf("Nome: %s\n", med.nome);
        printf("Fabricante: %s\n", med.fabricante);
        printf("Dosagem: %.2fmg\n", med.dosagem);
        printf("Preco: %.2f\n", med.preco);
        printf("Quantidade: %d\n", med.quantidade);
        printf("---------------------------------------------------------------------------\n\n");
        contador++;
    }

    if (contador == 0) {
        printf("Nao ha medicamentos para exibir\n\n");
    }

    fclose(fp);
}

//Função recursiva que roda até o usuário digitar '0' para sair
int menu() {
    FILE* fp;
    int opcao;

    printf("\n\t\t==== SISTEMA DE GERENCIAMENTO DE FARMACIA ====\n\n");
    printf("Selecione uma opcao:\n\n");
    printf("1. Cadastrar funcionario\n");
    printf("2. Cadastrar cliente\n");
    printf("3. Cadastrar medicamento\n");
    printf("4. Registrar venda\n");
    printf("5. Gerar relatorio de vendas\n");
    printf("6. Gerar relatorio de estoque\n");
    printf("7. Excluir funcionario\n");
    printf("8. Excluir cliente\n");
    printf("9. Excluir medicamento\n");
    printf("10. Listar funcionarios\n");
    printf("11. Listar clientes\n");
    printf("12. Listar medicamentos\n");
    printf("0. Sair\n\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            cadastrarFuncionario(fp);
            break;
        case 2:
            cadastrarCliente(fp);
            break;
        case 3:
            cadastrarMedicamento(fp);
            break;
        case 4:
            registrarVendas(fp);
            break;
        case 5:
            relatorioVendas(fp);
            break;
        case 6:
            relatorioEstoque(fp);
            break;
        case 7:
            excluirFuncionario(fp);
            break;
        case 8:
            excluirCliente(fp);
            break;
        case 9:
            excluirMedicamento(fp);
            break;
        case 10:
            listarFuncionario(fp);
            break;
        case 11:
            listarCliente(fp);
            break;
        case 12:
            listarMedicamento(fp);
            break;
        case 0:
            printf("\nSaindo...\n\n");
            return 0;
        default:
            printf("\nOpcao invalida\n\n");
    }

    menu();
    
    fclose(fp);
    return 0;
}

int main () {

    menu();

    return 0;
}