#ifndef HANDLERVISITOR_H_
#define HANDLERVISITOR_H_

class _MHandlerBase;
class CHandlerMethodBase;

class MHandlerVisitor
	{
public:
	virtual void Visit(const _MHandlerBase& aHandler) = 0;
	virtual void Visit(const CHandlerMethodBase& aHandler) = 0;
	};

#endif //HANDLERVISITOR_H_
