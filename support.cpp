#include "support.h"


template <typename Iter>
QString join(Iter begin, Iter end, const std::string& sep)
{
  std::stringstream result;
  if (begin != end)
      result << QString::toStdString(*begin++);
  while (begin != end)
      result << sep << QString::toStdString(*begin++);
  return QString::fromStdString(result.str());
}
