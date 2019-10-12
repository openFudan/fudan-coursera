/*
*/
#include "Foundation.H"
class istream;
class ostream;
class Token;
class ProgramNodeBuilder;
class ProgramNode;
class StatementNode;
class ExpressionNode;
class CodeGenerator;
class BytecodeStream;
/*
*/
class Scanner {
public:
    Scanner(istream&);
    virtual ~Scanner();

    virtual Token& Scan();
private:
    istream& _inputStream;
};
/*
*/
class Parser {
public:
    Parser();
    virtual ~Parser();

    virtual void Parse(Scanner&, ProgramNodeBuilder&);
};
/*
*/
class ProgramNodeBuilder {
public:
    ProgramNodeBuilder();
/*
*/
    virtual ProgramNode* NewVariable(
        char* variableName
    ) const;
/*
*/
    virtual ProgramNode* NewAssignment(
        ProgramNode* variable, ProgramNode* expression
    ) const;
/*
*/
    virtual ProgramNode* NewReturnStatement(
        ProgramNode* value
    ) const;
/*
*/
    virtual ProgramNode* NewCondition(
        ProgramNode* condition,
        ProgramNode* truePart, ProgramNode* falsePart
    ) const;
    // ...
/*
*/
    ProgramNode* GetRootNode();
private:
    ProgramNode* _node;
};
/*
*/
class ProgramNode {
public:
    // program node manipulation
    virtual void GetSourcePosition(int& line, int& index);
    // ...
/*
*/
    // child manipulation
    virtual void Add(ProgramNode*);
    virtual void Remove(ProgramNode*);
    // ...

    virtual void Traverse(CodeGenerator&);
protected:
    ProgramNode();
};
/*
*/
class CodeGenerator {
public:
    virtual void Visit(StatementNode*);
    virtual void Visit(ExpressionNode*);
    // ...
protected:
    CodeGenerator(BytecodeStream&);
protected:
    BytecodeStream& _output;
};
/*
*/
class ExpressionNode : public ProgramNode {
public:
    ExpressionNode();
    virtual void GetSourcePosition(int& line, int& index);
    virtual void Add(ProgramNode*);
    virtual void Remove(ProgramNode*);

    virtual void Traverse(CodeGenerator&);
protected:
    List<ProgramNode*>* _children;
};
/*
*/
void ExpressionNode::Traverse (CodeGenerator& cg) {
    cg.Visit(this);

    ListIterator<ProgramNode*> i(_children);

    for (i.First(); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Traverse(cg);
    }
}
/*
*/
class Compiler {
public:
    Compiler();

    virtual void Compile(istream&, BytecodeStream&);
};
/*
*/
class  RISCCodeGenerator : public CodeGenerator {
public:
    RISCCodeGenerator(BytecodeStream&);
    virtual void Visit(StatementNode*);
    virtual void Visit(ExpressionNode*);
    // ...
};
/*
*/
void Compiler::Compile (
    istream& input, BytecodeStream& output
) {
    Scanner scanner(input);
    ProgramNodeBuilder builder;
    Parser parser;

    parser.Parse(scanner, builder);

    RISCCodeGenerator generator(output);
    ProgramNode* parseTree = builder.GetRootNode();
    parseTree->Traverse(generator);
}
/*
*/
