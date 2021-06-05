#include "SimplePlugin.hpp"

#include "core/OutboundHandler.hpp"
#include "ui/Interface.hpp"

bool SimplePlugin::InitializePlugin(const QString &, const QJsonObject &_settings)
{
    this->settings = _settings;
    outboundHandler = std::make_shared<SimpleSerializer>();
    guiInterface = new SimpleGUIInterface();
    return true;
}
