# Simulador de gravidade com gotas
Um simulador interativo de gotas que caem e colidem entre si e com os limites da janela, utilizando a biblioteca SFML para visualização e princípios de física para a simulação.
## Como compilar

- Instale SFML na máquina:
``` 
sudo apt update
sudo apt install libsfml-dev
```

- Compile
```
g++ -std=c++17 Gota.cpp Simulacao.cpp main.cpp -o simulador_gotas -lsfml-graphics -lsfml-window -lsfml-system
```

- Execute
```
./simulador_gotas
```

Clique em qualquer área da janela para gerar as gotas.
