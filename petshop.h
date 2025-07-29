#ifndef PETSHOP_H
#define PETSHOP_H

typedef struct {
    char nome[50];
    char especie[30];
    int idade;
    char dono[50];
} Pet;

typedef struct {
    char nomePet[50];
    char tipo[30];
    char data[15];
} Servico;

void limparBuffer();
int emailValido(const char *email);

int login();
void mensagemBoasVindas();
void menuPrincipal();
void menuServico();

void cadastrarPet();
void listarPets();
void editarPet();
void excluirPet();

void marcarServico();
void listarServicos();

#endif
