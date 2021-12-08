#include "dinheiro.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <random>
#include <unordered_map>

void Dinheiro::initializeGL(GLuint program, std::string assetsPath) {
  m_dinheiros = gerarDinheiros();
  m_model.loadDiffuseTexture(assetsPath + "/maps/stacks_diffuse_no_ao.jpg");
  m_model.loadFromFile(assetsPath + "stacks of money.obj");
  m_model.setupVAO(program);

  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  m_randomEngine.seed(seed);
}

void Dinheiro::update(float deltaTime, glm::vec3 pacmanPosition, float* score) {
  // rotaciona a moeda e verifica se colidiu com o player
  m_rotacao.z += 30 * deltaTime;
  for (ulong i = 0; i < m_dinheiros.size(); i++) {
    if (m_dinheiros[i]->ativo) {
      if (checkColision(m_dinheiros[i]->posicao, pacmanPosition)) {
        m_dinheiros[i]->ativo = false;
        *score += m_dinheiros[i]->valor;
      }
    }
  }
}
bool Dinheiro::checkColision(glm::vec3 dinheiroPosition,
                             glm::vec3 pacmanPosition) {
  glm::vec3 distance = dinheiroPosition - pacmanPosition;
  return glm::length(distance) < 1.3;
}
void Dinheiro::computeModelMatrix(int positionIndex) {
  auto model = glm::mat4{1};

  m_modelMatrix = glm::translate(model, m_dinheiros[positionIndex]->posicao);

  m_modelMatrix =
      glm::rotate(m_modelMatrix, glm::radians(m_rotacao.x), glm::vec3(1, 0, 0));
  m_modelMatrix =
      glm::rotate(m_modelMatrix, glm::radians(m_rotacao.y), glm::vec3(0, 1, 0));
  m_modelMatrix =
      glm::rotate(m_modelMatrix, glm::radians(m_rotacao.z), glm::vec3(0, 0, 1));
  m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_escala));
}
void Dinheiro::paintGL(GLuint program, glm::mat4 cameraViewMatrix) {
  // se a moeda já foi capturada pelo player, não é mais renderizada.
  GLint modelMatrixLoc{glGetUniformLocation(program, "modelMatrix")};
  GLint normalMatrixLoc{glGetUniformLocation(program, "normalMatrix")};
  GLint shininessLoc{glGetUniformLocation(program, "shininess")};
  GLint KaLoc{glGetUniformLocation(program, "Ka")};
  GLint KdLoc{glGetUniformLocation(program, "Kd")};
  GLint KsLoc{glGetUniformLocation(program, "Ks")};
  GLint mappingModeLoc{glGetUniformLocation(program, "mappingMode")};

  for (ulong i = 0; i < m_dinheiros.size(); i++) {
    if (m_dinheiros[i]->ativo) {
      computeModelMatrix(i);
      glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);
      auto modelViewMatrix{glm::mat4(cameraViewMatrix * m_modelMatrix)};
      glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
      glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

      glUniform1f(shininessLoc, m_model.m_shininess);
      glUniform4fv(KaLoc, 1, &m_model.m_Ka.x);
      glUniform4fv(KdLoc, 1, &m_model.m_Kd.x);
      glUniform4fv(KsLoc, 1, &m_model.m_Ks.x);

      glUniform1i(mappingModeLoc, 3);
      m_model.render();
    }
  }
}

std::vector<DinheiroUnidade*> Dinheiro::gerarDinheiros() {
  std::uniform_real_distribution<float> rd(-5.0f, 5.0f);

  std::vector<DinheiroUnidade*> dinheiros{};
  for (int i = 0; i < 40; i++) {
    for (int j = 0; j < 40; j++) {
      float randX = rd(m_randomEngine) + ((float)(i + j) * 8);
      float randZ = (rd(m_randomEngine) + i) * (float(j * 2));
      DinheiroUnidade* dinheiro =
          criaDinheiroUnidade(100, glm::vec3(randX, 1, randZ));
      dinheiros.push_back(dinheiro);
    }
  }
  return dinheiros;
}

DinheiroUnidade* Dinheiro::criaDinheiroUnidade(float valor, glm::vec3 posicao) {
  auto dinheiro = (DinheiroUnidade*)malloc(sizeof(DinheiroUnidade));
  dinheiro->ativo = true;
  dinheiro->posicao = posicao;
  dinheiro->valor = valor;
  return dinheiro;
}

void Dinheiro::terminateGL() {}

Dinheiro::~Dinheiro() {}