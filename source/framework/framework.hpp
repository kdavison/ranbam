#pragma once

/*
framework:
  modules:
    
*/



namespace ranbam
{
class Framework {
public:
  void update();
private:
  std::list<modules> _modules;
};
}