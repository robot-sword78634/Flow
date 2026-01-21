#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

// Token types
enum TokenType {
    TOK_EOF, TOK_LET, TOK_PRINT, TOK_INPUT, TOK_INPUT_NUM, TOK_WHEN, TOK_OTHERWISE,
    TOK_REPEAT, TOK_TIMES, TOK_LOOP, TOK_WHILE, TOK_FROM, TOK_TO,
    TOK_LABEL, TOK_GOTO, TOK_RANDOM, TOK_SQRT, TOK_POW, TOK_ABS, TOK_FLOOR, TOK_CEIL,
    TOK_CALL, TOK_DEFINE,
    TOK_ARROW_RIGHT, TOK_ARROW_LEFT, TOK_IDENT, TOK_NUMBER, TOK_STRING,
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PERCENT, TOK_LPAREN, TOK_RPAREN,
    TOK_EQ, TOK_EQEQ, TOK_NEQ, TOK_LT, TOK_GT, TOK_LTE, TOK_GTE,
    TOK_COMMA, TOK_NEWLINE
};

struct Token {
    TokenType type;
    string value;
    int line;
};

// Lexer
class Lexer {
    string source;
    size_t pos;
    int line;

public:
    Lexer(const string& src) : source(src), pos(0), line(1) {}

    vector<Token> tokenize() {
        vector<Token> tokens;
        while (pos < source.length()) {
            char c = source[pos];

            // Skip whitespace (except newlines)
            if (c == ' ' || c == '\t' || c == '\r') {
                pos++;
                continue;
            }

            // Comments
            if (c == '#') {
                while (pos < source.length() && source[pos] != '\n') pos++;
                continue;
            }

            // Newlines
            if (c == '\n') {
                tokens.push_back({TOK_NEWLINE, "\\n", line});
                line++;
                pos++;
                continue;
            }

            // Strings
            if (c == '"') {
                tokens.push_back(readString());
                continue;
            }

            // Numbers
            if (isdigit(c)) {
                tokens.push_back(readNumber());
                continue;
            }

            // Identifiers and keywords
            if (isalpha(c)) {
                tokens.push_back(readIdentifier());
                continue;
            }

            // Operators and symbols
            if (c == '+') { tokens.push_back({TOK_PLUS, "+", line}); pos++; continue; }
            if (c == '*') { tokens.push_back({TOK_STAR, "*", line}); pos++; continue; }
            if (c == '/') { tokens.push_back({TOK_SLASH, "/", line}); pos++; continue; }
            if (c == '%') { tokens.push_back({TOK_PERCENT, "%", line}); pos++; continue; }
            if (c == '(') { tokens.push_back({TOK_LPAREN, "(", line}); pos++; continue; }
            if (c == ')') { tokens.push_back({TOK_RPAREN, ")", line}); pos++; continue; }
            if (c == ',') { tokens.push_back({TOK_COMMA, ",", line}); pos++; continue; }

            // Multi-character operators
            if (c == '-') {
                if (pos + 1 < source.length() && source[pos + 1] == '>') {
                    tokens.push_back({TOK_ARROW_RIGHT, "->", line});
                    pos += 2;
                } else {
                    tokens.push_back({TOK_MINUS, "-", line});
                    pos++;
                }
                continue;
            }

            if (c == '<') {
                if (pos + 1 < source.length() && source[pos + 1] == '-') {
                    tokens.push_back({TOK_ARROW_LEFT, "<-", line});
                    pos += 2;
                } else if (pos + 1 < source.length() && source[pos + 1] == '=') {
                    tokens.push_back({TOK_LTE, "<=", line});
                    pos += 2;
                } else {
                    tokens.push_back({TOK_LT, "<", line});
                    pos++;
                }
                continue;
            }

            if (c == '>') {
                if (pos + 1 < source.length() && source[pos + 1] == '=') {
                    tokens.push_back({TOK_GTE, ">=", line});
                    pos += 2;
                } else {
                    tokens.push_back({TOK_GT, ">", line});
                    pos++;
                }
                continue;
            }

            if (c == '=') {
                if (pos + 1 < source.length() && source[pos + 1] == '=') {
                    tokens.push_back({TOK_EQEQ, "==", line});
                    pos += 2;
                } else {
                    tokens.push_back({TOK_EQ, "=", line});
                    pos++;
                }
                continue;
            }

            if (c == '!') {
                if (pos + 1 < source.length() && source[pos + 1] == '=') {
                    tokens.push_back({TOK_NEQ, "!=", line});
                    pos += 2;
                    continue;
                }
            }

            cerr << "Unknown character: " << c << " at line " << line << endl;
            pos++;
        }

        tokens.push_back({TOK_EOF, "", line});
        return tokens;
    }

private:
    Token readString() {
        pos++; // skip opening quote
        string value;
        while (pos < source.length() && source[pos] != '"') {
            value += source[pos++];
        }
        pos++; // skip closing quote
        return {TOK_STRING, value, line};
    }

