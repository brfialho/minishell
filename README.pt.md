*Este projeto foi criado como parte do currículo da 42 por brfialho, rafreire.*

# 🔥 Minishell 🔥

Uma implementação simples de shell escrita em C, replicando funcionalidades centrais do bash.

---

## Descrição

**Minishell** é um shell Unix minimalista que interpreta e executa comandos, fornecendo uma interface de linha de comando interativa. Este projeto visa aprofundar o entendimento de gerenciamento de processos, descritores de arquivo, tratamento de sinais e técnicas de parsing em C.

### Principais Funcionalidades

- **Execução de Comandos**: Executa binários do `PATH` ou caminhos absolutos/relativos
- **Comandos Built-in**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipes**: Encadeia comandos usando o operador `|`
- **Redirecionamentos**: Entrada (`<`), saída (`>`), append (`>>`) e heredoc (`<<`)
- **Operadores Lógicos**: `&&` e `||` para execução condicional de comandos
- **Variáveis de Ambiente**: Expansão de `$VAR` e `$?` (último status de saída)
- **Tratamento de Aspas**: Aspas simples (`'`) e duplas (`"`) com regras corretas de expansão
- **Tratamento de Sinais**: `Ctrl+C`, `Ctrl+D` e `Ctrl+\` se comportam como no bash
- **Histórico de Comandos**: Navegue por comandos anteriores usando as setas

---

## Instruções

### Pré-requisitos

- **GCC** ou **Clang**
- **GNU Make**
- **Biblioteca Readline** (com headers de desenvolvimento)

No Debian/Ubuntu, instale o readline com:
```bash
sudo apt-get install libreadline-dev
```

No macOS com Homebrew:
```bash
brew install readline
```

### Compilação

Clone o repositório e compile usando `make`:

```bash
git clone --recurse-submodule https://github.com/brfialho/minishell.git
cd minishell
make
```

Isso gerará o executável `minishell`.

### Comandos Disponíveis do Make

| Comando       | Descrição                                        |
|---------------|--------------------------------------------------|
| `make`        | Compila o projeto                                |
| `make clean`  | Remove arquivos objeto                           |
| `make fclean` | Remove arquivos objeto e o executável            |
| `make re`     | Recompila do zero                                |
| `make leaks`  | Executa com Valgrind para detectar vazamentos    |
| `make test`   | Suíte de testes customizada com testes unitários |

### Suíte de testes

O projeto inclui uma suíte de testes unitários focada em validar alguns dos componentes mais críticos do shell.

A cobertura atual inclui:

Tokenização do lexer
Comportamento do parser e geração da AST
Lógica de expansão e tratamento de variáveis de ambiente

Execute os testes com:

```bash
make test
```

Os testes foram projetados para ajudar a validar a corretude do parser e prevenir regressões durante o desenvolvimento.

### Execução

Depois de compilar, inicie o shell:

```bash
./minishell
```

### Exemplos de Uso

```bash
# Execução simples de comandos
🔥Minihell🔥 /path$ ls -la

# Pipes
🔥Minihell🔥 /path$ cat file.txt | grep "pattern" | wc -l

# Redirecionamentos
🔥Minihell🔥 /path$ echo "Hello World" > output.txt
🔥Minihell🔥 /path$ cat < input.txt >> output.txt

# Heredoc
🔥Minihell🔥 /path$ cat << EOF
> Line 1
> Line 2
> EOF

# Variáveis de ambiente
🔥Minihell🔥 /path$ echo $HOME
🔥Minihell🔥 /path$ export MY_VAR="value"
🔥Minihell🔥 /path$ echo $MY_VAR

# Operadores lógicos
🔥Minihell🔥 /path$ ls && echo "Success"
🔥Minihell🔥 /path$ false || echo "Fallback"

# Sair com código de status
🔥Minihell🔥 /path$ exit 42
```

---

## Arquitetura do Projeto

```
minishell/
├── includes/          # Arquivos de header
├── libft/             # Biblioteca C customizada
├── srcs/
│   ├── builtins/      # Implementações dos comandos built-in
│   ├── env/           # Gerenciamento de variáveis de ambiente
│   ├── execution/     # Execução de comandos, pipes, redirecionamentos
│   ├── expansion/     # Expansão de variáveis e aspas
│   ├── heredoc/       # Tratamento de heredoc
│   |── lexer/         # Tokenização
│   |── parser/        # Construção da AST
│   ├── prompt/        # Exibição do prompt
│   └── signals/       # Tratamento de sinais
└── tests/             # Suíte de testes
```

---

## Recursos

### Documentação e Referências

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - Documentação oficial do GNU Bash
- [Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/readline.html) - Manual do GNU Readline

### Tutoriais e Artigos

- [Let's Build a Linux Shell - Part I](https://brennan.io/2015/01/16/write-a-shell-in-c/) - Stephen Brennan

### Uso de IA

Ferramentas de IA (GitHub Copilot) foram usadas neste projeto para:
- **Arquitetura do código**: Assistência no planejamento do design do workflow.
- **Documentação**: Assistência na escrita de comentários e deste README
- **Apoio em debugging**: Identificação de possíveis problemas e sugestões de correções
- **Pesquisa**: Consultas rápidas sobre system calls e funções de biblioteca

---

## Autores

 - [**rafreire**](https://github.com/AlmeidaRafaelFeh)
 - [**brfialho**](https://github.com/brfialho)

---

## Licença

Este projeto faz parte do currículo da 42 School. Todos os direitos reservados.
