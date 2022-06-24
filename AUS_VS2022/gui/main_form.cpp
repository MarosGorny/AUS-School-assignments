#include "../structures/heap_monitor.h"
#include "main_form.h"
#include "gui_log_consumer.h"
#include "../structures/_logger/file_log_consumer.h"
#include "../tests/test.h"
#include "../tests/vector/vector_test.h"
#include "../tests/array/array_test.h"
#include "../tests/list/list_test.h"
#include "../tests/matrix/matrix_test.h"
#include "../tests/stack/stack_test.h"
#include "../tests/queue/queue_test.h"
#include "../tests/priority_queue/priority_queue_test.h"
#include "../tests/tree/tree_test.h"
#include "../tests/table/table_test.h"
#include "../tests/table/sorting_test.h"
#include "../tests/stdvector/stdvector_test.h"
#include <algorithm>
#include <vector>

using System::String;

namespace WF = System::Windows::Forms;

[System::STAThread]
void main(array<String^>^)
{
	initHeapMonitor();
	WF::Application::EnableVisualStyles();
	WF::Application::SetCompatibleTextRenderingDefault(false);
	std::vector<tests::Test*> tests;

	// Registracia testov:

	tests.emplace_back(new tests::VectorTestOverall());

	tests.emplace_back(new tests::ArrayTestOverall());

	tests.emplace_back(new tests::ListTestOverall());

	tests.emplace_back(new tests::StackTestOverall());
	tests.emplace_back(new tests::QueueTestOverall());

	tests.emplace_back(new tests::MatrixTestOverall());

	tests.emplace_back(new tests::PriorityQueueTestOverall());

	tests.emplace_back(new tests::TreeTestOverall());

	tests.emplace_back(new tests::TableTestOverall());

	tests.emplace_back(new tests::SortsTest());

	gui::MainForm form(tests);

	// Registracia odoberatelov globalneho logu:

	// Odoberatel logu, ktory preposiela spravy do GUI.
	//gui::GuiLogConsumer* guiLogConsumer = new gui::GuiLogConsumer(%form);
	//structures::Logger::getInstance().registerConsumer(guiLogConsumer);

	//odoberatel logu, ktory preposiela spravy do suboru
	//structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer("log.csv");
	//structures::Logger::getInstance().registerConsumer(fileLogConsumer);

	WF::Application::Run(%form);

	// Ak ste Vas logger alokovali dynamicky, zmazatù ho mÙûete tu:
	//delete guiLogConsumer;
	//delete fileLogConsumer;
	for (tests::Test* test : tests)
	{
		delete test;
	}
}

namespace gui
{
	const int WidthFitHeader = -1;
	const int WidthFitContent = -2;

	/// <summary>
	/// Obal ukazovatela na test a skupinu v ListView,
	/// ktory sa vklada ako tag do uzlov TreeView.
	/// </summary>
	ref class TreeNodeTagData
	{
	public:
		TreeNodeTagData(tests::Test* test, WF::ListViewGroup^ group) :
			test_(test),
			group_(group)
		{
		}

		property tests::Test* Test
		{
			tests::Test* get() { return test_; }
		}

		property WF::ListViewGroup^ Group
		{
			WF::ListViewGroup^ get() { return group_; }
		}

	private:
		tests::Test* test_;
		WF::ListViewGroup^ group_;
	};

	/// <summary>
	/// TreeView, v ktorom je vypnuty dvojklik, kvoli problemom s oznacovanim.
	///	https://social.msdn.microsoft.com/Forums/windows/en-US/c1212cfe-170a-47f9-8b5f-e728fa229c59/how-to-prevent-collapse-when-double-click-treenode-?forum=winforms
	/// </summary>
	public ref class NoClickTree
		: public WF::TreeView
	{
	protected:
		System::Void WndProc(WF::Message% m) override
		{
			// Suppress WM_LBUTTONDBLCLK
			if (m.Msg == 0x203)
			{
				m.Result = System::IntPtr::Zero;
			}
			else
			{
				WF::TreeView::WndProc(m);
			}
			return System::Void();
		}
	};

// Utility functions:

	System::Drawing::Color TestResultToColor(tests::TestResult result)
	{
		switch (result)
		{
		case tests::TestResult::Passed:
			return System::Drawing::Color::FromArgb(1, 51, 204, 51);

		case tests::TestResult::Failed:
			return System::Drawing::Color::FromArgb(1, 255, 71, 0);

		case tests::TestResult::Partial:
			return System::Drawing::Color::FromArgb(1, 255, 255, 102);

		default:
			return System::Drawing::Color::White;
		}
	}

