#include "EventHandler.hpp"

using namespace Qv2rayPlugin;
SimpleEventHandler::SimpleEventHandler() : Qv2rayPlugin::PluginEventHandler()
{
}

QvPlugin_EventHandler(SimpleEventHandler, Connectivity)
{
    Q_UNUSED(pluginEvent);
}
QvPlugin_EventHandler(SimpleEventHandler, SystemProxy)
{
    Q_UNUSED(pluginEvent);
}
QvPlugin_EventHandler(SimpleEventHandler, ConnectionEntry)
{
    Q_UNUSED(pluginEvent);
}
QvPlugin_EventHandler(SimpleEventHandler, ConnectionStats)
{
    Q_UNUSED(pluginEvent);
}
