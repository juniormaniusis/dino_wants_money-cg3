#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <vector>

#include "abcg.hpp"
#include "camera.hpp"
#include "chao.hpp"
#include "gamedata.hpp"
#include "model.hpp"
#include "pacman.hpp"
#include "parede.hpp"

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

  Parede m_parede1;

  Model m_modelFloor;

  // TODO:: REVISAR
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Id{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Is{1.0f, 1.0f, 1.0f, 1.0f};

  void update();

  void handleEventUpPressed(SDL_Event& ev);
  void handleEventDownPressed(SDL_Event& ev);
  void handleEventLeftPressed(SDL_Event& ev);
  void handleEventRightPressed(SDL_Event& ev);
  void handleEventQPressed(SDL_Event& ev);
  void handleEventEPressed(SDL_Event& ev);
  void handleEventUpReleased(SDL_Event& ev);
  void handleEventDownReleased(SDL_Event& ev);
  void handleEventLeftReleased(SDL_Event& ev);
  void handleEventRightReleased(SDL_Event& ev);
  void handleEventQReleased(SDL_Event& ev);
  void handleEventEReleased(SDL_Event& ev);
};

#endif