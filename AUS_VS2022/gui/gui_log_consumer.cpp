#include "gui_log_consumer.h"

namespace gui
{
    GuiLogConsumer::GuiLogConsumer(MainForm^ form) :
        form_(form)
    {
    }

    void GuiLogConsumer::logMessage(structures::LogType type, const std::string& message)
    {
        form_->LogMessage(type, gcnew System::String(message.c_str()));
    }

    void GuiLogConsumer::logDuration(size_t size, tests::DurationType duration, const std::string& message)
    {
        form_->LogDuration(size, duration, message);
    }
}