#pragma once

// 仮画面B

#include "Base.hpp"


class Main : public Base {
  Texture image_;
  

public:
  Main()
    : image_("res/b.png")
  {}


  int update(AppEnv& env) override {
    if (env.isPushButton(Mouse::LEFT)) {
      // 左クリックで次の画面への移行を通知
      return TITLE;
    }

    return MAIN;
  }

  void draw() override {
    drawTextureBox(-256, -256, 512, 512,
                   0, 0, 512, 512,
                   image_);
  }
};
