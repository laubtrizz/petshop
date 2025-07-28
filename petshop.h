#ifndef PETSHOP_H
#define PETSHOP_H

// Definições das estruturas de dados
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

// Funções auxiliares
void limparBuffer();
int emailValido(const char *email);

// Funções principais
int login();
void mensagemBoasVindas();
void menuPrincipal();
void menuServico();

// Funções de manipulação de Pet
void cadastrarPet();
void listarPets();
void editarPet();
void excluirPet();

// Funções de manipulação de Servicos
void marcarServico();
void listarServicos();

#endif
