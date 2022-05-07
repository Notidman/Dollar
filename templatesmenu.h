#ifndef TEMPLATESMENU_H
#define TEMPLATESMENU_H

#include <QWidget>
#include <QFileDialog>

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

  void on_pb_rename_file_clicked();

  void name_item(QString str);

  void on_pb_unselect_clicked();

  void on_pb_set_defauilt_path_clicked();

  void on_comb_project_language_activated(const QString &arg1);

private:
  void create_item_in_tree(QString str);

private:
  QDialog* file_dialog;
  std::unique_ptr<QWidget> language_form;
  Ui::TemplatesMenu *ui;
};

#endif // TEMPLATESMENU_H
