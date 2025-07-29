#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "petshop.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int emailValido(const char *email) {
    return strlen(email) < 80 && strchr(email, '@') != NULL;
}

int login() {
    char usuario[20], senha[20];

    while (1) {
        printf("\n      Login      \n");
        printf("Usuario: ");
        fgets(usuario, sizeof(usuario), stdin);
        usuario[strcspn(usuario, "\n")] = '\0';

        printf("Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if (strcmp(usuario, "petshop") == 0 && strcmp(senha, "123456") == 0) {
            printf("Login bem-sucedido!\n");
            return 1;
        } else {
            printf("Usuario ou senha incorretos. Tente novamente.\n");
        }
    }
}

void mensagemBoasVindas() {
    printf("\nBem-vindo ao Sistema do Pet Shop!\n");
}

void menuPrincipal() {
    printf("\n======== Pet Shop =========\n");
    printf("1 - Cadastrar Pet\n");
    printf("2 - Listar Pets\n");
    printf("3 - Editar Cadastro de Pet\n");
    printf("4 - Excluir Cadastro do Pet\n");
    printf("5 - Marcar Servico\n");
    printf("6 - Ver Lista de Servicos\n");
    printf("0 - Sair\n");
    printf("===========================\n");
}

void menuServico() {
    printf("\n======== Servicos =========\n");
    printf("1 - Banho\n");
    printf("2 - Tosa\n");
    printf("3 - Consulta\n");
    printf("4 - Vacina\n");
    printf("0 - Cancelar\n");
    printf("===========================\n");
}

