#ifndef TEMPLATESMENU_H
#define TEMPLATESMENU_H

#include <QWidget>
#include <QFileDialog>
#include <QJsonObject>
#include <QTreeWidgetItem>

#include "dollarwriter.h"

namespace Ui {
class TemplatesMenu;
}

class TemplatesMenu : public QWidget
{
  Q_OBJECT

public:
  explicit TemplatesMenu(QWidget *parent = nullptr);
  ~TemplatesMenu();

private slots:
  void on_pb_reset_clicked();

  void on_pb_create_dir_clicked();

  void on_pb_create_file_clicked();

  void on_pb_delete_clicked();

  void on_pb_unselect_clicked();

  void on_pb_confirm_clicked();

  void on_pb_rewrite_file_clicked();

  void on_comb_project_language_textActivated(const QString &arg1);

  void on_pb_select_template_clicked();

signals:
  void dir_name(const QString& str);
  void file_name(const QString& str);
  void file_content(const QString& str);

private:
  QJsonObject create_json_struct(QTreeWidgetItem* tree);
  void parse_element_json(QTreeWidgetItem *item, const QJsonObject json);
  void fill_tree(QTreeWidgetItem *item, const QJsonArray &array);
  void create_dir_in_tree(const QString& str);
  void create_file_in_tree(const QStringList& str);
  void create_discription_in_file(const QString& str, QTreeWidgetItem *file);
  bool check_select_in_tree();
  bool check_select_in_tree_file();
  bool check_select_in_tree_dir();
  void rename_dir(const QString& str);
  void rename_file(const QStringList& str);

private:
  QDialog* file_dialog;
  QWidget* language_form;
  DollarWriter* dollar_writer;
  Ui::TemplatesMenu *ui;
};

#endif // TEMPLATESMENU_H