    Token readNumber() {
        string value;
        while (pos < source.length() && (isdigit(source[pos]) || source[pos] == '.')) {
            value += source[pos++];
        }
        return {TOK_NUMBER, value, line};
    }

    Token readIdentifier() {
        string value;
        while (pos < source.length() && (isalnum(source[pos]) || source[pos] == '_')) {
            value += source[pos++];
        }

        // Check for keywords
        if (value == "let") return {TOK_LET, value, line};
        if (value == "print") return {TOK_PRINT, value, line};
        if (value == "input") return {TOK_INPUT, value, line};
        if (value == "input_num") return {TOK_INPUT_NUM, value, line};
        if (value == "when") return {TOK_WHEN, value, line};
        if (value == "otherwise") return {TOK_OTHERWISE, value, line};
        if (value == "repeat") return {TOK_REPEAT, value, line};
        if (value == "times") return {TOK_TIMES, value, line};
        if (value == "loop") return {TOK_LOOP, value, line};
        if (value == "while") return {TOK_WHILE, value, line};
        if (value == "from") return {TOK_FROM, value, line};
        if (value == "to") return {TOK_TO, value, line};
        if (value == "label") return {TOK_LABEL, value, line};
        if (value == "goto") return {TOK_GOTO, value, line};
        if (value == "random") return {TOK_RANDOM, value, line};
        if (value == "sqrt") return {TOK_SQRT, value, line};
        if (value == "pow") return {TOK_POW, value, line};
        if (value == "abs") return {TOK_ABS, value, line};
        if (value == "floor") return {TOK_FLOOR, value, line};
        if (value == "ceil") return {TOK_CEIL, value, line};
        if (value == "call") return {TOK_CALL, value, line};
        if (value == "define") return {TOK_DEFINE, value, line};

        return {TOK_IDENT, value, line};
    }
};

// AST Node types
enum NodeType {
    NODE_PROGRAM, NODE_LET, NODE_PRINT, NODE_INPUT, NODE_INPUT_NUM, NODE_WHEN, NODE_REPEAT,
    NODE_LOOP_WHILE, NODE_LOOP_FOR, NODE_LABEL, NODE_GOTO, NODE_BLOCK,
    NODE_BINOP, NODE_UNARY, NODE_NUMBER, NODE_STRING, NODE_IDENT, NODE_CALL
};

struct ASTNode {
    NodeType type;
    string value;
    vector<shared_ptr<ASTNode>> children;
};

// Parser
class Parser {
    vector<Token> tokens;
    size_t pos;

public:
    Parser(const vector<Token>& toks) : tokens(toks), pos(0) {}

    shared_ptr<ASTNode> parse() {
        auto program = make_shared<ASTNode>();
        program->type = NODE_PROGRAM;

        while (current().type != TOK_EOF) {
            skipNewlines();
            if (current().type == TOK_EOF) break;
            program->children.push_back(parseStatement());
        }

        return program;
    }

private:
    Token current() { return tokens[pos]; }
    Token peek(int offset = 1) { return tokens[min(pos + offset, tokens.size() - 1)]; }
    void advance() { pos++; }
    void skipNewlines() { while (current().type == TOK_NEWLINE) advance(); }

    shared_ptr<ASTNode> parseStatement() {
        skipNewlines();

        if (current().type == TOK_LET) return parseLet();
        if (current().type == TOK_PRINT) return parsePrint();
        if (current().type == TOK_WHEN) return parseWhen();
        if (current().type == TOK_REPEAT) return parseRepeat();
        if (current().type == TOK_LOOP) return parseLoop();
        if (current().type == TOK_LABEL) return parseLabel();
        if (current().type == TOK_GOTO) return parseGoto();

        cerr << "Unexpected token: " << current().value << " at line " << current().line << endl;
        advance();
        return nullptr;
    }

