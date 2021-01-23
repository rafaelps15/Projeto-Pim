#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>



struct funcionario
{
    char usuario[20];
    char senha[20];
};

struct data
{
    int dia;
    int mes;
    int ano;
};

struct paciente
{
    char nome[20];
    int possuiCovid;
    struct data dataDiagnostico;
    int possuiComorbidade;
    int grupoRisco;
    char cpf[20];
    char telefone[20];
    char rua[20];
    int numeroCasa;
    char bairro[20];
    char cidade[20];
    char estado[20];
    char cep[20];
    char email[20];
    struct data dataNascimento;
};

int logado = 0;

void exibirTitulo(char mensagem[20]);

void adicionarFuncionario();
void loginFuncionario();
void listarFuncionarios();

void adicionarPaciente();
void listarPacientes();
void listarPacientesCovid();
void listarPacientesGrupoRisco();

char esperarEntrada();
void imprimirSeparador();
void imprimirTitulo(char titulo[]);

void salvarPaciente(struct paciente paciente, char arquivo[]);
void salvarFuncionario(struct funcionario paciente, char arquivo[]);

char funcionarioFile[] = {"funcionarios.dat"};
char pacienteFile[] = {"pacientes.dat"};
char pacienteGrupoRisco[] = {"paciente_grupo_risco.dat"};

int main()
{

    setlocale(LC_ALL, "");
    int escolha;

    while (1)
    {
        system("cls");

        imprimirTitulo("Gerenciamento paciente COVID-19");
        printf("1. Adicionar Funcionário\n\n");
        printf("2. Login\n\n");
        printf("3. Exibir todos funcionários\n\n");
        printf("4. Adicionar Paciente\n\n");
        printf("5. Exibir todos pacientes\n\n");
        printf("6. Exibir todos pacientes com COVID-19\n\n");
        printf("7. Exibir todos pacientes do Grupo de Risco\n\n");
        printf("0. Exit\n\n ");

        imprimirSeparador();

        printf("\nEscolha uma opção abaixo: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            adicionarFuncionario();
            break;

        case 2:
            loginFuncionario();
            break;

        case 3:
            listarFuncionarios();
            break;

        case 4:
            adicionarPaciente();
            break;

        case 5:
            listarPacientes();
            break;

        case 6:
            listarPacientesCovid();
            break;

        case 7:
            listarPacientesGrupoRisco();
            break;

        case 0:
            exit(0);
        }

        printf("\n\nPessione enter para continuar ");
        esperarEntrada();
    }

    return 0;
}

void adicionarFuncionario()
{

    struct funcionario funcionario;

    printf("\nEntre com o usuário: ");
    scanf("%s", funcionario.usuario);
    fflush(stdin);

    printf("\nEntre com a senha: ");
    scanf("%s", funcionario.senha);
    fflush(stdin);

    salvarFuncionario(funcionario, funcionarioFile);
}

void loginFuncionario()
{

    FILE *fp;
    struct funcionario funcionario;

    char usuario[20];
    char senha[20];

    fp = fopen(funcionarioFile, "rb");

    printf("\nEntre com o usuário: ");
    scanf("%s", usuario);
    fflush(stdin);

    printf("\nEntre com a senha: ");
    scanf("%s", senha);

    while (1)
    {
        fread(&funcionario, sizeof(funcionario), 1, fp);

        if (feof(fp))
            break;

        if (strcmp(funcionario.usuario, usuario) == 0 && strcmp(funcionario.senha, senha) == 0)
        {
            logado = 1;
            imprimirSeparador();
            printf("Funcionário logado com sucesso\n\n");
            printf("%s\t\n", funcionario.usuario);
            break;
        }
    }
    if (logado == 0)
    {
        printf("\nNenhum funcionário encontrado com esse login e senha");
    }
    fclose(fp);
}

void listarFuncionarios()

