#ifndef NACTOR_HPP
#define NACTOR_HPP

#include <memory>
#include "RootComponent.hpp"

class NActor : public NRootComponent
{
    public:
        NActor();

        typedef std::shared_ptr<NActor> Ptr;

        virtual void save(pugi::xml_node& node);
};

#endif // NACTOR_HPP
