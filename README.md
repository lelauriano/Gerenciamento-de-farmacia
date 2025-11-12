# Sistema de Gerenciamento de Farmácia 💊

Este é um projeto simples em C para gerenciar, cadastar, excluir, atualizar e listar clientes, funcionários, medicamentos e vendas de uma farmácia.

## 🛠️ Como Compilar

Este projeto é dividido em múltiplos arquivos e precisa ser compilado.

**Dependências:**
* Um compilador C (como o **GCC**)
* O utilitário Make (opcional, mas recomendado)

Método 1: Usando Make (Recomendado)

Se você tiver o make instalado, basta executar o comando make no seu terminal:

make


O Makefile incluído no projeto cuidará de compilar tudo automaticamente.

Método 2: Usando GCC Manualmente

Se você não tiver o make, pode compilar todos os arquivos-fonte manualmente com o GCC:

gcc main.c farmacia.c -o programa_farmacia


Como Executar:

Após a compilação (usando qualquer um dos métodos), um arquivo executável chamado programa_farmacia (ou programa_farmacia.exe no Windows) será criado.

Para executá-lo:
# No Windows (PowerShell)
./programa_farmacia.exe