	String^ MakeGroupName(WF::TreeNode^ node)
	{
		String^ name = node->Text;
		while (node->Parent)
		{
			node = node->Parent;
			name = node->Text + "." + name;
		}
		return name;
	}

	bool IsLeafNode(WF::TreeNode^ node)
	{
		return node->Nodes->Count == 0;
	}

	tests::Test* GetNodeTest(WF::TreeNode^ node)
	{
		return dynamic_cast<TreeNodeTagData^>(node->Tag)->Test;
	}

	WF::ListViewGroup^ GetNodeGroup(WF::TreeNode^ node)
	{
		return dynamic_cast<TreeNodeTagData^>(node->Tag)->Group;
	}

	System::Void SetSubtreeChecked(WF::TreeNode^ node, bool value)
	{
		for each (WF::TreeNode^ child in node->Nodes)
		{
			child->Checked = value;
			SetSubtreeChecked(child, value);
		}
		return System::Void();
	}

	System::Void SetParentChecked(WF::TreeNode^ node)
	{
		WF::TreeNode^ parent = node->Parent;
		while (parent)
		{
			parent->Checked = true;
			parent = parent->Parent;
		}
		return System::Void();
	}

	System::Void SetParentUnchecked(WF::TreeNode^ node)
	{
		WF::TreeNode^ parent = node->Parent;
		if (parent && parent->Checked)
		{
			bool anyChildChecked = false;
			for each (WF::TreeNode^ child in parent->Nodes)
			{
				anyChildChecked = anyChildChecked || child->Checked;
			}
			if (!anyChildChecked)
			{
				parent->Checked = false;
				SetParentUnchecked(parent);
			}
		}
		return System::Void();
	}

// MainForm:

	MainForm::MainForm(const std::vector<tests::Test*>& tests) :
		testLogIconList_(gcnew WF::ImageList()),
		globalLogIconList_(gcnew WF::ImageList()),
		testLogIconOrder_(new std::vector<tests::TestLogType>()),
		globalLogIconOrder_(new std::vector<structures::LogType>()),
		treeCheckInProgress_(false),
		isDisposed_(false)
	{
		InitializeComponent();

		CreateTestTree();
		RegisterTests(tests);

		RegisterTestLogIcon(tests::TestLogType::Pass);
		RegisterTestLogIcon(tests::TestLogType::Error);
		RegisterTestLogIcon(tests::TestLogType::Warning);
		RegisterTestLogIcon(tests::TestLogType::Info);
		RegisterTestLogIcon(tests::TestLogType::Elapsed);

		// https://www.flaticon.com/free-icons/tick Tick icons created by Roundicons - Flaticon
		// https://www.flaticon.com/free-icons/stopwatch Stopwatch icons created by Good Ware - Flaticon
		RegisterGlobalLogIcon(structures::LogType::Error);
		RegisterGlobalLogIcon(structures::LogType::Warning);
		RegisterGlobalLogIcon(structures::LogType::Info);
		RegisterGlobalLogIcon(structures::LogType::Duration);

		listViewTestLog->SmallImageList = testLogIconList_;
		listViewGlobalLog->SmallImageList = globalLogIconList_;
	}

	System::Void MainForm::LogMessage(structures::LogType type, String^ message)
	{
		String^ timestamp = System::DateTime::Now.ToString("HH:mm:ss");
		String^ typeStr = gcnew String(structures::logTypeToString(type).c_str());
		array<String^>^ columns = gcnew array<String^>(3)
		{
			timestamp,
			typeStr,
			message
		};
		WF::ListViewItem^ item = gcnew WF::ListViewItem(columns, GlobalLogTypeToIndex(type));
		listViewGlobalLog->Items->Insert(0, item);
		columnGlobalLogTime->Width = WidthFitContent;
		columnGlobalLogMessage->Width = WidthFitContent;
	}

	System::Void gui::MainForm::LogDuration(size_t size, tests::DurationType duration, const std::string& message)
	{
		//https://godbolt.org/z/WE44rqx6x
		String^ str = "Size: " + size + ", Duration: " + duration.count() + " nanoseconds, " + gcnew String(message.c_str());
		this->LogMessage(structures::LogType::Duration, str);
		return System::Void();
	}

