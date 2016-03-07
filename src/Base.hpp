#pragma once


enum {
  TITLE,
  MAIN,
};


struct Base {
  virtual ~Base() = default;

  virtual int update(AppEnv& env) = 0;
  virtual void draw()             = 0;
};