{
    if (logado == 0)
    {
        printf("\nÉ necessário estar logado para listar os funcionários\n");
        return;
    }

    FILE *fp;
    struct funcionario funcionario;
    int contador = 0;

    fp = fopen(funcionarioFile, "rb");

    imprimirSeparador();
    printf("\t\t Todos Funcionários\n\n");
    imprimirSeparador();

    printf("Usuário: \n\n");

    while (1)
    {
        fread(&funcionario, sizeof(funcionario), 1, fp);

        if (feof(fp))
            break;

        printf("%d - %s\t\n\n", ++contador, funcionario.usuario);
    }

    imprimirSeparador();

    fclose(fp);
}

void adicionarPaciente()
{
    if (logado == 0)
    {
        exibirTitulo("\nEfetue o login para adicionar paciente\n");
        return;
    }

    struct paciente paciente;

    int covid = 0;
    int comorbidade = 0;

    printf("\nEntre com o nome do paciente: ");
    fgets(paciente.nome, sizeof(paciente.nome), stdin);
    scanf("%[^\n]", paciente.nome);

    printf("\nPaciente está com COVID :\n1 - SIM\n2 - Não\n\n");
    scanf("%d", &covid);

    if (covid == 1)
    {
        printf("\nData do diagnóstico: ");
        scanf("%d/%d/%d", &paciente.dataDiagnostico.dia, &paciente.dataDiagnostico.mes, &paciente.dataDiagnostico.ano);
    }

    printf("\nExiste alguma comorbidade :\n1 - SIM\n2 - Não\n\n");
    scanf("%d", &comorbidade);

    printf("\nDigite o CPF: ");
    scanf("%s", paciente.cpf);

    printf("\nDigite o telefone: ");
    scanf("%s", paciente.telefone);

    printf("\nDigite o nome da rua: ");
    fgets(paciente.rua, sizeof(paciente.rua), stdin);
    scanf("%[^\n]", paciente.rua);

    printf("\nDigite a número da casa: ");
    scanf("%d", &paciente.numeroCasa);

    printf("\nDigite o bairro: ");
    fgets(paciente.bairro, sizeof(paciente.bairro), stdin);
    scanf("%[^\n]", paciente.bairro);

    printf("\nDigite a cidade:");
    fgets(paciente.cidade, sizeof(paciente.cidade), stdin);
    scanf("%[^\n]", paciente.cidade);

    printf("\nDigite o estado: ");
    fgets(paciente.estado, sizeof(paciente.estado), stdin);
    scanf("%[^\n]", paciente.estado);

    printf("\nDigite o CEP: ");
    scanf("%s", paciente.cep);

    printf("\nDigite a data de nascimento: ");
    scanf("%d/%d/%d", &paciente.dataNascimento.dia, &paciente.dataNascimento.mes, &paciente.dataNascimento.ano);

    printf("\nDigite o email: ");
    scanf("%s", paciente.email);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    paciente.grupoRisco = (tm.tm_year + 1900) - paciente.dataNascimento.ano >= 65 ? 1 : 0;
    paciente.possuiCovid = covid == 1 ? 1 : 0;
    paciente.possuiComorbidade = comorbidade == 1 ? 1 : 0;

    if (paciente.grupoRisco == 1)
    {
        struct paciente grupoRisco;
        strcpy(grupoRisco.cep, paciente.cep);
        grupoRisco.dataNascimento = paciente.dataNascimento;
        salvarPaciente(grupoRisco, pacienteGrupoRisco);
        return;
    }

    salvarPaciente(paciente, pacienteFile);
}

