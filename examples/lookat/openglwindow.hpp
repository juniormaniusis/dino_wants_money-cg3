#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <vector>

#include "abcg.hpp"
#include "camera.hpp"
#include "chao.hpp"
#include "gamedata.hpp"
#include "model.hpp"
#include "pacman.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  Camera m_camera;

  Chao m_chao;
  Pacman m_pacman;

  Model m_modelFloor;

  // TODO:: REVISAR
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Id{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Is{1.0f, 1.0f, 1.0f, 1.0f};

  glm::vec4 FOG_COLOR{0.5, 0.5, 0.5, 1};

  void update();
  void handleEventUpPressed();
  void handleEventDownPressed();
  void handleEventLeftPressed();
  void handleEventRightPressed();
  void handleEventSpaceBarPressed();
  void handleEventUpReleased();
  void handleEventDownReleased();
  void handleEventLeftReleased();
  void handleEventRightReleased();
};

#endif