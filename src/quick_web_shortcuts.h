#ifndef QUICKWEBSHORTCUTS_H
#define QUICKWEBSHORTCUTS_H

#include <KRunner/AbstractRunner>
#include "Config.h"

class QuickWebShortcuts : public Plasma::AbstractRunner {
Q_OBJECT

public:
    QuickWebShortcuts(QObject *parent, const QVariantList &args);

    ~QuickWebShortcuts() override;

    Config config;
    KConfigGroup configGroup;
    bool executed = false;

    Plasma::QueryMatch createMatch(const QString &text, const QMap<QString, QVariant> &data, const QString &icon = "");

protected Q_SLOTS:

    void init() override;

    void matchSessionFinished();

public: // Plasma::AbstractRunner API
    void match(Plasma::RunnerContext &context) override;

    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
};

#endif
