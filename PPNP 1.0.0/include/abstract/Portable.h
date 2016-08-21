#ifndef PORTABLE_H
#define PORTABLE_H

#include <iostream>

class Portable
{
  public:
    virtual void save() = 0;
    virtual void load() = 0;
  protected:
    std::string m_filename;
    std::string m_dirpath;
};

#endif // end PORTABLE_H
