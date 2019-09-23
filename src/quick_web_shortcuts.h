#ifndef QUICKWEBSHORTCUTS_H
#define QUICKWEBSHORTCUTS_H

#include <KRunner/AbstractRunner>
#include <searchproviders/RequiredData.h>
#include <QtNetwork/QNetworkAccessManager>

class QuickWebShortcuts : public Plasma::AbstractRunner {
Q_OBJECT

public:
    QuickWebShortcuts(QObject *parent, const QVariantList &args);

    void reloadConfiguration() override;

    KConfigGroup configGroup;
    bool openUrls, searchSuggestions, privateWindowSearchSuggestions;
    int minimumLetterCount, maxSuggestionResults;
    QString privateBrowser, privateBrowserMode, searchEngineBaseUrl, searchOptionTemplate, searchSuggestionChoice;
    QString bingMarket, googleLocale;
    QIcon currentIcon;
    QMap<QString, QIcon> icons;
    QNetworkProxy *proxy;

    RequiredData requiredData;
    QMap<QString, QString> searchEngines;

    Plasma::QueryMatch createMatch(const QString &text, const QMap<QString, QVariant> &data, const QString &icon = "");

    void bingSearchSuggest(Plasma::RunnerContext &context, const QString &term, const QString &browser = "");

    void googleSearchSuggest(Plasma::RunnerContext &context, const QString &term, const QString &browser = "");

    void duckDuckGoSearchSuggest(Plasma::RunnerContext &context, const QString &term, const QString &browser = "");

protected Q_SLOTS:

    void init() override;

    void matchSessionFinished();

public: // Plasma::AbstractRunner API
    void match(Plasma::RunnerContext &context) override;

    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
};

#endif
