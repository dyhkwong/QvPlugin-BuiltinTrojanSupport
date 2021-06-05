#include "OutboundHandler.hpp"

#include "QJsonStruct/QJsonIO.hpp"

#include <QUrl>
#include <QUrlQuery>

using namespace Qv2rayPlugin;

const Qv2rayPlugin::OutboundInfoObject SimpleSerializer::GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const
{
    OutboundInfoObject obj;
    obj[INFO_PROTOCOL] = protocol;
    if (protocol == "trojan")
    {
        auto server = outbound["servers"].toArray().first().toObject();
        const auto trojan = TrojanServerObject::fromJson(server);
        obj[INFO_SERVER] = trojan.address;
        obj[INFO_PORT] = trojan.port;
    }
    return obj;
}

const void SimpleSerializer::SetOutboundInfo(const QString &protocol, const Qv2rayPlugin::OutboundInfoObject &info, QJsonObject &outbound) const
{
    if ((QStringList{ "trojan" }).contains(protocol))
    {
        QJsonIO::SetValue(outbound, info[INFO_SERVER].toString(), "servers", 0, "address");
        QJsonIO::SetValue(outbound, info[INFO_PORT].toInt(), "servers", 0, "port");
    }
}

const QString SimpleSerializer::SerializeOutbound(const QString &protocol, const QString &alias, const QString &, const QJsonObject &obj,
                                                   const QJsonObject &objStream) const
{

    if (protocol == "trojan")
    {
        QString address, password, sni;
        int port;

        const auto server = obj["servers"].toArray().first().toObject();

        const auto network = QJsonIO::GetValue(objStream, "network").toString();
        if (network != "tcp" && !network.isEmpty())
            return "(Unsupported)";

        const auto security = QJsonIO::GetValue(objStream, "security").toString();
        if (security == "tls")
            sni = QJsonIO::GetValue(objStream, { "tlsSettings", "serverName" }).toString();
        else if (security == "xtls")
            sni = QJsonIO::GetValue(objStream, { "xtlsSettings", "serverName" }).toString();
        else
            return "(Unsupported)";

        address = QJsonIO::GetValue(obj, { "servers", 0, "address" }).toString();
        password = QJsonIO::GetValue(obj, { "servers", 0, "password" }).toString();
        port = QJsonIO::GetValue(obj, { "servers", 0, "port" }).toInt();

        QUrlQuery query;
        if (!sni.isEmpty())
            query.addQueryItem("sni", sni);

        QUrl url;
        url.setFragment(QUrl::toPercentEncoding(alias));
        url.setScheme(protocol);
        url.setHost(address);
        url.setPort(port);
        url.setUserName(password.toUtf8(), QUrl::DecodedMode);
        url.setQuery(query);

        return url.toString(QUrl::ComponentFormattingOption::FullyEncoded);
    }
    return "(Unsupported)";
}

const QPair<QString, QJsonObject> SimpleSerializer::DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const
{
    // not yet supported due to limitation of plugin structure
    return {};
}

const QList<QString> SimpleSerializer::SupportedLinkPrefixes() const
{
    return {};
}
