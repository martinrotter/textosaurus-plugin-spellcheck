// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef SPELLCHECKPLUGIN_H
#define SPELLCHECKPLUGIN_H

#include <qobject.h>

#include "libtextosaurus/saurus/plugin-system/pluginbase.h"

#include <QtGlobal>

class QLabel;

class TEXTOSAURUS_DLLSPEC_EXPORT SpellcheckPlugin : public QObject, public PluginBase {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "io.github.martinrotter.textosaurus.spellcheck" FILE "plugin.json")
  Q_INTERFACES(PluginBase)

  public:
    explicit SpellcheckPlugin(QObject* parent = nullptr);
    virtual ~SpellcheckPlugin() override;

    virtual QString name() const override;
    virtual QString id() const override;
    virtual QList<BaseSidebar*> sidebars() override;
    virtual QList<QAction*> userActions() override;
    virtual void start(const QString& library_file, QWidget* main_form_widget, TextApplication* text_app,
                       Settings* settings, IconFactory* icon_factory, WebFactory* web_factory) override;
    virtual void stop() override;
};

#endif // SPELLCHECKPLUGIN_H
