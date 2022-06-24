#include "queue_test.h"
#include "../../structures/queue/implicit_queue.h"
#include "../../structures/queue/explicit_queue.h"

namespace tests
{
// QueueTestInterface:

    QueueTestInterface::QueueTestInterface(std::string name) :
        SimpleTest(std::move(name))
    {
    }

    void QueueTestInterface::test()
    {
        int x = 0;
        structures::Queue<int>* queue = this->makeQueue();
        queue->size();
        queue->push(x);
        queue->peek();
        queue->pop();
        queue->clear();
        queue->assign(*queue);
        queue->equals(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

// ImplicitQueueTestInterface:

    ImplicitQueueTestInterface::ImplicitQueueTestInterface() :
        QueueTestInterface("Interface")
    {
    }

    structures::Queue<int>* ImplicitQueueTestInterface::makeQueue()
    {
        return new structures::ImplicitQueue<int>();
    }

// ExplicitQueueTestInterface:

    ExplicitQueueTestInterface::ExplicitQueueTestInterface() :
        QueueTestInterface("Interface")
    {
    }

    structures::Queue<int>* ExplicitQueueTestInterface::makeQueue()
    {
        return new structures::ExplicitQueue<int>();
    }

// ImplicitQueueTestOverall:

    ImplicitQueueTestOverall::ImplicitQueueTestOverall() :
        ComplexTest("ImplicitQueue")
    {
        addTest(new ImplicitQueueTestInterface());
    }

// ExplicitQueueTestOverall:

    ExplicitQueueTestOverall::ExplicitQueueTestOverall() :
        ComplexTest("ExplicitQueue")
    {
        addTest(new ExplicitQueueTestInterface());
    }

// QueueTestOverall:

    QueueTestOverall::QueueTestOverall() :
        ComplexTest("Queue")
    {
        addTest(new ImplicitQueueTestOverall());
        addTest(new ExplicitQueueTestOverall());
    }
}