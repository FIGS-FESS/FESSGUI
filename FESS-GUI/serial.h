#ifndef SERIAL_H
#define SERIAL_H

#define MAX 32

class Serial
{
    public:
        Serial();
        ~Serial();

        bool append(char x);
        bool getInterfaces();

    private:
        int len;
};

#endif // SERIAL_H
