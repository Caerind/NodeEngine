#ifndef NTICKABLE_HPP
#define NTICKABLE_HPP

class NTickable
{
    public:
        NTickable();

        virtual void tick(float dt);
};

#endif // NTICKABLE_HPP
