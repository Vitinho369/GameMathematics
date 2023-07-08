#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
using namespace std;

struct Player {
  int pontuation = 0;
  char name[50];
};

void readVar(int *respUser);

void generateQuest(int *operating, int *number1, int *number2, int *correctResp,
                   char *operation, int resp);

void dragonTop5();
void generateTop5(Player player);

int main() {
  srand(time(NULL));
  int numQuest = 1;
  int contTime;
  int nivel;
  Player player;

  system("echo 'Jogo de Matematica"
         "\nDigite o seu nome de usuario:'"
         "| boxes -d diamonds  -a c");

  cin.get(player.name, 50);
  system("clear");

  system("cat info.txt | boxes -d dog -a c");
  this_thread::sleep_for(10000ms);

  int respUser;
  int number1, number2;
  int correctResp;
  int operating;
  char operation;

  system("clear");
  contTime = 60;

  string textStego = "cowsay -f stegosaurus Pergunta n° ";
  textStego += to_string(numQuest);
  system(textStego.c_str());

  generateQuest(&operating, &number1, &number2, &correctResp, &operation,
                respUser);

  while (contTime > 0) {
    cout << "\rTempo: " << contTime;
    cout << " Qual a resposta da equacao " << number1 << operation << number2
         << " ?";
    thread readThread(readVar, &respUser);
    readThread.detach();

    this_thread::sleep_for(1000ms);
    contTime--;
    if (respUser == correctResp) {
      system("clear");

      player.pontuation += 10;
      generateQuest(&operating, &number1, &number2, &correctResp, &operation,
                    respUser);

      numQuest++;
      string textStego = "cowsay -f stegosaurus 'Pergunta n° ";

      textStego += to_string(numQuest) + "'";
      system(textStego.c_str());
    }
  }

  system("clear");

  string textCow = "cowsay PARABENS VOCE MARCOU ";
  textCow += to_string(player.pontuation) + " PONTOS";
  system(textCow.c_str());

  this_thread::sleep_for(5000ms);
  system("clear");

  system("sl");
  cout << "\n\nFIM DE JOGO";
  generateTop5(player);
  dragonTop5();
}

void readVar(int *respUser) { cin >> *respUser; }

void generateQuest(int *operating, int *number1, int *number2, int *correctResp,
                   char *operation, int resp) {
  do {
    *operating = rand() % 4;
    *number1 = rand() % 20;
    *number2 = rand() % 20;

    switch (*operating) {
    case 0:
      *correctResp = *number1 + *number2;
      *operation = '+';
      break;

    case 1:
      while (*number1 < *number2) {
        *number1 = rand() % 20;
        *number2 = rand() % 20;
      }
      *correctResp = *number1 - *number2;
      *operation = '-';
      break;

    case 2:
      *correctResp = *number1 * *number2;
      *operation = '*';
      break;

    case 3:
      while (*number1 < *number2) {
        *number1 = rand() % 20;
        *number2 = rand() % 20;
      }

      while (*number1 == 0) {
        *number1 = rand() % 20;
      }
      while (*number2 == 0) {
        *number2 = rand() % 20;
      }

      *correctResp = *number1 / *number2;
      *operation = '/';
      break;
    }
  } while (*correctResp == resp);
}

void generateTop5(Player player) {
  int tamTop5 = 0;
  Player playersTop5[6];
  Player newPlayer;

  ifstream readFile("top5.dat", ios::in | ios::binary);

  if (readFile.is_open()) {
    while (readFile.read((char *)&newPlayer, sizeof(Player))) {
      playersTop5[tamTop5++] = newPlayer;
    }
  }
  readFile.close();
  playersTop5[tamTop5++] = player;
  ofstream fileTop5("top5.dat", ios::out | ios::binary);

  Player aux;
  for (int i = 0; i < tamTop5; i++) {
    for (int j = 0; j < tamTop5; j++) {
      if (playersTop5[i].pontuation > playersTop5[j].pontuation) {
        aux = playersTop5[i];
        playersTop5[i] = playersTop5[j];
        playersTop5[j] = aux;
      }
    }
  }
  readFile.close();
  if (tamTop5 >= 5)
    tamTop5 = 5;

  for (int i = 0; i < tamTop5; i++) {
    fileTop5.write((char *)&playersTop5[i], sizeof(Player));
  }
  fileTop5.close();
}

void dragonTop5() {
  string textDragon;
  fstream fileTop5;
  ofstream top5Txt("top5.txt", ios::out);
  int i = 1;

  fileTop5.open("top5.dat", ios::in | ios::binary);

  Player player;
  top5Txt << "TOP 5\n\n";

  while (fileTop5.read((char *)&player, sizeof(Player))) {
    top5Txt << i++ << '-' << player.name << " | " << player.pontuation
            << "\n\n";
  }
  top5Txt.close();
  textDragon = "cat top5.txt | cowsay -f dragon";

  system(textDragon.c_str());
}