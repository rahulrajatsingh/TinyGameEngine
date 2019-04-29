#pragma once

namespace GEngine
{
  class IObject
  {
  public:
    IObject(void);
    virtual ~IObject(void);

    virtual int Render() = 0;
    
  private:
		//this guy will deal with the preparation of vertexes for the shape
		virtual void PrepareShape() = 0;  
  };
}