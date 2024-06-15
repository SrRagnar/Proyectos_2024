#include "TresEnRaya.h"

void TresEnRaya::Preguntar(bool jugador) const {
 std::cout << "Jugador " << (jugador? 'x' : 'o') << " , donde quieres poner la ficha? (fila - columna)" << std::endl;
}

void TresEnRaya::PreguntarMover(bool jugador) const {
 std::cout << "Jugador " << (jugador? 'x' : 'o') << " , que ficha quieres mover? (fila - columna)" << std::endl;
}

TresEnRaya::TresEnRaya(int n) : tamano_{n} {
  tablero_ = new char*[tamano_];  // Investigar mas
  for (int i{0}; i < tamano_; ++i) {
    tablero_[i] = new char[tamano_];
    for (int j{0}; j < tamano_; ++j) {
      tablero_[i][j] = '-';
    }
  }
} 

TresEnRaya::~TresEnRaya() { 
  for (int i{0}; i < tamano_; ++i) {
    delete[] tablero_[i];
  }
  delete[] tablero_;
} 

void TresEnRaya::MostrarTablero() const {
  for (int i{0}; i < tamano_; ++i) {
    for (int j{0}; j < tamano_; ++j) {
      std::cout << tablero_[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

bool TresEnRaya::CasillaValidaPoner(int posicion_x, int posicion_y) const {
  if ((posicion_x < 0 || posicion_y < 0) || (posicion_x >= tamano_ || posicion_y >= tamano_) || (tablero_[posicion_x][posicion_y] != '-')) {
    return 0;
  } 
  return 1;
}

bool TresEnRaya::CasillaValidaMover(int posicion_x, int posicion_y, bool jugador) const {
  if (jugador == 0) {
    if ((posicion_x < 0 || posicion_y < 0) || (posicion_x >= tamano_ || posicion_y >= tamano_ || (tablero_[posicion_x][posicion_y] != 'o'))) {
      return 0;
    } 
  } else {
     if ((posicion_x < 0 || posicion_y < 0) || (posicion_x >= tamano_ || posicion_y >= tamano_ || (tablero_[posicion_x][posicion_y] != 'x'))) {
      return 0;
    } 
  }
  return 1;
}

void TresEnRaya::PonerFicha(int posicion_x, int posicion_y, bool jugador) {
  if (!CasillaValidaPoner(posicion_x, posicion_y))  {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Esa posicion ya esta ocupada o esta fuera del rango." << std::endl;
    Preguntar(jugador);
    std::cin >> posicion_x >> posicion_y;
    PonerFicha(posicion_x - 1, posicion_y- 1, jugador);
    return;
  }
  tablero_[posicion_x][posicion_y] = jugador ? 'x' : 'o';
}

int TresEnRaya::ComprobarFinal() const {
  int contador_disponibles = 0;

  int* contador_x_columna = new int[tamano_]();
  int* contador_o_columna = new int[tamano_]();

  int* contador_x_fila = new int[tamano_]();
  int* contador_o_fila= new int[tamano_]();

  for (int i{0}; i < tamano_; ++i) {
    contador_o_columna[i] = 0;
    contador_x_columna[i] = 0;
    contador_o_fila[i] = 0;
    contador_x_fila[i] = 0;
  }

  int contador_x_diagonal = 0;
  int contador_o_diagonal = 0;

  int contador_x_diagonal2 = 0;
  int contador_o_diagonal2 = 0;

  for (int i{0}; i < tamano_; i++) {

    if (tablero_[i][i] == 'o') {
      contador_o_diagonal++;
    } else if (tablero_[i][i] == 'x') {
      contador_x_diagonal++;
    } 

    if (tablero_[i][tamano_ - 1 - i] == 'o') {
      contador_o_diagonal2++;
    } else if (tablero_[i][tamano_ - 1 - i] == 'x') {
      contador_x_diagonal2++;
    }
    
    for (int j{0}; j < tamano_; j++) {
      if (tablero_[i][j] == 'o') {
        contador_o_fila[i]++;
        contador_o_columna[j]++;
      } else if (tablero_[i][j] == 'x') {
        contador_x_fila[i]++;
        contador_x_columna[i]++;
      } else {
        contador_disponibles++;
      }
    }
  }
  
  for (int i {0}; i < tamano_; ++i) {
    if (contador_o_fila[i] == tamano_ || contador_o_columna[i] == tamano_) {
      delete[] contador_x_columna;
      delete[] contador_o_columna;
      delete[] contador_x_fila;
      delete[] contador_o_fila; 
      return 0;
    } else if (contador_x_fila[i] == tamano_ || contador_x_columna[i] == tamano_) {
      delete[] contador_x_columna;
      delete[] contador_o_columna;
      delete[] contador_x_fila;
      delete[] contador_o_fila; 
      return 1;
    }
  }
  delete[] contador_x_columna;
  delete[] contador_o_columna;
  delete[] contador_x_fila;
  delete[] contador_o_fila; 
  if ( contador_o_diagonal == tamano_ || contador_o_diagonal2 == tamano_) {
    return 0;
  } else if ( contador_x_diagonal == tamano_ || contador_x_diagonal2 == tamano_) {
    return 1;
  } else if (contador_disponibles == 0) {
    return -2;
  } else {
    return -1;
  }
}

void TresEnRaya::EmpezarPartida() {
  bool jugador = 0;
  while (ComprobarFinal() == -1) {
    //system("pause");
    MostrarTablero();
    std::cout << std::endl;
    Preguntar(jugador);
    int posicion_x;
    int posicion_y;
    std::cin >> posicion_x >> posicion_y;
    std::cout << std::endl;

    PonerFicha(posicion_x - 1, posicion_y - 1, jugador);
    jugador = !jugador;
  }
  int final = ComprobarFinal();
  if (final == 0) {
    std::cout << std::endl;
    MostrarTablero();
    std::cout << std::endl << "EL JUGADOR O HA GANADO!" << std::endl;
  } else if (final == 1) {
    std::cout << std::endl;
    MostrarTablero();
    std::cout << std::endl << "EL JUGADOR X HA GANADO!" << std::endl;
  } else if (final == -2) {
    std::cout << std::endl;
    MostrarTablero();
    std::cout << std::endl << "SE HA LLENADO EL TABLERO BOBAINAS" << std::endl;
  }
}

void TresEnRaya::MoverFicha(int posicion_x, int posicion_y, bool jugador) {
  if (!CasillaValidaMover(posicion_x, posicion_y, jugador)) {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Esa posicion no te pertenece o esta fuera del rango." << std::endl;
    PreguntarMover(jugador);
    std::cin >> posicion_x >> posicion_y;
    MoverFicha(posicion_x - 1, posicion_y - 1, jugador);
    return;
  }
  Preguntar(jugador);
  int posicion_x_mover;
  int posicion_y_mover;
  std::cin >> posicion_x_mover >> posicion_y_mover;
  PonerFicha(posicion_x_mover - 1, posicion_y_mover - 1, jugador);

  tablero_[posicion_x][posicion_y] = '-';
}

void TresEnRaya::EmpezarPartidaAlternativa() {
  int turno{0};
  bool jugador{0};
  while (ComprobarFinal() == -1) {
    //system("pause");
    MostrarTablero();
    std::cout << std::endl;
    if (turno < tamano_ * 2) {
      Preguntar(jugador);
      int posicion_x_poner;
      int posicion_y_poner;
      std::cin >> posicion_x_poner >> posicion_y_poner;
      std::cout << std::endl;
      PonerFicha(posicion_x_poner - 1, posicion_y_poner - 1, jugador);
    } else {
      PreguntarMover(jugador);
      int posicion_x_mover;
      int posicion_y_mover;
      std::cin >> posicion_x_mover >> posicion_y_mover;
      std::cout << std::endl;
      MoverFicha(posicion_x_mover - 1, posicion_y_mover - 1, jugador);
    }
    jugador = !jugador;
    ++turno;
  }

  int final = ComprobarFinal();
  if (final == 0) {
    std::cout << std::endl;
    MostrarTablero();
    std::cout << std::endl << "EL JUGADOR O HA GANADO!" << std::endl;
  } else if (final == 1) {
    std::cout << std::endl;
    MostrarTablero();
    std::cout << std::endl << "EL JUGADOR X HA GANADO!" << std::endl;
  } else if (final == -2) {
    std::cout << std::endl;
    MostrarTablero();
    std::cout << std::endl << "SE HA LLENADO EL TABLERO BOBAINAS" << std::endl;
  }
}