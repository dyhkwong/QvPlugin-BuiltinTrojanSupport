#include "PluginOutboundEditor.hpp"

SimplePluginOutboundEditor::SimplePluginOutboundEditor(QWidget *parent) : Qv2rayPlugin::QvPluginEditor(parent)
{
    setupUi(this);
    setProperty("QV2RAY_INTERNAL_HAS_STREAMSETTINGS", true);
    setProperty("QV2RAY_INTERNAL_HAS_FORWARD_PROXY", true);
}

void SimplePluginOutboundEditor::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void SimplePluginOutboundEditor::on_trojan_passwordTxt_textEdited(const QString &arg1)
{
    PLUGIN_EDITOR_LOADING_GUARD
    trojan.password = arg1;
}
