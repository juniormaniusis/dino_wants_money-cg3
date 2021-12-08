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
  static constexpr float VELOCIDADE_DESCOLAMENTO{3.5f};
  static constexpr float VELOCIDADE_ROTACAO{100.0f};
  static constexpr float GRAVIDADE{-4.5f};
  static constexpr float JUMP_POWER{2.0f};
  static constexpr float NIVEL_CHAO{0.0f};

  void initializeGL(std::string assetsPath, GLuint program);
  void paintGL(GLuint program, glm::mat4 cameraViewMatrix);
  void terminateGL();
  void update(float deltaTime);
  void computeModelMatrix();
  void pular();

 private:
  friend OpenGLWindow;
  friend Camera;
  Model m_model;
  glm::mat4 m_modelMatrix{1.0f};

  glm::vec3 m_posicao{0, 0.0f, 0};
  glm::vec3 m_rotacao{0, 180, 0};
  float m_escala{0.015f};
  float m_velocidadeDeslocamento{0};
  float m_velocidadePulo{0};
  float m_velocidadeRotacao{0};

  void computeGravity(float deltaTime);
};

#endif
