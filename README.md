### Nomes e RA

- Carlos Maniusis Jr. - RA: 11081816 (Prof. Bruno Marques)
- Melissa Gabriela Pereira da Soledade Perrone - RA: 11072216 (Prof Harlen Batagelo)

### Descrição

O projeto consiste em uma representação 3D de um mundo cheio de palmeiras e neblina, onde um dinossauro vive e coleta dinheiro para ganhar pontos.
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

#### Camera

A cena é observada a partir de uma câmera em pessoa, que segue os movimentos do dinossauro.

![ilustração de movimentos de pitch, yaw e roll de uma camera](https://github.com/juniormaniusis/dino_wants_money-cg3/blob/main/imagens/camera_yay_pitch_roll.jpg)

A imagem acima ilustra os movimentos de pitch, yaw e roll. Cada um ocorre em uma das dimensões.

```
-pitch: o movimento de olhar para cima e para baixo.
-yaw: o movimento de olhar para esquerda e direita.
-roll: movimento circular, em sentido horário ou anti horário.
```

Abaixo, temos a demonstração destes efeitos na implementação, note que não foi feito o uso do movimento roll.

![pitch](https://github.com/juniormaniusis/dino_wants_money-cg3/blob/main/imagens/pitch.gif)

![yaw](https://github.com/juniormaniusis/dino_wants_money-cg3/blob/main/imagens/angulo_player.gif)

Além destes, um outro movimento é possível com a camera. É possível se aproximar ou se afastar do dinossauro.

![aproximar e se afastar do dinossauro](https://github.com/juniormaniusis/dino_wants_money-cg3/blob/main/imagens/distancia_player.gif)

# ABCg

Development framework accompanying the course MCTA008-17 Computer Graphics at [UFABC](https://www.ufabc.edu.br/).

---

### Credits

Developed by Harlen Batagelo.

### License

ABCg is licensed under the MIT License. See [LICENSE](https://github.com/hbatagelo/abcg/blob/main/LICENSE) for more information.

---
