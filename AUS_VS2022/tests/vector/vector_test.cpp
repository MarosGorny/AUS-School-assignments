#include "vector_test.h"
#include "../../structures/vector/vector.h"

namespace tests
{
// VectorTestInterface:

    VectorTestInterface::VectorTestInterface() :
        SimpleTest("Interface")
    { //nic viac netreba robit
    }

    void VectorTestInterface::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        vector->size();
        vector->assign(*vector);
        vector->equals(*vector);
        vector->at(0);
        vector->getBytePointer(0);
        structures::Vector::copy(*vector, 0, *vector, 0, 1);
        //zatial ML, pretoze copy neprebehne, takze to spadne a nevydeletuje sa vector
        delete vector;
        SimpleTest::logPass("Compiled.");
    }



// VectorTestOverall:

    VectorTestOverall::VectorTestOverall() :
        ComplexTest("Vector")
    {
        //doplnit vsetky simple testy
        this->addTest(new VectorTestInterface());
        this->addTest(new VectorTestAt());
        this->addTest(new VectorTestCopy());
        this->addTest(new VectorTimeTest());
    }

 //VectorTestAt:

    VectorTestAt::VectorTestAt()
        :SimpleTest("At")
    {   //Vsetko co treba v ramci konstruktora
    }
    void VectorTestAt::test()
    {   
        this->logInfo("Start of test VectorTestAt");
        //Vytvorit vektor s velkostou 10
        structures::Vector* v = new structures::Vector(10);
        //otestuj, ci ma pozadovnu velkost 
        //AssertTrue, pouzivam ci je tvrdenie pravdive, assertFalse, opak.
        this->assertTrue(v->size() == 10, "v->size() == 10");

        for (structures::byte i = 0; i < v->size(); i++) {
            v->at(i) = i;
            //Mozna strata z intu, treba static cast (pretypovanie prim, typov)
            //                     pouzivam ak vacsi chcem do mensieho
            //Bud structures::byte, alebo pretypovanie---->
            //    Pretypovanie na mensieho udajoveho typu, napr int->byte
            //    v->at(i) = static_cast<structures::byte>(i)
        }

        for (int i = 0; i < v->size(); i++) {
            //Aby to bolo korektne, cislo pretransforujem na string
            this->assertTrue(v->at(i) == i,"v->at(" + std::to_string(i) + ") ==" + std::to_string(i));
        }

        for (int i = 0; i < v->size(); i++) {
            this->assertTrue(*v->getBytePointer(i) == i, "*v->getBytePointer(" + std::to_string(i) + ") ==" + std::to_string(i));
        }
        delete v;
        v = nullptr;

        this->logInfo("End of test VectorTestAt");
    }
    //VectorTestCopy:
    VectorTestCopy::VectorTestCopy()
        :SimpleTest("Copy")
    {
    }

    void VectorTestCopy::test()
    {
        this->logInfo("Start of test VectorTestCopy");

        //Vytvorit vektor s velkostou 10
        this->logInfo("Creating pointer to a vector:v of size 10");
        structures::Vector* v = new structures::Vector(10);
        
        //nastavit byty na hodnoty 0 az 9
        this->logInfo("Setting bytes to values 0-9");
        for (int i = 0; i < v->size(); i++) {
            v->at(i) = static_cast<structures::byte>(i);
        }
        
        //vytvorit kopu vektora pomocou kopirovacieho konstruktora
        this->logInfo("Creating pointer to a vector:vCopy from the first Vector - Copy Constructor");
        structures::Vector* vCopy = new structures::Vector(*v);

        //Skontrolovat, ci je kopia rovnaka ako original metodou equals.
        this->assertTrue(vCopy->equals(*v), "vCopy->equals(*v)");

        //Nastavit prvy byte kopie na hodnotu 10
        this->logInfo("vCopy->at(0) = 10");
        vCopy->at(0) = 10;
        

        //Skontrolovat, ci je kopia rozdielna od originalu
        this->assertFalse(vCopy->equals(*v),"vCopy->equals(*v)" );

        //Priradit kopu vektora do povodneho vektora metodou assign
        this->logInfo("v->assign(*vCopy)");
        v->assign(*vCopy);

        //Skontrolovat, ci je kopia rovnaka ako povodny vektor

        this->assertTrue(vCopy->equals(*v),"vCopy->equals(*v)");

        delete v;
        v = nullptr;

        delete vCopy;
        vCopy = nullptr;
        
        this->logInfo("End of test VectorTestCopy");
    }


    VectorTimeTest::VectorTimeTest()
        :SimpleTest("Time")
    {
    }

    void VectorTimeTest::test()
    {
        const int velkost = 1000000;
        this->startStopwatch();
        structures::Vector* v = new structures::Vector(velkost);

        for (int i = 0; i < v->size(); i++) {
            v->at(i) = static_cast<structures::byte>(i % 255);
        }


        delete v;
        v = nullptr;
        this->stopStopwatch();
        tests::DurationType duration = this->getElapsedTime();
        this->logInfo("Time of the test is " + std::to_string(duration.count()) + " ms");
        
        structures::Logger::getInstance().logDuration(velkost, duration, "Scenar TimeTest");

    }


}