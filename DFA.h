//
// Created by DarkWayC0de_pc on 17/11/2018.
//

#ifndef PR6_DFA_H
#define PR6_DFA_H

#include <set>
#include "Estado.h"

namespace CyA {
  class DFA {
  private:
    std::set<Estado> DFA_;
    unsigned nestados_,arranque_;

    void build(char nombrefichero[]);
    void analizar(std::ifstream &a);
    bool aceptacion(unsigned a);
  public:
    DFA();
    ~DFA();
    void cargar(char nombrefichero[]);
    bool vasio();
    std::ostream& write(std::ostream &os);
    void muerte(void);
    void cadena(void);
    unsigned siguiente(unsigned origen,char entrada,bool &aceptado);
  };
}

#endif //PR6_DFA_H
