// For license of this file, see <project-root-folder>/LICENSE.md.

#include "exampleplugin.h"

#include "libtextosaurus/common/miscellaneous/settings.h"
#include "libtextosaurus/saurus/miscellaneous/textapplication.h"
#include "libtextosaurus/saurus/miscellaneous/textapplicationsettings.h"
#include "libtextosaurus/saurus/gui/tabwidget.h"
#include "libtextosaurus/saurus/gui/texteditor.h"

#include <QMessageBox>
#include <QAction>
#include <QLabel>
#include <QLayout>

ExamplePlugin::ExamplePlugin(QObject *parent) {
  Q_UNUSED(parent)
}

ExamplePlugin::~ExamplePlugin() {
  qDebug("Destroying ExamplePlugin instance.");
}


QString ExamplePlugin::name() const {
  return tr("Example Plugin");
}

QString ExamplePlugin::id() const {
  return QSL("io.github.martinrotter.textosaurus.example");
}

QList<BaseSidebar*> ExamplePlugin::sidebars() {
  return {};
}

QList<QAction*> ExamplePlugin::userActions() {
  return {
    new QAction(tr("Sample Action"), this)
  };
}

void ExamplePlugin::start(
    QWidget *main_form_widget, TextApplication *text_app,
    Settings *settings, IconFactory *icon_factory,
    WebFactory *web_factory) {

  m_mainWidget = main_form_widget;

  QMessageBox::information(nullptr, "Example plugin loaded", "Example plugin loaded");

  m_widgetInfo = new QWidget(main_form_widget, Qt::Popup | Qt::WindowStaysOnTopHint);
  m_lblInfo = new QLabel(m_widgetInfo);
  QHBoxLayout *lay = new QHBoxLayout(m_widgetInfo);

  m_widgetInfo->setLayout(lay);
  m_widgetInfo->layout()->addWidget(m_lblInfo);

  connect(text_app->tabWidget(), &TabWidget::currentChanged, [text_app, this](int index) {
    if (index >= 0) {
      TextEditor* editor = text_app->tabWidget()->currentEditor();
      connect(editor, &TextEditor::updateUi, this, &ExamplePlugin::onUpdateUi, Qt::ConnectionType::UniqueConnection);

      //text_app->tabWidget()->currentEditor()->appendText(5, "123456789");
    }
  });
}

void ExamplePlugin::stop() {
  QMessageBox::information(nullptr, "Example plugin stopping", "Example plugin stopping");
}

void ExamplePlugin::onUpdateUi(int updated) {
  TextEditor* editor = qobject_cast<TextEditor*>(sender());

  if (editor != nullptr) {
    QByteArray sel_text = editor->getSelText();

    if (sel_text.isEmpty()) {
      // hide
      m_widgetInfo->hide();
    }
    else {
      auto px = editor->pointXFromPosition(editor->currentPos());
      auto py = editor->pointYFromPosition(editor->currentPos());
      QPoint point(px, py);

      QPoint glob_point = editor->mapToGlobal(point);

      // show info
      m_lblInfo->setText(sel_text);
      m_widgetInfo->show();
      m_widgetInfo->setGeometry(glob_point.x(), glob_point.y(), 32, 32);
    }
  }
}
