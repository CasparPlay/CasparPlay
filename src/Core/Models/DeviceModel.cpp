#include "DeviceModel.h"

DeviceModel::DeviceModel(int id, const QString& name, const QString& address, int port, const QString& username,
                         const QString& password, const QString& description, const QString& version, const QString& shadow,
                         int channels, const QString& channelFormats, int previewChannel, const QString& DbUserName, const QString& DbUserPass)
    : id(id), port(port), name(name), address(address), username(username),  password(password), description(description),
      version(version), shadow(shadow), channels(channels), channelFormats(channelFormats), previewChannel(previewChannel),
      DbUserName(DbUserName), DbUserPass(DbUserPass)
{
}

int DeviceModel::getId() const
{
    return this->id;
}

const QString& DeviceModel::getName() const
{
    return this->name;
}

const QString& DeviceModel::getAddress() const
{
    return this->address;
}

int DeviceModel::getPort() const
{
    return this->port;
}

const QString& DeviceModel::getUsername() const
{
    return this->username;
}

const QString& DeviceModel::getPassword() const
{
    return this->password;
}

const QString& DeviceModel::getDescription() const
{
    return this->description;
}

const QString& DeviceModel::getVersion() const
{
    return this->version;
}

const QString& DeviceModel::getShadow() const
{
    return this->shadow;
}

int DeviceModel::getChannels() const
{
    return this->channels;
}

const QString& DeviceModel::getChannelFormats() const
{
    return this->channelFormats;
}

int DeviceModel::getPreviewChannel() const
{
    return this->previewChannel;
}

const QString& DeviceModel::getDbUserName() const
{
    return this->DbUserName;
}

const QString& DeviceModel::getDbUserPass() const
{
    return this->DbUserPass;
}
