// Fadeのサンプル

#include "lib/framework.hpp"
#include "Fade.hpp"
#include "Title.hpp"
#include "Main.hpp"


enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT);

  // 開始時のFade
  Fade fade(1.0f,
            Color(0, 0, 0, 1), Color(0, 0, 0, 0),
            []() {});

  // 初期画面
  std::shared_ptr<Base> proc;
  proc = std::make_shared<Title>();
  int current_proc = TITLE;

  // Fade中は画面遷移しない
  bool is_fade = false;
  
  while (env.isOpen()) {
    env.begin();

    // 画面遷移の検出をBase::updateの戻り値で行っている
    int next_proc = proc->update(env);
    if (!is_fade && (next_proc != current_proc)) {
      switch (next_proc) {
      case TITLE:
        fade = Fade(2.0f,
                    Color(1, 1, 1, 0),
                    Color(1, 1, 1, 1),
                    Color(1, 1, 1, 0),
                    [&proc]() { proc = std::make_shared<Title>(); },
                    [&is_fade]() { is_fade = false; });
        break;

      case MAIN:
        fade = Fade(2.0f,
                    Color(1, 1, 0, 0),
                    Color(1, 1, 0, 1),
                    Color(1, 1, 0, 0),
                    [&proc]() { proc = std::make_shared<Main>(); },
                    [&is_fade]() { is_fade = false; });
        break;
      }
      
      current_proc = next_proc;
      is_fade = true;
    }
    
    fade.update(1.0f / 60.0f);
    
    proc->draw();
    fade.draw();
    
    env.end();
  }
}