    shared_ptr<ASTNode> parseLet() {
        auto node = make_shared<ASTNode>();
        node->type = NODE_LET;
        advance(); // skip 'let'

        node->value = current().value; // variable name
        advance();

        if (current().type != TOK_EQ) {
            cerr << "Expected '=' after variable name" << endl;
            return node;
        }
        advance();

        node->children.push_back(parseExpression());
        skipNewlines();
        return node;
    }

    shared_ptr<ASTNode> parsePrint() {
        auto node = make_shared<ASTNode>();
        node->type = NODE_PRINT;
        advance(); // skip 'print'

        node->children.push_back(parseExpression());
        skipNewlines();
        return node;
    }

    shared_ptr<ASTNode> parseWhen() {
        auto node = make_shared<ASTNode>();
        node->type = NODE_WHEN;
        advance(); // skip 'when'

        node->children.push_back(parseExpression()); // condition
        skipNewlines();

        if (current().type != TOK_ARROW_RIGHT) {
            cerr << "Expected '->' after condition" << endl;
            return node;
        }
        advance();
        skipNewlines();

        node->children.push_back(parseBlock()); // then block

        skipNewlines();
        if (current().type == TOK_OTHERWISE) {
            advance();
            skipNewlines();
            if (current().type == TOK_ARROW_RIGHT) {
                advance();
                skipNewlines();
                node->children.push_back(parseBlock()); // else block
            }
        }

        return node;
    }

    shared_ptr<ASTNode> parseRepeat() {
        auto node = make_shared<ASTNode>();
        node->type = NODE_REPEAT;
        advance(); // skip 'repeat'

        node->children.push_back(parseExpression()); // count

        if (current().type == TOK_TIMES) advance();
        skipNewlines();

        if (current().type != TOK_ARROW_RIGHT) {
            cerr << "Expected '->' after repeat count" << endl;
            return node;
        }
        advance();
        skipNewlines();

        node->children.push_back(parseBlock());
        return node;
    }

    shared_ptr<ASTNode> parseLoop() {
        advance(); // skip 'loop'

        if (current().type == TOK_WHILE) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_LOOP_WHILE;
            advance();

            node->children.push_back(parseExpression()); // condition
            skipNewlines();

            if (current().type != TOK_ARROW_RIGHT) {
                cerr << "Expected '->' after while condition" << endl;
                return node;
            }
            advance();
            skipNewlines();

            node->children.push_back(parseBlock());
            return node;
        }

        if (current().type == TOK_FROM) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_LOOP_FOR;
            advance();

            node->value = current().value; // loop variable
            advance();

            if (current().type != TOK_EQ) {
                cerr << "Expected '=' in for loop" << endl;
                return node;
            }
            advance();

            node->children.push_back(parseExpression()); // start value

            if (current().type != TOK_TO) {
                cerr << "Expected 'to' in for loop" << endl;
                return node;
            }
            advance();

            node->children.push_back(parseExpression()); // end value
            skipNewlines();

            if (current().type != TOK_ARROW_RIGHT) {
                cerr << "Expected '->' after for loop range" << endl;
                return node;
            }
            advance();
            skipNewlines();

