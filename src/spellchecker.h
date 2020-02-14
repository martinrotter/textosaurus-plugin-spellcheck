// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <QScopedPointer>
#include <QStringList>

#include <hunspell/hunspell.hxx>

class QMutex;

// Hunspell simple wrapper.
class Spellchecker {
  public:
    explicit Spellchecker();
    ~Spellchecker();

    void updateDictionaries(const QString& dict, const QString& aff);

    QStringList suggest(const QString& word) const;
    bool spell(const QString& word) const;

  private:
    QString prepareDictionaryPath(const QString& path) const;

  private:
    QScopedPointer<Hunspell> m_hunspell;
    QScopedPointer<QMutex> m_mutex;
};

#endif // SPELLCHECKER_H
