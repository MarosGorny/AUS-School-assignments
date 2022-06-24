#pragma once

#include "../tests/test.h"
#include "../structures/_logger/logger.h"
#include <ostream>
#include <string>
#include <vector>

namespace gui
{
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(const std::vector<tests::Test*>& tests);

		System::Void LogMessage(structures::LogType type, System::String^ message);
		System::Void LogDuration(size_t size, tests::DurationType duration, const std::string& message);

	public:
		/// <summary>
		/// Dispose. Cleans managed resources.
		/// </summary>
		~MainForm();

		/// <summary>
		/// Finalize. Cleans unmanaged resources.
		/// </summary>
		!MainForm();

	private:
		System::ComponentModel::Container^ components;
		System::Windows::Forms::SplitContainer^ splitNorthSouth;
		System::Windows::Forms::Panel^ panel2;
		System::Windows::Forms::Panel^ panel1;
		System::Windows::Forms::SplitContainer^ splitWeastEast;
		System::Windows::Forms::TreeView^ treeTests;
		System::Windows::Forms::Button^ buttonRunTests;
		System::Windows::Forms::Panel^ panelTestHeader;
		System::Windows::Forms::Label^ labelTestsHeader;
		System::Windows::Forms::Panel^ panelTestsTree;
		System::Windows::Forms::Panel^ panelTestResults;
		System::Windows::Forms::Label^ labelTestResultsHeader;
		System::Windows::Forms::Panel^ panelLoggerHeader;
		System::Windows::Forms::Label^ labelLoggerHeader;
		System::Windows::Forms::ListView^ listViewTestLog;
		System::Windows::Forms::ColumnHeader^ columnTestMessage;
		System::Windows::Forms::ListView^ listViewGlobalLog;
		System::Windows::Forms::ColumnHeader^ columnGlobalLogMessage;
		System::Windows::Forms::ImageList^ testLogIconList_;
		System::Windows::Forms::ImageList^ globalLogIconList_;
		System::Windows::Forms::ColumnHeader^ columnGlobalLogTime;
		System::Windows::Forms::Button^ buttonLogToClipboard;
		System::Windows::Forms::Button^ buttonLogToFile;
		System::Windows::Forms::Button^ buttonLogClear;
		System::Windows::Forms::ColumnHeader^ columnGlobalLogType;
		System::Windows::Forms::Button^ buttonTestLogToClipboard;
		System::Windows::Forms::Button^ buttonTestLogToFile;
		System::Windows::Forms::Button^ buttonTestLogClear;

		System::Windows::Forms::ColumnHeader^ columnTestType;

	private:
		System::Void CreateTestTree();
		System::Void RegisterTests(const std::vector<tests::Test*>& tests);
		System::Void AddTest(tests::Test* test, System::Windows::Forms::TreeNodeCollection^ nodes);
		System::Void RunSelectedTests(System::Windows::Forms::TreeNodeCollection^ nodes);
		System::Void ColorizeTestTree(System::Windows::Forms::TreeNodeCollection^ nodes);
		System::Void ShowTestLogs(System::Windows::Forms::TreeNodeCollection^ nodes);
		System::Void AdjustTestLogColumns();
		System::Void ResetTestLog();
		System::Void ResetTests();
		System::Void RegisterTestLogIcon(tests::TestLogType type);
		System::Void RegisterGlobalLogIcon(structures::LogType type);
		System::Int32 TestLogTypeToIndex(tests::TestLogType type);
		System::Int32 GlobalLogTypeToIndex(structures::LogType type);
		System::String^ GlobalLogToString();
		System::String^ TestLogToString();
		System::Void SaveToFile(System::String^ str);
		System::Void SaveToClipboard(System::String^ str);

