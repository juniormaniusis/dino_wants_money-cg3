#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <string_view>
#include "abcg.hpp"
#include "camera.hpp"
#include "model.hpp"
#include "kart.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  GLuint m_program{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  Model m_model;
  Model m_modelWall;
  Model m_modelFloor;
  Camera m_camera;
  Kart m_kart;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};
  float m_truckVertSpeed{0.0f};
  float m_panVertSpeed{0.0f};

  // Light and material properties
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Id{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Is{1.0f, 1.0f, 1.0f, 1.0f};
  
  void update();
  
};

#endif