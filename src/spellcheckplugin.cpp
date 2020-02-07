// For license of this file, see <project-root-folder>/LICENSE.md.

#include "spellcheckplugin.h"

#include "libtextosaurus/common/miscellaneous/settings.h"
#include "libtextosaurus/saurus/miscellaneous/textapplication.h"
#include "libtextosaurus/saurus/miscellaneous/textapplicationsettings.h"
#include "libtextosaurus/saurus/gui/tabwidget.h"
#include "libtextosaurus/saurus/gui/texteditor.h"

#include <hunspell/hunspell.hxx>

#include <QMessageBox>
#include <QAction>
#include <QLabel>
#include <QLayout>
#include <QTextCodec>

SpellcheckPlugin::SpellcheckPlugin(QObject *parent) {
  Q_UNUSED(parent)
}

SpellcheckPlugin::~SpellcheckPlugin() {
  qDebug("Destroying SpellcheckPlugin instance.");
}


QString SpellcheckPlugin::name() const {
  return tr("Spell Checker");
}

QString SpellcheckPlugin::id() const {
  return QSL("io.github.martinrotter.textosaurus.spellcheck");
}

QList<BaseSidebar*> SpellcheckPlugin::sidebars() {
  return {};
}

QList<QAction*> SpellcheckPlugin::userActions() {
  return {
    new QAction(tr("Sample Action"), this)
  };
}

void SpellcheckPlugin::start(const QString &library_file, QWidget *main_form_widget, TextApplication *text_app,
    Settings *settings, IconFactory *icon_factory, WebFactory *web_factory) {
  PluginBase::start(library_file, main_form_widget, text_app, settings, icon_factory, web_factory);

  QString aff = QSL("\\\\?\\") + "c:\\Projekty\\build\\src\\textosaurus\\plugins\\spellcheck\\dict\\index.aff";
  QString dic = QSL("\\\\?\\") + "c:\\Projekty\\build\\src\\textosaurus\\plugins\\spellcheck\\dict\\index.dic";

  Hunspell *spell = new Hunspell(aff.toUtf8().constData(), dic.toUtf8().constData());

  auto sp = spell->spell(QString("termín").toStdString());

  auto sss = spell->suggest(QString("Pepíčk").toUtf8().toStdString());
  auto xxx = QString(QByteArray::fromStdString(sss.at(2)));

  QMessageBox::information(nullptr, "Example plugin loaded", "Example plugin loaded");
}

void SpellcheckPlugin::stop() {
  QMessageBox::information(nullptr, "Example plugin stopping", "Example plugin stopping");
}
