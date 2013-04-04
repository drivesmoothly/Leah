#ifndef NOTIMPL_H_INCLUDED
#define NOTIMPL_H_INCLUDED

#include <exception>

/// Not implemented exception
class NotImplException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Function not implemented";
    }
};

#endif // NOTIMPL_H_INCLUDED
