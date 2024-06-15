#include "TresEnRaya.h"

int main() {
  std::cout << "A que 'tres' en raya quereis jugar hoy?" << std::endl;
  int dimension = 3;
  std::cin >> dimension;
  while (dimension <= 0) {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Dimension no valida." << std::endl;
    std::cout << "A que 'tres' en raya quereis jugar hoy?" << std::endl;
    std::cin >> dimension;
  }
  TresEnRaya mondongo(dimension);
  std::cout << "\nQue modo de juegos prefieres, clasico (1) o alternativo (2)?" << std::endl; 
  int modo{1};
  std::cin >> modo;
  while (modo != 1 && modo != 2) {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ese modo de juego no existe." << std::endl;
    std::cout << "Que modo de juegos prefieres, clasico (1) o alternativo (2)?" << std::endl;
    std::cin >> modo;
  }
  if (modo == 1) {
    mondongo.EmpezarPartida();
  } else {
    mondongo.EmpezarPartidaAlternativa();
  }
  system("pause");
  return 0;
}