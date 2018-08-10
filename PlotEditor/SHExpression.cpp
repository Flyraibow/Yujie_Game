#include "SHExpression.h"

#include "SHPlotContext.h"

#include <cstdlib>
#include <cassert>

namespace SailingHeroAPI {

using Expr = SHExpression;

bool ToBoolean(const std::string &value) {
    return !(value.empty() || value == "0" || value == "false");
}

double ToNumber(const std::string &value) {
    double result = std::strtod(value.c_str(), nullptr);
    if (result == HUGE_VAL)
        result = 0.0;
    return result;
}

class BinaryExpr : public Expr {
public:
    enum Operator {
        INVALID, LT = 1, LE = 2, EQ = 4, GE = 8, GT = 16, NE = 32, AND = 64, OR = 128
    };

    Operator op;
    std::unique_ptr<Expr> left, right;

    std::string eval() override {
        bool result = false;;
        if ((op | (LT|LE|EQ|GE|GT|NE)) != 0) {
            double v1 = ToNumber(left->eval());
            double v2 = ToNumber(right->eval());
            switch (op) {
                case LT: result = v1 < v2; break;
                case LE: result = v1 <= v2; break;
                case EQ: result = v1 == v2; break;
                case GE: result = v1 >= v2; break;
                case GT: result = v1 > v2; break;
                case NE: result = v1 != v2; break;
                default: break;
            }
        } else {
            bool v1 = ToBoolean(left->eval());
            bool v2 = ToBoolean(right->eval());
            switch (op) {
                case AND: result = v1 && v2; break;
                case OR: result = v1 || v2; break;
                default: break;
            }
        }
        return result ? "true" : "false";
    }
};

class UnaryExpr : public Expr {
public:
    enum Operator {
        INVALID, NOT
    };

    Operator op;
    std::unique_ptr<Expr> expr;

    std::string eval() override {
        return ToBoolean(expr->eval()) ? "false" : "true";
    }
};

class PrimaryExpr : public Expr {
public:
    enum Operator {
        GAME_DATA_QUERY, CACHE_DATA_QUERY, CONSTANT, FUNCTION
    };

    Operator op;
    struct Metadata {
        struct {
            std::string dataSetName;
            std::string id;
            std::string fieldName;
        } game_data_query_data;
        struct {
            std::string key;
        } cache_data_query_data;
        struct {
            std::string value;
        } constant_data;
        struct {
            std::string funcName;
            std::vector<std::unique_ptr<Expr>> arguments;
        } function_data;
    } metadata;

    std::string eval() override {
        std::string result;
        std::vector<std::string> arguments;
        switch (op) {
            case GAME_DATA_QUERY:
                result = SHPlotContext::getInstance()->evalGameDataQuery(
                    metadata.game_data_query_data.dataSetName,
                    metadata.game_data_query_data.id,
                    metadata.game_data_query_data.fieldName);
                break;
            case CACHE_DATA_QUERY:
                result = SHPlotContext::getInstance()->evalCacheDataQuery(
                    metadata.cache_data_query_data.key);
                break;
            case CONSTANT:
                result = metadata.constant_data.value;
                break;
            case FUNCTION:
                arguments.reserve(metadata.function_data.arguments.size());
                for (auto & expr : metadata.function_data.arguments) {
                    arguments.push_back(expr->eval());
                }
                result = SHPlotContext::getInstance()->evalBuiltinFunction(
                    metadata.function_data.funcName,
                    arguments);
                break;
            default:
                break;
        }
        return result;
    }
};

class Tokenizer {
public:
    Tokenizer(const std::string & e) : expr(e), pos(0) {
        skipSpaces();
    }