            node->children.push_back(parseBlock());
            return node;
        }

        cerr << "Expected 'while' or 'from' after 'loop'" << endl;
        return nullptr;
    }

    shared_ptr<ASTNode> parseLabel() {
        auto node = make_shared<ASTNode>();
        node->type = NODE_LABEL;
        advance(); // skip 'label'

        node->value = current().value;
        advance();
        skipNewlines();
        return node;
    }

    shared_ptr<ASTNode> parseGoto() {
        auto node = make_shared<ASTNode>();
        node->type = NODE_GOTO;
        advance(); // skip 'goto'

        node->value = current().value;
        advance();
        skipNewlines();
        return node;
    }

    shared_ptr<ASTNode> parseBlock() {
        auto block = make_shared<ASTNode>();
        block->type = NODE_BLOCK;

        while (current().type != TOK_ARROW_LEFT && current().type != TOK_EOF) {
            skipNewlines();
            if (current().type == TOK_ARROW_LEFT) break;
            auto stmt = parseStatement();
            if (stmt) block->children.push_back(stmt);
        }

        if (current().type == TOK_ARROW_LEFT) {
            advance();
            skipNewlines();
        }

        return block;
    }

    shared_ptr<ASTNode> parseExpression() {
        return parseComparison();
    }

    shared_ptr<ASTNode> parseComparison() {
        auto left = parseTerm();

        while (current().type == TOK_EQEQ || current().type == TOK_NEQ ||
               current().type == TOK_LT || current().type == TOK_GT ||
               current().type == TOK_LTE || current().type == TOK_GTE) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_BINOP;
            node->value = current().value;
            advance();

            node->children.push_back(left);
            node->children.push_back(parseTerm());
            left = node;
        }

        return left;
    }

    shared_ptr<ASTNode> parseTerm() {
        auto left = parseFactor();

        while (current().type == TOK_PLUS || current().type == TOK_MINUS) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_BINOP;
            node->value = current().value;
            advance();

            node->children.push_back(left);
            node->children.push_back(parseFactor());
            left = node;
        }

        return left;
    }

    shared_ptr<ASTNode> parseFactor() {
        auto left = parsePrimary();

        while (current().type == TOK_STAR || current().type == TOK_SLASH || current().type == TOK_PERCENT) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_BINOP;
            node->value = current().value;
            advance();

            node->children.push_back(left);
            node->children.push_back(parsePrimary());
            left = node;
        }

        return left;
    }

    shared_ptr<ASTNode> parsePrimary() {
        // Handle unary minus
        if (current().type == TOK_MINUS) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_UNARY;
            node->value = "-";
            advance();
            node->children.push_back(parsePrimary());
            return node;
        }

        if (current().type == TOK_NUMBER) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_NUMBER;
            node->value = current().value;
            advance();
            return node;
        }

        if (current().type == TOK_STRING) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_STRING;
            node->value = current().value;
            advance();
            return node;
        }

        if (current().type == TOK_IDENT) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_IDENT;
            node->value = current().value;
            advance();
            return node;
        }

        if (current().type == TOK_INPUT) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_INPUT;
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                if (current().type == TOK_STRING) {
                    node->children.push_back(parseExpression()); // prompt
                }
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_INPUT_NUM) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_INPUT_NUM;
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                if (current().type == TOK_STRING) {
                    node->children.push_back(parseExpression()); // prompt
                }
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_RANDOM) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_CALL;
            node->value = "random";
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                node->children.push_back(parseExpression()); // min
                if (current().type == TOK_COMMA) advance();
                node->children.push_back(parseExpression()); // max
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_SQRT) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_CALL;
            node->value = "sqrt";
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                node->children.push_back(parseExpression());
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_POW) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_CALL;
            node->value = "pow";
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                node->children.push_back(parseExpression()); // base
                if (current().type == TOK_COMMA) advance();
                node->children.push_back(parseExpression()); // exponent
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_ABS) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_CALL;
            node->value = "abs";
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                node->children.push_back(parseExpression());
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_FLOOR) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_CALL;
            node->value = "floor";
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                node->children.push_back(parseExpression());
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_CEIL) {
            auto node = make_shared<ASTNode>();
            node->type = NODE_CALL;
            node->value = "ceil";
            advance();

            if (current().type == TOK_LPAREN) {
                advance();
                node->children.push_back(parseExpression());
                if (current().type == TOK_RPAREN) advance();
            }
            return node;
        }

        if (current().type == TOK_LPAREN) {
            advance();
            auto expr = parseExpression();
            if (current().type == TOK_RPAREN) advance();
            return expr;
        }

        cerr << "Unexpected token in expression: " << current().value << endl;
        advance();
        return make_shared<ASTNode>();
    }
};

// Value type for variables
struct Value {
    bool is_string;
    double num_value;
    string str_value;
    
    Value() : is_string(false), num_value(0) {}
    Value(double n) : is_string(false), num_value(n) {}
    Value(string s) : is_string(true), str_value(s), num_value(0) {}
};

// Interpreter
class Interpreter {
    map<string, Value> variables;
    map<string, size_t> labels;
    shared_ptr<ASTNode> program;
    bool gotoFlag;
    string gotoTarget;

public:
    Interpreter() : gotoFlag(false) {
        srand(time(0));
    }

