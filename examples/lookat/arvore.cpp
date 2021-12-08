#include "arvore.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <random>
#include <unordered_map>

void Arvore::initializeGL(GLuint program, std::string assetsPath) {
  m_posicoes = gerarPosicoes();
  m_model.loadDiffuseTexture(assetsPath +
                             "maps/10446_Palm_Tree_v1_Diffuse.jpg");
  m_model.loadFromFile(assetsPath +
                       "10446_Palm_Tree_v1_max2010_iteration-2.obj");
  m_model.setupVAO(program);

  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  m_randomEngine.seed(seed);
}
void Arvore::computeModelMatrix(int positionIndex) {
  auto model = glm::mat4{1};

  m_modelMatrix = glm::translate(model, m_posicoes[positionIndex]);

  m_modelMatrix =
      glm::rotate(m_modelMatrix, glm::radians(m_rotacao.x), glm::vec3(1, 0, 0));
  m_modelMatrix =
      glm::rotate(m_modelMatrix, glm::radians(m_rotacao.y), glm::vec3(0, 1, 0));
  m_modelMatrix =
      glm::rotate(m_modelMatrix, glm::radians(m_rotacao.z), glm::vec3(0, 0, 1));
  m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_escala));
}
void Arvore::paintGL(GLuint program, glm::mat4 cameraViewMatrix) {
  GLint modelMatrixLoc{glGetUniformLocation(program, "modelMatrix")};
  GLint normalMatrixLoc{glGetUniformLocation(program, "normalMatrix")};
  GLint shininessLoc{glGetUniformLocation(program, "shininess")};
  GLint KaLoc{glGetUniformLocation(program, "Ka")};
  GLint KdLoc{glGetUniformLocation(program, "Kd")};
  GLint KsLoc{glGetUniformLocation(program, "Ks")};
  GLint mappingModeLoc{glGetUniformLocation(program, "mappingMode")};

  // m_posicao = glm::vec3(0);
  for (ulong i = 0; i < m_posicoes.size(); i++) {
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

std::vector<glm::vec3> Arvore::gerarPosicoes() {
  std::uniform_real_distribution<float> rd(-5.0f, 5.0f);

  std::vector<glm::vec3> posicoes{};
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 30; j++) {
      float randX = rd(m_randomEngine) + ((float)(i + j) * 8);
      float randZ = (rd(m_randomEngine) + i) * (float(j * 5));
      posicoes.push_back(glm::vec3(randX, 0, randZ));
    }
  }
  return posicoes;
}
// void Ground::paintGL() {
//   // Draw a grid of tiles centered on the xz plane
//   const int N{5};

//   abcg::glBindVertexArray(m_VAO);
//   for (const auto z : iter::range(-N, N + 1)) {
//     for (const auto x : iter::range(-N, N + 1)) {
//       // Set model matrix
//       glm::mat4 model{1.0f};
//       model = glm::translate(model, glm::vec3(x, 0.0f, z));
//       abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

//       // Set color (checkerboard pattern)
//       const float blue{(z + x) % 2 == 0 ? 0.12f : 0.21f};
//       abcg::glUniform4f(m_colorLoc, 0.00f, blue, 0.38f, 1.0f);

//       abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//     }
//   }
//   abcg::glBindVertexArray(0);
// }

void Arvore::terminateGL() {}

Arvore::~Arvore() {}