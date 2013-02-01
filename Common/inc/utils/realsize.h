#ifndef REALSIZE_H_
#define REALSIZE_H_

class TRealSize
    {
public:
    inline TRealSize(const TReal& aWidth, const TReal& aHeight) : iWidth(aWidth), iHeight(aHeight) {}
    TReal iWidth;
    TReal iHeight;
    };

#endif //REALSIZE_H_
