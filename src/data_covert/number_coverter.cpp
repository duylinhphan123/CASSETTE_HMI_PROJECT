#include "data_covert/number_coverter.h"
bool check_minus(int32_t _num)
{
  if (_num <= 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
byte first2num(int32_t _num)
{
  if (_num < 0)
  {
    _num = -_num;
    _num = (int)((_num / 10000)) % 100;
  }
  else
  {
    _num = (int)((_num / 10000)) % 100;
  }
  return _num;
}
byte mid2num(int32_t _num)
{
  if (_num < 0)
  {
    _num = -_num;
    _num = (int)((_num / 100)) % 100;
  }
  else
  {
    _num = (int)((_num / 100)) % 100;
  }
  return _num;
}
byte last2num(int32_t _num)
{
  if (_num < 0)
  {
    _num = -_num;
    _num = _num % 100;
  }
  else
  {
    _num = _num % 100;
  }
  return _num;
}