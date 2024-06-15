#include <iostream>
#include <limits>

class TresEnRaya {
 public:
  TresEnRaya(int n);
  ~TresEnRaya();
  void EmpezarPartida();
  void EmpezarPartidaAlternativa();
 private:
  int tamano_ = 3;
  char** tablero_;
  void Preguntar(bool jugador) const;
  void PreguntarMover(bool jugador) const;
  bool CasillaValidaPoner(int posicion_x, int posicion_y) const;
  bool CasillaValidaMover(int posicion_x, int posicion_y, bool jugador) const;
  void PonerFicha(int posicion_x, int posicion_y, bool jugador);
  void MoverFicha(int posicion_x, int posicion_y, bool jugador);
  int ComprobarFinal() const;
  void MostrarTablero() const;
};