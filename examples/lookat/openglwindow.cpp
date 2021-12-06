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

void OpenGLWindow::handleEvent(SDL_Event& ev) {
  if (ev.type == SDL_KEYDOWN) {
    if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) {
      m_camera.m_dollySpeed = 1.0f;

      // segue o movimento na direção que está.
      m_pacman.m_velocidade = 1;
    }
    if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) {
      m_camera.m_dollySpeed = -1.0f;

      // segue o movimento na direção contrária que está.
      m_pacman.m_velocidade = -1;
    }

    if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) {
      m_camera.m_panSpeed = -1.0f;
      m_pacman.m_sentidoRotacao = -1.0f;
    }

    if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) {
      m_camera.m_panSpeed = 1.0f;
      m_pacman.m_sentidoRotacao = 1.0f;
    }

    if (ev.key.keysym.sym == SDLK_q) {
      m_camera.m_truckSpeed = -1.0f;
    }
    if (ev.key.keysym.sym == SDLK_e) {
      m_camera.m_truckSpeed = 1.0f;
    }
  }
  if (ev.type == SDL_KEYUP) {
    if ((ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) &&
        m_camera.m_dollySpeed > 0) {
      m_camera.m_dollySpeed = 0.0f;
      m_pacman.m_velocidade = 0.0f;
    }

    if ((ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) &&
        m_camera.m_dollySpeed < 0) {
      m_camera.m_dollySpeed = 0.0f;
      m_pacman.m_velocidade = 0.0f;
    }

    if ((ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) &&
        m_camera.m_panSpeed < 0) {
      m_camera.m_panSpeed = 0.0f;
      m_pacman.m_sentidoRotacao = 0.0f;
    }
    if ((ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) &&
        m_camera.m_panSpeed > 0) {
      m_camera.m_panSpeed = 0.0f;
      m_pacman.m_sentidoRotacao = 0.0f;
    }
    if (ev.key.keysym.sym == SDLK_q && m_camera.m_truckSpeed < 0) {
      m_camera.m_truckSpeed = 0.0f;
    }
    if (ev.key.keysym.sym == SDLK_e && m_camera.m_truckSpeed > 0) {
      m_camera.m_truckSpeed = 0.0f;
    }
  }
}

void OpenGLWindow::initializeGL() {
  abcg::glClearColor(.3, .3, .3, 1);

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_program = createProgramFromFile(getAssetsPath() + "shaders/texture.vert",
                                    getAssetsPath() + "shaders/texture.frag");

  m_parede1.initializeGL(m_program, getAssetsPath(), glm::vec3(0),
                         glm::vec3(3, 0, 0));
  m_chao.initializeGL(m_program, getAssetsPath(), 4);
  m_pacman.initializeGL(getAssetsPath(),
                        m_program);  // todo: inverter esses parametros

  m_camera.initialize(m_pacman.m_posicao_inicial);

  m_modelFloor.loadDiffuseTexture(getAssetsPath() + "maps/floor.jpg");
  m_modelFloor.loadFromFile(getAssetsPath() + "track_floor.obj");
  m_modelFloor.setupVAO(m_program);

  // configura a tela para as dimensões iniciais.
  resizeGL(getWindowSettings().width, getWindowSettings().height);
}

void OpenGLWindow::paintGL() {
  update();

  // Clear color buffer and depth buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  abcg::glUseProgram(m_program);

  GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
  GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};

  GLint lightDirLoc{glGetUniformLocation(m_program, "lightDirWorldSpace")};

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

  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera.m_projMatrix[0][0]);

  m_parede1.paintGL(m_program, m_camera.m_viewMatrix);
  m_chao.paintGL(m_program, m_camera.m_viewMatrix);
  m_pacman.paintGL(m_program, m_camera.m_viewMatrix);
  glUseProgram(0);
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();

  // Create a window for the other widgets
  {
    const auto widgetSize{ImVec2(222, 90)};
    ImGui::SetNextWindowPos(ImVec2(m_viewportWidth - widgetSize.x - 5, 5));
    ImGui::SetNextWindowSize(widgetSize);
    ImGui::Begin("Widget window", nullptr, ImGuiWindowFlags_NoDecoration);

    static bool cameraFixa{true};
    ImGui::Checkbox("Camera Fixa", &cameraFixa);

    if (cameraFixa) {
      m_camera.m_cameraMode = CameraMode::Fixa;
    } else {
      m_camera.m_cameraMode = CameraMode::Livre;
    }

    /*
      {
        ImGui::SetNextWindowPos(ImVec2(5, m_viewportHeight - 94));
        ImGui::SetNextWindowSize(ImVec2(m_viewportWidth - 10, -1));
        ImGui::Begin("Slider window", nullptr, ImGuiWindowFlags_NoDecoration);

        // Create a slider to control the number of rendered triangles
        {
          // Slider will fill the space of the window
          ImGui::PushItemWidth(m_viewportWidth - 25);

          ImGui::SliderFloat3("", &m_camera.m_distance.x, -5.0f, 5.0f,
                              "%f u.m distância");

          ImGui::PopItemWidth();
        }

        ImGui::End();
      }
  */
    ImGui::End();
  }
}

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
  m_lightDir = glm::vec4(glm::normalize(m_camera.m_at - m_camera.m_eye), 0);
  const float deltaTime{static_cast<float>(getDeltaTime())};

  auto direcaoCamera = m_camera.getDirection();
  auto direcaoCameraXZ = glm::vec3(direcaoCamera.x, 0, direcaoCamera.z);

  m_pacman.update(deltaTime, direcaoCameraXZ);
  m_camera.update(deltaTime, m_pacman.m_posicao_atual,
                  m_pacman.m_sentidoRotacao);
}