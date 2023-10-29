#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura de usu�rio
struct User {
    char username[50];
    char password[50];
    char cell[13];
    int roomType;   // Adiciona um campo para armazenar o tipo de quarto reservado (1, 2 ou 3).
    int checkInDay; // Dia de check-in.
    int checkOutDay; // Dia de check-out.
};

// Fun��o para registrar um novo usu�rio
void registerUser(struct User users[], int *userCount) {
    printf("Digite um nome de usu�rio: ");
    scanf("%s", users[*userCount].username);
    printf("Digite um numero de celular: ");
    scanf("%s", users[*userCount].cell);
    printf("Digite uma senha: ");
    scanf("%s", users[*userCount].password);
    users[*userCount].roomType = 0; // Inicializa o tipo de quarto como 0 (n�o reservado).
    (*userCount)++;
    printf("Usu�rio registrado com sucesso!\n");
}

// Fun��o para fazer login
int loginUser(struct User users[], int userCount, char username[], char cell[], char password[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].cell, cell) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // Retorna o �ndice do usu�rio logado.
        }
    }
    return -1; // Login falhou
}

int main() {
    struct User users[10]; // Limite de 10 usu�rios
    int userCount = 0;
    int loggedInUserIndex = -1; // �ndice do usu�rio logado, inicializado como -1 (n�o logado).
    int choice;

    do {
        printf("\nMenu de Hospedagem de Hotel\n");
        printf("1. Registrar\n");
        printf("2. Fazer login\n");
        printf("3. Sair\n");

        if (loggedInUserIndex != -1) {
            printf("4. Gerenciar Reserva\n");
        }

        printf("Escolha uma op��o: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser(users, &userCount);
                break;
            case 2:
                printf("Digite seu nome de usu�rio: ");
                char username[50];
                scanf("%s", username);
                printf("Digite seu numero de celular: ");
                char cell[13];
                scanf("%s", cell);
                printf("Digite sua senha: ");
                char password[50];
                scanf("%s", password);
                loggedInUserIndex = loginUser(users, userCount, username, cell, password);

                if (loggedInUserIndex != -1) {
                    printf("\nLogin bem-sucedido!\n\n");
                    int escolha, escolha2;
    double preco;
    int dia;
    int quarto_ocupado[3][31] = {0}; // Array bidimensional para verificar a ocupa��o de cada quarto em cada dia.
    char continuar, continuar2;
    int dia_entrada, dia_saida;

    do {
        printf("Menu de Hospedagem\n");
        printf("1. Quarto Simples - R$100 por noite\n");
        printf("2. Quarto Duplo - R$150 por noite\n");
        printf("3. Suite de Luxo - R$300 por noite\n");
        printf("Escolha o tipo de quarto (1/2/3): ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                preco = 100.0;
                break;
            case 2:
                preco = 150.0;
                break;
            case 3:
                preco = 300.0;
                break;
            default:
                printf("Escolha inv�lida.\n");
                return 1; // Sai do programa com c�digo de erro.
        }

        printf("Voc� escolheu o Quarto %d. Deseja escolher algum servi�o extra? (S/N):\n", escolha);
        scanf(" %c", &continuar);

        if (continuar == 'S' || continuar == 's') {
            int escolha2;
            do {
                printf("Menu de servi�os extras\n");
                printf("1. Acesso ao frigobar - R$25\n");
                printf("2. Caf� da manh� - R$25\n");
                printf("3. Almo�o no local - R$50\n");
                scanf("%d", &escolha2);

                switch (escolha2) {
                    case 1:
                        preco = preco + 25;
                        break;
                    case 2:
                        preco = preco + 25;
                        break;
                    case 3:
                        preco = preco + 50;
                        break;
                    default:
                        printf("Escolha inv�lida.\n");
                        return 1; // Sai do programa com c�digo de erro.
                }
            } while (escolha2 < 1 || escolha2 > 3);
        }
        printf("O pre�o por noite � R$%.2lf\n", preco);
        printf("Digite o dia de entrada (1-31): ");
        scanf("%d", &dia_entrada);

                printf("Digite o dia de sa�da: ");
                scanf("%d", &dia_saida);
                dia = dia_saida - dia_entrada;

                // Verifica se o quarto j� est� ocupado nos dias escolhidos.
                if (dia < 1 || dia > 31) {
                    printf("Dia de agendamento inv�lido.\n");
                } else {
                    int quarto = escolha - 1; // Subtrai 1 para mapear 1, 2 e 3 para os �ndices 0, 1 e 2.
                    int dia_atual;
                    for (dia_atual = dia_entrada; dia_atual <= dia_saida; dia_atual++) {
                        if (quarto_ocupado[quarto][dia_atual - 1]) {
                            printf("Desculpe, o Quarto %d j� est� ocupado no dia %d.\n", escolha, dia_atual);
                            break;
                        } else {
                            quarto_ocupado[quarto][dia_atual - 1] = 1; // Marca o quarto como ocupado para o dia atual.
                        }
                    }
                    if (dia_atual > dia_saida) {
                        printf("Quarto agendado do dia %d at� o dia %d. O custo total � R$%.2lf\n", dia_entrada, dia_saida, preco * dia);

                        // Atualiza os dados de reserva do usu�rio logado
                        users[loggedInUserIndex].roomType = escolha;
                        users[loggedInUserIndex].checkInDay = dia_entrada;
                        users[loggedInUserIndex].checkOutDay = dia_saida;
                    }
                }

                printf("Deseja fazer outra hospedagem? (S/N): ");
                scanf(" %c", &continuar2);

            } while (continuar2 == 'S' || continuar2 == 's');

        } else {
            printf("Login falhou. Verifique seu nome de usu�rio e senha.\n");
        }
                break;
            case 3:
                printf("Saindo...\n");
                break;
            case 4:
                if (loggedInUserIndex != -1) {
                    struct User *currentUser = &users[loggedInUserIndex];
                    printf("Op��o de gerenciamento de reserva selecionada.\n");

                    // Mostra a reserva atual do usu�rio
                    printf("Sua reserva atual:\n");
                    printf("Tipo de quarto: %d\n", currentUser->roomType);
                    printf("Check-in: Dia %d\n", currentUser->checkInDay);
                    printf("Check-out: Dia %d\n", currentUser->checkOutDay);

                    // Op��es de gerenciamento
                    printf("1. Modificar datas de reserva\n");
                    printf("2. Modificar tipo de quarto\n");
                    printf("3. Cancelar reserva\n");
                    printf("4. Voltar\n");
                    printf("Escolha uma op��o: ");
                    int manageChoice;
                    scanf("%d", &manageChoice);

                    switch (manageChoice) {
                        case 1:
                            printf("Digite a nova data de check-in (1-31): ");
                            int newCheckIn;
                            scanf("%d", &newCheckIn);
                            printf("Digite a nova data de check-out: ");
                            int newCheckOut;
                            scanf("%d", &newCheckOut);

                            // Verifica se as novas datas s�o v�lidas
                            if (newCheckIn >= 1 && newCheckIn <= 31 && newCheckOut > newCheckIn && newCheckOut <= 31) {
                                currentUser->checkInDay = newCheckIn;
                                currentUser->checkOutDay = newCheckOut;
                                printf("Datas de reserva modificadas com sucesso.\n");
                            } else {
                                printf("Datas de reserva inv�lidas. N�o foram feitas altera��es.\n");
                            }
                            break;
                        case 2:
                            printf("Digite o novo tipo de quarto (1, 2, ou 3): ");
                            int newRoomType;
                            scanf("%d", &newRoomType);

                            // Verifica se o novo tipo de quarto � v�lido
                            if (newRoomType >= 1 && newRoomType <= 3) {
                                currentUser->roomType = newRoomType;
                                printf("Tipo de quarto modificado com sucesso.\n");
                            } else {
                                printf("Tipo de quarto inv�lido. N�o foi feita nenhuma altera��o.\n");
                            }
                            break;
                        case 3:
                            // Cancela a reserva
                            currentUser->roomType = 0;
                            currentUser->checkInDay = 0;
                            currentUser->checkOutDay = 0;
                            printf("Reserva cancelada com sucesso.\n");
                            break;
                        case 4:
                            break; // Volta ao menu principal de gerenciamento
                        default:
                            printf("Op��o inv�lida. Tente novamente.\n");
                    }
                } else {
                    printf("Voc� precisa fazer login para gerenciar sua reserva.\n");
                }
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (choice != 3);

    // Final do programa

    return 0;
}
