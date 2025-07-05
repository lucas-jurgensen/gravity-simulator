#ifndef SIMULACAO_H
#define SIMULACAO_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random> 

#include "Gota.h"

void resolverColisao(Gota& gota1, Gota& gota2);

class Simulacao {
public:
    const int LARGURA_JANELA = 800;
    const int ALTURA_JANELA = 600;
    const float GRAVIDADE = 200.0f; 
    const float ELASTICIDADE_PADRAO = 0.8f; 

private:
    sf::RenderWindow window;
    std::vector<Gota> gotas; 
    sf::Clock clock;

    std::random_device rd; 
    std::mt19937 gen; 
    std::uniform_real_distribution<> raioDist; 
    std::uniform_real_distribution<> velDist; 
    std::uniform_real_distribution<> elasticidadeDist; 

public:
    Simulacao();

    void addGota(float x, float y);
    void processEvents();
    void update(float deltaTime);
    void render();
    void run();
};

#endif 