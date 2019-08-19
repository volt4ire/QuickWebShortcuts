#include "quick_web_shortcuts.h"
#include <KSharedConfig>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include "Config.h"

#include <QDebug>
QuickWebShortcuts::QuickWebShortcuts(QObject *parent, const QVariantList &args)
        : Plasma::AbstractRunner(parent, args) {
    setObjectName("Quick Web Shortcuts");
    setSpeed(NormalSpeed);
    setHasRunOptions(true);
    setPriority(HighestPriority);
}

QuickWebShortcuts::~QuickWebShortcuts() = default;

void QuickWebShortcuts::init() {
#if clear_history != 0
    configGroup = KSharedConfig::openConfig("krunnerrc")->group("General");
    connect(this, SIGNAL(teardown()), this, SLOT(matchSessionFinished()));
#endif
}

void QuickWebShortcuts::matchSessionFinished() {
#if clear_history != 0
#if clear_history == 2
    QString history = configGroup.readEntry("history");
    QString filteredHistory;
    filteredHistory = history.replace(QRegExp(R"([a-z]{0,5}: ?[^,]+,?)"), "");
#elif clear_history == 1
    if (!executed) return;
    executed = false;
    QString history = configGroup.readEntry("history");
    QString filteredHistory;
    for (const auto &item : history.split(',')) {
        if (!item.startsWith(':')) {
            filteredHistory += item + ",";
        }
    }
#endif

    if (filteredHistory.size() == configGroup.readEntry("history").size()) return;

    QFile f(QDir::homePath() + "/.config/krunnerrc");
    if (f.open(QIODevice::ReadWrite)) {
        QString s;
        QTextStream t(&f);
        while (!t.atEnd()) {
            QString line = t.readLine();
            if (!line.startsWith("history")) {
                s.append(line + "\n");
            } else {
                s.append("history=" + filteredHistory + "\n");
            }
        }
        f.resize(0);
        f.write(s.toLocal8Bit());
        f.close();
    }
#endif
}

void QuickWebShortcuts::match(Plasma::RunnerContext &context) {
    if (!context.isValid()) return;

    QString term = context.query();
#ifndef open_urls
    if (!term.startsWith(":")) return;
#endif
    QList<Plasma::QueryMatch> matches;
    QMap<QString, QVariant> data;

// Private window option
    if (term.startsWith("::")) {
        term = term.mid(2);
        data.insert("browser", config.privateBrowser);
        QString url = config.searchEngineURL + QUrl::toPercentEncoding(term);
        data.insert("url", url);
        const QString mode = config.privateBrowser.contains("private") ? "private window" : "incognito mode";
#ifndef show_search_engine_name
        QString text = "Search for " + term + " in " + mode;
#else
        QString text = "Search " + config.searchEngine + " for " + term + " in " + mode;
#endif
        matches.append(createMatch(text, data));
    }

// Normal Window option
    else if (term.startsWith(':')) {
        term = term.mid(1);
#ifndef show_search_engine_name
        QString text = "Search for " + term;
#else
        QString text = "Search " + config.searchEngine + " for " + term;
#endif
        QString url = config.searchEngineURL + QUrl::toPercentEncoding(term);
        data.insert("browser", config.browser);
        data.insert("url", url);
        matches.append(createMatch(text, data));
    }

// Open urls
#ifdef open_urls
    else if (term.contains(QRegExp(R"(^.*\.[a-z]{2,5}$)"))) {
        QString text = "Go To  " + term;
        data.insert("url", !term.startsWith("http") ? "http://" + term : term);
        matches.append(createMatch(text, data, "globe"));
    }
#endif

    context.addMatches(matches);

}

void QuickWebShortcuts::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) {
    Q_UNUSED(context)

    executed = true;
    QMap<QString, QVariant> payload = match.data().toMap();
    system(qPrintable("$(" + payload.value("browser", "xdg-open").toString() + " " + payload.value("url").toString() + ") &"));
}

Plasma::QueryMatch QuickWebShortcuts::createMatch(const QString &text, const QMap<QString, QVariant> &data, const QString &icon) {
    Plasma::QueryMatch match(this);
    match.setIconName(icon.isEmpty() ? config.icon : icon);
    match.setText(text);
    match.setData(data);
    return match;
}

K_EXPORT_PLASMA_RUNNER(quick_web_shortcuts, QuickWebShortcuts)

// needed for the QObject subclass declared as part of K_EXPORT_PLASMA_RUNNER
#include "quick_web_shortcuts.moc"

