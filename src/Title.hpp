#pragma once

// 仮画面A

#include "Base.hpp"


class Title : public Base {
  Texture image_;
  

public:
  Title()
    : image_("res/a.png")
  {}


  int update(AppEnv& env) override {
    if (env.isPushButton(Mouse::LEFT)) {
      // 左クリックで次の画面への移行を通知
      return MAIN;
    }

    return TITLE;
  }

  void draw() override {
    drawTextureBox(-256, -256, 512, 512,
                   0, 0, 512, 512,
                   image_);
  }
  
};
