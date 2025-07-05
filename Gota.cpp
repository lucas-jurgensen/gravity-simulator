#include "Gota.h"
#include <iostream>

Gota::Gota(float inicioX, float inicioY, float novoRaio, float inicioVx, float inicioVy, float novaElasticidade, sf::Color novaCor) { 
    x = inicioX;
    y = inicioY;
    raio = novoRaio;
    vx = inicioVx;
    vy = inicioVy;
    elasticidade = novaElasticidade;
    cor = novaCor; 
}

void Gota::atualizar(float deltaTime, float gravidadeAplicada, float alturaChao, float larguraJanela) { 
    vy += gravidadeAplicada * deltaTime;
    x += vx * deltaTime;
    y += vy * deltaTime;

    if (y + raio >= alturaChao) {
        y = alturaChao - raio;      
        vy = -vy * elasticidade;    

        if (std::abs(vy) < 0.1f) { 
            vy = 0.0f;             
            vx = 0.0f; 
        }
    }

    if (x + raio >= larguraJanela) {
        x = larguraJanela - raio;   
        vx = -vx * elasticidade;    
        if (std::abs(vx) < 0.1f) {
            vx = 0.0f;
        }
    }
    else if (x - raio <= 0) { 
        x = raio;               
        vx = -vx * elasticidade;    
        if (std::abs(vx) < 0.1f) {
            vx = 0.0f;
        }
    }
}

void Gota::desenhar(sf::RenderWindow& window) {
    sf::CircleShape circle(raio);
    circle.setFillColor(cor);
    circle.setPosition(x - raio, y - raio);
    window.draw(circle);
}

float Gota::getMassa() const {
    return raio * raio; 
}