	// Deterministic Dispose.
	MainForm::~MainForm()
	{
		// See https://manski.net/2012/01/idisposable-finalizer-and-suppressfinalize/

		if (isDisposed_)
		{
			return;
		}

		if (components)
		{
			delete components;
		}

		this->!MainForm();
		isDisposed_ = true;
	}

	// Non-deterministic Finalize.
	MainForm::!MainForm()
	{
		delete testLogIconOrder_;
		delete globalLogIconOrder_;
	}

	System::Void gui::MainForm::CreateTestTree()
	{
		this->treeTests = (gcnew NoClickTree());
		this->treeTests->BorderStyle = WF::BorderStyle::None;
		this->treeTests->CheckBoxes = true;
		this->treeTests->Dock = WF::DockStyle::Fill;
		this->treeTests->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(238)));
		this->treeTests->Location = System::Drawing::Point(0, 0);
		this->treeTests->Margin = WF::Padding(4);
		this->treeTests->Name = L"treeTests";
		this->treeTests->Size = System::Drawing::Size(230, 561);
		this->treeTests->TabIndex = 0;
		this->treeTests->AfterCheck += gcnew WF::TreeViewEventHandler(this, &MainForm::treeTests_AfterCheck);
		this->treeTests->AfterSelect += gcnew WF::TreeViewEventHandler(this, &MainForm::treeTests_AfterSelect);
		this->panelTestsTree->Controls->Add(this->treeTests);
		return System::Void();
	}

	System::Void MainForm::RegisterTests(const std::vector<tests::Test*>& tests)
	{
		for (tests::Test* test : tests)
		{
			AddTest(test, treeTests->Nodes);
		}
		treeTests->ExpandAll();
		return System::Void();
	}

	System::Void MainForm::AddTest(tests::Test* test, WF::TreeNodeCollection^ nodes)
	{
		WF::TreeNode^ node = gcnew WF::TreeNode(gcnew String(test->getName().c_str()));
		nodes->Add(node);
		String^ groupName = MakeGroupName(node);
		WF::ListViewGroup^ group = gcnew WF::ListViewGroup();
		group->Name = groupName;
		group->Header = groupName;
		node->Tag = gcnew TreeNodeTagData(test, group);
		listViewTestLog->Groups->Add(group);
		tests::ComplexTest* complexTest = dynamic_cast<tests::ComplexTest*>(test);
		if (complexTest)
		{
			for (tests::Test* subTest : complexTest->getSubTests())
			{
				AddTest(subTest, node->Nodes);
			}
		}
		return System::Void();
	}

	System::Void MainForm::RunSelectedTests(WF::TreeNodeCollection^ nodes)
	{
		for each (WF::TreeNode^ node in nodes)
		{
			if (IsLeafNode(node) && node->Checked)
			{
				GetNodeTest(node)->run();
			}
			else
			{
				RunSelectedTests(node->Nodes);
			}
		}
		return System::Void();
	}

	System::Void MainForm::ColorizeTestTree(WF::TreeNodeCollection^ nodes)
	{
		for each (WF::TreeNode^ node in nodes)
		{
			node->BackColor = TestResultToColor(GetNodeTest(node)->getResult());
			ColorizeTestTree(node->Nodes);
		}
		return System::Void();
	}

	System::Void MainForm::ShowTestLogs(WF::TreeNodeCollection^ nodes)
	{
		for each (WF::TreeNode^ node in nodes)
		{
			if (node->Checked)
			{
				if (IsLeafNode(node))
				{
					const tests::SimpleTest* leafTestPtr = dynamic_cast<const tests::SimpleTest*>(GetNodeTest(node));
					if (leafTestPtr != nullptr)
					{
						const tests::SimpleTest& leafTest = *leafTestPtr;
						for (const tests::TestLog& log : leafTest.getOutput())
						{
							array<String^>^ columns = gcnew array<String^>(3)
							{
								gcnew String(tests::testLogTypeToString(log.getType()).c_str()),
								gcnew String(log.getMessage().c_str())
							};
							WF::ListViewItem^ item = gcnew WF::ListViewItem(columns, TestLogTypeToIndex(log.getType()));
							item->Group = GetNodeGroup(node);
							listViewTestLog->Items->Add(item);
						}
					}
				}

				ShowTestLogs(node->Nodes);
			}
		}
		return System::Void();
	}

	System::Void MainForm::AdjustTestLogColumns()
	{
		bool anyOutput = listViewTestLog->Items->Count != 0;
		columnTestType->Width = anyOutput ? WidthFitContent : WidthFitContent;
		columnTestMessage->Width = anyOutput ? WidthFitContent : WidthFitContent;
		return System::Void();
	}

	System::Void MainForm::ResetTestLog()
	{
		listViewTestLog->Items->Clear();
		return System::Void();
	}

	System::Void MainForm::ResetTests()
	{
		for each (WF::TreeNode^ node in treeTests->Nodes)
		{
			GetNodeTest(node)->reset();
		}
		return System::Void();
	}

	System::Void MainForm::RegisterTestLogIcon(tests::TestLogType type)
	{
		if (std::find(begin(*testLogIconOrder_), end(*testLogIconOrder_), type) != end(*testLogIconOrder_))
		{
			return;
		}

		testLogIconOrder_->emplace_back(type);

		switch (type)
		{
		case tests::TestLogType::Error:
			testLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/error.png"));
			break;

		case tests::TestLogType::Warning:
			testLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/warning.png"));
			break;

		case tests::TestLogType::Pass:
			testLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/ok.png"));
			break;

		case tests::TestLogType::Info:
			testLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/info.png"));
			break;

		case tests::TestLogType::Elapsed:
			testLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/elapsed.png"));
			break;

		default:
			break;
		}
		return System::Void();
	}

	System::Void MainForm::RegisterGlobalLogIcon(structures::LogType type)
	{
		if (std::find(begin(*globalLogIconOrder_), end(*globalLogIconOrder_), type) != end(*globalLogIconOrder_))
		{
			return;
		}

		globalLogIconOrder_->emplace_back(type);

		switch (type)
		{
		case structures::LogType::Info:
			globalLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/info.png"));
			break;

		case structures::LogType::Warning:
			globalLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/warning.png"));
			break;

		case structures::LogType::Error:
			globalLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/error.png"));
			break;

		case structures::LogType::Duration:
			globalLogIconList_->Images->Add(gcnew System::Drawing::Bitmap("images/elapsed.png"));
			break;

		default:
			break;
		}
		return System::Void();
	}

	System::Int32 MainForm::TestLogTypeToIndex(tests::TestLogType type)
	{
		System::Int32 i = 0;
		for (tests::TestLogType logType : *testLogIconOrder_)
		{
			if (logType == type)
			{
				return i;
			}
			++i;
		}
		return -1;
	}

	System::Int32 MainForm::GlobalLogTypeToIndex(structures::LogType type)
	{
		System::Int32 i = 0;
		for (structures::LogType logType : *globalLogIconOrder_)
		{
			if (logType == type)
			{
				return i;
			}
			++i;
		}
		return -1;
	}

	String^ MainForm::GlobalLogToString()
	{
		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
		for each (WF::ListViewItem^ item in listViewGlobalLog->Items)
		{
			String^ time = item->SubItems[0]->Text;
			String^ type = item->SubItems[1]->Text;
			String^ message = item->SubItems[2]->Text;
			sb->AppendFormat("[{0}] {1,-8} {2}{3}", time, type, message, System::Environment::NewLine);
		}
		return sb->ToString();
	}

	String^ MainForm::TestLogToString()
	{
		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
		WF::ListViewGroup^ currentGroup = nullptr;

		for each (WF::ListViewItem^ item in listViewTestLog->Items)
		{
			if (item->Group && item->Group != currentGroup)
			{
				sb->AppendLine();
				sb->AppendFormat("{0}{1}", item->Group->Header, System::Environment::NewLine);
				currentGroup = item->Group;
			}

			String^ type = item->SubItems[0]->Text;
			String^ message = item->SubItems[1]->Text;
			sb->AppendFormat("\t{0,-7} {1}{2}", type, message, System::Environment::NewLine);
		}

		return sb->ToString();
	}

	System::Void MainForm::SaveToFile(String^ str)
	{
#ifdef AUS_CATCH_EXCEPTIONS
		try
		{
#endif
			System::IO::Stream^ fileStream;
			WF::SaveFileDialog^ dialog = gcnew WF::SaveFileDialog();
			dialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
			dialog->FilterIndex = 1;
			dialog->RestoreDirectory = true;
			if (dialog->ShowDialog() == WF::DialogResult::OK)
			{
				if ((fileStream = dialog->OpenFile()) != nullptr)
				{
					System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(fileStream);
					sw->Write(str);
					sw->Flush();
					sw->Close();
					fileStream->Close();
					WF::MessageBox::Show(
						this,
						"Log was saved to file.",
						"Info",
						WF::MessageBoxButtons::OK,
						WF::MessageBoxIcon::Information);
				}
				else
				{
					structures::Logger::getInstance().logError("Failed to open the file.");
					WF::MessageBox::Show(
						this,
						"Fail to open the file.",
						"Error",
						WF::MessageBoxButtons::OK,
						WF::MessageBoxIcon::Error);
				}
			}
#ifdef AUS_CATCH_EXCEPTIONS
		}
		catch (System::Exception^)
		{
			structures::Logger::getInstance().logError("Failed to save the log to the file.");
			WF::MessageBox::Show(
				this,
				"Failed to save the log to the file.",
				"Error",
				WF::MessageBoxButtons::OK,
				WF::MessageBoxIcon::Error);
		}
#endif
		return System::Void();
	}

	System::Void MainForm::SaveToClipboard(String^ str)
	{
#ifdef AUS_CATCH_EXCEPTIONS
		try
		{
#endif
			WF::Clipboard::SetText(str);
			WF::MessageBox::Show(
				this,
				"Log was copied to your clipboard.",
				"Info",
				WF::MessageBoxButtons::OK,
				WF::MessageBoxIcon::Information);
#ifdef AUS_CATCH_EXCEPTIONS
		}
		catch (System::Exception^)
		{
			structures::Logger::getInstance().logError("Failed to copy log to the clipboard.");
			WF::MessageBox::Show(
				this,
				"Fail to copy log to the clipboard.",
				"Error",
				WF::MessageBoxButtons::OK,
				WF::MessageBoxIcon::Error);
		}
#endif
		return System::Void();
	}

	System::Void MainForm::buttonRunTests_Click(System::Object^, System::EventArgs^)
	{
		listViewTestLog->BeginUpdate();
		treeTests->BeginUpdate();
		ResetTests();
		ResetTestLog();
		RunSelectedTests(treeTests->Nodes);
		ColorizeTestTree(treeTests->Nodes);
		ShowTestLogs(treeTests->Nodes);
		AdjustTestLogColumns();
		treeTests->EndUpdate();
		listViewTestLog->EndUpdate();
		return System::Void();
	}

	System::Void MainForm::treeTests_AfterSelect(System::Object^, WF::TreeViewEventArgs^ e)
	{
		treeTests->SelectedNode = nullptr;
		e->Node->Checked = !e->Node->Checked;
		return System::Void();
	}

	System::Void MainForm::treeTests_AfterCheck(System::Object^, WF::TreeViewEventArgs^ e)
	{
		if (!treeCheckInProgress_)
		{
			treeCheckInProgress_ = true;
			SetSubtreeChecked(e->Node, e->Node->Checked);
			if (e->Node->Checked)
			{
				SetParentChecked(e->Node);
			}
			else
			{
				SetParentUnchecked(e->Node);
			}
			treeCheckInProgress_ = false;
		}
		return System::Void();
	}

	System::Void MainForm::buttonLogClear_Click(System::Object^, System::EventArgs^)
	{
		listViewGlobalLog->Items->Clear();
		return System::Void();
	}

	System::Void MainForm::buttonLogToFile_Click(System::Object^, System::EventArgs^)
	{
		if (listViewGlobalLog->Items->Count > 0)
		{
			SaveToFile(GlobalLogToString());
		}
		return System::Void();
	}

	System::Void MainForm::buttonLogToClipboard_Click(System::Object^, System::EventArgs^)
	{
		if (listViewGlobalLog->Items->Count > 0)
		{
			SaveToClipboard(GlobalLogToString());
		}
		return System::Void();
	}

	System::Void MainForm::buttonTestLogClear_Click(System::Object^, System::EventArgs^)
	{
		ResetTestLog();
		ResetTests();
		ColorizeTestTree(treeTests->Nodes);
		for each (WF::TreeNode^ node in treeTests->Nodes)
		{
			SetSubtreeChecked(node, false);
		}
		return System::Void();
	}

	System::Void MainForm::buttonTestLogToFile_Click(System::Object^, System::EventArgs^)
	{
		if (listViewTestLog->Items->Count > 0)
		{
			SaveToFile(TestLogToString());
		}
		return System::Void();
	}

	System::Void MainForm::buttonTestLogToClipboard_Click(System::Object^, System::EventArgs^)
	{
		if (listViewTestLog->Items->Count > 0)
		{
			SaveToClipboard(TestLogToString());
		}
		return System::Void();
	}
}