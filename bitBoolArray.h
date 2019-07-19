// Copyright (c) 2018, ICEE Solutions, All rights reserved.
//! @file bitBoolArray.h
//! @author sng
//! @brief bool array, 1 bit per bool


#ifndef __bitBoolArray_H__
#define __bitBoolArray_H__

#include <vector>

class bitBoolArray 
{
public:
  bitBoolArray(const unsigned size, const bool v =false) : _a((size + 7) >> 3) {if (v) set(); else reset();}

  class bit 
  {
  public:
    bit(unsigned char& c, const unsigned char k) : _c(c), _k(k) {}
    
    bool   get() const {return _c & _k;}
    void   set() {_c |= _k;}
    void reset() {_c &= ~_k;}
    void  flip() {_c ^= _k;}
    void   set(const bool v) {if (v) set(); else reset();}
        
    operator bool() const {return get();}
    void operator =(const bool v) {set(v);}
    void operator&=(const bool v) {if (!v) reset();}
    void operator|=(const bool v) {if (v) set();}
    void operator^=(const bool v) {if (v) flip();}
    
  private:
    unsigned char& _c;
    const unsigned char _k;
  };

  unsigned  size () const {return _a.size() << 3;}
  void     reset () {for (auto i =_a.begin(); i != _a.end(); ++i) *i = 0;}
  void       set () {for (auto i =_a.begin(); i != _a.end(); ++i) *i = 0xff;}
  void       set (const unsigned i, const bool v) {at(i).set(v);}
  void       set (const unsigned i)       {at(i).set();}
  void     reset (const unsigned i)       {at(i).reset();}
  void      flip (const unsigned i)       {at(i).flip();}
  bool       get (const unsigned i) const {return at(i);}
  bool        at (const unsigned i) const {return v(i) & k(i);}
  bit         at (const unsigned i)       {return bit(v(i), k(i));}
  bit  operator[](const unsigned i)       {return at(i);} 
  bool operator[](const unsigned i) const {return at(i);}

private:
  std::vector<unsigned char> _a;
  unsigned char& v(const unsigned i)       {return _a.at(i >>3u);}
  unsigned char  v(const unsigned i) const {return _a.at(i >>3u);}
  unsigned char  k(const unsigned i) const {return 1u << (i & 0x7);}
}; /* end of bitBoolArray */

#endif //__bitBoolArray_H__

