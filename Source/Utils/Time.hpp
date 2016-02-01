#ifndef NTIME_HPP
#define NTIME_HPP

#include <ctime>
#include <string>

namespace NTime
{

std::string getTime(std::string const& timeFormat);

int getHours();
int getMinutes();
int getSeconds();

int getDay();
int getMonth();
int getYear();

} // namespace NTime

#endif // NTIME_HPP
