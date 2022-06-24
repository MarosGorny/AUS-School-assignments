#include "matrix_test.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"
#include "../../structures/_logger/file_log_consumer.h"
#include <string>

namespace tests
{
	tests::MatrixTestInterface::MatrixTestInterface() :
		SimpleTest("Interface")
	{
	}

	void tests::MatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
	}

	structures::Matrix<int>* CoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestOverall::CoherentMatrixTestOverall() :
		ComplexTest("CoherentMatrix")
	{
		addTest(new CoherentMatrixTestInterface());
		addTest(new MatrixCohTestFunctions());
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new MatrixIncohTestFunctions());
	}

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
		addTest(new MatrixScenar());
		addTest(new MatrixUloha3()); 
		
	}
	MatrixCohTestFunctions::MatrixCohTestFunctions()
		:SimpleTest("Functions")
	{
	}
	void MatrixCohTestFunctions::test()
	{
		this->logInfo("Start of test MatrixCohTestFunctions");

		this->logInfo("Creating pointer to a CohMatrix:c of size 3,4");
		structures::CoherentMatrix<int>* c = new structures::CoherentMatrix<int>(3, 4);

		this->logInfo("Size of c = " + std::to_string(c->size()));

		this->logInfo("Checking inicialization");
		for (int i = 0; i < c->getRowCount(); i++)
		{
			for (int j = 0; j < c->getColumnCount(); j++) {
				this->assertTrue(c->at(i, j) == 0, 
								"c[" + 
								std::to_string(i)  + "," + 
								std::to_string(j) + "] == 0");
			}
		}

		this->logInfo("Setting values of c to values 0-11");
		for (int i = 0; i < c->getRowCount(); i++)
		{
			for (int j = 0; j < c->getColumnCount(); j++) {
				c->at(i, j) = static_cast<int>((i * c->getColumnCount()) + j);
			}
		}

		this->logInfo("Checking values");
		for (int i = 0; i < c->getRowCount(); i++)
		{
			for (int j = 0; j < c->getColumnCount(); j++) {
				this->assertTrue(c->at(i, j) == (i * c->getColumnCount() + j), 
					"c[" +
					std::to_string(i) + "," +
					std::to_string(j) + "] == " +
					std::to_string((i * c->getColumnCount()) + j));
			}
		}

		this->logInfo("Creating pointer to a CohMatrix:cCopy from the first Matrix - Copy Constructor");
		structures::CoherentMatrix<int>* cCopy = new structures::CoherentMatrix<int>(*c);

		//Skontrolovat, ci je kopia rovnaka ako original metodou equals.
		this->assertTrue(cCopy->equals(*c), "cCopy->equals(*c)");

		//Nastavit prvy byte kopie na hodnotu 10
		this->logInfo("cCopy->at(0,0) = 10");
		cCopy->at(0,0) = 10;


		//Skontrolovat, ci je kopia rozdielna od originalu
		this->assertFalse(cCopy->equals(*c), "cCopy->equals(*c)");

		//Priradit kopu vektora do povodneho vektora metodou assign
		this->logInfo("c->assign(*cCopy)");
		c->assign(*cCopy);

		//Skontrolovat, ci je kopia rovnaka ako povodny vektor
		this->assertTrue(cCopy->equals(*c), "cCopy->equals(*c)");

		delete c;
		c = nullptr;

		delete cCopy;
		cCopy = nullptr;

		this->logInfo("End of test MatrixCohTestFunctions");

	}
	MatrixIncohTestFunctions::MatrixIncohTestFunctions()
		:SimpleTest("Functions")
	{
	}
	void MatrixIncohTestFunctions::test()
	{
		this->logInfo("Start of test MatrixIncohTestFunctions");

		this->logInfo("Creating pointer to a InCohMatrix:c of size 3,4");
		structures::IncoherentMatrix<int>* c = new structures::IncoherentMatrix<int>(3, 4);

		this->logInfo("Checking inicialization");
		for (int i = 0; i < c->getRowCount(); i++)
		{
			for (int j = 0; j < c->getColumnCount(); j++) {
				this->assertTrue(c->at(i, j) == 0,
					"c[" +
					std::to_string(i) + "," +
					std::to_string(j) + "] == 0");
			}
		}

		this->logInfo("Setting values of c to values 0-11");
		for (int i = 0; i < c->getRowCount(); i++)
		{
			for (int j = 0; j < c->getColumnCount(); j++) {
				c->at(i, j) = static_cast<int>((i * c->getColumnCount()) + j);
			}
		}

		this->logInfo("Checking values");
		for (int i = 0; i < c->getRowCount(); i++)
		{
			for (int j = 0; j < c->getColumnCount(); j++) {
				this->assertTrue(c->at(i, j) == (i * c->getColumnCount() + j),
					"c[" +
					std::to_string(i) + "," +
					std::to_string(j) + "] == " +
					std::to_string((i * c->getColumnCount()) + j));
			}
		}
		
		this->logInfo("Creating pointer to a InCohMatrix:cCopy from the first Matrix - Copy Constructor");
		structures::IncoherentMatrix<int>* cCopy = new structures::IncoherentMatrix<int>(*c);

		
		//Skontrolovat, ci je kopia rovnaka ako original metodou equals.
		this->assertTrue(cCopy->equals(*c), "cCopy->equals(*c)");

		//Nastavit prvy byte kopie na hodnotu 10
		this->logInfo("cCopy->at(0,0) = 10");
		cCopy->at(0, 0) = 10;

		
		//Skontrolovat, ci je kopia rozdielna od originalu
		this->assertFalse(cCopy->equals(*c), "cCopy->equals(*c)");
		
		//Priradit kopu vektora do povodneho vektora metodou assign
		this->logInfo("c->assign(*cCopy)");
		c->assign(*cCopy);

		//Skontrolovat, ci je kopia rovnaka ako povodny vektor
		this->assertTrue(cCopy->equals(*c), "cCopy->equals(*c)");


		delete c;
		c = nullptr;

		delete cCopy;
		cCopy = nullptr;

		this->logInfo("End of test MatrixIncohTestFunctions");
	}




	MatrixScenar::MatrixScenar()
		:SimpleTest("uloha2[A,B,C,D]")
	{
	}

	template<typename T>
	inline void MatrixScenar::getRowColummnTime(structures::FileLogConsumer* fileLogger,structures::Matrix<T>* matica,std::string method, int pocetRiadkov, int pocetStlpcov) {
		if (method == "getColumnCount") {
			this->startStopwatch();
			matica->getColumnCount();
			this->stopStopwatch();
		}
		else {
			this->startStopwatch();
			matica->getRowCount();
			this->stopStopwatch();
		}
		
		tests::DurationType duration = this->getElapsedTime();
		//structures::Logger::getInstance().logDuration(pocetRiadkov, duration, method);
		fileLogger->matrixDuration(pocetRiadkov, pocetStlpcov, duration, method);
	}

	template <typename T>
	inline void MatrixScenar::getAtCountTime(structures::FileLogConsumer* fileLogger,structures::Matrix<T>* matica,int pocetRiadkov,int pocetStlpcov) {
		int riadok = rand() % pocetRiadkov;
		int stlpec = rand() % pocetStlpcov;
		this->startStopwatch();
		matica->at(riadok, stlpec);// = riadok;
		this->stopStopwatch();
		tests::DurationType duration = this->getElapsedTime();
		//structures::Logger::getInstance().logDuration(pocetRiadkov,  duration, "at");
		fileLogger->matrixDuration(pocetRiadkov, pocetStlpcov, duration, "at");

	}


	template<typename T>
	void MatrixScenar::uloha2(structures::Matrix<T>* matica,
					int ratioGetRow, int ratioGetColumn, int ratioAt,
					std::string nazov) {
		std::string nazovCSV = nazov + ".csv";

		structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);
		//structures::Logger::getInstance().registerConsumer(fileLogConsumer);
		fileLogConsumer->matrixTitle();
		srand(static_cast<unsigned int>(time(NULL)));

		const int REPEATS = 1000000;

		
		const int rowRatioPercent = (REPEATS / 100) * ratioGetRow;
		const int columnRatioPercent = (REPEATS / 100) * ratioGetColumn;
		const int atRatioPercent = (REPEATS / 100) * ratioAt;

		int counterRow = 0;
		int counterColumn = 0;
		int counterAt = 0;

		int pocetRiadkov = static_cast<int>(matica->getRowCount());
		int pocetStlpcov = static_cast<int>(matica->getColumnCount());

		for (int j = 0; j < REPEATS; j++)
		{
			int randomRatio = rand() % 100;
			if (randomRatio < ratioGetRow && counterRow < rowRatioPercent) {
				//getRow

				getRowColummnTime(fileLogConsumer,matica,"getRowCount",pocetRiadkov,pocetStlpcov);
				counterRow++;
			}
			else if (randomRatio < (ratioGetRow + ratioGetColumn) && counterColumn < columnRatioPercent) {
				//getColumn
				getRowColummnTime(fileLogConsumer,matica, "getColumnCount", pocetRiadkov, pocetStlpcov);
				counterColumn++;

			}
			else if (randomRatio < 100 && counterAt < atRatioPercent) {
				//at

				getAtCountTime(fileLogConsumer,matica,pocetRiadkov,pocetStlpcov);
				counterAt++;

			} 
			else if (counterRow < rowRatioPercent) {
				//getRow
				getRowColummnTime(fileLogConsumer,matica, "getRowCount", pocetRiadkov, pocetStlpcov);
				counterRow++;
			}
			else if (counterColumn < columnRatioPercent) {
				//getColumn
				getRowColummnTime(fileLogConsumer,matica, "getColumnCount", pocetRiadkov, pocetStlpcov);
				counterColumn++;
			}
			else {
				//at
				getAtCountTime(fileLogConsumer,matica, pocetRiadkov, pocetStlpcov);
				counterAt++;
			}
		}

		delete fileLogConsumer;
		fileLogConsumer = nullptr;

	}

	void MatrixScenar::test()
	{

		structures::IncoherentMatrix<int>* inCohA = new structures::IncoherentMatrix<int>(10, 50);
		uloha2(inCohA, 5,5,90,"IncoherentMatrix_A");
		delete inCohA;
		inCohA = nullptr;


		
		structures::CoherentMatrix<int>* cohA = new structures::CoherentMatrix<int>(10, 50);
		uloha2(cohA, 5, 5, 90,"CoherentMatrix_A");
		delete cohA;
		cohA = nullptr;
		
		structures::IncoherentMatrix<int>* inCohB = new structures::IncoherentMatrix<int>(2000, 500);
		uloha2(inCohB, 5, 5, 90, "IncoherentMatrix_B");
		delete inCohB;
		inCohB = nullptr;

		structures::CoherentMatrix<int>* cohB = new structures::CoherentMatrix<int>(2000, 500);
		uloha2(cohB, 5, 5, 90,"CoherentMatrix_B");
		delete cohB;
		cohB = nullptr;

		structures::IncoherentMatrix<int>* inCohC = new structures::IncoherentMatrix<int>(50, 10);
		uloha2(inCohC, 10, 30, 60,"IncoherentMatrix_C");
		delete inCohC;
		inCohC = nullptr;

		structures::CoherentMatrix<int>* cohC = new structures::CoherentMatrix<int>(50, 10);
		uloha2(cohC, 10, 30, 60,"CoherentMatrix_C");
		delete cohC;
		cohC = nullptr;

		structures::IncoherentMatrix<int>* inCohD = new structures::IncoherentMatrix<int>(500, 2000);
		uloha2(inCohD, 10, 30, 60, "IncoherentMatrix_D");
		delete inCohD;
		inCohD = nullptr;

		structures::CoherentMatrix<int>* cohD = new structures::CoherentMatrix<int>(500, 2000);
		uloha2(cohD, 10, 30, 60,"CoherentMatrix_D");
		delete cohD;
		cohD = nullptr;
		
	}

	MatrixUloha3::MatrixUloha3()
		:SimpleTest("uloha3 - at(),assign()")
	{
	}

	template <typename T>
	void MatrixUloha3::otestujMetodu(structures::Matrix<T>& matica, std::string metoda, std::string typMatice) {
		//random seed
		srand(static_cast<unsigned int>(time(NULL)));

		std::string csvName = typMatice + metoda + ".csv";

		structures::FileLogConsumer* fileLogger = new structures::FileLogConsumer(csvName);
		

		const int POCET_RIADKOV_STLPCOV = 3000;

		structures::CoherentMatrix<int>* typeMatrixCoh = dynamic_cast<structures::CoherentMatrix<int>*>(&matica);

		//Vypisanie poctu stlpcov pre matrix
		
		fileLogger->csvCELL("");
		for (int m = 1; m <= (POCET_RIADKOV_STLPCOV + 1); m += 100)
		{
			if (m >= (POCET_RIADKOV_STLPCOV - 1))
				fileLogger->csvCELL(std::to_string(m), false, true);
			else
				fileLogger->csvCELL(std::to_string(m));
		}
		

		for (int n = 1; n <= (POCET_RIADKOV_STLPCOV + 1); n += 100)
		{
			//Vypisanie riadku na zaciatku pre matrix
			
			fileLogger->csvCELL(std::to_string(n));
			
			for (int m = 1; m <= (POCET_RIADKOV_STLPCOV + 1); m += 100)
			{
				tests::DurationType duration{};
				//Vykonanie metody at aspon 100 krat
				const int OPAKOVANIE_METODY = 100;
				if (metoda == "at()" && (typeMatrixCoh == nullptr)) {
					structures::IncoherentMatrix<int>* inCohMatrix = new structures::IncoherentMatrix<int>(n, m);
		
					for (int i = 0; i < OPAKOVANIE_METODY; i++)
					{

						int riadok = rand() % inCohMatrix->getRowCount();
						int stlpec = rand() % inCohMatrix->getColumnCount();

						this->startStopwatch();
						inCohMatrix->at(riadok, stlpec);
						this->stopStopwatch();
						duration += this->getElapsedTime();
					}
					delete inCohMatrix;
					inCohMatrix = nullptr;
				}
				else if(metoda == "at()" && (typeMatrixCoh != nullptr)){
					structures::CoherentMatrix<int>* CohMatrix = new structures::CoherentMatrix<int>(n, m);
					for (int i = 0; i < OPAKOVANIE_METODY; i++)
					{

						int riadok = rand() % CohMatrix->getRowCount();
						int stlpec = rand() % CohMatrix->getColumnCount();

						this->startStopwatch();
						CohMatrix->at(riadok, stlpec);
						this->stopStopwatch();
						duration += this->getElapsedTime();
					}
					delete CohMatrix;
					CohMatrix = nullptr;
				}
				else {

					if (typeMatrixCoh == nullptr) {
						structures::IncoherentMatrix<int>* matrixIncoh = new structures::IncoherentMatrix<int>(n, m);

						for (int i = 0; i < OPAKOVANIE_METODY; i++)
						{
							structures::IncoherentMatrix<int>* copyMatrix = new structures::IncoherentMatrix<int>(n, m);

							this->startStopwatch();
							matrixIncoh->assign(*copyMatrix);
							this->stopStopwatch();
							duration += this->getElapsedTime();

							delete copyMatrix;
							copyMatrix = nullptr;
						}
						delete matrixIncoh;
						matrixIncoh = nullptr;

					} else {
						structures::CoherentMatrix<int>* matrixCoh = new structures::CoherentMatrix<int>(n, m);
						for (int i = 0; i < OPAKOVANIE_METODY; i++)
						{
							structures::CoherentMatrix<int>* copyMatrix = new structures::CoherentMatrix<int>(n, m);

							this->startStopwatch();
							matrixCoh->assign(*copyMatrix);
							this->stopStopwatch();
							
							duration += this->getElapsedTime();

							delete copyMatrix;
							copyMatrix = nullptr;
						}
						delete matrixCoh;
						matrixCoh = nullptr;
					}
					
				}

				auto longLongTime = duration.count() / OPAKOVANIE_METODY;

				//Vypisanie casu, a ak je na konci, tak na novy riadok. Pre matrix
				
				if (m >= POCET_RIADKOV_STLPCOV - 1)
					fileLogger->csvCELL(longLongTime, false, true);
				else
					fileLogger->csvCELL(longLongTime);
				

				//Vypisanie casu do vektora pod seba so size a time
				/*
				fileLogger->csvCELL(std::to_string(m * n));
				fileLogger->csvCELL(longLongTime, false, true);
				*/

			}
		}

		delete fileLogger;
		fileLogger = nullptr;
	}


	void MatrixUloha3::test() {
		structures::IncoherentMatrix<int> inCoh = structures::IncoherentMatrix<int>(1, 1);
		structures::CoherentMatrix<int> Coh = structures::CoherentMatrix<int>(1, 1);

		/*
		otestujMetodu(inCoh, "at()", "IncoherentMatrix");
		otestujMetodu(inCoh, "assign()", "IncoherentMatrix");
		otestujMetodu(Coh, "at()", "CoherentMatrix");
		otestujMetodu(Coh, "assign()", "CoherentMatrix");
		*/
		
		otestujMetodu(inCoh, "at()", "IncoherentMatrixVector_");
		otestujMetodu(inCoh, "assign()", "IncoherentMatrixVector_");
		otestujMetodu(Coh, "at()", "CoherentMatrixVector_");
		otestujMetodu(Coh, "assign()", "CoherentMatrixVector_");
		
	}

}
