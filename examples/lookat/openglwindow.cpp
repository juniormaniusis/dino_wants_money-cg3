#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

#include "gamedata.hpp"

void OpenGLWindow::handleEventUpPressed() {
  m_pacman.m_velocidadeDeslocamento = Pacman::VELOCIDADE_DESCOLAMENTO;
}
void OpenGLWindow::handleEventDownPressed() {
  m_pacman.m_velocidadeDeslocamento = -Pacman::VELOCIDADE_DESCOLAMENTO;
}

void OpenGLWindow::handleEventLeftPressed() {
  m_pacman.m_velocidadeRotacao = Pacman::VELOCIDADE_ROTACAO;
}

void OpenGLWindow::handleEventRightPressed() {
  m_pacman.m_velocidadeRotacao = -Pacman::VELOCIDADE_ROTACAO;
}

void OpenGLWindow::handleEventSpaceBarPressed() { m_pacman.pular(); }

void OpenGLWindow::handleEventUpReleased() {
  m_pacman.m_velocidadeDeslocamento = 0.0f;
}
void OpenGLWindow::handleEventDownReleased() {
  m_pacman.m_velocidadeDeslocamento = 0.0f;
}
void OpenGLWindow::handleEventLeftReleased() {
  m_pacman.m_velocidadeRotacao = 0.0f;
}
void OpenGLWindow::handleEventRightReleased() {
  m_pacman.m_velocidadeRotacao = 0.0f;
}

void OpenGLWindow::handleEvent(SDL_Event& ev) {
  const float deltaTime{static_cast<float>(getDeltaTime())};

  if (ev.type == SDL_MOUSEWHEEL) {
    m_camera.changeDistanceFromPlayer(ev.wheel.y);
  }

  if (ev.type == SDL_MOUSEMOTION &&
      ev.button.button == SDL_BUTTON(SDL_BUTTON_RIGHT)) {
    float deltaX = ev.motion.xrel * deltaTime;
    float deltaY = ev.motion.yrel * deltaTime;
    m_camera.calculateAngleAroundPlayer(deltaX);
    m_camera.calculatePitch(deltaY);
  }

  if (ev.type == SDL_KEYDOWN) {
    if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) {
      handleEventUpPressed();
    }
    if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) {
      handleEventDownPressed();
    }

    if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) {
      handleEventLeftPressed();
    }

    if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) {
      handleEventRightPressed();
    }

    if (ev.key.keysym.sym == SDLK_SPACE) {
      handleEventSpaceBarPressed();
    }
  }
  if (ev.type == SDL_KEYUP) {
    if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) {
      handleEventUpReleased();
    }

    if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) {
      handleEventDownReleased();
    }

    if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) {
      handleEventLeftReleased();
    }
    if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) {
      handleEventRightReleased();
    }
  }
}

void OpenGLWindow::initializeGL() {
  abcg::glClearColor(.5f, .5f, .5f, 1);
  // abcg::glClearColor(0.52f, 0.80f, 0.92f, 1);

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_program = createProgramFromFile(getAssetsPath() + "shaders/texture.vert",
                                    getAssetsPath() + "shaders/texture.frag");

  m_chao.initializeGL(m_program, getAssetsPath());

  m_pacman.initializeGL(getAssetsPath(),
                        m_program);  // todo: inverter esses parametros

  m_camera.initialize();

  m_modelFloor.loadDiffuseTexture(getAssetsPath() + "maps/floor.jpg");
  m_modelFloor.loadFromFile(getAssetsPath() + "track_floor.obj");
  m_modelFloor.setupVAO(m_program);

  // configura a tela para as dimensões iniciais.
  resizeGL(getWindowSettings().width, getWindowSettings().height);
}

void OpenGLWindow::paintGL() {
  update();

  // Clear color buffer and depth buffer
  abcg::glEnable(GL_DEPTH_TEST);
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  abcg::glUseProgram(m_program);

  GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
  GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};

  GLint lightDirLoc{glGetUniformLocation(m_program, "lightDirWorldSpace")};

  GLint skyColorLoc{glGetUniformLocation(m_program, "skyColor")};

  GLint IaLoc{glGetUniformLocation(m_program, "Ia")};
  GLint IdLoc{glGetUniformLocation(m_program, "Id")};
  GLint IsLoc{glGetUniformLocation(m_program, "Is")};

  GLint diffuseTexLoc{glGetUniformLocation(m_program, "diffuseTex")};

  // todos
  glUniform4fv(lightDirLoc, 1, &m_lightDir.x);
  glUniform4fv(IaLoc, 1, &m_Ia.x);
  glUniform4fv(IdLoc, 1, &m_Id.x);
  glUniform4fv(IsLoc, 1, &m_Is.x);
  glUniform1i(diffuseTexLoc, 0);
  glUniform3fv(skyColorLoc, 1, &skyColor.x);

  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera.m_projMatrix[0][0]);

  // m_parede1.paintGL(m_program, m_camera.m_viewMatrix);
  m_chao.paintGL(m_program, m_camera.m_viewMatrix);
  m_pacman.paintGL(m_program, m_camera.m_viewMatrix);
  glUseProgram(0);
}

void OpenGLWindow::paintUI() { abcg::OpenGLWindow::paintUI(); }

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_camera.computeProjectionMatrix(width, height);
}

void OpenGLWindow::terminateGL() {
  // m_ground.terminateGL();
  m_pacman.terminateGL();
  abcg::glDeleteProgram(m_program);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void OpenGLWindow::update() {
  m_lightDir = glm::vec4(glm::normalize(glm::vec3(-1, -1, -1)), 0);
  const float deltaTime{static_cast<float>(getDeltaTime())};
  m_pacman.update(deltaTime);
  m_camera.update(m_pacman.m_posicao, m_pacman.m_rotacao);
}