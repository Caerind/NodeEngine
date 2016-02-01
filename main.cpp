#include <iostream>

#include "Source/Utils/Time.hpp"
#include "Source/Utils/Log.hpp"
#include "Source/Utils/Compression.hpp"
#include "Source/Utils/Cocoa.hpp"
#include "Source/Utils/Gzstream.hpp"
#include "Source/Utils/Json.hpp"
#include "Source/Utils/Pugixml.hpp"
#include "Source/Utils/String.hpp"
#include "Source/Utils/Assume.hpp"
#include "Source/Utils/Array.hpp"
#include "Source/Utils/Map.hpp"
#include "Source/Utils/Vector.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;
    std::cout << NTime::getTime("[%x][%X]") << std::endl;

    NLog::log("test");

    std::string s = "Test";
    std::cout << s << std::endl;
    NCompression::compress(s);
    std::cout << s << std::endl;
    NCompression::decompress(s);
    std::cout << s << std::endl;

    std::string t = cocoa::SHA1("Hello");
    std::cout << t << " = " << cocoa::SHA1("Hello") << std::endl;

    NArray<int> a;
    a.add(1);
    a.add(3);
    std::vector<int> b = {2,4};
    a.append(b);
    a.remove(4);
    a.erase(2);
    std::cout << a.size() << std::endl;

    NMap<std::string,int> c;
    c.add("Test",4);
    c.add("Tedqsd",6);
    c.add("Tedqs",8);
    c["jer"] = 0;
    std::cout << c.contains("Test") << std::endl;

    NVector v;
    v = NVector::UpVector();

    std::string t1 = "test test";
    std::string t2 = NString::split(t1," ");
    std::cout << "-" << t1 << "-" << t2 << "-" << std::endl;

    bool error = true;
    Assume(!error);

    return 0;
}
