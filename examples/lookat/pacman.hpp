#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <vector>

#include "abcg.hpp"
#include "camera.hpp"
#include "gamedata.hpp"
#include "model.hpp"
class OpenGLWindow;
class Pacman {
 public:
  ~Pacman();
  void initializeGL(std::string assetsPath, GLuint program);
  void paintGL(GLint viewMatrixLoc, GLint projMatrixLoc, GLint modelMatrixLoc,
               GLint colorLoc);
  void terminateGL();
  void update(float deltaTime);

 private:
  friend OpenGLWindow;
  friend Camera;
  Model m_model;
  glm::mat4 m_modelMatrix{1.0f};

  glm::vec3 m_posicao_inicial{-0.9f, 0.0f, 4.0f};//{glm::vec3(0, 1, 0)};
  glm::vec3 m_escala_inicial{glm::vec3(.025f)};

  // posicionamento no espaço
  glm::vec3 m_posicao_atual{glm::vec3(0, 0, 0)};
  glm::vec3 m_direcao{glm::vec3(-1, 0, 0)};
  float m_tamanho{1.0f};
  float m_velocidade{0.0f};

  // m_sentidoRotacao < 0 => sentido anti horario
  // m_sentidoRotacao > 0 => sentido horario 
  float m_sentidoRotacao{0};
  float m_angulo{180}; //usar wrapangle depois
};

#endif