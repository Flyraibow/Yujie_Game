#ifndef _SH_EXPRESSION_H_
#define _SH_EXPRESSION_H_

#include <string>
#include <memory>

namespace SailingHeroAPI {

class SHExpression {
public:
    virtual ~SHExpression() = default;
    virtual std::string eval() = 0;
    virtual std::string DebugString() { return ""; }
};

std::unique_ptr<SHExpression> BuildSHExpression(std::string expr);

}

#endif