void cadastrarPet() {
    FILE *file = fopen("pets.txt", "a");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Pet p;
    printf("Nome do Pet: ");
    limparBuffer();
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Especie: ");
    fgets(p.especie, sizeof(p.especie), stdin);
    p.especie[strcspn(p.especie, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &p.idade);
    limparBuffer();

    printf("Nome do Dono: ");
    fgets(p.dono, sizeof(p.dono), stdin);
    p.dono[strcspn(p.dono, "\n")] = '\0';

    fprintf(file, "%s;%s;%d;%s\n", p.nome, p.especie, p.idade, p.dono);
    fclose(file);
    printf("Pet cadastrado com sucesso!\n");
}

void merge(Pet arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Pet L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].nome, R[j].nome) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSortPets(Pet arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortPets(arr, l, m);
        mergeSortPets(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void listarPets() {
    FILE *file = fopen("pets.txt", "r");
    if (!file) {
        printf("Nenhum pet cadastrado ainda.\n");
        return;
    }

    Pet pets[100];
    int count = 0;
    while (fscanf(file, "%49[^;];%29[^;];%d;%49[^\n]\n", pets[count].nome, pets[count].especie, &pets[count].idade, pets[count].dono) != EOF) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    mergeSortPets(pets, 0, count - 1);

    printf("\n                   Lista de Pets                   \n");
    for (int i = 0; i < count; i++) {
        printf("Nome: %s | Especie: %s | Idade: %d | Dono: %s\n",
               pets[i].nome, pets[i].especie, pets[i].idade, pets[i].dono);
    }
}

void editarPet() {
    FILE *file = fopen("pets.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Pet pets[100];
    int count = 0;
    while (fscanf(file, "%49[^;];%29[^;];%d;%49[^\n]\n", pets[count].nome, pets[count].especie, &pets[count].idade, pets[count].dono) != EOF) {
        count++;
    }
    fclose(file);

    char nomeBusca[50];
    printf("Digite o nome do pet para editar: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(pets[i].nome, nomeBusca) == 0) {
            printf("Novo nome: ");
            fgets(pets[i].nome, sizeof(pets[i].nome), stdin);
            pets[i].nome[strcspn(pets[i].nome, "\n")] = '\0';

            printf("Nova especie: ");
            fgets(pets[i].especie, sizeof(pets[i].especie), stdin);
            pets[i].especie[strcspn(pets[i].especie, "\n")] = '\0';

            printf("Nova idade: ");
            scanf("%d", &pets[i].idade);
            limparBuffer();

            printf("Novo dono: ");
            fgets(pets[i].dono, sizeof(pets[i].dono), stdin);
            pets[i].dono[strcspn(pets[i].dono, "\n")] = '\0';

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Pet nao encontrado.\n");
        return;
    }

    file = fopen("pets.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s;%d;%s\n", pets[i].nome, pets[i].especie, pets[i].idade, pets[i].dono);
    }
    fclose(file);
    printf("Cadastro atualizado com sucesso.\n");
}

void excluirPet() {
    FILE *file = fopen("pets.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Pet pets[100];
    int count = 0;
    while (fscanf(file, "%49[^;];%29[^;];%d;%49[^\n]\n", pets[count].nome, pets[count].especie, &pets[count].idade, pets[count].dono) != EOF) {
        count++;
    }
    fclose(file);

    char nomeBusca[50];
    printf("Digite o nome do pet para excluir: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    file = fopen("pets.txt", "w");
    for (int i = 0; i < count; i++) {
        if (strcmp(pets[i].nome, nomeBusca) != 0) {
            fprintf(file, "%s;%s;%d;%s\n", pets[i].nome, pets[i].especie, pets[i].idade, pets[i].dono);
        }
    }
    fclose(file);
    printf("Pet excluido com sucesso.\n");
}

void marcarServico() {
    FILE *file = fopen("servicos.txt", "a");
    if (!file) {
        printf("Erro ao abrir o arquivo de servicos!\n");
        return;
    }

    Servico s;
    printf("Nome do pet: ");
    limparBuffer();
    fgets(s.nomePet, sizeof(s.nomePet), stdin);
    s.nomePet[strcspn(s.nomePet, "\n")] = '\0';

    int opcao;
    menuServico();
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao) {
        case 1: strcpy(s.tipo, "Banho"); break;
        case 2: strcpy(s.tipo, "Tosa"); break;
        case 3: strcpy(s.tipo, "Consulta"); break;
        case 4: strcpy(s.tipo, "Vacina"); break;
        case 0: return;
        default: printf("Opcao invalida!\n"); return;
    }

    printf("Data do servico (DD/MM/AAAA): ");
    fgets(s.data, sizeof(s.data), stdin);
    s.data[strcspn(s.data, "\n")] = '\0';

    fprintf(file, "%s;%s;%s\n", s.nomePet, s.tipo, s.data);
    fclose(file);
    printf("Servico registrado com sucesso!\n");
}

void listarServicos() {
    FILE *file = fopen("servicos.txt", "r");
    if (!file) {
        printf("Nenhum servico registrado ainda.\n");
        return;
    }

    Servico s;
    printf("\n                   Lista de Servicos                   \n");
    while (fscanf(file, "%49[^;];%29[^;];%14[^\n]\n", s.nomePet, s.tipo, s.data) != EOF) {
        printf("Pet: %s | Servico: %s | Data: %s\n", s.nomePet, s.tipo, s.data);
    }

    fclose(file);
}

int main() {
    if (!login()) return 0;

    char emailUsuario[80];
    do {
        printf("Informe seu e-mail: ");
        fgets(emailUsuario, sizeof(emailUsuario), stdin);
        emailUsuario[strcspn(emailUsuario, "\n")] = '\0';

        if (!emailValido(emailUsuario)) {
            printf("E-mail invalido. Tente novamente.\n");
        }
    } while (!emailValido(emailUsuario));

    mensagemBoasVindas();

    int opcao;
    do {
        menuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrarPet();
            break;
            case 2: listarPets();
            break;
            case 3: editarPet(); 
            break;
            case 4: excluirPet(); 
            break;
            case 5: marcarServico(); 
            break;
            case 6: listarServicos(); 
            break;
            case 0: printf("Obrigado por usar o sistema do Pet Shop. Ate logo!  \n"); 
            break;
            default: printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
