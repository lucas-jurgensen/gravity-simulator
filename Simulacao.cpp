#include "Simulacao.h"
#include <iostream>
#include <cmath> 

void resolverColisao(Gota& gota1, Gota& gota2) {
    float dx = gota2.x - gota1.x;
    float dy = gota2.y - gota1.y;
    float distancia = std::sqrt(dx * dx + dy * dy);

    float somaRaios = gota1.raio + gota2.raio;

    if (distancia == 0.0f || distancia >= somaRaios) {
        return; 
    }

    float nx = dx / distancia;
    float ny = dy / distancia;

    float overlap = somaRaios - distancia;
    gota1.x -= nx * (overlap / 2.0f);
    gota1.y -= ny * (overlap / 2.0f);
    gota2.x += nx * (overlap / 2.0f);
    gota2.y += ny * (overlap / 2.0f);

    float v1n = gota1.vx * nx + gota1.vy * ny;
    float v2n = gota2.vx * nx + gota2.vy * ny;

    float v1tx = gota1.vx - v1n * nx;
    float v1ty = gota1.vy - v1n * ny;
    float v2tx = gota2.vx - v2n * nx;
    float v2ty = gota2.vy - v2n * ny;

    float e = std::min(gota1.elasticidade, gota2.elasticidade); 

    float m1 = gota1.getMassa();
    float m2 = gota2.getMassa();

    float v1n_final = (v1n * (m1 - e * m2) + v2n * (m2 + e * m2)) / (m1 + m2);
    float v2n_final = (v1n * (m1 + e * m1) + v2n * (m2 - e * m1)) / (m1 + m2);

    gota1.vx = v1n_final * nx + v1tx;
    gota1.vy = v1n_final * ny + v1ty;
    gota2.vx = v2n_final * nx + v2tx;
    gota2.vy = v2n_final * ny + v2ty;
}

Simulacao::Simulacao() : 
    window(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Simulacao de Gotas com Gravidade!"),
    gen(rd()), 
    raioDist(10.0, 30.0), 
    velDist(-100.0, 100.0), 
    elasticidadeDist(0.5, 0.95)
{
    window.setFramerateLimit(60); 
}

void Simulacao::addGota(float x, float y) {
    float novoRaio = raioDist(gen);
    float novaVx = velDist(gen);
    float novaVy = velDist(gen); 
    float novaElasticidade = elasticidadeDist(gen);
    
    sf::Color novaCor = sf::Color::White; 

    gotas.emplace_back(x, y, novoRaio, novaVx, novaVy, novaElasticidade, novaCor);
}

void Simulacao::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) { 
                addGota(static_cast<float>(event.mouseButton.x), 
                        static_cast<float>(event.mouseButton.y));
            }
        }
    }
}

void Simulacao::update(float deltaTime) {
    for (Gota& gota : gotas) {
        gota.atualizar(deltaTime, GRAVIDADE, ALTURA_JANELA, LARGURA_JANELA); 
    }

    for (size_t i = 0; i < gotas.size(); ++i) {
        for (size_t j = i + 1; j < gotas.size(); ++j) {
            Gota& gota1 = gotas[i];
            Gota& gota2 = gotas[j];

            float dx = gota2.x - gota1.x;
            float dy = gota2.y - gota1.y;
            float distanciaCentrosQuadrada = dx * dx + dy * dy; 
        
            float somaRaios = gota1.raio + gota2.raio;
            float somaRaiosQuadrada = somaRaios * somaRaios;

            if (distanciaCentrosQuadrada < somaRaiosQuadrada) { 
                resolverColisao(gota1, gota2); 
            } 
        }
    }
}

void Simulacao::render() {
    window.clear(sf::Color(50,50,50)); 

    for (Gota& gota : gotas) {
        gota.desenhar(window);
    }

    window.display();
}

void Simulacao::run() {
    while(window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
    
        processEvents();
        update(deltaTime);
        render();
    }
}