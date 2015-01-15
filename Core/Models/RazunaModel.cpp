#include "RazunaModel.h"

RazunaModel::RazunaModel(int id, const QString& name, const QString& apikey)
    : id(id), name(name), apikey(apikey)
{
}

int RazunaModel::getId() const
{
    return this->id;
}

const QString& RazunaModel::getName() const
{
    return this->name;
}

const QString& RazunaModel::getApiKey() const
{
    return this->apikey;
}
