#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>

void OpenGLWindow::handleEvent(SDL_Event& ev) {
  if (ev.type == SDL_KEYDOWN) {
    if (ev.key.keysym.sym == SDLK_z) m_dollySpeed = 1.0f;  // dolly
    if (ev.key.keysym.sym == SDLK_x) m_dollySpeed = -1.0f;
    if (ev.key.keysym.sym == SDLK_LEFT) m_panSpeed = -1.0f;  // panSide
    if (ev.key.keysym.sym == SDLK_RIGHT) m_panSpeed = 1.0f;
    if (ev.key.keysym.sym == SDLK_UP) m_panVertSpeed = 1.0f;  // panVert
    if (ev.key.keysym.sym == SDLK_DOWN) m_panVertSpeed = -1.0f;
    if (ev.key.keysym.sym == SDLK_w) m_kart.m_speed = 1.0f;  // kartMove
    if (ev.key.keysym.sym == SDLK_s) m_kart.m_speed = -1.0f;
    if (ev.key.keysym.sym == SDLK_a) m_kart.m_side = 1.0f;
    if (ev.key.keysym.sym == SDLK_d) m_kart.m_side = -1.0f;
    if (ev.key.keysym.sym == SDLK_j) m_truckSpeed = -1.0f;  // truckSide
    if (ev.key.keysym.sym == SDLK_l) m_truckSpeed = 1.0f;
    if (ev.key.keysym.sym == SDLK_k) m_truckVertSpeed = -1.0f;  // truckVert
    if (ev.key.keysym.sym == SDLK_i) m_truckVertSpeed = 1.0f;
  }
  if (ev.type == SDL_KEYUP) {
    if ((ev.key.keysym.sym == SDLK_z) && m_dollySpeed > 0) m_dollySpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_x) && m_dollySpeed < 0) m_dollySpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_LEFT) && m_panSpeed < 0) m_panSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_RIGHT) && m_panSpeed > 0) m_panSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_UP) && m_panVertSpeed > 0)
      m_panVertSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_DOWN) && m_panVertSpeed < 0)
      m_panVertSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_w) && m_kart.m_speed > 0)
      m_kart.m_speed = 0.0f;  // kartMove
    if ((ev.key.keysym.sym == SDLK_s) && m_kart.m_speed < 0)
      m_kart.m_speed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_a) && m_kart.m_side > 0)
      m_kart.m_side = 0.0f;
    if ((ev.key.keysym.sym == SDLK_d) && m_kart.m_side < 0)
      m_kart.m_side = 0.0f;
    if ((ev.key.keysym.sym == SDLK_j) && m_truckSpeed < 0) m_truckSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_l) && m_truckSpeed > 0) m_truckSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_k) && m_truckVertSpeed < 0)
      m_truckVertSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_i) && m_truckVertSpeed > 0)
      m_truckVertSpeed = 0.0f;
  }
}

void OpenGLWindow::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);

  m_program = createProgramFromFile(getAssetsPath() + "shaders/texture.vert",
                                    getAssetsPath() + "shaders/texture.frag");

  m_model.loadDiffuseTexture(getAssetsPath() + "maps/Cylinder2.png");
  m_modelFloor.loadDiffuseTexture(getAssetsPath() + "maps/floor.jpg");
  m_modelWall.loadDiffuseTexture(getAssetsPath() + "maps/wall.jpg");
  // Load model
  m_model.loadFromFile(getAssetsPath() + "kart23.obj");
  m_modelWall.loadFromFile(getAssetsPath() + "track_wall.obj");
  m_modelFloor.loadFromFile(getAssetsPath() + "track_floor.obj");

  m_model.setupVAO(m_program);
  m_modelWall.setupVAO(m_program);
  m_modelFloor.setupVAO(m_program);
  resizeGL(getWindowSettings().width, getWindowSettings().height);
}

