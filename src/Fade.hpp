#pragma once

// Fade In/Out
// 引数でコールバック処理を渡せるのが肝

#include <functional>
#include "lib/graph.hpp"


class Fade {
public:
  using Callback = std::function<void ()>;
  

private:
  float duration_sec_;

  Color begin_color_;
  Color mid_color_;
  Color end_color_;

  Callback mid_callback_;
  Callback end_callback_;
  
  float current_time_sec_;
  Color current_color_;

  bool pass_mid_;
  bool completed_;
  

public:
  // TIPS:「Fade無しの画面切り替え」にも対応したかったので
  //      デフォルトコンストラクタで用意した
  Fade()
    : completed_(true)
  {}

  // Fade OUT→画面切り替え→Fade IN
  // を簡便に書きたかったので
  // 開始色、中間色、終了色の３つ指定をしている
  Fade(const float duration_sec,
       const Color& begin_color,
       const Color& mid_color,
       const Color& end_color,
       Callback mid_callback,
       Callback end_callback)
    : duration_sec_(duration_sec),
      begin_color_(begin_color),
      mid_color_(mid_color),
      end_color_(end_color),
      mid_callback_(mid_callback),
      end_callback_(end_callback),
      current_time_sec_(0.0f),
      current_color_(begin_color_),
      pass_mid_(false),
      completed_(false)
  {}

  // 画面切り替え→Fade IN
  // だけの場合にも対応できるよう
  // 開始色、終了色の２つ指定版も用意
  Fade(const float duration_sec,
       const Color& begin_color,
       const Color& end_color,
       Callback end_callback)
    : duration_sec_(duration_sec),
      begin_color_(begin_color),
      mid_color_((begin_color + end_color) * 0.5f),
      end_color_(end_color),
      mid_callback_([]() {}),
      end_callback_(end_callback),
      current_time_sec_(0.0f),
      current_color_(begin_color_),
      pass_mid_(false),
      completed_(false)
  {}


  bool isCompleted() const {
    return completed_;
  }

  
  void update(const float elapsed_time_sec) {
    if (completed_) return;

    // FIXME:改良の余地はあるが、
    //       開始色→中間色→中間コールバック→終了色→終了コールバック
    //       と言う一連の処理を行っている
    current_time_sec_ += elapsed_time_sec;
    if (current_time_sec_ >= duration_sec_) {
      // Fadeが全て終わったら終了時のコールバックを実行
      end_callback_();
      
      current_time_sec_ = duration_sec_;
      completed_ = true;
    }
    
    float d = current_time_sec_ / duration_sec_;
    if (!pass_mid_ && (d >= 0.5f)) {
      // 中間地点でもコールバックを実行
      // TIPS:画面切り替えのタイミングに使える
      mid_callback_();
      
      pass_mid_ = true;
    }

    // TIPS:Colorを改造して「色の加減算」とかできるようになっている
    if (!pass_mid_) {
      current_color_ = begin_color_ + (mid_color_ - begin_color_) * d * 2.0f;
    }
    else {
      current_color_ = mid_color_ + (end_color_ - mid_color_) * (d - 0.5f) * 2.0f;
    }
  }

  void draw() {
    if (completed_) return;
    
    drawFillBox(-256, -256, 512, 512, current_color_);
  }
  
};