void listarPacientes()
{

    if (logado == 0)
    {
        printf("\nPara exibir os pacientes o funcionário deve estar logado\n");
        return;
    }



    FILE *fp;
    struct paciente paciente;

    fp = fopen(pacienteFile, "rb");

    if (fp == NULL)
    {
        printf("\nNenhum paciente cadastrado\n\n");
        return;
    }

    imprimirSeparador();
    printf("\t\t Todos Pacientes\n\n");
    imprimirSeparador();

    while (1)
    {
        fread(&paciente, sizeof(paciente), 1, fp);

        if (feof(fp))
            break;

        printf("Paciente: %s\n", paciente.nome);

        if(paciente.possuiCovid == 1)
        {
            printf("Possui COVID: SIM\n");
            printf("Data do diagnóstico: %d/%d/%d\n", paciente.dataDiagnostico.dia, paciente.dataDiagnostico.mes, paciente.dataDiagnostico.ano);
        }
        else
        {
            printf("Possui COVID: NÃO\n");
        }

        printf("Possui comorbidade: %s", paciente.possuiComorbidade == 0 ? "Não\n" : "Sim\n");
        printf("Pertence ao grupo de risco: %s", paciente.grupoRisco == 0 ? "Não\n" : "Sim\n");
        printf("CPF: %s\n", paciente.cpf);
        printf("Telefone: %s\n", paciente.telefone);
        printf("Rua: %s\n", paciente.rua);
        printf("Número casa: %d\n", paciente.numeroCasa);
        printf("Bairro: %s\n", paciente.bairro);
        printf("Cidade: %s\n", paciente.cidade);
        printf("Estado: %s\n", paciente.estado);
        printf("CEP: %s\n", paciente.cep);
        printf("Email: %s\n", paciente.email);
        printf("Nascimento: %d/%d/%d\n\n", paciente.dataNascimento.dia, paciente.dataNascimento.mes, paciente.dataNascimento.ano);
        imprimirSeparador();
    }

    fclose(fp);
}

void listarPacientesCovid()
{
    if (logado == 0)
    {
        printf("Para exibir os pacientes o funcionário deve estar logado");
        return;
    }

    FILE *fp;
    struct paciente paciente;
    int algumPossuiCovid = 0;

    fp = fopen(pacienteFile, "rb");

    if (fp == NULL)
    {
        printf("\nNenhum paciente cadastrado\n\n");
        return;
    }

    imprimirSeparador();
    printf("\t\t Todos Pacientes com COVID-19\n\n");
    imprimirSeparador();

    printf("Nome\tPossui Covid\n\n");

    while (1)
    {
        fread(&paciente, sizeof(paciente), 1, fp);

        if (feof(fp))
        {
            break;
        }

        if (paciente.possuiCovid == 1)
        {
            algumPossuiCovid = 1;

            printf("%s\t", paciente.nome);
            printf("SIM\t\n\n");
        }
    }

    if (algumPossuiCovid == 0)
    {
        printf("Nenhum paciente com COVID encontrado");
    }

    fclose(fp);
}

void listarPacientesGrupoRisco()
{
    if (logado == 0)
    {
        printf("Para exibir os pacientes o funcionário deve estar logado");
        return;
    }

    FILE *fp;
    struct paciente paciente;
    int algumPacienteGrupoRisco = 0;

    fp = fopen(pacienteGrupoRisco, "rb");

    if (fp == NULL)
    {
        printf("\nNenhum paciente cadastrado\n\n");
        return;
    }

    imprimirSeparador();
    printf("\t\t Todos Pacientes do grupo de risco:\n\n");
    imprimirSeparador();

    while (1)
    {
        fread(&paciente, sizeof(paciente), 1, fp);

        if (feof(fp))
            break;

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        algumPacienteGrupoRisco = 1;

        printf("CEP: %s\n", paciente.cep);
        printf("Idade: %d\n\n", (tm.tm_year + 1900) - paciente.dataNascimento.ano);
        imprimirSeparador();
    }

    if (algumPacienteGrupoRisco == 0)
        printf("Nenhum paciente do grupo de risco encontrado");
    printf("Nenhum paciente do grupo de risco encontrado");

    fclose(fp);
}

void exibirTitulo(char mensagem[20])
{
    imprimirSeparador();
    imprimirTitulo(mensagem);
    imprimirSeparador();
}

void imprimirSeparador()
{
    printf("===================================================================\n\n");
}

void imprimirTitulo(char titulo[])
{
    printf("========== %s ==========\n\n", titulo);
}

void salvarPaciente(struct paciente paciente, char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "ab");

    fwrite(&paciente, sizeof(paciente), 1, fp);

    fclose(fp);
}

void salvarFuncionario(struct funcionario paciente, char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "ab");

    fwrite(&paciente, sizeof(paciente), 1, fp);

    fclose(fp);
}

char esperarEntrada()
{
    char val;
    char rel;

    scanf("%c", &val);
    scanf("%c", &rel);

    return (val);
}
