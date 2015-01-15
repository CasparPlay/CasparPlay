#pragma once

#include "../Shared.h"

#include <QtCore/QString>

class CORE_EXPORT RazunaModel
{
    public:
        explicit RazunaModel(int id, const QString& name, const QString& apikey);

        int getId() const;
        const QString& getName() const;
        const QString& getApiKey() const;

    private:
        int id;
        QString apikey;
        QString name;
};
