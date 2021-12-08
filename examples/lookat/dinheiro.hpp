#ifndef Dinheiro_HPP_
#define Dinheiro_HPP_

#include <random>
#include <vector>

#include "abcg.hpp"
#include "camera.hpp"
#include "gamedata.hpp"
#include "model.hpp"

typedef struct DinheiroUnidade {
  bool ativo{0};
  float valor{100.0};
  glm::vec3 posicao{0};
} DinheiroUnidade;

class OpenGLWindow;
class Dinheiro {
 public:
  ~Dinheiro();

  void initializeGL(GLuint program, std::string assetsPath);
  void paintGL(GLuint program, glm::mat4 cameraViewMatrix);
  void terminateGL();
  void computeModelMatrix(int positionIndex);
  std::vector<DinheiroUnidade*> gerarDinheiros();
  void update(float deltaTime);

 private:
  friend OpenGLWindow;
  Model m_model;
  glm::mat4 m_modelMatrix{0};
  std::default_random_engine m_randomEngine;
  DinheiroUnidade* criaDinheiroUnidade(float valor, glm::vec3 posicao);
  std::vector<DinheiroUnidade*> m_dinheiros{};
  glm::vec3 m_rotacao{-90, 0, 0};
  float m_escala{0.005f};
};

#endif