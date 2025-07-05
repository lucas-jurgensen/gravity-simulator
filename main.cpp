#include "Simulacao.h"

int main() {
    Simulacao simulador; 
    simulador.addGota(200.0f, 100.0f);
    simulador.addGota(600.0f, 100.0f);
    simulador.addGota(300.0f, 50.0f);

    simulador.run(); 

    return 0;
}