#pragma once

#include "main_form.h"
#include "../structures/_logger/logger.h"
#include <string>
#include <vcclr.h>

namespace gui
{
    /// <summary>
    /// Odoberatel loggera. Preposiela vsetky logy do GUI.
    /// </summary>
    class GuiLogConsumer
        : public structures::ILogConsumer
    {
    public:
        GuiLogConsumer(MainForm^ form);
        void logMessage(structures::LogType type, const std::string& message) override;
        void logDuration(size_t size, tests::DurationType duration, const std::string& message) override;

    public:
        gcroot<MainForm^> form_;
    };
}