    bool isRelOp() const {
        return pos < expr.size() &&
            (expr[pos] == '<' ||
             expr[pos] == '=' ||
             expr[pos] == '>' ||
             (expr[pos] == '!' && expr[pos + 1] == '='));
    }
    bool isAndOp() const {
        return expr.substr(pos, 2) == "&&";
    }
    bool isOrOp() const {
        return expr.substr(pos, 2) == "||";
    }
    bool isNotOp() const {
        return pos < expr.size() && expr[pos] == '!';
    }
    bool isName() const {
        return pos < expr.size() && (expr[pos] == '_' || isalpha(expr[pos]));
    }
    bool isConst() const {
        return pos < expr.size() && (expr[pos] == '"' || isdigit(expr[pos]));
    }
    bool skipChar(char c) {
        if (pos < expr.size() && expr[pos] == c) {
            advancePos(1);
            return true;
        } else
            return false;
    }
    bool isId() const {
        return pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '-' && isdigit(expr[pos + 1]));
    }
    BinaryExpr::Operator getBinaryOp() {
        BinaryExpr::Operator op = BinaryExpr::INVALID;
        if (pos < expr.size()) {
            switch (expr[pos])
            {
                case '<':
                    if (expr[pos + 1] == '=') {
                        op = BinaryExpr::LE;
                        advancePos(2);
                    } else {
                        op = BinaryExpr::LT;
                        advancePos(1);
                    }
                    break;
                case '=':
                    assert(expr[pos + 1] == '=');
                    op = BinaryExpr::EQ;
                    advancePos(2);
                    break;
                case '>':
                    if (expr[pos + 1] == '=') {
                        op = BinaryExpr::GE;
                        advancePos(2);
                    }
                    else {
                        op = BinaryExpr::GT;
                        advancePos(1);
                    }
                    break;
                case '!':
                    assert(expr[pos + 1] == '=');
                    op = BinaryExpr::NE;
                    advancePos(2);
                    break;
                case '&':
                    assert(expr[pos + 1] == '&');
                    op = BinaryExpr::AND;
                    advancePos(2);
                    break;
                case '|':
                    assert(expr[pos + 1] == '|');
                    op = BinaryExpr::OR;
                    advancePos(2);
                    break;
                default:
                    break;
            }
        }
        return op;
    }
    UnaryExpr::Operator getUnaryOp() {
        if (pos < expr.size() && expr[pos] == '!') {
            advancePos(1);
            return UnaryExpr::NOT;
        } else
            return UnaryExpr::INVALID;
    }
    std::string peekName() const {
        size_t end = pos + 1;
        while (end < expr.size() && (expr[end] == '_' || isalnum(expr[end])))
            ++end;
        return expr.substr(pos, end - pos);
    }
    std::string getName() {
        size_t end = pos + 1;
        while (end < expr.size() && (expr[end] == '_' || isalnum(expr[end])))
            ++end;
        std::string name = expr.substr(pos, end - pos);
        advancePos(end - pos);
        return name;
    }
    std::string getConst() {
        size_t end = pos;
        std::string constant;
        if (end < expr.size()) {
            if (isdigit(expr[end])) {
                while (end < expr.size() && isdigit(expr[end]))
                    ++end;
                if (end < expr.size() && expr[end] == '.')
                    ++end;
                while (end < expr.size() && isdigit(expr[end]))
                    ++end;
                constant = expr.substr(pos, end - pos);
                advancePos(end - pos);
            } else {
                assert(expr[end] == '"');
                ++end;
                while (end < expr.size() && expr[end] != '"')
                    ++end;
                assert(end != expr.size());
                constant = expr.substr(pos + 1, end - pos - 1);
                advancePos(end - pos - 1);
            }
        }
        return constant;
    }
    std::string getId() {
        size_t end = pos;
        if (end < expr.size() && expr[end] == '-')
            ++end;
        while (end < expr.size() && isdigit(expr[end]))
            ++end;
        std::string id = expr.substr(pos, end - pos);
        advancePos(end - pos);
        return id;
    }

private:
    void skipSpaces() {
        while (pos < expr.size() && isspace(expr[pos]))
            ++pos;
    }
    void advancePos(size_t count) {
        pos += count;
        skipSpaces();
    }

    std::string expr;
    size_t pos;
};

