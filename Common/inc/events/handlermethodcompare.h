#ifndef HANDLERMETHODCOMPARE_H_
#define HANDLERMETHODCOMPARE_H_

#include <e32std.h>
#include "handlervisitor.h"

class CHandlerMethodBase;

class THandlerMethodCompare : public MHandlerVisitor
	{
public:
    IMPORT_C THandlerMethodCompare(CHandlerMethodBase& aFirst);

    IMPORT_C void Visit(const _MHandlerBase& /*aSecond*/);

    IMPORT_C void Visit(const CHandlerMethodBase& aSecond);

	inline TBool Result() const;

private:
	inline void SetResult(TBool aResult);

private:
	CHandlerMethodBase& iFirst;
	TBool iResult;
	};

#include "handlermethodcompare.inl"

#endif //HANDLERMETHODCOMPARE_H_
