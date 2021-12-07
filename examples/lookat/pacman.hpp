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
  static constexpr float VELOCIDADE_DESCOLAMENTO = 1.0f;
  static constexpr float VELOCIDADE_ROTACAO = 45.0f;
  void initializeGL(std::string assetsPath, GLuint program);
  void paintGL(GLuint program, glm::mat4 cameraViewMatrix);
  void terminateGL();
  void update(float deltaTime);
  void computeModelMatrix();

 private:
  friend OpenGLWindow;
  friend Camera;
  Model m_model;
  glm::mat4 m_modelMatrix{1.0f};

  // posicionamento no espaço
  glm::vec3 m_posicao{-0.9f, 0.0f, 4.0f};
  glm::vec3 m_rotacao{-90.0f, 0, -90.0f};
  float m_escala{0.025f};
  float m_velocidadeDeslocamento{0};
  float m_velocidadeRotacao{0};
};

#endif