    void run(shared_ptr<ASTNode> prog) {
        program = prog;
        // First pass: collect labels
        collectLabels(program);
        // Second pass: execute
        execute(program);
    }

private:
    void collectLabels(shared_ptr<ASTNode> node, size_t idx = 0) {
        if (!node) return;
        if (node->type == NODE_PROGRAM) {
            for (size_t i = 0; i < node->children.size(); i++) {
                if (node->children[i]->type == NODE_LABEL) {
                    labels[node->children[i]->value] = i;
                }
            }
        }
    }

    void execute(shared_ptr<ASTNode> node) {
        if (!node) return;

        if (node->type == NODE_PROGRAM) {
            for (size_t i = 0; i < node->children.size(); i++) {
                execute(node->children[i]);
                
                if (gotoFlag) {
                    if (labels.find(gotoTarget) != labels.end()) {
                        i = labels[gotoTarget] - 1; // -1 because loop will increment
                        gotoFlag = false;
                    } else {
                        cerr << "Label not found: " << gotoTarget << endl;
                        gotoFlag = false;
                    }
                }
            }
        }
        else if (node->type == NODE_LET) {
            Value val = evalValue(node->children[0]);
            variables[node->value] = val;
        }
        else if (node->type == NODE_PRINT) {
            Value val = evalValue(node->children[0]);
            if (val.is_string) {
                cout << val.str_value << endl;
            } else {
                cout << val.num_value << endl;
            }
        }
        else if (node->type == NODE_WHEN) {
            Value cond = evalValue(node->children[0]);
            double condNum = cond.is_string ? (cond.str_value.empty() ? 0 : 1) : cond.num_value;
            if (condNum != 0) {
                execute(node->children[1]); // then block
            } else if (node->children.size() > 2) {
                execute(node->children[2]); // else block
            }
        }
        else if (node->type == NODE_REPEAT) {
            Value countVal = evalValue(node->children[0]);
            int count = (int)countVal.num_value;
            for (int i = 0; i < count; i++) {
                execute(node->children[1]);
                if (gotoFlag) return; // Return to allow goto to propagate
            }
        }
        else if (node->type == NODE_LOOP_WHILE) {
            Value condVal = evalValue(node->children[0]);
            while (condVal.num_value != 0) {
                execute(node->children[1]);
                if (gotoFlag) return; // Return to allow goto to propagate
                condVal = evalValue(node->children[0]);
            }
        }
        else if (node->type == NODE_LOOP_FOR) {
            Value startVal = evalValue(node->children[0]);
            Value endVal = evalValue(node->children[1]);
            double start = startVal.num_value;
            double end = endVal.num_value;
            for (double i = start; i <= end; i++) {
                variables[node->value] = Value(i);
                execute(node->children[2]);
                if (gotoFlag) return; // Return to allow goto to propagate
            }
        }
        else if (node->type == NODE_GOTO) {
            gotoTarget = node->value;
            gotoFlag = true;
        }
        else if (node->type == NODE_BLOCK) {
            for (auto& child : node->children) {
                execute(child);
                if (gotoFlag) return; // Return to allow goto to propagate
            }
        }
    }