void OpenGLWindow::paintGL() {
  update();

  // Clear color buffer and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  glUseProgram(m_program);

  // Get location of uniform variables (could be precomputed)
  GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
  GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};
  GLint modelMatrixLoc{glGetUniformLocation(m_program, "modelMatrix")};
  GLint normalMatrixLoc{glGetUniformLocation(m_program, "normalMatrix")};
  GLint lightDirLoc{glGetUniformLocation(m_program, "lightDirWorldSpace")};
  GLint shininessLoc{glGetUniformLocation(m_program, "shininess")};
  GLint IaLoc{glGetUniformLocation(m_program, "Ia")};
  GLint IdLoc{glGetUniformLocation(m_program, "Id")};
  GLint IsLoc{glGetUniformLocation(m_program, "Is")};
  GLint KaLoc{glGetUniformLocation(m_program, "Ka")};
  GLint KdLoc{glGetUniformLocation(m_program, "Kd")};
  GLint KsLoc{glGetUniformLocation(m_program, "Ks")};
  GLint diffuseTexLoc{glGetUniformLocation(m_program, "diffuseTex")};
  GLint mappingModeLoc{glGetUniformLocation(m_program, "mappingMode")};

  // todos
  glUniform4fv(lightDirLoc, 1, &m_lightDir.x);
  glUniform4fv(IaLoc, 1, &m_Ia.x);
  glUniform4fv(IdLoc, 1, &m_Id.x);
  glUniform4fv(IsLoc, 1, &m_Is.x);
  glUniform1i(diffuseTexLoc, 0);

  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera.m_projMatrix[0][0]);

  // treno
  glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_kart.m_modelMatrix[0][0]);

  auto modelViewMatrix{glm::mat3(m_camera.m_viewMatrix * m_kart.m_modelMatrix)};
  glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

  glUniform1f(shininessLoc, m_model.m_shininess);  // depois mudar nos outros
  glUniform4fv(KaLoc, 1, &m_model.m_Ka.x);
  glUniform4fv(KdLoc, 1, &m_model.m_Kd.x);
  glUniform4fv(KsLoc, 1, &m_model.m_Ks.x);

  glUniform1i(mappingModeLoc, 3);  // from mesh

  m_model.render();

  glm::mat4 wallModel{1.0f};
  // current
  glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &wallModel[0][0]);

  auto modelViewMatrix2{
      glm::mat3(m_camera.m_viewMatrix * wallModel)};  // se pá nem precisa
  glm::mat3 normalMatrix2{glm::inverseTranspose(modelViewMatrix2)};
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix2[0][0]);

  // modelWall
  glUniform1f(shininessLoc, m_modelWall.m_shininess);
  glUniform4fv(KaLoc, 1, &m_modelWall.m_Ka.x);
  glUniform4fv(KdLoc, 1, &m_modelWall.m_Kd.x);
  glUniform4fv(KsLoc, 1, &m_modelWall.m_Ks.x);

  glUniform1i(mappingModeLoc, 0);  // o mesmo para os dois

  m_modelWall.render();

  // modelFloor
  glUniform1f(shininessLoc, m_modelFloor.m_shininess);
  glUniform4fv(KaLoc, 1, &m_modelFloor.m_Ka.x);
  glUniform4fv(KdLoc, 1, &m_modelFloor.m_Kd.x);
  glUniform4fv(KsLoc, 1, &m_modelFloor.m_Ks.x);

  m_modelFloor.render();

  glUseProgram(0);
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();
  auto widgetSize{ImVec2(200, 40)};
  ImGui::SetNextWindowPos(ImVec2(m_viewportWidth - widgetSize.x - 5, 5));
  ImGui::SetNextWindowSize(widgetSize);
  ImGui::Begin("Camera Select", nullptr, ImGuiWindowFlags_NoDecoration);
  {
    static std::size_t currentIndex{};
    std::vector<std::string> comboItems{"Third Person", "Free"};

    ImGui::PushItemWidth(120);
    if (ImGui::BeginCombo("Camera", comboItems.at(currentIndex).c_str())) {
      for (auto index : iter::range(comboItems.size())) {
        const bool isSelected{currentIndex == index};
        if (ImGui::Selectable(comboItems.at(index).c_str(), isSelected))
          currentIndex = index;
        if (isSelected) ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    if (currentIndex == 0) {
      m_camera.m_free = false;
    } else {
      m_camera.m_free = true;
    }
  }

  ImGui::End();
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_camera.computeProjectionMatrix(width, height);
}

void OpenGLWindow::terminateGL() { glDeleteProgram(m_program); }
void OpenGLWindow::update() {
  float deltaTime{static_cast<float>(getDeltaTime())};

  deltaTime = deltaTime * 2.5f;

  if (m_camera.m_free) {
    // Update LookAt camera
    m_camera.dolly(m_dollySpeed * deltaTime);
    m_camera.truck(m_truckSpeed * deltaTime);
    m_camera.truckVert(m_truckVertSpeed * deltaTime);
    m_camera.pan(m_panSpeed * deltaTime);
    m_camera.panVert(m_panVertSpeed * deltaTime);
  } else {
    m_camera.centerKart(m_kart.m_position, m_kart.m_angle);
  }

  m_kart.moveKart(m_kart.m_speed * deltaTime, m_kart.m_side * deltaTime);
}
