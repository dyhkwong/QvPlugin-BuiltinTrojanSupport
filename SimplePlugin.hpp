#pragma once

#include "QvPluginInterface.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class SimplePlugin
    : public QObject
    , Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return { "Builtin Trojan Support",               //
                 "Qv2ray Workgroup",                     //
                 "qvplugin_builtin_trojan",              //
                 "Trojan editor support",                //
                 "0.0.0",                                //
                 "Qv2ray/QvPlugin-BuiltinTrojanSupport", //
                 {
                     COMPONENT_OUTBOUND_HANDLER, //
                     COMPONENT_GUI               //
                 },
                 UPDATE_NONE };
    }
    ~SimplePlugin(){};
    bool InitializePlugin(const QString &, const QJsonObject &) override;

  signals:
    void PluginLog(const QString &) const override;
    void PluginErrorMessageBox(const QString &, const QString &) const override;
};