class ExpressionParser {
public:
    ExpressionParser(const std::string & expr) : tokens(expr) {}
    std::unique_ptr<Expr> relExpr() {
        std::unique_ptr<Expr> left = orExpr();
        if (tokens.isRelOp()) {
            BinaryExpr::Operator op = tokens.getBinaryOp();
            std::unique_ptr<Expr> right = orExpr();

            if (left && right) {
                BinaryExpr * rel = new BinaryExpr;
                rel->left = std::move(left);
                rel->op = op;
                rel->right = std::move(right);
                return std::unique_ptr<Expr>(rel);
            } else
                return nullptr;
        } else {
            return left;
        }
    }
    std::unique_ptr<Expr> orExpr() {
        std::unique_ptr<Expr> left = andExpr();
        if (tokens.isOrOp()) {
            BinaryExpr::Operator op = tokens.getBinaryOp();
            std::unique_ptr<Expr> right = andExpr();

            if (left && right) {
                BinaryExpr * rel = new BinaryExpr;
                rel->left = std::move(left);
                rel->op = op;
                rel->right = std::move(right);
                return std::unique_ptr<Expr>(rel);
            } else
                return nullptr;
        }
        else {
            return left;
        }
    }
    std::unique_ptr<Expr> andExpr() {
        std::unique_ptr<Expr> left = notExpr();
        if (tokens.isAndOp()) {
            BinaryExpr::Operator op = tokens.getBinaryOp();
            std::unique_ptr<Expr> right = notExpr();

            if (left && right) {
                BinaryExpr * rel = new BinaryExpr;
                rel->left = std::move(left);
                rel->op = op;
                rel->right = std::move(right);
                return std::unique_ptr<Expr>(rel);
            } else
                return nullptr;
        }
        else {
            return left;
        }
    }
    std::unique_ptr<Expr> notExpr() {
        if (tokens.isNotOp()) {
            UnaryExpr::Operator op = tokens.getUnaryOp();
            std::unique_ptr<Expr> expr = primaryExpr();

            if (expr) {
                UnaryExpr *unary = new UnaryExpr;
                unary->op = op;
                unary->expr = std::move(expr);
                return std::unique_ptr<Expr>(unary);
            } else
                return nullptr;
        } else {
            return primaryExpr();
        }
    }
    std::unique_ptr<Expr> primaryExpr() {
        std::unique_ptr<Expr> expr;

        if (tokens.isName())
        {
            PrimaryExpr::Operator op;
            PrimaryExpr::Metadata md;
            bool succeed = false;

            do {
                if (tokens.peekName() == "cache") {
                    tokens.getName();
                    if (!tokens.skipChar('.'))
                        break;
                    op = PrimaryExpr::CACHE_DATA_QUERY;
                    if (!tokens.isName())
                        break;
                    md.cache_data_query_data.key = tokens.getName();
                    succeed = true;
                } else if (tokens.peekName() == "game") {
                    tokens.getName();
                    if (!tokens.skipChar('.'))
                        break;
                    op = PrimaryExpr::GAME_DATA_QUERY;
                    if (!tokens.isName()
                        || tokens.peekName().substr(tokens.peekName().size() - 4, 4) != "Data")
                        break;
                    md.game_data_query_data.dataSetName = tokens.getName();
                    if (!tokens.skipChar('('))
                        break;
                    if (!tokens.isId())
                        break;
                    md.game_data_query_data.id = tokens.getId();
                    if (!tokens.skipChar(')'))
                        break;
                    if (!tokens.skipChar('.'))
                        break;
                    if (!tokens.isName())
                        break;
                    md.game_data_query_data.fieldName = tokens.getName();
                    succeed = true;
                } else {
                    op = PrimaryExpr::FUNCTION;
                    md.function_data.funcName = tokens.getName();
                    if (!tokens.skipChar('('))
                        break;
                    do {
                        md.function_data.arguments.emplace_back(relExpr());
                    } while (tokens.skipChar(','));
                    if (!tokens.skipChar(')'))
                        break;
                }
            } while (false);

            if (succeed) {
                PrimaryExpr *primary = new PrimaryExpr;
                primary->op = op;
                primary->metadata = std::move(md);
                expr.reset(primary);
            }
        }
        else if (tokens.isConst())
        {
            PrimaryExpr *primary = new PrimaryExpr;
            primary->op = PrimaryExpr::CONSTANT;
            primary->metadata.constant_data.value = tokens.getConst();
            expr.reset(primary);
        }
        else
        {
            if (tokens.skipChar('('))
                expr = relExpr();
            if (!tokens.skipChar(')'))
                expr.reset();
        }

        return expr;
    }

private:
    Tokenizer tokens;
};

std::unique_ptr<SHExpression> BuildSHExpression(std::string expr)
{
    ExpressionParser parser(expr);
    return parser.relExpr();
}

}
