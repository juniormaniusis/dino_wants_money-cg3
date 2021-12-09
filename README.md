# ABCg

Development framework accompanying the course MCTA008-17 Computer Graphics at [UFABC](https://www.ufabc.edu.br/).

---

### Credits

Developed by Harlen Batagelo.

### License

ABCg is licensed under the MIT License. See [LICENSE](https://github.com/hbatagelo/abcg/blob/main/LICENSE) for more information.

---

### Nomes e RA

- Carlos Maniusis Jr. - RA: 11081816 (Prof. Bruno Marques)
- Melissa Gabriela Pereira da Soledade Perrone - RA: 11072216 (Prof Harlen Batagelo)

### Descrição

O projeto consiste em uma representação 3D de um mundo cheio de palmeiras, onde um dinossauro vive e coleta dinheiro para ganhar pontos.
O dinossauro é controlado a partir do teclado e a camera a partir do mouse.

### Controles

Controles do Dinossauro

| Ação     | Controle        |
| -------- | --------------- |
| Mover-se | WASD            |
| Pular    | Barra de Espaço |

Controles da Camera

| Ação                                     | Controle           |
| ---------------------------------------- | ------------------ |
| Reposicionar-se em torno do dinossauro   | Movimento do Mouse |
| Aproximar-se ou Afastar-se do dinossauro | Scroll do Mouse    |

### Código

- camera.cpp: câmera utilizada no projeto lookat. Modificamos a posição inicial da câmera para ficar no início do corredor do labirinto.
- ground.cpp: representa o chão da cena, feito também em quadriculado e nos tons de azul, inspirados no jogo do Pacman.
- wall.cpp (4 arquivos wall): cada um dos arquivos representa uma parede (plano 3d). As paredes também estão em tons azuis, inspiração no jogo do Pacman.
- openglwindow.cpp: carrega o modelo do .obj file do Pacman e renderiza os outros objetos da cena (ground, walls).

### Imagens

Imagem inicial da cena e visão do corredor:

![Alt text](https://github.com/melissasoledade/abcg/blob/main/pacman-01.png)

Imagem da visão do Pacman:

![Alt text](https://github.com/melissasoledade/abcg/blob/main/pacman-02.png)

Pacman:

![Alt text](https://github.com/melissasoledade/abcg/blob/main/pacman-03.png)

Imagem de outro ângulo do Pacman:

![Alt text](https://github.com/melissasoledade/abcg/blob/main/pacman-04.png)
