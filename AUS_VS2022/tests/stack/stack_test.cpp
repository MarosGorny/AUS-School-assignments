#include "stack_test.h"
#include "../../structures/stack/implicit_stack.h"
#include "../../structures/stack/explicit_stack.h"

namespace tests
{
// StackTestInterface:

    StackTestInterface::StackTestInterface(std::string name) :
        SimpleTest(std::move(name))
    {
    }

    void StackTestInterface::test()
    {
        int x = 0;
        structures::Stack<int>* stack = this->makeStack();
        stack->size();
        stack->push(x);
        stack->peek();
        stack->pop();
        stack->clear();
        stack->assign(*stack);
        stack->equals(*stack);
        delete stack;
        this->logPass("Compiled.");
    }

// ImplicitStackTestInterface:

    ImplicitStackTestInterface::ImplicitStackTestInterface() :
        StackTestInterface("Interface")
    {
    }

    structures::Stack<int>* ImplicitStackTestInterface::makeStack()
    {
        return new structures::ImplicitStack<int>();
    }

// ExplicitStackTestInterface:

    ExplicitStackTestInterface::ExplicitStackTestInterface() :
        StackTestInterface("Interface")
    {
    }

    structures::Stack<int>* ExplicitStackTestInterface::makeStack()
    {
        return new structures::ExplicitStack<int>();
    }

// ImplicitStackTestOverall:

    ImplicitStackTestOverall::ImplicitStackTestOverall() :
        ComplexTest("ImplicitStack")
    {
        addTest(new ImplicitStackTestInterface());
    }

// ExplicitStackTestOverall:

    ExplicitStackTestOverall::ExplicitStackTestOverall() :
        ComplexTest("ExplicitStack")
    {
        addTest(new ExplicitStackTestInterface());
    }

// StackTestOverall:

    StackTestOverall::StackTestOverall() :
        ComplexTest("Stack")
    {
        addTest(new ImplicitStackTestOverall());
        addTest(new ExplicitStackTestOverall());
    }
}