	private:
		std::vector<tests::TestLogType>* testLogIconOrder_;
		std::vector<structures::LogType>* globalLogIconOrder_;
		bool treeCheckInProgress_;
		bool isDisposed_;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->splitNorthSouth = (gcnew System::Windows::Forms::SplitContainer());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->splitWeastEast = (gcnew System::Windows::Forms::SplitContainer());
			this->panelTestsTree = (gcnew System::Windows::Forms::Panel());
			this->panelTestHeader = (gcnew System::Windows::Forms::Panel());
			this->labelTestsHeader = (gcnew System::Windows::Forms::Label());
			this->listViewTestLog = (gcnew System::Windows::Forms::ListView());
			this->columnTestType = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnTestMessage = (gcnew System::Windows::Forms::ColumnHeader());
			this->panelTestResults = (gcnew System::Windows::Forms::Panel());
			this->buttonTestLogToClipboard = (gcnew System::Windows::Forms::Button());
			this->buttonTestLogToFile = (gcnew System::Windows::Forms::Button());
			this->buttonTestLogClear = (gcnew System::Windows::Forms::Button());
			this->labelTestResultsHeader = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonRunTests = (gcnew System::Windows::Forms::Button());
			this->listViewGlobalLog = (gcnew System::Windows::Forms::ListView());
			this->columnGlobalLogTime = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnGlobalLogType = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnGlobalLogMessage = (gcnew System::Windows::Forms::ColumnHeader());
			this->panelLoggerHeader = (gcnew System::Windows::Forms::Panel());
			this->buttonLogToClipboard = (gcnew System::Windows::Forms::Button());
			this->buttonLogToFile = (gcnew System::Windows::Forms::Button());
			this->buttonLogClear = (gcnew System::Windows::Forms::Button());
			this->labelLoggerHeader = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitNorthSouth))->BeginInit();
			this->splitNorthSouth->Panel1->SuspendLayout();
			this->splitNorthSouth->Panel2->SuspendLayout();
			this->splitNorthSouth->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitWeastEast))->BeginInit();
			this->splitWeastEast->Panel1->SuspendLayout();
			this->splitWeastEast->Panel2->SuspendLayout();
			this->splitWeastEast->SuspendLayout();
			this->panelTestHeader->SuspendLayout();
			this->panelTestResults->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panelLoggerHeader->SuspendLayout();
			this->SuspendLayout();
			//
			// splitNorthSouth
			//
			this->splitNorthSouth->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			this->splitNorthSouth->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitNorthSouth->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitNorthSouth->Location = System::Drawing::Point(0, 0);
			this->splitNorthSouth->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->splitNorthSouth->Name = L"splitNorthSouth";
			this->splitNorthSouth->Orientation = System::Windows::Forms::Orientation::Horizontal;
			//
			// splitNorthSouth.Panel1
			//
			this->splitNorthSouth->Panel1->Controls->Add(this->panel2);
			this->splitNorthSouth->Panel1->Controls->Add(this->panel1);
			//
			// splitNorthSouth.Panel2
			//
			this->splitNorthSouth->Panel2->BackColor = System::Drawing::Color::White;
			this->splitNorthSouth->Panel2->Controls->Add(this->listViewGlobalLog);
			this->splitNorthSouth->Panel2->Controls->Add(this->panelLoggerHeader);
			this->splitNorthSouth->Size = System::Drawing::Size(1479, 794);
			this->splitNorthSouth->SplitterDistance = 651;
			this->splitNorthSouth->SplitterWidth = 5;
			this->splitNorthSouth->TabIndex = 0;
			//
			// panel2
			//
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->panel2->Controls->Add(this->splitWeastEast);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(0, 54);
			this->panel2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1479, 597);
			this->panel2->TabIndex = 1;
			//
			// splitWeastEast
			//
			this->splitWeastEast->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			this->splitWeastEast->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitWeastEast->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitWeastEast->Location = System::Drawing::Point(0, 0);
			this->splitWeastEast->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->splitWeastEast->Name = L"splitWeastEast";
			//
			// splitWeastEast.Panel1
			//
			this->splitWeastEast->Panel1->BackColor = System::Drawing::Color::White;
			this->splitWeastEast->Panel1->Controls->Add(this->panelTestsTree);
			this->splitWeastEast->Panel1->Controls->Add(this->panelTestHeader);
			this->splitWeastEast->Panel1MinSize = 230;
			//
			// splitWeastEast.Panel2
			//
			this->splitWeastEast->Panel2->BackColor = System::Drawing::Color::White;
			this->splitWeastEast->Panel2->Controls->Add(this->listViewTestLog);
			this->splitWeastEast->Panel2->Controls->Add(this->panelTestResults);
			this->splitWeastEast->Size = System::Drawing::Size(1479, 597);
			this->splitWeastEast->SplitterDistance = 276;
			this->splitWeastEast->SplitterWidth = 5;
			this->splitWeastEast->TabIndex = 0;
			//
			// panelTestsTree
			//
			this->panelTestsTree->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelTestsTree->Location = System::Drawing::Point(0, 37);
			this->panelTestsTree->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelTestsTree->Name = L"panelTestsTree";
			this->panelTestsTree->Size = System::Drawing::Size(276, 560);
			this->panelTestsTree->TabIndex = 2;
			//
			// panelTestHeader
			//
			this->panelTestHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(157)));
			this->panelTestHeader->Controls->Add(this->labelTestsHeader);
			this->panelTestHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelTestHeader->Location = System::Drawing::Point(0, 0);
			this->panelTestHeader->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelTestHeader->Name = L"panelTestHeader";
			this->panelTestHeader->Size = System::Drawing::Size(276, 37);
			this->panelTestHeader->TabIndex = 1;
			//
			// labelTestsHeader
			//
			this->labelTestsHeader->AutoSize = true;
			this->labelTestsHeader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelTestsHeader->Location = System::Drawing::Point(4, 9);
			this->labelTestsHeader->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTestsHeader->Name = L"labelTestsHeader";
			this->labelTestsHeader->Size = System::Drawing::Size(56, 20);
			this->labelTestsHeader->TabIndex = 0;
			this->labelTestsHeader->Text = L"Tests";
			this->labelTestsHeader->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// listViewTestLog
			//
			this->listViewTestLog->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->columnTestType,
					this->columnTestMessage
			});
			this->listViewTestLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewTestLog->FullRowSelect = true;
			this->listViewTestLog->GridLines = true;
			this->listViewTestLog->HideSelection = false;
			this->listViewTestLog->Location = System::Drawing::Point(0, 37);
			this->listViewTestLog->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->listViewTestLog->Name = L"listViewTestLog";
			this->listViewTestLog->Size = System::Drawing::Size(1198, 560);
			this->listViewTestLog->TabIndex = 1;
			this->listViewTestLog->UseCompatibleStateImageBehavior = false;
			this->listViewTestLog->View = System::Windows::Forms::View::Details;
			//
			// columnTestType
			//
			this->columnTestType->Text = L"Type";
			//
			// columnTestMessage
			//
			this->columnTestMessage->Text = L"Message";
			this->columnTestMessage->Width = 414;
			//
			// panelTestResults
			//
			this->panelTestResults->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)), static_cast<System::Int32>(static_cast<System::Byte>(157)));
			this->panelTestResults->Controls->Add(this->buttonTestLogToClipboard);
			this->panelTestResults->Controls->Add(this->buttonTestLogToFile);
			this->panelTestResults->Controls->Add(this->buttonTestLogClear);
			this->panelTestResults->Controls->Add(this->labelTestResultsHeader);
			this->panelTestResults->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelTestResults->Location = System::Drawing::Point(0, 0);
			this->panelTestResults->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelTestResults->Name = L"panelTestResults";
			this->panelTestResults->Size = System::Drawing::Size(1198, 37);
			this->panelTestResults->TabIndex = 0;
			//
			// buttonTestLogToClipboard
			//
			this->buttonTestLogToClipboard->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonTestLogToClipboard->Location = System::Drawing::Point(865, 0);
			this->buttonTestLogToClipboard->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonTestLogToClipboard->Name = L"buttonTestLogToClipboard";
			this->buttonTestLogToClipboard->Size = System::Drawing::Size(133, 37);
			this->buttonTestLogToClipboard->TabIndex = 3;
			this->buttonTestLogToClipboard->Text = L"Copy to clipboard";
			this->buttonTestLogToClipboard->UseVisualStyleBackColor = true;
			this->buttonTestLogToClipboard->Click += gcnew System::EventHandler(this, &MainForm::buttonTestLogToClipboard_Click);
			//
			// buttonTestLogToFile
			//
			this->buttonTestLogToFile->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonTestLogToFile->Location = System::Drawing::Point(998, 0);
			this->buttonTestLogToFile->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonTestLogToFile->Name = L"buttonTestLogToFile";
			this->buttonTestLogToFile->Size = System::Drawing::Size(100, 37);
			this->buttonTestLogToFile->TabIndex = 2;
			this->buttonTestLogToFile->Text = L"Save to file";
			this->buttonTestLogToFile->UseVisualStyleBackColor = true;
			this->buttonTestLogToFile->Click += gcnew System::EventHandler(this, &MainForm::buttonTestLogToFile_Click);
			//
			// buttonTestLogClear
			//
			this->buttonTestLogClear->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonTestLogClear->Location = System::Drawing::Point(1098, 0);
			this->buttonTestLogClear->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonTestLogClear->Name = L"buttonTestLogClear";
			this->buttonTestLogClear->Size = System::Drawing::Size(100, 37);
			this->buttonTestLogClear->TabIndex = 1;
			this->buttonTestLogClear->Text = L"Clear results";
			this->buttonTestLogClear->UseVisualStyleBackColor = true;
			this->buttonTestLogClear->Click += gcnew System::EventHandler(this, &MainForm::buttonTestLogClear_Click);
			//
			// labelTestResultsHeader
			//
			this->labelTestResultsHeader->AutoSize = true;
			this->labelTestResultsHeader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->labelTestResultsHeader->Location = System::Drawing::Point(5, 9);
			this->labelTestResultsHeader->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTestResultsHeader->Name = L"labelTestResultsHeader";
			this->labelTestResultsHeader->Size = System::Drawing::Size(110, 20);
			this->labelTestResultsHeader->TabIndex = 0;
			this->labelTestResultsHeader->Text = L"Test results";
			this->labelTestResultsHeader->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// panel1
			//
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			this->panel1->Controls->Add(this->buttonRunTests);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1479, 54);
			this->panel1->TabIndex = 0;
			//
			// buttonRunTests
			//
			this->buttonRunTests->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->buttonRunTests->Location = System::Drawing::Point(5, 4);
			this->buttonRunTests->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonRunTests->Name = L"buttonRunTests";
			this->buttonRunTests->Size = System::Drawing::Size(159, 47);
			this->buttonRunTests->TabIndex = 0;
			this->buttonRunTests->Text = L"Otestuj vybrané";
			this->buttonRunTests->UseVisualStyleBackColor = true;
			this->buttonRunTests->Click += gcnew System::EventHandler(this, &MainForm::buttonRunTests_Click);
			//
			// listViewGlobalLog
			//
			this->listViewGlobalLog->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnGlobalLogTime,
					this->columnGlobalLogType, this->columnGlobalLogMessage
			});
			this->listViewGlobalLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewGlobalLog->FullRowSelect = true;
			this->listViewGlobalLog->HideSelection = false;
			this->listViewGlobalLog->Location = System::Drawing::Point(0, 37);
			this->listViewGlobalLog->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->listViewGlobalLog->Name = L"listViewGlobalLog";
			this->listViewGlobalLog->Size = System::Drawing::Size(1479, 101);
			this->listViewGlobalLog->TabIndex = 1;
			this->listViewGlobalLog->UseCompatibleStateImageBehavior = false;
			this->listViewGlobalLog->View = System::Windows::Forms::View::Details;
			//
			// columnGlobalLogTime
			//
			this->columnGlobalLogTime->Text = L"Time";
			//
			// columnGlobalLogType
			//
			this->columnGlobalLogType->Text = L"Type";
			//
			// columnGlobalLogMessage
			//
			this->columnGlobalLogMessage->Text = L"Message";
			this->columnGlobalLogMessage->Width = 909;
			//
			// panelLoggerHeader
			//
			this->panelLoggerHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)), static_cast<System::Int32>(static_cast<System::Byte>(157)));
			this->panelLoggerHeader->Controls->Add(this->buttonLogToClipboard);
			this->panelLoggerHeader->Controls->Add(this->buttonLogToFile);
			this->panelLoggerHeader->Controls->Add(this->buttonLogClear);
			this->panelLoggerHeader->Controls->Add(this->labelLoggerHeader);
			this->panelLoggerHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelLoggerHeader->Location = System::Drawing::Point(0, 0);
			this->panelLoggerHeader->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelLoggerHeader->Name = L"panelLoggerHeader";
			this->panelLoggerHeader->Size = System::Drawing::Size(1479, 37);
			this->panelLoggerHeader->TabIndex = 0;
			//
			// buttonLogToClipboard
			//
			this->buttonLogToClipboard->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonLogToClipboard->Location = System::Drawing::Point(1146, 0);
			this->buttonLogToClipboard->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonLogToClipboard->Name = L"buttonLogToClipboard";
			this->buttonLogToClipboard->Size = System::Drawing::Size(133, 37);
			this->buttonLogToClipboard->TabIndex = 3;
			this->buttonLogToClipboard->Text = L"Copy to clipboard";
			this->buttonLogToClipboard->UseVisualStyleBackColor = true;
			this->buttonLogToClipboard->Click += gcnew System::EventHandler(this, &MainForm::buttonLogToClipboard_Click);
			//
			// buttonLogToFile
			//
			this->buttonLogToFile->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonLogToFile->Location = System::Drawing::Point(1279, 0);
			this->buttonLogToFile->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonLogToFile->Name = L"buttonLogToFile";
			this->buttonLogToFile->Size = System::Drawing::Size(100, 37);
			this->buttonLogToFile->TabIndex = 2;
			this->buttonLogToFile->Text = L"Save to file";
			this->buttonLogToFile->UseVisualStyleBackColor = true;
			this->buttonLogToFile->Click += gcnew System::EventHandler(this, &MainForm::buttonLogToFile_Click);
			//
			// buttonLogClear
			//
			this->buttonLogClear->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonLogClear->Location = System::Drawing::Point(1379, 0);
			this->buttonLogClear->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->buttonLogClear->Name = L"buttonLogClear";
			this->buttonLogClear->Size = System::Drawing::Size(100, 37);
			this->buttonLogClear->TabIndex = 1;
			this->buttonLogClear->Text = L"Clear log";
			this->buttonLogClear->UseVisualStyleBackColor = true;
			this->buttonLogClear->Click += gcnew System::EventHandler(this, &MainForm::buttonLogClear_Click);
			//
			// labelLoggerHeader
			//
			this->labelLoggerHeader->AutoSize = true;
			this->labelLoggerHeader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelLoggerHeader->Location = System::Drawing::Point(4, 7);
			this->labelLoggerHeader->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelLoggerHeader->Name = L"labelLoggerHeader";
			this->labelLoggerHeader->Size = System::Drawing::Size(67, 20);
			this->labelLoggerHeader->TabIndex = 0;
			this->labelLoggerHeader->Text = L"Logger";
			this->labelLoggerHeader->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// MainForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1479, 794);
			this->Controls->Add(this->splitNorthSouth);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MainForm";
			this->Text = L"Datastructures";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->splitNorthSouth->Panel1->ResumeLayout(false);
			this->splitNorthSouth->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitNorthSouth))->EndInit();
			this->splitNorthSouth->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->splitWeastEast->Panel1->ResumeLayout(false);
			this->splitWeastEast->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitWeastEast))->EndInit();
			this->splitWeastEast->ResumeLayout(false);
			this->panelTestHeader->ResumeLayout(false);
			this->panelTestHeader->PerformLayout();
			this->panelTestResults->ResumeLayout(false);
			this->panelTestResults->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panelLoggerHeader->ResumeLayout(false);
			this->panelLoggerHeader->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void buttonRunTests_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void treeTests_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e);
		System::Void treeTests_AfterCheck(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e);
		System::Void buttonLogClear_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonLogToFile_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonLogToClipboard_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonTestLogClear_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonTestLogToFile_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonTestLogToClipboard_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