    Value evalValue(shared_ptr<ASTNode> node) {
        if (!node) return Value(0.0);

        if (node->type == NODE_NUMBER) {
            return Value(stod(node->value));
        }
        if (node->type == NODE_STRING) {
            return Value(node->value);
        }
        if (node->type == NODE_IDENT) {
            if (variables.find(node->value) != variables.end()) {
                return variables[node->value];
            }
            cerr << "Undefined variable: " << node->value << endl;
            return Value(0.0);
        }
        if (node->type == NODE_INPUT) {
            if (node->children.size() > 0 && node->children[0]->type == NODE_STRING) {
                cout << node->children[0]->value;
            }
            string input;
            getline(cin, input);
            return Value(input); // Return as string
        }
        if (node->type == NODE_INPUT_NUM) {
            if (node->children.size() > 0 && node->children[0]->type == NODE_STRING) {
                cout << node->children[0]->value;
            }
            string input;
            getline(cin, input);
            try {
                return Value(stod(input));
            } catch (...) {
                cerr << "Invalid input - please enter a number" << endl;
                return Value(0.0);
            }
        }
        if (node->type == NODE_CALL && node->value == "random") {
            Value minVal = evalValue(node->children[0]);
            Value maxVal = evalValue(node->children[1]);
            int min = (int)minVal.num_value;
            int max = (int)maxVal.num_value;
            return Value((double)(min + (rand() % (max - min + 1))));
        }
        if (node->type == NODE_CALL && node->value == "sqrt") {
            Value val = evalValue(node->children[0]);
            if (val.is_string) {
                cerr << "sqrt() requires a number, not a string" << endl;
                return Value(0.0);
            }
            return Value(sqrt(val.num_value));
        }
        if (node->type == NODE_CALL && node->value == "pow") {
            Value base = evalValue(node->children[0]);
            Value exp = evalValue(node->children[1]);
            if (base.is_string || exp.is_string) {
                cerr << "pow() requires numbers, not strings" << endl;
                return Value(0.0);
            }
            return Value(pow(base.num_value, exp.num_value));
        }
        if (node->type == NODE_CALL && node->value == "abs") {
            Value val = evalValue(node->children[0]);
            if (val.is_string) {
                cerr << "abs() requires a number, not a string" << endl;
                return Value(0.0);
            }
            return Value(fabs(val.num_value));
        }
        if (node->type == NODE_CALL && node->value == "floor") {
            Value val = evalValue(node->children[0]);
            if (val.is_string) {
                cerr << "floor() requires a number, not a string" << endl;
                return Value(0.0);
            }
            return Value(floor(val.num_value));
        }
        if (node->type == NODE_CALL && node->value == "ceil") {
            Value val = evalValue(node->children[0]);
            if (val.is_string) {
                cerr << "ceil() requires a number, not a string" << endl;
                return Value(0.0);
            }
            return Value(ceil(val.num_value));
        }
        if (node->type == NODE_UNARY) {
            Value val = evalValue(node->children[0]);
            if (val.is_string) {
                cerr << "Unary operator requires a number, not a string" << endl;
                return Value(0.0);
            }
            if (node->value == "-") {
                return Value(-val.num_value);
            }
            return Value(0.0);
        }
        if (node->type == NODE_BINOP) {
            Value left = evalValue(node->children[0]);
            Value right = evalValue(node->children[1]);

            // String concatenation
            if (node->value == "+" && (left.is_string || right.is_string)) {
                string leftStr = left.is_string ? left.str_value : to_string((int)left.num_value);
                string rightStr = right.is_string ? right.str_value : to_string((int)right.num_value);
                return Value(leftStr + rightStr);
            }

            // String comparison
            if (left.is_string && right.is_string) {
                if (node->value == "==") return Value(left.str_value == right.str_value ? 1.0 : 0.0);
                if (node->value == "!=") return Value(left.str_value != right.str_value ? 1.0 : 0.0);
                cerr << "Operator " << node->value << " not supported for strings" << endl;
                return Value(0.0);
            }

            // Numeric operations
            if (!left.is_string && !right.is_string) {
                if (node->value == "+") return Value(left.num_value + right.num_value);
                if (node->value == "-") return Value(left.num_value - right.num_value);
                if (node->value == "*") return Value(left.num_value * right.num_value);
                if (node->value == "/") return Value(left.num_value / right.num_value);
                if (node->value == "%") return Value((double)((int)left.num_value % (int)right.num_value));
                if (node->value == "==") return Value(left.num_value == right.num_value ? 1.0 : 0.0);
                if (node->value == "!=") return Value(left.num_value != right.num_value ? 1.0 : 0.0);
                if (node->value == "<") return Value(left.num_value < right.num_value ? 1.0 : 0.0);
                if (node->value == ">") return Value(left.num_value > right.num_value ? 1.0 : 0.0);
                if (node->value == "<=") return Value(left.num_value <= right.num_value ? 1.0 : 0.0);
                if (node->value == ">=") return Value(left.num_value >= right.num_value ? 1.0 : 0.0);
            }

            cerr << "Type mismatch in operation" << endl;
            return Value(0.0);
        }

        return Value(0.0);
    }

    double eval(shared_ptr<ASTNode> node) {
        Value val = evalValue(node);
        return val.num_value;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: flow <filename.flow>" << endl;
        return 1;
    }

    // Read file
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string source = buffer.str();

    // Tokenize
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();

    // Parse
    Parser parser(tokens);
    auto ast = parser.parse();

    // Execute
    Interpreter interpreter;
    interpreter.run(ast);

    return 0;
}
