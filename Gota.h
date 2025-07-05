#ifndef GOTA_H
#define GOTA_H

#include <SFML/Graphics.hpp> 
#include <cmath>

class Gota {
public:
    float x;
    float y;
    float raio;
    float vx;
    float vy;
    float elasticidade; 

    sf::Color cor;

    Gota(float inicioX, float inicioY, float novoRaio, float inicioVx, float inicioVy, float novaElasticidade, sf::Color novaCor);

    void atualizar(float deltaTime, float gravidadeAplicada, float alturaChao, float larguraJanela);
    void desenhar(sf::RenderWindow& window);
    float getMassa() const;
};

#endif