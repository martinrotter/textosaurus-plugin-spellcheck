// For license of this file, see <project-root-folder>/LICENSE.md.

#include "definitions.h"
#include "spellchecker.h"

#include <QMutex>

Spellchecker::Spellchecker() {
  m_mutex.reset(new QMutex());
}

Spellchecker::~Spellchecker() {}

void Spellchecker::updateDictionaries(const QString& dict, const QString& aff) {
  QMutexLocker lock(m_mutex.data());

#if defined (Q_OS_WIN)
  Hunspell* new_spell = new Hunspell(prepareDictionaryPath(aff).toUtf8().constData(),
                                     prepareDictionaryPath(dict).toUtf8().constData());
#else
  Hunspell* new_spell = new Hunspell(aff.toLocal8Bit().constData(),
                                     dict.toLocal8Bit().constData());
#endif

  m_hunspell.reset(new_spell);
}

QStringList Spellchecker::suggest(const QString& word) const {
  QMutexLocker lock(m_mutex.data());

  return {};
}

bool Spellchecker::spell(const QString& word) const {
  QMutexLocker lock(m_mutex.data());

  return {};
}

QString Spellchecker::prepareDictionaryPath(const QString& path) const {
  return QL1S("\\\\?\\") + path;
}
